/****************************************************************************
 Copyright (c) 2019 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

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

 ****************************************************************************/

#pragma once

#include <string>
#include <vector>
#include <mutex>
#include <memory>  // for std::shared_ptr
#include <atomic>
#include <condition_variable>

#include "network/WebSocket.h"
#include "platform/CCPlatformMacros.h"
#include "platform/CCStdC.h"
#include "platform/android/jni/JniHelper.h"


NS_CC_BEGIN

namespace network {

void _preloadJavaWebSocketClass();

void _WebSocketAndroidNativeTriggerEvent(JNIEnv *env, jclass *klass, jlong cid, jstring eventName, jstring data, jboolean isBinary);

/**
 * WebSocket is wrapper of the libwebsockets-protocol, let the develop could call the websocket easily.
 * Please note that all public methods of WebSocket have to be invoked on Cocos Thread.
 */
class CC_DLL WebSocketImpl
{
public:

    /**
     * Constructor of WebSocket.
     *
     * @js ctor
     */
    WebSocketImpl(WebSocket *ws);
    /**
     * Destructor of WebSocket.
     *
     * @js NA
     * @lua NA
     */
    virtual ~WebSocketImpl();


    bool init(const WebSocket::Delegate& delegate,
              const std::string& url,
              const std::vector<std::string>* protocols = nullptr,
              const std::string& caFilePath = "");


    void send(const std::string& message);


    void send(const unsigned char* binaryMsg, unsigned int len);


    void close();

    void closeAsync();


    inline WebSocket::State getReadyState() const { return _readyState; }

    inline const std::string& getUrl() const { return _url; }

    /**
     *  @brief Gets the protocol selected by websocket server.
     */
    inline const std::string& getProtocol() const { return _selectedProtocol; }

private:

    void triggerEvent(const std::string& eventName, const std::string &data, bool binary);

    int64_t     _connectionID = -1;
    WebSocket::State       _readyState = WebSocket::State::CONNECTING;
    WebSocket::Delegate*   _delegate  = nullptr;
    std::string _selectedProtocol;
    std::string _caFilePath;
    std::string _url;

    WebSocket  *_socket = nullptr;

    friend void cocos2d::network::_WebSocketAndroidNativeTriggerEvent(JNIEnv *env, jclass *klass, jlong cid, jstring eventName, jstring data, jboolean isBinary);
};

} // namespace network {

NS_CC_END

// end group
/// @}

