/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Valentin Milea
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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
****************************************************************************/


#include "WebSocketImpl.h"

#include "Uri.h"

#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventListener.h"
#include "base/CCEventListenerCustom.h"
#include "platform/CCFileUtils.h"

#include "loop/Looper.h"

#include <iostream>
#include <memory>
#include <cassert>
#include <algorithm>
#include <libwebsockets.h>

using namespace cocos2d;
using namespace cocos2d::loop;

#define WS_RX_BUFFER_SIZE ((1 << 16) - 1)
#define WS_REVERSED_RECEIVE_BUFFER_SIZE  (1 << 12)

/**
* set _callbackInvokeFlags with CallbackInvoke flag, return if it's already set.
*/
#define CHECK_INVOKE_FLAG(flg)  do { \
    if(_callbackInvokeFlags & flg)  return 0; \
    _callbackInvokeFlags |= flg; } while(0)

#define LOCK_MTX(mtx) std::lock_guard<std::mutex> __guard__(mtx)

//////////////////////////tool functions ////////////////////////

//android only
static std::string fileBaseName(const std::string &path)
{
    auto lastSlashIdx = path.find_last_of("\\/");
    if (lastSlashIdx == std::string::npos) return path;
    return path.substr(lastSlashIdx + 1);
}
/**
* test if path starts with "https" or "wss"
*/
static bool isSecureURL(const std::string &path)
{
    const char *p = path.c_str();
    if (path.length() < 5) return false;

    switch (p[0])
    {
    case 'h':
    case 'H':
    case 'w':
    case 'W':
    {
        if (strncmp(p, "https:", 6) == 0 ||
            strncmp(p, "wss:", 4) == 0 ||
            strncmp(p, "HTTPS:", 6) == 0 ||
            strncmp(p, "WSS:", 4) == 0
            ) {
            return true;
        }
        break;
    }
    default:
        break;
    }
    return false;
}

namespace cocos2d
{
    namespace network
    {
        /**
        * used to present whether `WebSocketImpl#_delegate` callback ever be called.
        */
        enum CallbackInvoke {
            CallbackInvoke_CONNECTED = 1 << 0,
            CallbackInvoke_CLOSED = 1 << 1,
            CallbackInvoke_ERROR = 1 << 2
        };


        ////////////////////net thread - begin ///////////////////

        //////////////basic data type - begin /////////////
        enum class NetCmdType
        {
            OPEN, CLOSE, WRITE, RECIEVE
        };

        class NetDataPack {
        public:
            NetDataPack() {}
            NetDataPack(const char *f, size_t l, bool isBinary) {
                _buffer = (uint8_t*)calloc(1, l + LWS_PRE);
                memcpy(_buffer + LWS_PRE, f, l);
                _size = l;
                _remain = l;
                _payload = _buffer + LWS_PRE;
                _isBinary = isBinary;
            }

            NetDataPack(const NetDataPack &) = delete; //non-copyable
            NetDataPack(NetDataPack&&) = delete;       //non-movable

            ~NetDataPack() {
                if (_buffer) {
                    free(_buffer);
                    _buffer = nullptr;
                }
                _size = 0;
            }


            size_t remain() { return _remain; }
            uint8_t *payload() { return _payload; }

            void consume(size_t d)
            {
                CCASSERT(d <= _remain, "data not enought!");
                _payload += d;
                _remain -= d;
                _consumed += d;
            }

            size_t consumed() { return _consumed; }
            bool isBinary() { return _isBinary; }
        private:
            uint8_t *_buffer = nullptr;
            uint8_t *_payload = nullptr;
            size_t _size = 0;
            size_t _remain = 0;
            bool _isBinary = true;
            size_t _consumed = 0;
        };

        /**
        * Message/Command sent to network thread. 
        */
        class NetCmd {
        public:
            static NetCmd Open(WebSocketImpl::Ptr ws);
            static NetCmd Close(WebSocketImpl::Ptr ws);
            static NetCmd Write(WebSocketImpl::Ptr ws, const char *data, size_t len, bool isBinary);

            NetCmd() {}
            NetCmd(WebSocketImpl::Ptr ws, NetCmdType cmd, std::shared_ptr<NetDataPack> data) :ws(ws), cmd(cmd), data(data) {}
            NetCmd(const NetCmd &o) :ws(o.ws), cmd(o.cmd), data(o.data) {}
        public:
            WebSocketImpl::Ptr ws{ nullptr };      //sender socket
            NetCmdType cmd;                     //command type
            std::shared_ptr<NetDataPack> data;  //write data
        };

        NetCmd NetCmd::Open(WebSocketImpl::Ptr ws) { return NetCmd(ws, NetCmdType::OPEN, nullptr); }
        NetCmd NetCmd::Close(WebSocketImpl::Ptr ws) { return NetCmd(ws, NetCmdType::CLOSE, nullptr); }
        NetCmd NetCmd::Write(WebSocketImpl::Ptr ws, const char *data, size_t len, bool isBinary)
        {
            auto pack = std::make_shared<NetDataPack>(data, len, isBinary);
            return NetCmd(ws, NetCmdType::WRITE, pack);
        }

        //////////////basic data type - end /////////////

        static int websocket_callback(lws *wsi, enum lws_callback_reasons reason, void *user, void *in, ssize_t len)
        {
            if (wsi == nullptr) return 0;
            int ret = 0;
            WebSocketImpl *ws = (WebSocketImpl*)lws_wsi_user(wsi);
            if (ws) {
                ret = ws->lwsCallback(wsi, reason, user, in, len);
            }
            return ret;
        }

        /////////////loop thread - begin /////////////////

        class HelperLoop;

        class Helper
        {
        public:

            Helper();
            virtual ~Helper();

            static std::shared_ptr<Helper> fetch();
            static void drop();

            void init();

            /**
            * clear helper, invoked in `Loop#after` callback.
            */
            void clear();

            /**
            * emit message to network thread
            */
            void send(const std::string &event, const NetCmd &cmd);

            /**
            * dispatch lambda to cocos thread
            */
            void runInUI(const std::function<void()> &fn);

            void handleCmdConnect(NetCmd &cmd);
            void handleCmdDisconnect(NetCmd &cmd);
            void handleCmdWrite(NetCmd &cmd);

            uv_loop_t * getUVLoop() { return _looper->getUVLoop(); }
            void reInitLibUV();

        private:
            //libwebsocket helper
            void initProtocols();
            lws_context_creation_info initCtxCreateInfo(const struct lws_protocols *protocols, bool useSSL);

        private:
            static std::shared_ptr<Helper> __sCacheHelper;
            static std::mutex __sCacheHelperMutex;

            std::shared_ptr<Looper<NetCmd> > _looper = nullptr;
            HelperLoop *_loop = nullptr;

        public:
            //libwebsocket fields
            lws_protocols *_lwsDefaultProtocols = nullptr;
            lws_context *_lwsContext = nullptr;

            friend class HelperLoop;
        };

        class HelperLoop : public Loop {
        public:
            HelperLoop(Helper *helper) :_helper(helper) {}
            void before() override;
            void after() override;
            void update(int dtms) override;
        private:
            Helper *_helper = nullptr;
        };

        //static fields
        std::shared_ptr<Helper> Helper::__sCacheHelper;
        std::mutex Helper::__sCacheHelperMutex;

        Helper::Helper()
        {}

        Helper::~Helper()
        {
            if (_loop)
            {
                delete _loop;
                _loop = nullptr;
            }
        }

        std::shared_ptr<Helper> Helper::fetch()
        {
            std::lock_guard<std::mutex> guard(__sCacheHelperMutex);
            if (!__sCacheHelper)
            {
                __sCacheHelper = std::make_shared<Helper>();
                __sCacheHelper->init();
            }
            return __sCacheHelper;
        }

        void Helper::drop()
        {
            // drop() 
            //  ~> _looper#stop() 
            //  ~> Helper::after()
            //  ~> shared_ptr<Helper>::reset()
            //  ~> Helper::~Helper()
            std::lock_guard<std::mutex> guard(__sCacheHelperMutex);
            if (__sCacheHelper)
                __sCacheHelper->_looper->asyncStop();

        }

        void Helper::init()
        {
            _loop = new HelperLoop(this);

            _looper = std::make_shared<Looper<NetCmd> >(ThreadCategory::NET_THREAD, _loop, 5000);

            initProtocols();
            lws_context_creation_info  info = initCtxCreateInfo(_lwsDefaultProtocols, true);
            _lwsContext = lws_create_context(&info);

            _looper->on("open", [this](NetCmd &ev) {this->handleCmdConnect(ev); });
            _looper->on("send", [this](NetCmd &ev) {this->handleCmdWrite(ev); });
            _looper->on("close", [this](NetCmd& ev) {this->handleCmdDisconnect(ev); });

            _looper->run();
        }

        void Helper::clear()
        {
            if (_lwsContext)
            {
                lws_libuv_stop(_lwsContext);
                lws_context_destroy(_lwsContext);
                _lwsContext = nullptr;
            }
            if (_lwsDefaultProtocols)
            {
                free(_lwsDefaultProtocols);
                _lwsDefaultProtocols = nullptr;
            }
            if (_looper) {
                _looper->asyncStop(); 
            }
            //deref helper, ~helper
            std::lock_guard<std::mutex> guard(__sCacheHelperMutex);
            if (__sCacheHelper) __sCacheHelper.reset();
        }

        void Helper::initProtocols()
        {
            if (!_lwsDefaultProtocols) free(_lwsDefaultProtocols);
            _lwsDefaultProtocols = (lws_protocols *)calloc(2, sizeof(struct lws_protocols));
            lws_protocols *p = &_lwsDefaultProtocols[0];
            p->name = "";
            p->rx_buffer_size = WS_RX_BUFFER_SIZE;
            p->callback = (lws_callback_function*)&websocket_callback;
            p->id = (1ULL << 32) - 1ULL;
        }

        lws_context_creation_info Helper::initCtxCreateInfo(const struct lws_protocols *protocols, bool useSSL)
        {
            lws_context_creation_info info;
            memset(&info, 0, sizeof(info));

            info.port = CONTEXT_PORT_NO_LISTEN;
            info.protocols = protocols;
            info.gid = -1;
            info.uid = -1;

            info.options = LWS_SERVER_OPTION_EXPLICIT_VHOSTS |
                LWS_SERVER_OPTION_LIBUV |
                LWS_SERVER_OPTION_PEER_CERT_NOT_REQUIRED;

            if (useSSL)
            {
                info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
            }
            info.user = nullptr;
            return info;
        }

        void Helper::send(const std::string &event, const NetCmd &cmd)
        {
            NetCmd _copy(cmd);
            _looper->emit(event, _copy);
        }


        void Helper::runInUI(const std::function<void()> &fn)
        {
            Director::getInstance()->getScheduler()->performFunctionInCocosThread(fn);
        }

        void Helper::handleCmdConnect(NetCmd &cmd)
        {
            cmd.ws->doConnect();
        }

        void Helper::handleCmdDisconnect(NetCmd &cmd)
        {
            cmd.ws->doDisconnect();
            //lws_callback_on_writable(cmd.ws->_wsi);
        }

        void Helper::handleCmdWrite(NetCmd &cmd)
        {
            auto pack = cmd.data;
            cmd.ws->_sendBuffer.push_back(pack);
            lws_callback_on_writable(cmd.ws->_wsi);
        }

        void Helper::reInitLibUV()
        {
            lws_uv_initloop(_lwsContext, getUVLoop(), 0);
        }

        void HelperLoop::before()
        {
            CCLOG("[WSHelper] thread start ... ");
            _helper->reInitLibUV();
        }

        void HelperLoop::update(int dtms)
        {
            //CCLOG("[HelperLoop] thread tick ... ");
        }

        void HelperLoop::after()
        {
            CCLOG("[WSHelper] thread quit!!! ... ");
            _helper->clear();
        }

        /////////////loop thread - end //////////////////


        ////////////////////net thread - end   ///////////////////

        int WebSocketImpl::_protocolCounter = 1;
        std::mutex WebSocketImpl::_cachedSocketsMtx;
        std::atomic_int64_t WebSocketImpl::_wsIdCounter{1};
        std::unordered_map<int64_t, WebSocketImpl::Ptr > WebSocketImpl::_cachedSockets;

        ///////friend function 
        static WebSocketImpl::Ptr findWs(int64_t wsId)
        {
            LOCK_MTX(WebSocketImpl::_cachedSocketsMtx);
            auto it = WebSocketImpl::_cachedSockets.find(wsId);
            return it == WebSocketImpl::_cachedSockets.end() ? nullptr : it->second;
        }

        void WebSocketImpl::closeAll()
        {
            LOCK_MTX(WebSocketImpl::_cachedSocketsMtx);
            auto tmp(std::move(_cachedSockets));
            for (auto ws : tmp)
            {
                ws.second->sigCloseSync();
            }
        }

        WebSocketImpl::WebSocketImpl(WebSocket *t)
        {
            _ws = t;
            _wsId = _wsIdCounter.fetch_add(1);
            auto wsId = _wsId;
            _resetDirectorListener = Director::getInstance()
                ->getEventDispatcher()
                ->addCustomEventListener(Director::EVENT_RESET, [wsId](EventCustom*) {
                auto ws = findWs(wsId);
                if (ws) ws->sigCloseSync();
            });
        }

        WebSocketImpl::~WebSocketImpl()
        {
            {
                LOCK_MTX(_cachedSocketsMtx);
                _cachedSockets.erase(_wsId); //redundancy
            }

            if (_lwsProtocols)
            {
                free(_lwsProtocols);
                _lwsProtocols = nullptr;
            }

            if (_lwsHost)
            {
                lws_vhost_destroy(_lwsHost);
                _lwsHost = nullptr;
            }

            if (_wsi)
            {
                _wsi = nullptr;
            }
            Director::getInstance()->getEventDispatcher()->removeEventListener(_resetDirectorListener);
        }

        bool WebSocketImpl::init(const WebSocket::Delegate &delegate, const std::string &url, const std::vector<std::string> *protocols, const std::string & caFile)
        {

            CCASSERT(url.length() > 0, "url should not be empty!");
            if (isSecureURL(url) && caFile.length() == 0)
            {
                CCLOGERROR("WebSocket url: `%s` uses SSL, which expects a caFile `%s`", url.c_str(), caFile.c_str());
                return false;
            }

            _helper = Helper::fetch();

            {
                LOCK_MTX(_cachedSocketsMtx);
                _cachedSockets.emplace(_wsId, shared_from_this());
            }

            _url = url;
            _uri = Uri::parse(url);
            _delegate = const_cast<WebSocket::Delegate*>(&delegate);
            if (protocols)
                _protocols = *protocols;
            _caFile = caFile;
            _callbackInvokeFlags = 0;

            size_t size = _protocols.size();
            if (size > 0)
            {
                _lwsProtocols = (struct lws_protocols*)calloc(size + 1, sizeof(struct lws_protocols));
                for (size_t i = 0; i < size; i++)
                {
                    struct lws_protocols *p = &_lwsProtocols[i];
                    p->name = _protocols[i].data();
                    p->id = (++_protocolCounter);
                    p->rx_buffer_size = WS_RX_BUFFER_SIZE;
                    p->per_session_data_size = 0;
                    p->user = this;
                    p->callback = (lws_callback_function*)&websocket_callback;
                    _joinedProtocols += _protocols[i];
                    if (i < size - 1) _joinedProtocols += ",";
                }
            }

            _state = WebSocket::State::CONNECTING;
            _helper->send("open", NetCmd::Open(this->shared_from_this()));

            return true;
        }

        void WebSocketImpl::sigCloseAsync()
        {
            if (_state == WebSocket::State::CLOSED ||
                _state == WebSocket::State::CLOSING ||
                _state == WebSocket::State::UNINITIALIZED
                )
                return;
            _helper->send("close", NetCmd::Close(this->shared_from_this()));
        }

        void WebSocketImpl::sigCloseSync(int timeoutMS)
        {
            if (_state == WebSocket::State::CLOSED ||
                _state == WebSocket::State::CLOSING ||
                _state == WebSocket::State::UNINITIALIZED
                )
                return;
            _state = WebSocket::State::CLOSING;
            _helper->send("close", NetCmd::Close(this->shared_from_this()));
            
            if (timeoutMS == 0)
            {
                //sleep forever, unless closed
                while (_state != WebSocket::State::CLOSED)
                {
                    std::this_thread::yield();
                }
            }
            else
            {
                int dtms = 3;
                while (_state != WebSocket::State::CLOSED && timeoutMS > 0)
                {
                    std::this_thread::sleep_for(milliseconds(dtms));
                    timeoutMS -= dtms;
                }
            }

            if (_state != WebSocket::State::CLOSED)
            {
                CCLOGERROR("WebSocket close error, not closed!");
            }
        }

        void WebSocketImpl::sigSend(const char *data, size_t len)
        {
            _helper->send("send", NetCmd::Write(this->shared_from_this(), data, len, true));
        }

        void WebSocketImpl::sigSend(const std::string &msg)
        {
            NetCmd cmd = NetCmd::Write(this->shared_from_this(), msg.data(), msg.length(), false);
            _helper->send("send", cmd);
        }

        int WebSocketImpl::lwsCallback(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, ssize_t len)
        {
            int ret = 0;
            switch (reason)
            {
            case LWS_CALLBACK_CLIENT_ESTABLISHED:
                ret = netOnConnected();
                break;
            case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
                ret = netOnError(WebSocket::ErrorCode::CONNECTION_FAILURE);
                break;
            case LWS_CALLBACK_CLIENT_RECEIVE:
                ret = netOnReadable(in, (size_t)len);
                break;
            case LWS_CALLBACK_CLIENT_WRITEABLE:
                ret = netOnWritable();
                break;
            case LWS_CALLBACK_WSI_DESTROY:
                ret = netOnClosed();
                break;
            case LWS_CALLBACK_CHANGE_MODE_POLL_FD:
            case LWS_CALLBACK_LOCK_POLL:
            case LWS_CALLBACK_UNLOCK_POLL:
                //reduce log
                break;
            default:
                lwsl_warn("lws callback reason %d is not handled!\n", reason);
                break;
            }
            return ret;
        }

        std::string WebSocketImpl::searchCaPath(const std::string &caFile, bool useSSL)
        {
            //CA certificate file is *not* required if ssl is not enabled
            if (!useSSL) return "";

            auto fileUtils = FileUtils::getInstance();
            bool isCAFileExists = fileUtils->isFileExist(caFile);
            if (isCAFileExists)
            {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                auto writablePath = fileUtils->getWritablePath();
                auto baseName = fileBaseName(caFile);
                auto fullCaPath = writablePath + baseName;

                if (fileUtils->isFileExist(fullCaPath))
                {
                    return fullCaPath;
                }
                else
                {
                    auto srcCaPath = fileUtils->fullPathForFilename(_caFile);
                    if (srcCaPath[0] != '/')
                    {
                        auto caData = fileUtils->getDataFromFile(srcCaPath);
                        if (!caData.isNull())
                        {
                            auto copyRet = fileUtils->writeDataToFile(caData, fullCaPath);
                            CCASSERT(copyRet, "Fail to copy CA");
                        }
                        else
                        {
                            CCASSERT(false, "CA file is empty!");
                        }
                    }
                    return fullCaPath; //copy done
                }
#else
                return fileUtils->fullPathForFilename(caFile);
#endif
            }
            else
            {
                return "";
            }
        }

        void WebSocketImpl::doConnect()
        {

            CCASSERT(_helper->getUVLoop(), "uv_loop_t* is required!");

            struct lws_extension exts[] = {
                {
                    "permessage-deflate",
                    lws_extension_callback_pm_deflate,
                    "permessage-deflate; client_max_window_bits"
                },
        {
            "deflate-frame",
            lws_extension_callback_pm_deflate,
            "deflate-frame"
        },
            { nullptr,nullptr,nullptr }
            };

            auto useSSL = _uri.isSecure();

            if (useSSL) {
                //caFile must be provided once ssl is enabled.
                //it can be downloaded from site https://curl.haxx.se/docs/caextract.html
                CCASSERT(_caFile.length() > 0, "set `caFile` when using wss!");
            }

            _caFullPath = searchCaPath(_caFile, useSSL);

            lws_context_creation_info info;
            memset(&info, 0, sizeof(info));
            info.port = CONTEXT_PORT_NO_LISTEN;
            info.protocols = _lwsProtocols == nullptr ? _helper->_lwsDefaultProtocols : _lwsProtocols;
            info.gid = -1;
            info.uid = -1;
            info.user = this;
            info.ssl_ca_filepath = _caFullPath.empty() ? nullptr : _caFullPath.c_str();

            info.options = LWS_SERVER_OPTION_EXPLICIT_VHOSTS |
                LWS_SERVER_OPTION_LIBUV;
            //ssl flags
            int sslFlags = 0;

            if (useSSL)
            {
                info.options = info.options | LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT |
                    LWS_SERVER_OPTION_PEER_CERT_NOT_REQUIRED;
                sslFlags = sslFlags | LCCSCF_USE_SSL | LCCSCF_ALLOW_SELFSIGNED |
                    LCCSCF_SKIP_SERVER_CERT_HOSTNAME_CHECK | LCCSCF_ALLOW_EXPIRED;
            }

            _lwsHost = lws_create_vhost(_helper->_lwsContext, &info);

            if (useSSL)
            {
                lws_init_vhost_client_ssl(&info, _lwsHost); //
            }

            auto path = _uri.getPathEtc().empty() ? "/" : _uri.getPathEtc();
            auto port = (int)_uri.getPort();
            if (port == 0)
                port = _uri.isSecure() ? 443 : 80;

            struct lws_client_connect_info cinfo;
            memset(&cinfo, 0, sizeof(cinfo));
            cinfo.context = _helper->_lwsContext;
            cinfo.address = _uri.getHostName().c_str();
            cinfo.port = port;
            cinfo.ssl_connection = sslFlags;
            cinfo.path = path.c_str();
            cinfo.host = _uri.getHostName().c_str();
            cinfo.origin = _uri.getAuthority().c_str();
            cinfo.protocol = _joinedProtocols.empty() ? "" : _joinedProtocols.c_str();
            cinfo.ietf_version_or_minus_one = -1;
            cinfo.userdata = this;
            cinfo.client_exts = exts;
            cinfo.vhost = _lwsHost;

            _wsi = lws_client_connect_via_info(&cinfo);

            if (_wsi == nullptr)
                netOnError(WebSocket::ErrorCode::UNKNOWN);

            _helper->reInitLibUV();
        }

        void WebSocketImpl::doDisconnect()
        {
            if (_state == WebSocket::State::CLOSED ||
                _state == WebSocket::State::UNINITIALIZED ) 
                return;
            _state = WebSocket::State::CLOSING;
            if(_wsi)
                lws_callback_on_writable(_wsi); //trigger onWritable
        }

        void WebSocketImpl::doWrite(NetDataPack &pack)
        {
            const size_t bufferSize = WS_RX_BUFFER_SIZE;
            const size_t frameSize = bufferSize > pack.remain() ? pack.remain() : bufferSize; //min

            int writeProtocol = 0;
            if (pack.consumed() == 0)
                writeProtocol |= (pack.isBinary() ? LWS_WRITE_BINARY : LWS_WRITE_TEXT);
            else
                writeProtocol |= LWS_WRITE_CONTINUATION;

            if (frameSize < pack.remain())
                writeProtocol |= LWS_WRITE_NO_FIN;

            int bytesWrite = lws_write(_wsi, pack.payload(), frameSize, (lws_write_protocol)writeProtocol);

            if (bytesWrite < 0)
            {
                //error 
                sigCloseSync();
            }
            else
            {
                pack.consume((size_t)bytesWrite);
            }
        }

        int WebSocketImpl::netOnError(WebSocket::ErrorCode ecode)
        {
            CHECK_INVOKE_FLAG(CallbackInvoke_ERROR);

            auto self = this->shared_from_this();

            _helper->runInUI([self, ecode]() {
                self->_delegate->onError(self->_ws, ecode);
                if (self->_state == WebSocket::State::CONNECTING)
                {
                    self->_state = WebSocket::State::CLOSED;
                }
            });

            //netOnClosed will be invoked by lws
            //netOnClosed();

            return 0;
        }

        int WebSocketImpl::netOnConnected()
        {
            CHECK_INVOKE_FLAG(CallbackInvoke_CONNECTED);
            //CCLOG("connected!");
            _state = WebSocket::State::OPEN;
            auto wsi = this->_wsi;
            auto self = this->shared_from_this();
            _helper->runInUI([self, wsi]() {
                self->_delegate->onOpen(self->_ws);
                lws_callback_on_writable(wsi);
            });
            return 0;
        }

        int WebSocketImpl::netOnClosed()
        {
            CHECK_INVOKE_FLAG(CallbackInvoke_CLOSED);
            _state = WebSocket::State::CLOSED;
            auto self = shared_from_this();
            auto wsid = _wsId;
            _helper->runInUI([self, wsid]() {
                self->_delegate->onClose(self->_ws);
            });

            {
                LOCK_MTX(WebSocketImpl::_cachedSocketsMtx);
                _cachedSockets.erase(wsid);
            }

            if (_cachedSockets.size() == 0)
            {
                //no active websocket, quit netThread
                Helper::drop();
            }

            return 0;
        }

        int WebSocketImpl::netOnReadable(void *in, size_t len)
        {
            //CCLOG("readable : %d", len);
            if (in && len > 0) {
                _receiveBuffer.insert(_receiveBuffer.end(), (uint8_t*)in, (uint8_t*)in + len);
            }

            auto remainSize = lws_remaining_packet_payload(_wsi);
            auto isFinalFrag = lws_is_final_fragment(_wsi);

            if (remainSize == 0 && isFinalFrag)
            {
                auto rbuffCopy = std::make_shared<std::vector<uint8_t>>(std::move(_receiveBuffer));

                _receiveBuffer.reserve(WS_REVERSED_RECEIVE_BUFFER_SIZE);

                bool isBinary = (lws_frame_is_binary(_wsi) != 0);

                if (!isBinary) //text, append '\0'
                {
                    rbuffCopy->insert(rbuffCopy->end(), '\0');
                }

                auto self = this->shared_from_this();
                _helper->runInUI([rbuffCopy, self, isBinary]() {
                    WebSocket::Data data((char*)(rbuffCopy->data()), rbuffCopy->size(), isBinary);
                    self->_delegate->onMessage(self->_ws, data);
                });
            }
            return 0;
        }

        int WebSocketImpl::netOnWritable()
        {
            //CCLOG("writable");

            //handle close
            if (_state == WebSocket::State::CLOSING || _state == WebSocket::State::CLOSED)
            {
                lwsl_warn("closing websocket\n");
                return -1;
            }

            //pop sent packs
            while (_sendBuffer.size() > 0 && _sendBuffer.front()->remain() == 0)
            {
                _sendBuffer.pop_front();
            }

            if (_sendBuffer.size() > 0)
            {
                auto &pack = _sendBuffer.front();
                if (pack->remain() > 0) {
                    doWrite(*pack);
                }
            }

            if (_wsi && _sendBuffer.size() > 0)
                lws_callback_on_writable(_wsi);

            return 0;
        }
    }
}
