#include "main.h"
#include "../Classes/AppDelegate.h"
#include "cocos2d.h"


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

USING_NS_CC;

// 500 is enough?
#define MAXPATHLEN 500

int main(int argc, char **argv)
{
    // get application path
    int length;
    char fullpath[MAXPATHLEN];
    length = readlink("/proc/self/exe", fullpath, sizeof(fullpath));
    fullpath[length] = '\0';

    std::string resourcePath = fullpath;
    resourcePath = resourcePath.substr(0, resourcePath.find_last_of("/"));
    resourcePath += "/../../../Resources/";
    
    // create the application instance
    AppDelegate app;
    CCApplication::sharedApplication()->setResourceRootPath(resourcePath.c_str());
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setFrameSize(480, 320);

    return CCApplication::sharedApplication()->run();
}
