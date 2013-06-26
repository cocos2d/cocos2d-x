/****************************************************************************
 Copyright (c) 2010-2013 cocos2d-x.org
 Copyright (c) 2013 James Chen
 
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

"[WebSocket module] is based in part on the work of the libwebsockets  project
(http://libwebsockets.org)"

 ****************************************************************************/

#include "WebSocket.h"
#include <pthread.h>
#include <queue>
#include <signal.h>
#include <errno.h>

NS_CC_EXT_BEGIN

class WsMessage
{
public:
    WsMessage() : what(0), obj(NULL){}
    unsigned int what; // message type
    void* obj;
};

/**
 *  @brief Websocket thread helper, it's used for sending message between UI thread and websocket thread.
 */
class WsThreadHelper : public cocos2d::CCObject
{
public:
    WsThreadHelper();
    ~WsThreadHelper();
        
    // Creates a new thread
    bool createThread(const WebSocket& ws);
    // Quits sub-thread (websocket thread).
    void quitSubThread();
    
    // Schedule callback function
    virtual void update(float dt);
    
    // Sends message to UI thread. It's needed to be invoked in sub-thread.
    void sendMessageToUIThread(WsMessage *msg);
    
    // Sends message to sub-thread(websocket thread). It's needs to be invoked in UI thread.
    void sendMessageToSubThread(WsMessage *msg);
    
    // Waits the sub-thread (websocket thread) to exit,
    void joinSubThread();
    
    
protected:
    friend class WsThreadEntry;
    void* wsThreadEntryFunc(void* arg);
    
private:
    std::list<WsMessage*>* _UIWsMessageQueue;
    std::list<WsMessage*>* _subThreadWsMessageQueue;
    pthread_mutex_t _UIWsMessageQueueMutex;
    pthread_mutex_t _subThreadWsMessageQueueMutex;
    pthread_t  _subThreadInstance;
    WebSocket* _ws;
    bool _needQuit;
    friend class WebSocket;
};

// Wrapper for converting websocket callback from static function to member function of WebSocket class.
class WebSocketCallbackWrapper {
public:
    
    static int onSocketCallback(struct libwebsocket_context *ctx,
                                struct libwebsocket *wsi,
                                enum libwebsocket_callback_reasons reason,
                                void *user, void *in, size_t len)
    {
        // Gets the user data from context. We know that it's a 'WebSocket' instance.
        WebSocket* wsInstance = (WebSocket*)libwebsocket_context_user(ctx);
        if (wsInstance)
        {
            return wsInstance->onSocketCallback(ctx, wsi, reason, user, in, len);
        }
        return 0;
    }
};

// Implementation of WsThreadHelper
WsThreadHelper::WsThreadHelper()
: _ws(NULL)
, _needQuit(false)
{
    _UIWsMessageQueue = new std::list<WsMessage*>();
    pthread_mutex_init(&_UIWsMessageQueueMutex, NULL);
    _subThreadWsMessageQueue = new std::list<WsMessage*>();
    pthread_mutex_init(&_subThreadWsMessageQueueMutex, NULL);
    
    CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
}

WsThreadHelper::~WsThreadHelper()
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
    pthread_mutex_destroy(&_UIWsMessageQueueMutex);
    pthread_mutex_destroy(&_subThreadWsMessageQueueMutex);
    delete _UIWsMessageQueue;
    delete _subThreadWsMessageQueue;
}

// For converting static function to member function
class WsThreadEntry
{
public:
    static void* entry(void* arg)
    {
        WsThreadHelper* self = static_cast<WsThreadHelper*>(arg);
        return self->wsThreadEntryFunc(arg);
    }
};

bool WsThreadHelper::createThread(const WebSocket& ws)
{
    _ws = const_cast<WebSocket*>(&ws);
    pthread_attr_t attr;
    pthread_attr_init (&attr);
//    pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
    
    // Creates websocket thread
	if (0 == pthread_create(&_subThreadInstance, &attr, WsThreadEntry::entry, this))
    {
        return true;
    }
    return false;
}

void WsThreadHelper::quitSubThread()
{
    _needQuit = true;
}

void* WsThreadHelper::wsThreadEntryFunc(void* arg)
{
    _ws->onSubThreadStarted();
    
    while (!_needQuit)
    {
        if (_ws->onSubThreadLoop())
        {
            break;
        }
    }
    
    _ws->onSubThreadEnded();

    return (void*)0;
}

void WsThreadHelper::sendMessageToUIThread(WsMessage *msg)
{
    pthread_mutex_lock(&_UIWsMessageQueueMutex);
    _UIWsMessageQueue->push_back(msg);
    pthread_mutex_unlock(&_UIWsMessageQueueMutex);
}

void WsThreadHelper::sendMessageToSubThread(WsMessage *msg)
{
    pthread_mutex_lock(&_subThreadWsMessageQueueMutex);
    _subThreadWsMessageQueue->push_back(msg);
    pthread_mutex_unlock(&_subThreadWsMessageQueueMutex);
}

void WsThreadHelper::joinSubThread()
{
    void* ret = NULL;
    pthread_join(_subThreadInstance, &ret);
}

void WsThreadHelper::update(float dt)
{
    WsMessage *msg = NULL;

    // Returns quickly if no message
    pthread_mutex_lock(&_UIWsMessageQueueMutex);
    if (0 == _UIWsMessageQueue->size())
    {
        pthread_mutex_unlock(&_UIWsMessageQueueMutex);
        return;
    }
    
    // Gets message
    msg = *(_UIWsMessageQueue->begin());
    _UIWsMessageQueue->pop_front();
    pthread_mutex_unlock(&_UIWsMessageQueueMutex);
    
    if (_ws)
    {
        _ws->onUIThreadReceiveMessage(msg);
    }
    
    CC_SAFE_DELETE(msg);
}

enum WS_MSG {
    WS_MSG_TO_SUBTRHEAD_SENDING_STRING = 0,
    WS_MSG_TO_SUBTRHEAD_SENDING_BINARY,
    WS_MSG_TO_UITHREAD_OPEN,
    WS_MSG_TO_UITHREAD_MESSAGE,
    WS_MSG_TO_UITHREAD_ERROR,
    WS_MSG_TO_UITHREAD_CLOSE
};

WebSocket::WebSocket()
: _readyState(kStateConnecting)
, _port(80)
, _wsHelper(NULL)
, _wsInstance(NULL)
, _wsContext(NULL)
, _delegate(NULL)
, _SSLConnection(0)
, _wsProtocols(NULL)
{
}

WebSocket::~WebSocket()
{
    close();
    CC_SAFE_RELEASE_NULL(_wsHelper);
    
    for (int i = 0; _wsProtocols[i].callback != NULL; ++i) {
        CC_SAFE_DELETE_ARRAY(_wsProtocols[i].name);
    }
	CC_SAFE_DELETE_ARRAY(_wsProtocols);
}

bool WebSocket::init(const Delegate& delegate,
                     const std::string& url,
                     const std::vector<std::string>* protocols/* = NULL*/)
{
    bool ret = false;
    bool useSSL = false;
    std::string host = url;
    int pos = 0;
    int port = 80;
    
    _delegate = const_cast<Delegate*>(&delegate);
    
    //ws://
    pos = host.find("ws://");
    if (pos == 0){
        host.erase(0,5);
    }
    
    pos = host.find("wss://");
    if (pos == 0)
    {
        host.erase(0,6);
        useSSL = true;
    }
    
    pos = host.find(":");
    if(pos >= 0){
        port = atoi(host.substr(pos+1, host.size()).c_str());
    }
    
    pos = host.find("/", pos);
    std::string path = "/";
    if(pos >= 0){
        path += host.substr(pos + 1, host.size());
    }
    
    pos = host.find(":");
    if(pos >= 0){
        host.erase(pos, host.size());
    }

    
    _host = host;
    _port = port;
    _path = path;
    _SSLConnection = useSSL ? 1 : 0;
    
    int protocolCount = 0;
    if (protocols && protocols->size() > 0)
    {
        protocolCount = protocols->size();
    }
    else
    {
        protocolCount = 1;
    }
    
	_wsProtocols = new libwebsocket_protocols[protocolCount+1];
	memset(_wsProtocols, 0, sizeof(libwebsocket_protocols)*(protocolCount+1));

    if (protocols)
    {
        int i = 0;
        for (std::vector<std::string>::const_iterator iter = protocols->begin(); iter != protocols->end(); ++iter, ++i) {
            char* name = new char[(*iter).length()+1];
            strcpy(name, (*iter).c_str());
            _wsProtocols[i].name = name;
            _wsProtocols[i].callback = WebSocketCallbackWrapper::onSocketCallback;
        }
    }
    else
    {
        char* name = new char[20];
        strcpy(name, "default-protocol");
        _wsProtocols[0].name = name;
        _wsProtocols[0].callback = WebSocketCallbackWrapper::onSocketCallback;
    }
    
    // WebSocket thread needs to be invoked at the end of this method.
    _wsHelper = new WsThreadHelper();
    ret = _wsHelper->createThread(*this);
    
    return ret;
}

void WebSocket::send(const std::string& message)
{
    if (_readyState == kStateOpen)
    {
        // In main thread
        WsMessage* msg = new WsMessage();
        msg->what = WS_MSG_TO_SUBTRHEAD_SENDING_STRING;
        Data* data = new Data();
        data->bytes = new char[message.length()+1];
        strcpy(data->bytes, message.c_str());
        data->len = message.length();
        msg->obj = data;
        _wsHelper->sendMessageToSubThread(msg);
    }
}

void WebSocket::send(const unsigned char* binaryMsg, unsigned int len)
{
    CCAssert(binaryMsg != NULL && len > 0, "parameter invalid.");

    if (_readyState == kStateOpen)
    {
        // In main thread
        WsMessage* msg = new WsMessage();
        msg->what = WS_MSG_TO_SUBTRHEAD_SENDING_BINARY;
        Data* data = new Data();
        data->bytes = new char[len];
        memcpy((void*)data->bytes, (void*)binaryMsg, len);
        data->len = len;
        msg->obj = data;
        _wsHelper->sendMessageToSubThread(msg);
    }
}

void WebSocket::close()
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(_wsHelper);
    
    if (_readyState == kStateClosing || _readyState == kStateClosed)
        return;

    CCLOG("websocket (%p) connection closed by client", this);
    _readyState = kStateClosed;

    _wsHelper->joinSubThread();
    
    // onClose callback needs to be invoked at the end of this method
    // since websocket instance may be deleted in 'onClose'.
    _delegate->onClose(this);
}

WebSocket::State WebSocket::getReadyState()
{
    return _readyState;
}

int WebSocket::onSubThreadLoop()
{
    if (_readyState == kStateClosed || _readyState == kStateClosing)
    {
        libwebsocket_context_destroy(_wsContext);
        // return 1 to exit the loop.
        return 1;
    }
    
    if (_wsContext && _readyState != kStateClosed && _readyState != kStateClosing)
    {
        libwebsocket_service(_wsContext, 0);
    }
    
    // Sleep 50 ms
#ifdef WIN32
	Sleep(50);
#else
    usleep(50000);
#endif
    // return 0 to continue the loop.
    return 0;
}

void WebSocket::onSubThreadStarted()
{
	struct lws_context_creation_info info;
	memset(&info, 0, sizeof info);
    
	/*
	 * create the websocket context.  This tracks open connections and
	 * knows how to route any traffic and which protocol version to use,
	 * and if each connection is client or server side.
	 *
	 * For this client-only demo, we tell it to not listen on any port.
	 */
    
	info.port = CONTEXT_PORT_NO_LISTEN;
	info.protocols = _wsProtocols;
#ifndef LWS_NO_EXTENSIONS
	info.extensions = libwebsocket_get_internal_extensions();
#endif
	info.gid = -1;
	info.uid = -1;
    info.user = (void*)this;
    
	_wsContext = libwebsocket_create_context(&info);
    
	if(NULL != _wsContext){
        _readyState = kStateConnecting;
        std::string name;
        for (int i = 0; _wsProtocols[i].callback != NULL; ++i) {
            name += (_wsProtocols[i].name);
            if (_wsProtocols[i+1].callback != NULL)
            {
                name += ", ";
            }
        }
        _wsInstance = libwebsocket_client_connect(_wsContext, _host.c_str(), _port, _SSLConnection,
                                             _path.c_str(), _host.c_str(), _host.c_str(),
                                             name.c_str(), -1);
	}
}

void WebSocket::onSubThreadEnded()
{

}

int WebSocket::onSocketCallback(struct libwebsocket_context *ctx,
                     struct libwebsocket *wsi,
                     enum libwebsocket_callback_reasons reason,
                     void *user, void *in, size_t len)
{
	//CCLOG("socket callback for %d reason", reason);
    CCAssert(_wsContext == NULL || ctx == _wsContext, "Invalid context.");
    CCAssert(_wsInstance == NULL || wsi == NULL || wsi == _wsInstance, "Invaild websocket instance.");

	switch (reason)
    {
        case LWS_CALLBACK_DEL_POLL_FD:
        case LWS_CALLBACK_PROTOCOL_DESTROY:
        case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
            {
                WsMessage* msg = NULL;
                if (reason == LWS_CALLBACK_CLIENT_CONNECTION_ERROR
                    || (reason == LWS_CALLBACK_PROTOCOL_DESTROY && _readyState == kStateConnecting)
                    || (reason == LWS_CALLBACK_DEL_POLL_FD && _readyState == kStateConnecting)
                    )
                {
                    msg = new WsMessage();
                    msg->what = WS_MSG_TO_UITHREAD_ERROR;
                    _readyState = kStateClosing;
                }
                else if (reason == LWS_CALLBACK_PROTOCOL_DESTROY && _readyState == kStateClosing)
                {
                    msg = new WsMessage();
                    msg->what = WS_MSG_TO_UITHREAD_CLOSE;
                }

                if (msg)
                {
                    _wsHelper->sendMessageToUIThread(msg);
                }
            }
            break;
        case LWS_CALLBACK_CLIENT_ESTABLISHED:
            {
                WsMessage* msg = new WsMessage();
                msg->what = WS_MSG_TO_UITHREAD_OPEN;
                _readyState = kStateOpen;
                /*
                 * start the ball rolling,
                 * LWS_CALLBACK_CLIENT_WRITEABLE will come next service
                 */
                libwebsocket_callback_on_writable(ctx, wsi);
                _wsHelper->sendMessageToUIThread(msg);
            }
            break;
            
        case LWS_CALLBACK_CLIENT_WRITEABLE:
            {
                pthread_mutex_lock(&_wsHelper->_subThreadWsMessageQueueMutex);
                std::list<WsMessage*>::iterator iter = _wsHelper->_subThreadWsMessageQueue->begin();
                
                int bytesWrite = 0;
                for (; iter != _wsHelper->_subThreadWsMessageQueue->end(); ++iter) {

                    WsMessage* subThreadMsg = *iter;
                    
                    if ( WS_MSG_TO_SUBTRHEAD_SENDING_STRING == subThreadMsg->what
                      || WS_MSG_TO_SUBTRHEAD_SENDING_BINARY == subThreadMsg->what)
                    {
                        Data* data = (Data*)subThreadMsg->obj;

                        unsigned char* buf = new unsigned char[LWS_SEND_BUFFER_PRE_PADDING
                                                               + data->len + LWS_SEND_BUFFER_POST_PADDING];
                        
                        memset(&buf[LWS_SEND_BUFFER_PRE_PADDING], 0, data->len);
                        memcpy((char*)&buf[LWS_SEND_BUFFER_PRE_PADDING], data->bytes, data->len);
                        
                        enum libwebsocket_write_protocol writeProtocol;
                        
                        if (WS_MSG_TO_SUBTRHEAD_SENDING_STRING == subThreadMsg->what)
                        {
                            writeProtocol = LWS_WRITE_TEXT;
                        }
                        else
                        {
                            writeProtocol = LWS_WRITE_BINARY;
                        }
                        
                        bytesWrite = libwebsocket_write(wsi,  &buf[LWS_SEND_BUFFER_PRE_PADDING], data->len, writeProtocol);
                        
                        if (bytesWrite < 0) {
                            CCLOGERROR("%s", "libwebsocket_write error...");
                        }
                        if (bytesWrite < data->len) {
                            CCLOGERROR("Partial write LWS_CALLBACK_CLIENT_WRITEABLE\n");
                        }
                        
                        CC_SAFE_DELETE_ARRAY(data->bytes);
                        CC_SAFE_DELETE(data);
                        CC_SAFE_DELETE_ARRAY(buf);
                    }
                    
                    CC_SAFE_DELETE(subThreadMsg);
                }

                _wsHelper->_subThreadWsMessageQueue->clear();
                
                pthread_mutex_unlock(&_wsHelper->_subThreadWsMessageQueueMutex);
                
                /* get notified as soon as we can write again */
                
                libwebsocket_callback_on_writable(ctx, wsi);
            }
            break;
            
        case LWS_CALLBACK_CLOSED:
            {
                
                CCLOG("%s", "connection closing..");

                _wsHelper->quitSubThread();
                
                if (_readyState != kStateClosed)
                {
                    WsMessage* msg = new WsMessage();
                    _readyState = kStateClosed;
                    msg->what = WS_MSG_TO_UITHREAD_CLOSE;
                    _wsHelper->sendMessageToUIThread(msg);
                }
            }
            break;
            
        case LWS_CALLBACK_CLIENT_RECEIVE:
            {
                if (in && len > 0)
                {
                    WsMessage* msg = new WsMessage();
                    msg->what = WS_MSG_TO_UITHREAD_MESSAGE;
                    
                    char* bytes = NULL;
                    Data* data = new Data();
                    
                    if (lws_frame_is_binary(wsi))
                    {
                        
                        bytes = new char[len];
                        data->isBinary = true;
                    }
                    else
                    {
                        bytes = new char[len+1];
                        bytes[len] = '\0';
                        data->isBinary = false;
                    }

                    memcpy(bytes, in, len);
                    
                    data->bytes = bytes;
                    data->len = len;
                    msg->obj = (void*)data;
                    
                    _wsHelper->sendMessageToUIThread(msg);
                }
            }
            break;
        default:
            break;
        
	}
    
	return 0;
}

void WebSocket::onUIThreadReceiveMessage(WsMessage* msg)
{
    switch (msg->what) {
        case WS_MSG_TO_UITHREAD_OPEN:
            {
                _delegate->onOpen(this);
            }
            break;
        case WS_MSG_TO_UITHREAD_MESSAGE:
            {
                Data* data = (Data*)msg->obj;
                _delegate->onMessage(this, *data);
                CC_SAFE_DELETE_ARRAY(data->bytes);
                CC_SAFE_DELETE(data);
            }
            break;
        case WS_MSG_TO_UITHREAD_CLOSE:
            {
                _delegate->onClose(this);
            }
            break;
        case WS_MSG_TO_UITHREAD_ERROR:
            {
                // FIXME: The exact error needs to be checked.
                WebSocket::ErrorCode err = kErrorConnectionFailure;
                _delegate->onError(this, err);
            }
            break;
        default:
            break;
    }
}

NS_CC_EXT_END
