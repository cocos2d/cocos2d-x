#include "FileUtils.h"
#include "zip_support/unzip.h"
#include <string>
#include <cassert>

#define BREAK_IF(cond)  if (cond) break;

namespace CocosDenshion {

static char s_ResourcePath[EOS_FILE_MAX_PATH] = {0};
static char s_ZipFilePath[EOS_FILE_MAX_PATH]  = {0};
static char s_AppDataPath[EOS_FILE_MAX_PATH]  = {0};

unsigned char* getFileDataFromZip(const char* pszZipFilePath, const char* pszFileName, unsigned long * pSize);
void fullPathFromRelativePath(const char *pszRelativePath, char* fullPath);
void updateZipFilePath(const char* pResPath);
void setZipFilePath(const char* pZipFileName);
const char* getDataPath();

bool FileUtils::isFileExisted(const char* pFilePath)
{
    bool bRet = false;

    if (strlen(s_ZipFilePath) != 0)
    {
        // if have set the zip file path,find the resource in the zip file
        unzFile pZipFile = unzOpen(s_ZipFilePath);
        do 
        {
            BREAK_IF(!pZipFile);

            Int32 nPos = unzLocateFile(pZipFile, pFilePath, 1);
            BREAK_IF(nPos != UNZ_OK);

            bRet = true;
            unzClose(pZipFile);
        } while (0);
    }
    else
    {
        char fullPath[EOS_FILE_MAX_PATH];
        fullPathFromRelativePath(pFilePath, fullPath);

        if (strlen(fullPath) > 0)
        {
            TUChar FilePath[EOS_FILE_MAX_PATH] = {0};
            TUString::StrGBToUnicode(FilePath, (const Char *) fullPath);

            // find in the hardware
            if (EOS_IsFileExist(FilePath))
            {
                bRet = true;
            }
        }
    }

    return bRet;
}

void FileUtils::setResource(const char* pszResPath, const char* pszZipFileName)
{
    if (pszResPath != NULL && pszZipFileName != NULL)
    {
        // record the resource path
        strcpy(s_ResourcePath, pszResPath);

        // record the zip file path
        setZipFilePath(pszZipFileName);
    }
    else if (pszResPath != NULL)
    {
        // update the zip file path
        updateZipFilePath(pszResPath);

        // record the resource path
        strcpy(s_ResourcePath, pszResPath);
    }
    else if (pszZipFileName != NULL)
    {
        // record the zip file path
        setZipFilePath(pszZipFileName);
    }
}

unsigned char* FileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{
    unsigned char * pBuffer = NULL;

    do 
    {
        if (strlen(s_ZipFilePath) != 0)
        {
            // if specify the zip file,load from it first
            pBuffer = getFileDataFromZip(s_ZipFilePath, pszFileName, pSize);
            BREAK_IF(pBuffer);
        }
        
        // read the file from hardware
        char fullPath[EOS_FILE_MAX_PATH] = {0};
        fullPathFromRelativePath(pszFileName, fullPath);

        BREAK_IF(strlen(fullPath) <= 0);
        FILE *fp = fopen(fullPath, pszMode);
        BREAK_IF(!fp);

        fseek(fp,0,SEEK_END);
        *pSize = ftell(fp);
        fseek(fp,0,SEEK_SET);
        pBuffer = new unsigned char[*pSize];
        fread(pBuffer,sizeof(unsigned char), *pSize,fp);
        fclose(fp);
    } while (0);

    return pBuffer;
}

////////////////////////////////////////
//
// tool functions
//
////////////////////////////////////////
unsigned char* getFileDataFromZip(const char* pszZipFilePath, const char* pszFileName, unsigned long * pSize)
{
    unsigned char * pBuffer = NULL;
    unzFile pFile = NULL;
    *pSize = 0;

    do 
    {
        BREAK_IF(!pszZipFilePath || !pszFileName);
        BREAK_IF(strlen(pszZipFilePath) == 0);

        pFile = unzOpen(pszZipFilePath);
        BREAK_IF(!pFile);

        int nRet = unzLocateFile(pFile, pszFileName, 1);
        BREAK_IF(UNZ_OK != nRet);

        char szFilePathA[260];
        unz_file_info FileInfo;
        nRet = unzGetCurrentFileInfo(pFile, &FileInfo, szFilePathA, sizeof(szFilePathA), NULL, 0, NULL, 0);
        BREAK_IF(UNZ_OK != nRet);

        nRet = unzOpenCurrentFile(pFile);
        BREAK_IF(UNZ_OK != nRet);

        pBuffer = new unsigned char[FileInfo.uncompressed_size];
        int nSize = unzReadCurrentFile(pFile, pBuffer, FileInfo.uncompressed_size);
        assert(nSize == 0 || nSize == FileInfo.uncompressed_size);

        *pSize = FileInfo.uncompressed_size;
        unzCloseCurrentFile(pFile);
    } while (0);

    if (pFile)
    {
        unzClose(pFile);
    }

    return pBuffer;
}

void fullPathFromRelativePath(const char *pszRelativePath, char* fullPath)
{
    // if have set the zip file path,return the relative path of zip file
    if (strlen(s_ZipFilePath) != 0)
    {
        if (strlen(pszRelativePath) < EOS_FILE_MAX_PATH)
        {
            strcpy(fullPath, pszRelativePath);
        }
        return;
    }

    // get the user data path and append relative path to it
    if (strlen(s_ResourcePath) == 0)
    {
        const char* pAppDataPath = getDataPath();
        strcpy(s_ResourcePath, pAppDataPath);
    }

#ifndef _TRANZDA_VM_
    char *pszDriver = "";
#else
    char *pszDriver = "D:/Work7";
#endif

    std::string pRet;
    if ((strlen(pszRelativePath) > 1 && pszRelativePath[1] == ':'))
    {
        pRet = pszRelativePath;
    }
    else if (strlen(pszRelativePath) > 0 && pszRelativePath[0] == '/')
    {
        pRet = pszDriver;
        pRet += pszRelativePath;
    }
    else
    {
        pRet = pszDriver;
        pRet += s_ResourcePath;
        pRet += pszRelativePath;
    }

    if (strlen(pRet.c_str()) < EOS_FILE_MAX_PATH &&
        strlen(pRet.c_str()) > 0)
    {
        strcpy(fullPath, pRet.c_str());
    }

    return;
}

void updateZipFilePath(const char* pResPath)
{
    if (! strlen(s_ZipFilePath))
    {
        return;
    }

    std::string strTemp = s_ZipFilePath;
    int nPos = std::string::npos;

    // find the path need br replaced
    std::string ResPath;
    if (strlen(s_ResourcePath))
    {
        ResPath = s_ResourcePath;
    }
    else
    {
        ResPath = getDataPath();
    }

    // replace the resource path in s_ZipFilePath
    nPos = strTemp.find(ResPath.c_str());
    if (nPos != std::string::npos)
    {
        strTemp.replace(nPos, ResPath.length(), pResPath);
        memset(s_ZipFilePath, 0, sizeof(char) * EOS_FILE_MAX_PATH);
        strcpy(s_ZipFilePath, strTemp.c_str());
    }
}

void setZipFilePath(const char* pZipFileName)
{
    // get the full path of zip file
    char fullPath[EOS_FILE_MAX_PATH] = {0};
    if (strlen(s_ResourcePath))
    {
        strcpy(fullPath, s_ResourcePath);
    }
    else
    {
        const char* pAppDataPath = getDataPath();
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
        TApplication::GetCurrentApplication()->MessageBox(szText,NULL,WMB_OK);
        return;
    }

#ifndef _TRANZDA_VM_
    char *pszDriver = "";
#else
    char *pszDriver = "D:/Work7";
#endif

    // record the zip file path
    strcpy(s_ZipFilePath, pszDriver);
    strcat(s_ZipFilePath, fullPath);
}

const char* getDataPath()
{
    if (strlen(s_AppDataPath))
    {
        return s_AppDataPath;
    }

    do 
    {
        TUChar AppID[EOS_FILE_MAX_PATH] = {0};
        UInt32 nCmdType = 0;
        Int32  nRet = SS_AppRequest_GetAppName(AppID, &nCmdType);
        BREAK_IF(nRet < 0);

        TUChar AppPath[EOS_FILE_MAX_PATH] = {0};
        SS_GetApplicationPath(AppID, SS_APP_PATH_TYPE_EXECUTABLE, AppPath);
        TUString::StrUnicodeToStrUtf8((Char*) s_AppDataPath, AppPath);
    } while (0);

    return s_AppDataPath;
}

} // end of namespace CocosDenshion
