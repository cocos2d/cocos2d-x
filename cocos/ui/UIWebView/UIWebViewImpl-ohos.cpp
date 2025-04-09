/****************************************************************************
 Copyright (c) 2022-2023 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/
#include "ui/UIWebView/UIWebViewImpl-ohos.h"

#include <cstdlib>
#include <string>
#include <unordered_map>

#include "platform/CCFileUtils.h"
#include "platform/ohos/CCLogOhos.h"
#include "ui/UIHelper.h"
#include "ui/UIWebView/UIWebView.h"
#include "aki/jsbind.h"

static const std::string SANDBOX_PREFIX = "file://";
static const char S_MIME_TYPE_TEXT[] = "text/html";
static const char S_ENCODING_UTF8[] = "UTF-8";

NS_CC_BEGIN

    namespace ui {
        static int32_t kWebViewTag = 0;
        static std::unordered_map<int, WebViewImpl *> sWebViewImpls;

        WebViewImpl::WebViewImpl(WebView *webView) : _viewTag(-1), _webView(webView) {
            _viewTag = kWebViewTag++;
            if (auto function = aki::JSBind::GetJSFunction("WebView.createWebView")) {
                function->Invoke<void>(_viewTag); 
            }
            sWebViewImpls[_viewTag] = this;
    // TODO There is a delay when the web component is bound to the controller. The sleep function is used to avoid errors. The onControllerAttached function that may be opened by API10 is used to control the binding.
            OHOS_LOGD("webview will sleep for 2s");
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }

        WebViewImpl::~WebViewImpl() {
            if (_viewTag != -1) {
                if (auto function = aki::JSBind::GetJSFunction("WebView.removeWebView")) {
                    function->Invoke<void>(_viewTag); 
                }
                auto iter = sWebViewImpls.find(_viewTag);
                if (iter != sWebViewImpls.end()) {
                    sWebViewImpls.erase(iter);
                }
                _viewTag = -1;
            }
        }

        void WebViewImpl::setJavascriptInterfaceScheme(const std::string &scheme) {
            if (auto function = aki::JSBind::GetJSFunction("WebView.setJavascriptInterfaceScheme")) {
                function->Invoke<void>(_viewTag, scheme); 
            }
        }

        void WebViewImpl::loadData(const Data &data, const std::string &mimeType,
                                   const std::string &encoding, const std::string &baseURL) {
            std::string dataString(reinterpret_cast<char *>(data.getBytes()),
                                   static_cast<unsigned int>(data.getSize()));
            if (auto function = aki::JSBind::GetJSFunction("WebView.loadData")) {
                function->Invoke<void>(_viewTag, dataString, mimeType, encoding, baseURL); 
            }
        }

        void WebViewImpl::loadHTMLString(const std::string &string, const std::string &baseURL) {
            if (auto function = aki::JSBind::GetJSFunction("WebView.loadData")) {
                function->Invoke<void>(_viewTag, string, S_MIME_TYPE_TEXT, S_ENCODING_UTF8, baseURL); 
            }
        }

        void WebViewImpl::loadURL(const std::string &url) {
            if (auto function = aki::JSBind::GetJSFunction("WebView.loadURL")) {
                function->Invoke<void>(_viewTag, url); 
            }
        }

        void WebViewImpl::loadURL(const std::string &url, bool cleanCachedData) {
            // The official website interface does not provide cache-related parameters. Therefore, the implementation of loadUrl is the same as that of the previous loadUrl.
            if (auto function = aki::JSBind::GetJSFunction("WebView.loadURL")) {
                function->Invoke<void>(_viewTag, url); 
            }
        }

        void WebViewImpl::loadFile(const std::string &fileName) {
            std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
            if(fullPath[0] == '/') {
                if (auto function = aki::JSBind::GetJSFunction("WebView.loadURL")) {
                  function->Invoke<void>(_viewTag, SANDBOX_PREFIX + fullPath); 
                }
            } else {
                if (auto function = aki::JSBind::GetJSFunction("WebView.loadFile")) {
                  function->Invoke<void>(_viewTag, fullPath); 
                }
            }
        }

        void WebViewImpl::stopLoading() {
            if (auto function = aki::JSBind::GetJSFunction("WebView.stopLoading")) {
              function->Invoke<void>(_viewTag); 
            }
        }

        void WebViewImpl::reload() {
            if (auto function = aki::JSBind::GetJSFunction("WebView.reload")) {
              function->Invoke<void>(_viewTag); 
            }
        }

        bool WebViewImpl::canGoBack() {
            return true;
        }

        bool WebViewImpl::canGoForward() {
            return true;
        }

        void WebViewImpl::goBack() {
            if (auto function = aki::JSBind::GetJSFunction("WebView.goBack")) {
              function->Invoke<void>(_viewTag); 
            }
        }

        void WebViewImpl::goForward() {
            if (auto function = aki::JSBind::GetJSFunction("WebView.goForward")) {
              function->Invoke<void>(_viewTag); 
            }
        }

        void WebViewImpl::evaluateJS(const std::string &js) {
            if (auto function = aki::JSBind::GetJSFunction("WebView.evaluateJS")) {
              function->Invoke<void>(_viewTag, js); 
            }
        }

        void WebViewImpl::setScalesPageToFit(bool scalesPageToFit) {
            if (auto function = aki::JSBind::GetJSFunction("WebView.setScalesPageToFit")) {
              function->Invoke<void>(_viewTag, scalesPageToFit); 
            }
        }

        void WebViewImpl::draw(cocos2d::Renderer *renderer, cocos2d::Mat4 const &transform, uint32_t flags) {
            if (flags & cocos2d::Node::FLAGS_TRANSFORM_DIRTY) {
                auto uiRect = cocos2d::ui::Helper::convertBoundingBoxToScreen(_webView);
                if (auto function = aki::JSBind::GetJSFunction("WebView.setWebViewRect")) {
                  function->Invoke<void>(_viewTag, (int) uiRect.origin.x, (int) uiRect.origin.y,
                                      (int) uiRect.size.width, (int) uiRect.size.height); 
                }
            }
        }

        void WebViewImpl::setVisible(bool visible) {
            if (auto function = aki::JSBind::GetJSFunction("WebView.setVisible")) {
              function->Invoke<void>(_viewTag, visible); 
            }
        }

        void WebViewImpl::setOpacityWebView(const float opacity) {
            _opacity = opacity;
            if (auto function = aki::JSBind::GetJSFunction("WebView.setOpacityWebView")) {
              function->Invoke<void>(_viewTag, (double)_opacity); 
            }
        }

        float WebViewImpl::getOpacityWebView() const {
            return _opacity;
        }

        void WebViewImpl::setBackgroundTransparent() {
            if (auto function = aki::JSBind::GetJSFunction("WebView.setBackgroundTransparent")) {
              function->Invoke<void>(_viewTag); 
            }
        }

        void WebViewImpl::setBounces(bool bounces) {
            // empty function as this was mainly a fix for iOS
        }

        bool WebViewImpl::shouldStartLoading(int viewTag, const std::string &url) {
            bool allowLoad = true;
            auto it = sWebViewImpls.find(viewTag);
            if (it != sWebViewImpls.end()) {
                auto webView = it->second->_webView;
                if (webView->getOnShouldStartLoading()) {
                    std::function < bool(WebView * sender,
                    const std::string &url)> fun = webView->getOnShouldStartLoading();
                    allowLoad = fun(webView, url);
                }
            }
            return allowLoad;
        }

        void WebViewImpl::finishLoading(int viewTag, const std::string &url) {
            auto it = sWebViewImpls.find(viewTag);
            if (it != sWebViewImpls.end()) {
                auto webView = it->second->_webView;
                if (webView->getOnDidFinishLoading()) {
                    WebView::ccWebViewCallback fun = webView->getOnDidFinishLoading();
                    fun(webView, url);
                }
            }
        }

        void WebViewImpl::failLoading(int viewTag, const std::string &url) {
            auto it = sWebViewImpls.find(viewTag);
            if (it != sWebViewImpls.end()) {
                auto webView = it->second->_webView;
                if (webView->getOnDidFailLoading()) {
                    WebView::ccWebViewCallback fun = webView->getOnDidFailLoading();
                    fun(webView, url);
                }
            }
        }

        void WebViewImpl::jsCallback(int viewTag, const std::string &message) {
            auto it = sWebViewImpls.find(viewTag);
            if (it != sWebViewImpls.end()) {
                auto webView = it->second->_webView;
                if (webView->getOnJSCallback()) {
                    WebView::ccWebViewCallback fun = webView->getOnJSCallback();
                    fun(webView, message);
                }
            }
        }
    } // namespace ui

NS_CC_END
