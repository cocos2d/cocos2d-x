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


#include <TG3.h>
#include "CCApplication.h"

NS_CC_BEGIN;

// record the resource path
static char s_pszResourcePath[EOS_FILE_MAX_PATH] = {0};
static char s_pszZipFilePath[EOS_FILE_MAX_PATH]  = {0};

void updateZipFilePath(const char* pResPath)
{
    if (! strlen(s_pszZipFilePath))
    {
        return;
    }

    std::string strTemp = s_pszZipFilePath;
    int nPos = std::string::npos;

    // find the path need br replaced
    std::string ResPath;
    if (strlen(s_pszResourcePath))
    {
        ResPath = s_pszResourcePath;
    }
    else
    {
        ResPath = CCApplication::sharedApplication().getAppDataPath();
    }

    // replace the resource path in s_pszZipFilePath
    nPos = strTemp.find(ResPath.c_str());
    if (nPos != std::string::npos)
    {
        strTemp.replace(nPos, ResPath.length(), pResPath);
        memset(s_pszZipFilePath, 0, sizeof(char) * EOS_FILE_MAX_PATH);
        strcpy(s_pszZipFilePath, strTemp.c_str());
    }
}

void setZipFilePath(const char* pZipFileName)
{
    CCAssert(pZipFileName != NULL, "[FileUtils setResourceZipFile] -- wrong zip file path");

    // get the full path of zip file
    char fullPath[EOS_FILE_MAX_PATH] = {0};

    if (strlen(s_pszResourcePath))
    {
        strcpy(fullPath, s_pszResourcePath);
    }
    else
    {
        const char* pAppDataPath = CCApplication::sharedApplication().getAppDataPath();
        strcpy(fullPath, pAppDataPath);
    }
    strcat(fullPath, pZipFileName);

    // if the zip file not exist,use message box to warn developer
    TUChar pszTmp[EOS_FILE_MAX_PATH] = {0};
    TUString::StrGBToUnicode(pszTmp, (const Char*) fullPath);
    Boolean bExist = EOS_IsFileExist(pszTmp);
    if (!bExist)
    {
        std::string strErr = "zip file ";
        strErr += fullPath;
        strErr += " not exist!";
        TUChar szText[EOS_FILE_MAX_PATH] = { 0 };
        TUString::StrUtf8ToStrUnicode(szText,(Char*)strErr.c_str());
		TMessageBox box(szText, NULL, WMB_OK);
        box.Show();
        return;
    }

#ifndef _TRANZDA_VM_
    char *pszDriver = "";
#else
    char *pszDriver = "D:/Work7";
#endif
    CCAssert((strlen(pszDriver) + strlen(fullPath)) <= EOS_FILE_MAX_PATH, "[FileUtils setResourceZipFile] -- zip file path too long");

    // record the zip file path
    strcpy(s_pszZipFilePath, pszDriver);
    strcat(s_pszZipFilePath, fullPath);
}


bool isResourceExist(const char* pszResName)
{
    bool bRet = false;

    TUChar FilePath[EOS_FILE_MAX_PATH] = {0};
    TUString::StrGBToUnicode(FilePath, (const Char *) pszResName);

    if (strlen(s_pszZipFilePath) != 0)
    {
        // if have set the zip file path,find the resource in the zip file
        unzFile pZipFile = unzOpen(s_pszZipFilePath);
        do 
        {
            CC_BREAK_IF(!pZipFile);

            Int32 nPos = unzLocateFile(pZipFile, pszResName, 1);
            CC_BREAK_IF(nPos != UNZ_OK);

            bRet = true;
            unzClose(pZipFile);
        } while (0);
    }
    else
    {
        // find in the hardware
        if (EOS_IsFileExist(FilePath))
        {
            bRet = true;
        }
    }

    return bRet;
}

const char* getDiffResolutionPath(const char *pszPath)
{
    CCString *pRet = new CCString(pszPath);
    pRet->autorelease();

    do 
    {
        TApplication* pApp = TApplication::GetCurrentApplication();
        CC_BREAK_IF(!pApp);

        // get the Resolution
        int nScreenWidth  = pApp->GetScreenWidth();
        int nScreenHeight = pApp->GetScreenHeight();

        // it's default resolution, do nothing
        CC_BREAK_IF(nScreenWidth == 320 && nScreenHeight == 480);

        if (nScreenWidth == 480 && nScreenHeight == 800)
        {
            // it's WVGA
            CC_BREAK_IF(pRet->m_sString.find("@WVGA") != -1);

            std::string filePathWithoutExtension = pszPath;
            std::string extension = "";
            std::string filePath = pszPath;
            int nExPos = filePath.find_last_of(".");

            if (nExPos != -1)
            {
                filePathWithoutExtension = filePath.substr(0, nExPos);
                extension = filePath.substr(nExPos);
            }

            // new path, add "@WVGA" before the extension
            pRet->m_sString = filePathWithoutExtension + "@WVGA" + extension;

            // not find the resource of new path,use the original path
            if (! isResourceExist(pRet->m_sString.c_str()))
            {
                pRet->m_sString = filePath;
            }
        }
        else
        {
            // not support resolution
            CCAssert(0, "it's not supportted resolution.");
        }
    } while (0);

    return pRet->m_sString.c_str();
}

void CCFileUtils::setResource(const char* pszZipFileName, const char* pszResPath)
{
    if (pszResPath != NULL && pszZipFileName != NULL)
    {
        // record the resource path
        strcpy(s_pszResourcePath, pszResPath);

        // record the zip file path
        setZipFilePath(pszZipFileName);
    }
    else if (pszResPath != NULL)
    {
        // update the zip file path
        updateZipFilePath(pszResPath);

        // record the resource path
        strcpy(s_pszResourcePath, pszResPath);
    }
    else if (pszZipFileName != NULL)
    {
        // record the zip file path
        setZipFilePath(pszZipFileName);
    }
}

const char* CCFileUtils::fullPathFromRelativePath(const char *pszRelativePath)
{
    // if have set the zip file path,return the relative path of zip file
    if (strlen(s_pszZipFilePath) != 0)
    {
        return getDiffResolutionPath(pszRelativePath);
    }

    // get the user data path and append relative path to it
    if (strlen(s_pszResourcePath) == 0)
    {
        const char* pAppDataPath = CCApplication::sharedApplication().getAppDataPath();
        strcpy(s_pszResourcePath, pAppDataPath);
    }

#ifndef _TRANZDA_VM_
    char *pszDriver = "";
#else
    char *pszDriver = "D:/Work7";
#endif

    CCString * pRet = new CCString();
    pRet->autorelease();
    if ((strlen(pszRelativePath) > 1 && pszRelativePath[1] == ':'))
    {
        pRet->m_sString = pszRelativePath;
    }
    else if (strlen(pszRelativePath) > 0 && pszRelativePath[0] == '/')
    {
        pRet->m_sString = pszDriver;
        pRet->m_sString += pszRelativePath;
    }
    else
    {
        pRet->m_sString = pszDriver;
        pRet->m_sString += s_pszResourcePath;
        pRet->m_sString += pszRelativePath;
    }
    return getDiffResolutionPath(pRet->m_sString.c_str());
}
const char *CCFileUtils::fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile)
{
	std::string relativeFile = fullPathFromRelativePath(pszRelativeFile);
	CCString *pRet = new CCString();
	pRet->autorelease();
	pRet->m_sString = relativeFile.substr(0, relativeFile.rfind('/')+1);
	pRet->m_sString += pszFilename;
	return getDiffResolutionPath(pRet->m_sString.c_str());
}

unsigned char* CCFileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{
    unsigned char * pBuffer = NULL;

    do 
    {
        if (0 != s_pszZipFilePath[0])
        {
            // if specify the zip file,load from it first
            pBuffer = getFileDataFromZip(s_pszZipFilePath, pszFileName, pSize);
            CC_BREAK_IF(pBuffer);
        }

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

    if (! pBuffer && getIsPopupNotify())
    {
        std::string title = "Notification";
        std::string msg = "Get data from file(";
        msg.append(pszFileName);
        if (0 != s_pszZipFilePath[0])
        {
            msg.append(") in zip archive(").append(s_pszZipFilePath);
        }
        msg.append(") failed!");

        CCMessageBox(msg.c_str(), title.c_str());
    }

    return pBuffer;
}

void CCFileUtils::setResourcePath(const char *pszResourcePath)
{
    CCAssert(0, "Have not implement!");
}

const char* CCFileUtils::getResourcePath(void)
{
    CCAssert(0, "Have not implement!");
    return NULL;
}

void CCFileUtils::setRelativePath(const char* pszRelativePath)
{
    CCAssert(0, "Have not implement!");
}

NS_CC_END;
