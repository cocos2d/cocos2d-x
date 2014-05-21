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

#ifndef __Downloader__
#define __Downloader__

#include "cocos2d.h"
#include "extensions/ExtensionMacros.h"

NS_CC_EXT_BEGIN

class DownloaderDelegateProtocol;

class CC_DLL Downloader
{
public:
    enum class ErrorCode
    {
        CREATE_FILE,
        
        NETWORK,
        
        NO_NEW_VERSION,
        
        UNCOMPRESS,
        
        CURL_UNINIT,
        
        INVALID_URL,
        
        INVALID_STORAGE_PATH
    };
    
    struct Error
    {
        ErrorCode code;
        std::string message;
        std::string customId;
        std::string url;
    };
    
    struct ProgressData
    {
        Downloader* downloader;
        std::string customId;
        std::string url;
        double downloaded;
    };
    
    struct DownloadUnit
    {
        std::string srcUrl;
        std::string storagePath;
        std::string customId;
    };
    
    /**
     *  The default constructor.
     */
    Downloader(DownloaderDelegateProtocol* delegate);
    
    DownloaderDelegateProtocol* getDelegate() const { return _delegate ;}
    
    int getConnectionTimeout();
    
    void setConnectionTimeout(int timeout);
    
    void downloadAsync(const std::string &srcUrl, const std::string &storagePath, const std::string &customId = "");
    
    void downloadSync(const std::string &srcUrl, const std::string &storagePath, const std::string &customId = "");
    
    void batchDownload(const std::map<std::string, DownloadUnit> &units);
    
protected:
    
    FILE *prepareDownload(const std::string &srcUrl, const std::string &storagePath, const std::string &customId);
    
    void download(const std::string &srcUrl, FILE *fp, const std::string &customId);
    
    void notifyError(ErrorCode code, const std::string &msg = "", const std::string &customId = "");
    
private:
    
    int _connectionTimeout;
    
    DownloaderDelegateProtocol* _delegate;
    
    std::string getFileNameFormUrl(const std::string &srcUrl);
};

class DownloaderDelegateProtocol
{
public:
    virtual ~DownloaderDelegateProtocol() {};
    
    /** @brief  Call back function for error handling,
     the error will then be reported to user's listener registed in addUpdateEventListener
     @param error   The error object contains ErrorCode, message, asset url, asset key
     @warning AssetsManager internal use only
     * @js NA
     * @lua NA
     */
    virtual void onError(const Downloader::Error &error) {};
    
    /** @brief  Call back function for recording downloading percent of the current asset,
     the progression will then be reported to user's listener registed in addUpdateProgressEventListener
     @param total       Total size to download for this asset
     @param downloaded  Total size already downloaded for this asset
     @param url         The url of this asset
     @param customId    The key of this asset
     @warning AssetsManager internal use only
     * @js NA
     * @lua NA
     */
    virtual void onProgress(double total, double downloaded, const std::string &url, const std::string &customId) {};
    
    /** @brief  Call back function for success of the current asset
     the success event will then be send to user's listener registed in addUpdateEventListener
     @param srcUrl      The url of this asset
     @param customId    The key of this asset
     @warning AssetsManager internal use only
     * @js NA
     * @lua NA
     */
    virtual void onSuccess(const std::string &srcUrl, const std::string &customId) {};
};

NS_CC_EXT_END;

#endif /* defined(__Downloader__) */
