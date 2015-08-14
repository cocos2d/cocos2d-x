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

#include "platform/CCPlatformConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

#include "HttpClient.h"

#include <thread>
#include <queue>
#include <condition_variable>

#include <errno.h>

#include "base/CCVector.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"

#include "platform/CCFileUtils.h"
#include "HttpConnection-winrt.h"

NS_CC_BEGIN

namespace network {

    static std::mutex       s_requestQueueMutex;
    static std::mutex       s_responseQueueMutex;

    static std::condition_variable_any s_SleepCondition;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    typedef int int32_t;
#endif

    static Vector<HttpRequest*>*  s_requestQueue = nullptr;
    static Vector<HttpResponse*>* s_responseQueue = nullptr;

    static HttpClient *s_pHttpClient = nullptr; // pointer to singleton

    static std::string s_errorBuffer ="";

    static std::string s_cookieFilename = "";

    static std::string s_sslCaFilename = "";

    // function used to collect response/header data
    static void writeData(std::vector<char> *pFromBuffer, std::vector<char> *pToBuffer)
    {
        if(nullptr == pFromBuffer || nullptr == pToBuffer)
            return;

        pToBuffer->insert(pToBuffer->end(), pFromBuffer->begin(), pFromBuffer->end());
    }

    static void processHttpResponse(HttpResponse* response, std::string& errorStr);

    static HttpRequest *s_requestSentinel = new HttpRequest;

    // Worker thread
    void HttpClient::networkThread()
    {
        auto scheduler = Director::getInstance()->getScheduler();

        while (true)
        {
            HttpRequest *request;

            // step 1: send http request if the requestQueue isn't empty
            {
                std::lock_guard<std::mutex> lock(s_requestQueueMutex);
                while (s_requestQueue->empty()) {
                    s_SleepCondition.wait(s_requestQueueMutex);
                }
                request = s_requestQueue->at(0);
                s_requestQueue->erase(0);
            }

            if (request == s_requestSentinel) {
                break;
            }

            // step 2: libcurl sync access

            // Create a HttpResponse object, the default setting is http access failed
            HttpResponse *response = new (std::nothrow) HttpResponse(request);

            processHttpResponse(response, s_errorBuffer);


            // add response packet into queue
            s_responseQueueMutex.lock();
            s_responseQueue->pushBack(response);
            s_responseQueueMutex.unlock();

            if (nullptr != s_pHttpClient) {
                scheduler->performFunctionInCocosThread(CC_CALLBACK_0(HttpClient::dispatchResponseCallbacks, this));
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

    // Worker thread
    void HttpClient::networkThreadAlone(HttpRequest* request, HttpResponse* response)
    {
        std::string errorStr;
        processHttpResponse(response, errorStr);

        auto scheduler = Director::getInstance()->getScheduler();
        scheduler->performFunctionInCocosThread([response, request]{
            const ccHttpRequestCallback& callback = request->getCallback();
            Ref* pTarget = request->getTarget();
            SEL_HttpResponse pSelector = request->getSelector();

            if (callback != nullptr)
            {
                callback(s_pHttpClient, response);
            }
            else if (pTarget && pSelector)
            {
                (pTarget->*pSelector)(s_pHttpClient, response);
            }
            response->release();
            // do not release in other thread
            request->release();
        });
    }

    // Process Response
    static void processHttpResponse(HttpResponse* response, std::string& errorStr)
    {
        auto request = response->getHttpRequest();
        long responseCode = -1;
        int retValue = 0;
        HttpConnection xhr;
        bool ok = false;
        bool manualAuthReqd = false;

        // Process the request -> get response packet
        switch (request->getRequestType())
        {
        case HttpRequest::Type::GET: // HTTP GET
            ok = (xhr.init(request) && xhr.open("GET", manualAuthReqd, s_cookieFilename) && xhr.send());
            break;

        case HttpRequest::Type::POST: // HTTP POST
            ok = (xhr.init(request) && xhr.open("POST", manualAuthReqd, s_cookieFilename) && xhr.send());
            break;

        case HttpRequest::Type::PUT: // HTTP PUT
            ok = (xhr.init(request) && xhr.open("PUT", manualAuthReqd, s_cookieFilename) && xhr.send());
            break;

        case HttpRequest::Type::DELETE: // HTTP DELETE
            ok = (xhr.init(request) && xhr.open("DELETE", manualAuthReqd, s_cookieFilename) && xhr.send());
            break;

        default:
            CCASSERT(true, "CCHttpClient: unknown request type, only GET and POST are supported");
            break;
        }

        writeData(xhr.getResponseHeader(), response->getResponseHeader());
        writeData(xhr.getResponseData(), response->getResponseData());
        retValue = ok ? 0 : 1;
        errorStr = xhr.getErrorMessage();
        responseCode = xhr.getStatusCode();

        // write data to HttpResponse
        response->setResponseCode(responseCode);

        if (retValue != 0)
        {
            response->setSucceed(false);
            response->setErrorBuffer(errorStr.c_str());
        }
        else
        {
            response->setSucceed(true);
        }
    }

    // HttpClient implementation
    HttpClient* HttpClient::getInstance()
    {
        if (s_pHttpClient == nullptr) {
            s_pHttpClient = new (std::nothrow) HttpClient();
        }

        return s_pHttpClient;
    }

    void HttpClient::destroyInstance()
    {
        CC_SAFE_DELETE(s_pHttpClient);
    }

    void HttpClient::enableCookies(const char* cookieFile) {
        if (cookieFile) {
            s_cookieFilename = std::string(cookieFile);
        }
        else {
            s_cookieFilename = (FileUtils::getInstance()->getWritablePath() + "cookieFile.txt");
        }
    }

    void HttpClient::setSSLVerification(const std::string& caFile)
    {
        s_sslCaFilename = caFile;
    }

    HttpClient::HttpClient()
        : _timeoutForConnect(30)
        , _timeoutForRead(60)
    {
    }

    HttpClient::~HttpClient()
    {
        if (s_requestQueue != nullptr) {
            {
                std::lock_guard<std::mutex> lock(s_requestQueueMutex);
                s_requestQueue->pushBack(s_requestSentinel);
            }
            s_SleepCondition.notify_one();
        }

        s_pHttpClient = nullptr;
    }

    //Lazy create semaphore & mutex & thread
    bool HttpClient::lazyInitThreadSemphore()
    {
        if (s_requestQueue != nullptr) {
            return true;
        }
        else {

            s_requestQueue = new (std::nothrow) Vector<HttpRequest*>();
            s_responseQueue = new (std::nothrow) Vector<HttpResponse*>();

            auto t = std::thread(CC_CALLBACK_0(HttpClient::networkThread, this));
            t.detach();
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

        if (nullptr != s_requestQueue) {
            s_requestQueueMutex.lock();
            s_requestQueue->pushBack(request);
            s_requestQueueMutex.unlock();

            // Notify thread start to work
            s_SleepCondition.notify_one();
        }
    }

    void HttpClient::sendImmediate(HttpRequest* request)
    {
        if (!request)
        {
            return;
        }

        request->retain();
        // Create a HttpResponse object, the default setting is http access failed
        HttpResponse *response = new (std::nothrow) HttpResponse(request);

        auto t = std::thread(&HttpClient::networkThreadAlone, this, request, response);
        t.detach();
    }

    // Poll and notify main thread if responses exists in queue
    void HttpClient::dispatchResponseCallbacks()
    {
        // log("CCHttpClient::dispatchResponseCallbacks is running");
        //occurs when cocos thread fires but the network thread has already quited
        if (nullptr == s_responseQueue) {
            return;
        }
        HttpResponse* response = nullptr;

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
            const ccHttpRequestCallback& callback = request->getCallback();
            Ref* pTarget = request->getTarget();
            SEL_HttpResponse pSelector = request->getSelector();

            if (callback != nullptr)
            {
                callback(this, response);
            }
            else if (pTarget && pSelector)
            {
                (pTarget->*pSelector)(this, response);
            }

            response->release();
            // do not release in other thread
            request->release();
        }
    }

    }

NS_CC_END

#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

