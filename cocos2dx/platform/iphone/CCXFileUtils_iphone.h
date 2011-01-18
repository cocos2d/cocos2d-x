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

#ifndef __PLATFORM_IPHONE_CCFILE_UTILS_H__
#define __PLATFORM_IPHONE_CCFILE_UTILS_H__

#include <string>
#include "ccxCommon.h"
#include "NSMutableDictionary.h"
#include "FileUtils.h"
namespace   cocos2d {

//! @brief  Helper class to handle file operations
class CCX_DLL CCFileUtils : public FileUtils
{
public:

    /**
    @brief   Generate the absolute path of the file.
    @param   pszRelativePath     The relative path of the file.
    @return  The absolute path of the file.
    @warning We only add the ResourcePath before the relative path of the file.
             If you have not set the ResourcePath,the function add "/NEWPLUS/TDA_DATA/UserData/" as default.
             You can set ResourcePath by function void setResourcePath(const char *pszResourcePath);
    */
    static const char* fullPathFromRelativePath(const char *pszRelativePath);

    /// @cond
    static const char* fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile);
    /// @endcond

    /**
    @brief   Generate a NSDictionary pointer by file
    @param   pFileName  The file name of *.plist file
    @return  The NSDictionary pointer generated from the file
    */
    static NSDictionary<std::string, NSObject*> *dictionaryWithContentsOfFile(const char *pFileName);

    /**
    @brief  Set the ResourcePath,we will find resource in this path
    @param pszResourcePath  The absolute resource path
    */
    static void setResourcePath(const char *pszResourcePath);
    
    /** loads a file into memory.
     the caller should release the allocated buffer.
     
     @returns the size of the allocated buffer
     @since v0.99.5
     */
	static int ccLoadFileIntoMemory(const char *filename, unsigned char **out);
    
     /** removes the HD suffix from a path
     
     @returns NSString * without the HD suffix
     @since v0.99.5
     */
	static const char *ccRemoveHDSuffixFromFile( const char *path );
	
    static const char* getResourcePath(void);
};
}//namespace   cocos2d 

#endif // __PLATFORM_IPHONE_CCFILE_UTILS_H__
