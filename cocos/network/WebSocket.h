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

#include "base/CCPlatformMacros.h"
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
     *  @brief message的数据结构
     */
    struct Data
    {
        Data():bytes(nullptr), len(0), issued(0), isBinary(false){}
        char* bytes;
        ssize_t len, issued;
        bool isBinary;
    };

    /**
     *  @brief websocket中的errors
     */
    enum class ErrorCode
    {
        TIME_OUT,
        CONNECTION_FAILURE,
        UNKNOWN,
    };

    /**
     *  Websocket 状态
     */
    enum class State
    {
        CONNECTING,
        OPEN,
        CLOSING,
        CLOSED,
    };

    /**
     *  @brief 处理websocket事件的delegate类
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
     *  @brief  websocket的初始化方法。
     *          在websocket实例被分配之后需要被正确引用
     *  @param  delegate 要从websocket接收事件的delegate
     *  @param  url      websocket服务端的url
     *  @return true: 成功, false: 失败
     */
    bool init(const Delegate& delegate,
              const std::string& url,
              const std::vector<std::string>* protocols = nullptr);

    /**
     *  @brief 向websocket服务端发送string数据
     */
    void send(const std::string& message);

    /**
     *  @brief 向websocket服务端发送二进制数据。
     */
    void send(const unsigned char* binaryMsg, unsigned int len);

    /**
     *  @brief 关闭到服务端的连接。
     */
    void close();

    /**
     *  @brief 获取当前连接的状态。
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
