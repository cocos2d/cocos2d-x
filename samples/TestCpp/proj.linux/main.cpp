#include "main.h"
#include "cocos2d.h"
#include "../Classes/AppDelegate.h"

USING_NS_CC;
int main(int argc, char **argv) {
    // create the application instance
    AppDelegate app;
    CCApplication::sharedApplication().setResourceRootPath("../Resources/");
    CCEGLView& eglView = CCEGLView::sharedOpenGLView();
    eglView.setSize(480, 320 );

    return CCApplication::sharedApplication().run();
}
