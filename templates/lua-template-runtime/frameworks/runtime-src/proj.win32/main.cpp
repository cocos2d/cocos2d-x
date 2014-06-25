#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"
#include <shellapi.h>
USING_NS_CC;

// uncomment below line, open debug console
//#define USE_WIN32_CONSOLE

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LPWSTR *szArgList=nullptr;
    int argCount=0;

    szArgList = CommandLineToArgvW(GetCommandLine(),&argCount);
    if (argCount >=2 )
    {
        int iLen = 2*wcslen(szArgList[1]);    
        char* chRtn = new char[iLen+1];    
        wcstombs(chRtn,szArgList[1],iLen+1);
        extern std::string g_resourcePath;
        g_resourcePath = chRtn;
        delete [] chRtn;
    }
    LocalFree(szArgList);

#ifdef USE_WIN32_CONSOLE
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif

    // create the application instance
    AppDelegate app;

    int ret = Application::getInstance()->run();

#ifdef USE_WIN32_CONSOLE
    FreeConsole();
#endif

    return ret;
}
std::string getCurAppPath(void)
{
    TCHAR szAppDir[MAX_PATH]={0};
    if (!GetModuleFileName(NULL,szAppDir,MAX_PATH))
        return "";
    int nEnd=0;
    for (int i=0;szAppDir[i];i++)
    {
        if(szAppDir[i]=='\\')
            nEnd = i;
    }
    szAppDir[nEnd] = 0;
    int iLen = 2*wcslen(szAppDir);    
    char* chRtn = new char[iLen+1];    
    wcstombs(chRtn,szAppDir,iLen+1);
    std::string strPath = chRtn;
    delete [] chRtn;
    chRtn=NULL;
    char fuldir[MAX_PATH]={0};
    _fullpath(fuldir,strPath.c_str(),MAX_PATH);
    return fuldir;    
}
