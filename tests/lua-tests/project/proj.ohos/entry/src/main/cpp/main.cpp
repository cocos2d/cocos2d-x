#include "AppDelegate.h"
#include "cocos2d.h"
#include "base/CCEventType.h"
#include "CCLogOhos.h"

using namespace cocos2d;

extern "C"
{  

void Cocos2dxRenderer_nativeInit(int w, int h)
{
    OHOS_LOGD("Cocos2dxRenderer_nativeInit() - window width:[%{public}d], height:[%{public}d]", w, h);
    if (!CCDirector::sharedDirector()->getOpenGLView())
    {
        OHOS_LOGD("Cocos2dxRenderer_nativeInit() - branch 1");
        GLView *view = GLViewImpl::sharedOpenGLView();
        view->setFrameSize(w, h);
        CCDirector::sharedDirector()->setOpenGLView(view);

        AppDelegate *pAppDelegate = new AppDelegate();
        CCApplication::sharedApplication()->run();
    }
    else
    {
        OHOS_LOGD("Cocos2dxRenderer_nativeInit() - branch 2");
        ccGLInvalidateStateCache();
        CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
        ccDrawInit();
        CCTextureCache::reloadAllTextures();
        CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_COME_TO_FOREGROUND, NULL);
        CCDirector::sharedDirector()->setGLDefaultValues();
    }
}

}