#include "main.h"
#include "SimulatorWin.h"
#include <shellapi.h>

#pragma comment(lib,"libcocos2d.lib")
#pragma comment(lib,"libluacocos2d.lib")
#pragma comment(lib,"libbox2d.lib")
#pragma comment(lib,"libSpine.lib")
#pragma comment(lib,"libsimulator.lib")


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
