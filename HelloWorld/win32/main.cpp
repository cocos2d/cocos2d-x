#include "main.h"

#include "AppDelegate.h"

HINSTANCE g_hInstance;

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	g_hInstance = hInstance;

	int nRet = 0;

    // create the application instance
	AppDelegate app;

    nRet = cocos2d::ccxApplication::sharedApplication().run();

	return nRet;
}
