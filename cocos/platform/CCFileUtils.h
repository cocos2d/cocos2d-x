/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#include <unordered_map>

#include "platform/CCPlatformMacros.h"
#include "base/ccTypes.h"
#include "base/CCValue.h"
#include "base/CCData.h"

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

/** @~english Helper class to handle file operations.  @~chinese 处理文件操作的通用工具类。*/
class CC_DLL FileUtils
{
public:
    /**@~english
     *  Gets the instance of FileUtils.
     * @~chinese 
     * 获取FileUtils的实例。
     */
    static FileUtils* getInstance();

    /**@~english
     *  Destroys the instance of FileUtils.
     * @~chinese 
     * 销毁FileUtils的实例。
     */
    static void destroyInstance();
    
    /**@~english
     * You can inherit from platform dependent implementation of FileUtils, such as FileUtilsAndroid,
     * and use this function to set delegate, then FileUtils will invoke delegate's implementation.
     * For example, your resources are encrypted, so you need to decrypt it after reading data from
     * resources, then you can implement all getXXX functions, and engine will invoke your own getXX
     * functions when reading data of resources.
     *
     * If you don't want to system default implementation after setting delegate, you can just pass nullptr
     * to this function.
     *
     * @~chinese 
     * 你可以从各个平台的文件工具类实现中继承,例如 FileUtilsAndroid, 然后
     * 使用这个函数来设置代理,然后FileUtils将调用代理的实现。
     * 例如,你的资源是加密的,因此您需要读取数据后对资源进行解密,
     * 然后您可以实现所有getXXX功能,当读取资源数据时，引擎将调用你自己的getXX功能。
     * 
     * 
     * 在设置代理后，如果你不想要系统默认实现的代理,你就可以通过这个函数设置值为nullptr
     * 
     * 
     * @warning @~english It will delete previous delegate
     * @~chinese 它将删除以前的delegate
     * @lua NA
     */
    static void setDelegate(FileUtils *delegate);

    /** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static FileUtils* sharedFileUtils() { return getInstance(); }

    /** @deprecated Use destroyInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static void purgeFileUtils() { destroyInstance(); }

    /**@~english
     *  The destructor of FileUtils.
     * @~chinese 
     * FileUtils的析构函数。
     * @js NA
     * @lua NA
     */
    virtual ~FileUtils();
    
    /**@~english
     *  Purges full path caches.
     * @~chinese 
     * 清除路径缓存。
     */
    virtual void purgeCachedEntries();
    
    /**@~english
     * Gets string from a file.
     * @~chinese 
     * 将一个文件内容读取为字符串。
     */
    virtual std::string getStringFromFile(const std::string& filename);
    
    /**@~english
     * Creates binary data from a file.
     * @~chinese 
     * 将一个文件内容读取为二进制数据。
     *  @return @~english A data object.
     * @~chinese 一个数据对象。
     */
    virtual Data getDataFromFile(const std::string& filename);
    
    /**@~english
     *  Gets resource file data
     *  @~chinese 
     *  获取资源文件数据
     *  @param filename @~english The resource file name which contains the path.
     *             @~chinese 包含路径的资源文件名称。
     *  @param mode @~english The read mode of the file. property like fopen function mode @~chinese 文件的读取模式,属性与fopen模式相同。
     *  @param size @~english If the file read succeeds, it will be the data size, otherwise 0. 
     *               @~chinese 如果文件读取成功,它就是数据大小,否则为0。
     * 
     *  @return @~english Upon success, a pointer to the data is returned, otherwise NULL.
     * @~chinese 在成功时,返回一个指向数据的指针,否则为空。
     *  @warning @~english Recall: you are responsible for calling free() on any Non-NULL pointer returned.
     * @~chinese 记得: 如果返回的指针是非空的，你需要负责调用free函数释放它
     */
    CC_DEPRECATED_ATTRIBUTE virtual unsigned char* getFileData(const std::string& filename, const char* mode, ssize_t *size);

    /**@~english
     *  Gets resource file data from a zip file.
     * @~chinese 
     *  从一个zip文件获取资源文件数据。
     *  @param zipFilePath @~english The resource zip file path.
     *                  @~chinese zip文件的路径。
     *  @param filename @~english The resource file path and name relative to the zip file.
     *                  @~chinese 资源在zip文件中的相对路径。
     *  @param size @~english If the file read operation succeeds, it will be the data size, otherwise 0.
     *              @~chinese 如果文件读取成功,它就是数据大小,否则为0。
     * 
     *  @return @~english Upon success, a pointer to the data is returned, otherwise nullptr.
     * @~chinese 在成功时,返回一个指向数据的指针,否则nullptr。
     *  @warning @~english Recall: you are responsible for calling free() on any Non-nullptr pointer returned.
     * @~chinese 记得:如果返回的指针是非空的，你需要负责调用free函数释放它
     */
    virtual unsigned char* getFileDataFromZip(const std::string& zipFilePath, const std::string& filename, ssize_t *size);

    
    /** @~english Returns the fullpath for a given filename.
     
     First it will try to get a new filename from the "filenameLookup" dictionary.
     If a new filename can't be found on the dictionary, it will use the original filename.
     Then it will try to obtain the full path of the filename using the FileUtils search rules: resolutions, and search paths.
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

     If the new file can't be found on the file system, it will return the parameter filename directly.

     This method was added to simplify multiplatform support. Whether you are using cocos2d-js or any cross-compilation toolchain like StellaSDK or Apportable,
     you might need to load different resources for a given file in the different platforms.

     * @~chinese 对于一个给定的文件名返回完整的文件路径。
     * 
     * 首先它将尝试从文件字典得到一个新文件名，
     * 如果在字典中不能找到新文件名,它将使用原来的文件名。
     * 然后它将尝试对这个要获取的完整路径文件名, 使用文件工具类的搜索规则来查找:分辨率,和搜索路径。
     * 文件搜索是基于数组元素的搜索路径和分辨率目录的顺序来决定的。
     * 
     * 例如:
     * 
     * 我们将两个元素("/mnt/sdcard/", "internal_dir/") 通过 setSearchPaths 函数放入搜索路径集合中
     * 并设置三个元素("resources-ipadhd/", "resources-ipad/", "resources-iphonehd")
     * 通过 setSearchResolutionsOrder 设置到分辨率集合中。这个 “internal_dir” 目录的路径 是相对于根目录的路径是 "Resources/"
     * 
     * 如果我们有一个文件名为'sprite.png',fileLookup字典中的映射包含 `key: sprite.png -> value: sprite.pvr.gz`.
     * 首先,它的文件名将从'sprite.png'变成'sprite.pvr.gz'。然后通过以下几个步骤来搜索'sprite.pvr.gz'文件:
     * 
     * 
            /mnt/sdcard/resources-ipadhd/sprite.pvr.gz      (如果找不到，则查找下一个)
            /mnt/sdcard/resources-ipad/sprite.pvr.gz        (如果找不到，则查找下一个)
            /mnt/sdcard/resources-iphonehd/sprite.pvr.gz    (如果找不到，则查找下一个)
            /mnt/sdcard/sprite.pvr.gz                       (如果找不到，则查找下一个)
            internal_dir/resources-ipadhd/sprite.pvr.gz     (如果找不到，则查找下一个)
            internal_dir/resources-ipad/sprite.pvr.gz       (如果找不到，则查找下一个)
            internal_dir/resources-iphonehd/sprite.pvr.gz   (如果找不到，则查找下一个)
            internal_dir/sprite.pvr.gz                      (如果找不到，则返回 "sprite.png")
     * 
     * 如果这个文件名包含相对路径,像 "gamescene/uilayer/sprite.png",
     * 并在fileLookup字典的映射关系是`key: gamescene/uilayer/sprite.png -> value: gamescene/uilayer/sprite.pvr.gz`.
     * 这个文件搜索顺序将会是:
     * 
     * 
            /mnt/sdcard/gamescene/uilayer/resources-ipadhd/sprite.pvr.gz      (如果找不到，则查找下一个)
            /mnt/sdcard/gamescene/uilayer/resources-ipad/sprite.pvr.gz        (如果找不到，则查找下一个)
            /mnt/sdcard/gamescene/uilayer/resources-iphonehd/sprite.pvr.gz    (如果找不到，则查找下一个)
            /mnt/sdcard/gamescene/uilayer/sprite.pvr.gz                       (如果找不到，则查找下一个)
            internal_dir/gamescene/uilayer/resources-ipadhd/sprite.pvr.gz     (如果找不到，则查找下一个)
            internal_dir/gamescene/uilayer/resources-ipad/sprite.pvr.gz       (如果找不到，则查找下一个)
            internal_dir/gamescene/uilayer/resources-iphonehd/sprite.pvr.gz   (如果找不到，则查找下一个)
            internal_dir/gamescene/uilayer/sprite.pvr.gz                      (如果找不到，则返回 "gamescene/uilayer/sprite.png")
     * 
     * 如果这个新的文件名在文件系统中无法找到,它将直接返回传进参数的文件名。
     * 
     * 这种方法的增加，简化了多平台支持。无论你是使用Cocos2d-JS或任何交叉编译工具链StellaSDK或Apportable等
     * 只要一个给定的文件你都能够在对应不同的平台上加载相应的资源。
     * 
     @since v2.1
     */
    virtual std::string fullPathForFilename(const std::string &filename) const;
    
    /**@~english
     * Loads the filenameLookup dictionary from the contents of a filename.
     * 
     * @~chinese 
     * 通过一个文件中的内容加载filenameLookup字典。
     * 
     * @note @~english The plist file name should follow the format below:
     * 
     * @~chinese plist文件名称应遵循以下格式:
     * 
     * @code
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
     * @endcode
     * @param filename @~english The plist file name.
     *
     * @~chinese plist文件名称。
     * 
     @since v2.1
     * @js loadFilenameLookup
     * @lua loadFilenameLookup
     */
    virtual void loadFilenameLookupDictionaryFromFile(const std::string &filename);
    
    /** @~english
     *  Sets the filenameLookup dictionary.
     *
     * @~chinese 
     * 设置filenameLookup字典。
     * 
     *  @param filenameLookupDict @~english The dictionary for replacing filename.
     * @~chinese 用于替换文件名的字典。
     *  @since v2.1
     */
    virtual void setFilenameLookupDictionary(const ValueMap& filenameLookupDict);
    
    /**@~english
     *  Gets full path from a file name and the path of the relative file.
     * @~chinese 
     * 从一个文件名和相对的路径文件得到完整路径。
     *  @param filename @~english The file name.
     * @~chinese 文件的名字。
     *  @param relativeFile @~english The path of the relative file.
     * @~chinese 相对的路径文件。
     *  @return @~english The full path.
     *          e.g. filename: hello.png, pszRelativeFile: /User/path1/path2/hello.plist
     *               Return: /User/path1/path2/hello.pvr (If there a a key(hello.png)-value(hello.pvr) in FilenameLookup dictionary. )
     *
     * @~chinese 这个给定文件名的完整文件路径。
        例如. filename: hello.png, pszRelativeFile: /User/path1/path2/hello.plist
     *  Return: /User/path1/path2/hello.pvr (如果在FilenameLookup字典中有这个键值对(hello.png)-value(hello.pvr))
     * 
     */
    virtual std::string fullPathFromRelativeFile(const std::string &filename, const std::string &relativeFile);

    /** @~english
     *  Sets the array that contains the search order of the resources.
     *
     * @~chinese 
     * 设置包含资源搜索顺序的数组
     * 
     *  @param searchResolutionsOrder @~english The source array that contains the search order of the resources.
     * @~chinese 这个数组包含了资源搜索顺序
     *  @see getSearchResolutionsOrder(), fullPathForFilename(const char*).
     *  @since v2.1@~english
     *  In js:var setSearchResolutionsOrder(var jsval)
     * @~chinese 
     * js:var setSearchResolutionsOrder(var jsval)
     *  @lua NA
     */
    virtual void setSearchResolutionsOrder(const std::vector<std::string>& searchResolutionsOrder);

    /**@~english
      * Append search order of the resources.
      *
      * @~chinese 
      * 添加的资源搜索顺序。
      * 
      * @see setSearchResolutionsOrder(), fullPathForFilename().
      * @since v2.1
      */
    virtual void addSearchResolutionsOrder(const std::string &order,const bool front=false);
    
    /**@~english
     *  Gets the array that contains the search order of the resources.
     *
     * @~chinese 
     * 获取包含资源的搜索顺序的数组
     * 
     *  @see setSearchResolutionsOrder(const std::vector<std::string>&), fullPathForFilename(const char*).
     *  @since v2.1
     *  @lua NA
     */
    virtual const std::vector<std::string>& getSearchResolutionsOrder() const;
    
    /** @~english
     *  Sets the array of search paths.
     *
     *  You can use this array to modify the search path of the resources.
     *  If you want to use "themes" or search resources in the "cache", you can do it easily by adding new entries in this array.
     *
     * @~chinese 
     * 设置搜索路径的数组。
     * 
     * 您可以使用这个数组修改资源的搜索路径。
     * 如果你想使用缓存中主题或者是资源,你很容易可以做到，只要在数组中添加新的条目就可以了。
     * 
     *  @note @~english This method could access relative path and absolute path.
     *        If the relative path was passed to the vector, FileUtils will add the default resource directory before the relative path.
     *        For instance:
     *            On Android, the default resource root path is "assets/".
     *            If "/mnt/sdcard/" and "resources-large" were set to the search paths vector,
     *            "resources-large" will be converted to "assets/resources-large" since it was a relative path.
     *
     * @~chinese 这个方法既可以访问绝对路径又可以访问相对路径。
     * 如果给集合传递的是一个相对路径，文件工具类会在这个相对路径的前面加上默认的资源目录
     * 例如:
     * 在Android上，默认的资源根路径是 "assets/".
     * 如果把"/mnt/sdcard/" 和"resources-large" 传递到 查找路径的集合中,因为它是一个相对路径，
     * 所以"resources-large" 会被转换成 "assets/resources-large" 
     * 
     *  @param searchPaths @~english The array contains search paths.
     * @~chinese 该数组包含搜索路径。
     *  @see fullPathForFilename(const char*)
     *  @since v2.1@~english
     *  In js:var setSearchPaths(var jsval);
     * @~chinese 
     * js:var setSearchPaths(var jsval);
     *  @lua NA
     */
    virtual void setSearchPaths(const std::vector<std::string>& searchPaths);
    
    /**@~english
     * Set default resource root path.
     * @~chinese 
     * 设置默认资源根路径。
     */
    void setDefaultResourceRootPath(const std::string& path);

    /**@~english
      * Add search path.
      *
     * @~chinese 
     * 添加搜索路径。
     * 
      * @since v2.1
      */
    void addSearchPath(const std::string & path, const bool front=false);
    
    /**@~english
     *  Gets the array of search paths.
     *  
     * @~chinese 
     * 获取数组的搜索路径。
     * 
     *  @return @~english The array of search paths.
     * @~chinese 数组的搜索路径。
     *  @see fullPathForFilename(const char*).
     *  @lua NA
     */
    virtual const std::vector<std::string>& getSearchPaths() const;

    /**@~english
     *  Gets the writable path.
     * @~chinese 
     *  获取可写的路径
     *  @return  @~english The path that can be write/read a file in
     * @~chinese 可以写/读文件的路径
     */
    virtual std::string getWritablePath() const = 0;
    
    /**@~english
     *  Sets writable path.
     * @~chinese 
     * 设置可写的路径。
     */
    virtual void setWritablePath(const std::string& writablePath);

    /**@~english
     *  Sets whether to pop-up a message box when failed to load an image.
     * @~chinese 
     * 设置当图片加载失败的时候是否弹出一个消息框
     */
    virtual void setPopupNotify(bool notify);
    
    /** @~english Checks whether to pop up a message box when failed to load an image. 
     * @~chinese 检查当图片加载失败的时候是否弹出一个消息框
     *  @return @~english True if pop up a message box when failed to load an image, false if not.
     * @~chinese 如果图片加载失败的时候会弹出一个消息框则返回true，否则返回false.
     */
    virtual bool isPopupNotify() const;

    /**@~english
     *  Converts the contents of a file to a ValueMap.
     * @~chinese 
     * 将一个文件的内容转换为ValueMap。
     *  @param filename @~english The filename of the file to gets content.
     * @~chinese 要获取内容的对应文件的文件名。
     *  @return @~english ValueMap of the file contents.
     * @~chinese 文件的内容。
     *  @note @~english This method is used internally.
     * @~chinese 该方法在内部使用。
     */
    virtual ValueMap getValueMapFromFile(const std::string& filename);

  /**   @~english Converts the contents of a file to a ValueMap.
    *   @~chinese 把文件的数据转换成ValueMap
    *   @note @~english This method is used internally.
    *   @~chinese 该方法在内部使用。
    */
    virtual ValueMap getValueMapFromData(const char* filedata, int filesize);

    /** @~english Write a ValueMap to a plist file.
    *   @~chinese 将ValueMap,写入到文件中
    * @param dict @~english the data which want to write into file
    *             @~chinese 需要写入文件的数据。
    * @param fullPath @~english file fullpath
    *             @~chinese 文件完整路径
    * @note @~english This method is used internally.
    *   @~chinese 该方法在内部使用。
    */
    virtual bool writeToFile(ValueMap& dict, const std::string& fullPath);

    /**
     *  write a string into a file
     *
     * @param dataStr the string want to save
     * @param fullPath The full path to the file you want to save a string
     * @return bool True if write success
     */
    virtual bool writeStringToFile(std::string dataStr, const std::string& fullPath);


    /**
     * write Data into a file
     *
     *@param retData the data want to save
     *@param fullPath The full path to the file you want to save a string
     *@return bool
     */
    virtual bool writeDataToFile(Data retData, const std::string& fullPath);

    /**
    * write ValueMap into a plist file
    *
    *@param dict the ValueMap want to save
    *@param fullPath The full path to the file you want to save a string
    *@return bool
    */
    virtual bool writeValueMapToFile(ValueMap& dict, const std::string& fullPath);

    /**
    * write ValueVector into a plist file
    *
    *@param vecData the ValueVector want to save
    *@param fullPath The full path to the file you want to save a string
    *@return bool
    */
    virtual bool writeValueVectorToFile(ValueVector vecData, const std::string& fullPath);

    /**@~english
    * Windows fopen can't support UTF-8 filename
    * Need convert all parameters fopen and other 3rd-party libs
    *
     * @~chinese 
     * Windows fopen不能支持utf - 8文件名
     * 需要使用第三方库将fopen的所有参数进行转换
     * 
    * @param filenameUtf8 @~english std::string name file for convertation from utf-8
     * @~chinese 需要转换成的utf-8文件的文件名
    * @return @~english std::string ansi filename in current locale
     * @~chinese 当前语言下标准ansi的文件名
    */
    virtual std::string getSuitableFOpen(const std::string& filenameUtf8) const;
    
    /**@~english Converts the contents of a file to a ValueVector.
    * @~chinese 将文件转换成ValueVector
    * @note @~english This method is used internally.
    *   @~chinese 该方法在内部使用。
    */
    virtual ValueVector getValueVectorFromFile(const std::string& filename);
    
    /**@~english
     *  Checks whether a file exists.
     *
     * @~chinese 
     * 检查一个文件是否存在。
     * 
     *  @note @~english If a relative path was passed in, it will be inserted a default root path at the beginning.
     * @~chinese 如果传递进来的参数是一个相对路径，将会在其开头加上一个默认的根路径
     *  @param filename @~english The path of the file, it could be a relative or absolute path.
     * @~chinese 文件的路径。可以是绝对路径，也可以是相对路径
     *  @return @~english True if the file exists, false if not.
     * @~chinese 如果文件存在返回true，否则返回false
     */
    virtual bool isFileExist(const std::string& filename) const;

    /**
    *  Gets filename extension is a suffix (separated from the base filename by a dot) in lower case.
    *  Examples of filename extensions are .png, .jpeg, .exe, .dmg and .txt.
    *  @param filePath The path of the file, it could be a relative or absolute path.
    *  @return suffix for filename in lower case or empty if a dot not found.
    */
    virtual std::string getFileExtension(const std::string& filePath) const;

    /**@~english
     *  Checks whether the path is an absolute path.
     *
     * @~chinese 
     * 检查路径是不是绝对路径。
     * 
     *  @note @~english On Android, if the parameter passed in is relative to "assets/", this method will treat it as an absolute path.
     *        Also on Blackberry, path starts with "app/native/Resources/" is treated as an absolute path.
     *
     * @~chinese 在Android平台上，如果传递进来的参数是相对于"assets/"，这个方法就会把它当成绝对路径
     * 在blackBarry平台上，以"app/native/Resources/"开头的路径被看成绝对路径
     * 
     *  @param path @~english The path that needs to be checked.
     * @~chinese 需要检查的路径
     *  @return @~english True if it's an absolute path, false if not.
     * @~chinese 如果是绝对路径返回true，否则返回false
     */
    virtual bool isAbsolutePath(const std::string& path) const;
    
    /**@~english
     *  Checks whether the path is a directory.
     *
     * @~chinese 
     * 检查一个路径是否是目录。
     * 
     *  @param dirPath @~english The path of the directory, it could be a relative or an absolute path.
     * @~chinese 目录的路径。可以是绝对路径，也可以是相对路径
     *  @return @~english True if the directory exists, false if not.
     * @~chinese 如果目录存在返回true，否则返回false
     */
    virtual bool isDirectoryExist(const std::string& dirPath) const;
    
    /**@~english
     *  Creates a directory.
     *
     * @~chinese 
     * 创建一个目录。
     * 
     *  @param dirPath @~english The path of the directory, it must be an absolute path.
     * @~chinese 目录的路径,它必须是一个绝对路径。
     *  @return @~english True if the directory have been created successfully, false if not.
     * @~chinese 如果成功创建了目录返回true,如果创建失败返回false
     */
    virtual bool createDirectory(const std::string& dirPath);
    
    /**@~english
     *  Removes a directory.
     *
     * @~chinese 
     * 删除一个目录。
     * 
     *  @param dirPath  @~english The path of the directory, it must be an absolute path.
     * @~chinese 目录的路径,它必须是一个绝对路径。
     *  @return @~english True if the directory have been removed successfully, false if not.
     * @~chinese 如果成功删除了目录返回true,如果删除失败返回false
     */
    virtual bool removeDirectory(const std::string& dirPath);
    
    /**@~english
     *  Removes a file.
     *
     * @~chinese 
     * 删除一个文件。
     * 
     *  @param filepath @~english The path of the file, it must be an absolute path.
     * @~chinese 文件的路径,它必须是一个绝对路径。
     *  @return @~english True if the file have been removed successfully, false if not.
     * @~chinese 如果成功删除了文件返回true,如果删除失败返回false
     */
    virtual bool removeFile(const std::string &filepath);
    
    /**@~english
     *  Renames a file under the given directory.
     *
     * @~chinese 
     * 重命名一个给定目录下的文件。
     * 
     *  @param path     @~english The parent directory path of the file, it must be an absolute path.
     * @~chinese 文件的父目录的路径,它必须是一个绝对路径。
     *  @param oldname  @~english The current name of the file.
     * @~chinese 当前文件的名称。
     *  @param name     @~english The new name of the file.
     * @~chinese 新文件的名称。
     *  @return @~english True if the file have been renamed successfully, false if not.
     * @~chinese 如果成功重命名了文件返回true,如果重命名失败返回false
     */
    virtual bool renameFile(const std::string &path, const std::string &oldname, const std::string &name);

    /**
     *  Renames a file under the given directory.
     *
     *  @param oldfullpath  The current fullpath of the file. Includes path and name.
     *  @param newfullpath  The new fullpath of the file. Includes path and name.
     *  @return True if the file have been renamed successfully, false if not.
     */
    virtual bool renameFile(const std::string &oldfullpath, const std::string &newfullpath);

    /**@~english
     *  Retrieve the file size.
     *
     * @~chinese 
     * 获取文件大小。
     * 
     *  @note @~english If a relative path was passed in, it will be inserted a default root path at the beginning.
     * @~chinese 如果传递进来的参数是一个相对路径，将会在其开头加上一个默认的根路径
     *  @param filepath @~english The path of the file, it could be a relative or absolute path.
     * @~chinese 文件的路径,它可能是一个相对或绝对路径。
     *  @return @~english The file size.
     * @~chinese 文件大小。
     */
    virtual long getFileSize(const std::string &filepath);

    /** @~english Returns the full path cache.  @~chinese 返回完整路径缓存。*/
    const std::unordered_map<std::string, std::string>& getFullPathCache() const { return _fullPathCache; }

protected:
    /**@~english
     *  The default constructor.
     * @~chinese 
     * 默认构造函数。
     */
    FileUtils();
    
    /**@~english
     *  Initializes the instance of FileUtils. It will set _searchPathArray and _searchResolutionsOrderArray to default values.
     *
     * @~chinese 
     * FileUtils的初始化实例。它将会设置_searchPathArray和_searchResolutionsOrderArray为默认值。
     * 
     *  @note @~english When you are porting Cocos2d-x to a new platform, you may need to take care of this method.
     *        You could assign a default value to _defaultResRootPath in the subclass of FileUtils(e.g. FileUtilsAndroid). Then invoke the FileUtils::init().
     * @~chinese 当你将Cocos2d-x移植到一个新的平台,您可能需要关注这个方法。
     * 你可以指定一个默认值的子类_defaultResRootPath FileUtils(如。FileUtilsAndroid)。然后调用FileUtils::init()。
     *  @return @~english true if successed, otherwise it returns false.
     *
     * @~chinese 如果成功返回true,否则返回false。
     * 
     */
    virtual bool init();
    
    /**@~english
     *  Gets the new filename from the filename lookup dictionary.
     *  It is possible to have a override names.
     * @~chinese 
     * 从文件名查找词典中获取新的文件名
     * 它可能有一个重定义的名字
     *  @param filename @~english The original filename.
     * @~chinese 原来的文件名。
     *  @return @~english The new filename after searching in the filename lookup dictionary.
     *          If the original filename wasn't in the dictionary, it will return the original filename.
     * @~chinese 从文件名查找词典中返回的新的文件名
     * 如果原始文件名不在查找词典中，则返回原始的文件名
     */
    virtual std::string getNewFilename(const std::string &filename) const;
    
    /**@~english
     *  Checks whether a file exists without considering search paths and resolution orders.
     * @~chinese 
     * 在不考虑查找路径和解析顺序的情况下，检查文件是否存在
     *  @param filename @~english The file (with absolute path) to look up for
     * @~chinese 需要查找的文件名（需要绝对路径）
     *  @return @~english Returns true if the file found at the given absolute path, otherwise returns false
     * @~chinese 传入的文件（绝对路径）如果在字典中存在,返回true,否则返回false
     */
    virtual bool isFileExistInternal(const std::string& filename) const = 0;
    
    /**@~english
     *  Checks whether a directory exists without considering search paths and resolution orders.
     * @~chinese 
     * 在不考虑查找路径和解析顺序的情况下，检查目录是否存在
     *  @param dirPath @~english The directory (with absolute path) to look up for
     * @~chinese 需要查找的目录(绝对路径)
     *  @return @~english Returns true if the directory found at the given absolute path, otherwise returns false
     * @~chinese 传入的目录（绝对路径）如果在字典中存在,返回true,否则返回false
     */
    virtual bool isDirectoryExistInternal(const std::string& dirPath) const;
    
    /**@~english
     *  Gets full path for filename, resolution directory and search path.
     *
     * @~chinese 
     * 以文件名、分辨率目录和查找路径为参数获取完整路径
     * 
     *  @param filename @~english The file name.
     * @~chinese 文件的名字。
     *  @param resolutionDirectory @~english The resolution directory.
     * @~chinese 分辨率目录。
     *  @param searchPath @~english The search path.
     * @~chinese 搜索路径。
     *  @return @~english The full path of the file. It will return an empty string if the full path of the file doesn't exist.
     * @~chinese 返回文件的完整路径。如果文件的完整路径不存在，则返回一个空的string对象
     */
    virtual std::string getPathForFilename(const std::string& filename, const std::string& resolutionDirectory, const std::string& searchPath) const;
    
    /**@~english
     *  Gets full path for the directory and the filename.
     *
     * @~chinese 
     * 以目录和文件名为参数获取完整路径
     * 
     *  @note @~english Only iOS and Mac need to override this method since they are using
     *        `[[NSBundle mainBundle] pathForResource: ofType: inDirectory:]` to make a full path.
     *        Other platforms will use the default implementation of this method.
     * @~chinese 只有在IOS和Mac平台上需要重载这个方法，因为这两个平台上他们使用`[[NSBundle mainBundle] pathForResource: ofType: inDirectory:]` 
     * 来获得完整路径。在其他的平台上则是使用这个方法的默认实现
     *  @param directory @~english The directory contains the file we are looking for.
     * @~chinese 包含我们将要查找文件的目录
     *  @param filename  @~english The name of the file.
     * @~chinese 文件名
     *  @return @~english The full path of the file, if the file can't be found, it will return an empty string.
     * @~chinese 返回文件的完整路径，如果查找不到此文件，则放回一个空的string对象
     */
    virtual std::string getFullPathForDirectoryAndFilename(const std::string& directory, const std::string& filename) const;
    
    /** @~english Dictionary used to lookup filenames based on a key.
     *  It is used internally by the following methods:
     *
     *  std::string fullPathForFilename(const char*);
     *
     * @~chinese 基于键值查找文件名的Dictionary变量
     * 它是在内部被以下方法使用到：
     * 
     * std::string fullPathForFilename(const char*);
     * 
     *  @since v2.1
     */
    ValueMap _filenameLookupDict;
    
    /** @~english
     *  The vector contains resolution folders.
     *  The lower index of the element in this vector, the higher priority for this resolution directory.
     * @~chinese 
     * 包含分辨率文件夹的集合
     * 在集合中的索引值越小，在分辨率目录中的优先级就越高
     */
    std::vector<std::string> _searchResolutionsOrderArray;
    
    /**@~english
     * The vector contains search paths.
     * The lower index of the element in this vector, the higher priority for this search path.
     * @~chinese 
     * 包含了搜索路径的集合。
     * 在集合中的索引值越小，在查找路径的优先级就越高
     */
    std::vector<std::string> _searchPathArray;
    
    /**@~english
     *  The default root path of resources.
     *  If the default root path of resources needs to be changed, do it in the `init` method of FileUtils's subclass.
     *  For instance:
     *  On Android, the default root path of resources will be assigned with "assets/" in FileUtilsAndroid::init().
     *  Similarly on Blackberry, we assign "app/native/Resources/" to this variable in FileUtilsBlackberry::init().
     * @~chinese 
     * 资源的默认的根路径
     * 如果要改变这个资源的默认的根路径，我们可以在FileUtils子类的init方法中完成
     * 例如:
     * 在Android平台上，资源的默认根路径会在FileUtilsAndroid::init()中被赋值为"assets/" 
     * 在Blackberry平台上，我们在FileUtilsBlackberry::init()中把"app/native/Resources/"赋给这个变量。
     */
    std::string _defaultResRootPath;
    
    /**@~english
     *  The full path cache. When a file is found, it will be added into this cache. 
     *  This variable is used for improving the performance of file search.
     * @~chinese 
     * 完整路径的缓存。在文件被查找到之后，会把文件的完整路径添加到这个缓存中。
     * 这个变量是用来提高文件查找性能的。
     */
    mutable std::unordered_map<std::string, std::string> _fullPathCache;
    
    /**@~english
     * Writable path.
     * @~chinese 
     * 可写的路径。
     */
    std::string _writablePath;

    /**@~english
     *  The singleton pointer of FileUtils.
     * @~chinese 
     * singleton 文件工具类的单例的指针。
     */
    static FileUtils* s_sharedFileUtils;

};

// end of support group
/** @} */

NS_CC_END

#endif    // __CC_FILEUTILS_H__
