/****************************************************************************
 Copyright (c) 2016 Yuki Kuwabara <do_low@hotmail.com>
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

#ifndef TapRecorder_Url_h
#define TapRecorder_Url_h

#include "CCProtocol.h"
#include <network/HttpClient.h>
#include "extensions/TapRecorder/CCEventListenerTapRecorder.h"

NS_CC_EXT_BEGIN

namespace TapRecorder
{
    class Url : public Protocol
    {
    public:
        enum EventType {
            DOWNLOAD_BEGAN = 1, DOWNLOAD_ENDED, DOWNLOAD_ERROR,
            UPLOAD_BEGAN,       UPLOAD_ENDED,   UPLOAD_ERROR
        };
        
        static Url* getInstance()
        {
            static Url instance;
            return &instance;
        }
        
        Url();
        ~Url();
        
        EventListenerTapRecorder<Url>* getEventListener();
        
        std::string getSavePath();
        std::string getError();
        
        void upload(const std::string& url, const std::string& fullpath);
        void download(const std::string& url, const std::string& savename);
        
    protected:
        EventListenerTapRecorder<Url>* _eventListener = nullptr;
        std::string _savePath;
        std::string _error;
        
        bool isSuccessHttpStatus(long statusCode);
    };
}

NS_CC_EXT_END

#endif /* TapRecorder_Url_h */
