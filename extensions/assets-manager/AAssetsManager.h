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

#include <mutex>

#include "cocos2d.h"
#include "extensions/ExtensionMacros.h"

NS_CC_EXT_BEGIN

struct Asset {
    std::string md5;
    std::string path;
    int group;
    bool updating;
};

/*
 *  This class is used to auto update resources, such as pictures or scripts.
 *  The updated package should be a zip file. And there should be a file named
 *  version in the server, which contains version code.
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
    
    AAssetsManager();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~AAssetsManager();
    
    /* @brief To access within scripting environment
     */
    static AAssetsManager* create();
    
    /* @brief Check out if there is a new version resource.
     *        You may use this method before updating, then let user determine whether
     *        he wants to update resources.
     */
    virtual bool checkUpdate();
    
    virtual void update();
    
    /* @brief Gets url of package.
     */
    const char* getPackageUrl() const;
    
    /* @brief Sets package url.
     */
    void setPackageUrl(const char* packageUrl);
    
    /* @brief Gets version file url.
     */
    const char* getVersionFileUrl() const;
    
    /* @brief Gets version file url.
     */
    void setVersionFileUrl(const char* versionFileUrl);
    
    /* @brief Gets current version code.
     */
    std::string getVersion();
    
    /* @brief Deletes recorded version code.
     */
    void deleteVersion();
    
    /* @brief Gets storage path.
     */
    const char* getStoragePath() const;
    
    /* @brief Sets storage path.
     *
     * @param storagePath The path to store downloaded resources.
     * @warm The path should be a valid path.
     */
    void setStoragePath(const char* storagePath);
    
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
    
    std::string _manifestUrl;
    
    std::string _versionUrl;
    
    std::string _remoteUrl;
    
    //! The version of downloaded resources.
    std::string _currentVer;
    
    std::string _groupVer;
    
    std::string _engineVer;
    
    std::string _remoteManifestVer;
    
    std::string _remoteGroupVer;
    
    std::string _remoteEngineVer;
    
    ValueMap* _assets;
    
    
    
    
    std::string _packageUrl;
    std::string _versionFileUrl;
    
    std::string _downloadedVersion;
    
    void *_curl;
    
    unsigned int _connectionTimeout;
    
    bool _isDownloading;
    bool _shouldDeleteDelegateWhenExit;
};

NS_CC_EXT_END;

#endif /* defined(__AAssetsManager__) */
