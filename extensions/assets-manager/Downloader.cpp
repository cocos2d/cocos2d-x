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

#include "Downloader.h"
#include "AssetsManager.h"

#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>

NS_CC_EXT_BEGIN

#define LOW_SPEED_LIMIT     1L
#define LOW_SPEED_TIME      5L
#define MAX_REDIRS          2

#define TEMP_EXT            ".temp"

size_t curlWriteFunc(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    FILE *fp = (FILE*)userdata;
    size_t written = fwrite(ptr, size, nmemb, fp);
    return written;
}

int downloadProgressFunc(Downloader::ProgressData *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded)
{
    if (ptr->totalToDownload == 0)
    {
        ptr->totalToDownload = totalToDownload;
    }
    
    if (ptr->downloaded != nowDownloaded)
    {
        ptr->downloaded = nowDownloaded;
        
        Downloader::ProgressData data = *ptr;
        
        if (nowDownloaded == totalToDownload)
        {
            AssetsManager::renameFile(data.path, data.name + TEMP_EXT, data.name);
            
            Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
                if (!data.downloader.expired())
                {
                    std::shared_ptr<Downloader> downloader = data.downloader.lock();
                
                    auto callback = downloader->getSuccessCallback();
                    if (callback != nullptr)
                    {
                        callback(data.url, data.path + data.name, data.customId);
                    }
                }
            });
        }
        else
        {
            Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
                if (!data.downloader.expired())
                {
                    std::shared_ptr<Downloader> downloader = data.downloader.lock();
                
                    auto callback = downloader->getProgressCallback();
                    if (callback != nullptr)
                    {
                        callback(totalToDownload, nowDownloaded, data.url, data.customId);
                    }
                }
                else
                {
                    CCLOG("invalid callback.");
                }
            });
        }
    }
    
    return 0;
}


Downloader::Downloader()
: _onError(nullptr)
, _onProgress(nullptr)
, _onSuccess(nullptr)
, _connectionTimeout(0)
{
}

Downloader::~Downloader()
{
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

void Downloader::notifyError(ErrorCode code, const std::string &msg/* ="" */, const std::string &customId/* ="" */, int curle_code/* = CURLE_OK*/, int curlm_code/* = CURLM_OK*/)
{
    std::shared_ptr<Downloader> downloader = shared_from_this();
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
        if (downloader != nullptr && downloader->_onError != nullptr)
        {
            Error err;
            err.code = code;
            err.curle_code = curle_code;
            err.curlm_code = curlm_code;
            err.message = msg;
            err.customId = customId;
            downloader->_onError(err);
        }
    });
}

void Downloader::notifyError(const std::string &msg, int curlm_code, const std::string &customId/* = ""*/)
{
    notifyError(ErrorCode::CURL_MULTI_ERROR, msg, customId, CURLE_OK, curlm_code);
}

void Downloader::notifyError(const std::string &msg, const std::string &customId, int curle_code)
{
    notifyError(ErrorCode::CURL_EASY_ERROR, msg, customId, curle_code);
}

std::string Downloader::getFileNameFromUrl(const std::string &srcUrl)
{
    // Find file name and file extension
    std::string filename;
    unsigned long found = srcUrl.find_last_of("/\\");
    if (found != std::string::npos)
        filename = srcUrl.substr(found+1);
    return filename;
}

void Downloader::clearBatchDownloadData()
{
    while (_progDatas.size() != 0) {
        delete _progDatas.back();
        _progDatas.pop_back();
    }
    
    while (_files.size() != 0) {
        delete _files.back();
        _files.pop_back();
    }
}

void Downloader::prepareDownload(const std::string &srcUrl, const std::string &storagePath, const std::string &customId, FileDescriptor *fDesc, ProgressData *pData)
{
    std::shared_ptr<Downloader> downloader = shared_from_this();
    pData->customId = customId;
    pData->url = srcUrl;
    pData->downloader = downloader;
    pData->downloaded = 0;
    pData->totalToDownload = 0;
    
    fDesc->fp = nullptr;
    fDesc->curl = nullptr;
    
    Error err;
    err.customId = customId;
    
    // Asserts
    // Find file name and file extension
    unsigned long found = storagePath.find_last_of("/\\");
    if (found != std::string::npos)
    {
        pData->name = storagePath.substr(found+1);
        pData->path = storagePath.substr(0, found+1);
    }
    else
    {
        err.code = ErrorCode::INVALID_URL;
        err.message = "Invalid url or filename not exist error: " + srcUrl;
        if (this->_onError) this->_onError(err);
        return;
    }
    
    // Create a file to save package.
    const std::string outFileName = storagePath + TEMP_EXT;
    fDesc->fp = fopen(outFileName.c_str(), "wb");
    if (!fDesc->fp)
    {
        err.code = ErrorCode::CREATE_FILE;
        err.message = "Can not create file " + outFileName;
        if (this->_onError) this->_onError(err);
    }
}

void Downloader::downloadAsync(const std::string &srcUrl, const std::string &storagePath, const std::string &customId/* = ""*/)
{
    FileDescriptor fDesc;
    ProgressData pData;
    prepareDownload(srcUrl, storagePath, customId, &fDesc, &pData);
    if (fDesc.fp != nullptr)
    {
        auto t = std::thread(&Downloader::download, this, srcUrl, customId, fDesc, pData);
        t.detach();
    }
}

void Downloader::downloadSync(const std::string &srcUrl, const std::string &storagePath, const std::string &customId/* = ""*/)
{
    FileDescriptor fDesc;
    ProgressData pData;
    prepareDownload(srcUrl, storagePath, customId, &fDesc, &pData);
    if (fDesc.fp != nullptr)
    {
        download(srcUrl, customId, fDesc, pData);
    }
}

void Downloader::download(const std::string &srcUrl, const std::string &customId, const FileDescriptor &fDesc, const ProgressData &data)
{
    CURL *curl = curl_easy_init();
    if (!curl)
    {
        this->notifyError(ErrorCode::CURL_EASY_ERROR, "Can not init curl with curl_easy_init", customId);
        return;
    }
    
    // Download pacakge
    curl_easy_setopt(curl, CURLOPT_URL, srcUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteFunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fDesc.fp);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
    curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, downloadProgressFunc);
    curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, &data);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, true);
    if (_connectionTimeout) curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, _connectionTimeout);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, LOW_SPEED_LIMIT);
    curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, LOW_SPEED_TIME);
    
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        AssetsManager::removeFile(data.path + data.name + TEMP_EXT);
        std::string msg = StringUtils::format("Unable to download file: [curl error]%s", curl_easy_strerror(res));
        this->notifyError(msg, customId, res);
    }
    
    fclose(fDesc.fp);
    curl_easy_cleanup(curl);
    
}

void Downloader::batchDownloadAsync(const std::unordered_map<std::string, Downloader::DownloadUnit> &units, const std::string &batchId/* = ""*/)
{
    auto t = std::thread(&Downloader::batchDownloadSync, this, units, batchId);
    t.detach();
}

void Downloader::batchDownloadSync(const std::unordered_map<std::string, Downloader::DownloadUnit> &units, const std::string &batchId/* = ""*/)
{
    CURLM* multi_handle = curl_multi_init();
    int still_running = 0;
    
    for (auto it = units.cbegin(); it != units.cend(); ++it)
    {
        DownloadUnit unit = it->second;
        std::string srcUrl = unit.srcUrl;
        std::string storagePath = unit.storagePath;
        std::string customId = unit.customId;
        
        FileDescriptor *fDesc = new FileDescriptor();
        ProgressData *data = new ProgressData();
        prepareDownload(srcUrl, storagePath, customId, fDesc, data);
        
        if (fDesc->fp != nullptr)
        {
            CURL* curl = curl_easy_init();
            curl_easy_setopt(curl, CURLOPT_URL, srcUrl.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteFunc);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fDesc->fp);
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
            curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, downloadProgressFunc);
            curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, data);
            curl_easy_setopt(curl, CURLOPT_FAILONERROR, true);
            if (_connectionTimeout) curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, _connectionTimeout);
            curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
            curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, LOW_SPEED_LIMIT);
            curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, LOW_SPEED_TIME);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
            curl_easy_setopt(curl, CURLOPT_MAXREDIRS, MAX_REDIRS);
            fDesc->curl = curl;
            
            CURLMcode code = curl_multi_add_handle(multi_handle, curl);
            if (code != CURLM_OK)
            {
                // Avoid memory leak
                delete data;
                delete fDesc;
                std::string msg = StringUtils::format("Unable to add curl handler for %s: [curl error]%s", customId.c_str(), curl_multi_strerror(code));
                this->notifyError(msg, code, customId);
            }
            else
            {
                // Add to list for tracking
                _progDatas.push_back(data);
                _files.push_back(fDesc);
            }
        }
    }
    
    // Query multi perform
    CURLMcode curlm_code = CURLM_CALL_MULTI_PERFORM;
    while(CURLM_CALL_MULTI_PERFORM == curlm_code) {
        curlm_code = curl_multi_perform(multi_handle, &still_running);
    }
    if (curlm_code != CURLM_OK) {
        std::string msg = StringUtils::format("Unable to continue the download process: [curl error]%s", curl_multi_strerror(curlm_code));
        this->notifyError(msg, curlm_code);
    }
    else
    {
        bool failed = false;
        while (still_running > 0 && !failed)
        {
            /* set a suitable timeout to play around with */
            struct timeval select_tv;
            long curl_timeo = -1;
            select_tv.tv_sec = 1;
            select_tv.tv_usec = 0;
            
            curl_multi_timeout(multi_handle, &curl_timeo);
            if(curl_timeo >= 0) {
                select_tv.tv_sec = curl_timeo / 1000;
                if(select_tv.tv_sec > 1)
                    select_tv.tv_sec = 1;
                else
                    select_tv.tv_usec = (curl_timeo % 1000) * 1000;
            }
            
            int rc;
            fd_set fdread;
            fd_set fdwrite;
            fd_set fdexcep;
            int maxfd = -1;
            FD_ZERO(&fdread);
            FD_ZERO(&fdwrite);
            FD_ZERO(&fdexcep);
            curl_multi_fdset(multi_handle, &fdread, &fdwrite, &fdexcep, &maxfd);
            rc = select(maxfd + 1, &fdread, &fdwrite, &fdexcep, &select_tv);
            
            switch(rc)
            {
                case -1:
                    failed = true;
                    break;
                case 0:
                default:
                    curlm_code = CURLM_CALL_MULTI_PERFORM;
                    while(CURLM_CALL_MULTI_PERFORM == curlm_code) {
                        curlm_code = curl_multi_perform(multi_handle, &still_running);
                    }
                    if (curlm_code != CURLM_OK) {
                        std::string msg = StringUtils::format("Unable to continue the download process: [curl error]%s", curl_multi_strerror(curlm_code));
                        this->notifyError(msg, curlm_code);
                    }
                    break;
            }
        }
    }
    
    // Clean up and close files
    curl_multi_cleanup(multi_handle);
    for (auto it = _files.begin(); it != _files.end(); ++it)
    {
        fclose((*it)->fp);
        curl_easy_cleanup((*it)->curl);
    }
    
    // Check unfinished files and notify errors
    for (auto it = _progDatas.begin(); it != _progDatas.end(); ++it) {
        ProgressData *data = *it;
        if (data->downloaded < data->totalToDownload)
        {
            AssetsManager::removeFile(data->path + data->name + TEMP_EXT);
            this->notifyError(ErrorCode::NETWORK, "Unable to download file", data->customId);
        }
    }
    
    std::shared_ptr<Downloader> downloader = shared_from_this();
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([downloader, batchId]{
        if (downloader != nullptr) {
            auto callback = downloader->getSuccessCallback();
            if (callback != nullptr)
            {
                callback("", "", batchId);
            }
        }
    });
    
    clearBatchDownloadData();
}

NS_CC_EXT_END
