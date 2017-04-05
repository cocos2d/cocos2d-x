#include "AppDelegate.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <app.h>

USING_NS_CC;

int main(int argc, char **argv)
{
    // create the application instance
    AppDelegate app;
#ifdef TIZEN
	Application::getInstance()->setMainArgs(argc, argv);//For Tizen 2.4, we need these two arguments.
#endif
    Application::getInstance()->setDeviceOrientation(APP_DEVICE_ORIENTATION_90);
    return Application::getInstance()->run();
}
