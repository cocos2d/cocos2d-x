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

#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>
#include <thread>

using namespace cocos2d;

NS_CC_EXT_BEGIN;

#define BUFFER_SIZE         8192
#define MAX_FILENAME        512
#define LOW_SPEED_LIMIT     1L
#define LOW_SPEED_TIME      5L

//const std::regex REGEX_FILENAME("([\\w\\d\\._\\-]+)\\.([\\w\\d])$");

static size_t curlWriteFunc(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    FILE *fp = (FILE*)userdata;
    size_t written = fwrite(ptr, size, nmemb, fp);
    return written;
}

int downloadProgressFunc(Downloader::ProgressData *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded)
{
    static int downloaded = 0;
    
    if (downloaded != nowDownloaded)
    {
        downloaded = nowDownloaded;
        std::string url = ptr->url;
        std::string customId = ptr->customId;
        DownloaderDelegateProtocol* delegate = ptr->downloader->getDelegate();
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([url, customId, delegate, totalToDownload]{
            if (delegate)
                delegate->onProgress(totalToDownload, downloaded, url, customId);
        });
    }
    
    return 0;
}


Downloader::Downloader(DownloaderDelegateProtocol* delegate)
: _delegate(delegate)
, _curl(nullptr)
{
    init();
}

bool Downloader::init()
{
    if (!_curl) {
        _curl = curl_easy_init();
        if (!_curl)
        {
            CCLOG("can not init curl");
            return false;
        }
    }
    return true;
}

void Downloader::notifyError(ErrorCode code, const std::string &msg/* ="" */, const std::string &customId/* ="" */)
{
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]{
        Error err;
        err.code = code;
        err.message = msg;
        err.customId = customId;
        if (this->_delegate)
            this->_delegate->onError(err);
    });
}

bool Downloader::checkStoragePath(const std::string &storagePath)
{
    size_t l = storagePath.size();
    if (l > 0 && storagePath[l - 1] != '/')
    {
        return false;
    }
    return true;
}

void Downloader::downloadAsync(const std::string &srcUrl, const std::string &storagePath, const std::string &customId/* = ""*/, const std::string &rename/* = ""*/)
{
    Error err;
    err.customId = customId;
    // Asserts
    if (!_curl)
    {
        err.code = ErrorCode::CURL_UNINIT;
        if (this->_delegate) this->_delegate->onError(err);
        return;
    }
    if (!checkStoragePath(storagePath))
    {
        err.code = ErrorCode::INVALID_STORAGE_PATH;
        if (this->_delegate) this->_delegate->onError(err);
        return;
    }
    
    // Find file name and file extension
    std::string filename = rename;
    if (filename.size() == 0)
    {
        unsigned long found = srcUrl.find_last_of("/\\");
        if (found != std::string::npos)
            filename = srcUrl.substr(found+1);
        if (filename.size() == 0)
        {
            err.code = ErrorCode::INVALID_URL;
            err.message = "Invalid url or filename not exist error: " + srcUrl;
            if (this->_delegate) this->_delegate->onError(err);
            return;
        }
        //std::smatch m;
        //std::regex_search(url, m, REGEX_FILENAME);
        //std::string filename = m.str();
    }
    
    auto t = std::thread(&Downloader::download, this, srcUrl, storagePath, filename, customId);
    t.detach();
}

void Downloader::download(const std::string &srcUrl, const std::string &storagePath, const std::string &filename, const std::string &customId)
{
    // Create a file to save package.
    const std::string outFileName = storagePath + filename;
    FILE *fp = fopen(outFileName.c_str(), "wb");
    if (!fp)
    {
        std::string msg = "Can not create file " + outFileName;
        this->notifyError(ErrorCode::CREATE_FILE, msg, customId);
        return;
    }
    
    ProgressData data;
    data.customId = customId;
    data.url = srcUrl;
    data.downloader = this;
    
    // Download pacakge
    CURLcode res;
    curl_easy_setopt(_curl, CURLOPT_URL, srcUrl.c_str());
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, curlWriteFunc);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(_curl, CURLOPT_NOPROGRESS, false);
    curl_easy_setopt(_curl, CURLOPT_PROGRESSFUNCTION, downloadProgressFunc);
    curl_easy_setopt(_curl, CURLOPT_PROGRESSDATA, &data);
    curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(_curl, CURLOPT_LOW_SPEED_LIMIT, LOW_SPEED_LIMIT);
    curl_easy_setopt(_curl, CURLOPT_LOW_SPEED_TIME, LOW_SPEED_TIME);
    
    res = curl_easy_perform(_curl);
    curl_easy_cleanup(_curl);
    if (res != 0)
    {
        this->notifyError(ErrorCode::NETWORK, "Error when download file", customId);
        fclose(fp);
        return;
    }
    
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([filename, srcUrl, customId, this]{
        if (this->_delegate)
            this->_delegate->onSuccess(srcUrl, customId, filename);
    });
    
    fclose(fp);
}

NS_CC_EXT_END;