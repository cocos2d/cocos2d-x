#include "main.h"
#include "service/PlayerWin.h"
#include <shellapi.h>

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	auto player = player::PlayerWin::getInstance();
	return player->run();
}
