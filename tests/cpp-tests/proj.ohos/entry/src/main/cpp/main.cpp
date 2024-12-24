#include "AppDelegate.h"
#include "cocos2d.h"
#include "base/CCEventType.h"
#include "CCLogOhos.h"

using namespace cocos2d;

extern "C" {

void Cocos2dxRenderer_nativeInit(int w, int h) {
    OHOS_LOGD("Cocos2dxRenderer_nativeInit() - window width:[%{public}d], height:[%{public}d]", w, h);
    if (!Director::getInstance()->getOpenGLView()) {
        OHOS_LOGD("Cocos2dxRenderer_nativeInit() - branch 1");
        GLView *view = GLViewImpl::sharedOpenGLView();
        view->setFrameSize(w, h);
        Director::getInstance()->setOpenGLView(view);

        AppDelegate *pAppDelegate = new AppDelegate();
        Application::getInstance()->run();
    }
}

}