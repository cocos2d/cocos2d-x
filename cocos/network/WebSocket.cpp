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

#include "network/WebSocket.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "WebSocket-android.h"
#else
#include "WebSocket-libwebsocket.h"
#endif

namespace cocos2d { namespace network {

    WebSocket::WebSocket() {
        _impl = std::make_shared<WebSocketImpl>(this);
    }

    WebSocket::~WebSocket() {
        if(_impl) {
            _impl->closeAsync();
        }
    }

    bool WebSocket::init(const WebSocket::Delegate& delegate,
                         const std::string& url,
                         const std::vector<std::string>* protocols,
                         const std::string& caFilePath) {
        return _impl->init(delegate, url, protocols, caFilePath);
    }

    void WebSocket::send(const std::string &message) {
        _impl->send(message);
    }

    void WebSocket::send(const unsigned char *binaryData, unsigned int len)
    {
        _impl->send(binaryData, len);
    }

    void WebSocket::close()
    {
        _impl->close();
    }

    void WebSocket::closeAsync()
    {
        _impl->closeAsync();
    }

    WebSocket::State WebSocket::getReadyState()
    {
        return _impl->getReadyState();
    }

    const std::string& WebSocket::getUrl() const
    {
        return _impl->getUrl();
    }

    const std::string & WebSocket::getProtocol() const
    {
        return _impl->getProtocol();
    }
}}


