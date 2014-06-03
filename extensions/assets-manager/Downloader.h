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

#include <unordered_map>
#include <memory>
#include <string>

NS_CC_EXT_BEGIN

class CC_DLL Downloader : public std::enable_shared_from_this<Downloader>
{
public:

    friend class AssetsManager;

    enum class ErrorCode
    {
        CREATE_FILE,

        NETWORK,

        NO_NEW_VERSION,

        UNCOMPRESS,

        CURL_UNINIT,
        
        CURL_MULTI_ERROR,
        
        CURL_EASY_ERROR,

        INVALID_URL,

        INVALID_STORAGE_PATH
    };

    struct Error
    {
        ErrorCode code;
        int curlm_code;
        int curle_code;
        std::string message;
        std::string customId;
        std::string url;
    };

    struct ProgressData
    {
        std::weak_ptr<Downloader> downloader;
        std::string customId;
        std::string url;
        std::string path;
        std::string name;
        double downloaded;
        double totalToDownload;
    };

    struct DownloadUnit
    {
        std::string srcUrl;
        std::string storagePath;
        std::string customId;
    };

    int getConnectionTimeout();

    void setConnectionTimeout(int timeout);

    std::function<void(const Downloader::Error &)> getErrorCallback() const { return _onError; };

    std::function<void(double, double, const std::string &, const std::string &)> getProgressCallback() const { return _onProgress; };

    std::function<void(const std::string &, const std::string &, const std::string &)> getSuccessCallback() const { return _onSuccess; };

    void downloadAsync(const std::string &srcUrl, const std::string &storagePath, const std::string &customId = "");

    void downloadSync(const std::string &srcUrl, const std::string &storagePath, const std::string &customId = "");
    
    void batchDownloadAsync(const std::unordered_map<std::string, DownloadUnit> &units, const std::string &batchId = "");
    
    void batchDownloadSync(const std::unordered_map<std::string, DownloadUnit> &units, const std::string &batchId = "");

    /**
     *  The default constructor.
     */
    Downloader();

    ~Downloader();

protected:
    
    struct FileDescriptor
    {
        FILE *fp;
        void *curl;
    };

    void prepareDownload(const std::string &srcUrl, const std::string &storagePath, const std::string &customId, FileDescriptor *fDesc, ProgressData *pData);

    void download(const std::string &srcUrl, const std::string &customId, const FileDescriptor &fDesc, const ProgressData &data);

    void notifyError(ErrorCode code, const std::string &msg = "", const std::string &customId = "", int curle_code = 0, int curlm_code = 0);
    
    void notifyError(const std::string &msg, int curlm_code, const std::string &customId = "");
    
    void notifyError(const std::string &msg, const std::string &customId, int curle_code);

private:

    int _connectionTimeout;

    std::function<void(const Downloader::Error &)> _onError;

    std::function<void(double, double, const std::string &, const std::string &)> _onProgress;

    std::function<void(const std::string &, const std::string &, const std::string &)> _onSuccess;

    std::string getFileNameFromUrl(const std::string &srcUrl);
    
    void clearBatchDownloadData();
    
    std::vector<FileDescriptor *> _files;
    
    std::vector<ProgressData *> _progDatas;

    void* _threadPool;
};

int downloadProgressFunc(Downloader::ProgressData *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded);

NS_CC_EXT_END

#endif /* defined(__Downloader__) */
