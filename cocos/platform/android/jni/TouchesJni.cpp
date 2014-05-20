/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#include "base/CCDirector.h"
#include "base/CCEventKeyboard.h"
#include "CCGLView.h"

#include <android/log.h>
#include <jni.h>

using namespace cocos2d;

extern "C" {
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesBegin(JNIEnv * env, jobject thiz, jint id, jfloat x, jfloat y) {
        cocos2d::Director::getInstance()->getOpenGLView()->handleTouchesBegin(1, &id, &x, &y);
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesEnd(JNIEnv * env, jobject thiz, jint id, jfloat x, jfloat y) {
        cocos2d::Director::getInstance()->getOpenGLView()->handleTouchesEnd(1, &id, &x, &y);
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesMove(JNIEnv * env, jobject thiz, jintArray ids, jfloatArray xs, jfloatArray ys) {
        int size = env->GetArrayLength(ids);
        jint id[size];
        jfloat x[size];
        jfloat y[size];

        env->GetIntArrayRegion(ids, 0, size, id);
        env->GetFloatArrayRegion(xs, 0, size, x);
        env->GetFloatArrayRegion(ys, 0, size, y);

        cocos2d::Director::getInstance()->getOpenGLView()->handleTouchesMove(size, id, x, y);
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesCancel(JNIEnv * env, jobject thiz, jintArray ids, jfloatArray xs, jfloatArray ys) {
        int size = env->GetArrayLength(ids);
        jint id[size];
        jfloat x[size];
        jfloat y[size];

        env->GetIntArrayRegion(ids, 0, size, id);
        env->GetFloatArrayRegion(xs, 0, size, x);
        env->GetFloatArrayRegion(ys, 0, size, y);

        cocos2d::Director::getInstance()->getOpenGLView()->handleTouchesCancel(size, id, x, y);
    }

#define KEYCODE_BACK 0x04
#define KEYCODE_MENU 0x52
#define KEYCODE_DPAD_UP 0x13
#define KEYCODE_DPAD_DOWN 0x14
#define KEYCODE_DPAD_LEFT 0x15
#define KEYCODE_DPAD_RIGHT 0x16
#define KEYCODE_ENTER 0x42
#define KEYCODE_PLAY  0x7e
#define KEYCODE_DPAD_CENTER  0x17
    
    
    static std::unordered_map<int, cocos2d::EventKeyboard::KeyCode> g_keyCodeMap = {
        { KEYCODE_BACK , cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE},
        { KEYCODE_MENU , cocos2d::EventKeyboard::KeyCode::KEY_MENU},
        { KEYCODE_DPAD_UP  , cocos2d::EventKeyboard::KeyCode::KEY_DPAD_UP },
        { KEYCODE_DPAD_DOWN , cocos2d::EventKeyboard::KeyCode::KEY_DPAD_DOWN },
        { KEYCODE_DPAD_LEFT , cocos2d::EventKeyboard::KeyCode::KEY_DPAD_LEFT },
        { KEYCODE_DPAD_RIGHT , cocos2d::EventKeyboard::KeyCode::KEY_DPAD_RIGHT },
        { KEYCODE_ENTER  , cocos2d::EventKeyboard::KeyCode::KEY_ENTER},
        { KEYCODE_PLAY  , cocos2d::EventKeyboard::KeyCode::KEY_PLAY},
        { KEYCODE_DPAD_CENTER  , cocos2d::EventKeyboard::KeyCode::KEY_DPAD_CENTER},
        
    };
    
    JNIEXPORT jboolean JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeKeyDown(JNIEnv * env, jobject thiz, jint keyCode) {
        Director* pDirector = Director::getInstance();
        
        auto iterKeyCode = g_keyCodeMap.find(keyCode);
        if (iterKeyCode == g_keyCodeMap.end()) {
            return JNI_FALSE;
        }
        
        cocos2d::EventKeyboard::KeyCode cocos2dKey = g_keyCodeMap.at(keyCode);
        cocos2d::EventKeyboard event(cocos2dKey, false);
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
        return JNI_TRUE;
        
    }}
