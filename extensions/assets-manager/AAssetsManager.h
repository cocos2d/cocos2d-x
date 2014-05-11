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
class AAssetsManager : public Ref
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
    
    AAssetsManager(const char* manifestUrl = NULL, const char* storagePath = "");
    /**
     * @js NA
     * @lua NA
     */
    virtual ~AAssetsManager();
    
    /* @brief To access within scripting environment
     */
    static AAssetsManager* create(const char* manifestUrl, const char* storagePath = "");
    
    /* @brief Check out if there is a new version of manifest.
     *        You may use this method before updating, then let user determine whether
     *        he wants to update resources.
     */
    //virtual bool checkUpdate();
    
    //virtual void update();
    
    /* @brief Gets url of a asset for the given key.
     */
    const char* get(const char* key) const;
    
    /* @brief Gets storage path.
     */
    const char* getStoragePath() const;
    
    /* @brief Sets storage path.
     *
     * @param storagePath The path to store downloaded resources.
     * @warm The path should be a valid path.
     */
    void setStoragePath(const char* storagePath);
    
    /* @brief Gets url of manifest.
     */
    const char* getManifestUrl() const;
    
    /* @brief Sets package url.
     */
    void setManifestUrl(const char* manifestUrl);
    
    /* @brief Gets version file url.
     */
    const char* getVersionFileUrl() const;
    
    /* @brief Sets version file url.
     */
    void setVersionFileUrl(const char* versionFileUrl);
    
    /* @brief Gets remote package url.
     */
    const char* getRemoteRootUrl() const;
    
    /* @brief Gets local manifest version.
     */
    const char* getLocalManifestVersion() const;
    
    /* @brief Gets local version for the given group.
     */
    const char* getLocalGroupVersion(int group) const;
    
    /* @brief Gets local engine version.
     */
    const char* getLocalEngineVersion() const;
    
    /* @brief Gets remote manifest version.
     */
    const char* getRemoteManifestVersion() const;
    
    /* @brief Gets remote version for the given group.
     */
    const char* getRemoteGroupVersion(int group) const;
    
    /* @brief Gets remote engine version.
     */
    const char* getRemoteEngineVersion() const;
    
    /** @brief Sets connection time out in seconds
     */
    void setConnectionTimeout(unsigned int timeout);
    
    /** @brief Gets connection time out in secondes
     */
    unsigned int getConnectionTimeout();
    
    
    /* downloadAndUncompress is the entry of a new thread
     */
    friend int assetsManagerProgressFunc(void *, double, double, double, double);
    
protected:
    void loadManifest();
    Asset parseAsset(const rapidjson::Value& json);
    bool downLoad();
    void checkStoragePath();
    bool uncompress();
    bool createDirectory(const char *path);
    void setSearchPath();
    void downloadAndUncompress();
    
private:
    /** @brief Initializes storage path.
     */
    void createStoragePath();
    
    /** @brief Destroys storage path.
     */
    void destroyStoragePath();
    
private:
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
    void *_curl;
    
    //! Indicate whether AssetsManager is downloading assets
    bool _isDownloading;
};

NS_CC_EXT_END;

#endif /* defined(__AAssetsManager__) */
