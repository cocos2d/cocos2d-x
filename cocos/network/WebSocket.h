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

#ifndef __CC_WEBSOCKET_H__
#define __CC_WEBSOCKET_H__

#include "CCPlatformMacros.h"
#include "CCStdC.h"
#include <list>
#include <string>
#include <vector>

struct libwebsocket;
struct libwebsocket_context;
struct libwebsocket_protocols;

NS_CC_BEGIN

namespace network {

class WsThreadHelper;
class WsMessage;

class WebSocket
{
public:
    /**
     * @js ctor
     */
    WebSocket();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~WebSocket();

    /**
     *  @brief Data structure for message
     */
    struct Data
    {
        Data():bytes(nullptr), len(0), issued(0), isBinary(false){}
        char* bytes;
        ssize_t len, issued;
        bool isBinary;
    };

    /**
     *  @brief Errors in websocket
     */
    enum class ErrorCode
    {
        TIME_OUT,
        CONNECTION_FAILURE,
        UNKNOWN,
    };

    /**
     *  Websocket state
     */
    enum class State
    {
        CONNECTING,
        OPEN,
        CLOSING,
        CLOSED,
    };

    /**
     *  @brief The delegate class to process websocket events.
     */
    class Delegate
    {
    public:
        virtual ~Delegate() {}
        virtual void onOpen(WebSocket* ws) = 0;
        virtual void onMessage(WebSocket* ws, const Data& data) = 0;
        virtual void onClose(WebSocket* ws) = 0;
        virtual void onError(WebSocket* ws, const ErrorCode& error) = 0;
    };


    /**
     *  @brief  The initialized method for websocket.
     *          It needs to be invoked right after websocket instance is allocated.
     *  @param  delegate The delegate which want to receive event from websocket.
     *  @param  url      The URL of websocket server.
     *  @return true: Success, false: Failure
     */
    bool init(const Delegate& delegate,
              const std::string& url,
              const std::vector<std::string>* protocols = nullptr);

    /**
     *  @brief Sends string data to websocket server.
     */
    void send(const std::string& message);

    /**
     *  @brief Sends binary data to websocket server.
     */
    void send(const unsigned char* binaryMsg, unsigned int len);

    /**
     *  @brief Closes the connection to server.
     */
    void close();

    /**
     *  @brief Gets current state of connection.
     */
    State getReadyState();

private:
    virtual void onSubThreadStarted();
    virtual int onSubThreadLoop();
    virtual void onSubThreadEnded();
    virtual void onUIThreadReceiveMessage(WsMessage* msg);


    friend class WebSocketCallbackWrapper;
    int onSocketCallback(struct libwebsocket_context *ctx,
                         struct libwebsocket *wsi,
                         int reason,
                         void *user, void *in, ssize_t len);

private:
    State        _readyState;
    std::string  _host;
    unsigned int _port;
    std::string  _path;

    ssize_t _pendingFrameDataLen;
    ssize_t _currentDataLen;
    char *_currentData;

    friend class WsThreadHelper;
    WsThreadHelper* _wsHelper;

    struct libwebsocket*         _wsInstance;
    struct libwebsocket_context* _wsContext;
    Delegate* _delegate;
    int _SSLConnection;
    struct libwebsocket_protocols* _wsProtocols;
};

}

NS_CC_END

#endif /* defined(__CC_JSB_WEBSOCKET_H__) */
