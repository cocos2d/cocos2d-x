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

#ifndef __PLATFORM_UPHONE_CCFILE_UTILS_H__
#define __PLATFORM_UPHONE_CCFILE_UTILS_H__

#include <string>
#include <ssFile.h>
#include "ccxCommon.h"
#include "NSMutableDictionary.h"
#include "FileUtils.h"

class TBitmap;
class TResourceLib;
struct AppResourceEntry;

typedef struct
{
    const char* ResName;
    int         nResID;
} T_ResourceInfo;

namespace   cocos2d {

class ResourceHandle
{
public:
    ResourceHandle();
    ~ResourceHandle();

    void setResourceEntry(const AppResourceEntry* pResEntry);
    void release();
    const TBitmap* LoadConstBitmap(int nResID);

private:
    TResourceLib* m_pResLib;
};

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

    static const char* getDiffResolutionPath(const char *pszPath);
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

    /**
    @brief Set the Resource Entry
    @param pResEntry The pointer of the Application's ResourceEntry
    */
    static void setResourceEntry(const AppResourceEntry* pResEntry);

    /**
    @brief Set the Resource Info(ResourceName and ResID)
    @param ResInfo Array of T_ResourceInfo,contain all resource names and ids.
    @param nCount  The count of the array elements.
    */
    static void setResourceInfo(const T_ResourceInfo ResInfo[], int nCount);

    /**
    @brief Whether the resource is exist or not.The function find the resource in hardware,if not find,it will find in resource map.
    @param pszResName The name of resource
    @return The return value is true if exist,otherwise return false.
    */
    static bool isResourceExist(const char* pszResName);

    /**
    @brief Get bitmap data from resource map
    @param pszBmpName The name of the bitmap
    @return If can find the name in resource map, return the pointer of the bitmap.Otherwise return NULL
    */
    static const TBitmap* getBitmapByResName(const char* pszBmpName);

    /**
    @brief Set the absolute path of the .zip file which contains all resource files
    @param pszZipPath The absolute path of the .zip file
    */
    static void setResourceZipFile(const char* pszZipPath);

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

    /**
    @brief Get resource file data
    @param[in]  pszFileName The resource file name which contain the path
    @param[in]  pszMode The read mode of the file
    @param[out] pSize If get the file data succeed the it will be the data size,or it will be 0
    @return if success,the pointer of data will be returned,or NULL is returned
    @warning If you get the file data succeed,you must delete it after used.
    */
    static unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize);
};
}//namespace   cocos2d 

#endif // __PLATFORM_UPHONE_CCFILE_UTILS_H__
