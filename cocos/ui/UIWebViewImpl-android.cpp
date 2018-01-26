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

#ifdef __ANDROID__

#include "ui/UIWebViewImpl-android.h"

#include <unordered_map>
#include <stdlib.h>
#include <string>
#include "platform/android/jni/JniHelper.h"

#include "ui/UIWebView.h"
#include "platform/CCGLView.h"
#include "base/CCDirector.h"
#include "platform/CCFileUtils.h"
#include "ui/UIHelper.h"

static const std::string className = "org/cocos2dx/lib/Cocos2dxWebViewHelper";

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,"",__VA_ARGS__)

static const std::string s_defaultBaseUrl = "file:///android_asset/";
static const std::string s_sdRootBaseUrl = "file://";

static std::string getFixedBaseUrl(const std::string& baseUrl)
{
    std::string fixedBaseUrl;
    if (baseUrl.empty())
    {
        fixedBaseUrl = s_defaultBaseUrl;
    }
    else if (baseUrl.find(s_sdRootBaseUrl) !=  std::string::npos)
    {
        fixedBaseUrl = baseUrl;
    }
    else if (baseUrl.c_str()[0] != '/') {
        if(baseUrl.find("assets/") == 0) {
            fixedBaseUrl = s_defaultBaseUrl + baseUrl.c_str()[7];
        }
        else {
            fixedBaseUrl = s_defaultBaseUrl + baseUrl;
        }
    }
    else {
        fixedBaseUrl = s_sdRootBaseUrl + baseUrl;
    }
    
    if (fixedBaseUrl.c_str()[fixedBaseUrl.length() - 1] != '/') {
        fixedBaseUrl += "/";
    }
    
    return fixedBaseUrl;
}

extern "C" {
    /*
     * Class:     org_cocos2dx_lib_Cocos2dxWebViewHelper
     * Method:    shouldStartLoading
     * Signature: (ILjava/lang/String;)Z
     */
    JNIEXPORT jboolean JNICALL Java_org_cocos2dx_lib_Cocos2dxWebViewHelper_shouldStartLoading(JNIEnv *env, jclass, jint index, jstring jurl) {
        auto charUrl = env->GetStringUTFChars(jurl, NULL);
        std::string url = charUrl;
        env->ReleaseStringUTFChars(jurl, charUrl);
        return cocos2d::experimental::ui::WebViewImpl::shouldStartLoading(index, url);
    }

    /*
     * Class:     org_cocos2dx_lib_Cocos2dxWebViewHelper
     * Method:    didFinishLoading
     * Signature: (ILjava/lang/String;)V
     */
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxWebViewHelper_didFinishLoading(JNIEnv *env, jclass, jint index, jstring jurl) {
        // LOGD("didFinishLoading");
        auto charUrl = env->GetStringUTFChars(jurl, NULL);
        std::string url = charUrl;
        env->ReleaseStringUTFChars(jurl, charUrl);
        cocos2d::experimental::ui::WebViewImpl::didFinishLoading(index, url);
    }

    /*
     * Class:     org_cocos2dx_lib_Cocos2dxWebViewHelper
     * Method:    didFailLoading
     * Signature: (ILjava/lang/String;)V
     */
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxWebViewHelper_didFailLoading(JNIEnv *env, jclass, jint index, jstring jurl) {
        // LOGD("didFailLoading");
        auto charUrl = env->GetStringUTFChars(jurl, NULL);
        std::string url = charUrl;
        env->ReleaseStringUTFChars(jurl, charUrl);
        cocos2d::experimental::ui::WebViewImpl::didFailLoading(index, url);
    }

    /*
     * Class:     org_cocos2dx_lib_Cocos2dxWebViewHelper
     * Method:    onJsCallback
     * Signature: (ILjava/lang/String;)V
     */
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxWebViewHelper_onJsCallback(JNIEnv *env, jclass, jint index, jstring jmessage) {
        // LOGD("jsCallback");
        auto charMessage = env->GetStringUTFChars(jmessage, NULL);
        std::string message = charMessage;
        env->ReleaseStringUTFChars(jmessage, charMessage);
        cocos2d::experimental::ui::WebViewImpl::onJsCallback(index, message);
    }
}

namespace {

int createWebViewJNI() {
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, className.c_str(), "createWebView", "()I")) {
        // LOGD("error: %s,%d",__func__,__LINE__);
        jint viewTag = t.env->CallStaticIntMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        return viewTag;
    }
    return -1;
}

std::string getUrlStringByFileName(const std::string &fileName) {
    // LOGD("error: %s,%d",__func__,__LINE__);
    const std::string basePath("file:///android_asset/");
    std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(fileName);
    const std::string assetsPath("assets/");

    std::string urlString;
    if (fullPath.find(assetsPath) != std::string::npos) {
        urlString = fullPath.replace(fullPath.find_first_of(assetsPath), assetsPath.length(), basePath);
    } else {
        urlString = fullPath;
    }

    return urlString;
}
} // namespace

namespace cocos2d {
    namespace experimental {
        namespace ui{

            static std::unordered_map<int, cocos2d::experimental::ui::WebViewImpl*> s_WebViewImpls;

            WebViewImpl::WebViewImpl(WebView *webView) : _viewTag(-1), _webView(webView) {
                _viewTag = createWebViewJNI();
                s_WebViewImpls[_viewTag] = this;
            }

            WebViewImpl::~WebViewImpl() {
                JniHelper::callStaticVoidMethod(className, "removeWebView", _viewTag);
                s_WebViewImpls.erase(_viewTag);
            }

            void WebViewImpl::loadData(const Data &data, const std::string &MIMEType, const std::string &encoding, const std::string &baseURL) {
                std::string dataString(reinterpret_cast<char *>(data.getBytes()), static_cast<unsigned int>(data.getSize()));
                JniHelper::callStaticVoidMethod(className, "setJavascriptInterfaceScheme", _viewTag, dataString, MIMEType, encoding, baseURL);
            }

            void WebViewImpl::loadHTMLString(const std::string &string, const std::string &baseURL) {
                JniHelper::callStaticVoidMethod(className, "loadHTMLString", _viewTag, string, getFixedBaseUrl(baseURL));
            }

            void WebViewImpl::loadURL(const std::string &url) {
                this->loadURL(url, false);
            }

            void WebViewImpl::loadURL(const std::string &url, bool cleanCachedData) {
                JniHelper::callStaticVoidMethod(className, "loadUrl", _viewTag, url, cleanCachedData);
            }

            void WebViewImpl::loadFile(const std::string &fileName) {
                auto fullPath = getUrlStringByFileName(fileName);
                JniHelper::callStaticVoidMethod(className, "loadFile", _viewTag, fullPath);
            }

            void WebViewImpl::stopLoading() {
                JniHelper::callStaticVoidMethod(className, "stopLoading", _viewTag);
            }

            void WebViewImpl::reload() {
                JniHelper::callStaticVoidMethod(className, "reload", _viewTag);
            }

            bool WebViewImpl::canGoBack() {
                return JniHelper::callStaticBooleanMethod(className, "canGoBack", _viewTag);
            }

            bool WebViewImpl::canGoForward() {
                return JniHelper::callStaticBooleanMethod(className, "canGoForward", _viewTag);
            }

            void WebViewImpl::goBack() {
                JniHelper::callStaticVoidMethod(className, "goBack", _viewTag);
            }

            void WebViewImpl::goForward() {
                JniHelper::callStaticVoidMethod(className, "goForward", _viewTag);
            }

            void WebViewImpl::setJavascriptInterfaceScheme(const std::string &scheme) {
                JniHelper::callStaticVoidMethod(className, "setJavascriptInterfaceScheme", _viewTag, scheme);
            }

            void WebViewImpl::evaluateJS(const std::string &js) {
                JniHelper::callStaticVoidMethod(className, "evaluateJS", _viewTag, js);
            }

            void WebViewImpl::setScalesPageToFit(const bool scalesPageToFit) {
                JniHelper::callStaticVoidMethod(className, "setScalesPageToFit", _viewTag, scalesPageToFit);
            }

            bool WebViewImpl::shouldStartLoading(const int viewTag, const std::string &url) {
                bool allowLoad = true;
                auto it = s_WebViewImpls.find(viewTag);
                if (it != s_WebViewImpls.end()) {
                    auto webView = it->second->_webView;
                    if (webView->_onShouldStartLoading) {
                        allowLoad = webView->_onShouldStartLoading(webView, url);
                    }
                }
                return allowLoad;
            }

            void WebViewImpl::didFinishLoading(const int viewTag, const std::string &url){
                auto it = s_WebViewImpls.find(viewTag);
                if (it != s_WebViewImpls.end()) {
                    auto webView = it->second->_webView;
                    if (webView->_onDidFinishLoading) {
                        webView->_onDidFinishLoading(webView, url);
                    }
                }
            }

            void WebViewImpl::didFailLoading(const int viewTag, const std::string &url){
                auto it = s_WebViewImpls.find(viewTag);
                if (it != s_WebViewImpls.end()) {
                    auto webView = it->second->_webView;
                    if (webView->_onDidFailLoading) {
                        webView->_onDidFailLoading(webView, url);
                    }
                }
            }

            void WebViewImpl::onJsCallback(const int viewTag, const std::string &message){
                auto it = s_WebViewImpls.find(viewTag);
                if (it != s_WebViewImpls.end()) {
                    auto webView = it->second->_webView;
                    if (webView->_onJSCallback) {
                        webView->_onJSCallback(webView, message);
                    }
                }
            }

            void WebViewImpl::draw(cocos2d::Renderer *renderer, cocos2d::Mat4 const &transform, uint32_t flags) {
                if (flags & cocos2d::Node::FLAGS_TRANSFORM_DIRTY) {
                    auto uiRect = cocos2d::ui::Helper::convertBoundingBoxToScreen(_webView);
                    JniHelper::callStaticVoidMethod(className, "setWebViewRect", _viewTag, 
                                                    (int)uiRect.origin.x, (int)uiRect.origin.y,
                                                    (int)uiRect.size.width, (int)uiRect.size.height);
                }
            }

            void WebViewImpl::setVisible(bool visible) {
                JniHelper::callStaticVoidMethod(className, "setVisible", _viewTag, visible);
            }
            
            void WebViewImpl::setOpacityWebView(const float opacity){
                JniHelper::callStaticVoidMethod(className, "setOpacityWebView", _viewTag, opacity);
            };
            
            
            float WebViewImpl::getOpacityWebView()const{
                return JniHelper::callStaticFloatMethod(className, "getOpacityWebView", _viewTag);
            };
            
            void WebViewImpl::setBackgroundTransparent(){
                JniHelper::callStaticVoidMethod(className, "setBackgroundTransparent", _viewTag);
            };

            void WebViewImpl::setBounces(bool bounces) {
                // empty function as this was mainly a fix for iOS
            }
        } // namespace ui
    } // namespace experimental
} //namespace cocos2d

#endif // __ANDROID__
