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
        std::weak_ptr<Downloader> downloader;
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

    int getConnectionTimeout();

    void setConnectionTimeout(int timeout);

    std::function<void(const Downloader::Error &)> getErrorCallback() const { return _onError; };

    std::function<void(double, double, const std::string &, const std::string &)> getProgressCallback() const { return _onProgress; };

    std::function<void(const std::string &, const std::string &)> getSuccessCallback() const { return _onSuccess; };

    void downloadAsync(const std::string &srcUrl, const std::string &storagePath, const std::string &customId = "");

    void downloadSync(const std::string &srcUrl, const std::string &storagePath, const std::string &customId = "");

    void batchDownload(const std::unordered_map<std::string, DownloadUnit> &units);

    /**
     *  The default constructor.
     */
    Downloader();

    ~Downloader();

protected:

    FILE *prepareDownload(const std::string &srcUrl, const std::string &storagePath, const std::string &customId);

    void download(const std::string &srcUrl, FILE *fp, const std::string &customId);

    void notifyError(ErrorCode code, const std::string &msg = "", const std::string &customId = "");

private:

    int _connectionTimeout;

    std::function<void(const Downloader::Error &)> _onError;

    std::function<void(double, double, const std::string &, const std::string &)> _onProgress;

    std::function<void(const std::string &, const std::string &)> _onSuccess;

    std::string getFileNameFromUrl(const std::string &srcUrl);

    void* _threadPool;
};

NS_CC_EXT_END

#endif /* defined(__Downloader__) */
