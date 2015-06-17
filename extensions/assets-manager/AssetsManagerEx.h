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

#ifndef __AssetsManagerEx__
#define __AssetsManagerEx__

#include "base/CCEventDispatcher.h"
#include "platform/CCFileUtils.h"
#include "CCEventAssetsManagerEx.h"
#include "Downloader.h"
#include "Manifest.h"
#include "extensions/ExtensionMacros.h"
#include "extensions/ExtensionExport.h"
#include "json/document.h"

#include <string>
#include <unordered_map>
#include <vector>

NS_CC_EXT_BEGIN

/**
 * @addtogroup assets_manager
 * @{
 */

/**
 * @brief @~english This class is used for resources hot update, you can update images or scripts during runtime of the game.
 * Compare to AssetsManager class, it's a upgraded version. 
 * It's based on manifest configuration files to compare between local version and remote version, 
 * then generate a list of assets which need to be upgraded, download them then finish the update process.
 * It contains the following features:
 * - Multi thread downloading support
 * - Two levels progression support: File level progression and byte level progression
 * - Zip compressed file support
 * - Download resuming
 * - Detailed progression informations and error informations
 * - Possibility to retry failed assets
 * Please refer to this detailed document for its usage: 
 * http://cocos2d-x.org/docs/manual/framework/html5/v3/assets-manager/en
 * @~chinese 该类用于资源热更新支持，比如游戏过程中动态照片或脚本。和AssetsManager类相比，它是一个升级版本，支持更强大的热更新功能。
 * AssetsManagerEx基于manifest配置文件来比较本地和远程资源的版本，生成需要更新的资源列表，下载它们并完成更新过程。
 * 下面是它主要的特性：
 * - 多线程并行下载支持
 * - 两层进度统计信息：文件级以及字节级
 * - Zip压缩文件支持
 * - 断点续传
 * - 详细的错误报告
 * - 文件下载失败重试支持
 * 详细的使用方式，请参考下面的文档： 
 * http://cocos2d-x.org/docs/manual/framework/html5/v3/assets-manager/zh
 */
class CC_EX_DLL AssetsManagerEx : public Ref
{
public:
    
    friend class Downloader;
    friend int downloadProgressFunc(Downloader::ProgressData *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded);
    
    /** @~english Update states
     * @~chinese 热更新状态列表
     */
    enum class State
    {
        /** @~english Unchecked whether there is a new version
         * @~chinese 尚未检查是否存在新版本
         */
        UNCHECKED,
        /** @~english Before downloading the version manifest file
         * @~chinese 在下载版本manifest文件之前
         */
        PREDOWNLOAD_VERSION,
        /** @~english Downloading the version manifest file
         * @~chinese 正在下载版本manifest文件
         */
        DOWNLOADING_VERSION,
        /** @~english After successfully downloaded and parsed the version manifest
         * @~chinese 成功下载并解析版本manifest之后
         */
        VERSION_LOADED,
        /** @~english Before downloading the resources manifest file
         * @~chinese 在下载资源manifest文件之前
         */
        PREDOWNLOAD_MANIFEST,
        /** @~english Downloading the resources manifest file
         * @~chinese 正在下载资源manifest文件
         */
        DOWNLOADING_MANIFEST,
        /** @~english After successfully downloaded and parsed the resources manifest
         * @~chinese 成功下载并解析资源manifest之后
         */
        MANIFEST_LOADED,
        /** @~english New version detected, needed to be updated
         * @~chinese 检查到新版本，需要更新
         */
        NEED_UPDATE,
        /** @~english Updating new version
         * @~chinese 更新中
         */
        UPDATING,
        /** @~english Updated to the latest version
         * @~chinese 已更新到最新版本
         */
        UP_TO_DATE,
        /** @~english Failed to update new version
         * @~chinese 更新失败
         */
        FAIL_TO_UPDATE
    };
    
    const static std::string VERSION_ID;
    const static std::string MANIFEST_ID;
    const static std::string BATCH_UPDATE_ID;
    
    /** @brief @~english Create function for creating a new AssetsManagerEx, use local manifest path and storage path as parameters.
     * @~chinese AssetsManagerEx的构造函数，使用本地manifest文件地址和资源存储路径作为参数。
     @param manifestUrl   @~english The url for the local manifest file
     * @~chinese 本地资源manifest文件地址
     @param storagePath   @~english The storage path for downloaded assetes
     * @~chinese 资源的存储路径
     @warning @~english   The cached manifest in your storage path have higher priority and will be searched first,
                only if it doesn't exist, AssetsManagerEx will use the given manifestUrl.
     * @~chinese 资源存储路径中缓存的manifest文件比包内的原始manifest文件有更高的优先级，首先会检索是否有缓存的manifest。
     * 只有当它不存在时，AssetsManagerEx才将使用指定的manifestUrl。
     */
    static AssetsManagerEx* create(const std::string &manifestUrl, const std::string &storagePath);
    
    /** @brief @~english  Check out if there is a new version of manifest.
     *          You may use this method before updating, then let user determine whether
     *          he wants to update resources.
     * @~chinese 检查是否有新版本。
     * 你可以用这种方法在更新之前让用户决定是否要更新资源。
     */
    void checkUpdate();
    
    /** @brief @~english Update with the current local manifest.
     * @~chinese 尝试更新资源
     */
    void update();
    
    /** @brief @~english Reupdate all failed assets under the current AssetsManagerEx context, failed assets are noted in the previous update process.
     * @~chinese 重新下载所有失败的资源，这些失败的资源，是前一次更新过程中记录下来的
     */
    void downloadFailedAssets();
    
    /** @brief @~english Gets the current update state.
     * @~chinese 获取当前更新的状态。
     * @return @~english The current update state.
     * @~chinese 更新状态
     */
    State getState() const;
    
    /** @brief @~english Gets storage path.
     * @~chinese 获取存储路径。
     * @return @~english The storage path.
     * @~chinese 存储路径
     */
    const std::string& getStoragePath() const;
    
    /** @brief @~english Function for retrieve the local manifest object.
     * @~chinese 获取本地资源清单对象。
     * @return @~english The local manifest.
     * @~chinese 本地的资源清单
     */
    const Manifest* getLocalManifest() const;
    
    /** @brief @~english Function for retrieve the remote manifest object
     * @~chinese 获取远程资源清单对象
     * @return @~english The remote manifest.
     * @~chinese 远程的资源清单
     */
    const Manifest* getRemoteManifest() const;
    
CC_CONSTRUCTOR_ACCESS:
    
    AssetsManagerEx(const std::string& manifestUrl, const std::string& storagePath);
    
    virtual ~AssetsManagerEx();
    
protected:
    
    std::string basename(const std::string& path) const;
    
    std::string get(const std::string& key) const;
    
    void initManifests(const std::string& manifestUrl);
    
    void loadLocalManifest(const std::string& manifestUrl);
    
    void prepareLocalManifest();
    
    void setStoragePath(const std::string& storagePath);
    
    void adjustPath(std::string &path);
    
    void dispatchUpdateEvent(EventAssetsManagerEx::EventCode code, const std::string &message = "", const std::string &assetId = "", int curle_code = 0, int curlm_code = 0);
    
    void downloadVersion();
    void parseVersion();
    void downloadManifest();
    void parseManifest();
    void startUpdate();
    void updateSucceed();
    bool decompress(const std::string &filename);
    void decompressDownloadedZip();
    
    /** @brief @~english Update a list of assets under the current AssetsManagerEx context
     * @~chinese 更新一个下载列表中的资源
     */
    void updateAssets(const Downloader::DownloadUnits& assets);
    
    /** @brief @~english Retrieve all failed assets during the last update
     * @~chinese 获取上次更新失败时的失败资源列表
     */
    const Downloader::DownloadUnits& getFailedAssets() const;
    
    /** @brief @~english Function for destorying the downloaded version file and manifest file
     * @~chinese 清除本地已下载版本
     */
    void destroyDownloadedVersion();
    
    /** @brief @~english  Call back function for error handling,
     * the error will then be reported to user's listener registed in EventListenerAssetsManagerEx
     * @~chinese 资源下载失败时的回调函数,
     * 这个错误将被报告给用户在EventListenerAssetsManagerEx中注册的监听器
     * @param error @~english The error object contains ErrorCode, message, asset url, asset key
     * @~chinese 错误的对象包含错误代码、消息、资源URL地址，资源的索引键值
     * @warning @~english AssetsManagerEx internal use only
     * @~chinese 仅限AssetsManagerEx内部使用
     * @js NA
     * @lua NA
     */
    virtual void onError(const Downloader::Error &error);
    
    /** @brief @~english  Call back function for recording downloading percent of the current asset,
     the progression will then be reported to user's listener registed in addUpdateProgressEventListener
     * @~chinese 记录资源下载的百分比的回调函数，
     * 报告的进展将被报告给用户在EventListenerAssetsManagerEx中注册的监听器
     @param total       @~english Total size to download for this asset
     * @~chinese 该资源的总大小
     @param downloaded  @~english Total size already downloaded for this asset
     * @~chinese 该资源已经下载的部分大小
     @param url         @~english The url of this asset
     * @~chinese 该资源的URL地址
     @param customId    @~english The key of this asset
     * @~chinese 该资源的索引键值
     @warning @~english AssetsManagerEx internal use only
     * @~chinese 仅限AssetsManagerEx内部使用
     * @js NA
     * @lua NA
     */
    virtual void onProgress(double total, double downloaded, const std::string &url, const std::string &customId);
    
    /** @brief @~english  Call back function for success of the current asset
     the success event will then be send to user's listener registed in addUpdateEventListener
     * @~chinese 资源下载成功的回调函数
     * 资源下载成功的事件将被发送到在EventListenerAssetsManagerEx中注册的监听器
     @param srcUrl      @~english The url of this asset
     * @~chinese 该资源的url
     @param customId    @~english The key of this asset
     * @~chinese 该资源的索引键值
     @warning @~english AssetsManagerEx internal use only
     * @~chinese 仅限AssetsManagerEx内部使用
     * @js NA
     * @lua NA
     */
    virtual void onSuccess(const std::string &srcUrl, const std::string &storagePath, const std::string &customId);
    
private:
    
    //! The event of the current AssetsManagerEx in event dispatcher
    std::string _eventName;
    
    //! Reference to the global event dispatcher
    EventDispatcher *_eventDispatcher;
    //! Reference to the global file utils
    FileUtils *_fileUtils;
    
    //! State of update
    State _updateState;
    
    //! Downloader
    std::shared_ptr<Downloader> _downloader;
    
    //! The reference to the local assets
    const std::unordered_map<std::string, Manifest::Asset> *_assets;
    
    //! The path to store downloaded resources.
    std::string _storagePath;
    
    //! The local path of cached version file
    std::string _cacheVersionPath;
    
    //! The local path of cached manifest file
    std::string _cacheManifestPath;
    
    //! The local path of cached temporary manifest file
    std::string _tempManifestPath;
    
    //! The path of local manifest file
    std::string _manifestUrl;
    
    //! Local manifest
    Manifest *_localManifest;
    
    //! Local temporary manifest for download resuming
    Manifest *_tempManifest;
    
    //! Remote manifest
    Manifest *_remoteManifest;
    
    //! Whether user have requested to update
    bool _waitToUpdate;
    
    //! All assets unit to download
    Downloader::DownloadUnits _downloadUnits;
    
    //! All failed units
    Downloader::DownloadUnits _failedUnits;
    
    //! All files to be decompressed
    std::vector<std::string> _compressedFiles;
    
    //! Download percent
    float _percent;
    
    //! Download percent by file
    float _percentByFile;
    
    //! Indicate whether the total size should be enabled
    int _totalEnabled;
    
    //! Indicate the number of file whose total size have been collected
    int _sizeCollected;
    
    //! Total file size need to be downloaded (sum of all file)
    double _totalSize;
    
    //! Downloaded size for each file
    std::unordered_map<std::string, double> _downloadedSize;
    
    //! Total number of assets to download
    int _totalToDownload;
    //! Total number of assets still waiting to be downloaded
    int _totalWaitToDownload;
    
    //! Marker for whether the assets manager is inited
    bool _inited;
};

/**
 * // AssetsManager
 * @}
 */

NS_CC_EXT_END

#endif /* defined(__AssetsManagerEx__) */
