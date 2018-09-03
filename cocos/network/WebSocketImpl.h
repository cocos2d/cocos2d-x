/****************************************************************************
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
****************************************************************************/


#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include <list>
#include <mutex>
#include <functional>
#include <libwebsockets.h>

#include "WebSocket.h"
#include "Uri.h"

namespace cocos2d
{
    class EventListenerCustom;

    namespace network
    {
        class NetDataPack;
        class Helper;
        
        class WebSocketImpl : public std::enable_shared_from_this<WebSocketImpl>
        {
        public:
            typedef std::shared_ptr<WebSocketImpl> Ptr;
        private:
            static int _protocolCounter;
            static int64_t _wsIdCounter;

            static std::mutex _cachedSocketsMtx;
            static std::unordered_map<int64_t, Ptr > _cachedSockets;
            static void closeAll();
        public:
            WebSocketImpl(WebSocket *);
            virtual ~WebSocketImpl();

        private:

            bool init(const WebSocket::Delegate& delegate, const std::string &uri, const std::vector<std::string> *protocols = nullptr, const std::string &caFile = "");
            void closeAsyncSig();
            void closeSyncSig();
            void closeSyncSig(int timeoutMS);
            void sendSig(const char *data, size_t len);
            void sendSig(const std::string &msg);

            int onLWSCallback(struct lws *wsi, enum lws_callback_reasons reason, void*, void*, ssize_t);

            std::string searchCaPath(const std::string &caFile, bool useSSL);

            void doConnect();
            void doDisconnect();    //callbacks
            void doWrite(NetDataPack &pack);

            int netOnError(WebSocket::ErrorCode code);
            int netOnConnected();
            int netOnClosed();
            int netOnReadable(void *, size_t len);
            int netOnWritable();

            WebSocket::Delegate* _delegate = nullptr;
            WebSocket *_ws = nullptr;
            WebSocket::State _state = WebSocket::State::UNINITIALIZED;
            std::shared_ptr<Helper> _helper;

            std::string _url;
            Uri _uri;
            std::string _caFile;
            std::string _caFullPath;
            std::vector<std::string> _protocols;
            std::string _joinedProtocols;
            std::vector<uint8_t> _receiveBuffer;
            //libwebsocket fields
            lws *_wsi = nullptr;
            lws_vhost *_lwsHost = nullptr;
            lws_protocols *_lwsProtocols = nullptr;
            int64_t _wsId = 0;
            std::list<std::shared_ptr<NetDataPack>> _sendBuffer;

            int32_t _callbackInvokeFlags = 0;

            EventListenerCustom* _resetDirectorListener = nullptr;

            friend class Helper;
            friend class WebSocket;
            friend int websocket_callback(lws *wsi, enum lws_callback_reasons reason, void *user, void *in, ssize_t len);
            friend WebSocketImpl::Ptr findWs(int64_t wsId);
        };
    }
}
