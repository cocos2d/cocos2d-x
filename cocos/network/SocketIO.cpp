/****************************************************************************
 Copyright (c) 2013      Chris Hannon
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

*based on the SocketIO library created by LearnBoost at http://socket.io
*using spec version 1 found at https://github.com/LearnBoost/socket.io-spec

 ****************************************************************************/

#include "SocketIO.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "WebSocket.h"
#include "HttpClient.h"
#include <algorithm>
#include <sstream>

NS_CC_BEGIN

namespace network {

//class declarations
    
    /*
    https://github.com/Automattic/engine.io-protocol
    ENGINE.IO packets:
    0 open
    1 close
    2 ping
    3 pong
    4 message
    5 upgrade
    6 noop
    
    https://github.com/automattic/socket.io-protocol
    SOCKET.IO packets:
    Packet#CONNECT (0)
    Packet#DISCONNECT (1)
    Packet#EVENT (2)
    Packet#ACK (3) (callback)
    Packet#ERROR (4)
    Packet#BINARY_EVENT (5)
    Packet#BINARY_ACK (6)
     */
    
enum class EngineIOPacket {
    EIO_OPEN,
    EIO_CLOSE,
    EIO_PING,
    EIO_PONG,
    EIO_MESSAGE,
    EIO_UPGRADE,
    EIO_NOOP
};
enum class SocketIOPacket {
    SIO_CONNECT,
    SIO_DISCONNECT,
    SIO_EVENT,
    SIO_ACK,
    SIO_ERROR,
    SIO_BINARY_EVENT,
    SIO_BINARY_ACK
};

/**
 *  @brief The implementation of the socket.io connection
 *         Clients/endpoints may share the same impl to accomplish multiplexing on the same websocket
 */
class SIOClientImpl :
    public cocos2d::Ref,
    public WebSocket::Delegate
{
private:
    int _port, _heartbeat, _timeout;
    std::string _host, _sid, _uri;
    bool _connected;

    WebSocket *_ws;

    Map<std::string, SIOClient*> _clients;

public:
    SIOClientImpl(const std::string& host, int port);
    virtual ~SIOClientImpl(void);

    static SIOClientImpl* create(const std::string& host, int port);

    virtual void onOpen(WebSocket* ws);
    virtual void onMessage(WebSocket* ws, const WebSocket::Data& data);
    virtual void onClose(WebSocket* ws);
    virtual void onError(WebSocket* ws, const WebSocket::ErrorCode& error);

    void handleSocketIOPacket(SocketIOPacket packet, std::string& payload);
    SIOClient* getClientFromPayload(std::string& payload);
    std::string getEventNameFromPayload(std::string& payload);
    int getCallbackNumberFromPayload(std::string& payload);

    void upgrade();
    void connect();
    void disconnect();
    bool init();
    void handshake();
    void handshakeResponse(HttpClient *sender, HttpResponse *response);
    void openSocket();
    void heartbeat(float dt);

    SIOClient* getClient(const std::string& endpoint);
    void addClient(const std::string& endpoint, SIOClient* client);

    void connectToEndpoint(const std::string& endpoint);
    void disconnectFromEndpoint(const std::string& endpoint);

    void send(std::string endpoint, std::string s);
    void emit(std::string endpoint, std::string eventname, std::string args, int callbackNumber = -1);

    std::string getUri();
    std::string getSid();
    
    inline bool isConnected() {
        return _connected;
    }
};


//method implementations

//begin SIOClientImpl methods
SIOClientImpl::SIOClientImpl(const std::string& host, int port) :
    _port(port),
    _host(host),
    _connected(false)
{
    std::stringstream s;
    s << host << ":" << port;
    _uri = s.str();

    _ws = nullptr;
}

SIOClientImpl::~SIOClientImpl()
{
    if (_connected)
        disconnect();

    CC_SAFE_DELETE(_ws);
}

void SIOClientImpl::handshake()
{
    log("SIOClientImpl::handshake() called");

    std::stringstream pre;
    pre << "http://" << _uri << "/socket.io/?EIO=3&transport=polling&b64=0";

    HttpRequest* request = new (std::nothrow) HttpRequest();
    request->setUrl(pre.str().c_str());
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback([&](HttpClient* client, HttpResponse* response) {
        handshakeResponse(client, response);
    });
    request->setTag("handshake");

    log("SIOClientImpl::handshake() waiting");

    HttpClient::getInstance()->send(request);

    request->release();

    return;
}

void SIOClientImpl::handshakeResponse(HttpClient *sender, HttpResponse *response)
{
    log("SIOClientImpl::handshakeResponse() called");

    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        log("%s completed", response->getHttpRequest()->getTag());
    }

    long statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag());
    log("response code: %ld", statusCode);

    if (!response->isSucceed())
    {
        log("SIOClientImpl::handshake() failed");
        log("error buffer: %s", response->getErrorBuffer());

        for (auto iter = _clients.begin(); iter != _clients.end(); ++iter)
        {
            iter->second->getDelegate()->onError(iter->second, response->getErrorBuffer());
        }

        return;
    }

    log("SIOClientImpl::handshake() succeeded");

    std::vector<char> *buffer = response->getResponseData();
    std::stringstream s;

    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        s << (*buffer)[i];
    }

    log("SIOClientImpl::handshake() dump data: %s", s.str().c_str());

    std::string res = s.str();
    std::string sid;
    size_t pos = 0;
    int heartbeat = 0, timeout = 0;

    pos = res.find("\"sid\":\"");
    if(pos != std::string::npos)
    {
        res.erase(0, pos+7);
        pos = res.find("\"");
        sid = res.substr(0, pos);
    }

    pos = res.find("\"pingInterval\":");
    if(pos != std::string::npos)
    {
        res.erase(0, pos+15);
        pos = res.find(",");
        heartbeat = atoi(res.substr(0, pos).c_str());
    }

    pos = res.find("\"pingTimeout\":");
    if(pos != std::string::npos)
    {
        res.erase(0, pos+14);
        pos = res.find("}");
        timeout = atoi(res.substr(0, pos).c_str());
    }

    _sid = sid;
    _heartbeat = heartbeat * 0.001;
    _timeout = timeout * 0.001;


    openSocket();

    return;

}
void SIOClientImpl::openSocket()
{
    log("SIOClientImpl::openSocket() called");

    std::stringstream s;
    s << _uri << "/socket.io/?EIO=3&transport=websocket&b64=0&sid=" << _sid;

    _ws = new (std::nothrow) WebSocket();
    if (!_ws->init(*this, s.str()))
    {
        CC_SAFE_DELETE(_ws);
    }

    return;
}

bool SIOClientImpl::init()
{
    log("SIOClientImpl::init() successful");
    return true;
}

void SIOClientImpl::connect()
{
    this->handshake();
}

void SIOClientImpl::disconnect()
{
    if(_ws->getReadyState() == WebSocket::State::OPEN)
    {
        std::stringstream s;
        s << (int)EngineIOPacket::EIO_CLOSE;

        _ws->send(s.str());

        log("Disconnect sent");

        _ws->close();
    }

    Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);

    _connected = false;

    SocketIO::getInstance()->removeSocket(_uri);
}

SIOClientImpl* SIOClientImpl::create(const std::string& host, int port)
{
    SIOClientImpl *s = new (std::nothrow) SIOClientImpl(host, port);

    if (s && s->init())
    {
        return s;
    }

    return nullptr;
}

SIOClient* SIOClientImpl::getClient(const std::string& endpoint)
{
    return _clients.at(endpoint);
}

void SIOClientImpl::addClient(const std::string& endpoint, SIOClient* client)
{
    _clients.insert(endpoint, client);
}

void SIOClientImpl::connectToEndpoint(const std::string& endpoint)
{
    if (endpoint == "/" || !_connected)
    {
        return;
    }

    std::stringstream s;
    s << (int)EngineIOPacket::EIO_MESSAGE << (int)SocketIOPacket::SIO_CONNECT << endpoint;

    _ws->send(s.str());
}

void SIOClientImpl::disconnectFromEndpoint(const std::string& endpoint)
{
    _clients.erase(endpoint);

    if (_clients.empty() || endpoint == "/")
    {
        log("SIOClientImpl::disconnectFromEndpoint out of endpoints, checking for disconnect");

        if(_connected)
            this->disconnect();
    }
    else
    {
        std::string path = endpoint == "/" ? "" : endpoint;

        std::stringstream s;
        s << (int)EngineIOPacket::EIO_MESSAGE << (int)SocketIOPacket::SIO_DISCONNECT << path;

        _ws->send(s.str());
    }
}

void SIOClientImpl::heartbeat(float dt)
{
    std::string s = "2";

    _ws->send(s);

    log("Heartbeat sent");
}


void SIOClientImpl::send(std::string endpoint, std::string s)
{
    std::stringstream pre;

    std::string path = endpoint == "/" ? "" : endpoint;

    pre << "42" << path << (path == "" ? "" : ",") << "[\"message\",\"" << s << "]";

    std::string msg = pre.str();

    log("sending message: %s", msg.c_str());

    _ws->send(msg);
}

void SIOClientImpl::emit(std::string endpoint, std::string eventname, std::string args, int callbackNumber)
{
    std::stringstream pre;

    std::string path = endpoint == "/" ? "" : endpoint;

    pre << "42" << path;
    if (path != "")
    {
        pre << ",";
    }
    if (callbackNumber != -1)
    {
        pre << callbackNumber;
    }
    pre << "[\"" << eventname << "\"," << args << "]";

    std::string msg = pre.str();

    log("emitting event with data: %s", msg.c_str());

    _ws->send(msg);
}

void SIOClientImpl::onOpen(WebSocket* ws)
{
    _connected = true;

    std::stringstream s;
    s << (int)EngineIOPacket::EIO_PING << "probe";
    _ws->send(s.str());

    Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(SIOClientImpl::heartbeat), this, (_heartbeat * .9f), false);

    log("SIOClientImpl::onOpen socket connected!");
}



void SIOClientImpl::onMessage(WebSocket* ws, const WebSocket::Data& data)
{
    log("SIOClientImpl::onMessage received: %s", data.bytes);

    std::string payload;
    payload = data.bytes;
    
    EngineIOPacket engineIOPacket = (EngineIOPacket) atoi(payload.substr(0, 1).c_str());
    switch (engineIOPacket)
    {
        case EngineIOPacket::EIO_PONG:
            //if the string contains "probe", it should send the upgrade packet
            if (payload.substr(1,5) == "probe")
            {
                //send upgrade packages
                upgrade();
            }
            break;
        case EngineIOPacket::EIO_MESSAGE:
            //a message, parse socketio packet
            SocketIOPacket socketIOPacket = (SocketIOPacket) atoi(payload.substr(1, 1).c_str());
            payload.erase(0,2);
            handleSocketIOPacket(socketIOPacket, payload);
            break;
    }
}
    
void SIOClientImpl::upgrade() {
    std::stringstream s;
    s << (int)EngineIOPacket::EIO_UPGRADE;
    _ws->send(s.str());
}

SIOClient* SIOClientImpl::getClientFromPayload(std::string& payload)
{
    std::string endpoint;
    size_t pos;

    if (payload.find("/") == 0)
    {
        pos = payload.find(",");
        if (pos != std::string::npos)
        {
            endpoint = payload.substr(0, pos);
            payload.erase(0, pos + 1);
        }
        else
        {
            endpoint = payload.c_str();
        }
    }
    else 
    {
        endpoint = "/";
    }

    return getClient(endpoint);
}

std::string SIOClientImpl::getEventNameFromPayload(std::string& payload) {
    std::string eventName = "";
    size_t pos;

    pos = payload.find("\"");
    if (pos != std::string::npos)
    {
        payload.erase(0, pos + 1);
        pos = payload.find("\"");
        if (pos != std::string::npos)
        {
            eventName = payload.substr(0, pos);
            payload.erase(0, pos + 2);
            if (payload.size() > 0)
            {
                payload.erase(payload.size() - 1, 1);
            }
        }
    }
    return eventName;
}

int SIOClientImpl::getCallbackNumberFromPayload(std::string& payload)
{
    int callbackNumber = -1;
    size_t pos;

    pos = payload.find("[");
    if (pos != std::string::npos)
    {
        callbackNumber = atoi(payload.substr(0, pos).c_str());
        payload.erase(0, pos + 1);
        if (payload.size() > 0) 
        {
            payload.erase(payload.size() - 1, 1);
        }
    }
    return callbackNumber;
}

void SIOClientImpl::handleSocketIOPacket(SocketIOPacket socketIOPacket, std::string& payload)
{
    std::string eventName;
    int callbackNumber;
    SIOClient* c  = nullptr;

    switch (socketIOPacket) {
        case SocketIOPacket::SIO_CONNECT:
            if (payload == "")
            {
                //loop through all clients (so that other endpoints also have the same connection with the same _sid) and notify them the connection has been made
                for (const auto& client : _clients) {
                    client.second->onOpen();
                }
            }
            c = getClientFromPayload(payload);
            if (c == nullptr)
            {
                log("SIOClientImpl no client found for endpoint: %s", payload.c_str());
            }
            else
            {
                log("SIOClientImpl connected to endpoint: %s", payload.c_str());
                c->onConnect();
            }

            break;
        case SocketIOPacket::SIO_DISCONNECT:
            log("SIOClientImpl disconnect received for: %s", payload.c_str());
            break;
        case SocketIOPacket::SIO_EVENT:
            log("SIOClientImpl event received with data %s", payload.c_str());

            c = getClientFromPayload(payload);
            if (c) {
                eventName = getEventNameFromPayload(payload);
                if (eventName == "") {
                    c->getDelegate()->onMessage(c, payload);
                }
                else
                {
                    c->fireEvent(eventName, payload);
                }
            }

            break;
        case SocketIOPacket::SIO_ACK:
            log("SIOClientImpl event with callback received %s", payload.c_str());
            c = getClientFromPayload(payload);
            if (c)
            {
                callbackNumber = getCallbackNumberFromPayload(payload);
                if (callbackNumber != -1)
                {
                    c->fireCallback(callbackNumber, payload);
                }
            }

            break;
    }
    
    return;
}

void SIOClientImpl::onClose(WebSocket* ws)
{
    if (!_clients.empty())
    {
        for (auto iter = _clients.begin(); iter != _clients.end(); ++iter)
        {
            iter->second->receivedDisconnect();
        }
        _clients.clear();
    }
    _connected = false;
    
    this->release();
}

void SIOClientImpl::onError(WebSocket* ws, const WebSocket::ErrorCode& error)
{
}

std::string SIOClientImpl::getUri()
{
    return _uri;
}

std::string SIOClientImpl::getSid()
{
    return _sid;
}

//begin SIOClient methods
SIOClient::SIOClient(const std::string& host, int port, const std::string& path, SIOClientImpl* impl, SocketIO::SIODelegate& delegate)
    : _port(port)
    , _callbackNumber(0)
    , _host(host)
    , _path(path)
    , _connected(false)
    , _socket(impl)
    , _delegate(&delegate)
{

}

SIOClient::~SIOClient(void)
{
    if (_connected)
    {
        _socket->disconnectFromEndpoint(_path);
    }
}

void SIOClient::onOpen()
{
    if (_path != "/")
    {
        _socket->connectToEndpoint(_path);
    }
}

void SIOClient::onConnect()
{
    _connected = true;
    _delegate->onConnect(this);
}

void SIOClient::send(std::string s)
{
    if (_connected) 
    {
        _socket->send(_path, s);
    }
    else 
    {
        _delegate->onError(this, "Client not yet connected");
    }
}

void SIOClient::emit(std::string eventname, std::string args)
{
    if(_connected)
    {
        _socket->emit(_path, eventname, args);
    }
    else 
    {
        _delegate->onError(this, "Client not yet connected");
    }
}

void SIOClient::emit(std::string eventname, std::string args, SIOEvent callback)
{
    if (_connected)
    {
        _callbackRegistry[_callbackNumber] = callback;
        _socket->emit(_path, eventname, args, _callbackNumber);

        _callbackNumber++;
    }
    else
    {
        _delegate->onError(this, "Client not yet connected");
    }
}

void SIOClient::disconnect()
{
    _connected = false;

    _socket->disconnectFromEndpoint(_path);

    _delegate->onClose(this);

    this->release();
}

void SIOClient::receivedDisconnect()
{
    _connected = false;

    _delegate->onClose(this);

    this->release();
}

void SIOClient::on(const std::string& eventName, SIOEvent e)
{
    _eventRegistry[eventName] = e;
}

void SIOClient::fireEvent(const std::string& eventName, const std::string& data)
{
    log("SIOClient::fireEvent called with event name: %s and data: %s", eventName.c_str(), data.c_str());

    _delegate->fireEventToScript(this, eventName, data);

    if(_eventRegistry[eventName])
    {
        SIOEvent e = _eventRegistry[eventName];

        e(this, data);

        return;
    }

    log("SIOClient::fireEvent no native event with name %s found", eventName.c_str());
}

void SIOClient::fireCallback(const int callbackNumber, const std::string& data)
{
    log("SIOClient::fireCallback called with callbackNumber: %d and data: %s", callbackNumber, data.c_str());

    if (_callbackRegistry[callbackNumber])
    {
        SIOEvent e = _callbackRegistry[callbackNumber];

        e(this, data);

        _callbackRegistry.erase(callbackNumber);

        return;
    }

    log("SIOClient::fireCallback no callback with callbackNumber: %d found", callbackNumber);
}

//begin SocketIO methods
SocketIO *SocketIO::_inst = nullptr;

SocketIO::SocketIO()
{
}

SocketIO::~SocketIO(void)
{
}

SocketIO* SocketIO::getInstance()
{
    if (nullptr == _inst)
        _inst = new (std::nothrow) SocketIO();

    return _inst;
}

void SocketIO::destroyInstance()
{
    CC_SAFE_DELETE(_inst);
}

SIOClient* SocketIO::connect(SocketIO::SIODelegate& delegate, const std::string& uri)
{

    return SocketIO::connect(uri, delegate);

}

SIOClient* SocketIO::connect(const std::string& uri, SocketIO::SIODelegate& delegate)
{
    std::string host = uri;
    int port = 0;
    size_t pos = 0;

    pos = host.find("//");
    if (pos != std::string::npos)
    {
        host.erase(0, pos+2);
    }

    pos = host.find(":");
    if (pos != std::string::npos)
    {
        port = atoi(host.substr(pos+1, host.size()).c_str());
    }

    pos = host.find("/", 0);
    std::string path = "/";
    if (pos != std::string::npos)
    {
        path += host.substr(pos + 1, host.size());
    }

    pos = host.find(":");
    if (pos != std::string::npos)
    {
        host.erase(pos, host.size());
    }
    else if ((pos = host.find("/")) != std::string::npos)
    {
        host.erase(pos, host.size());
    }

    std::stringstream s;
    s << host << ":" << port;

    log("Connect to host: %s\n", s.str().c_str());

    SIOClientImpl* socket = nullptr;
    SIOClient *c = nullptr;

    socket = SocketIO::getInstance()->getSocket(s.str());

    if(socket == nullptr)
    {
        //create a new socket, new client, connect
        socket = SIOClientImpl::create(host, port);

        //register socket
        SocketIO::getInstance()->addSocket(socket->getUri(), socket);

        c = new (std::nothrow) SIOClient(host, port, path, socket, delegate);

        socket->addClient(path, c);

        socket->connect();
    }
    else
    {
        //check if already connected to endpoint, handle
        c = socket->getClient(path);

        if(c == nullptr)
        {
            c = new (std::nothrow) SIOClient(host, port, path, socket, delegate);

            socket->addClient(path, c);

            socket->connectToEndpoint(path);
        }
        
        if (!socket->isConnected()) {
            socket->connect();
        }
    }

    return c;
}

SIOClientImpl* SocketIO::getSocket(const std::string& uri)
{
    return _sockets.at(uri);
}

void SocketIO::addSocket(const std::string& uri, SIOClientImpl* socket)
{
    _sockets.insert(uri, socket);
}

void SocketIO::removeSocket(const std::string& uri)
{
    _sockets.erase(uri);
}

}

NS_CC_END
