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

#include "base/CCPlatformMacros.h"
#include "base/ccTypes.h"
#include "base/CCValue.h"
#include "base/CCData.h"

#include <string>
#include <vector>
#include <unordered_map>

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

//! @brief  处理文件操作的协助类
class CC_DLL FileUtils
{
public:
    /**
     *  获取 FileUtils的实例
     */
    static FileUtils* getInstance();

    /**
     *  销毁FileUtils的实例
     */
    static void destroyInstance();

    /** @deprecated 使用getInstance()代替*/
    CC_DEPRECATED_ATTRIBUTE static FileUtils* sharedFileUtils() { return getInstance(); }

    /** @deprecated 使用destroyInstance() 代替 */
    CC_DEPRECATED_ATTRIBUTE static void purgeFileUtils() { destroyInstance(); }

    /**
     *  FileUtils的析构函数
     * @js NA
     * @lua NA
     */
    virtual ~FileUtils();
    
    /**
     *  清理文件查找缓存
     *
     *  @note 它应该在资源更新之后被调用。
     *        例如：在CocosPlayer这个示例中，每次你从CocosBuilder运行程序的时候，
     * 	      所有的资源都会下载到可写的文件夹里面。
     * 	      在js程序运行之前，这个方法应该被调用来清空文件查找缓存
     *       
     */
    virtual void purgeCachedEntries();
    
    /**
     *  通过文件名获得文件内容，返回string类型
     */
    virtual std::string getStringFromFile(const std::string& filename);
    
    /**
     *  创建文件内容的二进制数据
     *  @return 返回一个数据对象.
     */
    virtual Data getDataFromFile(const std::string& filename);
    
    /**
     *  获取资源文件数据
     *
     *  @param[in]  filename 包含查找路径的资源文件的文件名
     *  @param[in]  pszMode 文件的读取模式
     *  @param[out] pSize 如果文件读取成功，这个值就是数据的大小，否则就是零
     *  @return 如果成功，则返回数据指针，否则返回NULL
     *  @warning 注意：你应该对返回的非空指针调用free()函数负责
     */
    CC_DEPRECATED_ATTRIBUTE virtual unsigned char* getFileData(const std::string& filename, const char* mode, ssize_t *size);

    /**
     *  从zip文件中获取资源文件数据
     *
     *  @param[in]  filename 包含zip文件的相对路径的资源文件的文件名
     *  @param[out] size 如果文件读取成功，这个值就是数据的大小，否则就是零
     *  @return 如果成功，则返回数据指针，否则返回 nullptr.
     *  @warning 注意：你应该对返回的非空指针调用free()函数负责
     */
    virtual unsigned char* getFileDataFromZip(const std::string& zipFilePath, const std::string& filename, ssize_t *size);

    
    /** 返回给定的文件名的完整路径
    
     首先我们试着在“filenameLookup”词典中获得新的文件名。
     如果找不到新的文件名，则还是用原来的文件名。
     然后尝试使用FileUtils 的查找规则：resolutions, and search paths来获得该文件名的完整路径。
     文件查找是在数组中存放的查找路径的元素顺序和解析目录的基础上实现的。
  
     
     例如：
     
     	我们通过setSearchPaths给存放查找路径的vector设置两个元素（"/mnt/sdcard/", "internal_dir/"），
     	并通过setSearchResolutionsOrder给存放解析顺序的vector设置三个元素（"resources-ipadhd/", "resources-ipad/", "resources-iphonehd"）
	"internal_dir"是"Resources/"下的文件
     
     	如果我们有一个名为‘sprite.png’的文件，并且在文件查找词典中包含key为sprite.png、value为sprite.pvr.gz的键值对。
     	那么就会用'sprite.pvr.gz'代替'sprite.png'，然后按照下面的顺序查找文件sprite.pvr.gz：

     	    /mnt/sdcard/resources-ipadhd/sprite.pvr.gz      (如果找不到，则查找下一个)
     	    /mnt/sdcard/resources-ipad/sprite.pvr.gz        (如果找不到，则查找下一个)
     	    /mnt/sdcard/resources-iphonehd/sprite.pvr.gz    (如果找不到，则查找下一个)
     	    /mnt/sdcard/sprite.pvr.gz                       (如果找不到，则查找下一个)
     	    internal_dir/resources-ipadhd/sprite.pvr.gz     (如果找不到，则查找下一个)
     	    internal_dir/resources-ipad/sprite.pvr.gz       (如果找不到，则查找下一个)
     	    internal_dir/resources-iphonehd/sprite.pvr.gz   (如果找不到，则查找下一个)
     	    internal_dir/sprite.pvr.gz                      (如果找不到，则返回 "sprite.png")

        如果文件名包含像"gamescene/uilayer/sprite.png"的相对路径，
        并且文件查找词典中包含key为gamescene/uilayer/sprite.png、value为gamescene/uilayer/sprite.pvr.gz的键值对，
        那么将按下面的顺序查找文件：

     	    /mnt/sdcard/gamescene/uilayer/resources-ipadhd/sprite.pvr.gz      (如果找不到，则查找下一个)
     	    /mnt/sdcard/gamescene/uilayer/resources-ipad/sprite.pvr.gz        (如果找不到，则查找下一个)
     	    /mnt/sdcard/gamescene/uilayer/resources-iphonehd/sprite.pvr.gz    (如果找不到，则查找下一个)
     	    /mnt/sdcard/gamescene/uilayer/sprite.pvr.gz                       (如果找不到，则查找下一个)
     	    internal_dir/gamescene/uilayer/resources-ipadhd/sprite.pvr.gz     (如果找不到，则查找下一个)
     	    internal_dir/gamescene/uilayer/resources-ipad/sprite.pvr.gz       (如果找不到，则查找下一个)
     	    internal_dir/gamescene/uilayer/resources-iphonehd/sprite.pvr.gz   (如果找不到，则查找下一个)
     	    internal_dir/gamescene/uilayer/sprite.pvr.gz                      (如果找不到，则返回 "gamescene/uilayer/sprite.png")
     	    
     如果在文件系统中找不到新文件，就会直接返回文件名的那个参数。
     这个方法添加了跨平台的支持。你使用的无论是cocos2d-js还是其他的像StellaSDK 和 Apportable一样的跨平台编译工具链，
     对于不同平台下的给定的文件，你也许需要加载不同的资源。
     @since v2.1
     */
    virtual std::string fullPathForFilename(const std::string &filename);
    
    /**
     * 通过文件名加载文件查找词典。
     * 
     * @note plist文件应该遵循如下的格式：
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
     * @param filename plist文件名
     *
     @since v2.1
     * @js loadFilenameLookup
     * @lua loadFilenameLookup
     */
    virtual void loadFilenameLookupDictionaryFromFile(const std::string &filename);
    
    /** 
     *  设置文件查找词典
     *
     *  @param pFilenameLookupDict 代替文件名的词典
     *  @since v2.1
     */
    virtual void setFilenameLookupDictionary(const ValueMap& filenameLookupDict);
    
    /**
     *  通过文件名和文件的湘桂路径获取完整路径
     *  @param filename 文件名
     *  @param pszRelativeFile 文件的相对路径
     *  @return 完整路径
     *          例如：文件名: hello.png, pszRelativeFile: /User/path1/path2/hello.plist
     *               返回: /User/path1/path2/hello.pvr （如果有key为hello.png、value为hello.pvr的键值对） 
     * 
     */
    virtual std::string fullPathFromRelativeFile(const std::string &filename, const std::string &relativeFile);

    /** 
     * 设置包含资源查找路径的array
     *
     *  @param searchResolutionsOrder 包含资源查找顺序的原数组
     *  @see getSearchResolutionsOrder(void), fullPathForFilename(const char*).
     *  @since v2.1
     *  In js:var setSearchResolutionsOrder(var jsval)
     *  @lua NA
     */
    virtual void setSearchResolutionsOrder(const std::vector<std::string>& searchResolutionsOrder);

    /**
      * 添加资源的查找顺序
      *
      * @see setSearchResolutionsOrder(), fullPathForFilename().
      * @since v2.1
      */
    virtual void addSearchResolutionsOrder(const std::string &order);
    
    /**
     *  获取包含资源查找顺序的array
     *
     *  @see setSearchResolutionsOrder(const std::vector<std::string>&), fullPathForFilename(const char*).
     *  @since v2.1
     *  @lua NA
     */
    virtual const std::vector<std::string>& getSearchResolutionsOrder();
    
    /** 
     *  设置一组查找路径
     * 
     *  你可以用这个数组去修改资源的查找路径
     *如果你想使用缓存中主题或者是资源，你可以在这个数组中添加新的成员（资源的入口地址）
     *  @note 这个方法既可以访问绝对路径又可以访问相对路径。
     * 	      如果给vector传递的是一个相对路径，FileUtils会在这个相对路径的前面加上默认的资源目录
     *        例如：
     *        在Android上，默认的资源根路径是 "assets/".
     *        	如果把"/mnt/sdcard/" 和"resources-large" 传递到 查找路径的vector中,因为它是一个相对路径，
     * 	        所以"resources-large" 会被转换成 "assets/resources-large" 
     *
     *  @param searchPaths 包含查找路径的array
     *  @see fullPathForFilename(const char*)
     *  @since v2.1
     *  In js:var setSearchPaths(var jsval);
     *  @lua NA
     */
    virtual void setSearchPaths(const std::vector<std::string>& searchPaths);
    
    /**
      * 添加查找路径
      *
      * @since v2.1
      */
    void addSearchPath(const std::string & path);
    
    /**
     *  获取一组查找路径
     *  
     *  @return 返回查找路径的数组
     *  @see fullPathForFilename(const char*).
     *  @lua NA
     */
    virtual const std::vector<std::string>& getSearchPaths() const;

    /**
     *  获取可写的路径
     *  @return  返回一个可以写入或读取文件的路径
     */
    virtual std::string getWritablePath() const = 0;
    
    /**
     *  检查文件是否存在
     *
     *  @note 如果传递进来的参数是一个相对路径，将会在其开头加上一个默认的根路径
     *  @param strFilePath 文件的路径。可以使绝对路径，也可以是相对路径
     *  @return 如果文件存在返回true，否则返回false
     */
    virtual bool isFileExist(const std::string& filename) const;
    
    /**
     *  检查路径是不是绝对路径
     *
     *  @note 在Android平台上，如果传递进来的参数是相对于"assets/"，这个方法就会把它当成绝对路径
     * 	      在blackBarry平台上，以"app/native/Resources/"开头的路径被看成绝对路径
     *
     *  @param strPath 需要检查的路径
     *  @return 如果是绝对路径返回true，否则返回false
     */
    virtual bool isAbsolutePath(const std::string& path) const;
    
    
    /**
     * 设置或获得当图片加载失败的时候是否弹出一个消息框
     */
    virtual void setPopupNotify(bool notify);
    virtual bool isPopupNotify();

    /**
     *  把文件的内容转换成ValueMap
     *  @note 这是个内部调用的函数
     */
    virtual ValueMap getValueMapFromFile(const std::string& filename);
    
    /**
     *  把ValueMap写到一个plist文件中
     *  @note 这是个内部调用的函数
     */
    virtual bool writeToFile(ValueMap& dict, const std::string& fullPath);
    
    /**
     *  Converts the contents of a file to a ValueVector.
     *  @note This method is used internally.
     */
    virtual ValueVector getValueVectorFromFile(const std::string& filename);

    /**返回完整路径的缓存 */
    const std::unordered_map<std::string, std::string>& getFullPathCache() const { return _fullPathCache; }

protected:
    /**
     *  默认构造函数.
     */
    FileUtils();
    
    /**
     *  初始化FileUtils实例. set _searchPathArray and _searchResolutionsOrderArray 将被赋予默认的值
     *
     *  @note 当你把Cocos2d-x移植到一个新的平台，你要注意这个方法。
     * 	      你可以在FileUtils的子类中（如：FileUtilsAndroid）给value to _defaultResRootPath赋一个默认值，然后调用FileUtils::init().
     *  @return 如果成功则返回true，否则返回false
     *
     */
    virtual bool init();
    
    /**
     *  从文件名查找词典中获取新的文件名
     * 它可能有一个重写的名字
     *  @param filename 原始文件名
     *  @return 从文件名查找词典中返回的新的文件名
     *         如果原始文件名不在查找词典中，则返回原始的文件名
     */
    virtual std::string getNewFilename(const std::string &filename) const;
    
    /**
     *  在不考虑查找路径和解析顺序的情况下，检查文件是否存在
     */
    virtual bool isFileExistInternal(const std::string& filename) const = 0;
    
    /**
     *  以文件名、解析目录和查找路径为参数获取完整路径
     *
     *  @param filename 文件名
     *  @param resolutionDirectory 解析目录
     *  @param searchPath 查找路径
     *  @return 返回文件的完整路径。如果文件的完整路径不存在，则返回一个空的string对象
     */
    virtual std::string getPathForFilename(const std::string& filename, const std::string& resolutionDirectory, const std::string& searchPath);
    
    /**
     *  以目录和文件名为参数获取完整路径
     *
     *  @note 只有在IOS和Mac平台上需要重载这个方法，因为这两个平台上他们使用`[[NSBundle mainBundle] pathForResource: ofType: inDirectory:]` 
     * 	      来获得完整路径。在其他的平台上则是使用这个方法的默认实现
     *  @param strDirectory 包含我们将要查找文件的目录
     *  @param strFilename  文件名
     *  @return 返回文件的完整路径，如果查找不到此文件，则放回一个空的string对象
     */
    virtual std::string getFullPathForDirectoryAndFilename(const std::string& directory, const std::string& filename);
    
    
    /**基于键值查找文件名的Dictionary变量
     * 常下面的这些方法中使用：
     *
     *  std::string fullPathForFilename(const char*);
     *
     *  @since v2.1
     */
    ValueMap _filenameLookupDict;
    
    /** 
     * 包含分辨率文件夹的vector对象
     *  在vector中的索引值越小，对应的分辨率从目录的优先级就越高
     */
    std::vector<std::string> _searchResolutionsOrderArray;
    
    /**
     * 包含查找路径的vector变量
     * 在vector中的索引值越小，对应的查找路径的优先级就越高
     */
    std::vector<std::string> _searchPathArray;
    
    /**
     *  资源的默认的根路径
     * 如果要改变这个资源的默认的根路径，我们可以在FileUtils子类的init方法中完成
     * 例如：
     * 在Android平台上，资源的默认根路径会在FileUtilsAndroid::init()中被赋值为"assets/" 
     * 在Blackberry平台上，我们在FileUtilsBlackberry::init()中把"app/native/Resources/"赋给这个变量。
     */
    std::string _defaultResRootPath;
    
    /**
     * 完整路径的缓存。在文件被查找到之后，会把文件的完整路径添加到这个缓存中。
     * 这个变量是用来提高文件查找性能的。
     */
    std::unordered_map<std::string, std::string> _fullPathCache;
    
    /**
     *   FileUtils的单例指针
     */
    static FileUtils* s_sharedFileUtils;
    
};

// end of platform group
/// @}

NS_CC_END

#endif    // __CC_FILEUTILS_H__
