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

using namespace cocos2d;

namespace network {

static std::mutex       s_requestQueueMutex;
static std::mutex       s_responseQueueMutex;

static std::mutex		s_SleepMutex;
static std::condition_variable		s_SleepCondition;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
typedef int int32_t;
#endif

static bool s_need_quit = false;

static Vector<HttpRequest*>*  s_requestQueue = nullptr;
static Vector<HttpResponse*>* s_responseQueue = nullptr;

static HttpClient *s_pHttpClient = NULL; // pointer to singleton

typedef size_t (*write_callback)(void *ptr, size_t size, size_t nmemb, void *stream);

static std::string s_cookieFilename = "";
    
static CURLM* curlMultiHandle = NULL;
    
static bool pollCurlEvents();

// Callback function used by libcurl for collect response data
static size_t writeData(void *ptr, size_t size, size_t nmemb, void *stream)
{
    HttpResponse* resp = (HttpResponse*)stream;
    std::vector<char>* recvBuffer = resp->getResponseData();
    size_t sizes = size * nmemb;
    
    // add data to the end of recvBuffer
    // write data maybe called more than once in a single request
    recvBuffer->insert(recvBuffer->end(), (char*)ptr, (char*)ptr+sizes);
    
    return sizes;
}

size_t writeDataToFile(void *ptr, size_t size, size_t nmemb, void *stream)
{
    HttpResponse* resp = (HttpResponse*)stream;
    
    size_t written = fwrite(ptr, size, nmemb, resp->getFileHandle());
    resp->setDownloadSize(resp->getDownloadSize() + written);
    return written;
}

// Callback function used by libcurl for collect header data
static size_t writeHeaderData(void *ptr, size_t size, size_t nmemb, void *stream)
{
    HttpResponse* resp = (HttpResponse*)stream;
    std::vector<char>* recvBuffer = resp->getResponseHeader();
    size_t sizes = size * nmemb;
    
    // add data to the end of recvBuffer
    // write data maybe called more than once in a single request
    recvBuffer->insert(recvBuffer->end(), (char*)ptr, (char*)ptr+sizes);
    
    return sizes;
}
    
static int progressCallback(HttpResponse *response, double dltotal, double dlnow, double ultotal, double ulnow)
{
    response->getHttpRequest()->getProgressCallback()(response, dlnow, dltotal);
    return 0;
}


static int processGetTask(HttpRequest *request, write_callback callback, write_callback headerCallback, HttpResponse *response);
static int processPostTask(HttpRequest *request, write_callback callback, write_callback headerCallback, HttpResponse *response);
static int processPutTask(HttpRequest *request, write_callback callback, write_callback headerCallback, HttpResponse *response);
static int processDeleteTask(HttpRequest *request, write_callback callback, write_callback headerCallback, HttpResponse *response);
// int processDownloadTask(HttpRequest *task, write_callback callback, void *stream, int32_t *errorCode);

void processRequest(HttpRequest *request)
{
    if (request)
    {
        // Create a HttpResponse object, the default setting is http access failed
        HttpResponse *response = new HttpResponse(request);
        
        // request's refcount = 2 here, it's retained by HttpRespose constructor
        request->release();
        // ok, refcount = 1 now, only HttpResponse hold it.

        int retValue = 0;
        
        if (!request->getDownloadPath().empty())
        {
            response->setFileHandle(fopen(request->getDownloadPath().c_str(), "wb"));
        }
        
        // Process the request -> get response packet
        switch (request->getRequestType())
        {
            case HttpRequest::Type::GET: // HTTP GET
                retValue = processGetTask(request,
                                          request->getDownloadPath().empty() ? writeData : writeDataToFile,
                                          writeHeaderData,
                                          response);
                break;
                
            case HttpRequest::Type::POST: // HTTP POST
                retValue = processPostTask(request,
                                           request->getDownloadPath().empty() ? writeData : writeDataToFile,
                                           writeHeaderData,
                                           response);
                break;
                
            case HttpRequest::Type::PUT:
                retValue = processPutTask(request,
                                          request->getDownloadPath().empty() ? writeData : writeDataToFile,
                                          writeHeaderData,
                                          response);
                break;
                
            case HttpRequest::Type::DELETE:
                retValue = processDeleteTask(request,
                                             request->getDownloadPath().empty() ? writeData : writeDataToFile,
                                             writeHeaderData,
                                             response);
                break;
                
            default:
                CCASSERT(true, "CCHttpClient: unkown request type, only support GET/POST/PUT/DELETE.");
                break;
        }
    }
}

// Worker thread
static void networkThread(void)
{
    while (!s_need_quit)
    {
        // send http request if the requestQueue isn't empty
        s_requestQueueMutex.lock();
        
        while (s_requestQueue->size() > 0)
        {
            HttpRequest *request = dynamic_cast<HttpRequest*>(s_requestQueue->at(0));
            s_requestQueue->erase(0);
            processRequest(request);
        }

        s_requestQueueMutex.unlock();
        
        if (!pollCurlEvents())
        {
            // Wait for http request tasks from main thread
            std::unique_lock<std::mutex> lk(s_SleepMutex); 
            s_SleepCondition.wait(lk);
        }
    }
    
    // cleanup: if worker thread received quit signal, clean up un-completed request queue
    s_requestQueueMutex.lock();
    s_requestQueue->clear();
    s_requestQueueMutex.unlock();
    
    
    if (s_requestQueue != nullptr) {
        delete s_requestQueue;
        s_requestQueue = nullptr;
        delete s_responseQueue;
        s_responseQueue = nullptr;
    }
    
}

class CURLRaii
{
    /// Instance of CURL
    CURL *_curl;
    /// Keeps custom header data
    curl_slist *_headers;
    
    char _errorBuffer[CURL_ERROR_SIZE];
    HttpResponse *_response;
    
private:
    //Configure curl's timeout property
    bool configureCURL(CURL *handle)
    {
        if (!handle) {
            return false;
        }
        
        int32_t code;
        code = curl_easy_setopt(handle, CURLOPT_ERRORBUFFER, _errorBuffer);
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
        code = curl_easy_setopt(handle, CURLOPT_PRIVATE, this);
        if (code != CURLE_OK) {
            return false;
        }
        code = curl_easy_setopt(handle, CURLOPT_ACCEPT_ENCODING, "");
        if (code != CURLE_OK) {
            return false;
        }
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L);
        
        // FIXED #3224: The subthread of CCHttpClient interrupts main thread if timeout comes.
        // Document is here: http://curl.haxx.se/libcurl/c/curl_easy_setopt.html#CURLOPTNOSIGNAL
        curl_easy_setopt(handle, CURLOPT_NOSIGNAL, 1L);
        
        return true;
    }

public:
    CURLRaii()
        : _curl(curl_easy_init())
        , _headers(NULL)
        , _response(NULL)
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
    
    HttpResponse* getResponse()
    {
        return _response;
    }
    
    char* getErrorBuffer()
    {
        return _errorBuffer;
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
    bool init(HttpRequest *request, write_callback callback, write_callback headerCallback, HttpResponse *response)
    {
        if (!_curl)
            return false;
        if (!configureCURL(_curl))
            return false;
        _response = response;

        /* get custom header data (if set) */
       	std::vector<std::string> headers = request->getHeaders();
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
                && setOption(CURLOPT_WRITEDATA, response)
                && setOption(CURLOPT_HEADERFUNCTION, headerCallback)
                && setOption(CURLOPT_HEADERDATA, response)
                && setOption(CURLOPT_NOPROGRESS, 0L)
                && setOption(CURLOPT_PROGRESSFUNCTION, progressCallback)
                && setOption(CURLOPT_PROGRESSDATA, response);
        
    }

    /// @param responseCode Null not allowed
    bool perform()
    {
        return curl_multi_add_handle(curlMultiHandle, _curl) == CURLM_OK;
    }
};

//Process Get Request
static int processGetTask(HttpRequest *request, write_callback callback, write_callback headerCallback, HttpResponse *response)
{
    CURLRaii *curl = new CURLRaii();
    bool ok = curl->init(request, callback, headerCallback, response)
            && curl->setOption(CURLOPT_FOLLOWLOCATION, true)
            && curl->perform();
    return ok ? 0 : 1;
}

//Process POST Request
static int processPostTask(HttpRequest *request, write_callback callback, write_callback headerCallback, HttpResponse *response)
{
    CURLRaii *curl = new CURLRaii();
    bool ok = curl->init(request, callback, headerCallback, response)
            && curl->setOption(CURLOPT_POST, 1)
            && curl->setOption(CURLOPT_POSTFIELDS, request->getRequestData())
            && curl->setOption(CURLOPT_POSTFIELDSIZE, request->getRequestDataSize())
            && curl->perform();
    return ok ? 0 : 1;
}

//Process PUT Request
static int processPutTask(HttpRequest *request, write_callback callback, write_callback headerCallback, HttpResponse *response)
{
    CURLRaii *curl = new CURLRaii();
    bool ok = curl->init(request, callback, headerCallback, response)
            && curl->setOption(CURLOPT_CUSTOMREQUEST, "PUT")
            && curl->setOption(CURLOPT_POSTFIELDS, request->getRequestData())
            && curl->setOption(CURLOPT_POSTFIELDSIZE, request->getRequestDataSize())
            && curl->perform();
    return ok ? 0 : 1;
}

//Process DELETE Request
static int processDeleteTask(HttpRequest *request, write_callback callback, write_callback headerCallback, HttpResponse *response)
{
    CURLRaii *curl = new CURLRaii();
    bool ok = curl->init(request, callback, headerCallback, response)
            && curl->setOption(CURLOPT_CUSTOMREQUEST, "DELETE")
            && curl->setOption(CURLOPT_FOLLOWLOCATION, true)
            && curl->perform();
    return ok ? 0 : 1;
}

bool pollCurlEvents()
{
    int runningHandles = 0;
    
    CURLMcode ret;
    do{
        ret = curl_multi_perform(curlMultiHandle, &runningHandles);
    } while (ret == CURLM_CALL_MULTI_PERFORM);
    
    // when a curl request finishes, post notification on main thread
    {
        CURLMsg* msg = NULL;
        int msgLeft = 0;
        
        while ((msg=curl_multi_info_read(curlMultiHandle, &msgLeft)))
        {
            if (msg->msg == CURLMSG_DONE)
            {
                CURL* curl = msg->easy_handle;
                CURLcode code = msg->data.result;
                CURLRaii* curlRaii;
                
                int responseCode = -1;
                curl_easy_getinfo(curl, CURLINFO_PRIVATE, &curlRaii);
                HttpResponse* resp = curlRaii->getResponse();
                if (code == CURLE_OK)
                {
                    code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
                    if (code != CURLE_OK || (responseCode != 200 && responseCode != 304 && responseCode != 206)) {
                        code = CURLE_HTTP_RETURNED_ERROR;
                    }
                }
                if (!resp->getHttpRequest()->getDownloadPath().empty())
                {
                    fclose(resp->getFileHandle());
                    resp->setFileHandle(NULL);
                }
                
                resp->setErrorBuffer(curlRaii->getErrorBuffer());
                resp->setSucceed(code == CURLE_OK);
                resp->setResponseCode(responseCode);
                
                curl_multi_remove_handle(curlMultiHandle, curl);
                delete curlRaii;
                
                if (code != CURLE_OK)
                    log("HTTPClient: curl perform task error: %d, %s, %d", code, curl_easy_strerror(code), responseCode);
                
                s_responseQueueMutex.lock();
                s_responseQueue->pushBack(resp);
                s_responseQueueMutex.unlock();
                
                // resume dispatcher selector
                Director::getInstance()->getScheduler()->resumeTarget(HttpClient::getInstance());
            }
        }
    }
    
    if (runningHandles)
    {
//        curl_multi_wait(curlMultiHandle, NULL, 0, 50, NULL);
        return true;
    }
    else
    {
        return false;
    }
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
        
        s_requestQueue = new Vector<HttpRequest*>();
        s_responseQueue = new Vector<HttpResponse*>();
        
        auto t = std::thread(CC_CALLBACK_0(HttpClient::networkThread, this));
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
        
    request->retain();
    
    s_requestQueueMutex.lock();
    s_requestQueue->pushBack(request);
    s_requestQueueMutex.unlock();
    
    // Notify thread start to work
    s_SleepCondition.notify_one();
}

// Poll and notify main thread if responses exists in queue
void HttpClient::dispatchResponseCallbacks()
{
    // log("CCHttpClient::dispatchResponseCallbacks is running");
    
    HttpResponse* response = NULL;
    
    s_responseQueueMutex.lock();

    if (!s_responseQueue->empty())
    {
        response = s_responseQueue->at(0);
        s_responseQueue->erase(0);
    }
    
    s_responseQueueMutex.unlock();
    
    if (response)
    {
        HttpRequest *request = response->getHttpRequest();
        Object *pTarget = request->getTarget();
        SEL_HttpResponse pSelector = request->getSelector();

        if (pTarget && pSelector) 
        {
            (pTarget->*pSelector)(this, response);
        }
        
        response->release();
    }
}

}


