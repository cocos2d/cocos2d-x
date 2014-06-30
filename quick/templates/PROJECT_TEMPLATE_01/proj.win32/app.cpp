
#pragma comment(lib, "comctl32.lib")
#pragma comment(linker, "\"/manifestdependency:type='Win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='X86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "stdafx.h"
#include "app.h"
#include <io.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#include <Commdlg.h>
#include <Shlobj.h>
#include <winnls.h>
#include <shobjidl.h>
#include <objbase.h>
#include <objidl.h>
#include <shlguid.h>
#include <shellapi.h>

#include <vector>

#include "CCEGLView.h"
#include "CCLuaEngine.h"
#include "CCLuaStack.h"
#include "SimpleAudioEngine.h"


int APIENTRY _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    return App::createAndRun();
}

int App::createAndRun(void)
{
    App *host = App::sharedInstance();
    int ret = host->run();
    App::purgeSharedInstance();
    return ret;
}

App *App::s_sharedInstance = NULL;

App *App::sharedInstance(void)
{
    if (!s_sharedInstance)
    {
        s_sharedInstance = new App();
    }
    return s_sharedInstance;
}

void App::purgeSharedInstance(void)
{
    if (s_sharedInstance)
    {
        delete s_sharedInstance;
        s_sharedInstance = NULL;
    }
}

App::App(void)
: m_app(NULL)
, m_hwnd(NULL)
, m_exit(TRUE)
, m_writeDebugLogFile(NULL)
{
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);
}

int App::run(void)
{
    const char *QUICK_COCOS2DX_ROOT = getenv("QUICK_COCOS2DX_ROOT");
    SimulatorConfig::sharedDefaults()->setQuickCocos2dxRootPath(QUICK_COCOS2DX_ROOT);

    loadProjectConfig();

    HWND hwndConsole = NULL;
    if (m_project.isShowConsole())
    {
        AllocConsole();
        freopen("CONOUT$", "wt", stdout);
        freopen("CONOUT$", "wt", stderr);

        // disable close console
        hwndConsole = GetConsoleWindow();
        if (hwndConsole != NULL)
        {
            HMENU hMenu = GetSystemMenu(hwndConsole, FALSE);
            if (hMenu != NULL) DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);

            ShowWindow(hwndConsole, SW_SHOW);
            BringWindowToTop(hwndConsole);
        }
    }

    m_project.dump();

    if (m_project.isWriteDebugLogToFile())
    {
        const string debugLogFilePath = m_project.getDebugLogFilePath();
        m_writeDebugLogFile = fopen(debugLogFilePath.c_str(), "w");
        if (!m_writeDebugLogFile)
        {
            CCLOG("Cannot create debug log file %s", debugLogFilePath.c_str());
        }
    }

    do
    {
        m_exit = TRUE;

        // create the application instance
        m_app = new AppDelegate();
        m_app->setProjectConfig(m_project);

        // set environments
        SetCurrentDirectoryA(m_project.getProjectDir().c_str());
        CCFileUtils::sharedFileUtils()->setSearchRootPath(m_project.getProjectDir().c_str());
        CCFileUtils::sharedFileUtils()->setWritablePath(m_project.getWritableRealPath().c_str());

        // create opengl view
        CCEGLView* eglView = CCEGLView::sharedOpenGLView();
        eglView->setMenuResource(MAKEINTRESOURCE(IDC_LUAHOSTWIN32));
        eglView->setWndProc(WindowProc);
        eglView->setFrameSize(m_project.getFrameSize().width, m_project.getFrameSize().height);
        eglView->setFrameZoomFactor(m_project.getFrameScale());

        // make window actived
        m_hwnd = eglView->getHWnd();
        BringWindowToTop(m_hwnd);
        SetWindowTextA(m_hwnd, "__PROJECT_PACKAGE_LAST_NAME_L__");

        // restore window position
        const CCPoint windowOffset = m_project.getWindowOffset();
        if (windowOffset.x != 0 || windowOffset.y != 0)
        {
            eglView->moveWindow(windowOffset.x, windowOffset.y);
        }

        // set icon
        HICON icon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_LUAHOSTWIN32));
        SendMessage(m_hwnd, WM_SETICON, ICON_BIG, (LPARAM)icon);

        if (hwndConsole)
        {
            SendMessage(hwndConsole, WM_SETICON, ICON_BIG, (LPARAM)icon);
        }

        // update menu
        createViewMenu();
        updateMenu();

        // run game
        CCLuaStack *stack = CCLuaEngine::defaultEngine()->getLuaStack();
        const vector<string> arr = m_project.getPackagePathArray();
        for (vector<string>::const_iterator it = arr.begin(); it != arr.end(); ++it)
        {
            stack->addSearchPath(it->c_str());
        }

        m_app->run();

        // cleanup
        CCScriptEngineManager::sharedManager()->removeScriptEngine();
        CCScriptEngineManager::purgeSharedManager();
        CocosDenshion::SimpleAudioEngine::end();

        delete m_app;
        m_app = NULL;
    } while (!m_exit);

    FreeConsole();
    if (m_writeDebugLogFile) fclose(m_writeDebugLogFile);
    return 0;
}

void App::loadProjectConfig(void)
{
    vector<string> args;
    for (int i = 0; i < __argc; ++i)
    {
        wstring ws(__wargv[i]);
        string s;
        s.assign(ws.begin(), ws.end());
        args.push_back(s);
    }
    m_project.parseCommandLine(args);
}

void App::createViewMenu(void)
{
    HMENU menu = GetMenu(m_hwnd);
    HMENU viewMenu = GetSubMenu(menu, 1);

    for (int i = SimulatorConfig::sharedDefaults()->getScreenSizeCount() - 1; i >= 0; --i)
    {
        SimulatorScreenSize size = SimulatorConfig::sharedDefaults()->getScreenSize(i);
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

void App::updateMenu(void)
{
    HMENU menu = GetMenu(m_hwnd);
    HMENU viewMenu = GetSubMenu(menu, 1);

    if (m_project.isLandscapeFrame())
    {
        CheckMenuItem(viewMenu, ID_VIEW_PORTRAIT, MF_BYCOMMAND | MF_UNCHECKED);
        CheckMenuItem(viewMenu, ID_VIEW_LANDSCAPE, MF_BYCOMMAND | MF_CHECKED);
    }
    else
    {
        CheckMenuItem(viewMenu, ID_VIEW_PORTRAIT, MF_BYCOMMAND | MF_CHECKED);
        CheckMenuItem(viewMenu, ID_VIEW_LANDSCAPE, MF_BYCOMMAND | MF_UNCHECKED);
    }

    if (m_project.getFrameScale() < 1.0f)
    {
        CheckMenuItem(viewMenu, ID_VIEW_RESET_ZOOM, MF_BYCOMMAND | MF_UNCHECKED);
        CheckMenuItem(viewMenu, ID_VIEW_ZOOM_OUT, MF_BYCOMMAND | MF_CHECKED);
    }
    else
    {
        CheckMenuItem(viewMenu, ID_VIEW_RESET_ZOOM, MF_BYCOMMAND | MF_CHECKED);
        CheckMenuItem(viewMenu, ID_VIEW_ZOOM_OUT, MF_BYCOMMAND | MF_UNCHECKED);
    }

    int current = SimulatorConfig::sharedDefaults()->checkScreenSize(m_project.getFrameSize());
    for (int i = SimulatorConfig::sharedDefaults()->getScreenSizeCount() - 1; i >= 0; --i)
    {
        CheckMenuItem(viewMenu, i, MF_BYPOSITION | (i == current ? MF_CHECKED : MF_UNCHECKED));
    }
}

void App::relaunch(void)
{
    string commandLine = m_project.makeCommandLine(kProjectConfigAll);
    TCHAR moduleName[MAX_PATH];
    ZeroMemory(moduleName, sizeof(moduleName));
    GetModuleFileName(NULL, moduleName, MAX_PATH);

    wstring ws;
    ws.append(L"\"");
    ws.append(moduleName);
    ws.append(L"\" ");
    ws.append(commandLine.begin(), commandLine.end());

    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};
    lstrcpyW(moduleName, ws.c_str());
    if (CreateProcess(NULL, moduleName, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi))
    {
        ExitProcess(0);
    }
}

void App::writeDebugLog(const char *log)
{
    if (!m_writeDebugLogFile) return;

    fputs(log, m_writeDebugLogFile);
    fputc('\n', m_writeDebugLogFile);
    fflush(m_writeDebugLogFile);
}

// menu callback

void App::onFileRelaunch(void)
{
    relaunch();
}

void App::onFileExit(void)
{
    DestroyWindow(m_hwnd);
}

void App::onViewChangeFrameSize(int viewMenuID)
{
    int index = viewMenuID - ID_VIEW_SIZE;

    if (index >= 0 && index < SimulatorConfig::sharedDefaults()->getScreenSizeCount())
    {
        SimulatorScreenSize size = SimulatorConfig::sharedDefaults()->getScreenSize(index);
        bool isLandscape = m_project.isLandscapeFrame();
        m_project.setFrameSize(CCSize(size.width, size.height));
        if (isLandscape)
        {
            m_project.changeFrameOrientationToLandscape();
        }
        else
        {
            m_project.changeFrameOrientationToPortait();
        }
        m_project.setFrameScale(1.0f);
        relaunch();
    }
}

void App::onViewChangeOrientation(int viewMenuID)
{
    bool isLandscape = m_project.isLandscapeFrame();
    bool isNeedRelaunch = false;
    if (viewMenuID == ID_VIEW_PORTRAIT && isLandscape)
    {
        m_project.changeFrameOrientationToPortait();
        isNeedRelaunch = true;
    }
    else if (viewMenuID == ID_VIEW_LANDSCAPE && !isLandscape)
    {
        m_project.changeFrameOrientationToLandscape();
        isNeedRelaunch = true;
    }

    if (isNeedRelaunch) relaunch();
}

void App::onViewChangeZoom(int scaleMode)
{
    float scale = 1.0f;
    if (scaleMode == ID_VIEW_ZOOM_OUT)
    {
        scale = 0.5f;
    }

    m_project.setFrameScale(scale);
    CCEGLView::sharedOpenGLView()->setFrameZoomFactor(scale);
    CCEGLView::sharedOpenGLView()->resize(m_project.getFrameSize().width * scale,
        m_project.getFrameSize().height * scale);
    updateMenu();
}

// windows callback
LRESULT App::WindowProc(UINT message, WPARAM wParam, LPARAM lParam, BOOL* pProcessed)
{
    int wmId, wmEvent;
    App *host = App::sharedInstance();
    HWND hwnd = host->getWindowHandle();

    switch (message)
    {
    case WM_COMMAND:
        wmId    = LOWORD(wParam);
        wmEvent = HIWORD(wParam);

        switch (wmId)
        {
        case ID_FILE_RELAUNCH:
            host->onFileRelaunch();
            break;

        case ID_FILE_EXIT:
            host->onFileExit();
            break;

        case ID_VIEW_PORTRAIT:
        case ID_VIEW_LANDSCAPE:
            host->onViewChangeOrientation(wmId);
            break;

        case ID_VIEW_RESET_ZOOM:
        case ID_VIEW_ZOOM_OUT:
            host->onViewChangeZoom(wmId);
            break;

        default:
            if (wmId >= ID_VIEW_SIZE && wmId <= ID_VIEW_SIZE + SimulatorConfig::sharedDefaults()->getScreenSizeCount() - 1)
            {
                host->onViewChangeFrameSize(wmId);
                break;
            }

            return 0;
        }
        break;

    case WM_KEYDOWN:
        if (wParam == VK_F5)
        {
            host->onFileRelaunch();
        }
        break;

    case WM_COPYDATA:
        {
            PCOPYDATASTRUCT pMyCDS = (PCOPYDATASTRUCT) lParam;
            if (pMyCDS->dwData == CCLOG_STRING)
            {
                const char *szBuf = (const char*)(pMyCDS->lpData);
                sharedInstance()->writeDebugLog(szBuf);
                break;
            }
        }

    default:
        return 0;
    }

    *pProcessed = TRUE;
    return 0;
}
