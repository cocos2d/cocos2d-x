#include "../../Classes/AppDelegate.h"

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
    Application::getInstance()->setDeviceOrientation(APP_DEVICE_ORIENTATION_90);
    return Application::getInstance()->run();
}
