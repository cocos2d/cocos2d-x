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
#ifndef __CC_FILEUTILS_PLATFORM_H__
#define __CC_FILEUTILS_PLATFORM_H__

#include <string>
#include "CCMutableDictionary.h"

NS_CC_BEGIN;

//! @brief  Helper class to handle file operations
class CC_DLL CCFileUtils
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

    /** removes the suffix from a path
     * On RetinaDisplay it will remove the -hd suffix
     * On iPad it will remove the -ipad suffix
     * On iPhone it will remove the (empty) suffix
     Only valid on iOS. Not valid for OS X.
 
     @since v0.99.5
     */
    static std::string& removeSuffixFromFile(std::string& path);

    /**
    @brief   Generate the absolute path of the file.
    @param   pszRelativePath     The relative path of the file.
    @return  The absolute path of the file.
    @warning We only add the ResourcePath before the relative path of the file.
    If you have not set the ResourcePath,the function add "/NEWPLUS/TDA_DATA/UserData/" as default.
    You can set ResourcePath by function void setResourcePath(const char *pszResourcePath);
    */
    static const char* fullPathFromRelativePath(const char *pszRelativePath);

	/** Returns the fullpath of an filename including the resolution of the image.
 
        If in RetinaDisplay mode, and a RetinaDisplay file is found, it will return that path.
        If in iPad mode, and an iPad file is found, it will return that path.
 
        Examples:
 
        * In iPad mode: "image.png" -> "/full/path/image-ipad.png" (in case the -ipad file exists)
        * In RetinaDisplay mode: "image.png" -> "/full/path/image-hd.png" (in case the -hd file exists)
 
        If an iPad file is found, it will set resolution type to kCCResolutioniPad
        If a RetinaDisplay file is found, it will set resolution type to kCCResolutionRetinaDisplay
 
      */
	static const char* fullPathFromRelativePath(const char *pszRelativePath, ccResolutionType *pResolutionType);

    /// @cond
    static const char* fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile);
    /// @endcond

	/** Sets the iPhone RetinaDisplay suffix to load resources.
        By default it is "-hd".
        Only valid on iOS. Not valid for OS X.
 
        @since v1.1
     */
	static void setiPhoneRetinaDisplaySuffix(const char *suffix);

	/** Sets the iPad suffix to load resources.
        By default it is "".
        Only valid on iOS. Not valid for OS X.
 

     */
	static void setiPadSuffix(const char *suffix);

	/** Sets the iPad Retina Display suffix to load resources.
        By default it is "-ipadhd".
        Only valid on iOS. Not valid for OS X.
 
        @since v1.1
     */
	static void setiPadRetinaDisplaySuffix(const char *suffix);

	/** Returns whether or not a given filename exists with the iPad suffix.
        Only available on iOS. Not supported on OS X.
        @since v1.1
    */
	bool iPadFileExistsAtPath(const char *filename);

	/** Returns whether or not a given filename exists with the iPad RetinaDisplay suffix.
        Only available on iOS. Not supported on OS X.
 
     */
	bool iPadRetinaDisplayFileExistsAtPath(const char *filename);

	/** Returns whether or not a given path exists with the iPhone RetinaDisplay suffix.
        Only available on iOS. Not supported on OS X.
        @since v1.1
    */
	bool iPhoneRetinaDisplayFileExistsAtPath(const char *filename);

    /**
    @brief  Set the ResourcePath,we will find resource in this path
    @param pszResourcePath  The absolute resource path
	@warning Don't call this function in android and iOS, it has not effect.
	In android, if you want to read file other than apk, you shoud use invoke getFileData(), and pass the 
	absolute path.
    */
    static void setResourcePath(const char *pszResourcePath);

    /**
    @brief   Generate a CCDictionary pointer by file
    @param   pFileName  The file name of *.plist file
    @return  The CCDictionary pointer generated from the file
    */
    static CCDictionary<std::string, CCObject*> *dictionaryWithContentsOfFile(const char *pFileName);

	/*
	@brief The same meaning as dictionaryWithContentsOfFile(), but it doesn't call autorelease, so the
	       invoker should call release().
	*/
	static CCDictionary<std::string, CCObject*> *dictionaryWithContentsOfFileThreadSafe(const char *pFileName);

	/**
	@brief   Get the writeable path
	@return  The path that can write/read file
	*/
	static std::string getWriteablePath();

    /**
    @brief Set/Get whether pop-up a message box when the image load failed
    */
    static void setIsPopupNotify(bool bNotify);
    static bool getIsPopupNotify();

    ///////////////////////////////////////////////////
    // interfaces on wophone
    ///////////////////////////////////////////////////
    /**
    @brief  Set the resource zip file name
    @param pszZipFileName The relative path of the .zip file
    */
    static void setResource(const char* pszZipFileName);

    ///////////////////////////////////////////////////
    // interfaces on ios
    ///////////////////////////////////////////////////
    static int ccLoadFileIntoMemory(const char *filename, unsigned char **out);
};

class CCFileData
{
public:
    CCFileData(const char* pszFileName, const char* pszMode)
        : m_pBuffer(0)
        , m_uSize(0)
    {
        m_pBuffer = CCFileUtils::getFileData(pszFileName, pszMode, &m_uSize);
    }
    ~CCFileData()
    {
        CC_SAFE_DELETE_ARRAY(m_pBuffer);
    }

    bool reset(const char* pszFileName, const char* pszMode)
    {
        CC_SAFE_DELETE_ARRAY(m_pBuffer);
        m_uSize = 0;
        m_pBuffer = CCFileUtils::getFileData(pszFileName, pszMode, &m_uSize);
        return (m_pBuffer) ? true : false;
    }

    CC_SYNTHESIZE_READONLY(unsigned char *, m_pBuffer, Buffer);
    CC_SYNTHESIZE_READONLY(unsigned long ,  m_uSize,   Size);
};

NS_CC_END;

#endif	// end of __CC_EGLVIEW_PLATFORM_H__
