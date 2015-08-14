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
#include <vector>

#include "network/CCIDownloaderImpl.h"
#include "platform/CCPlatformMacros.h"

/**
 * @addtogroup network
 * @{
 */

NS_CC_BEGIN

namespace network
{
    class DownloaderImpl : public IDownloaderImpl
    {
    public:
        DownloaderImpl();
        virtual ~DownloaderImpl();

        bool init() override;

        // Overrides
        int performDownload(DownloadUnit* unit,
                            const WriterCallback& writerCallback,
                            const ProgressCallback& progressCallback
                            ) override;
        int performBatchDownload(const DownloadUnits& units,
                                 const WriterCallback& writerCallback,
                                 const ProgressCallback& progressCallback,
                                 const ErrorCallback& errorCallback                                         
                                 ) override;
        int getHeader(const std::string& url, HeaderInfo* headerInfo) override;
        std::string getStrError() const override;
        void setConnectionTimeout(int timeout) override;
        bool supportsResume(const std::string& url);

        //
        const WriterCallback& getWriterCallback() const { return _writerCallback; }
        const ProgressCallback& getProgressCallback() const { return _progressCallback; }
        
    private:

        int _connectionTimeout;
        WriterCallback _writerCallback;
        ProgressCallback _progressCallback;

        void* _curlHandle;
        int _lastErrCode;
        bool _initialized;
    };

} // namespace network

NS_CC_END

// end group
/// @}
