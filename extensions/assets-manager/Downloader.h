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

#include "platform/CCFileUtils.h"
#include "extensions/ExtensionMacros.h"
#include "extensions/ExtensionExport.h"

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>

NS_CC_EXT_BEGIN

class CC_EX_DLL Downloader : public std::enable_shared_from_this<Downloader>
{
public:

    friend class AssetsManagerEx;

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

        INVALID_STORAGE_PATH,
        
        PREPARE_HEADER_ERROR
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
        bool resumeDownload;
    };
    
    struct StreamData
    {
        long offset;
        long total;
        unsigned char *buffer;
    };
    
    struct HeaderInfo
    {
        bool valid;
        std::string url;
        std::string contentType;
        double contentSize;
        long responseCode;
    };
    
    typedef std::unordered_map<std::string, DownloadUnit> DownloadUnits;
    
    typedef std::function<void(const Downloader::Error &)> ErrorCallback;
    typedef std::function<void(double, double, const std::string &, const std::string &)> ProgressCallback;
    typedef std::function<void(const std::string &, const std::string &, const std::string &)> SuccessCallback;
    typedef std::function<void(const std::string &, const HeaderInfo &)> HeaderCallback;

    int getConnectionTimeout();

    void setConnectionTimeout(int timeout);
    
    void setErrorCallback(const ErrorCallback &callback) { _onError = callback; };
    
    void setProgressCallback(const ProgressCallback &callback) { _onProgress = callback; };
    
    void setSuccessCallback(const SuccessCallback &callback) { _onSuccess = callback; };
    
    void setHeaderCallback(const HeaderCallback &callback) { _onHeader = callback; };

    ErrorCallback getErrorCallback() const { return _onError; };

    ProgressCallback getProgressCallback() const { return _onProgress; };

    SuccessCallback getSuccessCallback() const { return _onSuccess; };
    
    HeaderCallback getHeaderCallback() const { return _onHeader; };
    
    long getContentSize(const std::string &srcUrl);
    
    HeaderInfo getHeader(const std::string &srcUrl);
    
    void getHeaderAsync(const std::string &srcUrl, const HeaderCallback &callback);
    
    void downloadToBufferAsync(const std::string &srcUrl, unsigned char *buffer, const long &size, const std::string &customId = "");
    
    void downloadToBufferSync(const std::string &srcUrl, unsigned char *buffer, const long &size, const std::string &customId = "");

    void downloadAsync(const std::string &srcUrl, const std::string &storagePath, const std::string &customId = "");

    void downloadSync(const std::string &srcUrl, const std::string &storagePath, const std::string &customId = "");
    
    void batchDownloadAsync(const DownloadUnits &units, const std::string &batchId = "");
    
    void batchDownloadSync(const DownloadUnits &units, const std::string &batchId = "");

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

    void prepareDownload(const std::string &srcUrl, const std::string &storagePath, const std::string &customId, bool resumeDownload, FileDescriptor *fDesc, ProgressData *pData);
    
    HeaderInfo prepareHeader(const std::string &srcUrl, void* header = nullptr);
    
    void downloadToBuffer(const std::string &srcUrl, const std::string &customId, const StreamData &buffer, const ProgressData &data);

    void download(const std::string &srcUrl, const std::string &customId, const FileDescriptor &fDesc, const ProgressData &data);
    
    void groupBatchDownload(const DownloadUnits &units);

    void notifyError(ErrorCode code, const std::string &msg = "", const std::string &customId = "", int curle_code = 0, int curlm_code = 0);
    
    void notifyError(const std::string &msg, int curlm_code, const std::string &customId = "");
    
    void notifyError(const std::string &msg, const std::string &customId, int curle_code);

private:

    int _connectionTimeout;

    ErrorCallback _onError;

    ProgressCallback _onProgress;

    SuccessCallback _onSuccess;
    
    HeaderCallback _onHeader;

    std::string getFileNameFromUrl(const std::string &srcUrl);
    
    void clearBatchDownloadData();
    
    std::vector<FileDescriptor *> _files;
    
    std::vector<ProgressData *> _progDatas;
    
    FileUtils *_fileUtils;
    
    bool _supportResuming;
};

int downloadProgressFunc(Downloader::ProgressData *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded);

NS_CC_EXT_END

#endif /* defined(__Downloader__) */