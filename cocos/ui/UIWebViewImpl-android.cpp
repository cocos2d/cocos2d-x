/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#include "UIWebViewImpl-android.h"

#include <unordered_map>
#include <stdlib.h>
#include <string>
#include "jni/JniHelper.h"
#include <jni.h>

#include "UIWebView.h"
#include "platform/CCGLView.h"
#include "base/CCDirector.h"
#include "platform/CCFileUtils.h"

#define CLASS_NAME "org/cocos2dx/lib/Cocos2dxWebViewHelper"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,"",__VA_ARGS__)

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
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "createWebView", "()I")) {
        // LOGD("error: %s,%d",__func__,__LINE__);
        jint viewTag = t.env->CallStaticIntMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        return viewTag;
    }
    return -1;
}

void removeWebViewJNI(const int index) {
    // LOGD("error: %s,%d",__func__,__LINE__);
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "removeWebView", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setWebViewRectJNI(const int index, const int left, const int top, const int width, const int height) {
    // LOGD("error: %s,%d",__func__,__LINE__);
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setWebViewRect", "(IIIII)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, left, top, width, height);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setJavascriptInterfaceSchemeJNI(const int index, const std::string &scheme) {
    // LOGD("error: %s,%d",__func__,__LINE__);
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setJavascriptInterfaceScheme", "(ILjava/lang/String;)V")) {
        jstring jScheme = t.env->NewStringUTF(scheme.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, jScheme);

        t.env->DeleteLocalRef(jScheme);
        t.env->DeleteLocalRef(t.classID);
    }
}

void loadDataJNI(const int index, const std::string &data, const std::string &MIMEType, const std::string &encoding, const std::string &baseURL) {
    // LOGD("error: %s,%d",__func__,__LINE__);
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "loadData", "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring jData = t.env->NewStringUTF(data.c_str());
        jstring jMIMEType = t.env->NewStringUTF(MIMEType.c_str());
        jstring jEncoding = t.env->NewStringUTF(encoding.c_str());
        jstring jBaseURL = t.env->NewStringUTF(baseURL.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, jData, jMIMEType, jEncoding, jBaseURL);

        t.env->DeleteLocalRef(jData);
        t.env->DeleteLocalRef(jMIMEType);
        t.env->DeleteLocalRef(jEncoding);
        t.env->DeleteLocalRef(jBaseURL);
        t.env->DeleteLocalRef(t.classID);
    }
}

void loadHTMLStringJNI(const int index, const std::string &string, const std::string &baseURL) {
    // LOGD("error: %s,%d",__func__,__LINE__);
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "loadHTMLString", "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring jString = t.env->NewStringUTF(string.c_str());
        jstring jBaseURL = t.env->NewStringUTF(baseURL.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, jString, jBaseURL,nullptr);

        t.env->DeleteLocalRef(jString);
        t.env->DeleteLocalRef(jBaseURL);
        t.env->DeleteLocalRef(t.classID);
    }
}

void loadUrlJNI(const int index, const std::string &url) {
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "loadUrl", "(ILjava/lang/String;)V")) {
        jstring jUrl = t.env->NewStringUTF(url.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, jUrl);

        t.env->DeleteLocalRef(jUrl);
        t.env->DeleteLocalRef(t.classID);
    }
}

void loadFileJNI(const int index, const std::string &filePath) {
    // LOGD("error: %s,%d",__func__,__LINE__);
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "loadFile", "(ILjava/lang/String;)V")) {
        jstring jFilePath = t.env->NewStringUTF(filePath.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, jFilePath);

        t.env->DeleteLocalRef(jFilePath);
        t.env->DeleteLocalRef(t.classID);
    }
}

void stopLoadingJNI(const int index) {
    // LOGD("error: %s,%d",__func__,__LINE__);
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "stopLoading", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index);
        t.env->DeleteLocalRef(t.classID);
    }
}

void reloadJNI(const int index) {
    // LOGD("error: %s,%d",__func__,__LINE__);
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "reload", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index);
        t.env->DeleteLocalRef(t.classID);
    }
}

bool canGoBackJNI(const int index) {
    // LOGD("error: %s,%d",__func__,__LINE__);
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "canGoBack", "(I)Z")) {
        jboolean ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, index);
        t.env->DeleteLocalRef(t.classID);
        return ret;
    }
    return false;
}

bool canGoForwardJNI(const int index) {
    // LOGD("error: %s,%d",__func__,__LINE__);
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "canGoForward", "(I)Z")) {
        jboolean ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, index);
        t.env->DeleteLocalRef(t.classID);
        return ret;
    }
    return false;
}

void goBackJNI(const int index) {
    // LOGD("error: %s,%d",__func__,__LINE__);
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "goBack", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index);
        t.env->DeleteLocalRef(t.classID);
    }
}

void goForwardJNI(const int index) {
    // LOGD("error: %s,%d",__func__,__LINE__);
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "goForward", "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index);
        t.env->DeleteLocalRef(t.classID);
    }
}

void evaluateJSJNI(const int index, const std::string &js) {
    // LOGD("error: %s,%d",__func__,__LINE__);
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "evaluateJS", "(ILjava/lang/String;)V")) {
        jstring jjs = t.env->NewStringUTF(js.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, jjs);

        t.env->DeleteLocalRef(jjs);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setScalesPageToFitJNI(const int index, const bool scalesPageToFit) {
    // LOGD("error: %s,%d",__func__,__LINE__);
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setScalesPageToFit", "(IZ)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, scalesPageToFit);
        t.env->DeleteLocalRef(t.classID);
  }
}

void setWebViewVisibleJNI(const int index, const bool visible) {
    // LOGD("error: %s,%d",__func__,__LINE__);
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setVisible", "(IZ)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, index, visible);
        t.env->DeleteLocalRef(t.classID);
    }
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
                removeWebViewJNI(_viewTag);
                s_WebViewImpls.erase(_viewTag);
            }

            void WebViewImpl::loadData(const Data &data, const std::string &MIMEType, const std::string &encoding, const std::string &baseURL) {
                std::string dataString(reinterpret_cast<char *>(data.getBytes()), static_cast<unsigned int>(data.getSize()));
                loadDataJNI(_viewTag, dataString, MIMEType, encoding, baseURL);
            }

            void WebViewImpl::loadHTMLString(const std::string &string, const std::string &baseURL) {
                loadHTMLStringJNI(_viewTag, string, baseURL);
            }

            void WebViewImpl::loadURL(const std::string &url) {
                loadUrlJNI(_viewTag, url);
            }

            void WebViewImpl::loadFile(const std::string &fileName) {
                auto fullPath = getUrlStringByFileName(fileName);
                loadFileJNI(_viewTag, fullPath);
            }

            void WebViewImpl::stopLoading() {
                stopLoadingJNI(_viewTag);
            }

            void WebViewImpl::reload() {
                reloadJNI(_viewTag);
            }

            bool WebViewImpl::canGoBack() {
                return canGoBackJNI(_viewTag);
            }

            bool WebViewImpl::canGoForward() {
                return canGoForwardJNI(_viewTag);
            }

            void WebViewImpl::goBack() {
                goBackJNI(_viewTag);
            }

            void WebViewImpl::goForward() {
                goForwardJNI(_viewTag);
            }

            void WebViewImpl::setJavascriptInterfaceScheme(const std::string &scheme) {
                setJavascriptInterfaceSchemeJNI(_viewTag, scheme);
            }

            void WebViewImpl::evaluateJS(const std::string &js) {
                evaluateJSJNI(_viewTag, js);
            }

            void WebViewImpl::setScalesPageToFit(const bool scalesPageToFit) {
                setScalesPageToFitJNI(_viewTag, scalesPageToFit);
            }

            bool WebViewImpl::shouldStartLoading(const int viewTag, const std::string &url) {
                auto it = s_WebViewImpls.find(viewTag);
                if (it != s_WebViewImpls.end()) {
                    auto webView = s_WebViewImpls[viewTag]->_webView;
                    if (webView->_onShouldStartLoading) {
                        return webView->_onShouldStartLoading(webView, url);
                    }
                }
                return true;
            }

            void WebViewImpl::didFinishLoading(const int viewTag, const std::string &url){
                auto it = s_WebViewImpls.find(viewTag);
                if (it != s_WebViewImpls.end()) {
                    auto webView = s_WebViewImpls[viewTag]->_webView;
                    if (webView->_onDidFinishLoading) {
                        webView->_onDidFinishLoading(webView, url);
                    }
                }
            }

            void WebViewImpl::didFailLoading(const int viewTag, const std::string &url){
                auto it = s_WebViewImpls.find(viewTag);
                if (it != s_WebViewImpls.end()) {
                    auto webView = s_WebViewImpls[viewTag]->_webView;
                    if (webView->_onDidFailLoading) {
                        webView->_onDidFailLoading(webView, url);
                    }
                }
            }

            void WebViewImpl::onJsCallback(const int viewTag, const std::string &message){
                auto it = s_WebViewImpls.find(viewTag);
                if (it != s_WebViewImpls.end()) {
                    auto webView = s_WebViewImpls[viewTag]->_webView;
                    if (webView->_onJSCallback) {
                        webView->_onJSCallback(webView, message);
                    }
                }
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

                    setWebViewRectJNI(_viewTag,uiLeft,uiTop,
                                      (rightTop.x - leftBottom.x) * glView->getScaleX(),
                                      (rightTop.y - leftBottom.y) * glView->getScaleY());
                }
            }

            void WebViewImpl::setVisible(bool visible) {
                setWebViewVisibleJNI(_viewTag, visible);
            }
        } // namespace ui
    } // namespace experimental
} //namespace cocos2d

#endif // __ANDROID__
