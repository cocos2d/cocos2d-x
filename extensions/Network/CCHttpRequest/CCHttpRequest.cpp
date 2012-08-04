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

#include "CCHttpRequest.h"
#include <queue>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include "platform/CCThread.h"
#include "curl/curl.h"

NS_CC_EXT_BEGIN

static pthread_t        s_requestThread;
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

static bool need_quit = false;

static std::queue<HttpRequestPacket *> *s_requestQueue = NULL;
static std::queue<HttpResponsePacket *> *s_responseQueue = NULL;

static CCHttpRequest *_g_singleton_httprequest = NULL;

static char errorBuffer[CURL_ERROR_SIZE];
typedef size_t (*write_callback)(void *ptr, size_t size, size_t nmemb, void *stream);

//Callback function used by libcurl for save file
size_t writeFile(void *ptr, size_t size, size_t nmemb, void *stream)
{
    int written = fwrite(ptr, size, nmemb, (FILE *)stream);
    
    return written;
}

//Callback function used by libcurl for collect response data
size_t writeData(void *ptr, size_t size, size_t nmemb, void *stream)
{
    std::string *str = (std::string *)stream;
    
    size_t sizes = size * nmemb;
    str->append((char *)ptr, sizes);
    
    return sizes;
}

//Prototypes
void releaseRequestQueue();
bool configureCURL(CURL *handle);
int processGetTask(HttpRequestPacket *task, write_callback callback, void *stream, int32_t *responseCode);
int processPostTask(HttpRequestPacket *task, write_callback callback, void *stream, int32_t *responseCode);
int processDownloadTask(HttpRequestPacket *task, write_callback callback, void *stream, int32_t *responseCode);

void CCHttpRequest::purgeSharedHttpRequest()
{
    CC_SAFE_RELEASE_NULL(_g_singleton_httprequest);
}

CCHttpRequest *CCHttpRequest::sharedHttpRequest()
{
    if (_g_singleton_httprequest == NULL) {
        _g_singleton_httprequest = new CCHttpRequest();
    }
    
    return _g_singleton_httprequest;
}

//Worker thread
static void *requestThread(void *data)
{
    CCThread thread;
    thread.createAutoreleasePool();
    
    HttpRequestPacket *req = NULL;
    
    while (true) {
        //Wait for http request tasks from main thread
        int semWaitRet = sem_wait(s_pSem);
        if (semWaitRet < 0) {
            CCLog("HttpRequest async thread semaphore error: %s\n", strerror(errno));
            break;
        }
        
        std::queue<HttpRequestPacket *> *pQueue = s_requestQueue;
        pthread_mutex_lock(&s_requestQueueMutex); //Get request task from queue
        if (pQueue->empty()) {
            pthread_mutex_unlock(&s_requestQueueMutex);
            
            if (need_quit) {
                break;
            } else {
                continue;
            }
        } else {
            if (need_quit) {
                pthread_mutex_unlock(&s_requestQueueMutex);
                break;
            }
            
            req = pQueue->front();
            pQueue->pop();
            pthread_mutex_unlock(&s_requestQueueMutex);
        }
        
        //Create a response packet and assume it will successed
        HttpResponsePacket *responsePacket = new HttpResponsePacket();
        responsePacket->request = req;
        responsePacket->succeed = true;

        //Process the request
        if (req->reqType == kHttpRequestGet) { //Get Request
            int32_t ret = processGetTask(req, writeData, &responsePacket->responseData, &responsePacket->responseCode);
            if (ret != 0) {
                responsePacket->succeed = false;
                responsePacket->responseData = errorBuffer;
            }
        } else if (req->reqType == kHttpRequestPost) { //Post Request
            int32_t ret = processPostTask(req, writeData, &responsePacket->responseData, &responsePacket->responseCode);
            if (ret != 0) {
                responsePacket->succeed = false;
                responsePacket->responseData = errorBuffer;
            }
        } else if (req->reqType == kHttpRequestDownloadFile) { //Download File Request
            bool fullyDownloaded = true;
            std::vector<std::string>::iterator iter;
            std::string saveFileName;
            std::string needDownload;
            
            for (iter = req->files.begin(); iter != req->files.end(); ++iter) {
                needDownload = *iter;
                std::string::size_type pos = needDownload.rfind("/");
                
                if (pos != std::string::npos) {
                    saveFileName = needDownload.substr(pos + 1);
                } else {
                    saveFileName = needDownload;
                }
                
                //If the download url is http://www.xxx.com/yyy.html
                //The saved file name must be yyy.html
                saveFileName = CCFileUtils::sharedFileUtils()->getWriteablePath() + saveFileName;
                FILE *handle = fopen(saveFileName.c_str(), "w+");
                if (!handle) {
                    fullyDownloaded = false;
                    break;
                }
                req->url = needDownload;
                int32_t ret = processDownloadTask(req, writeFile, handle, &responsePacket->responseCode);
                if (handle) {
                    fclose(handle);
                }
                if (ret != 0) {
                    fullyDownloaded = false;
                    break;
                }
            }
            
            //Only consider download task successfully when all the files downloaded
            if (!fullyDownloaded) {
                responsePacket->succeed = false;
                responsePacket->responseData = errorBuffer;
            }
        }
        
        pthread_mutex_lock(&s_responseQueueMutex);
        s_responseQueue->push(responsePacket);
        pthread_mutex_unlock(&s_responseQueueMutex);
    }
    
    //If worker thread received quit signal, clean up un-completed request queue
    releaseRequestQueue();
    
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
        
        delete s_requestQueue;
        delete s_responseQueue;
    }

    pthread_exit(NULL);
    
    return 0;
}

//Release Http request task queue
void releaseRequestQueue()
{
    pthread_mutex_lock(&s_requestQueueMutex);
    
    int32_t requestQueueSize = s_requestQueue->size();
    if (requestQueueSize > 0) {
        for (int32_t i = 0; i < requestQueueSize; ++i) {
            HttpRequestPacket *packet = s_requestQueue->front();
            s_requestQueue->pop();
            
            delete packet;
        }
        
        s_asyncRequestCount -= requestQueueSize;
    }
    
    pthread_mutex_unlock(&s_requestQueueMutex);
}

//Configure curl's timeout property
bool configureCURL(CURL *handle)
{
    if (!handle) {
        return false;
    }
    
    int32_t code;
    code = curl_easy_setopt(handle, CURLOPT_ERRORBUFFER, errorBuffer);
    if (code != CURLE_OK) {
        return false;
    }
    code = curl_easy_setopt(handle, CURLOPT_TIMEOUT, CCHttpRequest::sharedHttpRequest()->getDownloadTimeout());
    if (code != CURLE_OK) {
        return false;
    }
    code = curl_easy_setopt(handle, CURLOPT_CONNECTTIMEOUT, CCHttpRequest::sharedHttpRequest()->getConnectTimeout());
    if (code != CURLE_OK) {
        return false;
    }
    
    return true;
}

//Process Get Request
int processGetTask(HttpRequestPacket *task, write_callback callback, void *stream, int32_t *responseCode)
{
    CURLcode code = CURL_LAST;
    CURL *curl = curl_easy_init();
    
    do {
        if (!configureCURL(curl)) {
            break;
        }
        
        code = curl_easy_setopt(curl, CURLOPT_URL, task->url.c_str());
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
        code = curl_easy_perform(curl);
        if (code != CURLE_OK) {
            break;
        }
        
        code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, responseCode); 
        if (code != CURLE_OK || *responseCode / 100 != 2) {
            code = CURLE_HTTP_RETURNED_ERROR;
        }
    } while (0);
    if (curl) {
        curl_easy_cleanup(curl);
    }
    
    return (code == CURLE_OK ? 0 : 1);
}

//Process POST Request
int processPostTask(HttpRequestPacket *task, write_callback callback, void *stream, int32_t *responseCode)
{
    CURLcode code = CURL_LAST;
    CURL *curl = curl_easy_init();
    
    do {
        if (!configureCURL(curl)) {
            break;
        }
        
        code = curl_easy_setopt(curl, CURLOPT_URL, task->url.c_str());
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
        code = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, task->reqData.data());
        if (code != CURLE_OK) {
            break;
        }
        code = curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, task->reqData.size());
        if (code != CURLE_OK) {
            break;
        }
        code = curl_easy_perform(curl);
        if (code != CURLE_OK) {
            break;
        }
        
        code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, responseCode); 
        if (code != CURLE_OK || *responseCode / 100 != 2) {
            code = CURLE_HTTP_RETURNED_ERROR;
        }
    } while (0);
    if (curl) {
        curl_easy_cleanup(curl);
    }
    
    return (code == CURLE_OK ? 0 : 1);    
}

//Process Download Request
int processDownloadTask(HttpRequestPacket *task, write_callback callback, void *stream, int32_t *responseCode)
{
    return processGetTask(task, callback, stream, responseCode);
}

CCHttpRequest::CCHttpRequest()
{
    m_timeout = 60;
    m_connectTimeout = 10;
}

CCHttpRequest::~CCHttpRequest()
{
    need_quit = true;
    
    if (s_pSem != NULL) {
        sem_post(s_pSem);
    }
}

//Lazy create semaphore & mutex & thread
bool CCHttpRequest::lazyInitThreadSemphore()
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
        
        s_requestQueue = new std::queue<HttpRequestPacket *>();
        s_responseQueue = new std::queue<HttpResponsePacket *>();
        
        pthread_mutex_init(&s_requestQueueMutex, NULL);
        pthread_mutex_init(&s_responseQueueMutex, NULL);
        
        pthread_create(&s_requestThread, NULL, requestThread, NULL);
        pthread_detach(s_requestThread);
        
        need_quit = false;
    }
    
    return true;
}

//Add a get task to queue
void CCHttpRequest::addGetTask(std::string url, cocos2d::CCObject *pTarget, SEL_CallFuncND pSelector)
{
    bool inited = lazyInitThreadSemphore();
    if (!inited) {
        return;
    }
    
    if (0 == s_asyncRequestCount) {
        CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(CCHttpRequest::dispatchResponseCallbacks), this, 0, false);
    }
    
    ++s_asyncRequestCount;
    if (pTarget) {
        pTarget->retain();
    }
    
    HttpRequestPacket *packet = new HttpRequestPacket();
    packet->reqType = kHttpRequestGet;
    packet->reqId = this->reqId;
    packet->url = url;
    packet->pTarget = pTarget;
    packet->pSelector = pSelector;
    
    this->reqId.clear();
    
    pthread_mutex_lock(&s_requestQueueMutex);
    s_requestQueue->push(packet);
    pthread_mutex_unlock(&s_requestQueueMutex);
    
    //Notify thread start to work
    sem_post(s_pSem);
}

//Add a post task to queue
void CCHttpRequest::addPostTask(std::string &url, std::string &postData, CCObject *pTarget, SEL_CallFuncND pSelector)
{
    bool inited = lazyInitThreadSemphore();
    if (!inited) {
        return;
    }
    
    if (0 == s_asyncRequestCount) {
        CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(CCHttpRequest::dispatchResponseCallbacks), this, 0, false);
    }
    
    ++s_asyncRequestCount;
    if (pTarget) {
        pTarget->retain();
    }
    
    HttpRequestPacket *packet = new HttpRequestPacket();
    packet->reqType = kHttpRequestPost;
    packet->reqId = this->reqId;
    packet->url = url;
    packet->reqData = postData;
    packet->pTarget = pTarget;
    packet->pSelector = pSelector;
    
    this->reqId.clear();
    
    pthread_mutex_lock(&s_requestQueueMutex);
    s_requestQueue->push(packet);
    pthread_mutex_unlock(&s_requestQueueMutex);
    
    //Notify thread start to work
    sem_post(s_pSem);
}

//Add post task to queue, data binary safe
void CCHttpRequest::addPostTask(std::string &url, std::vector<char> &buffer, cocos2d::CCObject *pTarget, SEL_CallFuncND pSelector)
{
    std::string postData = std::string((const char *)&buffer.front(), buffer.size());
    addPostTask(url, postData, pTarget, pSelector);
}

//Convert const char* to string and call the matched addPostTask method
void CCHttpRequest::addPostTask(std::string &url, const char *buffer, int32_t bufferLen, cocos2d::CCObject *pTarget, SEL_CallFuncND pSelector)
{
    std::string postData = std::string(buffer, bufferLen);
    addPostTask(url, postData, pTarget, pSelector);
}

//Add a download task to queue
void CCHttpRequest::addDownloadTask(std::vector<std::string> &urls, CCObject *pTarget, SEL_CallFuncND pSelector)
{
    bool init = lazyInitThreadSemphore();
    if (!init) {
        return;
    }
    
    if (0 == s_asyncRequestCount) {
        CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(CCHttpRequest::dispatchResponseCallbacks), this, 0, false);
    }
    
    ++s_asyncRequestCount;
    if (pTarget) {
        pTarget->retain();
    }
    
    HttpRequestPacket *packet = new HttpRequestPacket();
    packet->reqType = kHttpRequestDownloadFile;
    packet->reqId   = this->reqId;
    packet->files   = urls;
    packet->pTarget = pTarget;
    packet->pSelector = pSelector;
    
    pthread_mutex_lock(&s_requestQueueMutex);
    s_requestQueue->push(packet);
    pthread_mutex_unlock(&s_requestQueueMutex);
    
    sem_post(s_pSem);    
}

//Poll and notify main thread if responses exists in queue
void CCHttpRequest::dispatchResponseCallbacks(float delta)
{
    std::queue<HttpResponsePacket *> *pQueue = s_responseQueue;
    
    pthread_mutex_lock(&s_responseQueueMutex);
    if (pQueue->empty()) {
        pthread_mutex_unlock(&s_responseQueueMutex);
    } else {
        HttpResponsePacket *packet = pQueue->front();
        pQueue->pop();
  
        pthread_mutex_unlock(&s_responseQueueMutex);
        
        --s_asyncRequestCount;
        if (0 == s_asyncRequestCount) {
            CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(CCHttpRequest::dispatchResponseCallbacks), this);
        }
        
        HttpRequestPacket *orgRequest = packet->request;
        CCObject *pTarget = orgRequest->pTarget;
        SEL_CallFuncND pSelector = orgRequest->pSelector;

        if (pTarget && pSelector) {
            (pTarget->*pSelector)((CCNode *)this, packet);
            
            pTarget->release();
        }
        
        delete orgRequest;
        delete packet;
    }
}

NS_CC_EXT_END


