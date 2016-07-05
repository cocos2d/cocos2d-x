#include "../Classes/AppDelegate.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

USING_NS_CC;

#define STRINGIZE_(x) #x
#define STRINGIZE(x) STRINGIZE_(x)

int main(int argc, char **argv)
{
    // create the application instance
#ifdef EMSCRIPTEN_APP_VERSION
    Application::setAppVersion(STRINGIZE(EMSCRIPTEN_APP_VERSION));
#else
    Application::setAppVersion("1.0");
#endif
    AppDelegate app;
    return Application::getInstance()->run();
}