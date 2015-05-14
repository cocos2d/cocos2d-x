#include "main.h"
#include "SimulatorWin.h"
#include <shellapi.h>

#if _MSC_VER > 1700
#pragma comment(lib,"libcocos2d_2013.lib")
#pragma comment(lib,"libjscocos2d_2013.lib")
#pragma comment(lib,"libbox2d_2013.lib")
#pragma comment(lib,"libSpine_2013.lib")
#pragma comment(lib,"libsimulator_2013.lib")
#else
#pragma comment(lib,"libcocos2d_2012.lib")
#pragma comment(lib,"libjscocos2d_2012.lib")
#pragma comment(lib,"libbox2d_2012.lib")
#pragma comment(lib,"libSpine_2012.lib")
#pragma comment(lib,"libsimulator_2012.lib")
#endif

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
    auto simulator = SimulatorWin::getInstance();
    return simulator->run();
}
