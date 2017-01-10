/****************************************************************************
 Copyright (c) 2015-2016 cocos2d-x.org

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

#include <functional>
#include <string>
#include <memory>
#include <vector>

#include "platform/CCPlatformMacros.h"

namespace cocos2d { namespace network {

    class IDownloadTask;
    class IDownloaderImpl;
    class Downloader;

    class CC_DLL DownloadTask final
    {
    public:
        const static int ERROR_NO_ERROR = 0;
        const static int ERROR_INVALID_PARAMS = -1;
        const static int ERROR_FILE_OP_FAILED = -2;
        const static int ERROR_IMPL_INTERNAL = -3;

        std::string identifier;
        std::string requestURL;
        std::string storagePath;

        DownloadTask();
        virtual ~DownloadTask();

    private:
        friend class Downloader;
        std::unique_ptr<IDownloadTask> _coTask;
    };

    class CC_DLL DownloaderHints
    {
    public:
        uint32_t countOfMaxProcessingTasks;
        uint32_t timeoutInSeconds;
        std::string tempFileNameSuffix;
    };

    class CC_DLL Downloader final
    {
    public:
        Downloader();
        Downloader(const DownloaderHints& hints);
        ~Downloader();

        std::function<void(const DownloadTask& task,
                           std::vector<unsigned char>& data)> onDataTaskSuccess;

        std::function<void(const DownloadTask& task)> onFileTaskSuccess;

        std::function<void(const DownloadTask& task,
                           int64_t bytesReceived,
                           int64_t totalBytesReceived,
                           int64_t totalBytesExpected)> onTaskProgress;

        std::function<void(const DownloadTask& task,
                           int errorCode,
                           int errorCodeInternal,
                           const std::string& errorStr)> onTaskError;
        
        void setOnFileTaskSuccess(const std::function<void(const DownloadTask& task)>& callback) {onFileTaskSuccess = callback;};
        
        void setOnTaskProgress(const std::function<void(const DownloadTask& task,
                                                  int64_t bytesReceived,
                                                  int64_t totalBytesReceived,
                                                  int64_t totalBytesExpected)>& callback) {onTaskProgress = callback;};
        
        void setOnTaskError(const std::function<void(const DownloadTask& task,
                                               int errorCode,
                                               int errorCodeInternal,
                                               const std::string& errorStr)>& callback) {onTaskError = callback;};

        std::shared_ptr<const DownloadTask> createDownloadDataTask(const std::string& srcUrl, const std::string& identifier = "");

        std::shared_ptr<const DownloadTask> createDownloadFileTask(const std::string& srcUrl, const std::string& storagePath, const std::string& identifier = "");

    private:
        std::unique_ptr<IDownloaderImpl> _impl;
    };

}}  // namespace cocos2d::network

