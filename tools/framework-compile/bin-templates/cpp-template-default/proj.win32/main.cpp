#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;

#pragma comment(lib,"libcocos2d.lib")
#pragma comment(lib,"libbox2d.lib")
#pragma comment(lib,"libSpine.lib")

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}
