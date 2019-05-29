/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#pragma once

#include <string>
#include <vector>
#include <mutex>
#include <memory>  // for std::shared_ptr
#include <atomic>
#include <condition_variable>

#include "platform/CCPlatformMacros.h"
#include "platform/CCStdC.h"
#include "network/WebSocket.h"


struct lws;
struct lws_protocols;
struct lws_vhost;
/**
 * @addtogroup network
 * @{
 */

NS_CC_BEGIN

class EventListenerCustom;

namespace network {

class WebSocket;
class WsThreadHelper;

/**
 * WebSocket is wrapper of the libwebsockets-protocol, let the develop could call the websocket easily.
 * Please note that all public methods of WebSocket have to be invoked on Cocos Thread.
 */
class CC_DLL WebSocketImpl
{
public:

    WebSocketImpl(WebSocket *);

    virtual ~WebSocketImpl();

    bool init(const WebSocket::Delegate& delegate,
              const std::string& url,
              const std::vector<std::string>* protocols = nullptr,
              const std::string& caFilePath = "");

    void send(const std::string& message);

    void send(const unsigned char* binaryMsg, unsigned int len);

    void close();

    void closeAsync();

    WebSocket::State getReadyState();

    inline const std::string& getUrl() const { return _url; }

    inline const std::string& getProtocol() const { return _selectedProtocol; }


private:

    // The following callback functions are invoked in websocket thread
    void onClientOpenConnectionRequest();
    int onSocketCallback(struct lws *wsi, int reason, void *in, ssize_t len);

    int onClientWritable();
    int onClientReceivedData(void* in, ssize_t len);
    int onConnectionOpened();
    int onConnectionError(void* in, ssize_t len);
    int onConnectionClosed();

    struct lws_vhost* createVhost(struct lws_protocols* protocols, int& sslConnection);

private:

    std::vector<char> _receivedData;

    struct lws* _wsInstance;
    struct lws_protocols* _lwsProtocols;
    std::string _clientSupportedProtocols;

    std::shared_ptr<std::atomic<bool>> _isDestroyed;

    std::mutex _closeMutex;
    std::condition_variable _closeCondition;
    std::vector<char*> _protocolNames;

    enum class CloseState
    {
        NONE,
        SYNC_CLOSING,
        SYNC_CLOSED,
        ASYNC_CLOSING
    };
    
    CloseState _closeState;
    std::mutex  _readyStateMutex;
    EventListenerCustom* _resetDirectorListener;

    friend class WsThreadHelper;
    friend class WebSocketCallbackWrapper;

    WebSocket *_socket = nullptr;


    WebSocket::State       _readyState =  WebSocket::State ::CONNECTING;
    WebSocket::Delegate*   _delegate  = nullptr;
    std::string _selectedProtocol;
    std::string _caFilePath;

    std::string _url;

};

} // namespace network {

NS_CC_END

// end group
/// @}

