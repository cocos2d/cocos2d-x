
#pragma comment(lib, "comctl32.lib")
#pragma comment(linker, "\"/manifestdependency:type='Win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='X86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "stdafx.h"
#include <io.h>
#include <stdlib.h>
#include <malloc.h>
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

#include "SimulatorWin.h"

#include "glfw3.h"
#include "glfw3native.h"

#include "CCLuaEngine.h"
#include "AppEvent.h"
#include "AppLang.h"
#include "runtime/ConfigParser.h"
#include "runtime/Runtime.h"

#include "platform/win32/PlayerWin.h"
#include "platform/win32/PlayerMenuServiceWin.h"

// define 1 to open console ui and setup windows system menu, 0 to disable
#include "ide-support/CodeIDESupport.h"
#if (CC_CODE_IDE_DEBUG_SUPPORT > 0)
#define SIMULATOR_WITH_CONSOLE_AND_MENU 1
#else
#define SIMULATOR_WITH_CONSOLE_AND_MENU 0
#endif

USING_NS_CC;

static WNDPROC g_oldWindowProc = NULL;
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
void onHelpAbout()
{
    DialogBox(GetModuleHandle(NULL),
        MAKEINTRESOURCE(IDD_DIALOG_ABOUT),
        Director::getInstance()->getOpenGLView()->getWin32Window(),
        AboutDialogCallback);
}

void shutDownApp()
{
    auto glview = dynamic_cast<GLViewImpl*> (Director::getInstance()->getOpenGLView());
    HWND hWnd = glview->getWin32Window();
    ::SendMessage(hWnd, WM_CLOSE, NULL, NULL);
}

std::string getCurAppPath(void)
{
    TCHAR szAppDir[MAX_PATH] = { 0 };
    if (!GetModuleFileName(NULL, szAppDir, MAX_PATH))
        return "";
    int nEnd = 0;
    for (int i = 0; szAppDir[i]; i++)
    {
        if (szAppDir[i] == '\\')
            nEnd = i;
    }
    szAppDir[nEnd] = 0;
    int iLen = 2 * wcslen(szAppDir);
    char* chRtn = new char[iLen + 1];
    wcstombs(chRtn, szAppDir, iLen + 1);
    std::string strPath = chRtn;
    delete[] chRtn;
    chRtn = NULL;
    char fuldir[MAX_PATH] = { 0 };
    _fullpath(fuldir, strPath.c_str(), MAX_PATH);
    return fuldir;
}

static void initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

SimulatorWin *SimulatorWin::_instance = nullptr;

SimulatorWin *SimulatorWin::getInstance()
{
    if (!_instance)
    {
        _instance = new SimulatorWin();
    }
    return _instance;
}

SimulatorWin::SimulatorWin()
    : _app(nullptr)
    , _hwnd(NULL)
    , _hwndConsole(NULL)
    , _writeDebugLogFile(nullptr)
{
}

SimulatorWin::~SimulatorWin()
{
    CC_SAFE_DELETE(_app);
    if (_writeDebugLogFile)
    {
        fclose(_writeDebugLogFile);
    }
}

void SimulatorWin::quit()
{
    Director::getInstance()->end();
}

void SimulatorWin::relaunch()
{
    _project.setWindowOffset(Vec2(getPositionX(), getPositionY()));
    openNewPlayerWithProjectConfig(_project);

    quit();
}

void SimulatorWin::openNewPlayer()
{
    openNewPlayerWithProjectConfig(_project);
}

void SimulatorWin::openNewPlayerWithProjectConfig(const ProjectConfig &config)
{
    static long taskid = 100;
    stringstream buf;
    buf << taskid++;

    string commandLine;
    commandLine.append(getApplicationExePath());
    commandLine.append(" ");
    commandLine.append(config.makeCommandLine());

    CCLOG("SimulatorWin::openNewPlayerWithProjectConfig(): %s", commandLine.c_str());

    // http://msdn.microsoft.com/en-us/library/windows/desktop/ms682499(v=vs.85).aspx
    SECURITY_ATTRIBUTES sa = {0};
    sa.nLength = sizeof(sa);

    PROCESS_INFORMATION pi = {0};
    STARTUPINFO si = {0};
    si.cb = sizeof(STARTUPINFO);

#define MAX_COMMAND 1024 // lenth of commandLine is always beyond MAX_PATH

    WCHAR command[MAX_COMMAND];
    memset(command, 0, sizeof(command));
    MultiByteToWideChar(CP_UTF8, 0, commandLine.c_str(), -1, command, MAX_COMMAND);

    BOOL success = CreateProcess(NULL,
                                 command,   // command line
                                 NULL,      // process security attributes
                                 NULL,      // primary thread security attributes
                                 FALSE,     // handles are inherited
                                 0,         // creation flags
                                 NULL,      // use parent's environment
                                 NULL,      // use parent's current directory
                                 &si,       // STARTUPINFO pointer
                                 &pi);      // receives PROCESS_INFORMATION

    if (!success)
    {
        CCLOG("PlayerTaskWin::run() - create process failed, for execute %s", commandLine.c_str());
    }
}

void SimulatorWin::openProjectWithProjectConfig(const ProjectConfig &config)
{
    openNewPlayerWithProjectConfig(config);
    quit();
}

int SimulatorWin::getPositionX()
{
    RECT rect;
    GetWindowRect(_hwnd, &rect);
    return rect.left;
}

int SimulatorWin::getPositionY()
{
    RECT rect;
    GetWindowRect(_hwnd, &rect);
    return rect.top;
}

int SimulatorWin::run()
{
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    parseCocosProjectConfig(_project);

    // load project config from command line args
    vector<string> args;
    for (int i = 0; i < __argc; ++i)
    {
        wstring ws(__wargv[i]);
        string s;
        s.assign(ws.begin(), ws.end());
        args.push_back(s);
    }
    _project.parseCommandLine(args);

    if (_project.getProjectDir().empty())
    {
        if (args.size() == 2)
        {
            // for Code IDE before RC2
            _project.setProjectDir(args.at(1));
            _project.setDebuggerType(kCCRuntimeDebuggerCodeIDE);
        }
    }

    // create the application instance
    _app = new AppDelegate();
    RuntimeEngine::getInstance()->setProjectConfig(_project);

#if (SIMULATOR_WITH_CONSOLE_AND_MENU > 0)
    // create console window
    if (_project.isShowConsole())
    {
        AllocConsole();
        _hwndConsole = GetConsoleWindow();
        if (_hwndConsole != NULL)
        {
            ShowWindow(_hwndConsole, SW_SHOW);
            BringWindowToTop(_hwndConsole);
            freopen("CONOUT$", "wt", stdout);
            freopen("CONOUT$", "wt", stderr);

            HMENU hmenu = GetSystemMenu(_hwndConsole, FALSE);
            if (hmenu != NULL)
            {
                DeleteMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);
            }
        }
    }
#endif

    // log file
    if (_project.isWriteDebugLogToFile())
    {
        const string debugLogFilePath = _project.getDebugLogFilePath();
        _writeDebugLogFile = fopen(debugLogFilePath.c_str(), "w");
        if (!_writeDebugLogFile)
        {
            CCLOG("Cannot create debug log file %s", debugLogFilePath.c_str());
        }
    }

    // set environments
    SetCurrentDirectoryA(_project.getProjectDir().c_str());
    FileUtils::getInstance()->setDefaultResourceRootPath(_project.getProjectDir());
    FileUtils::getInstance()->setWritablePath(_project.getWritableRealPath().c_str());

    // check screen DPI
    HDC screen = GetDC(0);
    int dpi = GetDeviceCaps(screen, LOGPIXELSX);
    ReleaseDC(0, screen);

    // set scale with DPI
    //  96 DPI = 100 % scaling
    // 120 DPI = 125 % scaling
    // 144 DPI = 150 % scaling
    // 192 DPI = 200 % scaling
    // http://msdn.microsoft.com/en-us/library/windows/desktop/dn469266%28v=vs.85%29.aspx#dpi_and_the_desktop_scaling_factor
    //
    // enable DPI-Aware with DeclareDPIAware.manifest
    // http://msdn.microsoft.com/en-us/library/windows/desktop/dn469266%28v=vs.85%29.aspx#declaring_dpi_awareness
    float screenScale = 1.0f;
    if (dpi >= 120 && dpi < 144)
    {
        screenScale = 1.25f;
    }
    else if (dpi >= 144 && dpi < 192)
    {
        screenScale = 1.5f;
    }
    else if (dpi >= 192)
    {
        screenScale = 2.0f;
    }
    CCLOG("SCREEN DPI = %d, SCREEN SCALE = %0.2f", dpi, screenScale);

    // create opengl view
    Size frameSize = _project.getFrameSize();
    float frameScale = 1.0f;
    if (_project.isRetinaDisplay())
    {
        frameSize.width *= screenScale;
        frameSize.height *= screenScale;
    }
    else
    {
        frameScale = screenScale;
    }

    const Rect frameRect = Rect(0, 0, frameSize.width, frameSize.height);
    ConfigParser::getInstance()->setInitViewSize(frameSize);
    const bool isResize = _project.isResizeWindow();
    std::stringstream title;
    title << "Cocos Simulator - " << ConfigParser::getInstance()->getInitViewName();
    initGLContextAttrs();
    auto glview = GLViewImpl::createWithRect(title.str(), frameRect, frameScale);
    _hwnd = glview->getWin32Window();
    player::PlayerWin::createWithHwnd(_hwnd);
    DragAcceptFiles(_hwnd, TRUE);
    //SendMessage(_hwnd, WM_SETICON, ICON_BIG, (LPARAM)icon);
    //SendMessage(_hwnd, WM_SETICON, ICON_SMALL, (LPARAM)icon);
    //FreeResource(icon);

    auto director = Director::getInstance();
    director->setOpenGLView(glview);

    director->setAnimationInterval(1.0 / 60.0);

    // set window position
    if (_project.getProjectDir().length())
    {
        setZoom(_project.getFrameScale());
    }
    Vec2 pos = _project.getWindowOffset();
    if (pos.x != 0 && pos.y != 0)
    {
        RECT rect;
        GetWindowRect(_hwnd, &rect);
        MoveWindow(_hwnd, pos.x, pos.y, rect.right - rect.left, rect.bottom - rect.top, FALSE);
    }

    // path for looking Lang file, Studio Default images
    FileUtils::getInstance()->addSearchPath(getApplicationPath().c_str());

#if SIMULATOR_WITH_CONSOLE_AND_MENU > 0
    // init player services
    setupUI();
    DrawMenuBar(_hwnd);
#endif

    // prepare
    FileUtils::getInstance()->setPopupNotify(false);
    _project.dump();
    auto app = Application::getInstance();

    g_oldWindowProc = (WNDPROC)SetWindowLong(_hwnd, GWL_WNDPROC, (LONG)SimulatorWin::windowProc);

    // startup message loop
    return app->run();
}

// services

void SimulatorWin::setupUI()
{
    auto menuBar = player::PlayerProtocol::getInstance()->getMenuService();

    // FILE
    menuBar->addItem("FILE_MENU", tr("File"));
    menuBar->addItem("EXIT_MENU", tr("Exit"), "FILE_MENU");

    // VIEW
    menuBar->addItem("VIEW_MENU", tr("View"));
    SimulatorConfig *config = SimulatorConfig::getInstance();
    int current = config->checkScreenSize(_project.getFrameSize());
    for (int i = 0; i < config->getScreenSizeCount(); i++)
    {
        SimulatorScreenSize size = config->getScreenSize(i);
        std::stringstream menuId;
        menuId << "VIEWSIZE_ITEM_MENU_" << i;
        auto menuItem = menuBar->addItem(menuId.str(), size.title.c_str(), "VIEW_MENU");

        if (i == current)
        {
            menuItem->setChecked(true);
        }
    }

    menuBar->addItem("DIRECTION_MENU_SEP", "-", "VIEW_MENU");
    menuBar->addItem("DIRECTION_PORTRAIT_MENU", tr("Portrait"), "VIEW_MENU")
        ->setChecked(_project.isPortraitFrame());
    menuBar->addItem("DIRECTION_LANDSCAPE_MENU", tr("Landscape"), "VIEW_MENU")
        ->setChecked(_project.isLandscapeFrame());

    menuBar->addItem("VIEW_SCALE_MENU_SEP", "-", "VIEW_MENU");
    std::vector<player::PlayerMenuItem*> scaleMenuVector;
    auto scale100Menu = menuBar->addItem("VIEW_SCALE_MENU_100", tr("Zoom Out").append(" (100%)"), "VIEW_MENU");
    auto scale75Menu = menuBar->addItem("VIEW_SCALE_MENU_75", tr("Zoom Out").append(" (75%)"), "VIEW_MENU");
    auto scale50Menu = menuBar->addItem("VIEW_SCALE_MENU_50", tr("Zoom Out").append(" (50%)"), "VIEW_MENU");
    auto scale25Menu = menuBar->addItem("VIEW_SCALE_MENU_25", tr("Zoom Out").append(" (25%)"), "VIEW_MENU");
    int frameScale = int(_project.getFrameScale() * 100);
    if (frameScale == 100)
    {
        scale100Menu->setChecked(true);
    }
    else if (frameScale == 75)
    {
        scale75Menu->setChecked(true);
    }
    else if (frameScale == 50)
    {
        scale50Menu->setChecked(true);
    }
    else if (frameScale == 25)
    {
        scale25Menu->setChecked(true);
    }
    else
    {
        scale100Menu->setChecked(true);
    }

    scaleMenuVector.push_back(scale100Menu);
    scaleMenuVector.push_back(scale75Menu);
    scaleMenuVector.push_back(scale50Menu);
    scaleMenuVector.push_back(scale25Menu);

    // About
    menuBar->addItem("HELP_MENU", tr("Help"));
    menuBar->addItem("ABOUT_MENUITEM", tr("About"), "HELP_MENU");

    menuBar->addItem("REFRESH_MENU_SEP", "-", "VIEW_MENU");
    menuBar->addItem("REFRESH_MENU", tr("Refresh"), "VIEW_MENU");

    HWND &hwnd = _hwnd;
    ProjectConfig &project = _project;
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithFixedPriority(EventListenerCustom::create("APP.EVENT", [&project, &hwnd, scaleMenuVector](EventCustom* event){
        auto menuEvent = dynamic_cast<AppEvent*>(event);
        if (menuEvent)
        {
            rapidjson::Document dArgParse;
            dArgParse.Parse<0>(menuEvent->getDataString().c_str());
            if (dArgParse.HasMember("name"))
            {
                string strcmd = dArgParse["name"].GetString();

                if (strcmd == "menuClicked")
                {
                    player::PlayerMenuItem *menuItem = static_cast<player::PlayerMenuItem*>(menuEvent->getUserData());
                    if (menuItem)
                    {
                        if (menuItem->isChecked())
                        {
                            return;
                        }

                        string data = dArgParse["data"].GetString();

                        if ((data == "CLOSE_MENU") || (data == "EXIT_MENU"))
                        {
                            _instance->quit();
                        }
                        else if (data == "REFRESH_MENU")
                        {
                            _instance->relaunch();
                        }
                        else if (data.find("VIEW_SCALE_MENU_") == 0) // begin with VIEW_SCALE_MENU_
                        {
                            string tmp = data.erase(0, strlen("VIEW_SCALE_MENU_"));
                            float scale = atof(tmp.c_str()) / 100.0f;
                            project.setFrameScale(scale);

                            auto glview = static_cast<GLViewImpl*>(Director::getInstance()->getOpenGLView());
                            glview->setFrameZoomFactor(scale);

                            // update scale menu state
                            for (auto &it : scaleMenuVector)
                            {
                                it->setChecked(false);
                            }
                            menuItem->setChecked(true);

                            // update window size
                            RECT rect;
                            GetWindowRect(hwnd, &rect);
                            MoveWindow(hwnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top + GetSystemMetrics(SM_CYMENU), FALSE);

                            // fix: can not update window on some windows system
                            ::SendMessage(hwnd, WM_MOVE, NULL, NULL);
                        }
                        else if (data.find("VIEWSIZE_ITEM_MENU_") == 0) // begin with VIEWSIZE_ITEM_MENU_
                        {
                            string tmp = data.erase(0, strlen("VIEWSIZE_ITEM_MENU_"));
                            int index = atoi(tmp.c_str());
                            SimulatorScreenSize size = SimulatorConfig::getInstance()->getScreenSize(index);

                            if (project.isLandscapeFrame())
                            {
                                std::swap(size.width, size.height);
                            }

                            project.setFrameSize(cocos2d::Size(size.width, size.height));
                            project.setWindowOffset(cocos2d::Vec2(_instance->getPositionX(), _instance->getPositionY()));
                            _instance->openProjectWithProjectConfig(project);
                        }
                        else if (data == "DIRECTION_PORTRAIT_MENU")
                        {
                            project.changeFrameOrientationToPortait();
                            _instance->openProjectWithProjectConfig(project);
                        }
                        else if (data == "DIRECTION_LANDSCAPE_MENU")
                        {
                            project.changeFrameOrientationToLandscape();
                            _instance->openProjectWithProjectConfig(project);
                        }
                        else if (data == "ABOUT_MENUITEM")
                        {
                            onHelpAbout();
                        }

                    }
                }
            }
        }
    }), 1);

    AppDelegate *app = _app;
    auto listener = EventListenerCustom::create(kAppEventDropName, [&project, app](EventCustom* event)
    {
        AppEvent *dropEvent = dynamic_cast<AppEvent*>(event);
        if (dropEvent)
        {
            string dirPath = dropEvent->getDataString() + "/";
            string configFilePath = dirPath + CONFIG_FILE;

            if (FileUtils::getInstance()->isDirectoryExist(dirPath) &&
                FileUtils::getInstance()->isFileExist(configFilePath))
            {
                // parse config.json
                ConfigParser::getInstance()->readConfig(configFilePath);

                project.setProjectDir(dirPath);
                project.setScriptFile(ConfigParser::getInstance()->getEntryFile());
                project.setWritablePath(dirPath);

                RuntimeEngine::getInstance()->setProjectConfig(project);
            }
        }
    });
    dispatcher->addEventListenerWithFixedPriority(listener, 1);
}

void SimulatorWin::setZoom(float frameScale)
{
    _project.setFrameScale(frameScale);
    cocos2d::Director::getInstance()->getOpenGLView()->setFrameZoomFactor(frameScale);
}

// debug log
void SimulatorWin::writeDebugLog(const char *log)
{
    if (!_writeDebugLogFile) return;

    fputs(log, _writeDebugLogFile);
    fputc('\n', _writeDebugLogFile);
    fflush(_writeDebugLogFile);
}

void SimulatorWin::parseCocosProjectConfig(ProjectConfig &config)
{
    // get project directory
    ProjectConfig tmpConfig;
    // load project config from command line args
    vector<string> args;
    for (int i = 0; i < __argc; ++i)
    {
        wstring ws(__wargv[i]);
        string s;
        s.assign(ws.begin(), ws.end());
        args.push_back(s);
    }

    if (args.size() >= 2)
    {
        if (args.size() && args.at(1).at(0) == '/')
        {
            // FIXME:
            // for Code IDE before RC2
            tmpConfig.setProjectDir(args.at(1));
        }

        tmpConfig.parseCommandLine(args);
    }

    // set project directory as search root path
    FileUtils::getInstance()->setDefaultResourceRootPath(tmpConfig.getProjectDir().c_str());

    // parse config.json
    auto parser = ConfigParser::getInstance();
    auto configPath = tmpConfig.getProjectDir().append(CONFIG_FILE);
    parser->readConfig(configPath);

    // set information
    config.setConsolePort(parser->getConsolePort());
    config.setFileUploadPort(parser->getUploadPort());
    config.setFrameSize(parser->getInitViewSize());
    if (parser->isLanscape())
    {
        config.changeFrameOrientationToLandscape();
    }
    else
    {
        config.changeFrameOrientationToPortait();
    }
    config.setScriptFile(parser->getEntryFile());
}

//
// D:\aaa\bbb\ccc\ddd\abc.txt --> D:/aaa/bbb/ccc/ddd/abc.txt
//
std::string SimulatorWin::convertPathFormatToUnixStyle(const std::string& path)
{
    std::string ret = path;
    int len = ret.length();
    for (int i = 0; i < len; ++i)
    {
        if (ret[i] == '\\')
        {
            ret[i] = '/';
        }
    }
    return ret;
}

//
// @return: C:/Users/win8/Documents/
//
std::string SimulatorWin::getUserDocumentPath()
{
    TCHAR filePath[MAX_PATH];
    SHGetSpecialFolderPath(NULL, filePath, CSIDL_PERSONAL, FALSE);
    int length = 2 * wcslen(filePath);
    char* tempstring = new char[length + 1];
    wcstombs(tempstring, filePath, length + 1);
    string userDocumentPath(tempstring);
    delete [] tempstring;

    userDocumentPath = convertPathFormatToUnixStyle(userDocumentPath);
    userDocumentPath.append("/");

    return userDocumentPath;
}

//
// convert Unicode/LocalCode TCHAR to Utf8 char
//
char* SimulatorWin::convertTCharToUtf8(const TCHAR* src)
{
#ifdef UNICODE
    WCHAR* tmp = (WCHAR*)src;
    size_t size = wcslen(src) * 3 + 1;
    char* dest = new char[size];
    memset(dest, 0, size);
    WideCharToMultiByte(CP_UTF8, 0, tmp, -1, dest, size, NULL, NULL);
    return dest;
#else
    char* tmp = (char*)src;
    uint32 size = strlen(tmp) + 1;
    WCHAR* dest = new WCHAR[size];
    memset(dest, 0, sizeof(WCHAR)*size);
    MultiByteToWideChar(CP_ACP, 0, src, -1, dest, (int)size); // convert local code to unicode.

    size = wcslen(dest) * 3 + 1;
    char* dest2 = new char[size];
    memset(dest2, 0, size);
    WideCharToMultiByte(CP_UTF8, 0, dest, -1, dest2, size, NULL, NULL); // convert unicode to utf8.
    delete[] dest;
    return dest2;
#endif
}

//
std::string SimulatorWin::getApplicationExePath()
{
    TCHAR szFileName[MAX_PATH];
    GetModuleFileName(NULL, szFileName, MAX_PATH);
    std::u16string u16ApplicationName;
    char *applicationExePath = convertTCharToUtf8(szFileName);
    std::string path(applicationExePath);
    CC_SAFE_FREE(applicationExePath);

    return path;
}

std::string SimulatorWin::getApplicationPath()
{
    std::string path = getApplicationExePath();
    size_t pos;
    while ((pos = path.find_first_of("\\")) != std::string::npos)
    {
        path.replace(pos, 1, "/");
    }
    size_t p = path.find_last_of("/");
    string workdir;
    if (p != path.npos)
    {
        workdir = path.substr(0, p);
    }

    return workdir;
}

LRESULT CALLBACK SimulatorWin::windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (!_instance) return 0;

    switch (uMsg)
    {
    case WM_SYSCOMMAND:
    case WM_COMMAND:
    {
        if (HIWORD(wParam) == 0)
        {
            // menu
            WORD menuId = LOWORD(wParam);
            auto menuService = dynamic_cast<player::PlayerMenuServiceWin*> (player::PlayerProtocol::getInstance()->getMenuService());
            auto menuItem = menuService->getItemByCommandId(menuId);
            if (menuItem)
            {
                AppEvent event("APP.EVENT", APP_EVENT_MENU);

                std::stringstream buf;
                buf << "{\"data\":\"" << menuItem->getMenuId().c_str() << "\"";
                buf << ",\"name\":" << "\"menuClicked\"" << "}";
                event.setDataString(buf.str());
                event.setUserData(menuItem);
                Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
            }

            if (menuId == ID_HELP_ABOUT)
            {
                onHelpAbout();
            }
        }
        break;
    }
    case WM_KEYDOWN:
    {
#if (SIMULATOR_WITH_CONSOLE_AND_MENU > 0)
        if (wParam == VK_F5)
        {
            _instance->relaunch();
        }
#endif
        break;
    }

    case WM_COPYDATA:
        {
            PCOPYDATASTRUCT pMyCDS = (PCOPYDATASTRUCT) lParam;
            if (pMyCDS->dwData == 1)
            {
                const char *szBuf = (const char*)(pMyCDS->lpData);
                SimulatorWin::getInstance()->writeDebugLog(szBuf);
                break;
            }
        }

    case WM_DESTROY:
    {
        DragAcceptFiles(hWnd, FALSE);
        break;
    }

    case WM_DROPFILES:
    {
        HDROP hDrop = (HDROP)wParam;

        const int count = DragQueryFileW(hDrop, 0xffffffff, NULL, 0);

        if (count > 0)
        {
            int fileIndex = 0;

            const UINT length = DragQueryFileW(hDrop, fileIndex, NULL, 0);
            WCHAR* buffer = (WCHAR*)calloc(length + 1, sizeof(WCHAR));

            DragQueryFileW(hDrop, fileIndex, buffer, length + 1);
            char *utf8 = SimulatorWin::convertTCharToUtf8(buffer);
            std::string firstFile(utf8);
            CC_SAFE_FREE(utf8);
            DragFinish(hDrop);

            // broadcast drop event
            AppEvent forwardEvent("APP.EVENT.DROP", APP_EVENT_DROP);
            forwardEvent.setDataString(firstFile);

            Director::getInstance()->getEventDispatcher()->dispatchEvent(&forwardEvent);
        }
    }   // WM_DROPFILES

    }
    return g_oldWindowProc(hWnd, uMsg, wParam, lParam);
}

