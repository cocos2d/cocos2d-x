
#include "SimulatorConfig.h"
#include "RuntimeConfig.h"

#include "glfw3native.h"
#include "resource.h"

class  ScriptingCore;

WNDPROC g_pOldProc; 
LRESULT CALLBACK SNewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SimulatorConfig *pSimulator=SimulatorConfig::getInstance();
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
				printf("TRESET");
				break;

			case ID_VIEW_PORTRAIT:
			case ID_VIEW_LANDSCAPE:
				pSimulator->onViewChangeOrientation(wmId);
				break;
			case ID_HELP_ABOUT:
				pSimulator->onHelpAbout();
			default:
				if (wmId >= ID_VIEW_SIZE && wmId <= ID_VIEW_SIZE + SimulatorConfig::getInstance()->getScreenSizeCount() - 1)
				{
					pSimulator->onViewChangeFrameSize(wmId);
					break;
				}
				return 0;
			}
		}
		break;
	}
	return g_pOldProc(hWnd, message, wParam, lParam);
}

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
void SimulatorConfig::onHelpAbout()
{
	DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ABOUT), m_hWnd, AboutDialogCallback);
}

SimulatorConfig *SimulatorConfig::s_sharedInstance = NULL;
SimulatorConfig *SimulatorConfig::getInstance()
{
	if (!s_sharedInstance)
	{		
		s_sharedInstance = new SimulatorConfig();
	}
	return s_sharedInstance;
}

void SimulatorConfig::createSimulator(const char* viewName, float width, float height)
{
	m_screenSize.width = width;
	m_screenSize.height = height;
	m_eglView.init(viewName,width,height);
	m_hWnd=glfwGetWin32Window(m_eglView.getWindow());
	HMENU hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU_COCOS));
	SetMenu(m_hWnd, hMenu);
	createViewMenu();
	updateMenu();

	g_pOldProc = (WNDPROC)SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)SNewWndProc); 
	if (g_pOldProc==0) 
	{
		printf("SetWindowLong NewWndProc Error:%d\n",GetLastError()); 
	}
	
}
SimulatorConfig::SimulatorConfig()
{
	isLandscape = true;
	m_screenSizeArray.push_back(SimulatorScreenSize("iPhone 3Gs (480x320)", 480, 320));
	m_screenSizeArray.push_back(SimulatorScreenSize("iPhone 4 (960x640)", 960, 640));
	m_screenSizeArray.push_back(SimulatorScreenSize("iPhone 5 (1136x640)", 1136, 640));
	m_screenSizeArray.push_back(SimulatorScreenSize("iPad (1024x768)", 1024, 768));
	m_screenSizeArray.push_back(SimulatorScreenSize("iPad Retina (2048x1536)", 2048, 1536));
	m_screenSizeArray.push_back(SimulatorScreenSize("Android (800x480)", 800, 480));
	m_screenSizeArray.push_back(SimulatorScreenSize("Android (854x480)", 854, 480));
	m_screenSizeArray.push_back(SimulatorScreenSize("Android (960x540)", 960, 540));
	m_screenSizeArray.push_back(SimulatorScreenSize("Android (1024x600)", 1024, 600));
	m_screenSizeArray.push_back(SimulatorScreenSize("Android (1280x720)", 1280, 720));
	m_screenSizeArray.push_back(SimulatorScreenSize("Android (1280x800)", 1280, 800));
	m_screenSizeArray.push_back(SimulatorScreenSize("Android (1920x1080)", 1920, 1080));
}

void SimulatorConfig::createViewMenu()
{
	HMENU menu = GetMenu(m_hWnd);
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

void SimulatorConfig::updateMenu()
{
	HMENU menu = GetMenu(m_hWnd);
	HMENU viewMenu = GetSubMenu(menu, 1);

	if (isLandscape)
	{
		CheckMenuItem(viewMenu, ID_VIEW_PORTRAIT, MF_BYCOMMAND | MF_UNCHECKED);
		CheckMenuItem(viewMenu, ID_VIEW_LANDSCAPE, MF_BYCOMMAND | MF_CHECKED);
	}
	else
	{
		CheckMenuItem(viewMenu, ID_VIEW_PORTRAIT, MF_BYCOMMAND | MF_CHECKED);
		CheckMenuItem(viewMenu, ID_VIEW_LANDSCAPE, MF_BYCOMMAND | MF_UNCHECKED);
	}

	int current = SimulatorConfig::getInstance()->checkScreenSize();
	for (int i = SimulatorConfig::getInstance()->getScreenSizeCount() - 1; i >= 0; --i)
	{
		CheckMenuItem(viewMenu, i, MF_BYPOSITION | (i == current ? MF_CHECKED : MF_UNCHECKED));
	}
}

int SimulatorConfig::getScreenSizeCount(void)
{
	return (int)m_screenSizeArray.size();
}

const SimulatorScreenSize SimulatorConfig::getScreenSize(int index)
{
	return m_screenSizeArray.at(index);
}

int SimulatorConfig::checkScreenSize()
{
	int width = m_screenSize.width;
	int height = m_screenSize.height;

	if (height > width)
	{
		int w = width;
		width = height;
		height = w;
	}

	int count = (int)m_screenSizeArray.size();
	for (int i = 0; i < count; ++i)
	{
		const SimulatorScreenSize &size = m_screenSizeArray[i];
		if (size.width == width && size.height == height)
		{
			return i;
		}
	}

	return -1;
}
void SimulatorConfig::updateView()
{
	if (isLandscape)
	{
		glfwSetWindowSize(m_eglView.getWindow(),m_screenSize.width,m_screenSize.height);
	}
	else
	{
		glfwSetWindowSize(m_eglView.getWindow(),m_screenSize.height,m_screenSize.width);
	}
	updateMenu();
	RuntimeConfig::getInstance()->resetRuntime();
}
void SimulatorConfig::onViewChangeOrientation(int viewMenuID)
{
	if (viewMenuID == ID_VIEW_PORTRAIT && isLandscape)
	{
		isLandscape = false;
		updateView();
	}
	else if (viewMenuID == ID_VIEW_LANDSCAPE && !isLandscape)
	{
		isLandscape = true;
		glfwSetWindowSize(m_eglView.getWindow(),m_screenSize.width,m_screenSize.height);
		updateView();
	}
}
void SimulatorConfig::onViewChangeFrameSize(int viewMenuID)
{
	int index = viewMenuID - ID_VIEW_SIZE;

	if (index >= 0 && index < SimulatorConfig::getInstance()->getScreenSizeCount())
	{
		SimulatorScreenSize size = SimulatorConfig::getInstance()->getScreenSize(index);
		m_screenSize.width = size.width;
		m_screenSize.height = size.height;
		updateView();	
	}
}
