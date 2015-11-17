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
 * @addtogroup network
 * @{
 */

NS_CC_BEGIN

namespace network {

class WsThreadHelper;
class WsMessage;

/**
 * WebSocket is wrapper of the libwebsockets-protocol, let the develop could call the websocket easily.
 */
class CC_DLL WebSocket
{
public:
    /**
     * Construtor of WebSocket.
     *
     * @js ctor
     */
    WebSocket();
    /**
     * Destructor of WebSocket.
     *
     * @js NA
     * @lua NA
     */
    virtual ~WebSocket();

    /**
     * Data structure for message
     */
    struct Data
    {
        Data():bytes(nullptr), len(0), issued(0), isBinary(false){}
        char* bytes;
        ssize_t len, issued;
        bool isBinary;
    };

    /**
     * ErrorCode enum used to represent the error in the websocket.
     */
    enum class ErrorCode
    {
        TIME_OUT,           /** &lt; value 0 */
        CONNECTION_FAILURE, /** &lt; value 1 */
        UNKNOWN,            /** &lt; value 2 */
    };

    /**
     *  State enum used to represent the Websocket state.
     */
    enum class State
    {
        CONNECTING,  /** &lt; value 0 */
        OPEN,        /** &lt; value 1 */
        CLOSING,     /** &lt; value 2 */
        CLOSED,      /** &lt; value 3 */
    };

    /**
     * The delegate class is used to process websocket events.
     *
     * The most member function are pure virtual functions,they should be implemented the in subclass.
     * @lua NA
     */
    class Delegate
    {
    public:
        /** Destructor of Delegate. */
        virtual ~Delegate() {}
        /**
         * This function to be called after the client connection complete a handshake with the remote server.
         * This means that the WebSocket connection is ready to send and receive data.
         * 
         * @param ws The WebSocket object connected
         */
        virtual void onOpen(WebSocket* ws) = 0;
        /**
         * This function to be called when data has appeared from the server for the client connection.
         *
         * @param ws The WebSocket object connected.
         * @param data Data object for message.
         */
        virtual void onMessage(WebSocket* ws, const Data& data) = 0;
        /**
         * When the WebSocket object connected wants to close or the protocol won't get used at all and current _readyState is State::CLOSING,this function is to be called.
         *
         * @param ws The WebSocket object connected.
         */
        virtual void onClose(WebSocket* ws) = 0;
        /**
         * This function is to be called in the following cases:
         * 1. client connection is failed.
         * 2. the request client connection has been unable to complete a handshake with the remote server.
         * 3. the protocol won't get used at all after this callback and current _readyState is State::CONNECTING.
         * 4. when a socket descriptor needs to be removed from an external polling array. in is again the struct libwebsocket_pollargs containing the fd member to be removed. If you are using the internal polling loop, you can just ignore it and current _readyState is State::CONNECTING.
         *
         * @param ws The WebSocket object connected.
         * @param error WebSocket::ErrorCode enum,would be ErrorCode::TIME_OUT or ErrorCode::CONNECTION_FAILURE.
         */
        virtual void onError(WebSocket* ws, const ErrorCode& error) = 0;
    };


    /**
     *  @brief  The initialized method for websocket.
     *          It needs to be invoked right after websocket instance is allocated.
     *  @param  delegate The delegate which want to receive event from websocket.
     *  @param  url      The URL of websocket server.
     *  @return true: Success, false: Failure.
     *  @lua NA
     */
    bool init(const Delegate& delegate,
              const std::string& url,
              const std::vector<std::string>* protocols = nullptr);

    /**
     *  @brief Sends string data to websocket server.
     *  
     *  @param message string data.
     *  @lua sendstring
     */
    void send(const std::string& message);

    /**
     *  @brief Sends binary data to websocket server.
     *  
     *  @param binaryMsg binary string data.
     *  @param len the size of binary string data.
     *  @lua sendstring
     */
    void send(const unsigned char* binaryMsg, unsigned int len);

    /**
     *  @brief Closes the connection to server.
     */
    void close();

    /**
     *  @brief Gets current state of connection.
     *  @return State the state value could be State::CONNECTING, State::OPEN, State::CLOSING or State::CLOSED
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
