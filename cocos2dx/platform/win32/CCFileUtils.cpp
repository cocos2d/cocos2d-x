/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#define __CC_PLATFORM_FILEUTILS_CPP__
#include "platform/CCFileUtilsCommon_cpp.h"
#include <windows.h>
#include "CCDirector.h"

#define CC_RETINA_DISPLAY_FILENAME_SUFFIX "-hd"
#define CC_IPAD_FILENAME_SUFFIX "-ipad"
#define CC_IPAD_DISPLAY_RETINA_SUPPFIX "-ipadhd"

using namespace std;

NS_CC_BEGIN

// record the resource path
static char s_pszResourcePath[MAX_PATH] = {0};

static void _CheckPath()
{
    if (! s_pszResourcePath[0])
    {
        WCHAR  wszPath[MAX_PATH];
        int nNum = WideCharToMultiByte(CP_ACP, 0, wszPath, 
            GetCurrentDirectoryW(sizeof(wszPath), wszPath), 
            s_pszResourcePath, MAX_PATH, NULL, NULL);
        s_pszResourcePath[nNum] = '\\';
    }
}

static CCFileUtils* s_pFileUtils = NULL;

CCFileUtils* CCFileUtils::sharedFileUtils()
{
    if (s_pFileUtils == NULL)
    {
        s_pFileUtils = new CCFileUtils();
    }
    return s_pFileUtils;
}

void CCFileUtils::purgeFileUtils()
{
    if (s_pFileUtils != NULL)
    {
        s_pFileUtils->purgeCachedEntries();
    }
    
    CC_SAFE_DELETE(s_pFileUtils);
}

void CCFileUtils::purgeCachedEntries()
{

}

void CCFileUtils::setResourcePath(const char *pszResourcePath)
{
    CCAssert(pszResourcePath != NULL, "[FileUtils setResourcePath] -- wrong resource path");
    CCAssert(strlen(pszResourcePath) <= MAX_PATH, "[FileUtils setResourcePath] -- resource path too long");

    strcpy(s_pszResourcePath, pszResourcePath);
}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath, ccResolutionType *pResolutionType)
{
    _CheckPath();

    CCString * pRet = new CCString();
    pRet->autorelease();
    if ((strlen(pszRelativePath) > 1 && pszRelativePath[1] == ':'))
    {
        // path start with "x:", is absolute path
        pRet->m_sString = pszRelativePath;
    }
    else if (strlen(pszRelativePath) > 0 
        && ('/' == pszRelativePath[0] || '\\' == pszRelativePath[0]))
    {
        // path start with '/' or '\', is absolute path without driver name
        char szDriver[3] = {s_pszResourcePath[0], s_pszResourcePath[1], 0};
        pRet->m_sString = szDriver;
        pRet->m_sString += pszRelativePath;
    }
    else
    {
        pRet->m_sString = s_pszResourcePath;
        pRet->m_sString += pszRelativePath;
    }

    // is ipad?
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    bool isIpad = (winSize.width == 1024 || winSize.height == 768);

    std::string hiRes = pRet->m_sString.c_str();
    std::string::size_type pos = hiRes.find_last_of("/\\");
    std::string::size_type dotPos = hiRes.find_last_of(".");
    *pResolutionType = kCCResolutioniPhone;

    if (isIpad)
    {
        if (CC_CONTENT_SCALE_FACTOR() == 1.0f)
        {
            // ipad

            if (std::string::npos != dotPos && dotPos > pos)
            {
                hiRes.insert(dotPos, CC_IPAD_FILENAME_SUFFIX);
            }
            else
            {
                hiRes.append(CC_IPAD_FILENAME_SUFFIX);
            }
            
            *pResolutionType = kCCResolutioniPad;
        }
        else
        {
            // ipad retina

            if (std::string::npos != dotPos && dotPos > pos)
            {
                hiRes.insert(dotPos, CC_IPAD_DISPLAY_RETINA_SUPPFIX);
            }
            else
            {
                hiRes.append(CC_IPAD_DISPLAY_RETINA_SUPPFIX);
            }
            
            *pResolutionType = kCCResolutioniPadRetinaDisplay;
        }
    }
    else
    {    
        if (CC_CONTENT_SCALE_FACTOR() != 1.0f)
        {
            // iphone retina

            if (std::string::npos != dotPos && dotPos > pos)
            {
                hiRes.insert(dotPos, CC_RETINA_DISPLAY_FILENAME_SUFFIX);
            }
            else
            {
                hiRes.append(CC_RETINA_DISPLAY_FILENAME_SUFFIX);
            }
            
            *pResolutionType = kCCResolutioniPhoneRetinaDisplay;
        }
    }  

    DWORD attrib = GetFileAttributesA(hiRes.c_str());
    if (attrib != INVALID_FILE_ATTRIBUTES && ! (FILE_ATTRIBUTE_DIRECTORY & attrib))
    {
        pRet->m_sString.swap(hiRes);
    }

    return pRet->m_sString.c_str();
}

const char *CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
{
    _CheckPath();
    // std::string relativeFile = fullPathFromRelativePath(pszRelativeFile);
    std::string relativeFile = pszRelativeFile;
    CCString *pRet = new CCString();
    pRet->autorelease();
    pRet->m_sString = relativeFile.substr(0, relativeFile.find_last_of("/\\") + 1);
    pRet->m_sString += pszFilename;
    return pRet->m_sString.c_str();
}

unsigned char* CCFileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long* pSize)
{
    unsigned char* pBuffer = NULL;
    CCAssert(pszFileName != NULL && pSize != NULL && pszMode != NULL, "Invaild parameters.");
    *pSize = 0;
    do 
    {
        // read the file from hardware
        FILE *fp = fopen(pszFileName, pszMode);
        CC_BREAK_IF(!fp);

        fseek(fp,0,SEEK_END);
        *pSize = ftell(fp);
        fseek(fp,0,SEEK_SET);
        pBuffer = new unsigned char[*pSize];
        *pSize = fread(pBuffer,sizeof(unsigned char), *pSize,fp);
        fclose(fp);
    } while (0);

    if (! pBuffer && isPopupNotify())
    {
        std::string title = "Notification";
        std::string msg = "Get data from file(";
        msg.append(pszFileName).append(") failed!");

        CCMessageBox(msg.c_str(), title.c_str());
    }
    return pBuffer;
}

string CCFileUtils::getWriteablePath()
{
    // return the path that the exe file saved in

    char full_path[_MAX_PATH + 1];
    ::GetModuleFileNameA(NULL, full_path, _MAX_PATH + 1);

    string ret((char*)full_path);

    // remove xxx.exe
    ret =  ret.substr(0, ret.rfind("\\") + 1);

    return ret;
}

NS_CC_END
