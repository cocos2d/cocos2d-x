#include "FileUtils.h"
#include "zip_support/unzip.h"
#include <string>
#include <cassert>

#define BREAK_IF(cond)  if (cond) break;

static char s_ResourcePath[MAX_PATH] = {0};
static char s_ZipFilePath[MAX_PATH]  = {0};

unsigned char* getFileDataFromZip(const char* pszZipFilePath, const char* pszFileName, unsigned long * pSize);
void fullPathFromRelativePath(const char *pszRelativePath, char* fullPath);

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
        char fullPath[MAX_PATH];
        fullPathFromRelativePath(pFilePath, fullPath);

        if (strlen(fullPath) > 0)
        {
            TUChar FilePath[MAX_PATH] = {0};
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

void FileUtils::setResourcePath(const char *pszResourcePath)
{
    assert(pszResourcePath);
    strcpy(s_ResourcePath, pszResourcePath);
}

void FileUtils::setResourceZipFile(const char* pszZipPath)
{
    // if the zip file not exist,use message box to warn developer
    TUChar pszTmp[MAX_PATH] = {0};
    TUString::StrGBToUnicode(pszTmp, (const Char*) pszZipPath);
    Boolean bExist = EOS_IsFileExist(pszTmp);
    if (!bExist)
    {
        std::string strErr = "zip file ";
        strErr += pszZipPath;
        strErr += " not exist!";
        TUChar szText[MAX_PATH] = { 0 };
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
    strcat(s_ZipFilePath, pszZipPath);
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
        char fullPath[MAX_PATH] = {0};
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
        if (strlen(pszRelativePath) < MAX_PATH)
        {
            strcpy(fullPath, pszRelativePath);
        }
        return;
    }

    // get the user data path and append relative path to it
    if (strlen(s_ResourcePath) == 0)
    {
        const TUChar *pszTmp = EOS_GetSpecialPath(EOS_FILE_SPECIAL_PATH_USER_DATA);
        TUString::StrUnicodeToStrUtf8((Char*) s_ResourcePath, pszTmp);
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

    if (strlen(pRet.c_str()) < MAX_PATH &&
        strlen(pRet.c_str()) > 0)
    {
        strcpy(fullPath, pRet.c_str());
    }

    return;
}
