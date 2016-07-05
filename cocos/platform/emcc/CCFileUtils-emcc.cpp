#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_EMSCRIPTEN

#include "CCFileUtils-emcc.h"
#include "platform/CCCommon.h"
#include "CCApplication.h"
#include <unistd.h>
#include <sys/stat.h>

using namespace std;

NS_CC_BEGIN

FileUtils* FileUtils::getInstance()
{
    if (s_sharedFileUtils == NULL)
    {
        s_sharedFileUtils = new FileUtilsEmscripten();
        if(!s_sharedFileUtils->init())
        {
          delete s_sharedFileUtils;
          s_sharedFileUtils = NULL;
          CCLOG("ERROR: Could not init CCFileUtilsEmscripten");
        }
    }
    return s_sharedFileUtils;
}

FileUtilsEmscripten::FileUtilsEmscripten()
{
    mkdir("/data", S_IRWXU | S_IRWXG | S_IRWXO);
    mkdir("/cache", S_IRWXU | S_IRWXG | S_IRWXO);
}

bool FileUtilsEmscripten::init()
{
    _defaultResRootPath = "/";
    return FileUtils::init();
}

string FileUtilsEmscripten::getWritablePath() const
{
    // Let's write it in the current working directory's data folder
    char cwd[FILENAME_MAX] = {0};

    getcwd(cwd, FILENAME_MAX - 1);
    cwd[FILENAME_MAX-1] = '\0';

    std::string path = cwd;
    path += "/data/";

    return path;
}

string FileUtilsEmscripten::getCachePath() const
{
    // Let's write it in the current working directory's data folder
    char cwd[FILENAME_MAX] = {0};

    getcwd(cwd, FILENAME_MAX - 1);
    cwd[FILENAME_MAX-1] = '\0';

    std::string path = cwd;
    path += "/cache/";

    return path;
}

bool FileUtilsEmscripten::isFileExistInternal(const std::string& strFilePath) const
{
    std::string strPath = strFilePath;
    if (strPath[0] != '/')
    { // Not absolute path, add the default root path at the beginning.
        if (strPath.find(_defaultResRootPath) != 0)
        {// Didn't find "assets/" at the beginning of the path, adding it.
            strPath.insert(0, _defaultResRootPath);
        }
    }

    return access(strPath.c_str(), F_OK) != -1 ? true : false;
}

NS_CC_END

#endif
