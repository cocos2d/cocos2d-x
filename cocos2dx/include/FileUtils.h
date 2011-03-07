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

#ifndef __SUPPORT_FILE_SUPPORT_FILEUTILS_H__
#define __SUPPORT_FILE_SUPPORT_FILEUTILS_H__

#include "ccxString.h"

namespace cocos2d {

class CC_DLL FileUtils
{
public:
    /**
    @brief Get resource file data
    @param[in]  pszFileName The resource file name which contain the path
    @param[in]  pszMode The read mode of the file
    @param[out] pSize If get the file data succeed the it will be the data size,or it will be 0
    @return if success,the pointer of data will be returned,or NULL is returned
    @warning If you get the file data succeed,you must delete it after used.
    */
    static unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize);

    /**
    @brief Get resource file data from zip file
    @param[in]  pszFileName The resource file name which contain the relative path of zip file
    @param[out] pSize If get the file data succeed the it will be the data size,or it will be 0
    @return if success,the pointer of data will be returned,or NULL is returned
    @warning If you get the file data succeed,you must delete it after used.
    */
    static unsigned char* getFileDataFromZip(const char* pszZipFilePath, const char* pszFileName, unsigned long * pSize);

    /** removes the HD suffix from a path
    @returns const char * without the HD suffix
    @since v0.99.5
    */
    static ccxString& ccRemoveHDSuffixFromFile(ccxString& path);
};

} // namespace cocos2d

#endif // __SUPPORT_FILE_SUPPORT_FILEUTILS_H__
