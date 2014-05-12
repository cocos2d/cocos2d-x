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

#ifndef __Downloader__
#define __Downloader__

#include "cocos2d.h"
#include "extensions/ExtensionMacros.h"

NS_CC_EXT_BEGIN

class DownloaderDelegateProtocol;

class CC_DLL Downloader
{
public:
    enum class ErrorCode
    {
        // Error caused by creating a file to store downloaded data
        CREATE_FILE,
        /** Error caused by network
         -- network unavaivable
         -- timeout
         -- ...
         */
        NETWORK,
        /** There is not a new version
         */
        NO_NEW_VERSION,
        /** Error caused in uncompressing stage
         -- can not open zip file
         -- can not read file global information
         -- can not read file information
         -- can not create a directory
         -- ...
         */
        UNCOMPRESS,
        
        CURL_UNINIT,
        
        INVALID_URL,
        
        INVALID_STORAGE_PATH
    };
    
    struct Error
    {
        ErrorCode code;
        std::string message;
    };
    
    /**
     *  The default constructor.
     */
    Downloader(DownloaderDelegateProtocol* delegate);
    
    bool init();
    
    DownloaderDelegateProtocol* getDelegate() const { return _delegate ;}
    
    void download(const char* srcUrl, const char* storagePath);
    
protected:
    
    void downloadAsync(const char* srcUrl, const char* storagePath);
    
    void notifyError(ErrorCode code, const char* msg = "");
    
    bool checkStoragePath(const char* storagePath);
    
protected:
    
    DownloaderDelegateProtocol* _delegate;
    
    void *_curl;
};

class DownloaderDelegateProtocol
{
public:
    virtual ~DownloaderDelegateProtocol() {};

    /* @brief Call back function for error
     @param error Error object
     * @js NA
     * @lua NA
     */
    virtual void onError(const Downloader::Error &error) {};
    
    /** @brief Call back function for recording downloading percent
     @param percent How much percent downloaded
     @warning    This call back function just for recording downloading percent.
     AssetsManager will do some other thing after downloading, you should
     write code in onSuccess() after downloading.
     * @js NA
     * @lua NA
     */
    virtual void onProgress(int percent) {};
    
    /** @brief Call back function for success
     * @js NA
     * @lua NA
     */
    virtual void onSuccess() {};
};

NS_CC_EXT_END;

#endif /* defined(__Downloader__) */
