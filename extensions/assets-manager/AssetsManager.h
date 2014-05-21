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

#include "cocos2d.h"
#include "extensions/ExtensionMacros.h"

NS_CC_EXT_BEGIN

class AssetsManagerDelegateProtocol;

/*
 *  这个是自动更新诸如图片、脚本等资源的类
 *  更新包应该是zip文件，并且在客户端应该有一个命名为version的文件，里面包含版本号。
 *  
 */
class AssetsManager : public Node
{
public:
    enum class ErrorCode
    {
        
        //创建存储已下载数据的文件引起的错误
        CREATE_FILE,
        /** 网络错误
         -- 不可用网络
         -- 超时
         -- ...
         */
        NETWORK,
        /** 没用新版本
         */
        NO_NEW_VERSION,
        /** 解压缩文件引起的错误
         -- 无法打开zip文件
         -- 无法读取文件的全局信息
         -- 无法读取文件信息
         -- 无法创建目录
         -- ...
         */
        UNCOMPRESS,
    };
    
    /* @brief 以packUrl,versionFileUrl,storagePath为参数创建AssetsManager
     *
     * @param packageUrl 新包的URL, 这个包应该是一个zip文件.
     * @param versionFileUrl 版本文件的URL. 里面应该包含新包的版本号.
     * @param storagePath 存储已下载资源的路径.
     * @js NA
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

    /* @brief 在脚本环境中访问
     */
    static AssetsManager* create(const char* packageUrl, const char* versionFileUrl, const char* storagePath, ErrorCallback errorCallback, ProgressCallback progressCallback, SuccessCallback successCallback );

    /* @brief 检查是否有新版的资源
     *        你可以在更新之前调用这个方法，然后让用户决定是否更新资源
     *       
     */
    virtual bool checkUpdate();
    
    using Node::update;
    /* @brief 如果有新的版本，就下载新包并解压缩下载的zip文件
     *        并且设置存储已下载文件的搜寻路径
     */
    virtual void update();
    
    /* @brief 获取包的URL.
     */
    const char* getPackageUrl() const;
    
    /* @brief 设置包的URL.
     */
    void setPackageUrl(const char* packageUrl);
    
    /* @brief 获取版本文件的URL.
     */
    const char* getVersionFileUrl() const;
    
    /* @brief 设置版本文件的URL.
     */
    void setVersionFileUrl(const char* versionFileUrl);
    
    /* @brief 获取当前版本号.
     */
    std::string getVersion();
    
    /* @brief 删除原来的(recorded)版本号.
     */
    void deleteVersion();
    
    /* @brief 获取存储路径.
     */
    const char* getStoragePath() const;
    
    /* @brief 设置存储路径.
     *
     * @param storagePath 存储已下载资源的路径.
     * @warm 这应该是一个有效的路径.
     */
    void setStoragePath(const char* storagePath);
    
    /** @brief 设置委托，这个委托将接收消息
     * @js NA
     * @lua NA
     */
    void setDelegate(AssetsManagerDelegateProtocol *delegate);
    
    /**
     * @js NA
     * @lua NA
     */
    AssetsManagerDelegateProtocol* getDelegate() const { return _delegate ;}
    
    /** @brief 设置以秒为单位的连接超时时间
     */
    void setConnectionTimeout(unsigned int timeout);
    
    /** @brief 获取以秒为单位的连接超时时间
     */
    unsigned int getConnectionTimeout();
    
    /* 用一个新的线程下载并解压缩
     */
    friend int assetsManagerProgressFunc(void *, double, double, double, double);

protected:
    bool downLoad();
    void checkStoragePath();
    bool uncompress();
    bool createDirectory(const char *path);
    void setSearchPath();
    void downloadAndUncompress();

private:
    /** @brief 初始化存储路径
     */
    void createStoragePath();
    
    /** @brief 销毁存储路径
     */
    void destroyStoragePath();
    
private:
    //! 存储已下载资源的路径（成员变量）
    std::string _storagePath;
    
    //! 以下载资源的版本（成员变量）
    std::string _version;
    
    std::string _packageUrl;
    std::string _versionFileUrl;
    
    std::string _downloadedVersion;
    
    void *_curl;

    unsigned int _connectionTimeout;
    
    AssetsManagerDelegateProtocol *_delegate; 
    
    bool _isDownloading;
    bool _shouldDeleteDelegateWhenExit;
    
    std::string keyOfVersion() const;
    std::string keyOfDownloadedVersion() const;
};

class AssetsManagerDelegateProtocol
{
public:
    virtual ~AssetsManagerDelegateProtocol(){};
public:
    /* @brief 发生错误时调用的成员函数
       @param 错误类型
     * @js NA
     * @lua NA
     */
    virtual void onError(AssetsManager::ErrorCode errorCode) {};
    /** @brief 记录下载进度的回调函数
        @param percent 已下载的百分比
        @warning    这个回调函数只是记录下载的百分比
              你应该在onSuccess()函数中编写代码，让AssetsManager在下载完成后做一些其他的事情
        
     * @js NA
     * @lua NA
     */
    virtual void onProgress(int percent) {};
    /** @brief 成功的时候调用的回调函数
     * @js NA
     * @lua NA
     */
    virtual void onSuccess() {};
};

// 弃用的声明
CC_DEPRECATED_ATTRIBUTE typedef AssetsManager CCAssetsManager;
CC_DEPRECATED_ATTRIBUTE typedef AssetsManagerDelegateProtocol CCAssetsManagerDelegateProtocol;

NS_CC_EXT_END;

#endif /* defined(__AssetsManager__) */
