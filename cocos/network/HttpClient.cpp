/****************************************************************************
 Copyright (c) 2012      greathqy
 Copyright (c) 2012      cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#include "base/CCVector.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "platform/CCFileUtils.h"

#include "curl/curl.h"

#include <errno.h>

#include <thread>
#include <queue>
#include <condition_variable>

NS_CC_BEGIN

namespace network {

typedef size_t (*write_callback)(void *ptr, size_t size, size_t nmemb, void *stream);

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

struct HttpTask {

    HttpTask(HttpClient *client_, HttpRequest* request_, const std::string &cookiesFilename_, const std::string &sslCaFilename_)
        : client(client_)
        , response(new HttpResponse(request_))
        , timeoutForConnect(client_->getTimeoutForConnect())
        , timeoutForRead(client_->getTimeoutForRead())
        , cookiesFilename(cookiesFilename_)
        , sslCaFilename(sslCaFilename_) {
        client->retain();
    }

    HttpClient *client;
    HttpResponse *response;
    const int timeoutForRead;
    const int timeoutForConnect;
    const std::string cookiesFilename;
    const std::string sslCaFilename;
};

class CURLRaii
{
    /// Instance of CURL
    CURL *_curl;
    /// Keeps custom header data
    curl_slist *_headers;
    HttpTask *_task;
public:
    CURLRaii(HttpTask *task)
        : _curl(curl_easy_init())
        , _headers(nullptr)
        , _task(task)
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

    //Configure curl's timeout property
    bool configureCURL(char *errorBuffer)
    {
        CURLcode code;
        code = curl_easy_setopt(_curl, CURLOPT_ERRORBUFFER, errorBuffer);
        if (code != CURLE_OK) {
            return false;
        }
        code = curl_easy_setopt(_curl, CURLOPT_TIMEOUT, _task->timeoutForRead);
        if (code != CURLE_OK) {
            return false;
        }
        code = curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT, _task->timeoutForConnect);
        if (code != CURLE_OK) {
            return false;
        }
        if (_task->sslCaFilename.empty()) {
            curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYHOST, 0L);
        } else {
            curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 1L);
            curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYHOST, 2L);
            curl_easy_setopt(_curl, CURLOPT_CAINFO, _task->sslCaFilename.c_str());
        }

        // FIXED #3224: The subthread of CCHttpClient interrupts main thread if timeout comes.
        // Document is here: http://curl.haxx.se/libcurl/c/curl_easy_setopt.html#CURLOPTNOSIGNAL 
        curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1L);

        return true;
    }

    /**
     * @brief Inits CURL instance for common usage
     * @param request Null not allowed
     * @param callback Response write callback
     * @param stream Response write stream
     */
    bool init(HttpRequest *request, write_callback callback, void *stream, write_callback headerCallback, void *headerStream, char *errorBuffer)
    {
        if (!_curl)
            return false;
        if (!configureCURL(errorBuffer))
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
        if (!_task->cookiesFilename.empty()) {
            if (!setOption(CURLOPT_COOKIEFILE, _task->cookiesFilename.c_str())) {
                return false;
            }
            if (!setOption(CURLOPT_COOKIEJAR, _task->cookiesFilename.c_str())) {
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
    bool perform(long *responseCode)
    {
        if (CURLE_OK != curl_easy_perform(_curl))
            return false;
        CURLcode code = curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, responseCode);
        if (code != CURLE_OK || !(*responseCode >= 200 && *responseCode < 300)) {
            CCLOGERROR("Curl curl_easy_getinfo failed: %s", curl_easy_strerror(code));
            return false;
        }
        // Get some mor data.
        
        return true;
    }
};

//Process Get Request
static int processGetTask(HttpTask *task, HttpRequest *request, write_callback callback, void *stream, long *responseCode, write_callback headerCallback, void *headerStream, char *errorBuffer)
{
    CURLRaii curl(task);
    bool ok = curl.init(request, callback, stream, headerCallback, headerStream, errorBuffer)
            && curl.setOption(CURLOPT_FOLLOWLOCATION, true)
            && curl.perform(responseCode);
    return ok ? 0 : 1;
}

//Process POST Request
static int processPostTask(HttpTask *task, HttpRequest *request, write_callback callback, void *stream, long *responseCode, write_callback headerCallback, void *headerStream, char *errorBuffer)
{
    CURLRaii curl(task);
    bool ok = curl.init(request, callback, stream, headerCallback, headerStream, errorBuffer)
            && curl.setOption(CURLOPT_POST, 1)
            && curl.setOption(CURLOPT_POSTFIELDS, request->getRequestData())
            && curl.setOption(CURLOPT_POSTFIELDSIZE, request->getRequestDataSize())
            && curl.perform(responseCode);
    return ok ? 0 : 1;
}

//Process PUT Request
static int processPutTask(HttpTask *task, HttpRequest *request, write_callback callback, void *stream, long *responseCode, write_callback headerCallback, void *headerStream, char *errorBuffer)
{
    CURLRaii curl(task);
    bool ok = curl.init(request, callback, stream, headerCallback, headerStream, errorBuffer)
            && curl.setOption(CURLOPT_CUSTOMREQUEST, "PUT")
            && curl.setOption(CURLOPT_POSTFIELDS, request->getRequestData())
            && curl.setOption(CURLOPT_POSTFIELDSIZE, request->getRequestDataSize())
            && curl.perform(responseCode);
    return ok ? 0 : 1;
}

//Process DELETE Request
static int processDeleteTask(HttpTask *task, HttpRequest *request, write_callback callback, void *stream, long *responseCode, write_callback headerCallback, void *headerStream, char *errorBuffer)
{
    CURLRaii curl(task);
    bool ok = curl.init(request, callback, stream, headerCallback, headerStream, errorBuffer)
            && curl.setOption(CURLOPT_CUSTOMREQUEST, "DELETE")
            && curl.setOption(CURLOPT_FOLLOWLOCATION, true)
            && curl.perform(responseCode);
    return ok ? 0 : 1;
}


// Process Response
static void processResponse(HttpTask* task, HttpResponse* response, char* errorBuffer)
{
    auto request = response->getHttpRequest();
    long responseCode = -1;
    int retValue = 0;

    // Process the request -> get response packet
    switch (request->getRequestType())
    {
    case HttpRequest::Type::GET: // HTTP GET
        retValue = processGetTask(task,
            request,
            writeData, 
            response->getResponseData(), 
            &responseCode,
            writeData,
            response->getResponseHeader(),
            errorBuffer);
        break;

    case HttpRequest::Type::POST: // HTTP POST
        retValue = processPostTask(task,
            request,
            writeData, 
            response->getResponseData(), 
            &responseCode,
            writeData,
            response->getResponseHeader(),
            errorBuffer);
        break;

    case HttpRequest::Type::PUT:
        retValue = processPutTask(task,
            request,
            writeData,
            response->getResponseData(),
            &responseCode,
            writeData,
            response->getResponseHeader(),
            errorBuffer);
        break;

    case HttpRequest::Type::DELETE:
        retValue = processDeleteTask(task,
            request,
            writeData,
            response->getResponseData(),
            &responseCode,
            writeData,
            response->getResponseHeader(),
            errorBuffer);
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
        response->setErrorBuffer(errorBuffer);
    }
    else
    {
        response->setSucceed(true);
    }
}

class HttpTaskQueue {
public:

    void pushTask(HttpTask* task) {
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _tasks.push_back(task);
        }
        _notEmpty.notify_one();
    }

    void pushImmediateTask(HttpTask *task) {
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _immediateTasks.push_back(task);
        }
        _notEmpty.notify_one();
    }

    HttpTask* takeTask() {
        std::lock_guard<std::mutex> lock(_mutex);
        while (_immediateTasks.empty() && _tasks.empty()) {
            _notEmpty.wait(_mutex);
        }
        if (!_immediateTasks.empty()) {
            HttpTask *task = _tasks.front();
            _tasks.pop_front();
            return task;
        }
        HttpTask* task = _tasks.front();
        _tasks.pop_front();
        return task;
    }

private:
    std::deque<HttpTask*> _tasks;
    std::deque<HttpTask*> _immediateTasks;
    std::mutex _mutex;
    std::condition_variable_any _notEmpty;
};

static void performTasks(Scheduler *scheduler, HttpTaskQueue *tq) {
    std::unique_ptr<char[]> errorBuffer(new char[1024]);
    for (;;) {
        std::unique_ptr<HttpTask> task(tq->takeTask());
        HttpClient* client = task->client;
        HttpResponse* response = task->response;
        errorBuffer[0] = '\0';
        processResponse(task.get(), response, errorBuffer.get());
        scheduler->performFunctionInCocosThread([client, response] {
            HttpRequest *request = response->getHttpRequest();
            const ccHttpRequestCallback& callback = request->getCallback();
            Ref* pTarget = request->getTarget();
            SEL_HttpResponse pSelector = request->getSelector();
            if (callback != nullptr) {
                callback(client, response);
            } else if (pTarget && pSelector) {
                (pTarget->*pSelector)(client, response);
            }
            client->release();
            response->release();
        });
    }
}

class HttpBackend {
public:

    HttpTaskQueue* getTaskQueue() {
        if (!_thread.joinable()) {
            Scheduler *scheduler = Director::getInstance()->getScheduler();
            _thread = std::thread(performTasks, scheduler, &_tqueue);
        }
        return &_tqueue;
    }

private:
    HttpTaskQueue _tqueue;
    std::thread _thread;
};

static HttpTaskQueue* getBackendTaskQueue() {
    static HttpBackend httpBackend;
    return httpBackend.getTaskQueue();
}

static HttpClient *_pHttpClient;

// HttpClient implementation
HttpClient* HttpClient::getInstance()
{
    if (_pHttpClient == nullptr) {
        _pHttpClient = new (std::nothrow) HttpClient();
    }
    return _pHttpClient;
}

void HttpClient::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(_pHttpClient);
}

void HttpClient::enableCookies(const char* cookieFile) {
    if (cookieFile) {
        _cookiesFilename = std::string(cookieFile);
    }
    else {
        _cookiesFilename = (FileUtils::getInstance()->getWritablePath() + "cookieFile.txt");
    }
}
    
void HttpClient::setSSLVerification(const std::string& caFile)
{
    _sslCaFilename = caFile;
}

HttpClient::HttpClient()
: _timeoutForConnect(30)
, _timeoutForRead(60)
{
}

HttpClient::~HttpClient()
{
}

void HttpClient::send(HttpRequest* request)
{    
    if (!request)
    {
        return;
    }

    HttpTask *task = new HttpTask(this, request, _cookiesFilename, _sslCaFilename);
    HttpTaskQueue *tq = getBackendTaskQueue();
    tq->pushTask(task);
}

void HttpClient::sendImmediate(HttpRequest* request)
{
    if(!request)
    {
        return;
    }

    HttpTask *task = new HttpTask(this, request, _cookiesFilename, _sslCaFilename);
    HttpTaskQueue *tq = getBackendTaskQueue();
    tq->pushImmediateTask(task);
}

}

NS_CC_END


