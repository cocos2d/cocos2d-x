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

#include "FileUtils.h"
#include <stdio.h>
#include "CCCocos2dDefine.h"
#include "support/zip_support/unzip.h"
#include <string>
#include <assert.h>

namespace cocos2d {

unsigned char* FileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{
    unsigned char * Buffer = NULL;

    do 
    {
        // read the file from hardware
        FILE *fp = fopen(pszFileName, pszMode);
        CC_BREAK_IF(!fp);

        fseek(fp,0,SEEK_END);
        *pSize = ftell(fp);
        fseek(fp,0,SEEK_SET);
        Buffer = new unsigned char[*pSize];
        fread(Buffer,sizeof(unsigned char), *pSize,fp);
        fclose(fp);
    } while (0);

    return Buffer;
}


unsigned char* FileUtils::getFileDataFromZip(const char* pszZipFilePath, const char* pszFileName, unsigned long * pSize)
{
    unsigned char * pBuffer = NULL;
    unzFile pFile = NULL;
    *pSize = 0;

    do 
    {
        CC_BREAK_IF(!pszZipFilePath || !pszFileName);
        CC_BREAK_IF(strlen(pszZipFilePath) == 0);

        pFile = unzOpen(pszZipFilePath);
        CC_BREAK_IF(!pFile);

        int nRet = unzLocateFile(pFile, pszFileName, 1);
        CC_BREAK_IF(UNZ_OK != nRet);

        char szFilePathA[260];
        unz_file_info FileInfo;
        nRet = unzGetCurrentFileInfo(pFile, &FileInfo, szFilePathA, sizeof(szFilePathA), NULL, 0, NULL, 0);
        CC_BREAK_IF(UNZ_OK != nRet);

        nRet = unzOpenCurrentFile(pFile);
        CC_BREAK_IF(UNZ_OK != nRet);

        pBuffer = new unsigned char[FileInfo.uncompressed_size];
        int nSize = 0;
		nSize = unzReadCurrentFile(pFile, pBuffer, FileInfo.uncompressed_size);
        CCAssert(nSize == 0 || nSize == FileInfo.uncompressed_size, "the file size is wrong");

        *pSize = FileInfo.uncompressed_size;
        unzCloseCurrentFile(pFile);
    } while (0);

    if (pFile)
    {
        unzClose(pFile);
    }

    return pBuffer;
}

const char* FileUtils::ccRemoveHDSuffixFromFile(const char* path)
{
#if CC_IS_RETINA_DISPLAY_SUPPORTED

    if( CC_CONTENT_SCALE_FACTOR() == 2 )
    {
        std::string curPath = path;
        int pos = curPath.rfind("/");
        std::string fileName = curPath.substr(pos + 1);

        std::string filePath = "";
        if (-1 != pos)
        {
            filePath = curPath.substr(0, pos);
        }

        int suffixPos = fileName.rfind(CC_RETINA_DISPLAY_FILENAME_SUFFIX);
        if (-1 != suffixPos)
        {
            fileName.replace(pos, strlen(CC_RETINA_DISPLAY_FILENAME_SUFFIX), "");
        }

        std::string result = filePath + fileName;
        return result.c_str();
    }

#endif // CC_IS_RETINA_DISPLAY_SUPPORTED

    return path;
}

} //namespace   cocos2d 
