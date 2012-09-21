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
// #include "platform/CCThread.h"

#include <queue>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

#include "curl/curl.h"

NS_CC_EXT_BEGIN

static pthread_t        s_networkThread;
static pthread_mutex_t  s_requestQueueMutex;
static pthread_mutex_t  s_responseQueueMutex;
static sem_t *          s_pSem = NULL;
static unsigned long    s_asyncRequestCount = 0;

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#define CC_ASYNC_HTTPREQUEST_USE_NAMED_SEMAPHORE 1
#else
#define CC_ASYNC_HTTPREQUEST_USE_NAMED_SEMAPHORE 0
#endif

#if CC_ASYNC_HTTPREQUEST_USE_NAMED_SEMAPHORE
#define CC_ASYNC_HTTPREQUEST_SEMAPHORE "ccHttpAsync"
#else
static sem_t s_sem;
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
typedef int int32_t;
#endif

static bool need_quit = false;

static CCArray* s_requestQueue = NULL;
static CCArray* s_responseQueue = NULL;

static CCHttpClient *s_pHttpClient = NULL; // pointer to singleton

static char s_errorBuffer[CURL_ERROR_SIZE];

typedef size_t (*write_callback)(void *ptr, size_t size, size_t nmemb, void *stream);


// Callback function used by libcurl for collect response data
size_t writeData(void *ptr, size_t size, size_t nmemb, void *stream)
{
    std::vector<char> *recvBuffer = (std::vector<char>*)stream;
    size_t sizes = size * nmemb;
    
    // add data to the end of recvBuffer
    // write data maybe called more than once in a single request
    recvBuffer->insert(recvBuffer->end(), (char*)ptr, (char*)ptr+sizes);
    
    return sizes;
}

// Prototypes
bool configureCURL(CURL *handle);
int processGetTask(CCHttpRequest *request, write_callback callback, void *stream, int32_t *errorCode);
int processPostTask(CCHttpRequest *request, write_callback callback, void *stream, int32_t *errorCode);
// int processDownloadTask(HttpRequest *task, write_callback callback, void *stream, int32_t *errorCode);


// Worker thread
static void* networkThread(void *data)
{    
    CCHttpRequest *request = NULL;
    
    while (true) 
    {
        // Wait for http request tasks from main thread
        int semWaitRet = sem_wait(s_pSem);
        if (semWaitRet < 0) {
            CCLog("HttpRequest async thread semaphore error: %s\n", strerror(errno));
            break;
        }
        
        if (need_quit)
        {
            break;
        }
        
        // step 1: send http request if the requestQueue isn't empty
        request = NULL;
        
        pthread_mutex_lock(&s_requestQueueMutex); //Get request task from queue
        if (0 != s_requestQueue->count())
        {
            request = dynamic_cast<CCHttpRequest*>(s_requestQueue->objectAtIndex(0));
            s_requestQueue->removeObjectAtIndex(0);  
            // request's refcount = 1 here
        }
        pthread_mutex_unlock(&s_requestQueueMutex);
        
        if (NULL == request)
        {
            continue;
        }
        
        // step 2: libcurl sync access
        
        // Create a HttpResponse object, the default setting is http access failed
        CCHttpResponse *response = new CCHttpResponse(request);
        
        // request's refcount = 2 here, it's retained by HttpRespose constructor
        request->release();
        // ok, refcount = 1 now, only HttpResponse hold it.
        
        int responseCode = -1;
        int retValue = 0;

        // Process the request -> get response packet
        switch (request->getRequestType())
        {
            case CCHttpRequest::kHttpGet: // HTTP GET
                retValue = processGetTask(request, 
                                          writeData, 
                                          response->getResponseData(), 
                                          &responseCode);
                break;
            
            case CCHttpRequest::kHttpPost: // HTTP POST
                retValue = processPostTask(request, 
                                           writeData, 
                                           response->getResponseData(), 
                                           &responseCode);
                break;
            
            default:
                CCAssert(true, "CCHttpClient: unkown request type, only GET and POSt are supported");
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
        pthread_mutex_lock(&s_responseQueueMutex);
        s_responseQueue->addObject(response);
        pthread_mutex_unlock(&s_responseQueueMutex);
        
        // resume dispatcher selector
        CCDirector::sharedDirector()->getScheduler()->resumeTarget(CCHttpClient::getInstance());
    }
    
    // cleanup: if worker thread received quit signal, clean up un-completed request queue
    pthread_mutex_lock(&s_requestQueueMutex);
    s_requestQueue->removeAllObjects();
    pthread_mutex_unlock(&s_requestQueueMutex);
    s_asyncRequestCount -= s_requestQueue->count();
    
    if (s_pSem != NULL) {
#if CC_ASYNC_HTTPREQUEST_USE_NAMED_SEMAPHORE
        sem_unlink(CC_ASYNC_HTTPREQUEST_SEMAPHORE);
        sem_close(s_pSem);
#else
        sem_destroy(s_pSem);
#endif
        
        s_pSem = NULL;
        
        pthread_mutex_destroy(&s_requestQueueMutex);
        pthread_mutex_destroy(&s_responseQueueMutex);
        
        s_requestQueue->release();
        s_responseQueue->release();
    }

    pthread_exit(NULL);
    
    return 0;
}

//Configure curl's timeout property
bool configureCURL(CURL *handle)
{
    if (!handle) {
        return false;
    }
    
    int32_t code;
    code = curl_easy_setopt(handle, CURLOPT_ERRORBUFFER, s_errorBuffer);
    if (code != CURLE_OK) {
        return false;
    }
    code = curl_easy_setopt(handle, CURLOPT_TIMEOUT, CCHttpClient::getInstance()->getTimeoutForRead());
    if (code != CURLE_OK) {
        return false;
    }
    code = curl_easy_setopt(handle, CURLOPT_CONNECTTIMEOUT, CCHttpClient::getInstance()->getTimeoutForConnect());
    if (code != CURLE_OK) {
        return false;
    }
    
    return true;
}

//Process Get Request
int processGetTask(CCHttpRequest *request, write_callback callback, void *stream, int *responseCode)
{
    CURLcode code = CURL_LAST;
    CURL *curl = curl_easy_init();
    
    do {
        if (!configureCURL(curl)) 
        {
            break;
        }
        
        code = curl_easy_setopt(curl, CURLOPT_URL, request->getUrl());
        if (code != CURLE_OK) 
        {
            break;
        }
        
        code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, request->getUrl());
        if (code != CURLE_OK)
        {
            break;
        }

        code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        if (code != CURLE_OK) 
        {
            break;
        }
        
        code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, stream);
        if (code != CURLE_OK) 
        {
            break;
        }
        
        code = curl_easy_perform(curl);
        if (code != CURLE_OK) 
        {
            break;
        }
        
        code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, responseCode); 
        if (code != CURLE_OK || *responseCode != 200) 
        {
            code = CURLE_HTTP_RETURNED_ERROR;
        }
    } while (0);
    
    if (curl) {
        curl_easy_cleanup(curl);
    }
    
    return (code == CURLE_OK ? 0 : 1);
}

//Process POST Request
int processPostTask(CCHttpRequest *request, write_callback callback, void *stream, int32_t *responseCode)
{
    CURLcode code = CURL_LAST;
    CURL *curl = curl_easy_init();
    
    do {
        if (!configureCURL(curl)) {
            break;
        }
        
        code = curl_easy_setopt(curl, CURLOPT_URL, request->getUrl());
        if (code != CURLE_OK) {
            break;
        }
        code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        if (code != CURLE_OK) {
            break;
        }
        code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, stream);
        if (code != CURLE_OK) {
            break;
        }
        code = curl_easy_setopt(curl, CURLOPT_POST, 1);
        if (code != CURLE_OK) {
            break;
        }
        code = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request->getRequestData());
        if (code != CURLE_OK) {
            break;
        }
        code = curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, request->getRequestDataSize());
        if (code != CURLE_OK) {
            break;
        }
        code = curl_easy_perform(curl);
        if (code != CURLE_OK) {
            break;
        }
        
        code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, responseCode); 
        if (code != CURLE_OK || *responseCode != 200) {
            code = CURLE_HTTP_RETURNED_ERROR;
        }
    } while (0);
    if (curl) {
        curl_easy_cleanup(curl);
    }
    
    return (code == CURLE_OK ? 0 : 1);    
}

// HttpClient implementation
CCHttpClient* CCHttpClient::getInstance()
{
    if (s_pHttpClient == NULL) {
        s_pHttpClient = new CCHttpClient();
    }
    
    return s_pHttpClient;
}

void CCHttpClient::destroyInstance()
{
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(CCHttpClient::dispatchResponseCallbacks), 
                                                                     CCHttpClient::getInstance());
    CC_SAFE_RELEASE_NULL(s_pHttpClient);
}

CCHttpClient::CCHttpClient()
:_timeoutForRead(60)
,_timeoutForConnect(30)
{
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(
                    schedule_selector(CCHttpClient::dispatchResponseCallbacks), this, 0, false);
    CCDirector::sharedDirector()->getScheduler()->pauseTarget(this);
}

CCHttpClient::~CCHttpClient()
{
    need_quit = true;
    
    if (s_pSem != NULL) {
        sem_post(s_pSem);
    }
    
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(CCHttpClient::dispatchResponseCallbacks), this);
}

//Lazy create semaphore & mutex & thread
bool CCHttpClient::lazyInitThreadSemphore()
{
    if (s_pSem != NULL) {
        return true;
    } else {
#if CC_ASYNC_HTTPREQUEST_USE_NAMED_SEMAPHORE
        s_pSem = sem_open(CC_ASYNC_HTTPREQUEST_SEMAPHORE, O_CREAT, 0644, 0);
        if (s_pSem == SEM_FAILED) {
            CCLog("Open HttpRequest Semaphore failed");
            s_pSem = NULL;
            return false;
        }
#else
        int semRet = sem_init(&s_sem, 0, 0);
        if (semRet < 0) {
            CCLog("Init HttpRequest Semaphore failed");
            return false;
        }
        
        s_pSem = &s_sem;
#endif
        
        s_requestQueue = new CCArray();
        s_requestQueue->init();
        
        s_responseQueue = new CCArray();
        s_responseQueue->init();
        
        pthread_mutex_init(&s_requestQueueMutex, NULL);
        pthread_mutex_init(&s_responseQueueMutex, NULL);
        
        pthread_create(&s_networkThread, NULL, networkThread, NULL);
        pthread_detach(s_networkThread);
        
        need_quit = false;
    }
    
    return true;
}

//Add a get task to queue
void CCHttpClient::send(CCHttpRequest* request)
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
        
    pthread_mutex_lock(&s_requestQueueMutex);
    s_requestQueue->addObject(request);
    pthread_mutex_unlock(&s_requestQueueMutex);
    
    // Notify thread start to work
    sem_post(s_pSem);
}

// Poll and notify main thread if responses exists in queue
void CCHttpClient::dispatchResponseCallbacks(float delta)
{
    // CCLog("CCHttpClient::dispatchResponseCallbacks is running");
    
    CCHttpResponse* response = NULL;
    
    pthread_mutex_lock(&s_responseQueueMutex);
    if (s_responseQueue->count())
    {
        response = dynamic_cast<CCHttpResponse*>(s_responseQueue->objectAtIndex(0));
        s_responseQueue->removeObjectAtIndex(0);
    }
    pthread_mutex_unlock(&s_responseQueueMutex);
    
    if (response)
    {
        --s_asyncRequestCount;
        
        CCHttpRequest *request = response->getHttpRequest();
        CCObject *pTarget = request->getTarget();
        SEL_CallFuncND pSelector = request->getSelector();

        if (pTarget && pSelector) 
        {
            (pTarget->*pSelector)((CCNode *)this, response);
        }
        
        response->release();
    }
    
    if (0 == s_asyncRequestCount) 
    {
        CCDirector::sharedDirector()->getScheduler()->pauseTarget(this);
    }
    
}

NS_CC_EXT_END


