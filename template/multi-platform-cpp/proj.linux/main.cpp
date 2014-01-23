#include "../Classes/AppDelegate.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

USING_NS_CC;

int main(int argc, char **argv)
{
    // create the application instance
    AppDelegate app;
    EGLView eglView;
    eglView.init("Cocos2d-x Game",900,640);
    return Application::getInstance()->run();
}
