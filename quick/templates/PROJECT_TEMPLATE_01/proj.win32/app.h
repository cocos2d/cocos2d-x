
#pragma once

#include "resource.h"

// C RunTime Header Files
#include "CCStdC.h"

#include <string>

#include "cocos2d.h"
#include "AppDelegate.h"
#include "ProjectConfig/SimulatorConfig.h"

using namespace std;
using namespace cocos2d;

class CC_DLL App : public CCObject
{
public:
    static int createAndRun(void);

    AppDelegate *getApp(void) {
        return m_app;
    }

    HWND getWindowHandle(void) {
        return m_hwnd;
    }

private:
    static App *s_sharedInstance;
    static App *sharedInstance(void);
    static void purgeSharedInstance(void);

    App(void);

    AppDelegate *m_app;
    ProjectConfig m_project;

    HWND m_hwnd;
    BOOL m_exit;
    FILE *m_writeDebugLogFile;

    int run(void);
    void loadProjectConfig(void);
    void createViewMenu(void);
    void updateMenu(void);
    void relaunch(void);

    // debug log
    void writeDebugLog(const char *log);

    // menu callback
    void onFileRelaunch(void);
    void onFileExit(void);

    void onViewChangeFrameSize(int viewMenuID);
    void onViewChangeOrientation(int viewMenuID);
    void onViewChangeZoom(int scaleMode);

    // windows callback
    static LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam, BOOL *pProcessed);
};
