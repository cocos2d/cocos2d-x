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
#include <sstream>
#include <condition_variable>
#include <stdio.h>
#include <errno.h>

#include "base/CCVector.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"

#include "platform/CCFileUtils.h"
#include "platform/android/jni/JniHelper.h"

NS_CC_BEGIN

namespace network {
    
typedef std::vector<std::string> HttpRequestHeaders;
typedef HttpRequestHeaders::iterator HttpRequestHeadersIter;
typedef std::vector<std::string> HttpCookies;
typedef HttpCookies::iterator HttpCookiesIter;

static std::mutex       s_requestQueueMutex;
static std::mutex       s_responseQueueMutex;
static std::mutex       s_cookieFileMutex;

static std::condition_variable_any s_sleepCondition;

static Vector<HttpRequest*>*  s_requestQueue = nullptr;
static Vector<HttpResponse*>* s_responseQueue = nullptr;

static HttpClient *s_httpClient = nullptr; // pointer to singleton

static std::string s_responseMessage = "";

static std::string s_cookieFilename = "";
    
static std::string s_sslCaFilename = "";

static HttpRequest *s_requestSentinel = new HttpRequest;
    

struct CookiesInfo
{
    std::string domain;
    bool tailmatch;
    std::string path;
    bool secure;
    std::string key;
    std::string value;
    std::string expires;
};

//static size_t writeData(void *ptr, size_t size, size_t nmemb, void *stream)
static size_t writeData(void* buffer, size_t sizes, HttpResponse* response)
{
    std::vector<char> * recvBuffer = (std::vector<char>*)response->getResponseData();
    recvBuffer->clear();
    recvBuffer->insert(recvBuffer->end(), (char*)buffer, ((char*)buffer) + sizes);
    return sizes;
} 

//static size_t writeHeaderData(void *ptr, size_t size, size_t nmemb, void *stream)
size_t writeHeaderData(void* buffer, size_t sizes,HttpResponse* response)
{
    std::vector<char> * recvBuffer = (std::vector<char>*) response->getResponseHeader();
    recvBuffer->clear();
    recvBuffer->insert(recvBuffer->end(), (char*)buffer, (char*)buffer + sizes);
    return sizes;
}

static void processResponse(HttpResponse* response, std::string& responseMessage);

class HttpURLConnection
{
public:
    HttpURLConnection():_httpURLConnection(nullptr),
    _requestmethod(""),
    _responseCookies(""),
    _cookieFileName(""),
    _contentLength(0)
    {

    }

    ~HttpURLConnection()
    {

    }
    
    void setRequestMethod(const char* method)
    {
        _requestmethod = method;
        
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                           "org/cocos2dx/lib/Cocos2dxHttpURLConnection",
                                           "setRequestMethod",
                                           "(Ljava/net/HttpURLConnection;Ljava/lang/String;)V"))
        {
            jstring jstr = methodInfo.env->NewStringUTF(_requestmethod.c_str());
            methodInfo.env->CallStaticVoidMethod(
                                                 methodInfo.classID, methodInfo.methodID, _httpURLConnection, jstr);
            methodInfo.env->DeleteLocalRef(jstr);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
    }
    
    bool init(HttpRequest* request)
    {
        createHttpURLConnection(request->getUrl());
        if(!configure())
            return false;
        /* get custom header data (if set) */
        HttpRequestHeaders headers=request->getHeaders();
        if(!headers.empty())
        {
            /* append custom headers one by one */
            for (HttpRequestHeadersIter it = headers.begin(); it != headers.end(); ++it)
            {
                std::string val = *it;
                
                int len = val.length();
                int pos = val.find(':');
                if (-1 == pos || pos >= len)
                {
                    continue;
                }
                std::string str1 = val.substr(0, pos);
                std::string str2 = val.substr(pos + 1, len - pos - 1);
                addRequestHeader(str1.c_str(), str2.c_str());
            }
        }
        
        addCookiesForRequestHeader();
        
        return true;
    }
    
    int connect()
    {
        int suc = 0;
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                           "org/cocos2dx/lib/Cocos2dxHttpURLConnection",
                                           "connect",
                                           "(Ljava/net/HttpURLConnection;)I"))
        {
            suc = methodInfo.env->CallStaticIntMethod(
                                                      methodInfo.classID, methodInfo.methodID, _httpURLConnection);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
        
        return suc;
    }
    
    void disconnect()
    {
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                           "org/cocos2dx/lib/Cocos2dxHttpURLConnection",
                                           "disconnect",
                                           "(Ljava/net/HttpURLConnection;)V"))
        {
            methodInfo.env->CallStaticVoidMethod(
                                                 methodInfo.classID, methodInfo.methodID, _httpURLConnection);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
    }
    
    int getResponseCode()
    {
        int responseCode = 0;
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                           "org/cocos2dx/lib/Cocos2dxHttpURLConnection",
                                           "getResponseCode",
                                           "(Ljava/net/HttpURLConnection;)I"))
        {
            responseCode = methodInfo.env->CallStaticIntMethod(
                                                           methodInfo.classID, methodInfo.methodID, _httpURLConnection);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
        
        return responseCode;
    }
    
    char* getResponseMessage()
    {
        char* message = nullptr;
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                           "org/cocos2dx/lib/Cocos2dxHttpURLConnection",
                                           "getResponseMessage",
                                           "(Ljava/net/HttpURLConnection;)Ljava/lang/String;"))
        {
            jobject jObj = methodInfo.env->CallStaticObjectMethod(
                                                                  methodInfo.classID, methodInfo.methodID, _httpURLConnection);
            message = getBufferFromJString((jstring)jObj, methodInfo.env);
            if (nullptr != jObj)
            {
                methodInfo.env->DeleteLocalRef(jObj);
            }
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
        
        return message;
    }
    
    void sendRequest(HttpRequest* request)
    {
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                           "org/cocos2dx/lib/Cocos2dxHttpURLConnection",
                                           "sendRequest",
                                           "(Ljava/net/HttpURLConnection;[B)V"))
        {
            
            jbyteArray bytearray;
            ssize_t dataSize = request->getRequestDataSize();
            bytearray = methodInfo.env->NewByteArray(dataSize);
            methodInfo.env->SetByteArrayRegion(bytearray, 0, dataSize, (const jbyte*)request->getRequestData());
            methodInfo.env->CallStaticVoidMethod(
                                                 methodInfo.classID, methodInfo.methodID, _httpURLConnection, bytearray);
            methodInfo.env->DeleteLocalRef(bytearray);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
    }
    
    size_t saveResponseCookies(const char* responseCookies, size_t count)
    {
        if (nullptr == responseCookies || strlen(responseCookies) == 0 || count == 0)
            return 0;
        
        if (_cookieFileName.empty())
        {
            _cookieFileName = FileUtils::getInstance()->getWritablePath() + "cookieFile.txt";
        }
        
        std::lock_guard<std::mutex> lock(s_cookieFileMutex);
        
        FILE* fp = fopen(_cookieFileName.c_str(), "w");
        if (nullptr == fp)
        {
            CCLOG("can't create or open response cookie files");
            return 0;
        }
        
        fwrite(responseCookies, sizeof(char), count, fp);
        
        fclose(fp);
        
        return count;
    }
    
    char* getResponseHeaders()
    {
        char* headers = nullptr;
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                           "org/cocos2dx/lib/Cocos2dxHttpURLConnection",
                                           "getResponseHeaders",
                                           "(Ljava/net/HttpURLConnection;)Ljava/lang/String;"))
        {
            jobject jObj = methodInfo.env->CallStaticObjectMethod(
                                                                  methodInfo.classID, methodInfo.methodID, _httpURLConnection);
            headers = getBufferFromJString((jstring)jObj, methodInfo.env);
            if (nullptr != jObj) {
                methodInfo.env->DeleteLocalRef(jObj);
            }
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
        
        return headers;
        
    }
    
    char* getResponseContent(HttpResponse* response)
    {
        if (nullptr == response)
            return nullptr;
        
        char* content = nullptr;
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                           "org/cocos2dx/lib/Cocos2dxHttpURLConnection",
                                           "getResponseContent",
                                           "(Ljava/net/HttpURLConnection;)[B"))
        {
            jobject jObj = methodInfo.env->CallStaticObjectMethod(
                                                                  methodInfo.classID, methodInfo.methodID, _httpURLConnection);
            
            _contentLength = getCStrFromJByteArray((jbyteArray)jObj, methodInfo.env, &content);
            if (nullptr != jObj) 
            {
                methodInfo.env->DeleteLocalRef(jObj);
            }
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
        
        return content;
    }
    
    char* getResponseHeaderByKey(const char* key)
    {
        char* value = nullptr;
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                           "org/cocos2dx/lib/Cocos2dxHttpURLConnection",
                                           "getResponseHeaderByKey",
                                           "(Ljava/net/HttpURLConnection;Ljava/lang/String;)Ljava/lang/String;"))
        {
            jstring jstrKey = methodInfo.env->NewStringUTF(key);
            jobject jObj = methodInfo.env->CallStaticObjectMethod(
                                                                  methodInfo.classID, methodInfo.methodID, _httpURLConnection, jstrKey);
            value = getBufferFromJString((jstring)jObj, methodInfo.env);
            methodInfo.env->DeleteLocalRef(jstrKey);
            if (nullptr != jObj) {
                methodInfo.env->DeleteLocalRef(jObj);
            }
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
        
        return value;
    }
    
    int getResponseHeaderByKeyInt(const char* key)
    {
        int contentLength = 0;
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                           "org/cocos2dx/lib/Cocos2dxHttpURLConnection",
                                           "getResponseHeaderByKeyInt",
                                           "(Ljava/net/HttpURLConnection;Ljava/lang/String;)I"))
        {
            jstring jstrKey = methodInfo.env->NewStringUTF(key);
            contentLength = methodInfo.env->CallStaticIntMethod(
                                                                methodInfo.classID, methodInfo.methodID, _httpURLConnection, jstrKey);
            methodInfo.env->DeleteLocalRef(jstrKey);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
        
        return contentLength;
    }
    
    char* getResponseHeaderByIdx(int idx)
    {
        char* header = nullptr;
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                           "org/cocos2dx/lib/Cocos2dxHttpURLConnection",
                                           "getResponseHeaderByIdx",
                                           "(Ljava/net/HttpURLConnection;I)Ljava/lang/String;"))
        {
            jobject jObj = methodInfo.env->CallStaticObjectMethod(
                                                                  methodInfo.classID, methodInfo.methodID, _httpURLConnection, idx);
            header = getBufferFromJString((jstring)jObj, methodInfo.env);
            if (nullptr != jObj) {
                methodInfo.env->DeleteLocalRef(jObj);
            }
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
        
        return header;
    }
    
    const std::string getCookieFileName()
    {
        return _cookieFileName;
    }
    
    void setCookieFileName(std::string& filename)
    {
        _cookieFileName = filename;
    }
    
    int getContentLength()
    {
        return _contentLength;
    }
    
private:
    void createHttpURLConnection(std::string url)
    {
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
            "org/cocos2dx/lib/Cocos2dxHttpURLConnection",
            "createHttpURLConnection",
            "(Ljava/lang/String;)Ljava/net/HttpURLConnection;"))
        {
            _url = url;
            jstring jurl = methodInfo.env->NewStringUTF(url.c_str());
            jobject jObj = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID, jurl);
            _httpURLConnection = methodInfo.env->NewGlobalRef(jObj);
            methodInfo.env->DeleteLocalRef(jurl);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
    }

    void addRequestHeader(const char* key, const char* value) 
    {
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
            "org/cocos2dx/lib/Cocos2dxHttpURLConnection",
            "addRequestHeader",
            "(Ljava/net/HttpURLConnection;Ljava/lang/String;Ljava/lang/String;)V"))
        {
            jstring jstrKey = methodInfo.env->NewStringUTF(key);
            jstring jstrVal = methodInfo.env->NewStringUTF(value);
            methodInfo.env->CallStaticVoidMethod(
                methodInfo.classID, methodInfo.methodID, _httpURLConnection, jstrKey, jstrVal);
            methodInfo.env->DeleteLocalRef(jstrKey);
            methodInfo.env->DeleteLocalRef(jstrVal);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
    }
    
    void addCookiesForRequestHeader()
    {
        if(s_cookieFilename.empty())
            return;
        
        _cookieFileName = FileUtils::getInstance()->fullPathForFilename(s_cookieFilename.c_str());
        
        std::lock_guard<std::mutex> lock(s_cookieFileMutex);
        
        std::string cookiesInfo = FileUtils::getInstance()->getStringFromFile(_cookieFileName.c_str());
        
        if (cookiesInfo.empty())
            return;
        
        HttpCookies cookiesVec;
        cookiesVec.clear();
        
        std::stringstream  stream(cookiesInfo);
        std::string item;
        while (std::getline(stream, item, '\n'))
        {
            cookiesVec.push_back(item);
        }
        
        if (cookiesVec.empty())
            return;
        
        HttpCookiesIter iter = cookiesVec.begin();
        
        std::vector<CookiesInfo> cookiesInfoVec;
        cookiesInfoVec.clear();

        for (; iter != cookiesVec.end(); iter++)
        {
            std::string cookies = *iter;
            if (cookies.find("#HttpOnly_") != std::string::npos)
            {
                cookies = cookies.substr(10);
            }
            
            if(cookies.at(0) == '#')
                continue;
            
            CookiesInfo co;
            std::stringstream streamInfo(cookies);
            std::string item;
            std::vector<std::string> elems;
            
            while (std::getline(streamInfo, item, '\t'))
            {
                elems.push_back(item);
            }
            
            co.domain = elems[0];
            if (co.domain.at(0) == '.')
            {
                co.domain = co.domain.substr(1);
            }
            co.tailmatch = strcmp("TRUE", elems.at(1).c_str())?true: false;
            co.path   = elems.at(2);
            co.secure = strcmp("TRUE", elems.at(3).c_str())?true: false;
            co.expires = elems.at(4);
            co.key = elems.at(5);
            co.value = elems.at(6);
            cookiesInfoVec.push_back(co);
        }

        std::vector<CookiesInfo>::iterator cookiesIter = cookiesInfoVec.begin();
        std::string sendCookiesInfo = "";
        int cookiesCount = 0;
        for (; cookiesIter != cookiesInfoVec.end(); cookiesIter++)
        {
            if (_url.find(cookiesIter->domain) != std::string::npos)
            {
                std::string keyValue = cookiesIter->key;
                keyValue.append("=");
                keyValue.append(cookiesIter->value);
                if (cookiesCount != 0)
                    sendCookiesInfo.append(";");
                
                sendCookiesInfo.append(keyValue);
            }
            cookiesCount++;
        }

        //set Cookie
        addRequestHeader("Cookie",sendCookiesInfo.c_str());
    }

    void setReadAndConnectTimeout(int readMiliseconds, int connectMiliseconds)
    {
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
            "org/cocos2dx/lib/Cocos2dxHttpURLConnection",
            "setReadAndConnectTimeout",
            "(Ljava/net/HttpURLConnection;II)V"))
        {
            methodInfo.env->CallStaticVoidMethod(
                methodInfo.classID, methodInfo.methodID, _httpURLConnection, readMiliseconds, connectMiliseconds);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
    }

    void setVerifySSL()
    {
        if(s_sslCaFilename.empty())
            return;

        std::string fullpath = FileUtils::getInstance()->fullPathForFilename(s_sslCaFilename.c_str());

        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
            "org/cocos2dx/lib/Cocos2dxHttpURLConnection",
            "setVerifySSL",
            "(Ljava/net/HttpURLConnection;Ljava/lang/String;)V"))
        {
            jstring jstrfullpath = methodInfo.env->NewStringUTF(fullpath.c_str());
            methodInfo.env->CallStaticVoidMethod(
                methodInfo.classID, methodInfo.methodID, _httpURLConnection, jstrfullpath);
            methodInfo.env->DeleteLocalRef(jstrfullpath);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
    }

    bool configure()
    {   
        if(nullptr == _httpURLConnection)
            return false;

        HttpClient* instnace = HttpClient::getInstance();
        if(nullptr == instnace)
            return false;

        setReadAndConnectTimeout(instnace->getTimeoutForRead() * 1000, instnace->getTimeoutForConnect() * 1000);

        setVerifySSL();

        return true;
    }

    char* getBufferFromJString(jstring jstr, JNIEnv* env)
    {
        if (nullptr == jstr) 
        {
            return nullptr;
        }

        const char* str = nullptr;
        char* ret = nullptr;
        str = env->GetStringUTFChars(jstr, nullptr);
        if (nullptr != str) 
        {
            ret = strdup(str);
        }

        env->ReleaseStringUTFChars(jstr, str);

        return ret;
    }

    int getCStrFromJByteArray(jbyteArray jba, JNIEnv* env, char** ppData) 
    {
        if (nullptr == jba) 
        {
            *ppData = nullptr;
            return 0;
        }

        char* str = nullptr;

        int len  = env->GetArrayLength(jba);
        str = (char*)malloc(sizeof(char)*len);
        env->GetByteArrayRegion(jba, 0, len, (jbyte*)str);

        *ppData = str;
        return len;
    }

    const std::string getCookieString()
    {
        return _responseCookies;
    }
private:
    jobject _httpURLConnection;
    std::string _requestmethod;
    std::string _responseCookies;
    std::string _cookieFileName;
    std::string _url;
    int _contentLength;
};

// Process Response
static void processResponse(HttpResponse* response, std::string& responseMessage)
{
    auto request = response->getHttpRequest();
    HttpRequest::Type requestType = request->getRequestType();

    if (HttpRequest::Type::GET != requestType && 
        HttpRequest::Type::POST != requestType && 
        HttpRequest::Type::PUT != requestType &&
        HttpRequest::Type::DELETE != requestType)
    {
        CCASSERT(true, "CCHttpClient: unknown request type, only GET、POST、PUT、DELETE are supported");
        return;
    }

    long responseCode = -1;
    int  retValue = 0;

    HttpURLConnection urlConnection;
    if(!urlConnection.init(request))
    {
        response->setSucceed(false);
        response->setErrorBuffer("HttpURLConnetcion init failed");
        return;
    }

    switch (requestType)
    {
        case HttpRequest::Type::GET:
            urlConnection.setRequestMethod("GET");
            break;

        case HttpRequest::Type::POST:
            urlConnection.setRequestMethod("POST");
            break;

        case HttpRequest::Type::PUT:
            urlConnection.setRequestMethod("PUT");
            break;

        case HttpRequest::Type::DELETE:
            urlConnection.setRequestMethod("DELETE");
            break;
        default:
            break;
    }

    int suc = urlConnection.connect();
    if (0 != suc)
    {
        response->setSucceed(false);
        response->setErrorBuffer("connect failed");
        response->setResponseCode(responseCode);
        return;
    }

    if (HttpRequest::Type::POST == requestType ||
        HttpRequest::Type::PUT == requestType)
    {
        urlConnection.sendRequest(request);
    }

    responseCode = urlConnection.getResponseCode();

    char* headers = urlConnection.getResponseHeaders();
    if (nullptr != headers)
    {
        writeHeaderData(headers, strlen(headers), response);
    }
    free(headers);

    //get and save cookies
    char* cookiesInfo = urlConnection.getResponseHeaderByKey("set-cookie");
    if (nullptr != cookiesInfo)
    {
        urlConnection.saveResponseCookies(cookiesInfo, strlen(cookiesInfo));
    }
    free(cookiesInfo);

    //content len
    int contentLength = urlConnection.getResponseHeaderByKeyInt("Content-Length");
    char* contentInfo = urlConnection.getResponseContent(response);
    if (nullptr != contentInfo) {
//      response->setResponseDataString(contentInfo, contentLength);
        std::vector<char> * recvBuffer = (std::vector<char>*)response->getResponseData();
        recvBuffer->clear();
        recvBuffer->insert(recvBuffer->begin(), (char*)contentInfo, ((char*)contentInfo) + urlConnection.getContentLength());
    }
    free(contentInfo);
    
    responseMessage = urlConnection.getResponseMessage();
    urlConnection.disconnect();

    // write data to HttpResponse
    response->setResponseCode(responseCode);

    if (responseCode == -1) 
    {
        response->setSucceed(false);
        response->setErrorBuffer(responseMessage.c_str());
    }
    else
    {
        response->setSucceed(true);
    }
}

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
                s_sleepCondition.wait(s_requestQueueMutex);
            }
            request = s_requestQueue->at(0);
            s_requestQueue->erase(0);
        }

        if (request == s_requestSentinel) {
            break;
        }
        
        // Create a HttpResponse object, the default setting is http access failed
        HttpResponse *response = new (std::nothrow) HttpResponse(request);
        processResponse(response, s_responseMessage);
        
        // add response packet into queue
        s_responseQueueMutex.lock();
        s_responseQueue->pushBack(response);
        s_responseQueueMutex.unlock();
        
        if (nullptr != s_httpClient) {
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
    std::string responseMessage = "";
    processResponse(response, responseMessage);

    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->performFunctionInCocosThread([response, request]{
        const ccHttpRequestCallback& callback = request->getCallback();
        Ref* pTarget = request->getTarget();
        SEL_HttpResponse pSelector = request->getSelector();

        if (callback != nullptr)
        {
            callback(s_httpClient, response);
        }
        else if (pTarget && pSelector)
        {
            (pTarget->*pSelector)(s_httpClient, response);
        }
        response->release();
        // do not release in other thread
        request->release();
    });
}

// HttpClient implementation
HttpClient* HttpClient::getInstance()
{
    if (s_httpClient == nullptr) {
        s_httpClient = new (std::nothrow) HttpClient();
    }
    
    return s_httpClient;
}

void HttpClient::destroyInstance()
{
    CC_SAFE_DELETE(s_httpClient);
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
        s_sleepCondition.notify_one();
    }

    s_httpClient = nullptr;
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
        s_sleepCondition.notify_one();
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


