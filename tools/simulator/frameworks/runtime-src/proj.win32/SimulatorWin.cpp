/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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
#include <Winuser.h>

#include "SimulatorWin.h"

#include "glfw3.h"
#include "glfw3native.h"

#include "AppEvent.h"
#include "AppLang.h"
#include "runtime/ConfigParser.h"
#include "runtime/Runtime.h"

#include "platform/win32/PlayerWin.h"
#include "platform/win32/PlayerMenuServiceWin.h"

#include "resource.h"

USING_NS_CC;

static WNDPROC g_oldWindowProc = NULL;
INT_PTR CALLBACK AboutDialogCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    LOGFONT lf;
    HFONT hFont;

    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        ZeroMemory(&lf, sizeof(LOGFONT));
        lf.lfHeight = 24;
        lf.lfWeight = 200;
        _tcscpy(lf.lfFaceName, _T("Arial"));

        hFont = CreateFontIndirect(&lf);
        if ((HFONT)0 != hFont)
        {
            SendMessage(GetDlgItem(hDlg, IDC_ABOUT_TITLE), WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);
        }
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
    TCHAR szAppDir[MAX_PATH] = {0};
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
    char fuldir[MAX_PATH] = {0};
    _fullpath(fuldir, strPath.c_str(), MAX_PATH);
    return fuldir;
}

static bool stringEndWith(const std::string& str, const std::string& needle)
{
    if (str.length() >= needle.length())
    {
        return (0 == str.compare(str.length() - needle.length(), needle.length(), needle));
    }
    return false;
}

static void initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

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
    : _hwnd(NULL)
    , _hwndConsole(NULL)
    , _app(nullptr)
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

#define MAX_COMMAND 1024 // length of commandLine is always beyond MAX_PATH

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

    // check scale
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

    // check screen workarea
    RECT workareaSize;
    if (SystemParametersInfo(SPI_GETWORKAREA, NULL, &workareaSize, NULL))
    {
        float workareaWidth = fabsf(workareaSize.right - workareaSize.left);
        float workareaHeight = fabsf(workareaSize.bottom - workareaSize.top);
        float frameBorderCX = GetSystemMetrics(SM_CXSIZEFRAME);
        float frameBorderCY = GetSystemMetrics(SM_CYSIZEFRAME);
        workareaWidth -= frameBorderCX * 2;
        workareaHeight -= (frameBorderCY * 2 + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU));
        CCLOG("WORKAREA WIDTH %0.2f, HEIGHT %0.2f", workareaWidth, workareaHeight);
        while (true && frameScale > 0.25f)
        {
            if (frameSize.width * frameScale > workareaWidth || frameSize.height * frameScale > workareaHeight)
            {
                frameScale = frameScale - 0.25f;
            }
            else
            {
                break;
            }
        }

        if (frameScale < 0.25f) frameScale = 0.25f;
    }
    _project.setFrameScale(frameScale);
    CCLOG("FRAME SCALE = %0.2f", frameScale);

    // create opengl view
    const Rect frameRect = Rect(0, 0, frameSize.width, frameSize.height);
    ConfigParser::getInstance()->setInitViewSize(frameSize);
    const bool isResize = _project.isResizeWindow();
    std::stringstream title;
    title << "Cocos Simulator (" << _project.getFrameScale() * 100 << "%)";
    initGLContextAttrs();
    auto glview = GLViewImpl::createWithRect(title.str(), frameRect, frameScale);
    _hwnd = glview->getWin32Window();
    player::PlayerWin::createWithHwnd(_hwnd);
    DragAcceptFiles(_hwnd, TRUE);
    //SendMessage(_hwnd, WM_SETICON, ICON_BIG, (LPARAM)icon);
    //SendMessage(_hwnd, WM_SETICON, ICON_SMALL, (LPARAM)icon);
    //FreeResource(icon);

    // path for looking Lang file, Studio Default images
    FileUtils::getInstance()->addSearchPath(getApplicationPath().c_str());

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
        if (pos.x < 0)
            pos.x = 0;
        if (pos.y < 0)
            pos.y = 0;
        MoveWindow(_hwnd, pos.x, pos.y, rect.right - rect.left, rect.bottom - rect.top, FALSE);
    }

    // init player services
    setupUI();
    DrawMenuBar(_hwnd);

    // prepare
    FileUtils::getInstance()->setPopupNotify(false);
    _project.dump();
    auto app = Application::getInstance();

    g_oldWindowProc = (WNDPROC)SetWindowLong(_hwnd, GWL_WNDPROC, (LONG)SimulatorWin::windowProc);

    // update window title
    updateWindowTitle();

    // startup message loop
    int ret = app->run();
    CC_SAFE_DELETE(_app);
    return ret;
}

// services

void SimulatorWin::setupUI()
{
    auto menuBar = player::PlayerProtocol::getInstance()->getMenuService();

    // FILE
    menuBar->addItem("FILE_MENU", tr("File"));
    menuBar->addItem("OPEN_FILE_MENU", tr("Open File") + "...", "FILE_MENU");
    menuBar->addItem("OPEN_PROJECT_MENU", tr("Open Project") + "...", "FILE_MENU");
    menuBar->addItem("FILE_MENU_SEP1", "-", "FILE_MENU");
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

    // About
    menuBar->addItem("HELP_MENU", tr("Help"));
    menuBar->addItem("ABOUT_MENUITEM", tr("About"), "HELP_MENU");

    menuBar->addItem("DIRECTION_MENU_SEP", "-", "VIEW_MENU");
    menuBar->addItem("DIRECTION_PORTRAIT_MENU", tr("Portrait"), "VIEW_MENU")
        ->setChecked(_project.isPortraitFrame());
    menuBar->addItem("DIRECTION_LANDSCAPE_MENU", tr("Landscape"), "VIEW_MENU")
        ->setChecked(_project.isLandscapeFrame());

    menuBar->addItem("VIEW_SCALE_MENU_SEP", "-", "VIEW_MENU");
    std::vector<player::PlayerMenuItem*> scaleMenuVector;
    auto scale200Menu = menuBar->addItem("VIEW_SCALE_MENU_200", tr("Zoom Out").append(" (200%)"), "VIEW_MENU");
    auto scale175Menu = menuBar->addItem("VIEW_SCALE_MENU_175", tr("Zoom Out").append(" (175%)"), "VIEW_MENU");
    auto scale150Menu = menuBar->addItem("VIEW_SCALE_MENU_150", tr("Zoom Out").append(" (150%)"), "VIEW_MENU");
    auto scale125Menu = menuBar->addItem("VIEW_SCALE_MENU_125", tr("Zoom Out").append(" (125%)"), "VIEW_MENU");
    auto scale100Menu = menuBar->addItem("VIEW_SCALE_MENU_100", tr("Zoom Out").append(" (100%)"), "VIEW_MENU");
    auto scale75Menu = menuBar->addItem("VIEW_SCALE_MENU_75", tr("Zoom Out").append(" (75%)"), "VIEW_MENU");
    auto scale50Menu = menuBar->addItem("VIEW_SCALE_MENU_50", tr("Zoom Out").append(" (50%)"), "VIEW_MENU");
    auto scale25Menu = menuBar->addItem("VIEW_SCALE_MENU_25", tr("Zoom Out").append(" (25%)"), "VIEW_MENU");
    int frameScale = int(_project.getFrameScale() * 100);

    if (frameScale == 200)
    {
        scale200Menu->setChecked(true);
    }
    else if (frameScale == 175)
    {
        scale175Menu->setChecked(true);
    }
    else if (frameScale == 150)
    {
        scale150Menu->setChecked(true);
    }
    else if (frameScale == 125)
    {
        scale125Menu->setChecked(true);
    }
    else if (frameScale == 100)
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

    scaleMenuVector.push_back(scale200Menu);
    scaleMenuVector.push_back(scale175Menu);
    scaleMenuVector.push_back(scale150Menu);
    scaleMenuVector.push_back(scale125Menu);
    scaleMenuVector.push_back(scale100Menu);
    scaleMenuVector.push_back(scale75Menu);
    scaleMenuVector.push_back(scale50Menu);
    scaleMenuVector.push_back(scale25Menu);

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

                            _instance->setZoom(scale);

                            // update scale menu state
                            for (auto &it : scaleMenuVector)
                            {
                                it->setChecked(false);
                            }
                            menuItem->setChecked(true);

                            // update window title
                            _instance->updateWindowTitle();

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
                        else if (data == "OPEN_FILE_MENU")
                        {
                            auto fileDialog = player::PlayerProtocol::getInstance()->getFileDialogService();
                            stringstream extensions;
                            extensions << "All Support File|config.json,*.csd,*csd;"
                                << "Project Config File|config.json;"
                                << "Cocos Studio File|*.csd;"
                                << "Cocos Studio Binary File|*.csb";
                            auto entry = fileDialog->openFile(tr("Choose File"), "", extensions.str());

                            _instance->onOpenFile(entry);
                        }
                        else if (data == "OPEN_PROJECT_MENU")
                        {
                            auto fileDialog = player::PlayerProtocol::getInstance()->getFileDialogService();
                            auto path = fileDialog->openDirectory(tr("Choose Folder"), "");

                            _instance->onOpenProjectFolder(path);
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

void SimulatorWin::updateWindowTitle()
{
    std::stringstream title;
    title << "Cocos " << tr("Simulator") << " (" << _project.getFrameScale() * 100 << "%)";
    std::u16string u16title;
    cocos2d::StringUtils::UTF8ToUTF16(title.str(), u16title);
    SetWindowText(_hwnd, (LPCTSTR)u16title.c_str());
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
    string solutionDir = tmpConfig.getProjectDir();
    if (!solutionDir.empty())
    {
        for (int i = 0; i < solutionDir.size(); ++i)
        {
            if (solutionDir[i] == '\\')
            {
                solutionDir[i] = '/';
            }
        }
        int nPos = -1;
        if (solutionDir[solutionDir.length() - 1] == '/')
            nPos = solutionDir.rfind('/', solutionDir.length() - 2);
        else
            nPos = solutionDir.rfind('/');
        if (nPos > 0)
            solutionDir = solutionDir.substr(0, nPos + 1);
        FileUtils::getInstance()->setDefaultResourceRootPath(solutionDir);
        FileUtils::getInstance()->addSearchPath(solutionDir);
        FileUtils::getInstance()->addSearchPath(tmpConfig.getProjectDir().c_str());
    }
    else
    {
        FileUtils::getInstance()->setDefaultResourceRootPath(tmpConfig.getProjectDir().c_str());
    }

    // parse config.json
    auto parser = ConfigParser::getInstance();
    auto configPath = solutionDir.append(CONFIG_FILE);
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
        if (wParam == VK_F5)
        {
            _instance->relaunch();
        }
        break;
    }

    case WM_COPYDATA:
    {
        PCOPYDATASTRUCT pMyCDS = (PCOPYDATASTRUCT)lParam;
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

            _instance->onDrop(firstFile);
        }
    }   // WM_DROPFILES

    }
    return g_oldWindowProc(hWnd, uMsg, wParam, lParam);
}

void SimulatorWin::onOpenFile(const std::string &filePath)
{
    string entry = filePath;
    if (entry.empty()) return;

    if (stringEndWith(entry, "config.json") || stringEndWith(entry, ".csb") || stringEndWith(entry, ".csd"))
    {
        replaceAll(entry, "\\", "/");
        size_t p = entry.find_last_of("/");
        if (p != entry.npos)
        {
            string workdir = entry.substr(0, p);
            _project.setProjectDir(workdir);
        }

        _project.setScriptFile(entry);
        if (stringEndWith(entry, CONFIG_FILE))
        {
            ConfigParser::getInstance()->readConfig(entry);
            _project.setScriptFile(ConfigParser::getInstance()->getEntryFile());
        }
        openProjectWithProjectConfig(_project);
    }
    else
    {
        auto title = tr("Open File") + tr("Error");
        auto msg = tr("Only support") + " config.json;*.csb;*.csd";
        auto msgBox = player::PlayerProtocol::getInstance()->getMessageBoxService();
        msgBox->showMessageBox(title, msg);
    }
}

/*
1. find @folderPath/config.json
2. get project name from file: @folderPath/folderName.ccs
3. find @folderPath/cocosstudio/MainScene.csd
4. find @folderPath/cocosstudio/MainScene.csb
*/
void SimulatorWin::onOpenProjectFolder(const std::string &folderPath)
{
    string path = folderPath;
    if (!path.empty())
    {
        replaceAll(path, "\\", "/");

        auto fileUtils = FileUtils::getInstance();
        bool foundProjectFile = false;
        // 1. check config.json
        auto configPath = path + "/" + CONFIG_FILE;
        if (fileUtils->isFileExist(configPath))
        {
            ConfigParser::getInstance()->readConfig(configPath);
            _project.setProjectDir(path);
            _project.setScriptFile(ConfigParser::getInstance()->getEntryFile());
            foundProjectFile = true;
        }
        // check ccs project
        else
        {
            // 2.
            if (path.at(path.size() - 1) == '/') path.erase(path.size() - 1);
            ssize_t pos = path.find_last_of('/');
            if (pos != std::string::npos)
            {
                auto folderName = path.substr(path.find_last_of('/'), path.size());
                auto ccsFilePath = path + folderName + ".ccs";
                if (fileUtils->isFileExist(ccsFilePath))
                {
                    auto fileContent = fileUtils->getStringFromFile(ccsFilePath);

                    string matchString("<Project Name=\"");
                    pos = fileContent.find(matchString);
                    // get project file name
                    if (pos != std::string::npos)
                    {
                        fileContent = fileContent.substr(pos + matchString.size(), fileContent.size());
                        ssize_t posEnd = fileContent.find_first_of('"');
                        auto projectFileName = path + "/cocosstudio/" + fileContent.substr(0, posEnd);
                        _project.setProjectDir(path);
                        _project.setScriptFile(projectFileName);
                        foundProjectFile = true;
                    }
                }
            }

            if (!foundProjectFile)
            {
                auto csdFilePath = path + "/cocosstudio/MainScene.csd";
                auto csbFilePath = path + "/cocosstudio/MainScene.csb";
                // 3.
                if (fileUtils->isFileExist(csdFilePath))
                {
                    _project.setProjectDir(path);
                    _project.setScriptFile(csdFilePath);
                    foundProjectFile = true;
                }
                // 4.
                else if (fileUtils->isFileExist(csbFilePath))
                {
                    _project.setProjectDir(path);
                    _project.setScriptFile(csbFilePath);
                    foundProjectFile = true;
                }
            }
        }

        if (foundProjectFile)
        {
            openProjectWithProjectConfig(_project);
        }
        else
        {
            auto title = tr("Open Project") + tr("Error");
            auto msgBox = player::PlayerProtocol::getInstance()->getMessageBoxService();
            msgBox->showMessageBox(title, tr("Can not find project"));
        }
    }
}

void SimulatorWin::onDrop(const std::string &path)
{
    auto fileUtils = FileUtils::getInstance();
    if (fileUtils->isDirectoryExist(path))
    {
        onOpenProjectFolder(path);
    }
    else if (fileUtils->isFileExist(path))
    {
        onOpenFile(path);
    }
}
