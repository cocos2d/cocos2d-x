#include "AppDelegate.h"
#include "cocos2d.h"
#include <jni.h>
#include <android/log.h>

using namespace cocos2d;

#define IMG_PATH        "assets"

extern "C"
{

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
{
    if (!cocos2d::CCDirector::sharedDirector()->getOpenGLView())
    {
        cocos2d::CCXEGLView *view = new cocos2d::CCXEGLView();
        view->setFrameWitdAndHeight(w, h);
        cocos2d::CCDirector::sharedDirector()->setOpenGLView(view);

        CCFileUtils::setRelativePath(IMG_PATH);

        AppDelegate app;
        app.Run();
    }
    else
    {
        cocos2d::CCTexture2D::reloadAllTextures();
        cocos2d::CCDirector::sharedDirector()->setGLDefaultValues();
    }
}

}
