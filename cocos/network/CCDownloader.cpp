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

// include platform specific implement class
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "network/CCDownloader-apple.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "network/CCDownloader-apple.h"
#else
//#include "network/CCDownloaderImpl.h"
#endif

namespace cocos2d { namespace network {

    DownloadTask::DownloadTask()
    {
        DLLOG("Construct DownloadTask %p", this);
    }
    
    DownloadTask::~DownloadTask()
    {
        DLLOG("Destruct DownloadTask %p", this);
    }
    
////////////////////////////////////////////////////////////////////////////////
//  Downloader Task Meta Data
    struct Downloader::TaskMeta
    {
        std::vector<char> buf; // use to store data from DataTask
    };

////////////////////////////////////////////////////////////////////////////////
//  Implement Downloader

    Downloader::Downloader()
    {
        DLLOG("Construct Downloader %p", this);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        _impl.reset(new DownloaderApple());
#else
        _impl.reset(new DownloaderApple());
#endif
        _impl->onTaskProgress = [this](const DownloadTask& task,
                                       const char *data,
                                       int64_t bytesReceived,
                                       int64_t totalBytesReceived,
                                       int64_t totalBytesExpected)
        {
            if (task.storagePath.length())
            {
                if (onFileTaskProgress)
                {
                    onFileTaskProgress(task, bytesReceived, totalBytesReceived, totalBytesExpected);
                }
            }
            else
            {
                if (onDataTaskProgress)
                {
                    // data task
                    auto& buf = taskMetaMap[&task].buf;
                    size_t newSize = buf.size() + bytesReceived;
                    if (newSize > buf.capacity())
                    {
                        buf.reserve(newSize);
                    }
                    buf.insert(buf.end(), data, data + bytesReceived);
                    onDataTaskProgress(task, buf, totalBytesReceived, totalBytesExpected);
                }
            }
        };
        
        _impl->onTaskFinish = [this](const DownloadTask& task,
                                     int errorCode,
                                     int errorCodeInternal,
                                     const std::string& errorStr)
        {
            if (DownloadTask::ERROR_NO_ERROR != errorCode)

            {
                if (onTaskError)
                {
                    onTaskError(task, errorCode, errorCodeInternal, errorStr);
                }
            }

            if (task.storagePath.length())
            {
                if (onFileTaskSuccess)
                {
                    onFileTaskSuccess(task);
                }
            }
            else
            {
                // data task
                if (onDataTaskSuccess)
                {
                    auto& buf = taskMetaMap[&task].buf;
                    onDataTaskSuccess(task, buf);
                }
            }
        };
    }
    
    Downloader::~Downloader()
    {
        DLLOG("Destruct Downloader %p", this);
    }
    
    std::shared_ptr<const DownloadTask> Downloader::createDownloadDataTask(const std::string& srcUrl, const std::string& identifier/* = ""*/)
    {
        std::shared_ptr<DownloadTask> task(new DownloadTask());
        do
        {
            task->requestURL    = srcUrl;
            task->identifier    = identifier;
            if (0 == srcUrl.length())
            {
                if (onTaskError)
                {
                    onTaskError(*task, DownloadTask::ERROR_INVALID_PARAMS, 0, "URL or is empty.");
                }
                task.reset();
                break;
            }
            task->_coTask.reset(_impl->createCoTask(task));
        } while (0);
        
        return task;
    }
    
    std::shared_ptr<const DownloadTask> Downloader::createDownloadFileTask(const std::string& srcUrl,
                                                                           const std::string& storagePath,
                                                                           const std::string& identifier/* = ""*/)
    {
        std::shared_ptr<DownloadTask> task(new DownloadTask());
        do
        {
            task->requestURL    = srcUrl;
            task->storagePath   = storagePath;
            task->identifier    = identifier;
            if (0 == srcUrl.length() || 0 == storagePath.length())
            {
                if (onTaskError)
                {
                    onTaskError(*task, DownloadTask::ERROR_INVALID_PARAMS, 0, "URL or storage path is empty.");
                }
                task.reset();
                break;
            }
            task->_coTask.reset(_impl->createCoTask(task));
        } while (0);

        return task;
    }
    
//std::string Downloader::getFileNameFromUrl(const std::string& srcUrl)
//{
//    // Find file name and file extension
//    std::string filename;
//    unsigned long found = srcUrl.find_last_of("/\\");
//    if (found != std::string::npos)
//        filename = srcUrl.substr(found+1);
//    return filename;
//}

}}  //  namespace cocos2d::network
