/****************************************************************************
Copyright (c) 2015 Chukong Technologies Inc.

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

#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "base/CCConsole.h"

//#define CC_DOWNLOADER_DEBUG
#ifdef  CC_DOWNLOADER_DEBUG
#define DLLOG(format, ...)      cocos2d::log(format, ##__VA_ARGS__)
#else
#define DLLOG(...)       do {} while (0)
#endif

namespace cocos2d { namespace network
{
    class DownloadTask;
    
    class CC_DLL IDownloadTask
    {
    public:
        virtual ~IDownloadTask(){}
    };

    class IDownloaderImpl
    {
    public:
        virtual ~IDownloaderImpl(){}
        
        std::function<void(const DownloadTask& task,
                           int64_t bytesReceived,
                           int64_t totalBytesReceived,
                           int64_t totalBytesExpected,
                           std::function<int64_t(void *buffer, int64_t len)>& transferDataToBuffer)> onTaskProgress;
        
        std::function<void(const DownloadTask& task,
                           int errorCode,
                           int errorCodeInternal,
                           const std::string& errorStr,
                           std::vector<unsigned char>& data)> onTaskFinish;
        
        virtual IDownloadTask *createCoTask(std::shared_ptr<const DownloadTask>& task) = 0;
    };

}}  // namespace cocos2d::network
