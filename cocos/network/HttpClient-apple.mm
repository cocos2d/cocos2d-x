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

#include <thread>
#include <queue>
#include <condition_variable>

#include <errno.h>

#import "HttpAsynConnection.h"
#include "HttpCookie.h"

#include "base/CCVector.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"

#include "platform/CCFileUtils.h"

NS_CC_BEGIN

namespace network {

static std::mutex       s_requestQueueMutex;
static std::mutex       s_responseQueueMutex;

static std::condition_variable_any s_SleepCondition;

static Vector<HttpRequest*>*  s_requestQueue = nullptr;
static Vector<HttpResponse*>* s_responseQueue = nullptr;

static HttpClient *s_HttpClient = nullptr; // pointer to singleton
    
static HttpCookie *s_cookie = nullptr;
    
static const int ERROR_SIZE = 256;

static char s_errorBuffer[ERROR_SIZE] = {0};

static std::string s_cookieFilename = "";
    
static std::string s_sslCaFilename = "";


static int processTask(HttpRequest *request, NSString *requestType, void *stream, long *errorCode, void *headerStream, char *errorBuffer);

static void processResponse(HttpResponse* response, char* errorBuffer);

static HttpRequest *s_requestSentinel = new HttpRequest;

// Worker thread
void HttpClient::networkThread()
{    
    auto scheduler = Director::getInstance()->getScheduler();
    
    while (true) @autoreleasepool {
        
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
        
        // Create a HttpResponse object, the default setting is http access failed
        HttpResponse *response = new (std::nothrow) HttpResponse(request);
        
        processResponse(response, s_errorBuffer);
        
        // add response packet into queue
        s_responseQueueMutex.lock();
        s_responseQueue->pushBack(response);
        s_responseQueueMutex.unlock();
        
        if (nullptr != s_HttpClient) {
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
    char errorBuffer[ERROR_SIZE] = { 0 };
    processResponse(response, errorBuffer);

    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->performFunctionInCocosThread([response, request]{
        const ccHttpRequestCallback& callback = request->getCallback();
        Ref* pTarget = request->getTarget();
        SEL_HttpResponse pSelector = request->getSelector();

        if (callback != nullptr)
        {
            callback(s_HttpClient, response);
        }
        else if (pTarget && pSelector)
        {
            (pTarget->*pSelector)(s_HttpClient, response);
        }
        response->release();
        // do not release in other thread
        request->release();
    });
}

//Process Request
static int processTask(HttpRequest *request, NSString* requestType, void *stream, long *responseCode, void *headerStream, char *errorBuffer)
{
    //create request with url
    NSString* urlstring = [NSString stringWithUTF8String:request->getUrl()];
    NSURL *url = [NSURL URLWithString:urlstring];

    NSMutableURLRequest *nsrequest = [NSMutableURLRequest requestWithURL:url
                                               cachePolicy:NSURLRequestReloadIgnoringLocalAndRemoteCacheData
                                           timeoutInterval:HttpClient::getInstance()->getTimeoutForConnect()];
    
    //set request type
    [nsrequest setHTTPMethod:requestType];

    /* get custom header data (if set) */
    std::vector<std::string> headers=request->getHeaders();
    if(!headers.empty())
    {
        /* append custom headers one by one */
        for (std::vector<std::string>::iterator it = headers.begin(); it != headers.end(); ++it)
        {
            unsigned long i = it->find(':', 0);
            unsigned long length = it->size();
            std::string field = it->substr(0, i);
            std::string value = it->substr(i+1, length-i);
            NSString *headerField = [NSString stringWithUTF8String:field.c_str()];
            NSString *headerValue = [NSString stringWithUTF8String:value.c_str()];
            [nsrequest setValue:headerValue forHTTPHeaderField:headerField];
        }
    }

    //if request type is post or put,set header and data
    if([requestType  isEqual: @"POST"] || [requestType isEqual: @"PUT"])
    {
        if ([requestType isEqual: @"PUT"])
        {
            [nsrequest setValue: @"application/x-www-form-urlencoded" forHTTPHeaderField: @"Content-Type"];
        }
        
        char* requestDataBuffer = request->getRequestData();
        if (nullptr !=  requestDataBuffer && 0 != request->getRequestDataSize())
        {
            NSData *postData = [NSData dataWithBytes:requestDataBuffer length:request->getRequestDataSize()];
            [nsrequest setHTTPBody:postData];
        }
    }

    //read cookie propertities from file and set cookie
    if(!s_cookieFilename.empty())
    {
        const CookiesInfo* cookieInfo = s_cookie->getMatchCookie(request->getUrl());
        if(cookieInfo != nullptr)
        {
            NSString *domain = [NSString stringWithCString:cookieInfo->domain.c_str() encoding:[NSString defaultCStringEncoding]];
            NSString *path = [NSString stringWithCString:cookieInfo->path.c_str() encoding:[NSString defaultCStringEncoding]];
            NSString *value = [NSString stringWithCString:cookieInfo->value.c_str() encoding:[NSString defaultCStringEncoding]];
            NSString *name = [NSString stringWithCString:cookieInfo->name.c_str() encoding:[NSString defaultCStringEncoding]];

            // create the properties for a cookie
            NSDictionary *properties = [NSDictionary dictionaryWithObjectsAndKeys: name,NSHTTPCookieName,
            value, NSHTTPCookieValue, path, NSHTTPCookiePath,
            domain, NSHTTPCookieDomain,
            nil];
            
            // create the cookie from the properties
            NSHTTPCookie *cookie = [NSHTTPCookie cookieWithProperties:properties];
            
            // add the cookie to the cookie storage
            [[NSHTTPCookieStorage sharedHTTPCookieStorage] setCookie:cookie];
        }
    }
    
    HttpAsynConnection *httpAsynConn = [[HttpAsynConnection new] autorelease];
    httpAsynConn.srcURL = urlstring;
    httpAsynConn.sslFile = nil;
    
    if(!s_sslCaFilename.empty())
    {
        long len = s_sslCaFilename.length();
        long pos = s_sslCaFilename.rfind('.', len-1);
        
        httpAsynConn.sslFile = [NSString stringWithUTF8String:s_sslCaFilename.substr(0, pos-1).c_str()];
    }
    [httpAsynConn startRequest:nsrequest];
    
    while( httpAsynConn.finish != true)
    {
        [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]];
    }
    
    //if http connection return error
    if (httpAsynConn.connError != nil)
    {
        NSString* errorString = [httpAsynConn.connError localizedDescription];
        strcpy(errorBuffer, [errorString UTF8String]);
        return 0;
    }

    //if http response got error, just log the error
    if (httpAsynConn.responseError != nil)
    {
        NSString* errorString = [httpAsynConn.responseError localizedDescription];
        strcpy(errorBuffer, [errorString UTF8String]);
    }
    
    *responseCode = httpAsynConn.responseCode;
    
    //add cookie to cookies vector
    if(!s_cookieFilename.empty())
    {
        NSArray *cookies = [NSHTTPCookie cookiesWithResponseHeaderFields:httpAsynConn.responseHeader forURL:url];
        for (NSHTTPCookie *cookie in cookies)
        {
            //NSLog(@"Cookie: %@", cookie);
            NSString *domain = cookie.domain;
            //BOOL session = cookie.sessionOnly;
            NSString *path = cookie.path;
            BOOL secure = cookie.isSecure;
            NSDate *date = cookie.expiresDate;
            NSString *name = cookie.name;
            NSString *value = cookie.value;
            
            CookiesInfo cookieInfo;
            cookieInfo.domain = [domain cStringUsingEncoding: NSUTF8StringEncoding];
            cookieInfo.path = [path cStringUsingEncoding: NSUTF8StringEncoding];
            cookieInfo.secure = (secure == YES) ? true : false;
            cookieInfo.expires = [[NSString stringWithFormat:@"%ld", (long)[date timeIntervalSince1970]] cStringUsingEncoding: NSUTF8StringEncoding];
            cookieInfo.name = [name cStringUsingEncoding: NSUTF8StringEncoding];
            cookieInfo.value = [value cStringUsingEncoding: NSUTF8StringEncoding];
            cookieInfo.tailmatch = true;
            
            s_cookie->updateOrAddCookie(&cookieInfo);
        }
    }
    
    //handle response header
    NSMutableString *header = [NSMutableString string];
    [header appendFormat:@"HTTP/1.1 %ld %@\n", (long)httpAsynConn.responseCode, httpAsynConn.statusString];
    for (id key in httpAsynConn.responseHeader)
    {
        [header appendFormat:@"%@: %@\n", key, [httpAsynConn.responseHeader objectForKey:key]];
    }
    if (header.length > 0)
    {
        NSRange range = NSMakeRange(header.length-1, 1);
        [header deleteCharactersInRange:range];
    }
    NSData *headerData = [header dataUsingEncoding:NSUTF8StringEncoding];
    std::vector<char> *headerBuffer = (std::vector<char>*)headerStream;
    const void* headerptr = [headerData bytes];
    long headerlen = [headerData length];
    headerBuffer->insert(headerBuffer->end(), (char*)headerptr, (char*)headerptr+headerlen);

    //handle response data
    std::vector<char> *recvBuffer = (std::vector<char>*)stream;
    const void* ptr = [httpAsynConn.responseData bytes];
    long len = [httpAsynConn.responseData length];
    recvBuffer->insert(recvBuffer->end(), (char*)ptr, (char*)ptr+len);
    
    return 1;
}

// Process Response
static void processResponse(HttpResponse* response, char* errorBuffer)
{
    auto request = response->getHttpRequest();
    long responseCode = -1;
    int retValue = 0;
    NSString* requestType = nil;

    // Process the request -> get response packet
    switch (request->getRequestType())
    {
    case HttpRequest::Type::GET: // HTTP GET
        requestType = @"GET";
        break;

    case HttpRequest::Type::POST: // HTTP POST
        requestType = @"POST";
        break;

    case HttpRequest::Type::PUT:
        requestType = @"PUT";
        break;

    case HttpRequest::Type::DELETE:
        requestType = @"DELETE";
        break;

    default:
        CCASSERT(true, "CCHttpClient: unknown request type, only GET and POSt are supported");
        break;
    }
    
    retValue = processTask(request,
        requestType,
        response->getResponseData(),
        &responseCode,
        response->getResponseHeader(),
        errorBuffer);

    // write data to HttpResponse
    response->setResponseCode(responseCode);

    if (retValue != 0) 
    {
        response->setSucceed(true);
    }
    else
    {
        response->setSucceed(false);
        response->setErrorBuffer(errorBuffer);
    }
}

// HttpClient implementation
HttpClient* HttpClient::getInstance()
{
    if (s_HttpClient == nullptr) {
        s_HttpClient = new (std::nothrow) HttpClient();
    }
    
    return s_HttpClient;
}

void HttpClient::destroyInstance()
{
    CC_SAFE_DELETE(s_HttpClient);
}

void HttpClient::enableCookies(const char* cookieFile) {
    if (cookieFile) {
        s_cookieFilename = std::string(cookieFile);
        s_cookieFilename = FileUtils::getInstance()->fullPathForFilename(s_cookieFilename);
    }
    else {
        s_cookieFilename = (FileUtils::getInstance()->getWritablePath() + "cookieFile.txt");
    }
    
    s_cookie = new(std::nothrow)HttpCookie;
    s_cookie->setCookieFileName(s_cookieFilename);
    s_cookie->readFile();
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

    s_HttpClient = nullptr;
    
    if(!s_cookieFilename.empty())
    {
        s_cookie->writeFile();
        //delete s_cookie;
    }
    //s_cookie = nullptr;
}

//Lazy create semaphore & mutex & thread
bool HttpClient::lazyInitThreadSemphore()
{
    if (s_requestQueue != nullptr) {
        return true;
    } else {
        
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
    if(!request)
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


