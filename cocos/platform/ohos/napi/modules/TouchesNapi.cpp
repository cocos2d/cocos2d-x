#include "deprecated/CCSet.h"
#include "base/CCDirector.h"
#include "base/CCTouch.h"
#include "platform/CCGLView.h"
#include "platform/ohos/CCLogOhos.h"
#include <cstddef>

using namespace cocos2d;

extern "C" {
    void Cocos2dxRenderer_nativeTouchesBegin(int num, intptr_t ids[] , float xs[], float ys[]) {
        cocos2d::Director::sharedDirector()->getOpenGLView()->handleTouchesBegin(num, ids, xs, ys);
    }

    void Cocos2dxRenderer_nativeTouchesEnd(intptr_t id, float x, float y) {
        cocos2d::Director::sharedDirector()->getOpenGLView()->handleTouchesEnd(1, &id, &x, &y);
    }

    void Cocos2dxRenderer_nativeTouchesMove(int num, intptr_t ids[] , float xs[], float ys[]) {
       cocos2d::Director::sharedDirector()->getOpenGLView()->handleTouchesMove(num, ids, xs, ys);
    }

    void Cocos2dxRenderer_nativeTouchesCancel(int num, intptr_t ids[] , float xs[], float ys[]) {
       cocos2d::Director::sharedDirector()->getOpenGLView()->handleTouchesCancel(num, ids, xs, ys);
    }

    #define KEYCODE_BACK 0x04
    #define KEYCODE_MENU 0x52
    bool Cocos2dxRenderer_nativeKeyDown(int keyCode) {
       Director* pDirector = Director::sharedDirector();
       switch (keyCode) {
           case KEYCODE_BACK:
                    // TBD need fixed 
//                 if (pDirector->getKeypadDispatcher()->dispatchKeypadMSG(kTypeBackClicked))
                   return true;
               break;
           case KEYCODE_MENU:
//               if (pDirector->getKeypadDispatcher()->dispatchKeypadMSG(kTypeMenuClicked))
                   return true;
               break;
           default:
               return false;
       }
        return 0;
    }
}
