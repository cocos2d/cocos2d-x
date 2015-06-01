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

#include <string>
#include <vector>

#include "platform/CCPlatformMacros.h"
#include "platform/CCStdC.h"

struct libwebsocket;
struct libwebsocket_context;
struct libwebsocket_protocols;

/**
 * @addtogroup core
 * @{
 */

NS_CC_BEGIN

namespace network {

class WsThreadHelper;
class WsMessage;

/**
 * @ WebSocket 
 * @brief @~english WebSocket is wrapper of the libwebsockets-protocol, let the developer could call the websocket easily.
 * @~chinese WebSocket是libwebsockets-protocol一层封闭，可以让开发者方便的调用websocket的功能。
 */
class CC_DLL WebSocket
{
public:
    /**
     * @~english Construtor of WebSocket.
     * @~chinese 构造函数
     * @js ctor
     */
    WebSocket();
    /**
     * @~english Destructor of WebSocket.
     * @~chinese 析构函数
     * @js NA
     * @lua NA
     */
    virtual ~WebSocket();

    /**
     * @~english Data structure for message
     * @~chinese message的数据结构
     */
    struct Data
    {
        Data():bytes(nullptr), len(0), issued(0), isBinary(false){}
        char* bytes;
        ssize_t len, issued;
        bool isBinary;
    };

    /**
     * @~english ErrorCode enum used to represent the error in the Websocket.
     * @~chinese Websocket的错误码枚举
     */
    enum class ErrorCode
    {
        TIME_OUT,           /** &lt; value 0 */
        CONNECTION_FAILURE, /** &lt; value 1 */
        UNKNOWN,            /** &lt; value 2 */
    };

    /**
     *@~english State enum used to represent the Websocket state.
     *@~chinese Websocket的状态枚举
     */
    enum class State
    {
        CONNECTING,  /** &lt; value 0 */
        OPEN,        /** &lt; value 1 */
        CLOSING,     /** &lt; value 2 */
        CLOSED,      /** &lt; value 3 */
    };

    /**
     * @~english The delegate class is used to process websocket events.
     * The most member function are pure virtual functions,they should be implemented the in subclass.
     * @~chinese 用于处理websocket事件的代理类。多数成员函数为纯虚函数，它们需要在子类中实现。
     * @lua NA
     */
    class Delegate
    {
    public:
        /** Destructor of Delegate. */
        virtual ~Delegate() {}
        /**
         * @~english This function to be called after the client connection complete a handshake with the remote server.
         *This means that the WebSocket connection is ready to send and receive data.
         * @~chinese 这个函数在客户端完成和远程服务器完成握手后被调用，这意味着WebSocket已经准备好发送和接收数据了。
         * @param ws @~english The WebSocket object connected. @~chinese 连接上的WebSocket。
         */
        virtual void onOpen(WebSocket* ws) = 0;
        /**
         * @~english This function to be called when data has appeared from the server for the client connection.
         * @~chinese 当有数据从服务端传回时将调用这个函数
         * @param ws @~english The WebSocket object connected. @~chinese 连接上的WebSocket。
         * @param data @~english Data object for message. @~chinese 信息数据。
         */
        virtual void onMessage(WebSocket* ws, const Data& data) = 0;
        /**
         * @~english When the WebSocket object connected wants to close or the protocol won't get used at all and current _readyState is State::CLOSING,this function is to be called.
         * @~chinese 当已连接上的WebSocket对象想关闭或者不使用协议并且当前的_readyState是State::CLOSING时，这个函数将会触发。
         * @param ws @~english The WebSocket object connected. @~chinese 连接上的WebSocket。
         */
        virtual void onClose(WebSocket* ws) = 0;
        /**
         * @~english This function is to be called in the following cases:
         * 1. client connection is failed.
         * 2. the request client connection has been unable to complete a handshake with the remote server.
         * 3. the protocol won't get used at all after this callback and current _readyState is State::CONNECTING.
         * 4. when a socket descriptor needs to be removed from an external polling array. in is again the struct libwebsocket_pollargs containing the fd member to be removed. If you are using the internal polling loop, you can just ignore it and current _readyState is State::CONNECTING.
         * @~chinese 这个函数在以下几种情况下会被触发:
         * 1. 连接失败
         * 2. 客户端和服务端握手失败
         * 3. 根本不使用协议并且当前的_readyState为State::CONNECTING
         * 4. 当一个socket描述符需要从外部轮询数据数队列中移除时，包含fd成员的libwebsocket_pollargs结构也要被移除。如果你是使用内部轮询循环时，你可忽略它并且当前的_readyState为State::CONNECTING.
         * @param ws @~english The WebSocket object connected. @~chinese 连接上的WebSocket。
         * @param error @~english WebSocket::ErrorCode enum,would be ErrorCode::TIME_OUT or ErrorCode::CONNECTION_FAILURE. @~chinese WebSocket的错误码枚举，可以为ErrorCode::TIME_OUT或ErrorCode::CONNECTION_FAILURE。
         */
        virtual void onError(WebSocket* ws, const ErrorCode& error) = 0;
    };


    /**
     *  @~english The initialized method for websocket.
     *            It needs to be invoked right after websocket instance is allocated.
     *  @~chinese WebSocket的初始化方法，它在WebSocket实例被分配后被触发。
     *  @param  delegate @~english The delegate which want to receive event from websocket. @~chinese 接收来自websocket
     *  @param  url      @~english The URL of websocket server. @~chinese websocket服务端URL地址
     *  @return @~english true: Success, false: Failure. @~chinese true:成功，false:失败
     *  @lua NA
     */
    bool init(const Delegate& delegate,
              const std::string& url,
              const std::vector<std::string>* protocols = nullptr);

    /**
     *  @~english Sends string data to websocket server. @~chinese 向websocket服务端发送字符串数据
     *  
     *  @param @~english message string data. @~chinese 字符串数据
     *  @lua sendstring
     */
    void send(const std::string& message);

    /**
     *  @~english Sends binary data to websocket server. @~chinese 向websocket服务端发送二进制数据
     *  
     *  @param @~english binaryMsg binary string data. @~chinese 二进制字符串数据
     *  @param @~english len the size of binary string data. @~chinese 二进制字符串数据的长度
     *  @lua sendstring
     */
    void send(const unsigned char* binaryMsg, unsigned int len);

    /**
     *  @~english Closes the connection to server. @~chinese 关闭到服务端的连接。
     */
    void close();

    /**
     *  @~english Gets current state of connection. @~chinese 获取当前连接的状态。
     *  @return @~english State the state value coule be State::CONNECTING, State::OPEN, State::CLOSING or State::CLOSED. @~chinese 返回State类型的值，可以为State::CONNECTING, State::OPEN, State::CLOSING 或者 State::CLOSED
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

// end group
/// @}

#endif /* defined(__CC_JSB_WEBSOCKET_H__) */
