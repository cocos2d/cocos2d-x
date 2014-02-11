/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "SimulatorWindow.h"

#include "cocos2d.h"
#include "glfw3native.h"
#include "resource.h"
#include "Runtime.h"

#include <string>
#include <vector>
using namespace std;
using namespace cocos2d;


WNDPROC g_oldProc=NULL;
bool g_landscape=false;
CCSize g_screenSize;
GLView* g_eglView=NULL;
INT_PTR CALLBACK AboutDialogCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


void createViewMenu()
{
	HMENU menu = GetMenu(glfwGetWin32Window(g_eglView->getWindow()));
	HMENU viewMenu = GetSubMenu(menu, 1);

	for (int i = SimulatorConfig::getInstance()->getScreenSizeCount() - 1; i >= 0; --i)
	{
		SimulatorScreenSize size = SimulatorConfig::getInstance()->getScreenSize(i);
		wstring menuName;
		menuName.assign(size.title.begin(), size.title.end());

		MENUITEMINFO item;
		ZeroMemory(&item, sizeof(item));
		item.cbSize = sizeof(item);
		item.fMask = MIIM_FTYPE | MIIM_ID | MIIM_STRING;
		item.fType = MFT_STRING;
		item.wID = ID_VIEW_SIZE + i;
		item.dwTypeData = (LPTSTR)menuName.c_str();
		item.cch = menuName.length();

		InsertMenuItem(viewMenu, 0, TRUE, &item);
	}
}

void updateMenu()
{
	HMENU menu = GetMenu(glfwGetWin32Window(g_eglView->getWindow()));
	HMENU viewMenu = GetSubMenu(menu, 1);

	if (g_landscape)
	{
		CheckMenuItem(viewMenu, ID_VIEW_PORTRAIT, MF_BYCOMMAND | MF_UNCHECKED);
		CheckMenuItem(viewMenu, ID_VIEW_LANDSCAPE, MF_BYCOMMAND | MF_CHECKED);
	}
	else
	{
		CheckMenuItem(viewMenu, ID_VIEW_PORTRAIT, MF_BYCOMMAND | MF_CHECKED);
		CheckMenuItem(viewMenu, ID_VIEW_LANDSCAPE, MF_BYCOMMAND | MF_UNCHECKED);
	}

	int width = g_screenSize.width;
	int height = g_screenSize.height;
	if (height > width)
	{
		int w = width;
		width = height;
		height = w;
	}

	int count = SimulatorConfig::getInstance()->getScreenSizeCount();
	for (int i = 0; i < count; ++i)
	{
		bool bSel = false;

		SimulatorScreenSize size = SimulatorConfig::getInstance()->getScreenSize(i);
		if (size.width == width && size.height == height)
		{
			bSel = true;
		}
		CheckMenuItem(viewMenu, i, MF_BYPOSITION | (bSel? MF_CHECKED : MF_UNCHECKED));
	}
}

/*@brief updateView*/
void updateView()
{
	if (g_landscape)
	{
		glfwSetWindowSize(g_eglView->getWindow(),g_screenSize.width,g_screenSize.height);
	}
	else
	{
		glfwSetWindowSize(g_eglView->getWindow(),g_screenSize.height,g_screenSize.width);
	}
	updateMenu();
}

void onViewChangeOrientation(int viewMenuID)
{
	if (viewMenuID == ID_VIEW_PORTRAIT && g_landscape)
	{
		g_landscape = false;
		updateView();
	}
	else if (viewMenuID == ID_VIEW_LANDSCAPE && !g_landscape)
	{
		g_landscape = true;
		updateView();
	}
}

void onViewChangeFrameSize(int viewMenuID)
{
	int index = viewMenuID - ID_VIEW_SIZE;
	if (index >= 0 && index < SimulatorConfig::getInstance()->getScreenSizeCount())
	{
		SimulatorScreenSize size = SimulatorConfig::getInstance()->getScreenSize(index);
		g_screenSize.width = size.width;
		g_screenSize.height = size.height;
		updateView();	
	}
}

void onHelpAbout()
{
	DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ABOUT), glfwGetWin32Window(g_eglView->getWindow()), AboutDialogCallback);
}

/*@brief new windows process*/
LRESULT CALLBACK SNewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	switch (message)
	{
	case WM_COMMAND:
		{
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);

			switch (wmId)
			{
			case ID_FILE_EXIT:
				exit(0);
				break;

			case ID_VIEW_PORTRAIT:
			case ID_VIEW_LANDSCAPE:
				onViewChangeOrientation(wmId);
				break;

			case ID_CONTROL_RELOAD:
				ReloadScript();
				break;

			case ID_HELP_ABOUT:
				onHelpAbout();

			default:
				if (wmId >= ID_VIEW_SIZE && wmId <= ID_VIEW_SIZE + SimulatorConfig::getInstance()->getScreenSizeCount() - 1)
				{
					onViewChangeFrameSize(wmId);
					break;
				}
				return 0;
			}
		}
		break;
	}
	return g_oldProc(hWnd, message, wParam, lParam);
}

/*@brief AboutDialog Callback*/
INT_PTR CALLBACK AboutDialogCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void createSimulator(const char* viewName, float width, float height, float frameZoomFactor)
{
	if (g_eglView)
	{
		return;
	}

	g_eglView = GLView::createWithRect(viewName,Rect(0,0,width,height),frameZoomFactor);
	auto director = Director::getInstance();
	director->setOpenGLView(g_eglView);
	g_landscape = false;
	g_screenSize.width = width;
	g_screenSize.height = height;
	if (width  > height)
	{
		g_landscape = true;
	}

	HWND hWnd=glfwGetWin32Window(g_eglView->getWindow());
	HMENU hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU_COCOS));
	SetMenu(hWnd, hMenu);
	createViewMenu();
	updateMenu();

	g_oldProc = (WNDPROC)SetWindowLong(hWnd, GWL_WNDPROC, (LONG)SNewWndProc); 
	if (g_oldProc==0) 
	{
		printf("SetWindowLong NewWndProc Error:%d\n",GetLastError()); 
	}

}