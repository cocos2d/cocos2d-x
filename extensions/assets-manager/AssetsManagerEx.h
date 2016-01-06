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

#include <string>
#include <unordered_map>
#include <vector>

#include "base/CCEventDispatcher.h"
#include "platform/CCFileUtils.h"
#include "network/CCDownloader.h"

#include "CCEventAssetsManagerEx.h"

#include "Manifest.h"
#include "extensions/ExtensionMacros.h"
#include "extensions/ExtensionExport.h"
#include "json/document.h"


NS_CC_EXT_BEGIN

/**
 * @brief   This class is used to auto update resources, such as pictures or scripts.
 */
class CC_EX_DLL AssetsManagerEx : public Ref
{
public:
    
    //! Update states
    enum class State
    {
        UNCHECKED,
        PREDOWNLOAD_VERSION,
        DOWNLOADING_VERSION,
        VERSION_LOADED,
        PREDOWNLOAD_MANIFEST,
        DOWNLOADING_MANIFEST,
        MANIFEST_LOADED,
        NEED_UPDATE,
        UPDATING,
        UNZIPPING,
        UP_TO_DATE,
        FAIL_TO_UPDATE
    };
    
    const static std::string VERSION_ID;
    const static std::string MANIFEST_ID;
    
    /** @brief Create function for creating a new AssetsManagerEx
     @param manifestUrl   The url for the local manifest file
     @param storagePath   The storage path for downloaded assetes
     @warning   The cached manifest in your storage path have higher priority and will be searched first,
                only if it doesn't exist, AssetsManagerEx will use the given manifestUrl.
     */
    static AssetsManagerEx* create(const std::string &manifestUrl, const std::string &storagePath);
    
    /** @brief  Check out if there is a new version of manifest.
     *          You may use this method before updating, then let user determine whether
     *          he wants to update resources.
     */
    void checkUpdate();
    
    /** @brief Update with the current local manifest.
     */
    void update();
    
    /** @brief Reupdate all failed assets under the current AssetsManagerEx context
     */
    void downloadFailedAssets();
    
    /** @brief Gets the current update state.
     */
    State getState() const;
    
    /** @brief Gets storage path.
     */
    const std::string& getStoragePath() const;
    
    /** @brief Function for retrieve the local manifest object
     */
    const Manifest* getLocalManifest() const;
    
    /** @brief Function for retrieve the remote manifest object
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
    
    /** @brief Update a list of assets under the current AssetsManagerEx context
     */
    void updateAssets(const DownloadUnits& assets);
    
    /** @brief Retrieve all failed assets during the last update
     */
    const DownloadUnits& getFailedAssets() const;
    
    /** @brief Function for destroying the downloaded version file and manifest file
     */
    void destroyDownloadedVersion();
    
    /** @brief  Call back function for error handling,
     the error will then be reported to user's listener registed in addUpdateEventListener
     @param error   The error object contains ErrorCode, message, asset url, asset key
     @warning AssetsManagerEx internal use only
     * @js NA
     * @lua NA
     */
    virtual void onError(const network::DownloadTask& task,
                         int errorCode,
                         int errorCodeInternal,
                         const std::string& errorStr);
    
    /** @brief  Call back function for recording downloading percent of the current asset,
     the progression will then be reported to user's listener registed in addUpdateProgressEventListener
     @param total       Total size to download for this asset
     @param downloaded  Total size already downloaded for this asset
     @param url         The url of this asset
     @param customId    The key of this asset
     @warning AssetsManagerEx internal use only
     * @js NA
     * @lua NA
     */
    virtual void onProgress(double total, double downloaded, const std::string &url, const std::string &customId);
    
    /** @brief  Call back function for success of the current asset
     the success event will then be send to user's listener registed in addUpdateEventListener
     @param srcUrl      The url of this asset
     @param customId    The key of this asset
     @warning AssetsManagerEx internal use only
     * @js NA
     * @lua NA
     */
    virtual void onSuccess(const std::string &srcUrl, const std::string &storagePath, const std::string &customId);
    
private:
    void batchDownload();
    
    //! The event of the current AssetsManagerEx in event dispatcher
    std::string _eventName;
    
    //! Reference to the global event dispatcher
    EventDispatcher *_eventDispatcher;
    //! Reference to the global file utils
    FileUtils *_fileUtils;
    
    //! State of update
    State _updateState;
    
    //! Downloader
    std::shared_ptr<network::Downloader> _downloader;
    
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
    DownloadUnits _downloadUnits;
    
    //! All failed units
    DownloadUnits _failedUnits;
    
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

NS_CC_EXT_END

#endif /* defined(__AssetsManagerEx__) */
