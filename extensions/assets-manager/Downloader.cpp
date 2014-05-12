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
#include <regex>

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

int downloadProgressFunc(void *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded)
{
    static int percent = 0;
    int tmp = (int)(nowDownloaded / totalToDownload * 100);
    
    if (percent != tmp)
    {
        percent = tmp;
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
            auto downloader = static_cast<Downloader*>(ptr);
            DownloaderDelegateProtocol* delegate = downloader->getDelegate();
            if (delegate)
                delegate->onProgress(percent);
            
            CCLOG("downloading... %d%%", percent);
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

void Downloader::notifyError(ErrorCode code, const char* msg/* ="" */)
{
    Error err;
    err.code = code;
    err.message = msg;
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]{
        if (this->_delegate)
            this->_delegate->onError(err);
    });
}

bool Downloader::checkStoragePath(const char* storagePath)
{
    int l = sizeof(storagePath);
    if (l > 0 && storagePath[l - 1] != '/')
    {
        return false;
    }
    return true;
}

void Downloader::download(const char *srcUrl, const char *storagePath)
{
    auto t = std::thread(&Downloader::downloadAsync, this, srcUrl, storagePath);
    t.detach();
}

void Downloader::downloadAsync(const char* srcUrl, const char* storagePath)
{
    // Asserts
    if (!_curl)
        this->notifyError(ErrorCode::CURL_UNINIT);
    if (checkStoragePath(storagePath))
        this->notifyError(ErrorCode::INVALID_STORAGE_PATH);
    
    // Find file name and file extension
    std::string url(srcUrl);
    std::string filename = "";
    unsigned long found = url.find_last_of("/\\");
    if (found != std::string::npos)
        filename = url.substr(found+1);
    if (filename.size() == 0)
    {
        std::string msg = "Invalid url or filename not exist error: " + url;
        this->notifyError(ErrorCode::INVALID_URL, msg.c_str());
        return;
    }
    //std::smatch m;
    //std::regex_search(url, m, REGEX_FILENAME);
    //std::string filename = m.str();
    
    // Create a file to save package.
    const std::string outFileName = storagePath + filename;
    FILE *fp = fopen(outFileName.c_str(), "wb");
    if (!fp)
    {
        std::string msg = "Can not create file " + outFileName;
        this->notifyError(ErrorCode::CREATE_FILE, msg.c_str());
        return;
    }
    
    // Download pacakge
    CURLcode res;
    curl_easy_setopt(_curl, CURLOPT_URL, srcUrl);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, curlWriteFunc);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(_curl, CURLOPT_NOPROGRESS, false);
    curl_easy_setopt(_curl, CURLOPT_PROGRESSFUNCTION, downloadProgressFunc);
    curl_easy_setopt(_curl, CURLOPT_PROGRESSDATA, this);
    curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(_curl, CURLOPT_LOW_SPEED_LIMIT, LOW_SPEED_LIMIT);
    curl_easy_setopt(_curl, CURLOPT_LOW_SPEED_TIME, LOW_SPEED_TIME);
    
    res = curl_easy_perform(_curl);
    curl_easy_cleanup(_curl);
    if (res != 0)
    {
        this->notifyError(ErrorCode::NETWORK, "Error when download file");
        fclose(fp);
        return;
    }
    
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([srcUrl, this]{
        if (this->_delegate)
            this->_delegate->onSuccess();
        CCLOG("Succeed downloading file %s", srcUrl);
    });
    
    fclose(fp);
}

NS_CC_EXT_END;