/****************************************************************************
 Copyright (c) 2010-2013 cocos2d-x.org
 
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

#include "CCZipFile.h"
#include "ccMacros.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN

static const std::string emptyFilename("");

CCZipFile *CCZipFile::create(const char *zipFilename)
{
    CCZipFile *zip = new CCZipFile();
    if (zip->initWithFilename(zipFilename))
    {
        zip->autorelease();
        return zip;
    }
    else
    {
        delete zip;
        return NULL;
    }
}

CCZipFile *CCZipFile::createWithBuffer(const void* buffer, uLong size)
{
    CCZipFile *zip = new CCZipFile();
    if (zip->initWithBuffer(buffer, size))
    {
        zip->autorelease();
        return zip;
    }
    else
    {
        delete zip;
        return NULL;
    }
}

bool CCZipFile::initWithFilename(const char *zipFilename)
{
    if (!zipFilename || strlen(zipFilename) == 0) return false;

    m_zipFile = unzOpen(zipFilename);
    if (!m_zipFile) return false;
    
    return true;
}

bool CCZipFile::initWithBuffer(const void *buffer, uLong size)
{
    if (!buffer || size == 0) return false;

    m_zipFile = unzOpenBuffer(buffer, size);
    if (!m_zipFile) return false;

    return true;
}

CCZipFile::~CCZipFile(void)
{
    close();
}

const std::string CCZipFile::getFirstFilename(void)
{
    if (unzGoToFirstFile(m_zipFile) != UNZ_OK) return emptyFilename;
    std::string path;
    unz_file_info info;
    getCurrentFileInfo(&path, &info);
    return path;
}

const std::string CCZipFile::getNextFilename(void)
{
    if (unzGoToNextFile(m_zipFile) != UNZ_OK) return emptyFilename;
    std::string path;
    unz_file_info info;
    getCurrentFileInfo(&path, &info);
    return path;
}

unsigned char* CCZipFile::getFileData(const char *filename, unsigned long *filesize)
{
    unsigned char *buffer = NULL;
    *filesize = 0;
    
    do 
    {
        int ret = unzLocateFile(m_zipFile, filename, 1);
        CC_BREAK_IF(UNZ_OK != ret);

        std::string path;
        unz_file_info info;
        CC_BREAK_IF(UNZ_OK != getCurrentFileInfo(&path, &info));
        
        ret = unzOpenCurrentFile(m_zipFile);
        CC_BREAK_IF(UNZ_OK != ret);
        
        buffer = new unsigned char[info.uncompressed_size];
        int size = 0;
        size = unzReadCurrentFile(m_zipFile, buffer, info.uncompressed_size);
        CCAssert(size == 0 || size == (int)info.uncompressed_size, "the file size is wrong");
        
        *filesize = info.uncompressed_size;
        unzCloseCurrentFile(m_zipFile);
    } while (0);
    
    return buffer;
}

void CCZipFile::close(void)
{
    if (m_zipFile)
    {
        unzClose(m_zipFile);
        m_zipFile = NULL;
    }
}

int CCZipFile::getCurrentFileInfo(std::string *filename, unz_file_info *info)
{
    char path[FILENAME_MAX + 1];
    int ret = unzGetCurrentFileInfo(m_zipFile, info, path, sizeof(path), NULL, 0, NULL, 0);
    if (ret != UNZ_OK)
    {
        *filename = emptyFilename;
    }
    else
    {
        filename->assign(path);
    }
    return ret;
}

NS_CC_END
