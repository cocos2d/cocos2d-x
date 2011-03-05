#include "tests.h"

#include <jni.h>
#include <android/log.h>

#include "AppDelegate.h"

using namespace cocos2d;

extern "C"
{
	
void initProgram()
{
	AppDelegate app;
	app.Run();
}

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
{
    if (!cocos2d::CCDirector::sharedDirector()->getOpenGLView())
    {
        cocos2d::CCEGLView *view = new cocos2d::CCEGLView();
        view->setFrameWitdAndHeight(w, h);
        cocos2d::CCDirector::sharedDirector()->setOpenGLView(view);
        initProgram();
    }
    else
    {
        cocos2d::CCTexture2D::reloadAllTextures();
        cocos2d::CCDirector::sharedDirector()->setGLDefaultValues();
    }
}

}
