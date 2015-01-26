#include "network/CCHTTPRequest.h"
#include <stdio.h>
#include <iostream>
#include <thread>

#if CC_LUA_ENGINE_ENABLED > 0
extern "C" {
#include "lua.h"
}
#include "CCLuaEngine.h"
#endif
#include <sstream>


NS_CC_EXTRA_BEGIN

unsigned int HTTPRequest::s_id = 0;

HTTPRequest *HTTPRequest::createWithUrl(HTTPRequestDelegate *delegate,
                                            const char *url,
                                            int method)
{
    HTTPRequest *request = new HTTPRequest();
    request->initWithDelegate(delegate, url, method);
    request->autorelease();
    return request;
}

#if CC_LUA_ENGINE_ENABLED > 0
HTTPRequest *HTTPRequest::createWithUrlLua(LUA_FUNCTION listener,
                                               const char *url,
                                               int method)
{
    HTTPRequest *request = new HTTPRequest();
    request->initWithListener(listener, url, method);
    request->autorelease();
    return request;
}
#endif

bool HTTPRequest::initWithDelegate(HTTPRequestDelegate *delegate, const char *url, int method)
{
    _delegate = delegate;
    return initWithUrl(url, method);
}

#if CC_LUA_ENGINE_ENABLED > 0
bool HTTPRequest::initWithListener(LUA_FUNCTION listener, const char *url, int method)
{
    _listener = listener;
    return initWithUrl(url, method);
}
#endif

bool HTTPRequest::initWithUrl(const char *url, int method)
{
    CCAssert(url, "HTTPRequest::initWithUrl() - invalid url");
    _curl = curl_easy_init();
    curl_easy_setopt(_curl, CURLOPT_URL, url);
    curl_easy_setopt(_curl, CURLOPT_USERAGENT, "libcurl");
    curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT, DEFAULT_TIMEOUT);
    curl_easy_setopt(_curl, CURLOPT_TIMEOUT, DEFAULT_TIMEOUT);
    curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1L);

    if (method == kCCHTTPRequestMethodPOST)
    {
        curl_easy_setopt(_curl, CURLOPT_POST, 1L);
        curl_easy_setopt(_curl, CURLOPT_COPYPOSTFIELDS, "");
    }
    
    ++s_id;
    // CCLOG("HTTPRequest[0x%04x] - create request with url: %s", s_id, url);
    return true;
}

HTTPRequest::~HTTPRequest(void)
{
    cleanup();
    if (_listener)
    {
#if (CC_LUA_ENGINE_ENABLED > 0)
        LuaEngine::getInstance()->removeScriptHandler(_listener);
#endif
    }
    // CCLOG("HTTPRequest[0x%04x] - request removed", s_id);
}

void HTTPRequest::setRequestUrl(const char *url)
{
    CCAssert(url, "HTTPRequest::setRequestUrl() - invalid url");
    _url = url;
    curl_easy_setopt(_curl, CURLOPT_URL, _url.c_str());
}

const string HTTPRequest::getRequestUrl(void)
{
    return _url;
}

void HTTPRequest::addRequestHeader(const char *header)
{
    CCAssert(_state == kCCHTTPRequestStateIdle, "HTTPRequest::addRequestHeader() - request not idle");
    CCAssert(header, "HTTPRequest::addRequestHeader() - invalid header");
    _headers.push_back(string(header));
}

void HTTPRequest::addPOSTValue(const char *key, const char *value)
{
    CCAssert(_state == kCCHTTPRequestStateIdle, "HTTPRequest::addPOSTValue() - request not idle");
    CCAssert(key, "HTTPRequest::addPOSTValue() - invalid key");
    _postFields[string(key)] = string(value ? value : "");
}

void HTTPRequest::setPOSTData(const char *data)
{
    CCAssert(_state == kCCHTTPRequestStateIdle, "HTTPRequest::setPOSTData() - request not idle");
    CCAssert(data, "HTTPRequest::setPOSTData() - invalid post data");
    _postFields.clear();
    curl_easy_setopt(_curl, CURLOPT_POST, 1L);
    curl_easy_setopt(_curl, CURLOPT_COPYPOSTFIELDS, data);
}

void HTTPRequest::addFormFile(const char *name, const char *filePath, const char *contentType)
{
	curl_formadd(&_formPost, &_lastPost,
		CURLFORM_COPYNAME, name,
		CURLFORM_FILE, filePath,
		CURLFORM_CONTENTTYPE, contentType,
		CURLFORM_END);
	//CCLOG("addFormFile %s %s %s", name, filePath, contentType);
}

void HTTPRequest::addFormContents(const char *name, const char *value)
{
	curl_formadd(&_formPost, &_lastPost,
		CURLFORM_COPYNAME, name,
		CURLFORM_COPYCONTENTS, value,
		CURLFORM_END);
	//CCLOG("addFormContents %s %s", name, value);
}

void HTTPRequest::setCookieString(const char *cookie)
{
    CCAssert(_state == kCCHTTPRequestStateIdle, "HTTPRequest::setAcceptEncoding() - request not idle");
    curl_easy_setopt(_curl, CURLOPT_COOKIE, cookie ? cookie : "");
}

const string HTTPRequest::getCookieString(void)
{
    CCAssert(_state == kCCHTTPRequestStateCompleted, "HTTPRequest::getResponseData() - request not completed");
    return _responseCookies;
}

void HTTPRequest::setAcceptEncoding(int acceptEncoding)
{
    CCAssert(_state == kCCHTTPRequestStateIdle, "HTTPRequest::setAcceptEncoding() - request not idle");
    switch (acceptEncoding)
    {
        case kCCHTTPRequestAcceptEncodingGzip:
            curl_easy_setopt(_curl, CURLOPT_ACCEPT_ENCODING, "gzip");
            break;
            
        case kCCHTTPRequestAcceptEncodingDeflate:
            curl_easy_setopt(_curl, CURLOPT_ACCEPT_ENCODING, "deflate");
            break;
            
        default:
            curl_easy_setopt(_curl, CURLOPT_ACCEPT_ENCODING, "identity");
    }
}

void HTTPRequest::setTimeout(int timeout)
{
    CCAssert(_state == kCCHTTPRequestStateIdle, "HTTPRequest::setTimeout() - request not idle");
    curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT, timeout);
    curl_easy_setopt(_curl, CURLOPT_TIMEOUT, timeout);
}

bool HTTPRequest::start(void)
{
    CCAssert(_state == kCCHTTPRequestStateIdle, "HTTPRequest::start() - request not idle");

    _state = kCCHTTPRequestStateInProgress;
    _curlState = kCCHTTPRequestCURLStateBusy;
    retain();

    curl_easy_setopt(_curl, CURLOPT_HTTP_CONTENT_DECODING, 1);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, writeDataCURL);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, this);
    curl_easy_setopt(_curl, CURLOPT_HEADERFUNCTION, writeHeaderCURL);
    curl_easy_setopt(_curl, CURLOPT_WRITEHEADER, this);
    curl_easy_setopt(_curl, CURLOPT_NOPROGRESS, false);
    curl_easy_setopt(_curl, CURLOPT_PROGRESSFUNCTION, progressCURL);
    curl_easy_setopt(_curl, CURLOPT_PROGRESSDATA, this);
    curl_easy_setopt(_curl, CURLOPT_COOKIEFILE, "");

#ifdef _WINDOWS_

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	std::thread worker(requestCURL, this);
	worker.detach();

#else
    CreateThread(NULL,          // default security attributes
                 0,             // use default stack size
                 requestCURL,   // thread function name
                 this,          // argument to thread function
                 0,             // use default creation flags
                 NULL);
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_WP8

#else
    pthread_create(&_thread, NULL, requestCURL, this);
    pthread_detach(_thread);
#endif

    Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
    // CCLOG("HTTPRequest[0x%04x] - request start", s_id);
    return true;
}

void HTTPRequest::cancel(void)
{
    _delegate = NULL;
    if (_state == kCCHTTPRequestStateIdle || _state == kCCHTTPRequestStateInProgress)
    {
        _state = kCCHTTPRequestStateCancelled;
    }
}

int HTTPRequest::getState(void)
{
    return _state;
}

int HTTPRequest::getResponseStatusCode(void)
{
    CCAssert(_state == kCCHTTPRequestStateCompleted, "Request not completed");
    return _responseCode;
}

const HTTPRequestHeaders &HTTPRequest::getResponseHeaders(void)
{
    CCAssert(_state == kCCHTTPRequestStateCompleted, "HTTPRequest::getResponseHeaders() - request not completed");
    return _responseHeaders;
}

const string HTTPRequest::getResponseHeadersString()
{
    string buf;
    for (HTTPRequestHeadersIterator it = _responseHeaders.begin(); it != _responseHeaders.end(); ++it)
    {
        buf.append(*it);
    }
    return buf;
}

const string HTTPRequest::getResponseString(void)
{
    CCAssert(_state == kCCHTTPRequestStateCompleted, "HTTPRequest::getResponseString() - request not completed");
    return string(_responseBuffer ? static_cast<char*>(_responseBuffer) : "");
}

void *HTTPRequest::getResponseData(void)
{
    CCAssert(_state == kCCHTTPRequestStateCompleted, "HTTPRequest::getResponseData() - request not completed");
    void *buff = malloc(_responseDataLength);
    memcpy(buff, _responseBuffer, _responseDataLength);
    return buff;
}

#if CC_LUA_ENGINE_ENABLED > 0
LUA_STRING HTTPRequest::getResponseDataLua(void)
{
    CCAssert(_state == kCCHTTPRequestStateCompleted, "HTTPRequest::getResponseDataLua() - request not completed");
    LuaStack *stack = LuaEngine::getInstance()->getLuaStack();
    stack->clean();
    stack->pushString(static_cast<char*>(_responseBuffer), (int)_responseDataLength);
    return 1;
}
#endif

int HTTPRequest::getResponseDataLength(void)
{
    CCAssert(_state == kCCHTTPRequestStateCompleted, "Request not completed");
    return (int)_responseDataLength;
}

size_t HTTPRequest::saveResponseData(const char *filename)
{
    CCAssert(_state == kCCHTTPRequestStateCompleted, "HTTPRequest::saveResponseData() - request not completed");
    
    FILE *fp = fopen(filename, "wb");
    CCAssert(fp, "HTTPRequest::saveResponseData() - open file failure");
    
    size_t writedBytes = _responseDataLength;
    if (writedBytes > 0)
    {
        fwrite(_responseBuffer, _responseDataLength, 1, fp);
    }
    fclose(fp);
    return writedBytes;
}

int HTTPRequest::getErrorCode(void)
{
    return _errorCode;
}

const string HTTPRequest::getErrorMessage(void)
{
    return _errorMessage;
}

HTTPRequestDelegate* HTTPRequest::getDelegate(void)
{
    return _delegate;
}

void HTTPRequest::checkCURLState(float dt)
{
    CC_UNUSED_PARAM(dt);
    if (_curlState != kCCHTTPRequestCURLStateBusy)
    {
        Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
        release();
    }
}

void HTTPRequest::update(float dt)
{
    if (_state == kCCHTTPRequestStateInProgress)
    {
#if CC_LUA_ENGINE_ENABLED > 0
        if (_listener)
        {
            LuaValueDict dict;
            
            dict["name"] = LuaValue::stringValue("progress");
            dict["total"] = LuaValue::intValue((int)_dltotal);
            dict["dltotal"] = LuaValue::intValue((int)_dlnow);
            dict["request"] = LuaValue::ccobjectValue(this, "HTTPRequest");
            
            LuaStack *stack = LuaEngine::getInstance()->getLuaStack();
            stack->clean();
            stack->pushLuaValueDict(dict);
            stack->executeFunctionByHandler(_listener, 1);
        }
#endif
        return;
    }
    
    Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
    if (_curlState != kCCHTTPRequestCURLStateIdle)
    {
        Director::getInstance()->getScheduler()->schedule(schedule_selector(HTTPRequest::checkCURLState), this, 0, false);
    }

    if (_state == kCCHTTPRequestStateCompleted)
    {
        // CCLOG("HTTPRequest[0x%04x] - request completed", s_id);
        if (_delegate) _delegate->requestFinished(this);
    }
    else
    {
        // CCLOG("HTTPRequest[0x%04x] - request failed", s_id);
        if (_delegate) _delegate->requestFailed(this);
    }

#if CC_LUA_ENGINE_ENABLED > 0
    if (_listener)
    {
        LuaValueDict dict;

        switch (_state)
        {
            case kCCHTTPRequestStateCompleted:
                dict["name"] = LuaValue::stringValue("completed");
                break;
                
            case kCCHTTPRequestStateCancelled:
                dict["name"] = LuaValue::stringValue("cancelled");
                break;
                
            case kCCHTTPRequestStateFailed:
                dict["name"] = LuaValue::stringValue("failed");
                break;
                
            default:
                dict["name"] = LuaValue::stringValue("unknown");
        }
        dict["request"] = LuaValue::ccobjectValue(this, "HTTPRequest");
        LuaStack *stack = LuaEngine::getInstance()->getLuaStack();
        stack->clean();
        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(_listener, 1);
    }
#endif
}

// instance callback

void HTTPRequest::onRequest(void)
{
    if (_postFields.size() > 0)
    {
        curl_easy_setopt(_curl, CURLOPT_POST, 1L);
        stringbuf buf;
        for (Fields::iterator it = _postFields.begin(); it != _postFields.end(); ++it)
        {
            char *part = curl_easy_escape(_curl, it->first.c_str(), 0);
            buf.sputn(part, strlen(part));
            buf.sputc('=');
            curl_free(part);
            
            part = curl_easy_escape(_curl, it->second.c_str(), 0);
            buf.sputn(part, strlen(part));
            curl_free(part);
            
            buf.sputc('&');
        }
        curl_easy_setopt(_curl, CURLOPT_COPYPOSTFIELDS, buf.str().c_str());
    }

    struct curl_slist *chunk = NULL;
    for (HTTPRequestHeadersIterator it = _headers.begin(); it != _headers.end(); ++it)
    {
        chunk = curl_slist_append(chunk, (*it).c_str());
    }

	if (_formPost)
	{
		curl_easy_setopt(_curl, CURLOPT_HTTPPOST, _formPost);
	}

    curl_slist *cookies = NULL;
    curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, chunk);
    CURLcode code = curl_easy_perform(_curl);
    curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, &_responseCode);
    curl_easy_getinfo(_curl, CURLINFO_COOKIELIST, &cookies);

    if (cookies)
    {
        struct curl_slist *nc = cookies;
        stringbuf buf;
        while (nc)
        {
            buf.sputn(nc->data, strlen(nc->data));
            buf.sputc('\n');
            nc = nc->next;
        }
        _responseCookies = buf.str();
        curl_slist_free_all(cookies);
        cookies = NULL;
    }

    curl_easy_cleanup(_curl);
    _curl = NULL;
	if (_formPost)
	{
		curl_formfree(_formPost);
		_formPost = NULL;
	}
    curl_slist_free_all(chunk);
    
    _errorCode = code;
    _errorMessage = (code == CURLE_OK) ? "" : curl_easy_strerror(code);
    _state = (code == CURLE_OK) ? kCCHTTPRequestStateCompleted : kCCHTTPRequestStateFailed;
    _curlState = kCCHTTPRequestCURLStateClosed;
}

size_t HTTPRequest::onWriteData(void *buffer, size_t bytes)
{
    if (_responseDataLength + bytes + 1 > _responseBufferLength)
    {
        _responseBufferLength += BUFFER_CHUNK_SIZE;
        _responseBuffer = realloc(_responseBuffer, _responseBufferLength);
    }

    memcpy(static_cast<char*>(_responseBuffer) + _responseDataLength, buffer, bytes);
    _responseDataLength += bytes;
    static_cast<char*>(_responseBuffer)[_responseDataLength] = 0;
    return bytes;
}

size_t HTTPRequest::onWriteHeader(void *buffer, size_t bytes)
{
    char *headerBuffer = new char[bytes + 1];
    headerBuffer[bytes] = 0;
    memcpy(headerBuffer, buffer, bytes);    
    _responseHeaders.push_back(string(headerBuffer));
    delete []headerBuffer;
    return bytes;
}

int HTTPRequest::onProgress(double dltotal, double dlnow, double ultotal, double ulnow)
{
    _dltotal = dltotal;
    _dlnow = dlnow;
    _ultotal = ultotal;
    _ulnow = ulnow;
    
    return _state == kCCHTTPRequestStateCancelled ? 1: 0;
}

void HTTPRequest::cleanup(void)
{
    _state = kCCHTTPRequestStateCleared;
    _responseBufferLength = 0;
    _responseDataLength = 0;
    if (_responseBuffer)
    {
        free(_responseBuffer);
        _responseBuffer = NULL;
    }
    if (_curl)
    {
        curl_easy_cleanup(_curl);
        _curl = NULL;
    }
}

// curl callback

#ifdef _WINDOWS_
DWORD WINAPI HTTPRequest::requestCURL(LPVOID userdata)
{
    static_cast<HTTPRequest*>(userdata)->onRequest();
    return 0;
}
#else // _WINDOWS_
void *HTTPRequest::requestCURL(void *userdata)
{
    static_cast<HTTPRequest*>(userdata)->onRequest();
    return NULL;
}
#endif // _WINDOWS_

size_t HTTPRequest::writeDataCURL(void *buffer, size_t size, size_t nmemb, void *userdata)
{
    return static_cast<HTTPRequest*>(userdata)->onWriteData(buffer, size *nmemb);
}

size_t HTTPRequest::writeHeaderCURL(void *buffer, size_t size, size_t nmemb, void *userdata)
{
    return static_cast<HTTPRequest*>(userdata)->onWriteHeader(buffer, size *nmemb);
}

int HTTPRequest::progressCURL(void *userdata, double dltotal, double dlnow, double ultotal, double ulnow)
{
    return static_cast<HTTPRequest*>(userdata)->onProgress(dltotal, dlnow, ultotal, ulnow);
}

NS_CC_EXTRA_END
