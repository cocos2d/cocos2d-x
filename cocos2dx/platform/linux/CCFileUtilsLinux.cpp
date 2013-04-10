/*
 * CCFileUtilsLinux.cpp
 *
 *  Created on: Aug 9, 2011
 *      Author: laschweinski
 */
#include "CCFileUtilsLinux.h"
#include "platform/CCCommon.h"
#include "ccMacros.h"
#include "CCApplication.h"
#include "cocoa/CCString.h"
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

using namespace std;

NS_CC_BEGIN

CCFileUtils* CCFileUtils::sharedFileUtils()
{
    if (s_sharedFileUtils == NULL)
    {
        s_sharedFileUtils = new CCFileUtilsLinux();
        s_sharedFileUtils->init();
    }
    return s_sharedFileUtils;
}

CCFileUtilsLinux::CCFileUtilsLinux()
{}

bool CCFileUtilsLinux::init()
{
    std::string path;
    path.append(getenv("HOME"));
    path.append("/.config/");
    path.append(getenv("_"));
    path.append("/");

    struct stat st;
    stat(path.c_str(), &st);
    if (!S_ISDIR(st.st_mode)) {
        mkdir(path.c_str(), 0744);
    }

    m_writablePath = path;

    return CCFileUtils::init();
}

string CCFileUtilsLinux::getWritablePath()
{
    return m_writablePath;
}

bool CCFileUtilsLinux::isFileExist(const std::string& strFilePath)
{
    std::string strPath = strFilePath;
    if (!isAbsolutePath(strPath))
    { // Not absolute path, add the default root path at the beginning.
        strPath.insert(0, m_strDefaultResRootPath);
    }
    
    struct stat sts;
    return (stat(strPath.c_str(), &sts) != -1) ? true : false;
}

NS_CC_END
