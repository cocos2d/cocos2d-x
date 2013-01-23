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
#include "CCPlatformMacros.h"
#include "ccTypes.h"
#include "ccTypeInfo.h"

NS_CC_BEGIN

class CCDictionary;
class CCArray;
/**
 * @addtogroup platform
 * @{
 */

//! @brief  Helper class to handle file operations
class CC_DLL CCFileUtils : public TypeInfo
{
public:
    virtual long getClassTypeInfo() {
		static const long id = cocos2d::getHashCodeByString(typeid(cocos2d::CCFileUtils).name());
		return id;
    }
    
    static CCFileUtils* sharedFileUtils();
    static void purgeFileUtils();

    void purgeCachedEntries();
    /**
    @brief Get resource file data
    @param[in]  pszFileName The resource file name which contains the path.
    @param[in]  pszMode The read mode of the file.
    @param[out] pSize If the file read operation succeeds, it will be the data size, otherwise 0.
    @return Upon success, a pointer to the data is returned, otherwise NULL.
    @warning Recall: you are responsible for calling delete[] on any Non-NULL pointer returned.
    */
    unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize);

    /**
    @brief Get resource file data from a zip file.
    @param[in]  pszFileName The resource file name which contains the relative path of the zip file.
    @param[out] pSize If the file read operation succeeds, it will be the data size, otherwise 0.
    @return Upon success, a pointer to the data is returned, otherwise NULL.
    @warning Recall: you are responsible for calling delete[] on any Non-NULL pointer returned.
    */
    unsigned char* getFileDataFromZip(const char* pszZipFilePath, const char* pszFileName, unsigned long * pSize);

    /**
    @brief   Generate the absolute path of the file.
    @param   pszRelativePath     The relative path of the file.
    @return  The absolute path of the file.
    @warning We only add the ResourcePath before the relative path of the file.
    @deprecated Please use fullPathForFilename instead.
    If you have not set the ResourcePath, the function appends "/NEWPLUS/TDA_DATA/UserData/" by default.
    You can set ResourcePath with void setResourcePath(const char *pszResourcePath);
    */
    CC_DEPRECATED_ATTRIBUTE const char* fullPathFromRelativePath(const char *pszRelativePath);
    
    /** Returns the fullpath for a given filename.
     
     First it will try to get a new filename from the "filenameLookup" dictionary. If a new filename can't be found on the dictionary, it will use the original filename.
     Then it will try obtain the full path of the filename using the CCFileUtils search rules:  resources directory
     
     If the filename can't be found on resource directory(e.g. Resources/iphone-hd), it will go back to the root of asset folder(e.g. Resources/) to find the filename.
     
     If the filename can't be found on the file system, it will return the filename directly.
     
     This method was added to simplify multiplatform support. Whether you are using cocos2d-js or any cross-compilation toolchain like StellaSDK or Apportable,
     you might need to load differerent resources for a given file in the different platforms.
     
     Examples:
     
     * In iOS: "image.png" -> "image.pvr" -> "/full/path/res_dir/image.pvr"
     * In Android: "image.png" -> "image.png" -> "/full/path/res_dir/image.png"
     
     @since v2.1
     */
    const char* fullPathForFilename(const char* filename);
    
    /**
     * Loads the filenameLookup dictionary from the contents of a filename.
     * 
     * @note The plist file name should follow the format below:
     * <?xml version="1.0" encoding="UTF-8"?>
     * <!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
     * <plist version="1.0">
     * <dict>
     *     <key>ios</key>
     *     <dict>
     *         <key>sounds/click.wav</key>
     *         <string>sounds/click.caf</string>
     *         <key>sounds/endgame.wav</key>
     *         <string>sounds/endgame.caf</string>
     *         <key>sounds/gem-0.wav</key>
     *         <string>sounds/gem-0.caf</string>
     *     </dict>
     *     <key>android</key>
     *     <dict>
     *         <key>sounds/click.wav</key>
     *         <string>sounds/click.ogg</string>
     *         <key>sounds/endgame.wav</key>
     *         <string>sounds/endgame.ogg</string>
     *         <key>sounds/gem-0.wav</key>
     *         <string>sounds/gem-0.ogg</string>
     *     </dict>
     *     <key>metadata</key>
     *     <dict>
     *         <key>version</key>
     *         <integer>1</integer>
     *     </dict>
     * </dict>
     * </plist>
     *
     * @param filename The plist file name.
     *
     @since v2.1
     */
    void loadFilenameLookupDictionaryFromFile(const char* filename);
    
    /** Loads the filenameLookup dictionary from the contents of a filename.
     
     @since v2.1
     */
    void setFilenameLookupDictionary(CCDictionary* pFilenameLookupDict);
    
    /// @cond
    const char* fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile);
    /// @endcond

    /**
     @brief  Set the resource directory; we will find resources relative to this directory.
     @param pszDirectoryName  Relative path to root.
     @deprecated Please use setSearchPath instead.
    */
    CC_DEPRECATED_ATTRIBUTE void setResourceDirectory(const char *pszDirectoryName);

    /** Array that contains the search order of the resources based for the device.
     By default it will try to load resources in the following order until one is found:
     - On iPad HD: iPad HD resources, iPad resources, resources not associated with any device
     - On iPad: iPad resources, resources not associated with any device
     - On iPhone 5 HD: iPhone 5 HD resources, iPhone HD resouces, iPhone 5 resources, iPhone resources, resources not associated with any device
     - On iPhone HD: iPhone HD resources, iPhone resouces, resources not associated with any device
     - On iPhone: iPhone resources, resources not associated with any device
     
     - On Mac HD: Mac HD resources, Mac resources, resources not associated with any device
     - On Mac: Mac resources, resources not associated with any device
     
     If the property "enableiPhoneResourcesOniPad" is enabled, it will also search for iPhone resources if you are in an iPad.
     
     @since v2.1
     */
    void setSearchResolutionsOrder(CCArray* pSearchResolutionsOrder);
    CCArray* getSearchResolutionsOrder();
    
    /** Array of search paths.
     You can use this array to modify the search path of the resources.
     If you want to use "themes" or search resources in the "cache", you can do it easily by adding new entries in this array.
     
     By default it is an array with only the "" (empty string) element.
     
     @since v2.1
     */
    void setSearchPath(CCArray* pSearchPaths);
    CCArray* getSearchPath();
    
    /**
    @brief  Get the resource directory
    */
    const char* getResourceDirectory();

    /**
    @brief   Get the writeable path
    @return  The path that can write/read file
    */
    std::string getWriteablePath();

    /**
    @brief Set/Get whether pop-up a message box when the image load failed
    */
    void setPopupNotify(bool bNotify);
    bool isPopupNotify();
    
protected:
    CCFileUtils(void)
    : m_pFilenameLookupDict(NULL)
    , m_pSearchResolutionsOrderArray(NULL)
    , m_pSearchPathArray(NULL)
    {
    }
    
    bool init();
    
    std::string getNewFilename(const char* pszFileName);
    std::string getPathForFilename(const std::string& filename, const std::string& resourceDirectory, const std::string& searchPath);
    
    std::string m_obDirectory;
    
    /** Dictionary used to lookup filenames based on a key.
     It is used internally by the following methods:
     
     const char* fullPathForFilename(const char* )key;
     
     @since v2.1
     */
    CCDictionary* m_pFilenameLookupDict;
    
    CCArray* m_pSearchResolutionsOrderArray;
    CCArray* m_pSearchPathArray;
};

// end of platform group
/// @}

NS_CC_END

#endif    // __CC_FILEUTILS_PLATFORM_H__
