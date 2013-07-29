/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 greathqy
 
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

#include "HttpClient.h"
#include <thread>
#include <queue>
#include <errno.h>

#include "curl/curl.h"

#include "platform/CCFileUtils.h"

NS_CC_EXT_BEGIN

static std::mutex       s_requestQueueMutex;
static std::mutex       s_responseQueueMutex;

static std::mutex		s_SleepMutex;
static std::condition_variable		s_SleepCondition;

static unsigned long    s_asyncRequestCount = 0;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
typedef int int32_t;
#endif

static bool s_need_quit = false;

static Array* s_requestQueue = NULL;
static Array* s_responseQueue = NULL;

static HttpClient *s_pHttpClient = NULL; // pointer to singleton

static char s_errorBuffer[CURL_ERROR_SIZE];

typedef size_t (*write_callback)(void *ptr, size_t size, size_t nmemb, void *stream);

static std::string s_cookieFilename = "";

// Callback function used by libcurl for collect response data
static size_t writeData(void *ptr, size_t size, size_t nmemb, void *stream)
{
    std::vector<char> *recvBuffer = (std::vector<char>*)stream;
    size_t sizes = size * nmemb;
    
    // add data to the end of recvBuffer
    // write data maybe called more than once in a single request
    recvBuffer->insert(recvBuffer->end(), (char*)ptr, (char*)ptr+sizes);
    
    return sizes;
}

// Callback function used by libcurl for collect header data
static size_t writeHeaderData(void *ptr, size_t size, size_t nmemb, void *stream)
{
    std::vector<char> *recvBuffer = (std::vector<char>*)stream;
    size_t sizes = size * nmemb;
    
    // add data to the end of recvBuffer
    // write data maybe called more than once in a single request
    recvBuffer->insert(recvBuffer->end(), (char*)ptr, (char*)ptr+sizes);
    
    return sizes;
}


static int processGetTask(HttpRequest *request, write_callback callback, void *stream, int32_t *errorCode, write_callback headerCallback, void *headerStream);
static int processPostTask(HttpRequest *request, write_callback callback, void *stream, int32_t *errorCode, write_callback headerCallback, void *headerStream);
static int processPutTask(HttpRequest *request, write_callback callback, void *stream, int32_t *errorCode, write_callback headerCallback, void *headerStream);
static int processDeleteTask(HttpRequest *request, write_callback callback, void *stream, int32_t *errorCode, write_callback headerCallback, void *headerStream);
// int processDownloadTask(HttpRequest *task, write_callback callback, void *stream, int32_t *errorCode);


// Worker thread
static void networkThread(void)
{    
    HttpRequest *request = NULL;
    
    while (true) 
    {
        if (s_need_quit)
        {
            break;
        }
        
        // step 1: send http request if the requestQueue isn't empty
        request = NULL;
        
        s_requestQueueMutex.lock();
        
        //Get request task from queue
        
        if (0 != s_requestQueue->count())
        {
            request = dynamic_cast<HttpRequest*>(s_requestQueue->objectAtIndex(0));
            s_requestQueue->removeObjectAtIndex(0);
        }
        
        s_requestQueueMutex.unlock();
        
        if (NULL == request)
        {
            // Wait for http request tasks from main thread
            std::unique_lock<std::mutex> lk(s_SleepMutex); 
            s_SleepCondition.wait(lk);
            continue;
        }
        
        // step 2: libcurl sync access
        
        // Create a HttpResponse object, the default setting is http access failed
        HttpResponse *response = new HttpResponse(request);
        
        // request's refcount = 2 here, it's retained by HttpRespose constructor
        request->release();
        // ok, refcount = 1 now, only HttpResponse hold it.
        
        int32_t responseCode = -1;
        int retValue = 0;

        // Process the request -> get response packet
        switch (request->getRequestType())
        {
            case HttpRequest::Type::GET: // HTTP GET
                retValue = processGetTask(request,
                                          writeData, 
                                          response->getResponseData(), 
                                          &responseCode,
                                          writeHeaderData,
                                          response->getResponseHeader());
                break;
            
            case HttpRequest::Type::POST: // HTTP POST
                retValue = processPostTask(request,
                                           writeData, 
                                           response->getResponseData(), 
                                           &responseCode,
                                           writeHeaderData,
                                           response->getResponseHeader());
                break;

            case HttpRequest::Type::PUT:
                retValue = processPutTask(request,
                                          writeData,
                                          response->getResponseData(),
                                          &responseCode,
                                          writeHeaderData,
                                          response->getResponseHeader());
                break;

            case HttpRequest::Type::DELETE:
                retValue = processDeleteTask(request,
                                             writeData,
                                             response->getResponseData(),
                                             &responseCode,
                                             writeHeaderData,
                                             response->getResponseHeader());
                break;
            
            default:
                CCASSERT(true, "CCHttpClient: unkown request type, only GET and POSt are supported");
                break;
        }
                
        // write data to HttpResponse
        response->setResponseCode(responseCode);
        
        if (retValue != 0) 
        {
            response->setSucceed(false);
            response->setErrorBuffer(s_errorBuffer);
        }
        else
        {
            response->setSucceed(true);
        }

        
        // add response packet into queue
        s_responseQueueMutex.lock();
        s_responseQueue->addObject(response);
        s_responseQueueMutex.unlock();
        
        // resume dispatcher selector
        Director::getInstance()->getScheduler()->resumeTarget(HttpClient::getInstance());
    }
    
    // cleanup: if worker thread received quit signal, clean up un-completed request queue
    s_requestQueueMutex.lock();
    s_requestQueue->removeAllObjects();
    s_requestQueueMutex.unlock();
    
    s_asyncRequestCount -= s_requestQueue->count();
    
    if (s_requestQueue != NULL) {

        s_requestQueue->release();
        s_requestQueue = NULL;
        s_responseQueue->release();
        s_responseQueue = NULL;
    }
    
}

//Configure curl's timeout property
static bool configureCURL(CURL *handle)
{
    if (!handle) {
        return false;
    }
    
    int32_t code;
    code = curl_easy_setopt(handle, CURLOPT_ERRORBUFFER, s_errorBuffer);
    if (code != CURLE_OK) {
        return false;
    }
    code = curl_easy_setopt(handle, CURLOPT_TIMEOUT, HttpClient::getInstance()->getTimeoutForRead());
    if (code != CURLE_OK) {
        return false;
    }
    code = curl_easy_setopt(handle, CURLOPT_CONNECTTIMEOUT, HttpClient::getInstance()->getTimeoutForConnect());
    if (code != CURLE_OK) {
        return false;
    }
    curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L);

    return true;
}

class CURLRaii
{
    /// Instance of CURL
    CURL *_curl;
    /// Keeps custom header data
    curl_slist *_headers;
public:
    CURLRaii()
        : _curl(curl_easy_init())
        , _headers(NULL)
    {
    }

    ~CURLRaii()
    {
        if (_curl)
            curl_easy_cleanup(_curl);
        /* free the linked list for header data */
        if (_headers)
            curl_slist_free_all(_headers);
    }

    template <class T>
    bool setOption(CURLoption option, T data)
    {
        return CURLE_OK == curl_easy_setopt(_curl, option, data);
    }

    /**
     * @brief Inits CURL instance for common usage
     * @param request Null not allowed
     * @param callback Response write callback
     * @param stream Response write stream
     */
    bool init(HttpRequest *request, write_callback callback, void *stream, write_callback headerCallback, void *headerStream)
    {
        if (!_curl)
            return false;
        if (!configureCURL(_curl))
            return false;

        /* get custom header data (if set) */
       	std::vector<std::string> headers=request->getHeaders();
        if(!headers.empty())
        {
            /* append custom headers one by one */
            for (std::vector<std::string>::iterator it = headers.begin(); it != headers.end(); ++it)
                _headers = curl_slist_append(_headers,it->c_str());
            /* set custom headers for curl */
            if (!setOption(CURLOPT_HTTPHEADER, _headers))
                return false;
        }
        if (!s_cookieFilename.empty()) {
            if (!setOption(CURLOPT_COOKIEFILE, s_cookieFilename.c_str())) {
                return false;
            }
            if (!setOption(CURLOPT_COOKIEJAR, s_cookieFilename.c_str())) {
                return false;
            }
        }

        return setOption(CURLOPT_URL, request->getUrl())
                && setOption(CURLOPT_WRITEFUNCTION, callback)
                && setOption(CURLOPT_WRITEDATA, stream)
                && setOption(CURLOPT_HEADERFUNCTION, headerCallback)
                && setOption(CURLOPT_HEADERDATA, headerStream);
        
    }

    /// @param responseCode Null not allowed
    bool perform(int *responseCode)
    {
        if (CURLE_OK != curl_easy_perform(_curl))
            return false;
        CURLcode code = curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, responseCode);
        if (code != CURLE_OK || *responseCode != 200) {
            CCLOGERROR("Curl curl_easy_getinfo failed: %s", curl_easy_strerror(code));
            return false;
        }
        // Get some mor data.
        
        return true;
    }
};

//Process Get Request
static int processGetTask(HttpRequest *request, write_callback callback, void *stream, int32_t *responseCode, write_callback headerCallback, void *headerStream)
{
    CURLRaii curl;
    bool ok = curl.init(request, callback, stream, headerCallback, headerStream)
            && curl.setOption(CURLOPT_FOLLOWLOCATION, true)
            && curl.perform(responseCode);
    return ok ? 0 : 1;
}

//Process POST Request
static int processPostTask(HttpRequest *request, write_callback callback, void *stream, int32_t *responseCode, write_callback headerCallback, void *headerStream)
{
    CURLRaii curl;
    bool ok = curl.init(request, callback, stream, headerCallback, headerStream)
            && curl.setOption(CURLOPT_POST, 1)
            && curl.setOption(CURLOPT_POSTFIELDS, request->getRequestData())
            && curl.setOption(CURLOPT_POSTFIELDSIZE, request->getRequestDataSize())
            && curl.perform(responseCode);
    return ok ? 0 : 1;
}

//Process PUT Request
static int processPutTask(HttpRequest *request, write_callback callback, void *stream, int32_t *responseCode, write_callback headerCallback, void *headerStream)
{
    CURLRaii curl;
    bool ok = curl.init(request, callback, stream, headerCallback, headerStream)
            && curl.setOption(CURLOPT_CUSTOMREQUEST, "PUT")
            && curl.setOption(CURLOPT_POSTFIELDS, request->getRequestData())
            && curl.setOption(CURLOPT_POSTFIELDSIZE, request->getRequestDataSize())
            && curl.perform(responseCode);
    return ok ? 0 : 1;
}

//Process DELETE Request
static int processDeleteTask(HttpRequest *request, write_callback callback, void *stream, int32_t *responseCode, write_callback headerCallback, void *headerStream)
{
    CURLRaii curl;
    bool ok = curl.init(request, callback, stream, headerCallback, headerStream)
            && curl.setOption(CURLOPT_CUSTOMREQUEST, "DELETE")
            && curl.setOption(CURLOPT_FOLLOWLOCATION, true)
            && curl.perform(responseCode);
    return ok ? 0 : 1;
}

// HttpClient implementation
HttpClient* HttpClient::getInstance()
{
    if (s_pHttpClient == NULL) {
        s_pHttpClient = new HttpClient();
    }
    
    return s_pHttpClient;
}

void HttpClient::destroyInstance()
{
    CCASSERT(s_pHttpClient, "");
    Director::getInstance()->getScheduler()->unscheduleSelector(schedule_selector(HttpClient::dispatchResponseCallbacks), s_pHttpClient);
    s_pHttpClient->release();
}

void HttpClient::enableCookies(const char* cookieFile) {
    if (cookieFile) {
        s_cookieFilename = std::string(cookieFile);
    }
    else {
        s_cookieFilename = (FileUtils::getInstance()->getWritablePath() + "cookieFile.txt");
    }
}

HttpClient::HttpClient()
: _timeoutForConnect(30)
, _timeoutForRead(60)
{
    Director::getInstance()->getScheduler()->scheduleSelector(
                    schedule_selector(HttpClient::dispatchResponseCallbacks), this, 0, false);
    Director::getInstance()->getScheduler()->pauseTarget(this);
}

HttpClient::~HttpClient()
{
    s_need_quit = true;
    
    if (s_requestQueue != NULL) {
    	s_SleepCondition.notify_one();
    }
    
    s_pHttpClient = NULL;
}

//Lazy create semaphore & mutex & thread
bool HttpClient::lazyInitThreadSemphore()
{
    if (s_requestQueue != NULL) {
        return true;
    } else {
        
        s_requestQueue = new Array();
        s_requestQueue->init();
        
        s_responseQueue = new Array();
        s_responseQueue->init();

        
        auto t = std::thread(&networkThread);
        t.detach();
        
        s_need_quit = false;
    }
    
    return true;
}

//Add a get task to queue
void HttpClient::send(HttpRequest* request)
{    
    if (false == lazyInitThreadSemphore()) 
    {
        return;
    }
    
    if (!request)
    {
        return;
    }
        
    ++s_asyncRequestCount;
    
    request->retain();
    
    s_requestQueueMutex.lock();
    s_requestQueue->addObject(request);
    s_requestQueueMutex.unlock();
    
    // Notify thread start to work
    s_SleepCondition.notify_one();
}

// Poll and notify main thread if responses exists in queue
void HttpClient::dispatchResponseCallbacks(float delta)
{
    // log("CCHttpClient::dispatchResponseCallbacks is running");
    
    HttpResponse* response = NULL;
    
    s_responseQueueMutex.lock();

    if (s_responseQueue->count())
    {
        response = dynamic_cast<HttpResponse*>(s_responseQueue->objectAtIndex(0));
        s_responseQueue->removeObjectAtIndex(0);
    }
    
    s_responseQueueMutex.unlock();
    
    if (response)
    {
        --s_asyncRequestCount;
        
        HttpRequest *request = response->getHttpRequest();
        Object *pTarget = request->getTarget();
        SEL_HttpResponse pSelector = request->getSelector();

        if (pTarget && pSelector) 
        {
            (pTarget->*pSelector)(this, response);
        }
        
        response->release();
    }
    
    if (0 == s_asyncRequestCount) 
    {
        Director::getInstance()->getScheduler()->pauseTarget(this);
    }
    
}

NS_CC_EXT_END


