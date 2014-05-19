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

#ifndef __AAssetsManager__
#define __AAssetsManager__

#include <string>
#include <map>
#include <vector>

#include "cocos2d.h"
#include "Downloader.h"
#include "Manifest.h"
#include "extensions/ExtensionMacros.h"
#include "json/document.h"

NS_CC_EXT_BEGIN

/*
 *  This class is used to auto update resources, such as pictures or scripts.
 */
class AAssetsManager : public Ref, DownloaderDelegateProtocol
{
public:
    enum UpdateEventCode
    {
        NEW_VERSION_FOUND,
        
        ALREADY_UP_TO_DATE,
        
        UPDATING_ERROR,
        
        FINISHED_UPDATE,
        
        FINISHED_WITH_ERROR,
        
        UNCOMPRESS_ERROR,
    };
    
    struct UpdateEvent
    {
        UpdateEventCode code;
        std::string message;
        std::string assetId;
        AAssetsManager *manager;
    };
    
    enum UpdateState
    {
        UNKNOWN,
        CHECKING,
        PREDOWNLOAD_VERSION,
        DOWNLOADING_VERSION,
        VERSION_LOADED,
        PREDOWNLOAD_MANIFEST,
        DOWNLOADING_MANIFEST,
        MANIFEST_LOADED,
        NEED_UPDATE,
        UPDATING,
        UP_TO_DATE
    };
    
    //! The root of writable path
    static std::string s_nWritableRoot;
    
    AAssetsManager(const std::string &managerId, const std::string& manifestUrl = NULL, const std::string& storagePath = "");
    /**
     * @js NA
     * @lua NA
     */
    virtual ~AAssetsManager();
    
    /* @brief To access within scripting environment
     */
    static AAssetsManager* create(const std::string &managerId, const std::string &manifestUrl, const std::string &storagePath = "");
    
    
    /* @brief Check out if there is a new version of manifest.
     *        You may use this method before updating, then let user determine whether
     *        he wants to update resources.
     */
    void checkUpdate();
    
    void update();
    
    UpdateState updateState();
    
    std::string getLoadedEventName(const std::string& key);
    
    /* @brief Gets url of a asset for the given key.
     */
    std::string get(const std::string& key) const;
    
    /* @brief Gets storage path.
     */
    const std::string& getStoragePath() const;
    
    /* @brief Sets storage path.
     *
     * @param storagePath The path to store downloaded resources.
     * @warm The path should be a valid path.
     */
    void setStoragePath(const std::string& storagePath);
    
    const Manifest* getLocalManifest();
    
    void addUpdateEventListener(const std::function<void(EventCustom*)>& callback, int priority = 1);
    
    void addUpdateProgressEventListener(const std::function<void(EventCustom*)>& callback, int priority = 1);
    
    void addNoLocalManifestErrorListener(const std::function<void(EventCustom*)>& callback, int priority = 1);
    
    
    /* @brief Call back function for error
     @param errorCode Type of error
     * @js NA
     * @lua NA
     */
    virtual void onError(const Downloader::Error &error);
    
    /** @brief Call back function for recording downloading percent
     @param percent How much percent downloaded
     @warning    This call back function just for recording downloading percent.
     AssetsManager will do some other thing after downloading, you should
     write code in onSuccess() after downloading.
     * @js NA
     * @lua NA
     */
    virtual void onProgress(double total, double downloaded, const std::string &url, const std::string &customId);
    
    /** @brief Call back function for success
     * @js NA
     * @lua NA
     */
    virtual void onSuccess(const std::string &srcUrl, const std::string &customId);
    
protected:
    void loadManifest(const std::string& manifestUrl);
    void setLocalManifest(Manifest *manifest);
    void adjustPath(std::string &path);
    void prependSearchPath(const std::string &path);
    
    void dispatchUpdateEvent(UpdateEventCode code, std::string message = "", std::string assetId = "");
    //bool uncompress();
    //void downloadAndUncompress();
    
private:
    
    void createDirectory(const std::string &path);
    
    void destroyDirectory(const std::string &path);
    
    void destroyFile(const std::string &path);
    
private:
    
    std::string _managerId;
    
    EventDispatcher *_eventDispatcher;
    FileUtils *_fileUtils;
    
    UpdateState _updateState;
    
    bool _waitToUpdate;
    
    std::map<std::string, Downloader::DownloadUnit> _downloadUnits;
    
    int _totalToDownload;
    int _totalWaitToDownload;
    
    const std::map<std::string, Manifest::Asset> *_assets;
    
    //! The path to store downloaded resources.
    std::string _storagePath;
    
    //! The path of local manifest file
    std::string _manifestUrl;
    
    //! Local manifest
    Manifest *_localManifest;
    
    //! Remote manifest
    Manifest *_remoteManifest;
    
    //! Downloader
    Downloader* _downloader;
};

NS_CC_EXT_END;

#endif /* defined(__AAssetsManager__) */
