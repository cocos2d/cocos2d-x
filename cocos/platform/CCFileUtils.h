/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include <type_traits>
#include <mutex>

#include "platform/CCPlatformMacros.h"
#include "base/ccTypes.h"
#include "base/CCValue.h"
#include "base/CCData.h"
#include "base/CCAsyncTaskPool.h"
#include "base/CCScheduler.h"
#include "base/CCDirector.h"

NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */


class ResizableBuffer {
public:
    virtual ~ResizableBuffer() {}
    virtual void resize(size_t size) = 0;
    virtual void* buffer() const = 0;
};

template<typename T>
class ResizableBufferAdapter { };


template<typename CharT, typename Traits, typename Allocator>
class ResizableBufferAdapter< std::basic_string<CharT, Traits, Allocator> > : public ResizableBuffer {
    typedef std::basic_string<CharT, Traits, Allocator> BufferType;
    BufferType* _buffer;
public:
    explicit ResizableBufferAdapter(BufferType* buffer) : _buffer(buffer) {}
    virtual void resize(size_t size) override {
        _buffer->resize((size + sizeof(CharT) - 1) / sizeof(CharT));
    }
    virtual void* buffer() const override {
        // can not invoke string::front() if it is empty

        if (_buffer->empty())
            return nullptr;
        else
            return &_buffer->front();
    }
};

template<typename T, typename Allocator>
class ResizableBufferAdapter< std::vector<T, Allocator> > : public ResizableBuffer {
    typedef std::vector<T, Allocator> BufferType;
    BufferType* _buffer;
public:
    explicit ResizableBufferAdapter(BufferType* buffer) : _buffer(buffer) {}
    virtual void resize(size_t size) override {
        _buffer->resize((size + sizeof(T) - 1) / sizeof(T));
    }
    virtual void* buffer() const override {
        // can not invoke vector::front() if it is empty

        if (_buffer->empty())
            return nullptr;
        else
            return &_buffer->front();
    }
};


template<>
class ResizableBufferAdapter<Data> : public ResizableBuffer {
    typedef Data BufferType;
    BufferType* _buffer;
public:
    explicit ResizableBufferAdapter(BufferType* buffer) : _buffer(buffer) {}
    virtual void resize(size_t size) override {
        size_t oldSize = static_cast<size_t>(_buffer->getSize());
        if (oldSize != size) {
            auto old = _buffer->getBytes();
            void* buffer = realloc(old, size);
            if (buffer)
                _buffer->fastSet((unsigned char*)buffer, size);
        }
    }
    virtual void* buffer() const override {
        return _buffer->getBytes();
    }
};

/** Helper class to handle file operations. */
class CC_DLL FileUtils
{
public:
    /**
     *  Gets the instance of FileUtils.
     */
    static FileUtils* getInstance();

    /**
     *  Destroys the instance of FileUtils.
     */
    static void destroyInstance();

    /**
     * You can inherit from platform dependent implementation of FileUtils, such as FileUtilsAndroid,
     * and use this function to set delegate, then FileUtils will invoke delegate's implementation.
     * For example, your resources are encrypted, so you need to decrypt it after reading data from
     * resources, then you can implement all getXXX functions, and engine will invoke your own getXX
     * functions when reading data of resources.
     *
     * If you don't want to system default implementation after setting delegate, you can just pass nullptr
     * to this function.
     *
     * @warning It will delete previous delegate
     * @lua NA
     */
    static void setDelegate(FileUtils *delegate);

    /**
     *  The destructor of FileUtils.
     * @js NA
     * @lua NA
     */
    virtual ~FileUtils();

    /**
     *  Purges full path caches.
     */
    virtual void purgeCachedEntries();

    /**
     *  Gets string from a file.
     */
    virtual std::string getStringFromFile(const std::string& filename) const;
    
    /**
     * Gets string from a file, async off the main cocos thread
     *
     * @param path filepath for the string to be read. Can be relative or absolute path
     * @param callback Function that will be called when file is read. Will be called 
     * on the main cocos thread.
     */
    virtual void getStringFromFile(const std::string& path, std::function<void(std::string)> callback) const;

    /**
     *  Creates binary data from a file.
     *  @return A data object.
     */
    virtual Data getDataFromFile(const std::string& filename) const;
    

    /**
     * Gets a binary data object from a file, async off the main cocos thread.
     *
     * @param filename filepath for the data to be read. Can be relative or absolute path
     * @param callback Function that will be called when file is read. Will be called 
     * on the main cocos thread.
     */
    virtual void getDataFromFile(const std::string& filename, std::function<void(Data)> callback) const;

    enum class Status
    {
        OK = 0,
        NotExists = 1, // File not exists
        OpenFailed = 2, // Open file failed.
        ReadFailed = 3, // Read failed
        NotInitialized = 4, // FileUtils is not initializes
        TooLarge = 5, // The file is too large (great than 2^32-1)
        ObtainSizeFailed = 6, // Failed to obtain the file size.
        NotRegularFileType = 7 // File type is not S_IFREG
    };

    /**
     *  Gets whole file contents as string from a file.
     *
     *  Unlike getStringFromFile, these getContents methods:
     *      - read file in binary mode (does not convert CRLF to LF).
     *      - does not truncate the string when '\0' is found (returned string of getContents may have '\0' in the middle.).
     *
     *  The template version of can accept cocos2d::Data, std::basic_string and std::vector.
     *
     *  @code
     *  std::string sbuf;
     *  FileUtils::getInstance()->getContents("path/to/file", &sbuf);
     *
     *  std::vector<int> vbuf;
     *  FileUtils::getInstance()->getContents("path/to/file", &vbuf);
     *
     *  Data dbuf;
     *  FileUtils::getInstance()->getContents("path/to/file", &dbuf);
     *  @endcode
     *
     *  Note: if you read to std::vector<T> and std::basic_string<T> where T is not 8 bit type,
     *  you may get 0 ~ sizeof(T)-1 bytes padding.
     *
     *  - To write a new buffer class works with getContents, just extend ResizableBuffer.
     *  - To write a adapter for existing class, write a specialized ResizableBufferAdapter for that class, see follow code.
     *
     *  @code
     *  NS_CC_BEGIN // ResizableBufferAdapter needed in cocos2d namespace.
     *  template<>
     *  class ResizableBufferAdapter<AlreadyExistsBuffer> : public ResizableBuffer {
     *  public:
     *      ResizableBufferAdapter(AlreadyExistsBuffer* buffer)  {
     *          // your code here
     *      }
     *      virtual void resize(size_t size) override  {
     *          // your code here
     *      }
     *      virtual void* buffer() const override {
     *          // your code here
     *      }
     *  };
     *  NS_CC_END
     *  @endcode
     *
     *  @param[in]  filename The resource file name which contains the path.
     *  @param[out] buffer The buffer where the file contents are store to.
     *  @return Returns:
     *      - Status::OK when there is no error, the buffer is filled with the contents of file.
     *      - Status::NotExists when file not exists, the buffer will not changed.
     *      - Status::OpenFailed when cannot open file, the buffer will not changed.
     *      - Status::ReadFailed when read end up before read whole, the buffer will fill with already read bytes.
     *      - Status::NotInitialized when FileUtils is not initializes, the buffer will not changed.
     *      - Status::TooLarge when there file to be read is too large (> 2^32-1), the buffer will not changed.
     *      - Status::ObtainSizeFailed when failed to obtain the file size, the buffer will not changed.
     */
    template <
        typename T,
        typename Enable = typename std::enable_if<
            std::is_base_of< ResizableBuffer, ResizableBufferAdapter<T> >::value
        >::type
    >
    Status getContents(const std::string& filename, T* buffer) const {
        ResizableBufferAdapter<T> buf(buffer);
        return getContents(filename, &buf);
    }
    virtual Status getContents(const std::string& filename, ResizableBuffer* buffer) const;

    /**
     *  Gets resource file data from a zip file.
     *
     *  @param[in]  filename The resource file name which contains the relative path of the zip file.
     *  @param[out] size If the file read operation succeeds, it will be the data size, otherwise 0.
     *  @return Upon success, a pointer to the data is returned, otherwise nullptr.
     *  @warning Recall: you are responsible for calling free() on any Non-nullptr pointer returned.
     */
    virtual unsigned char* getFileDataFromZip(const std::string& zipFilePath, const std::string& filename, ssize_t *size) const;


    /** Returns the fullpath for a given filename.

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

     @since v2.1
     */
    virtual std::string fullPathForFilename(const std::string &filename) const;


    /**
     * Loads the filenameLookup dictionary from the contents of a filename.
     *
     * @note The plist file name should follow the format below:
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
     * @param filename The plist file name.
     *
     @since v2.1
     * @js loadFilenameLookup
     * @lua loadFilenameLookup
     */
    virtual void loadFilenameLookupDictionaryFromFile(const std::string &filename);

    /**
     *  Sets the filenameLookup dictionary.
     *
     *  @param filenameLookupDict The dictionary for replacing filename.
     *  @since v2.1
     */
    virtual void setFilenameLookupDictionary(const ValueMap& filenameLookupDict);

    /**
     *  Gets full path from a file name and the path of the relative file.
     *  @param filename The file name.
     *  @param relativeFile The path of the relative file.
     *  @return The full path.
     *          e.g. filename: hello.png, pszRelativeFile: /User/path1/path2/hello.plist
     *               Return: /User/path1/path2/hello.pvr (If there a a key(hello.png)-value(hello.pvr) in FilenameLookup dictionary. )
     *
     */
    virtual std::string fullPathFromRelativeFile(const std::string &filename, const std::string &relativeFile) const;

    /**
     *  Sets the array that contains the search order of the resources.
     *
     *  @param searchResolutionsOrder The source array that contains the search order of the resources.
     *  @see getSearchResolutionsOrder(), fullPathForFilename(const char*).
     *  @since v2.1
     *  In js:var setSearchResolutionsOrder(var jsval)
     *  @lua NA
     */
    virtual void setSearchResolutionsOrder(const std::vector<std::string>& searchResolutionsOrder);

    /**
      * Append search order of the resources.
      *
      * @see setSearchResolutionsOrder(), fullPathForFilename().
      * @since v2.1
      */
    virtual void addSearchResolutionsOrder(const std::string &order,const bool front=false);

    /**
     *  Gets the array that contains the search order of the resources.
     *
     *  @see setSearchResolutionsOrder(const std::vector<std::string>&), fullPathForFilename(const char*).
     *  @since v2.1
     *  @lua NA
     */
    virtual const std::vector<std::string> getSearchResolutionsOrder() const;

    /**
     *  Sets the array of search paths.
     *
     *  You can use this array to modify the search path of the resources.
     *  If you want to use "themes" or search resources in the "cache", you can do it easily by adding new entries in this array.
     *
     *  @note This method could access relative path and absolute path.
     *        If the relative path was passed to the vector, FileUtils will add the default resource directory before the relative path.
     *        For instance:
     *            On Android, the default resource root path is "assets/".
     *            If "/mnt/sdcard/" and "resources-large" were set to the search paths vector,
     *            "resources-large" will be converted to "assets/resources-large" since it was a relative path.
     *
     *  @param searchPaths The array contains search paths.
     *  @see fullPathForFilename(const char*)
     *  @since v2.1
     *  In js:var setSearchPaths(var jsval);
     *  @lua NA
     */
    virtual void setSearchPaths(const std::vector<std::string>& searchPaths);

    /**
     * Get default resource root path.
     */
    const std::string getDefaultResourceRootPath() const;

    /**
     * Set default resource root path.
     */
    void setDefaultResourceRootPath(const std::string& path);

    /**
      * Add search path.
      *
      * @since v2.1
      */
    void addSearchPath(const std::string & path, const bool front=false);

    /**
     *  Gets the array of search paths.
     *
     *  @return The array of search paths which may contain the prefix of default resource root path. 
     *  @note In best practise, getter function should return the value of setter function passes in.
     *        But since we should not break the compatibility, we keep using the old logic. 
     *        Therefore, If you want to get the original search paths, please call 'getOriginalSearchPaths()' instead.
     *  @see fullPathForFilename(const char*).
     *  @lua NA
     */
    virtual const std::vector<std::string> getSearchPaths() const;

    /**
     *  Gets the original search path array set by 'setSearchPaths' or 'addSearchPath'.
     *  @return The array of the original search paths
     */
    virtual const std::vector<std::string> getOriginalSearchPaths() const;

    /**
     *  Gets the writable path.
     *  @return  The path that can be write/read a file in
     */
    virtual std::string getWritablePath() const = 0;

    /**
     *  Sets writable path.
     */
    virtual void setWritablePath(const std::string& writablePath);

    /**
     *  Sets whether to pop-up a message box when failed to load an image.
     */
    virtual void setPopupNotify(bool notify);

    /** Checks whether to pop up a message box when failed to load an image.
     *  @return True if pop up a message box when failed to load an image, false if not.
     */
    virtual bool isPopupNotify() const;

    /**
     *  Converts the contents of a file to a ValueMap.
     *  @param filename The filename of the file to gets content.
     *  @return ValueMap of the file contents.
     *  @note This method is used internally.
     */
    virtual ValueMap getValueMapFromFile(const std::string& filename) const;


    /** Converts the contents of a file to a ValueMap.
     *  This method is used internally.
     */
    virtual ValueMap getValueMapFromData(const char* filedata, int filesize) const;

    /**
    * write a ValueMap into a plist file
    *
    *@param dict the ValueMap want to save
    *@param fullPath The full path to the file you want to save a string
    *@return bool
    */
    virtual bool writeToFile(const ValueMap& dict, const std::string& fullPath) const;

    /**
     *  write a string into a file
     *
     * @param dataStr the string want to save
     * @param fullPath The full path to the file you want to save a string
     * @return bool True if write success
     */
    virtual bool writeStringToFile(const std::string& dataStr, const std::string& fullPath) const;

    
    /**
     * Write a string to a file, done async off the main cocos thread
     * Use this function if you need file access without blocking the main thread.
     *
     * This function takes a std::string by value on purpose, to leverage move sematics.
     * If you want to avoid a copy of your datastr, use std::move/std::forward if appropriate
     *
     * @param dataStr the string want to save
     * @param fullPath The full path to the file you want to save a string
     * @param callback The function called once the string has been written to a file. This
     * function will be executed on the main cocos thread. It will have on boolean argument 
     * signifying if the write was successful.
     */
    virtual void writeStringToFile(std::string dataStr, const std::string& fullPath, std::function<void(bool)> callback) const;
    
    /**
     * write Data into a file
     *
     *@param data the data want to save
     *@param fullPath The full path to the file you want to save a string
     *@return bool
     */
    virtual bool writeDataToFile(const Data& data, const std::string& fullPath) const;
    

    /**
    * Write Data into a file, done async off the main cocos thread.
    *
    * Use this function if you need to write Data while not blocking the main cocos thread.
    *
    * This function takes Data by value on purpose, to leverage move sematics.
    * If you want to avoid a copy of your data, use std::move/std::forward if appropriate
    *
    *@param data The data that will be written to disk
    *@param fullPath The absolute file path that the data will be written to
    *@param callback The function that will be called when data is written to disk. This
    * function will be executed on the main cocos thread. It will have on boolean argument 
    * signifying if the write was successful.
    */
    virtual void writeDataToFile(Data data, const std::string& fullPath, std::function<void(bool)> callback) const;

    /**
    * write ValueMap into a plist file
    *
    *@param dict the ValueMap want to save
    *@param fullPath The full path to the file you want to save a string
    *@return bool
    */
    virtual bool writeValueMapToFile(const ValueMap& dict, const std::string& fullPath) const;

    /**
    * Write a ValueMap into a file, done async off the main cocos thread.
    *
    * Use this function if you need to write a ValueMap while not blocking the main cocos thread.
    *
    * This function takes ValueMap by value on purpose, to leverage move sematics.
    * If you want to avoid a copy of your dict, use std::move/std::forward if appropriate
    *
    *@param dict The ValueMap that will be written to disk
    *@param fullPath The absolute file path that the data will be written to
    *@param callback The function that will be called when dict is written to disk. This
    * function will be executed on the main cocos thread. It will have on boolean argument 
    * signifying if the write was successful.
    */
    virtual void writeValueMapToFile(ValueMap dict, const std::string& fullPath, std::function<void(bool)> callback) const;

    /**
    * write ValueVector into a plist file
    *
    *@param vecData the ValueVector want to save
    *@param fullPath The full path to the file you want to save a string
    *@return bool
    */
    virtual bool writeValueVectorToFile(const ValueVector& vecData, const std::string& fullPath) const;

    /**
    * Write a ValueVector into a file, done async off the main cocos thread.
    *
    * Use this function if you need to write a ValueVector while not blocking the main cocos thread.
    *
    * This function takes ValueVector by value on purpose, to leverage move sematics.
    * If you want to avoid a copy of your dict, use std::move/std::forward if appropriate
    *
    *@param vecData The ValueVector that will be written to disk
    *@param fullPath The absolute file path that the data will be written to
    *@param callback The function that will be called when vecData is written to disk. This
    * function will be executed on the main cocos thread. It will have on boolean argument 
    * signifying if the write was successful.
    */
    virtual void writeValueVectorToFile(ValueVector vecData, const std::string& fullPath, std::function<void(bool)> callback) const;

    /**
    * Windows fopen can't support UTF-8 filename
    * Need convert all parameters fopen and other 3rd-party libs
    *
    * @param filenameUtf8 std::string name file for conversion from utf-8
    * @return std::string ansi filename in current locale
    */
    virtual std::string getSuitableFOpen(const std::string& filenameUtf8) const;

    // Converts the contents of a file to a ValueVector.
    // This method is used internally.
    virtual ValueVector getValueVectorFromFile(const std::string& filename) const;

    /**
     *  Checks whether a file exists.
     *
     *  @note If a relative path was passed in, it will be inserted a default root path at the beginning.
     *  @param filename The path of the file, it could be a relative or absolute path.
     *  @return True if the file exists, false if not.
     */
    virtual bool isFileExist(const std::string& filename) const;

    /**
     * Checks if a file exists, done async off the main cocos thread.
     * 
     * Use this function if you need to check if a file exists while not blocking the main cocos thread.
     *
     *  @note If a relative path was passed in, it will be inserted a default root path at the beginning.
     *  @param filename The path of the file, it could be a relative or absolute path.
     *  @param callback The function that will be called when the operation is complete. Will have one boolean
     * argument, true if the file exists, false otherwise.
     */
    virtual void isFileExist(const std::string& filename, std::function<void(bool)> callback) const;

    /**
    *  Gets filename extension is a suffix (separated from the base filename by a dot) in lower case.
    *  Examples of filename extensions are .png, .jpeg, .exe, .dmg and .txt.
    *  @param filePath The path of the file, it could be a relative or absolute path.
    *  @return suffix for filename in lower case or empty if a dot not found.
    */
    virtual std::string getFileExtension(const std::string& filePath) const;

    /**
     *  Checks whether the path is an absolute path.
     *
     *  @note On Android, if the parameter passed in is relative to "assets/", this method will treat it as an absolute path.
     *        Also on Blackberry, path starts with "app/native/Resources/" is treated as an absolute path.
     *
     *  @param path The path that needs to be checked.
     *  @return True if it's an absolute path, false if not.
     */
    virtual bool isAbsolutePath(const std::string& path) const;

    /**
     *  Checks whether the path is a directory.
     *
     *  @param dirPath The path of the directory, it could be a relative or an absolute path.
     *  @return True if the directory exists, false if not.
     */
    virtual bool isDirectoryExist(const std::string& dirPath) const;

    /**
     *  Checks whether the absoulate path is a directory, async off of the main cocos thread.
     *
     * @param dirPath The path of the directory, it must be an absolute path
     * @param callback that will accept a boolean, true if the file exists, false otherwise. 
     * Callback will happen on the main cocos thread.
     */
    virtual void isDirectoryExist(const std::string& fullPath, std::function<void(bool)> callback) const;

    /**
     *  Creates a directory.
     *
     *  @param dirPath The path of the directory, it must be an absolute path.
     *  @return True if the directory have been created successfully, false if not.
     */
    virtual bool createDirectory(const std::string& dirPath) const;

    /**
     * Create a directory, async off the main cocos thread.
     *
     * @param dirPath the path of the directory, it must be an absolute path
     * @param callback The function that will be called when the operation is complete. Will have one boolean
     * argument, true if the directory was successfully, false otherwise.
     */
    virtual void createDirectory(const std::string& dirPath, std::function<void(bool)> callback) const;

    /**
     *  Removes a directory.
     *
     *  @param dirPath  The full path of the directory, it must be an absolute path.
     *  @return True if the directory have been removed successfully, false if not.
     */
    virtual bool removeDirectory(const std::string& dirPath) const;

    /**
     * Removes a directory, async off the main cocos thread.
     *
     * @param dirPath the path of the directory, it must be an absolute path
     * @param callback The function that will be called when the operation is complete. Will have one boolean
     * argument, true if the directory was successfully removed, false otherwise.
     */
    virtual void removeDirectory(const std::string& dirPath, std::function<void(bool)> callback) const;

    /**
     *  Removes a file.
     *
     *  @param filepath The full path of the file, it must be an absolute path.
     *  @return True if the file have been removed successfully, false if not.
     */
    virtual bool removeFile(const std::string &filepath) const;

    /**
     * Removes a file, async off the main cocos thread.
     *
     * @param filepath the path of the file to remove, it must be an absolute path
     * @param callback The function that will be called when the operation is complete. Will have one boolean
     * argument, true if the file was successfully removed, false otherwise.
     */
    virtual void removeFile(const std::string &filepath, std::function<void(bool)> callback) const;

    /**
     *  Renames a file under the given directory.
     *
     *  @param path     The parent directory path of the file, it must be an absolute path.
     *  @param oldname  The current name of the file.
     *  @param name     The new name of the file.
     *  @return True if the file have been renamed successfully, false if not.
     */
    virtual bool renameFile(const std::string &path, const std::string &oldname, const std::string &name) const;

    /**
     *  Renames a file under the given directory, async off the main cocos thread.
     *
     *  @param path     The parent directory path of the file, it must be an absolute path.
     *  @param oldname  The current name of the file.
     *  @param name     The new name of the file.
     *  @param callback The function that will be called when the operation is complete. Will have one boolean
     * argument, true if the file was successfully renamed, false otherwise.
     */
    virtual void renameFile(const std::string &path, const std::string &oldname, const std::string &name, std::function<void(bool)> callback) const;

    /**
     *  Renames a file under the given directory.
     *
     *  @param oldfullpath  The current fullpath of the file. Includes path and name.
     *  @param newfullpath  The new fullpath of the file. Includes path and name.
     *  @return True if the file have been renamed successfully, false if not.
     */
    virtual bool renameFile(const std::string &oldfullpath, const std::string &newfullpath) const;

    /**
     *  Renames a file under the given directory, async off the main cocos thread.
     *
     *  @param oldfullpath  The current fullpath of the file. Includes path and name.
     *  @param newfullpath  The new fullpath of the file. Includes path and name.
     *  @param callback The function that will be called when the operation is complete. Will have one boolean
     * argument, true if the file was successfully renamed, false otherwise.
     */
    virtual void renameFile(const std::string &oldfullpath, const std::string &newfullpath, std::function<void(bool)> callback) const;

    /**
     *  Retrieve the file size.
     *
     *  @note If a relative path was passed in, it will be inserted a default root path at the beginning.
     *  @param filepath The path of the file, it could be a relative or absolute path.
     *  @return The file size.
     */
    virtual long getFileSize(const std::string &filepath) const;

    /**
     *  Retrieve the file size, async off the main cocos thread.
     *
     *  @note If a relative path was passed in, it will be inserted a default root path at the beginning.
     *  @param filepath The path of the file, it could be a relative or absolute path.
     *  @param callback The function that will be called when the operation is complete. Will have one long
     * argument, the file size.
     */
    virtual void getFileSize(const std::string &filepath, std::function<void(long)> callback) const;

    /**
     *  List all files in a directory.
     *
     *  @param dirPath The path of the directory, it could be a relative or an absolute path.
     *  @return File paths in a string vector
     */
    virtual std::vector<std::string> listFiles(const std::string& dirPath) const;

    /**
     * List all files in a directory async, off of the main cocos thread.
     *
     * @param dirPath The path of the directory, it could be a relative or an absolute path.
     * @param callback The callback to be called once the list operation is complete. Will be called on the main cocos thread.
     * @js NA
     * @lua NA
     */
    virtual void listFilesAsync(const std::string& dirPath, std::function<void(std::vector<std::string>)> callback) const;
    
    /**
     *  List all files recursively in a directory.
     *
     *  @param dirPath The path of the directory, it could be a relative or an absolute path.
     *  @return File paths in a string vector
     */
    virtual void listFilesRecursively(const std::string& dirPath, std::vector<std::string> *files) const;

    /**
    *  List all files recursively in a directory, async off the main cocos thread.
    *
    *  @param dirPath The path of the directory, it could be a relative or an absolute path.
    *  @param callback The callback to be called once the list operation is complete. 
    *          Will be called on the main cocos thread.
    * @js NA
    * @lua NA
    */
    virtual void listFilesRecursivelyAsync(const std::string& dirPath, std::function<void(std::vector<std::string>)> callback) const;

    /** Returns the full path cache. */
    const std::unordered_map<std::string, std::string> getFullPathCache() const { return _fullPathCache; }

    /**
     *  Gets the new filename from the filename lookup dictionary.
     *  It is possible to have a override names.
     *  @param filename The original filename.
     *  @return The new filename after searching in the filename lookup dictionary.
     *          If the original filename wasn't in the dictionary, it will return the original filename.
     */
    virtual std::string getNewFilename(const std::string &filename) const;

protected:
    /**
     *  The default constructor.
     */
    FileUtils();

    /**
     *  Initializes the instance of FileUtils. It will set _searchPathArray and _searchResolutionsOrderArray to default values.
     *
     *  @note When you are porting Cocos2d-x to a new platform, you may need to take care of this method.
     *        You could assign a default value to _defaultResRootPath in the subclass of FileUtils(e.g. FileUtilsAndroid). Then invoke the FileUtils::init().
     *  @return true if succeed, otherwise it returns false.
     *
     */
    virtual bool init();

    /**
     *  Checks whether a file exists without considering search paths and resolution orders.
     *  @param filename The file (with absolute path) to look up for
     *  @return Returns true if the file found at the given absolute path, otherwise returns false
     */
    virtual bool isFileExistInternal(const std::string& filename) const = 0;

    /**
     *  Checks whether a directory exists without considering search paths and resolution orders.
     *  @param dirPath The directory (with absolute path) to look up for
     *  @return Returns true if the directory found at the given absolute path, otherwise returns false
     */
    virtual bool isDirectoryExistInternal(const std::string& dirPath) const;

    /**
     *  Gets full path for filename, resolution directory and search path.
     *
     *  @param filename The file name.
     *  @param resolutionDirectory The resolution directory.
     *  @param searchPath The search path.
     *  @return The full path of the file. It will return an empty string if the full path of the file doesn't exist.
     */
    virtual std::string getPathForFilename(const std::string& filename, const std::string& resolutionDirectory, const std::string& searchPath) const;

    virtual std::string getPathForDirectory(const std::string &dir, const std::string &resolutionDiretory, const std::string &searchPath) const;
    
    
    /**
     *  Gets full path for the directory and the filename.
     *
     *  @note Only iOS and Mac need to override this method since they are using
     *        `[[NSBundle mainBundle] pathForResource: ofType: inDirectory:]` to make a full path.
     *        Other platforms will use the default implementation of this method.
     *  @param directory The directory contains the file we are looking for.
     *  @param filename  The name of the file.
     *  @return The full path of the file, if the file can't be found, it will return an empty string.
     */
    virtual std::string getFullPathForFilenameWithinDirectory(const std::string& directory, const std::string& filename) const;
    
 
    /**
     * Returns the fullpath for a given dirname.
     * @since 3.17.1
     */
    virtual std::string fullPathForDirectory(const std::string &dirname) const;

    /**
    * mutex used to protect fields. 
    */
    mutable std::recursive_mutex _mutex;


    /** Dictionary used to lookup filenames based on a key.
     *  It is used internally by the following methods:
     *
     *  std::string fullPathForFilename(const char*);
     *
     *  @since v2.1
     */
    ValueMap _filenameLookupDict;

    /**
     *  The vector contains resolution folders.
     *  The lower index of the element in this vector, the higher priority for this resolution directory.
     */
    std::vector<std::string> _searchResolutionsOrderArray;

    /**
     * The vector contains search paths.
     * The lower index of the element in this vector, the higher priority for this search path.
     */
    std::vector<std::string> _searchPathArray;

    /**
     * The search paths which was set by 'setSearchPaths' / 'addSearchPath'.
     */
    std::vector<std::string> _originalSearchPaths;

    /**
     *  The default root path of resources.
     *  If the default root path of resources needs to be changed, do it in the `init` method of FileUtils's subclass.
     *  For instance:
     *  On Android, the default root path of resources will be assigned with "assets/" in FileUtilsAndroid::init().
     *  Similarly on Blackberry, we assign "app/native/Resources/" to this variable in FileUtilsBlackberry::init().
     */
    std::string _defaultResRootPath;

    /**
     *  The full path cache for normal files. When a file is found, it will be added into this cache.
     *  This variable is used for improving the performance of file search.
     */
    mutable std::unordered_map<std::string, std::string> _fullPathCache;

    /**
     *  The full path cache for directories. When a diretory is found, it will be added into this cache.
     *  This variable is used for improving the performance of file search.
     */
    mutable std::unordered_map<std::string, std::string> _fullPathCacheDir;

    /**
     * Writable path.
     */
    std::string _writablePath;

    /**
     *  The singleton pointer of FileUtils.
     */
    static FileUtils* s_sharedFileUtils;

    /**
     *  Remove null value key (for iOS)
     */
    virtual void valueMapCompact(ValueMap& valueMap) const;
    virtual void valueVectorCompact(ValueVector& valueVector) const;

    template<typename T, typename R, typename ...ARGS>
    static void performOperationOffthread(T&& action, R&& callback, ARGS&& ...args)
    {

        // Visual Studio 2013 does not support using std::bind to forward template parameters into
        // a lambda. To get around this, we will just copy these arguments via lambda capture
#if defined(_MSC_VER) && _MSC_VER  < 1900 
        auto lambda = [action, callback, args...]() 
        {
            Director::getInstance()->getScheduler()->performFunctionInCocosThread(std::bind(callback, action(args...)));
        };
#else
        // As cocos2d-x uses c++11, we will use std::bind to leverage move sematics to
        // move our arguments into our lambda, to potentially avoid copying. 
        auto lambda = std::bind([](const T& actionIn, const R& callbackIn, const ARGS& ...argsIn)
        {
            Director::getInstance()->getScheduler()->performFunctionInCocosThread(std::bind(callbackIn, actionIn(argsIn...)));
        }, std::forward<T>(action), std::forward<R>(callback), std::forward<ARGS>(args)...);
        
#endif

        AsyncTaskPool::getInstance()->enqueue(AsyncTaskPool::TaskType::TASK_IO, [](void*){}, nullptr, std::move(lambda));
    }
};

// end of support group
/** @} */

NS_CC_END

#endif    // __CC_FILEUTILS_H__
