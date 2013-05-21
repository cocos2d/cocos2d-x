#include "CCFileUtilsEmscripten.h"
#include "platform/CCCommon.h"
#include "ccMacros.h"
#include "CCApplication.h"
#include "cocoa/CCString.h"
#include <unistd.h>

using namespace std;

NS_CC_BEGIN

CCFileUtils* CCFileUtils::sharedFileUtils()
{
    if (s_sharedFileUtils == NULL)
    {
        s_sharedFileUtils = new CCFileUtilsEmscripten();
        s_sharedFileUtils->init();
    }
    return s_sharedFileUtils;
}

CCFileUtilsEmscripten::CCFileUtilsEmscripten()
{}

bool CCFileUtilsEmscripten::init()
{
    m_strDefaultResRootPath = "app/native/Resources/";
    return CCFileUtils::init();
}

string CCFileUtilsEmscripten::getWritablePath()
{
    // Let's write it in the current working directory's data folder
    char cwd[FILENAME_MAX] = {0};

    getcwd(cwd, FILENAME_MAX - 1);
    cwd[FILENAME_MAX-1] = '\0';

    std::string path = cwd;
    path += "/data/";

    return path;
}

bool CCFileUtilsEmscripten::isAbsolutePath(const std::string& strPath)
{
    if (strPath[0] == '/' || strPath.find(m_strDefaultResRootPath) == 0)
    {
        return true;
    }
    return false;
}

bool CCFileUtilsEmscripten::isFileExist(const std::string& strFilePath)
{
    std::string strPath = strFilePath;
    if (strPath[0] != '/')
    { // Not absolute path, add the default root path at the beginning.
        if (strPath.find(m_strDefaultResRootPath) != 0)
        {// Didn't find "assets/" at the beginning of the path, adding it.
            strPath.insert(0, m_strDefaultResRootPath);
        }
    }

    return access(strPath.c_str(), F_OK) != -1 ? true : false;
}

NS_CC_END
