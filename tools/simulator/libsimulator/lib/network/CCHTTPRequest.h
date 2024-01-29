/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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


#ifndef __CC_HTTP_REQUEST_H_
#define __CC_HTTP_REQUEST_H_

#include "cocos2dx_extra.h"
#include "cocos2d.h"
#include "network/CCHTTPRequestDelegate.h"

#if CC_LUA_ENGINE_ENABLED > 0
#include "CCLuaEngine.h"
#endif

#ifdef _WINDOWS_
#include <Windows.h>
#else
#include <pthread.h>
#endif

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include "curl/curl.h"

using namespace std;
//USING_NS_CC;

NS_CC_EXTRA_BEGIN

#define kCCHTTPRequestMethodGET                 0
#define kCCHTTPRequestMethodPOST                1

#define kCCHTTPRequestAcceptEncodingIdentity    0
#define kCCHTTPRequestAcceptEncodingGzip        1
#define kCCHTTPRequestAcceptEncodingDeflate     2

#define kCCHTTPRequestStateIdle                 0
#define kCCHTTPRequestStateCleared              1
#define kCCHTTPRequestStateInProgress           2
#define kCCHTTPRequestStateCompleted            3
#define kCCHTTPRequestStateCancelled            4
#define kCCHTTPRequestStateFailed               5

#define kCCHTTPRequestCURLStateIdle             0
#define kCCHTTPRequestCURLStateBusy             1
#define kCCHTTPRequestCURLStateClosed           2

typedef vector<string> HTTPRequestHeaders;
typedef HTTPRequestHeaders::iterator HTTPRequestHeadersIterator;

class HTTPRequest : public Ref
{
public:
    static HTTPRequest *createWithUrl(HTTPRequestDelegate *delegate,
                                        const char *url,
                                        int method = kCCHTTPRequestMethodGET);

#if CC_LUA_ENGINE_ENABLED > 0
    static HTTPRequest* createWithUrlLua(LUA_FUNCTION listener,
                                           const char *url,
                                           int method = kCCHTTPRequestMethodGET);
#endif

    ~HTTPRequest(void);

    /** @brief Set request url. */
    void setRequestUrl(const char *url);

    /** @brief Get request url. */
    const string getRequestUrl(void);

    /** @brief Add a custom header to the request. */
    void addRequestHeader(const char *header);

    /** @brief Add a POST variable to the request, POST only. */
    void addPOSTValue(const char *key, const char *value);

    /** @brief Set POST data to the request body, POST only. */
    void setPOSTData(const char *data);


	void addFormFile(const char *name, const char *filePath, const char *fileType="application/octet-stream");
	void addFormContents(const char *name, const char *value);

    /** @brief Set/Get cookie string. */
    void setCookieString(const char *cookie);
    const string getCookieString(void);

    /** @brief Set accept encoding. */
    void setAcceptEncoding(int acceptEncoding);

    /** @brief Number of seconds to wait before timing out - default is 10. */
    void setTimeout(int timeout);

    /** @brief Execute an asynchronous request. */
    bool start(void);

    /** @brief Cancel an asynchronous request, clearing all delegates first. */
    void cancel(void);

    /** @brief Get the request state. */
    int getState(void);

    /** @brief Return HTTP status code. */
    int getResponseStatusCode(void);

    /** @brief Return HTTP response headers. */
    const HTTPRequestHeaders &getResponseHeaders(void);
    const string getResponseHeadersString(void);

    /** @brief Returns the contents of the result. */
    const string getResponseString(void);

    /** @brief Alloc memory block, return response data. use free() release memory block */
    void *getResponseData(void);

#if CC_LUA_ENGINE_ENABLED > 0
    LUA_STRING getResponseDataLua(void);
#endif

    /** @brief Get response data length (bytes). */
    int getResponseDataLength(void);

    /** @brief Save response data to file. */
    size_t saveResponseData(const char *filename);

    /** @brief Get error code. */
    int getErrorCode(void);

    /** @brief Get error message. */
    const string getErrorMessage(void);

    /** @brief Return HTTPRequestDelegate delegate. */
    HTTPRequestDelegate* getDelegate(void);

    /** @brief timer function. */
    void checkCURLState(float dt);
    virtual void update(float dt);

private:
    HTTPRequest(void)
    : _delegate(NULL)
    , _listener(0)
    , _state(kCCHTTPRequestStateIdle)
    , _errorCode(0)
    , _responseCode(0)
    , _responseBuffer(NULL)
    , _responseBufferLength(0)
    , _responseDataLength(0)
    , _curlState(kCCHTTPRequestCURLStateIdle)
    , _formPost(NULL)
    , _lastPost(NULL)
    , _dltotal(0)
    , _dlnow(0)
    , _ultotal(0)
    , _ulnow(0)
    {
    }
    bool initWithDelegate(HTTPRequestDelegate* delegate, const char *url, int method);
#if CC_LUA_ENGINE_ENABLED > 0
    bool initWithListener(LUA_FUNCTION listener, const char *url, int method);
#endif
    bool initWithUrl(const char *url, int method);

    enum {
        DEFAULT_TIMEOUT = 10, // 10 seconds
        BUFFER_CHUNK_SIZE = 32768, // 32 KB
    };

    static unsigned int s_id;
    string _url;
    HTTPRequestDelegate* _delegate;
    int _listener;
    int _curlState;

    CURL *_curl;
	curl_httppost *_formPost;
	curl_httppost *_lastPost;

    int     _state;
    int     _errorCode;
    string  _errorMessage;

    // request
    typedef map<string, string> Fields;
    Fields _postFields;
    HTTPRequestHeaders _headers;

    // response
    int _responseCode;
    HTTPRequestHeaders _responseHeaders;
    void *_responseBuffer;
    size_t _responseBufferLength;
    size_t _responseDataLength;
    string _responseCookies;
    
    double _dltotal;
    double _dlnow;
    double _ultotal;
    double _ulnow;

    // private methods
    void cleanup(void);
    void cleanupRawResponseBuff(void);

    // instance callback
    void onRequest(void);
    size_t onWriteData(void *buffer, size_t bytes);
    size_t onWriteHeader(void *buffer, size_t bytes);
    int onProgress(double dltotal, double dlnow, double ultotal, double ulnow);

    // curl callback
#ifdef _WINDOWS_
    static DWORD WINAPI requestCURL(LPVOID userdata);
#else
    pthread_t _thread;
    static void *requestCURL(void *userdata);
#endif
    static size_t writeDataCURL(void *buffer, size_t size, size_t nmemb, void *userdata);
    static size_t writeHeaderCURL(void *buffer, size_t size, size_t nmemb, void *userdata);
    static int progressCURL(void *userdata, double dltotal, double dlnow, double ultotal, double ulnow);
};

NS_CC_EXTRA_END

#endif /* __CC_HTTP_REQUEST_H_ */
