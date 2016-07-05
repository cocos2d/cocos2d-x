/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
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

"[WebSocket module] is based in part on the work of the libwebsockets  project
(http://libwebsockets.org)"

 ****************************************************************************/

#include "platform/CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_EMSCRIPTEN)

#include "WebSocket.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include <emscripten.h>


NS_CC_BEGIN

namespace network {
    
extern "C"
{
    void WebSocket_init(void *userData, const char *);
    void WebSocket_send(void *userData, const char *);
    void WebSocket_send_data(void *userData, unsigned char *, unsigned int);
    void WebSocket_close(void *userData);
    
    typedef void (*socket_callback)(void* userData, unsigned char *msg, int length);
    typedef void (*socket_close_callback)(void* userData, int err, unsigned char *msg, int length);
    typedef void (*socket_error_callback)(void* userData);
    
    void WebSocket_set_socket_open_callback(void *userData, socket_callback callback);
    void WebSocket_set_socket_listen_callback(void *userData, socket_callback callback);
    void WebSocket_set_socket_connection_callback(void *userData, socket_callback callback);
    void WebSocket_set_socket_message_callback(void *userData, socket_callback callback);
    
    void WebSocket_set_socket_error_callback(void *userData, socket_error_callback callback);
    void WebSocket_set_socket_close_callback(void *userData, socket_close_callback callback);
};
    
class WebSocketCallbackWrapper {
public:
    
    static void onOpen(void* userData, unsigned char *msg, int length)
    {
        WebSocket* webSocket = static_cast<WebSocket*>(userData);
        if (webSocket)
            webSocket->onConnectionOpened();
    }
    
    static void onMessage(void* userData, unsigned char *msg, int length)
    {
        WebSocket* webSocket = static_cast<WebSocket*>(userData);
        if (webSocket)
            webSocket->onClientReceivedData((void*)msg, (ssize_t)length);
    }
    
    static void onError(void* userData)
    {
        WebSocket* webSocket = static_cast<WebSocket*>(userData);
        
        if (webSocket)
            webSocket->onConnectionError();
    }
    
    static void onClose(void* userData, int err, unsigned char* msg, int length)
    {
        WebSocket* webSocket = static_cast<WebSocket*>(userData);
        
        CCLOG("WebSocketCallbackWrapper::onClose: errorCode:%i %s", err, (char*)msg);
        
        if (webSocket)
            webSocket->onConnectionClosed();
    }
};
    

WebSocket::WebSocket()
    : _readyState(State::CONNECTING)
    , _port(80)
    , _wsHelper(nullptr)
    , _wsInstance(nullptr)
    , _wsContext(nullptr)
    , _isDestroyed(std::make_shared<std::atomic<bool>>(false))
    , _delegate(nullptr)
    , _SSLConnection(0)
    , _wsProtocols(nullptr)
{
}

WebSocket::~WebSocket()
{
    close();
}
    
bool WebSocket::init(const Delegate& delegate,
                     const std::string& url,
                     const std::vector<std::string>* protocols/* = nullptr*/)
{
    _delegate = const_cast<Delegate*>(&delegate);
    
    WebSocket_init(this, url.c_str());
    
    WebSocket_set_socket_error_callback(static_cast<void*>(this), &WebSocketCallbackWrapper::onError);
    WebSocket_set_socket_open_callback(static_cast<void*>(this), &WebSocketCallbackWrapper::onOpen);
    WebSocket_set_socket_message_callback(static_cast<void*>(this), &WebSocketCallbackWrapper::onMessage);
    WebSocket_set_socket_close_callback(static_cast<void*>(this), &WebSocketCallbackWrapper::onClose);
    _readyState = State::CONNECTING;
    
    return true;
}

void WebSocket::send(const std::string& message)
{
    if (_readyState == State::OPEN)
    {
        WebSocket_send(this, message.c_str());
    }
}

void WebSocket::send(const unsigned char* binaryMsg, unsigned int len)
{
    if (_readyState == State::OPEN)
    {
        CCASSERT(binaryMsg != nullptr && len > 0, "parameter invalid.");
        
        WebSocket_send_data(this, (unsigned char*)binaryMsg, len);
    }
}

void WebSocket::close()
{
    if (_readyState == State::CLOSING || _readyState == State::CLOSED)
    {
        return;
    }
    
    _readyState = State::CLOSED;
    
    // onClose callback needs to be invoked at the end of this method
    // since websocket instance may be deleted in 'onClose'.
    _delegate->onClose(this);
    
    WebSocket_close(this);
}

WebSocket::State WebSocket::getReadyState()
{
    return _readyState;
}

void WebSocket::onSubThreadLoop()
{
}

void WebSocket::onSubThreadStarted()
{
}

void WebSocket::onSubThreadEnded()
{
}

int WebSocket::onSocketCallback(struct lws *wsi, int reason, void *user, void *in, ssize_t len)
{
	return 0;
}
    
void WebSocket::onClientWritable()
{
    
}
    
void WebSocket::onClientReceivedData(void* in, ssize_t len)
{
    CCLOG("Receiving data:len=%d\n", (int)len);
    WebSocket::Data data;
    data.isBinary = true;
    data.bytes = (char*)in;
    data.len = len;
    _delegate->onMessage(this, data);
}

void WebSocket::onConnectionOpened()
{
    _readyState = State::OPEN;
    _delegate->onOpen(this);
}

void WebSocket::onConnectionError()
{
    CCLOG("WebSocket (%p) onConnectionError ...\n", this);
    _readyState = State::CLOSING;
    _delegate->onError(this, ErrorCode::CONNECTION_FAILURE);
}

void WebSocket::onConnectionClosed()
{
    if (_readyState == State::CLOSED)
    {
        CCLOG("onConnectionClosed: WebSocket (%p) was closed, no need to close it again!\n", this);
        return;
    }
    
    CCLOG("WebSocket (%p) onConnectionClosed ...\n", this);
    _readyState = State::CLOSED;
    _delegate->onClose(this);
}

}

NS_CC_END

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_EMSCRIPTEN)
