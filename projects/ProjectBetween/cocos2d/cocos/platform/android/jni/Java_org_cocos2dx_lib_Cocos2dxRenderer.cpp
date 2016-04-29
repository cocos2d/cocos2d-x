#include "base/CCIMEDispatcher.h"
#include "base/CCDirector.h"
#include "base/CCEventType.h"
#include "base/CCEventCustom.h"
#include "base/CCEventDispatcher.h"
#include "../CCApplication.h"
#include "platform/CCFileUtils.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

#include "base/ccUTF8.h"

using namespace cocos2d;

extern "C" {

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeRender(JNIEnv* env) {
        cocos2d::Director::getInstance()->mainLoop();
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeOnPause() {
        if (Director::getInstance()->getOpenGLView()) {
                Application::getInstance()->applicationDidEnterBackground();
                cocos2d::EventCustom backgroundEvent(EVENT_COME_TO_BACKGROUND);
                cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&backgroundEvent);
        }
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeOnResume() {
        if (Director::getInstance()->getOpenGLView()) {
            Application::getInstance()->applicationWillEnterForeground();
            cocos2d::EventCustom foregroundEvent(EVENT_COME_TO_FOREGROUND);
            cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&foregroundEvent);
        }
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInsertText(JNIEnv* env, jobject thiz, jstring text) {
        std::string  strValue = cocos2d::StringUtils::getStringUTFCharsJNI(env, text);
        const char* pszText = strValue.c_str();
        cocos2d::IMEDispatcher::sharedDispatcher()->dispatchInsertText(pszText, strlen(pszText));
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeDeleteBackward(JNIEnv* env, jobject thiz) {
        cocos2d::IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
    }

    JNIEXPORT jstring JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeGetContentText() {
        JNIEnv * env = 0;

        if (JniHelper::getJavaVM()->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK || ! env) {
            return 0;
        }
        std::string pszText = cocos2d::IMEDispatcher::sharedDispatcher()->getContentText();
        return cocos2d::StringUtils::newStringUTFJNI(env, pszText);
    }
}
