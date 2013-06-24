#include "../Classes/AppDelegate.h"
#include "cocos2d.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

USING_NS_CC;

int main(int argc, char **argv)
{
    // create the application instance
    AppDelegate app;

    EGLView* eglView = EGLView::sharedOpenGLView();
    eglView->setFrameSize(800, 480);

    return Application::sharedApplication()->run();
}
