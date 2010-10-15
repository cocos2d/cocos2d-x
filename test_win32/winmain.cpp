#include "winmain.h"
#include "TestApplication.h"

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
	TestApplication app;
	do 
	{
		if (! app.InitInstance())
		{
			break;
		}
		if (! app.initCocos2d())
		{
			break;
		}
		nRet = app.Run();
	} while (0);
	return nRet;
}
