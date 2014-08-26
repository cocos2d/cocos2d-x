#include "org_cocos2dx_lib_Cocos2dxWebViewHelper.h"
#include "WebViewImpl_android.h"
#include "WebView.h"
#include <stdlib.h>
#include <jni.h>
#include <string>


JNIEXPORT jboolean JNICALL Java_org_cocos2dx_lib_Cocos2dxWebViewHelper_shouldStartLoading(JNIEnv *env, jclass, jint index, jstring jurl) {
    auto charUrl = env->GetStringUTFChars(jurl, NULL);
    std::string url = charUrl;
    env->ReleaseStringUTFChars(jurl, charUrl);
    return cocos2d::plugin::WebViewImpl::shouldStartLoading(index, url);
}

JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxWebViewHelper_didFinishLoading(JNIEnv *env, jclass, jint index, jstring jurl) {
    auto charUrl = env->GetStringUTFChars(jurl, NULL);
    std::string url = charUrl;
    env->ReleaseStringUTFChars(jurl, charUrl);
    cocos2d::plugin::WebViewImpl::didFinishLoading(index, url);
}

JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxWebViewHelper_didFailLoading(JNIEnv *env, jclass, jint index, jstring jurl) {
    auto charUrl = env->GetStringUTFChars(jurl, NULL);
    std::string url = charUrl;
    env->ReleaseStringUTFChars(jurl, charUrl);
    cocos2d::plugin::WebViewImpl::didFailLoading(index, url);
}

JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxWebViewHelper_onJsCallback(JNIEnv *env, jclass, jint index, jstring jmessage) {
    auto charMessage = env->GetStringUTFChars(jmessage, NULL);
    std::string message = charMessage;
    env->ReleaseStringUTFChars(jmessage, charMessage);
    cocos2d::plugin::WebViewImpl::onJsCallback(index, message);
}
