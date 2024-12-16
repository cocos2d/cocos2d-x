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
#include "ui/UIWebViewImpl-ohos.h"

#include <cstdlib>
#include <string>
#include <unordered_map>

#include "platform/CCFileUtils.h"
#include "platform/ohos/CCLogOhos.h"
#include "platform/ohos/napi/helper/NapiHelper.h"
#include "ui/UIWebView.h"
#include "base/CCDirector.h"
#include "platform/CCGLView.h"

static const std::string SANDBOX_PREFIX = "file://";
static const char S_MIME_TYPE_TEXT[] = "text/html";
static const char S_ENCODING_UTF8[] = "UTF-8";

NS_CC_BEGIN
namespace experimental {
    namespace ui {
        static int32_t kWebViewTag = 0;
        static std::unordered_map<int, WebViewImpl *> sWebViewImpls;

        WebViewImpl::WebViewImpl(WebView *webView) : _viewTag(-1), _webView(webView) {
            _viewTag = kWebViewTag++;
            JSFunction::getFunction("WebView.createWebView").invoke<void>(_viewTag);
            sWebViewImpls[_viewTag] = this;
        }

        WebViewImpl::~WebViewImpl() {
            if (_viewTag != -1) {
                JSFunction::getFunction("WebView.removeWebView").invoke<void>(_viewTag);
                auto iter = sWebViewImpls.find(_viewTag);
                if (iter != sWebViewImpls.end()) {
                    sWebViewImpls.erase(iter);
                }
                _viewTag = -1;
            }
        }

        void WebViewImpl::setJavascriptInterfaceScheme(const std::string &scheme) {
            JSFunction::getFunction("WebView.setJavascriptInterfaceScheme").invoke<void>(_viewTag, scheme);
        }

        void WebViewImpl::loadData(const Data &data, const std::string &mimeType,
                                   const std::string &encoding, const std::string &baseURL) {
            std::string dataString(reinterpret_cast<char *>(data.getBytes()),
                                   static_cast<unsigned int>(data.getSize()));
            JSFunction::getFunction("WebView.loadData").invoke<void>(_viewTag, dataString, mimeType, encoding, baseURL);
        }

        void WebViewImpl::loadHTMLString(const std::string &string, const std::string &baseURL) {
            JSFunction::getFunction("WebView.loadData").invoke<void>(_viewTag, string, S_MIME_TYPE_TEXT, S_ENCODING_UTF8, baseURL);
        }

        void WebViewImpl::loadURL(const std::string &url) {
            JSFunction::getFunction("WebView.loadURL").invoke<void>(_viewTag, url);
        }

        void WebViewImpl::loadURL(const std::string &url, bool cleanCachedData) {
            // 官网接口未提供缓存相关参数，故与上一个loadUrl实现一致
            JSFunction::getFunction("WebView.loadURL").invoke<void>(_viewTag, url);
        }

        // TODO 当前仅支持绝对路径或rawfile目录，待完善功能
        void WebViewImpl::loadFile(const std::string &fileName) {
            std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
            if(fullPath[0] == '/') {
                JSFunction::getFunction("WebView.loadURL").invoke<void>(_viewTag, SANDBOX_PREFIX + fullPath);
            } else {
                JSFunction::getFunction("WebView.loadFile").invoke<void>(_viewTag, fullPath);
            }
        }

        void WebViewImpl::stopLoading() {
            JSFunction::getFunction("WebView.stopLoading").invoke<void>(_viewTag);
        }

        void WebViewImpl::reload() {
            JSFunction::getFunction("WebView.reload").invoke<void>(_viewTag);
        }

        bool WebViewImpl::canGoBack() {
            return JSFunction::getFunction("WebView.canGoBack").invoke<bool>(_viewTag);
        }

        bool WebViewImpl::canGoForward() {
            return JSFunction::getFunction("WebView.canGoForward").invoke<bool>(_viewTag);
        }

        void WebViewImpl::goBack() {
            JSFunction::getFunction("WebView.goBack").invoke<void>(_viewTag);
        }

        void WebViewImpl::goForward() {
            JSFunction::getFunction("WebView.goForward").invoke<void>(_viewTag);
        }

        void WebViewImpl::evaluateJS(const std::string &js) {
            JSFunction::getFunction("WebView.evaluateJS").invoke<void>(_viewTag, js);
        }

        void WebViewImpl::setScalesPageToFit(bool scalesPageToFit) {
            JSFunction::getFunction("WebView.setScalesPageToFit").invoke<void>(_viewTag, scalesPageToFit);
        }

        void WebViewImpl::draw(cocos2d::Renderer *renderer, cocos2d::Mat4 const &transform, uint32_t flags) {
            if (flags & cocos2d::Node::FLAGS_TRANSFORM_DIRTY) {
                auto directorInstance = cocos2d::Director::getInstance();
                auto glView = directorInstance->getOpenGLView();
                auto frameSize = glView->getFrameSize();
        
                auto winSize = directorInstance->getWinSize();
                auto leftBottom = this->_webView->convertToWorldSpace(cocos2d::Point::ZERO);
                auto rightTop = this->_webView->convertToWorldSpace(cocos2d::Point(this->_webView->getContentSize().width,this->_webView->getContentSize().height));
                
                auto uiLeft = frameSize.width / 2 + (leftBottom.x - winSize.width / 2 ) * glView->getScaleX();
                auto uiTop = frameSize.height /2 - (rightTop.y - winSize.height / 2) * glView->getScaleY();
                auto uiWidth = (rightTop.x - leftBottom.x) * glView->getScaleX();
                auto uiHeight = (rightTop.y - leftBottom.y) * glView->getScaleY();
                JSFunction::getFunction("WebView.setWebViewRect").invoke<void>(_viewTag, uiLeft, uiTop, uiWidth, uiHeight);
            }
        }

        void WebViewImpl::setVisible(bool visible) {
            JSFunction::getFunction("WebView.setVisible").invoke<void>(_viewTag, visible);
        }

        void WebViewImpl::setOpacityWebView(const float opacity) {
            JSFunction::getFunction("WebView.setOpacityWebView").invoke<void>(_viewTag, (double)opacity);
        }

        float WebViewImpl::getOpacityWebView() const { 
            return JSFunction::getFunction("WebView.getOpacityWebView").invoke<double>(_viewTag);
        }

        void WebViewImpl::setBackgroundTransparent() {
            JSFunction::getFunction("WebView.setBackgroundTransparent").invoke<void>(_viewTag);
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

        void WebViewImpl::didFinishLoading(int viewTag, const std::string &url) {
            auto it = sWebViewImpls.find(viewTag);
            if (it != sWebViewImpls.end()) {
                auto webView = it->second->_webView;
                if (webView->getOnDidFinishLoading()) {
                    WebView::ccWebViewCallback fun = webView->getOnDidFinishLoading();
                    fun(webView, url);
                }
            }
        }

        void WebViewImpl::didFailLoading(int viewTag, const std::string &url) {
            auto it = sWebViewImpls.find(viewTag);
            if (it != sWebViewImpls.end()) {
                auto webView = it->second->_webView;
                if (webView->getOnDidFailLoading()) {
                    WebView::ccWebViewCallback fun = webView->getOnDidFailLoading();
                    fun(webView, url);
                }
            }
        }

        void WebViewImpl::onJsCallback(int viewTag, const std::string &message) {
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
} // namespace experimental
NS_CC_END