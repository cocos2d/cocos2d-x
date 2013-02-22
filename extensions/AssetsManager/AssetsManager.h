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
#include <curl/curl.h>

class AssetsManagerProtocol;

/* 
 *  This class is used to auto update resources, such as pictures or scripts.
 *  The updated package should be a zip file. And there should be a file named
 *  version in the server, which contains version code.
 */
class AssetsManager
{
public:
    enum ErrorCode
    {
        ServerNotAvailable,    /** server address error or timeout */
        TimeOut,
    };
    
    //! Default constructor. You should set server address later.
    AssetsManager();
    
    /* @brief Creates a AssetsManager with new package url and version code url.
     *        AssetsManager will use the value returned by CCFileUtils::getWritablePath() as storage path.
     *
     * @param packageUrl URL of new package, the package should be a zip file.
     * @param versionFileUrl URL of version file. It should contain version code of new package.
     */
    AssetsManager(const char* packageUrl, const char* versionFileUrl);
    
    /* @brief Creates a AssetsManager with new package url, version code url and storage path.
     *
     * @param packageUrl URL of new package, the package should be a zip file.
     * @param versionFileUrl URL of version file. It should contain version code of new package.
     * @param storagePath The path to store downloaded resources.
     */
    AssetsManager(const char* packageUrl, const char* versionFileUrl, const char* storagePath);
    
    /* @brief Check out if there is a new version resource.
     *        You may use this method before updating, then let user determine whether
     *        he wants to update resources.
     */
    virtual bool checkUpdate();
    
    virtual void update();
    
    /* @brief Gets url of package.
     */
    const char* getPackageUrl() const;
    
    /* @brief Sets url of package.
     *
     * @param packageUrl Package url.
     */
    void setPackageUrl(const char* packageUrl);
    
    const char* getVersionFileUrl() const;
    void setVersionFileUrl(const char* versionFileUrl);
    
    /* @brief Gets storage path.
     */
    const char* getStoragePath() const;
    
    /* @brief Sets storage path.
     *
     * @param storagePath The path to store downloaded resources.
     */
    void setStoragePath(const char* storagePath);
    
protected:
    bool downLoad();
    void checkStoragePath();
    bool uncompress();
    bool createDirectory(const char *path);
    void setSearchPath();
    
private:
    //! The path to store downloaded resources.
    std::string _storagePath;
    
    //! The version of downloaded resources.
    std::string _version;
    
    std::string _packageUrl;
    std::string _versionFileUrl;
    
    AssetsManagerProtocol* _delegate;
    
    CURL *_curl;
};

/* @brief This class is used as base class of the delegate of AssetsManager.
 */
class AssetsManagerProtocol
{
public:
    /* @brief When an error happens in updating resources, AssetsManager will invoke its delegate's onError().
     *
     * @param errorCode The pointer to record error code.
     *                  The value will be set by AssetsManager.
     */
    virtual void onError(AssetsManager::ErrorCode* errorCode) = 0;
    
    virtual void onUpdate(float* percent) = 0;
};


#endif /* defined(__AssetsManager__) */
