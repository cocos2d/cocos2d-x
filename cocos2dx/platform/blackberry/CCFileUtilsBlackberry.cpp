#include "CCFileUtilsBlackberry.h"
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
        s_sharedFileUtils = new CCFileUtilsBlackberry();
        s_sharedFileUtils->init();
    }
    return s_sharedFileUtils;
}

CCFileUtilsBlackberry::CCFileUtilsBlackberry()
{}

bool CCFileUtilsBlackberry::init()
{
    m_strDefaultResRootPath = "app/native/Resources/";
    return CCFileUtils::init();
}

string CCFileUtilsBlackberry::getWriteablePath()
{
    // Let's write it in the current working directory's data folder
    char cwd[FILENAME_MAX] = {0};

    getcwd(cwd, FILENAME_MAX - 1);
    cwd[FILENAME_MAX-1] = '\0';

    std::string path = cwd;
    path += "/data/";

    return path;
}

bool CCFileUtilsBlackberry::isAbsolutePath(const std::string& strPath)
{
    if (strPath[0] == '/' || strPath.find(m_strDefaultResRootPath) == 0)
    {
        return true;
    }
    return false;
}

bool CCFileUtilsBlackberry::isFileExist(const std::string& strFullpathOfFile)
{
    return access(strFullpathOfFile.c_str(), F_OK) != -1 ? true : false;
}

NS_CC_END
