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
#include <functional>
#include <unordered_map>

#include "platform/CCPlatformMacros.h"
#include "platform/CCStdC.h"

/**
 * @addtogroup network
 * @{
 */

NS_CC_BEGIN

namespace network
{
    struct HeaderInfo
    {
        bool valid;
        std::string url;
        std::string contentType;
        double contentSize;
        long responseCode;
    };

    struct DownloadUnit
    {
        // info provided by the user
        std::string srcUrl;
        std::string storagePath;
        std::string customId;

        // additional info created by CCDownloader
        mutable void* fp;
        mutable bool resumeDownload;
        mutable double downloaded;
        mutable double totalToDownload;
        mutable void *_reserved;
    };

    typedef std::unordered_map<std::string, DownloadUnit> DownloadUnits;

    class IDownloaderImpl
    {
    public:
        typedef std::function<int(void* ptr, ssize_t, ssize_t, void* userdata)> WriterCallback;
        typedef std::function<int(void* userdata, double, double)> ProgressCallback;
        typedef std::function<void(const std::string&, int, const std::string&)> ErrorCallback;

        IDownloaderImpl(){}
        virtual ~IDownloaderImpl(){}
        virtual bool init() = 0;

        enum class Options {
            RESUME
        };

        // methods that must be overriden
        virtual int performDownload(DownloadUnit* unit,
                                    const WriterCallback& writerCallback,
                                    const ProgressCallback& progressCallback
                                    ) = 0;

        virtual int performBatchDownload(const DownloadUnits& units,
                                         const WriterCallback& writerCallback,
                                         const ProgressCallback& progressCallback,
                                         const ErrorCallback& errorCallback
                                         ) = 0;

        virtual int getHeader(const std::string& url, HeaderInfo* headerInfo) = 0;
        virtual std::string getStrError() const = 0;
        virtual void setConnectionTimeout(int timeout) = 0;
    };
}

NS_CC_END
