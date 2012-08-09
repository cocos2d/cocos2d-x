#include "main.h"

#include "../Classes/AppDelegate.h"
#include "cocos2d.h"
#include "CCEGLView.h"

USING_NS_CC;
int main(int argc, char **argv)
{
    // create the application instance
    AppDelegate app;
    CCApplication::sharedApplication().setResourceRootPath("../Resources/");
    CCEGLView& eglView = CCEGLView::sharedOpenGLView();
    eglView.setSize(960, 640 );
    return CCApplication::sharedApplication().run();
}
