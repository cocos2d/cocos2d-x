/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "CCApplication.h"
#include "CCDirector.h"
#include "CCDrawingPrimitives.h"
#include "CCEventCustom.h"
#include "CCEventType.h"
#include "CCGLView.h"
#include "CCShaderCache.h"
#include "CCTextureCache.h"
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#include <jni.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

void cocos_android_app_init(JNIEnv* env, jobject thiz) __attribute__((weak));

using namespace cocos2d;

extern "C"
{

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JniHelper::setJavaVM(vm);

    return JNI_VERSION_1_4;
}

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
{
    auto director = cocos2d::Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview)
    {
        glview = cocos2d::GLView::create("Android app");
        glview->setFrameSize(w, h);
        director->setOpenGLView(glview);

        cocos_android_app_init(env, thiz);

        cocos2d::Application::getInstance()->run();
    }
    else
    {
        cocos2d::GL::invalidateStateCache();
        cocos2d::ShaderCache::getInstance()->reloadDefaultShaders();
        cocos2d::DrawPrimitives::init();
        cocos2d::VolatileTextureMgr::reloadAllTextures();

        cocos2d::EventCustom foregroundEvent(EVENT_COME_TO_FOREGROUND);
        director->getEventDispatcher()->dispatchEvent(&foregroundEvent);
        director->setGLDefaultValues();
    }

}

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeOnSurfaceChanged(JNIEnv*  env, jobject thiz, jint w, jint h)
{
    cocos2d::Application::getInstance()->applicationScreenSizeChanged(w, h);
}
    
    
}
