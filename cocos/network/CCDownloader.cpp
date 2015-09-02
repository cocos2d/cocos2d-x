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

#include "network/CCDownloader.h"

#include <curl/curl.h>
#include <curl/easy.h>
#include <cstdio>
#include <cerrno>
#include <thread>

#include "network/CCDownloaderImpl.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "deprecated/CCString.h"

namespace cocos2d {
namespace network {


#define LOW_SPEED_LIMIT     1L
#define LOW_SPEED_TIME      5L
#define MAX_REDIRS          2
#define DEFAULT_TIMEOUT     5
#define HTTP_CODE_SUPPORT_RESUME    206
#define MAX_WAIT_MSECS 30*1000 /* Wait max. 30 seconds */

#define TEMP_EXT            ".temp"

Downloader::Downloader()
: _connectionTimeout(DEFAULT_TIMEOUT)
, _onError(nullptr)
, _onProgress(nullptr)
, _onSuccess(nullptr)
, _supportResuming(false)
, _downloaderImpl(nullptr)
{
    _fileUtils = FileUtils::getInstance();
    _downloaderImpl = new DownloaderImpl();
    _downloaderImpl->init();
}

Downloader::~Downloader()
{
    CC_SAFE_DELETE(_downloaderImpl);
}

int Downloader::getConnectionTimeout()
{
    return _connectionTimeout;
}

void Downloader::setConnectionTimeout(int timeout)
{
    if (timeout >= 0)
        _connectionTimeout = timeout;
}

void Downloader::notifyError(ErrorCode code, const std::string& msg/* ="" */, const std::string& customId/* ="" */, int curle_code/* = CURLE_OK*/, int curlm_code/* = CURLM_OK*/)
{
    std::weak_ptr<Downloader> ptr = shared_from_this();
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
        if (!ptr.expired())
        {
            std::shared_ptr<Downloader> downloader = ptr.lock();
            if (downloader->_onError != nullptr)
            {
                Error err;
                err.code = code;
                err.curle_code = curle_code;
                err.curlm_code = curlm_code;
                err.message = msg;
                err.customId = customId;
                downloader->_onError(err);
            }
        }
    });
}

void Downloader::notifyError(const std::string& msg, int curlm_code, const std::string& customId/* = ""*/)
{
    notifyError(ErrorCode::CURL_MULTI_ERROR, msg, customId, CURLE_OK, curlm_code);
}

void Downloader::notifyError(const std::string& msg, const std::string& customId, int curle_code)
{
    notifyError(ErrorCode::CURL_EASY_ERROR, msg, customId, curle_code);
}

std::string Downloader::getFileNameFromUrl(const std::string& srcUrl)
{
    // Find file name and file extension
    std::string filename;
    unsigned long found = srcUrl.find_last_of("/\\");
    if (found != std::string::npos)
        filename = srcUrl.substr(found+1);
    return filename;
}

void Downloader::prepareDownload(const DownloadUnit& downloadUnit)
{
    std::string name = "";
    std::string path = "";

    FILE *localFP = nullptr;

    downloadUnit.downloaded = 0;
    downloadUnit.totalToDownload = 0;

    Error err;
    err.customId = downloadUnit.customId;
    
    // Asserts
    // Find file name and file extension
    unsigned long found = downloadUnit.storagePath.find_last_of("/\\");
    if (found != std::string::npos)
    {
        name = downloadUnit.storagePath.substr(found+1);
        path = downloadUnit.storagePath.substr(0, found+1);
    }
    else
    {
        err.code = ErrorCode::INVALID_URL;
        err.message = "Invalid url or filename not exist error: " + downloadUnit.srcUrl;
        if (this->_onError)
            this->_onError(err);
        downloadUnit.fp = nullptr;
        return;
    }

    // create possible subdirectories
    if (!FileUtils::getInstance()->isDirectoryExist(path))
        FileUtils::getInstance()->createDirectory(path);
    
    // Create a file to save file.
    const std::string outFileName = downloadUnit.storagePath + TEMP_EXT;
    if (_supportResuming && downloadUnit.resumeDownload && _fileUtils->isFileExist(outFileName))
    {
        localFP = fopen(FileUtils::getInstance()->getSuitableFOpen(outFileName).c_str(), "ab");
    }
    else
    {
        localFP = fopen(FileUtils::getInstance()->getSuitableFOpen(outFileName).c_str(), "wb");
    }
    if (!localFP)
    {
        err.code = ErrorCode::CREATE_FILE;
        err.message = StringUtils::format("Can not create file %s: errno %d", outFileName.c_str(), errno);
        if (this->_onError)
            this->_onError(err);
    }

    downloadUnit.fp = localFP;
}

void Downloader::downloadToBufferAsync(const std::string& srcUrl, unsigned char *buffer, long size, const std::string& customId/* = ""*/)
{
    if (buffer != nullptr)
    {
        auto t = std::thread(&Downloader::downloadToBuffer, this, srcUrl, customId, buffer, size);
        t.detach();
    }
}

void Downloader::downloadToBufferSync(const std::string& srcUrl, unsigned char *buffer, long size, const std::string& customId/* = ""*/)
{
    if (buffer != nullptr)
    {
        downloadToBuffer(srcUrl, customId, buffer, size);
    }
}

void Downloader::downloadToBuffer(const std::string& srcUrl, const std::string& customId, unsigned char* buffer, long size)
{
    CC_ASSERT(buffer && "must not be nill");

    CC_ASSERT(_downloaderImpl && "Cannot instanciate more than one instance of DownloaderImpl");

    std::weak_ptr<Downloader> ptr = shared_from_this();
    std::shared_ptr<Downloader> shared = ptr.lock();

    StreamData streamBuffer;
    streamBuffer.buffer = buffer;
    streamBuffer.total = size;
    streamBuffer.offset = 0;

    DownloadUnit unit;
    unit.srcUrl = srcUrl;
    unit.customId = customId;
    unit.fp = &streamBuffer;
    unit.downloaded = 0;
    unit.totalToDownload = 0;

    int res = _downloaderImpl->performDownload(&unit,
                                               std::bind(&Downloader::bufferWriteFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4),
                                               std::bind(&Downloader::downloadProgressFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
                                      );
    // Download pacakge
    if (res != 0)
    {
        std::string msg = StringUtils::format("Unable to download file to buffer: [curl error]%s", _downloaderImpl->getStrError().c_str());
        this->notifyError(msg, customId, res);
    }
    else
    {
        if (std::this_thread::get_id() != Director::getInstance()->getCocos2dThreadId())
        {
            std::weak_ptr<Downloader> ptr = shared_from_this();
            std::shared_ptr<Downloader> shared = ptr.lock();

            Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
                if (!ptr.expired())
                {
                    std::shared_ptr<Downloader> downloader = ptr.lock();
                    reportDownloadFinished(unit.srcUrl, "", unit.customId);
                }
            });
        }
        else
        {
            reportDownloadFinished(unit.srcUrl, "", unit.customId);
        }
    }
}

void Downloader::downloadAsync(const std::string& srcUrl, const std::string& storagePath, const std::string& customId/* = ""*/)
{
    auto t = std::thread(&Downloader::downloadToFP, this, srcUrl, customId, storagePath);
    t.detach();
}

void Downloader::downloadSync(const std::string& srcUrl, const std::string& storagePath, const std::string& customId/* = ""*/)
{
    downloadToFP(srcUrl, customId, storagePath);
}

void Downloader::downloadToFP(const std::string& srcUrl, const std::string& customId, const std::string& storagePath)
{
    CC_ASSERT(_downloaderImpl && "Cannot instanciate more than one instance of DownloaderImpl");

    std::weak_ptr<Downloader> ptr = shared_from_this();
    std::shared_ptr<Downloader> shared = ptr.lock();

    DownloadUnit unit;
    unit.srcUrl = srcUrl;
    unit.customId = customId;
    unit.storagePath = storagePath;
    unit.fp = nullptr;

    prepareDownload(unit);

    int res = _downloaderImpl->performDownload(&unit,
                                               std::bind(&Downloader::fileWriteFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4),
                                               std::bind(&Downloader::downloadProgressFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
                                               );

    if (res != 0)
    {
        // XXX: If this is called from a different thread, will it crash?
        // XXX: Can fileUtils run on a different thread ?
        // XXX: can notifyError run on a different thread ?
        _fileUtils->removeFile(unit.storagePath + TEMP_EXT);
        std::string msg = StringUtils::format("Unable to download file: [curl error]%s", _downloaderImpl->getStrError().c_str());
        this->notifyError(msg, customId, res);
    }
    
    fclose((FILE*)unit.fp);

    // This can only be done after fclose
    if (res == 0)
    {
        _fileUtils->renameFile(unit.storagePath + TEMP_EXT, unit.storagePath);

        if (std::this_thread::get_id() != Director::getInstance()->getCocos2dThreadId())
        {
            std::weak_ptr<Downloader> ptr = shared_from_this();
            std::shared_ptr<Downloader> shared = ptr.lock();

            Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
                if (!ptr.expired())
                {
                    std::shared_ptr<Downloader> downloader = ptr.lock();
                    reportDownloadFinished(unit.srcUrl, unit.storagePath, unit.customId);
                }
            });
        }
        else
        {
            reportDownloadFinished(unit.srcUrl, unit.storagePath, unit.customId);
        }
    }
}

void Downloader::batchDownloadAsync(const DownloadUnits& units, const std::string& batchId/* = ""*/)
{
    auto t = std::thread(&Downloader::batchDownloadSync, this, units, batchId);
    t.detach();
}

void Downloader::batchDownloadSync(const DownloadUnits& units, const std::string& batchId/* = ""*/)
{
    // Make sure downloader won't be released
    std::weak_ptr<Downloader> ptr = shared_from_this();
    std::shared_ptr<Downloader> shared = ptr.lock();
    
    if (units.size() != 0)
    {
        _supportResuming = _downloaderImpl->supportsResume(units.cbegin()->second.srcUrl);

        // split units in multiple parts if the size is bigger
        // than FOPEN_MAX
        if (units.size() >= FOPEN_MAX)
        {
            int count = 0;
            DownloadUnits group;
            for (auto it = units.cbegin(); it != units.cend(); ++it, ++count)
            {
                if (count == FOPEN_MAX)
                {
                    groupBatchDownload(group);
                    group.clear();
                    count = 0;
                }
                const std::string& key = it->first;
                const DownloadUnit& unit = it->second;
                group.emplace(key, unit);
            }
            if (group.size() > 0)
            {
                groupBatchDownload(group);
            }
        }
        else
        {
            groupBatchDownload(units);
        }
    }
    
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([ptr, batchId]{
        if (!ptr.expired()) {
            std::shared_ptr<Downloader> downloader = ptr.lock();
            auto callback = downloader->getSuccessCallback();
            if (callback != nullptr)
            {
                callback("", "", batchId);
            }
        }
    });
    _supportResuming = false;
}

void Downloader::groupBatchDownload(const DownloadUnits& units)
{
    std::weak_ptr<Downloader> ptr = shared_from_this();
    std::shared_ptr<Downloader> shared = ptr.lock();
    
    // static_cast needed since notifyError is overloaded
    auto errorCallback = std::bind( static_cast<void(Downloader::*)(const std::string&, int, const std::string&)>
                          (&Downloader::notifyError), this,
                          std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

    for (const auto& entry: units)
    {
        auto&& unit = entry.second;
        prepareDownload(unit);
    }
    _downloaderImpl->performBatchDownload(units,
                                          std::bind(&Downloader::fileWriteFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4),
                                          std::bind(&Downloader::batchDownloadProgressFunc, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
                                          errorCallback
                                          );

    // Check unfinished files and notify errors, succeed files will be renamed from temporary file name to real name
    for(const auto& entry: units)
    {
        const auto& unit = entry.second;

        // first close, then rename. Otherwise sharing_violation_error on windows
        if (unit.fp)
            fclose((FILE*)unit.fp);

        if (unit.downloaded < unit.totalToDownload || unit.totalToDownload == 0)
        {
            this->notifyError(ErrorCode::NETWORK, "Unable to download file", unit.customId);
        }
        else
        {
            _fileUtils->renameFile(unit.storagePath + TEMP_EXT, unit.storagePath);
        }
    }
}

HeaderInfo Downloader::getHeader(const std::string &srcUrl)
{
    HeaderInfo info;
    _downloaderImpl->getHeader(srcUrl, &info);
    return info;
}

// callbacks
size_t Downloader::fileWriteFunc(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    CC_ASSERT(userdata && "Invalid userdata");
    DownloadUnit* unit = (DownloadUnit*)userdata;
    FILE *fp = (FILE*)(unit->fp);
    
    CC_ASSERT(fp && "Invalid FP");
    size_t written = fwrite(ptr, size, nmemb, fp);
    return written;
}

size_t Downloader::bufferWriteFunc(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    CC_ASSERT(userdata && "Invalid userdata");
    Downloader::StreamData* streamBuffer = (Downloader::StreamData*)((DownloadUnit*)userdata)->fp;

    CC_ASSERT(streamBuffer && "Invalid streamBuffer");

    size_t written = size * nmemb;
    // Avoid pointer overflow
    if (streamBuffer->offset + written <= static_cast<size_t>(streamBuffer->total))
    {
        memcpy(streamBuffer->buffer + streamBuffer->offset, ptr, written);
        streamBuffer->offset += written;
        return written;
    }
    else return 0;
}

void Downloader::reportDownloadFinished(const std::string& url, const std::string& path, const std::string& customid)
{
    if (_onSuccess != nullptr)
    {
        _onSuccess(url, path, customid);
    }
}
void Downloader::reportProgressFinished(double totalToDownload, double nowDownloaded, const DownloadUnit* unit)
{
    if (_onProgress != nullptr)
    {
        _onProgress(totalToDownload, nowDownloaded, unit->srcUrl, unit->customId);
    }
    reportDownloadFinished(unit->srcUrl, unit->storagePath, unit->customId);
}

void Downloader::reportProgressInProgress(double totalToDownload, double nowDownloaded, const DownloadUnit* unit)
{
    if (_onProgress != nullptr)
    {
        _onProgress(totalToDownload, nowDownloaded, unit->srcUrl, unit->customId);
    }
}

// This is only for batchDownload process, will notify file succeed event in progress function
int Downloader::batchDownloadProgressFunc(void *userdata, double totalToDownload, double nowDownloaded)
{
    CC_ASSERT(userdata && "Invalid userdata");

    DownloadUnit* ptr = (DownloadUnit*) userdata;
    if (ptr->totalToDownload == 0)
    {
        ptr->totalToDownload = totalToDownload;
    }

    if (ptr->downloaded != nowDownloaded)
    {
        ptr->downloaded = nowDownloaded;

        if (nowDownloaded == totalToDownload)
        {
            if (std::this_thread::get_id() != Director::getInstance()->getCocos2dThreadId())
            {
                std::weak_ptr<Downloader> _this = shared_from_this();
                DownloadUnit copyUnit = *ptr;
                Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
                    if (!_this.expired())
                    {
                        this->reportProgressFinished(totalToDownload, nowDownloaded, &copyUnit);
                    }
                });
            }
            else
            {
                reportProgressFinished(totalToDownload, nowDownloaded, ptr);
            }
        }
        else
        {
            if (std::this_thread::get_id() != Director::getInstance()->getCocos2dThreadId())
            {
                std::weak_ptr<Downloader> _this = shared_from_this();
                DownloadUnit copyUnit = *ptr;
                Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
                    if (!_this.expired())
                    {
                        reportProgressInProgress(totalToDownload, nowDownloaded, &copyUnit);
                    }
                });
            }
            else
            {
                reportProgressInProgress(totalToDownload, nowDownloaded, ptr);
            }
        }
    }

    return 0;
}

// Compare to batchDownloadProgressFunc, this only handles progress information notification
int Downloader::downloadProgressFunc(void *userdata, double totalToDownload, double nowDownloaded)
{
    CC_ASSERT(userdata && "Invalid userdata");

    DownloadUnit* ptr = (DownloadUnit*)userdata;
    if (ptr->totalToDownload == 0)
    {
        ptr->totalToDownload = totalToDownload;
    }

    if (ptr->downloaded != nowDownloaded)
    {
        ptr->downloaded = nowDownloaded;
        DownloadUnit copyUnit = *ptr;
        std::weak_ptr<Downloader> _this = shared_from_this();

        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
            if (!_this.expired())
            {
                std::shared_ptr<Downloader> downloader = _this.lock();
                
                auto callback = downloader->getProgressCallback();
                if (callback != nullptr)
                {
                    callback(totalToDownload, nowDownloaded, copyUnit.srcUrl, copyUnit.customId);
                }
            }
        });
    }
    
    return 0;
}


} //  namespace network
}  // namespace cocos2d

