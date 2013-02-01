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
#ifndef __CC_FILEUTILS_H__
#define __CC_FILEUTILS_H__

#include <string>
#include <vector>
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

//! @brief  The super class for CCFileUtils
class CC_DLL CCFileUtils : public TypeInfo
{
public:
    /**
     *  Returns an unique ID for this class.
     *  @note It's only used for JSBindings now.
     *  @return The unique ID for this class.
     */
    virtual long getClassTypeInfo() {
		static const long id = cocos2d::getHashCodeByString(typeid(cocos2d::CCFileUtils).name());
		return id;
    }
    
    /**
     *  Gets the instance of CCFileUtils.
     */
    static CCFileUtils* sharedFileUtils();
    
    /**
     *  Destroys the instance of CCFileUtils.
     */
    static void purgeFileUtils();
    
    /**
     *  The destructor of CCFileUtils.
     */
    virtual ~CCFileUtils();
    
    /**
     *  Purges the file searching cache.
     *
     *  @note It should be invoked after the resources were updated.
     *        For instance, in the CocosPlayer sample, every time you run application from CocosBuilder,
     *        All the resources will be downloaded to the writable folder, before new js app launchs,
     *        this method should be invoked to clean the file search cache.
     */
    virtual void purgeCachedEntries();
    
    /**
    @brief Get resource file data
    @param[in]  pszFileName The resource file name which contains the path.
    @param[in]  pszMode The read mode of the file.
    @param[out] pSize If the file read operation succeeds, it will be the data size, otherwise 0.
    @return Upon success, a pointer to the data is returned, otherwise NULL.
    @warning Recall: you are responsible for calling delete[] on any Non-NULL pointer returned.
    */
    virtual unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize);

    /**
    @brief Get resource file data from a zip file.
    @param[in]  pszFileName The resource file name which contains the relative path of the zip file.
    @param[out] pSize If the file read operation succeeds, it will be the data size, otherwise 0.
    @return Upon success, a pointer to the data is returned, otherwise NULL.
    @warning Recall: you are responsible for calling delete[] on any Non-NULL pointer returned.
    */
    virtual unsigned char* getFileDataFromZip(const char* pszZipFilePath, const char* pszFileName, unsigned long * pSize);

    
    /** Returns the fullpath for a given filename.
     
     First it will try to get a new filename from the "filenameLookup" dictionary.
     If a new filename can't be found on the dictionary, it will use the original filename.
     Then it will try to obtain the full path of the filename using the CCFileUtils search rules: resolutions, and search paths.
     The file search is based on the array element order of search paths and resolution directories.
     
     For instance:

     	We set two elements("/mnt/sdcard/", "internal_dir/") to search paths vector by setSearchPaths,
     	and set three elements("resources-ipadhd/", "resources-ipad/", "resources-iphonehd")
     	to resolutions vector by setSearchResolutionsOrder. The "internal_dir" is relative to "Resources/".

		If we have a file named 'sprite.png', the mapping in fileLookup dictionary contains `key: sprite.png -> value: sprite.pvr.gz`.
     	Firstly, it will replace 'sprite.png' with 'sprite.pvr.gz', then searching the file sprite.pvr.gz as follows:

     	    /mnt/sdcard/resources-ipadhd/sprite.pvr.gz      (if not found, search next)
     	    /mnt/sdcard/resources-ipad/sprite.pvr.gz        (if not found, search next)
     	    /mnt/sdcard/resources-iphonehd/sprite.pvr.gz    (if not found, search next)
     	    /mnt/sdcard/sprite.pvr.gz                       (if not found, search next)
     	    internal_dir/resources-ipadhd/sprite.pvr.gz     (if not found, search next)
     	    internal_dir/resources-ipad/sprite.pvr.gz       (if not found, search next)
     	    internal_dir/resources-iphonehd/sprite.pvr.gz   (if not found, search next)
     	    internal_dir/sprite.pvr.gz                      (if not found, return "sprite.png")

        If the filename contains relative path like "gamescene/uilayer/sprite.png",
        and the mapping in fileLookup dictionary contains `key: gamescene/uilayer/sprite.png -> value: gamescene/uilayer/sprite.pvr.gz`.
        The file search order will be:

     	    /mnt/sdcard/gamescene/uilayer/resources-ipadhd/sprite.pvr.gz      (if not found, search next)
     	    /mnt/sdcard/gamescene/uilayer/resources-ipad/sprite.pvr.gz        (if not found, search next)
     	    /mnt/sdcard/gamescene/uilayer/resources-iphonehd/sprite.pvr.gz    (if not found, search next)
     	    /mnt/sdcard/gamescene/uilayer/sprite.pvr.gz                       (if not found, search next)
     	    internal_dir/gamescene/uilayer/resources-ipadhd/sprite.pvr.gz     (if not found, search next)
     	    internal_dir/gamescene/uilayer/resources-ipad/sprite.pvr.gz       (if not found, search next)
     	    internal_dir/gamescene/uilayer/resources-iphonehd/sprite.pvr.gz   (if not found, search next)
     	    internal_dir/gamescene/uilayer/sprite.pvr.gz                      (if not found, return "gamescene/uilayer/sprite.png")

     If the new file can't be found on the file system, it will return the parameter pszFileName directly.
     
     This method was added to simplify multiplatform support. Whether you are using cocos2d-js or any cross-compilation toolchain like StellaSDK or Apportable,
     you might need to load different resources for a given file in the different platforms.

     @since v2.1
     */
    virtual std::string fullPathForFilename(const char* pszFileName);
    
    /**
     * Loads the filenameLookup dictionary from the contents of a filename.
     * 
     * @note The plist file name should follow the format below:
     * <?xml version="1.0" encoding="UTF-8"?>
     * <!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
     * <plist version="1.0">
     * <dict>
     *     <key>filenames</key>
     *     <dict>
     *         <key>sounds/click.wav</key>
     *         <string>sounds/click.caf</string>
     *         <key>sounds/endgame.wav</key>
     *         <string>sounds/endgame.caf</string>
     *         <key>sounds/gem-0.wav</key>
     *         <string>sounds/gem-0.caf</string>
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
    virtual void loadFilenameLookupDictionaryFromFile(const char* filename);
    
    /** 
     *  Sets the filenameLookup dictionary.
     *
     *  @param pFilenameLookupDict The dictionary for replacing filename.
     *  @since v2.1
     */
    virtual void setFilenameLookupDictionary(CCDictionary* pFilenameLookupDict);
    
    /**
     *  Gets full path from a file name and the path of the reletive file.
     *  @param pszFilename The file name.
     *  @param pszRelativeFile The path of the relative file.
     *  @return The full path.
     *          e.g. pszFilename: hello.png, pszRelativeFile: /User/path1/path2/hello.plist
     *               Return: /User/path1/path2/hello.pvr (If there a a key(hello.png)-value(hello.pvr) in FilenameLookup dictionary. )
     *
     */
    virtual const char* fullPathFromRelativeFile(const char *pszFilename, const char *pszRelativeFile);

    /** 
     *  Sets the array that contains the search order of the resources.
     *
     *  @param searchResolutionsOrder The source array that contains the search order of the resources.
     *  @see getSearchResolutionsOrder(), fullPathForFilename().
     *  @since v2.1
     */
    virtual void setSearchResolutionsOrder(const std::vector<std::string>& searchResolutionsOrder);
    
    /**
     *  Gets the array that contains the search order of the resources.
     *
     *  @see setSearchResolutionsOrder(), fullPathForFilename().
     *  @since v2.1
     */
    virtual const std::vector<std::string>& getSearchResolutionsOrder();
    
    /** 
     *  Sets the array of search paths.
     *  You can use this array to modify the search path of the resources.
     *  If you want to use "themes" or search resources in the "cache", you can do it easily by adding new entries in this array.
     *
     *  @note This method could access relative path and absolute path.
     *        If the relative path was passed to the vector, CCFileUtils will add the default resource directory before the relative path.
     *        For instance:
     *        	On Android, the default resource root path is "assets/".
     *        	If "/mnt/sdcard/" and "resources-large" were set to the search paths vector,
     *        	"resources-large" will be converted to "assets/resources-large" since it was a relative path.
     *
     *  @param searchPaths The array contains search paths.
     *  @see fullPathForFilename()
     *  @since v2.1
     */
    virtual void setSearchPaths(const std::vector<std::string>& searchPaths);
    
    /**
     *  Gets the array of search paths.
     *  
     *  @return The array of search paths.
     *  @see fullPathForFilename().
     */
    virtual const std::vector<std::string>& getSearchPaths();

    /**
    @brief   Gets the writeable path.
    @return  The path that can write/read file
    */
    virtual std::string getWriteablePath() = 0;
    
    /**
     *  Checks whether file exists.
     *
     *  @param strFullpathOfFile The full path of file.
     */
    virtual bool isFileExist(const std::string& strFullpathOfFile) = 0;
    
    /**
     *  Checks whether the path is an absolute path.
     *
     *  @param strPath The path that needs to be checked.
     */
    virtual bool isAbsolutePath(const std::string& strPath);
    
    
    /**
    @brief Set/Get whether pop-up a message box when the image load failed
    */
    virtual void setPopupNotify(bool bNotify);
    virtual bool isPopupNotify();

protected:
    CCFileUtils();
    
    virtual bool init();
    
    virtual std::string getNewFilename(const char* pszFileName);
    
    /**
     *  Get Full path for filename, resolution directory and search path.
     *
     *  @param filename The file name.
     *  @param resolutionDirectory The resolution directory.
     *  @param searchPath The search path.
     *  @param retFullPath The return value of full path.
     *  @return Whether the file exists.
     */
    virtual std::string getPathForFilename(const std::string& filename, const std::string& resolutionDirectory, const std::string& searchPath);
    
    virtual std::string getFullPathForDirectoryAndFilename(const std::string& strDirectory, const std::string& strFilename);
    
    /** Dictionary used to lookup filenames based on a key.
     It is used internally by the following methods:
     
     const char* fullPathForFilename(const char* )key;
     
     @since v2.1
     */
    CCDictionary* m_pFilenameLookupDict;
    
    std::vector<std::string> m_searchResolutionsOrderArray;
    std::vector<std::string> m_searchPathArray;
    std::string m_strDefaultResRootPath;
    
    static CCFileUtils* s_sharedFileUtils;
};

// end of platform group
/// @}

NS_CC_END

#endif    // __CC_FILEUTILS_H__
