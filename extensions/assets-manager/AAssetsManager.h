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
#include <mutex>

#include "cocos2d.h"
#include "Downloader.h"
#include "extensions/ExtensionMacros.h"
#include "json/document.h"

NS_CC_EXT_BEGIN

struct Asset {
    std::string md5;
    std::string path;
    std::string group;
    bool updating;
};

/*
 *  This class is used to auto update resources, such as pictures or scripts.
 */
class AAssetsManager : public Ref, DownloaderDelegateProtocol
{
public:
    enum class ErrorCode
    {
        // Error caused by creating a file to store downloaded data
        CREATE_FILE,
        /** Error caused by network
         -- network unavaivable
         -- timeout
         -- ...
         */
        NETWORK,
        /** There is not a new version
         */
        NO_NEW_VERSION,
        /** Error caused in uncompressing stage
         -- can not open zip file
         -- can not read file global information
         -- can not read file information
         -- can not create a directory
         -- ...
         */
        UNCOMPRESS,
    };
    
    //! The root of writable path
    static std::string s_nWritableRoot;
    
    AAssetsManager(const std::string& manifestUrl = NULL, const std::string& storagePath = "");
    /**
     * @js NA
     * @lua NA
     */
    virtual ~AAssetsManager();
    
    /* @brief To access within scripting environment
     */
    static AAssetsManager* create(const std::string& manifestUrl, const std::string& storagePath = "");
    
    /* @brief Check out if there is a new version of manifest.
     *        You may use this method before updating, then let user determine whether
     *        he wants to update resources.
     */
    virtual bool checkUpdate();
    
    //virtual void update();
    
    /* @brief Gets url of a asset for the given key.
     */
    const std::string& get(const std::string& key) const;
    
    /* @brief Gets loaded event name for the resource of the given key
     */
    std::string getLoadedEventName(const std::string& key);
    
    /* @brief Gets storage path.
     */
    const std::string& getStoragePath() const;
    
    /* @brief Sets storage path.
     *
     * @param storagePath The path to store downloaded resources.
     * @warm The path should be a valid path.
     */
    void setStoragePath(const std::string& storagePath);
    
    /* @brief Gets url of manifest.
     */
    const std::string& getManifestUrl() const;
    
    /* @brief Sets package url.
     */
    void setManifestUrl(const std::string& manifestUrl);
    
    /* @brief Gets version file url.
     */
    const std::string& getVersionFileUrl() const;
    
    /* @brief Sets version file url.
     */
    void setVersionFileUrl(const std::string& versionFileUrl);
    
    /* @brief Gets remote package url.
     */
    const std::string& getRemoteRootUrl() const;
    
    /* @brief Gets local manifest version.
     */
    const std::string& getLocalManifestVersion() const;
    
    /* @brief Gets local version for the given group.
     */
    const std::string& getLocalGroupVersion(int group) const;
    
    /* @brief Gets local engine version.
     */
    const std::string& getLocalEngineVersion() const;
    
    /* @brief Gets remote manifest version.
     */
    const std::string& getRemoteManifestVersion() const;
    
    /* @brief Gets remote version for the given group.
     */
    const std::string& getRemoteGroupVersion(int group) const;
    
    /* @brief Gets remote engine version.
     */
    const std::string& getRemoteEngineVersion() const;
    
    /** @brief Sets connection time out in seconds
     */
    void setConnectionTimeout(unsigned int timeout);
    
    /** @brief Gets connection time out in secondes
     */
    unsigned int getConnectionTimeout();
    
    
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
    virtual void onSuccess(const std::string &srcUrl, const std::string &customId, const std::string &filename);
    
protected:
    void loadManifest();
    Asset parseAsset(const rapidjson::Value& json);
    bool downLoad();
    void adjustStoragePath();
    bool uncompress();
    bool createDirectory(const std::string& path);
    void prependSearchPath(const std::string& path);
    void downloadAndUncompress();
    
private:
    /** @brief Initializes storage path.
     */
    void createStoragePath();
    
    /** @brief Destroys storage path.
     */
    void destroyStoragePath();
    
private:
    
    EventDispatcher *_eventDispatcher;
    
    //! The path to store downloaded resources.
    std::string _storagePath;
    
    //! The path of local manifest file
    std::string _manifestUrl;
    
    //! The remote path of manifest file
    std::string _remoteManifestUrl;
    
    //! The remote path of version file [Optional]
    std::string _remoteVersionUrl;
    
    //! The url of remote package's root
    std::string _remoteUrl;
    
    //! The version of local manifest
    std::string _currentVer;
    
    //! All groups exist in manifest
    std::vector<std::string> _groups;
    
    //! The versions of all local group
    std::map<std::string, std::string> _groupVer;
    
    //! The version of local engine
    std::string _engineVer;
    
    //! The version of remote manifest
    std::string _remoteManifestVer;
    
    //! The versions of all remote group
    std::map<int, std::string> _remoteGroupVer;
    
    //! The version of remote engine
    std::string _remoteEngineVer;
    
    //! Full assets list
    std::map<std::string, Asset> _assets;
    
    //! Indicate whether the manifest file have been parsed
    bool _manifestLoaded;
    
    //! Time out configuration for connection
    unsigned int _connectionTimeout;
    
    //! CURL ref
    void*_curl;
    
    //! Downloader
    Downloader* _downloader;
    
    //! Indicate whether AssetsManager is downloading assets
    bool _isDownloading;
};

NS_CC_EXT_END;

#endif /* defined(__AAssetsManager__) */
