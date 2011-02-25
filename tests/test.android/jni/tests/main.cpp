#include "Application.h"
#include "cocos2d.h"
#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

#define IMG_PATH        "assets"

extern "C"
{

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
{
    if (!cocos2d::CCDirector::sharedDirector()->getOpenGLView())
    {
		cocos2d::CCXEGLView *view = &cocos2d::CCXEGLView::sharedOpenGLView();
        view->setFrameWitdAndHeight(w, h);
        cocos2d::CCDirector::sharedDirector()->setOpenGLView(view);

        CCFileUtils::setRelativePath(IMG_PATH);

        Application app;
        app.run();
    }
    else
    {
        cocos2d::CCTexture2D::reloadAllTextures();
        cocos2d::CCDirector::sharedDirector()->setGLDefaultValues();
    }
}

}
