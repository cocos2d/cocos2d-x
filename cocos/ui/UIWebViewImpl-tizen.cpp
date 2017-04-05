/****************************************************************************
 Copyright (c) 2014-2017 Chukong Technologies Inc.
 
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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN)

#include "ui/UIWebViewImpl-tizen.h"

#include <unordered_map>
#include <stdlib.h>
#include <string>

#include "platform/tizen/CCApplication-tizen.h"
#include "ui/UIWebView.h"
#include "platform/CCGLView.h"
#include "base/CCDirector.h"
#include "platform/CCFileUtils.h"
#include "EWebKit.h"

void JScallback(Evas_Object* o, const char* result_value, void* user_data)
{
}

namespace cocos2d {
    namespace experimental {
        namespace ui{

            WebViewImpl::WebViewImpl(WebView *webView) : _webView(webView) {
                Application* app = Application::getInstance();
                Evas *evas = evas_object_evas_get(app->_win);
                _ewkView = ewk_view_add(evas);
            }

            WebViewImpl::~WebViewImpl() {
                evas_object_del(_ewkView);
            }

            void WebViewImpl::loadData(const Data &data, const std::string &MIMEType, const std::string &encoding, const std::string &baseURL) {
                const char* contents = nullptr;
                size_t contents_size = 0;
                char* mime_type = (char*)MIMEType.c_str();
                char* encode = (char*)encoding.c_str();
                char* base_uri = (char*)baseURL.c_str();
                ewk_view_contents_set(_ewkView, contents, contents_size, mime_type, encode, base_uri);
            }

            void WebViewImpl::loadHTMLString(const std::string &string, const std::string &baseURL) {

                const char* contents = string.c_str();
                size_t contents_size = string.length();
                char* mime_type = (char*)baseURL.c_str();
                char* encoding = nullptr;
                char* base_uri = nullptr;//(char*)baseURL.c_str();
                ewk_view_contents_set(_ewkView, contents, contents_size, mime_type, encoding, base_uri);
            }

            void WebViewImpl::loadURL(const std::string &url) {

                const char* urlchar = url.c_str();
                ewk_view_url_set(_ewkView, urlchar);
            }

            void WebViewImpl::loadURL(const std::string &url, bool cleanCachedData) {
                this->loadURL(url);
            }

            void WebViewImpl::loadFile(const std::string &fileName) {
                auto fileUtiles = FileUtils::getInstance();
                auto fileFullPath = fileUtiles->fullPathForFilename(fileName);
                auto contentsString = fileUtiles->getStringFromFile(fileFullPath);
                loadHTMLString(contentsString, "text/html");
            }

            void WebViewImpl::stopLoading() {
                ewk_view_stop(_ewkView);
            }

            void WebViewImpl::reload() {
                ewk_view_reload(_ewkView);
            }

            bool WebViewImpl::canGoBack() {
                return ewk_view_back_possible(_ewkView);
            }

            bool WebViewImpl::canGoForward() {
                return ewk_view_forward_possible(_ewkView);
            }

            void WebViewImpl::goBack() {
                ewk_view_back(_ewkView);
            }

            void WebViewImpl::goForward() {
                ewk_view_forward(_ewkView);
            }

            void WebViewImpl::setJavascriptInterfaceScheme(const std::string &scheme) {
            }

            void WebViewImpl::evaluateJS(const std::string &js) {
                const char* script = js.c_str();
                Eina_Bool ret = ewk_view_script_execute(_ewkView, script, JScallback, this);
            }

            void WebViewImpl::setScalesPageToFit(const bool scalesPageToFit) {
            }

            void WebViewImpl::draw(cocos2d::Renderer *renderer, cocos2d::Mat4 const &transform, int flags) {
                if (flags & cocos2d::Node::FLAGS_TRANSFORM_DIRTY) {
                    auto directorInstance = cocos2d::Director::getInstance();
                    auto glView = directorInstance->getOpenGLView();
                    auto frameSize = glView->getFrameSize();

                    auto winSize = directorInstance->getWinSize();

                    auto leftBottom = this->_webView->convertToWorldSpace(cocos2d::Point::ZERO);
                    auto rightTop = this->_webView->convertToWorldSpace(cocos2d::Point(this->_webView->getContentSize().width,this->_webView->getContentSize().height));

                    auto uiLeft = frameSize.width / 2 + (leftBottom.x - winSize.width / 2 ) * glView->getScaleX();
                    auto uiTop = frameSize.height /2 - (rightTop.y - winSize.height / 2) * glView->getScaleY();

                    Evas_Coord width = (rightTop.x - leftBottom.x) * glView->getScaleX();
                    Evas_Coord height = (rightTop.y - leftBottom.y) * glView->getScaleY();

                    evas_object_resize(_ewkView, width, height);
                    evas_object_move(_ewkView, uiLeft, uiTop);
                    evas_object_show(_ewkView);
                }
            }

            void WebViewImpl::setVisible(bool visible) {
                if (visible)
                {
                    evas_object_show(_ewkView);
                }
                else
                {
                    evas_object_hide(_ewkView);
                }
            }

            void WebViewImpl::setBounces(bool bounces) {
                // empty function as this was mainly a fix for iOS
            }
        } // namespace ui
    } // namespace experimental
} //namespace cocos2d

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN)
