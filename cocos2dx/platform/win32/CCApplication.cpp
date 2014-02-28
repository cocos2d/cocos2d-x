#include "CCApplication.h"
#include "CCEGLView.h"
#include "CCDirector.h"
#include <algorithm>
#include "platform/CCFileUtils.h"
/**
@brief    This function change the PVRFrame show/hide setting in register.
@param  bEnable If true show the PVRFrame window, otherwise hide.
*/
static void PVRFrameEnableControlWindow(bool bEnable);

NS_CC_BEGIN

// sharedApplication pointer
CCApplication * CCApplication::sm_pSharedApplication = 0;

CCApplication::CCApplication()
: m_hInstance(NULL)
, m_hAccelTable(NULL)
{
    m_hInstance    = GetModuleHandle(NULL);
    m_nAnimationInterval.QuadPart = 0;
    CC_ASSERT(! sm_pSharedApplication);
    sm_pSharedApplication = this;
}

CCApplication::~CCApplication()
{
    CC_ASSERT(this == sm_pSharedApplication);
    sm_pSharedApplication = NULL;
}

int CCApplication::run()
{
    PVRFrameEnableControlWindow(false);

    // Main message loop:
    MSG msg;
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nLast;
    LARGE_INTEGER nNow;

    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nLast);

    // Initialize instance and cocos2d.
    if (!applicationDidFinishLaunching())
    {
        return 0;
    }

    CCEGLView* pMainWnd = CCEGLView::sharedOpenGLView();
    pMainWnd->centerWindow();
    ShowWindow(pMainWnd->getHWnd(), SW_SHOW);

    while (1)
    {
        if (! PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // Get current time tick.
            QueryPerformanceCounter(&nNow);

            // If it's the time to draw next frame, draw it, else sleep a while.
            if (nNow.QuadPart - nLast.QuadPart > m_nAnimationInterval.QuadPart)
            {
                nLast.QuadPart = nNow.QuadPart;
                CCDirector::sharedDirector()->mainLoop();
            }
            else
            {
                Sleep(0);
            }
            continue;
        }

        if (WM_QUIT == msg.message)
        {
            // Quit message loop.
            break;
        }

        // Deal with windows message.
        if (! m_hAccelTable || ! TranslateAccelerator(msg.hwnd, m_hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

void CCApplication::setAnimationInterval(double interval)
{
    LARGE_INTEGER nFreq;
    QueryPerformanceFrequency(&nFreq);
    m_nAnimationInterval.QuadPart = (LONGLONG)(interval * nFreq.QuadPart);
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
CCApplication* CCApplication::sharedApplication()
{
    CC_ASSERT(sm_pSharedApplication);
    return sm_pSharedApplication;
}

ccLanguageType CCApplication::getCurrentLanguage()
{
    ccLanguageType ret = kLanguageEnglish;

    LCID localeID = GetUserDefaultLCID();
    unsigned short primaryLanguageID = localeID & 0xFF;
    
    switch (primaryLanguageID)
    {
        case LANG_CHINESE:
            ret = kLanguageChinese;
            break;
        case LANG_ENGLISH:
            ret = kLanguageEnglish;
            break;
        case LANG_FRENCH:
            ret = kLanguageFrench;
            break;
        case LANG_ITALIAN:
            ret = kLanguageItalian;
            break;
        case LANG_GERMAN:
            ret = kLanguageGerman;
            break;
        case LANG_SPANISH:
            ret = kLanguageSpanish;
            break;
        case LANG_DUTCH:
            ret = kLanguageDutch;
            break;
        case LANG_RUSSIAN:
            ret = kLanguageRussian;
            break;
        case LANG_KOREAN:
            ret = kLanguageKorean;
            break;
        case LANG_JAPANESE:
            ret = kLanguageJapanese;
            break;
        case LANG_HUNGARIAN:
            ret = kLanguageHungarian;
            break;
        case LANG_PORTUGUESE:
            ret = kLanguagePortuguese;
            break;
        case LANG_ARABIC:
            ret = kLanguageArabic;
            break;
    }

    return ret;
}

TargetPlatform CCApplication::getTargetPlatform()
{
    return kTargetWindows;
}

void CCApplication::setResourceRootPath(const std::string& rootResDir)
{
    m_resourceRootPath = rootResDir;
    std::replace(m_resourceRootPath.begin(), m_resourceRootPath.end(), '\\', '/');
    if (m_resourceRootPath[m_resourceRootPath.length() - 1] != '/')
    {
        m_resourceRootPath += '/';
    }
    CCFileUtils* pFileUtils = CCFileUtils::sharedFileUtils();
    std::vector<std::string> searchPaths = pFileUtils->getSearchPaths();
    searchPaths.insert(searchPaths.begin(), m_resourceRootPath);
    pFileUtils->setSearchPaths(searchPaths);
}

const std::string& CCApplication::getResourceRootPath(void)
{
    return m_resourceRootPath;
}

void CCApplication::setStartupScriptFilename(const std::string& startupScriptFile)
{
    m_startupScriptFilename = startupScriptFile;
    std::replace(m_startupScriptFilename.begin(), m_startupScriptFilename.end(), '\\', '/');
}

NS_CC_END

//////////////////////////////////////////////////////////////////////////
// Local function
//////////////////////////////////////////////////////////////////////////
static void PVRFrameEnableControlWindow(bool bEnable)
{
    HKEY hKey = 0;

    // Open PVRFrame control key, if not exist create it.
    if(ERROR_SUCCESS != RegCreateKeyExW(HKEY_CURRENT_USER,
        L"Software\\Imagination Technologies\\PVRVFRame\\STARTUP\\",
        0,
        0,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
        0,
        &hKey,
        NULL))
    {
        return;
    }

    const WCHAR* wszValue = L"hide_gui";
    const WCHAR* wszNewData = (bEnable) ? L"NO" : L"YES";
    WCHAR wszOldData[256] = {0};
    DWORD   dwSize = sizeof(wszOldData);
    LSTATUS status = RegQueryValueExW(hKey, wszValue, 0, NULL, (LPBYTE)wszOldData, &dwSize);
    if (ERROR_FILE_NOT_FOUND == status              // the key not exist
        || (ERROR_SUCCESS == status                 // or the hide_gui value is exist
        && 0 != wcscmp(wszNewData, wszOldData)))    // but new data and old data not equal
    {
        dwSize = sizeof(WCHAR) * (wcslen(wszNewData) + 1);
        RegSetValueEx(hKey, wszValue, 0, REG_SZ, (const BYTE *)wszNewData, dwSize);
    }

    RegCloseKey(hKey);
}
