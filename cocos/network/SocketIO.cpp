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
    void emit(std::string endpoint, std::string eventname, std::string args);


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
    pre << "http://" << _uri << "/socket.io/1";

    HttpRequest* request = new HttpRequest();
    request->setUrl(pre.str().c_str());
    request->setRequestType(HttpRequest::Type::GET);

    request->setResponseCallback(CC_CALLBACK_2(SIOClientImpl::handshakeResponse, this));
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

    pos = res.find(":");
    if(pos != std::string::npos)
    {
        sid = res.substr(0, pos);
        res.erase(0, pos+1);
    }

    pos = res.find(":");
    if(pos != std::string::npos)
    {
        heartbeat = atoi(res.substr(pos+1, res.size()).c_str());
    }

    pos = res.find(":");
    if(pos != std::string::npos)
    {
        timeout = atoi(res.substr(pos+1, res.size()).c_str());
    }

    _sid = sid;
    _heartbeat = heartbeat;
    _timeout = timeout;

    openSocket();

    return;

}

void SIOClientImpl::openSocket()
{
    log("SIOClientImpl::openSocket() called");

    std::stringstream s;
    s << _uri << "/socket.io/1/websocket/" << _sid;

    _ws = new WebSocket();
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
        std::string s = "0::";

        _ws->send(s);

        log("Disconnect sent");

        _ws->close();
    }

    Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);

    _connected = false;

    SocketIO::getInstance()->removeSocket(_uri);
}

SIOClientImpl* SIOClientImpl::create(const std::string& host, int port)
{
    SIOClientImpl *s = new SIOClientImpl(host, port);

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
    std::string path = endpoint == "/" ? "" : endpoint;

    std::string s = "1::" + path;

    _ws->send(s);
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

        std::string s = "0::" + path;

        _ws->send(s);
    }
}

void SIOClientImpl::heartbeat(float dt)
{
    std::string s = "2::";

    _ws->send(s);

    log("Heartbeat sent");
}


void SIOClientImpl::send(std::string endpoint, std::string s)
{
    std::stringstream pre;

    std::string path = endpoint == "/" ? "" : endpoint;

    pre << "3::" << path << ":" << s;

    std::string msg = pre.str();

    log("sending message: %s", msg.c_str());

    _ws->send(msg);
}

void SIOClientImpl::emit(std::string endpoint, std::string eventname, std::string args)
{
    std::stringstream pre;

    std::string path = endpoint == "/" ? "" : endpoint;

    pre << "5::" << path << ":{\"name\":\"" << eventname << "\",\"args\":" << args << "}";

    std::string msg = pre.str();

    log("emitting event with data: %s", msg.c_str());

    _ws->send(msg);
}

void SIOClientImpl::onOpen(WebSocket* ws)
{
    _connected = true;

    SocketIO::getInstance()->addSocket(_uri, this);

    for (auto iter = _clients.begin(); iter != _clients.end(); ++iter)
    {
        iter->second->onOpen();
    }

    Director::getInstance()->getScheduler()->schedule(schedule_selector(SIOClientImpl::heartbeat), this, (_heartbeat * .9f), false);

    log("SIOClientImpl::onOpen socket connected!");
}

void SIOClientImpl::onMessage(WebSocket* ws, const WebSocket::Data& data)
{
    log("SIOClientImpl::onMessage received: %s", data.bytes);

    int control = atoi(&data.bytes[0]);

    std::string payload, msgid, endpoint, s_data, eventname;
    payload = data.bytes;

    size_t pos, pos2;

    pos = payload.find(":");
    if(pos != std::string::npos ) {
        payload.erase(0, pos+1);
    }

    pos = payload.find(":");
    if(pos != std::string::npos ) {
        msgid = atoi(payload.substr(0, pos+1).c_str());
    }
    payload.erase(0, pos+1);

    pos = payload.find(":");
    if(pos != std::string::npos)
    {
        endpoint = payload.substr(0, pos);
        payload.erase(0, pos+1);
    }
    else
    {
        endpoint = payload;
    }

    if (endpoint == "") endpoint = "/";


    s_data = payload;
    SIOClient *c = nullptr;
    c = getClient(endpoint);
    if (c == nullptr) log("SIOClientImpl::onMessage client lookup returned nullptr");

    switch(control)
    {
        case 0:
            log("Received Disconnect Signal for Endpoint: %s\n", endpoint.c_str());
            if(c) c->receivedDisconnect();
            disconnectFromEndpoint(endpoint);
            break;
        case 1:
            log("Connected to endpoint: %s \n",endpoint.c_str());
            if(c) c->onConnect();
            break;
        case 2:
            log("Heartbeat received\n");
            break;
        case 3:
            log("Message received: %s \n", s_data.c_str());
            if(c) c->getDelegate()->onMessage(c, s_data);
            break;
        case 4:
            log("JSON Message Received: %s \n", s_data.c_str());
            if(c) c->getDelegate()->onMessage(c, s_data);
            break;
        case 5:
            log("Event Received with data: %s \n", s_data.c_str());

            if(c)
            {
                eventname = "";
                pos = s_data.find(":");
                pos2 = s_data.find(",");
                if(pos2 > pos)
                {
                    s_data = s_data.substr(pos+1, pos2-pos-1);
                    std::remove_copy(s_data.begin(), s_data.end(),
                         std::back_inserter(eventname), '"');
                }

                c->fireEvent(eventname, payload);
            }

            break;
        case 6:
            log("Message Ack\n");
            break;
        case 7:
            log("Error\n");
            if(c) c->getDelegate()->onError(c, s_data);
            break;
        case 8:
            log("Noop\n");
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
    }

    this->release();
}

void SIOClientImpl::onError(WebSocket* ws, const WebSocket::ErrorCode& error)
{
}

//begin SIOClient methods
SIOClient::SIOClient(const std::string& host, int port, const std::string& path, SIOClientImpl* impl, SocketIO::SIODelegate& delegate)
    : _port(port)
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
        _inst = new SocketIO();

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

    SIOClientImpl* socket = nullptr;
    SIOClient *c = nullptr;

    socket = SocketIO::getInstance()->getSocket(s.str());

    if(socket == nullptr)
    {
        //create a new socket, new client, connect
        socket = SIOClientImpl::create(host, port);

        c = new SIOClient(host, port, path, socket, delegate);

        socket->addClient(path, c);

        socket->connect();
    }
    else
    {
        //check if already connected to endpoint, handle
        c = socket->getClient(path);

        if(c == nullptr)
        {
            c = new SIOClient(host, port, path, socket, delegate);

            socket->addClient(path, c);

            socket->connectToEndpoint(path);
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
