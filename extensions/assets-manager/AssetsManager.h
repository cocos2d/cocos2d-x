/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#ifndef __AssetsManager__
#define __AssetsManager__

#include <string>

#include <mutex>

#include "2d/CCNode.h"
#include "extensions/ExtensionMacros.h"
#include "extensions/ExtensionExport.h"


namespace cocos2d { namespace network {
    class Downloader;
}}

NS_CC_EXT_BEGIN

/**
 * @addtogroup assets_manager
 * @{
 */

class AssetsManagerDelegateProtocol;

/** 
 * @~english
 *  This class is used to auto update resources, such as pictures or scripts.
 *  The updated package should be a zip file. And in the server there should be a file which contains version code.
 * @~chinese 
 * 该类用于自动更新资源，如图片或脚本资源。
 * 更新包是一个zip包。服务器上应该有一个文件，其中包含版本代码。
 */
class CC_EX_DLL AssetsManager : public Node
{
public:
    /** @~english Error code that can be notified to listener
     * @~chinese 会被传递給事件监听器的错误代码列表
     */
    enum class ErrorCode
    {
        /** @~english Error caused by creating a file to store downloaded data
         * @~chinese 创建文件失败的错误
         */
        CREATE_FILE,
        /** @~english Errors caused by network, there are the following possibilities:
         - network unavaivable
         - timeout
         - ...
         * @~chinese 网络错误，可能的原因有：
         * — 网络不可用
         * — 超时
         * — ...
         */
        NETWORK,
        /** @~english There is not a new version
         * @~chinese 没有新版本
         */
        NO_NEW_VERSION,
        /** @~english Error caused in uncompressing stage
         - can not open zip file
         - can not read file global information
         - can not read file information
         - can not create a directory
         - ...
         * @~chinese 压缩阶段引起的错误
         * — 不能打开压缩文件
         * - 不能读取文件的全局信息
         * — 不能读取文件信息
         * — 不能创建一个目录
         * — ...
         */
        UNCOMPRESS,
    };
    
    /* @brief @~english Creates a AssetsManager with new package url, version code url and storage path.
     *
     * @~chinese 使用新包的URL地址，版本文件URL地址和存储路径创建一个新的AssetsManager对象。
     * 
     * @param packageUrl @~english URL of new package, the package should be a zip file.
     * @~chinese 新包的URL，新包应该是一个zip文件。
     * @param versionFileUrl @~english URL of version file. It should contain version code of new package.
     * @~chinese 版本文件的URL，它应该包含新版本的版本号。
     * @param storagePath @~english The path to store downloaded resources.
     * @~chinese 用来存储下载资源的路径。
     * @return @~english The AssetsManager object when created successfully, otherwise return nullptr.
     * @~chinese 当创建成功返回AssetsManager对象，否则返回nullptr。
     * @js NA
     * @lua new
     */
    AssetsManager(const char* packageUrl = NULL, const char* versionFileUrl = NULL, const char* storagePath = NULL);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~AssetsManager();
    
    typedef std::function<void(int)> ErrorCallback;
    typedef std::function<void(int)> ProgressCallback;
    typedef std::function<void(void)> SuccessCallback;

    /* @brief @~english Creates a AssetsManager with new package url, version code url and storage path.
     *
     * @~chinese 使用新包的URL地址，版本文件URL地址，存储路径以及回调函数创建一个新的AssetsManager对象。
     * 
     * @param packageUrl @~english URL of new package, the package should be a zip file.
     * @~chinese 新包的URL，新包应该是一个zip文件。
     * @param versionFileUrl @~english URL of version file. It should contain version code of new package.
     * @~chinese 版本文件的URL，它应该包含新版本的版本号。
     * @param storagePath @~english The path to store downloaded resources.
     * @~chinese 用来存储下载资源的路径。
     * @param errorCallback @~english The callback to invoke when error happens.
     * @~chinese 错误发生时的回调函数。
     * @param progressCallback @~english The callback to invoke when progression changes.
     * @~chinese 下载过程中进度改变时的回调函数。
     * @param successCallback @~english The callback to invoke when succeed to update.
     * @~chinese 成功更新时的回调函数。
     * @return @~english The AssetsManager object when created successfully, otherwise return nullptr.
     * @~chinese 当创建成功返回AssetsManager对象，否则返回nullptr。
     * @js NA
     * @lua new
     */
    static AssetsManager* create(const char* packageUrl, const char* versionFileUrl, const char* storagePath, ErrorCallback errorCallback, ProgressCallback progressCallback, SuccessCallback successCallback );

    /* @brief @~english Check out if there is a new version resource.
     *        You may use this method before updating, then let user determine whether
     *        he wants to update resources.
     * @~chinese 检查是否有新版本的资源。
     * 你可以用这种方法在更新之前让用户决定是否进行更新。
     * @return @~english Return true if there is a new version, otherwise return false.
     * @~chinese 如果有新版本则返回true，否则返回false。
     */
    virtual bool checkUpdate();
    
    using Node::update;
    /* @brief @~english Download new package if there is a new version, and uncompress downloaded zip file to the predefined storage path.
     *        Of course it will set search path that stores downloaded files.
     * @~chinese 如果有新版本就下载新的包，并解压缩下载的zip文件到预设的存储路径。
     * 当然，它会将存储路径添加到搜索路径中。
     */
    virtual void update();
    
    /* @brief @~english Gets url of package.
     * @~chinese 获取资源包的URL地址。
     * @return @~english The package url.
     * @~chinese 资源包的URL地址。
     */
    const char* getPackageUrl() const;
    
    /* @brief @~english Sets package url.
     * @~chinese 设置资源包的URL地址。
     * @param packageUrl @~english The package url.
     * @~chinese 资源包的URL地址。
     */
    void setPackageUrl(const char* packageUrl);
    
    /* @brief @~english Gets version file url.
     * @~chinese 获取版本文件的URL地址。
     * @return @~english The version file url.
     * @~chinese 版本文件的URL地址。
     */
    const char* getVersionFileUrl() const;
    
    /* @brief @~english Sets version file url.
     * @~chinese 设置版本文件的URL地址。
     * @param versionFileUrl @~english The version file url.
     * @~chinese 版本文件的URL地址。
     */
    void setVersionFileUrl(const char* versionFileUrl);
    
    /* @brief @~english Gets the current version code.
     * @~chinese 获取当前版本号。
     * @return @~english The current version code.
     * @~chinese 当前版本号。
     */
    std::string getVersion();
    
    /* @brief @~english Deletes recorded version code.
     * @~chinese 删除本地版本号。
     */
    void deleteVersion();
    
    /* @brief @~english Gets storage path.
     * @~chinese 获取存储路径。
     * @return @~english The storage path.
     * @~chinese 存储路径。
     */
    const char* getStoragePath() const;
    
    /* @brief @~english Sets storage path.
     *
     * @~chinese 设置存储路径。
     * 
     * @param storagePath @~english The path to store downloaded resources.
     * @~chinese 存储下载资源的路径。
     * @warm @~english The path should be a valid path.
     * @~chinese 这个路径必须是一个有效的本地路径。
     */
    void setStoragePath(const char* storagePath);
    
    /** @brief @~english Sets delegate, the delegate will receive messages
     * @~chinese 设置接收消息的代理
     * @param delegate @~english The delegate which extends `AssetsManagerDelegateProtocol`.
     * @~chinese 继承自`AssetsManagerDelegateProtocol`的代理对象。
     * @js NA
     * @lua NA
     */
    void setDelegate(AssetsManagerDelegateProtocol *delegate);
    
    /** @brief @~english Gets delegate, the delegate will receive messages
     * @~chinese 获取接收消息的代理
     * @return @~english The delegate which extends `AssetsManagerDelegateProtocol`.
     * @~chinese 继承自`AssetsManagerDelegateProtocol`的代理对象。
     * @js NA
     * @lua NA
     */
    AssetsManagerDelegateProtocol* getDelegate() const { return _delegate ;}
    
    /** @brief @~english Sets connection time out in seconds
     * @~chinese 设置连接超时时间，以秒为单位
     * @param timeout @~english The time out value.
     * @~chinese 连接超时时间。
     */
    void setConnectionTimeout(unsigned int timeout);
    
    /** @brief @~english Gets connection time out in secondes
     * @~chinese 获取连接超时时间，以秒为单位
     * @return @~english The time out value.
     * @~chinese 连接超时时间。
     */
    unsigned int getConnectionTimeout();

protected:
    void checkStoragePath();
    bool uncompress();
    void setSearchPath();
    void downloadAndUncompress();

private:
    /** @brief @~english Initializes storage path.
     * @~chinese 初始化存储路径。
     */
    void createStoragePath();
    
    /** @brief @~english Destroys storage path.
     * @~chinese 删除存储路径。
     */
    void destroyStoragePath();
    
private:
    //! The path to store downloaded resources.
    std::string _storagePath;
    
    //! The version of downloaded resources.
    std::string _version;
    
    std::string _packageUrl;
    std::string _versionFileUrl;
    
    std::string _downloadedVersion;
    
    cocos2d::network::Downloader* _downloader;

    unsigned int _connectionTimeout;
    
    AssetsManagerDelegateProtocol *_delegate; 
    
    bool _isDownloading;
    bool _shouldDeleteDelegateWhenExit;
    
    std::string keyOfVersion() const;
    std::string keyOfDownloadedVersion() const;
};

/** 
 * @~english
 *  This class is the delegate for receving events during update process of AssetsManager.
 * @~chinese 
 * 该类是用于在AssetsManager更新过程中接收事件的代理
 * @see AssetsManager
 */
class AssetsManagerDelegateProtocol
{
public:
    virtual ~AssetsManagerDelegateProtocol(){};
public:
    /* @brief @~english Call back function for error
     * @~chinese 发生错误时的回调函数
       @param errorCode @~english Type of error
     * @~chinese 错误代码
     * @js NA
     * @lua NA
     */
    virtual void onError(AssetsManager::ErrorCode errorCode) {};
    /** @brief @~english Call back function for recording downloading percent
     * @~chinese 记录下载百分比的回调函数
     * @param percent @~english How much percent downloaded
     * @~chinese 下载了多少百分比
     * @warning @~english This call back function just for recording downloading percent.
              AssetsManager will do some other thing after downloading, if you want to manipulate the downloaded files,
              you should write code in onSuccess() after downloading. 
     * @~chinese 这个回调函数只是为了记录下载百分比。
     * AssetsManager下载后会做一些其他的事情，你可以在onSuccess回调中中对下载好的文件作相应的处理。
     * @js NA
     * @lua NA
     */
    virtual void onProgress(int percent) {};
    /** @brief @~english Call back function for success
     * @~chinese 更新成功的回调函数
     * @js NA
     * @lua NA
     */
    virtual void onSuccess() {};
};

// Deprecated declaration
CC_DEPRECATED_ATTRIBUTE typedef AssetsManager CCAssetsManager;
CC_DEPRECATED_ATTRIBUTE typedef AssetsManagerDelegateProtocol CCAssetsManagerDelegateProtocol;

/**
 * // AssetsManager
 * @}
 */

NS_CC_EXT_END;

#endif /* defined(__AssetsManager__) */
