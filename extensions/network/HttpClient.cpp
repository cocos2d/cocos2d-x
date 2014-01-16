/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 greathqy
 Copyright (c) 2013-2014 Martell Malone < martell malone at g mail dot com >
 
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

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
#include <queue>
#include <pthread.h>
#include <errno.h>
#include "curl/curl.h"
#else
#include <queue>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <errno.h>
#include "cocos2d.h"
#include <wrl.h>
#include <wrl/implements.h>
#include <Msxml6.h>
#include <ppltasks.h>
#include <sstream>
#include <robuffer.h>


using namespace concurrency;
using namespace Microsoft::WRL;
using namespace Platform;
using namespace std;
using namespace Windows::Foundation;
using namespace Windows::Storage::Streams;

using namespace Windows::Networking::Connectivity;

class HttpRequestStringCallback 
    : public Microsoft::WRL::RuntimeClass<RuntimeClassFlags<ClassicCom>, IXMLHTTPRequest2Callback, FtmBase>
{
public:
    HttpRequestStringCallback(IXMLHTTPRequest2* httpRequest, 
        cancellation_token ct = concurrency::cancellation_token::none()) :
        request(httpRequest), cancellationToken(ct)
    {
        if (cancellationToken != cancellation_token::none())
        {
            registrationToken = cancellationToken.register_callback([this]() 
            {
                if (request != nullptr) 
                {
                    request->Abort();
                }
            });
        }
    }

    IFACEMETHODIMP OnRedirect(IXMLHTTPRequest2* hell, PCWSTR bla) 
    {
        redirecturl = bla;
        return S_OK;
    }

    IFACEMETHODIMP OnHeadersAvailable(IXMLHTTPRequest2*, DWORD statusCode, PCWSTR reasonPhrase)
    {
        HRESULT hr = S_OK;

        try
        {
            this->statusCode = statusCode;
            this->reasonPhrase = reasonPhrase;
        }
        catch (std::bad_alloc&)
        {
            hr = E_OUTOFMEMORY;
        }

        return hr;
    }

    IFACEMETHODIMP OnDataAvailable(IXMLHTTPRequest2*, ISequentialStream*)
    {
        return S_OK;
    }

    IFACEMETHODIMP OnResponseReceived(IXMLHTTPRequest2 *request, ISequentialStream *pResponseStream)
    {
        HRESULT hr = S_OK;
        std::string str;
        std::stringbuf buf;
        char buffer[4096] = {0};
        ULONG cb = 0;

        while (true)
        {
            hr = pResponseStream->Read(buffer, sizeof(buffer) - 1, &cb);
            if (FAILED(hr) || cb == 0)
            {
                break;
            }

            buf.sputn(buffer, cb);
        }

        if (cb > 0)
            buf.sputn(buffer, cb);

        buf.sputn("\0", 1);
        str = buf.str();

        try
        {
            completionEvent.set(std::make_tuple<HRESULT, std::string>(std::move(hr), std::move(str)));
        }
        catch (std::bad_alloc&)
        {
            return E_OUTOFMEMORY;
        }

        return S_OK;
    }

    IFACEMETHODIMP OnError(IXMLHTTPRequest2*, HRESULT hrError) 
    {
        HRESULT hr = S_OK;

        try
        {
            completionEvent.set(make_tuple<HRESULT, string>(move(hrError), string()));
        }
        catch (std::bad_alloc&)
        {
            hr = E_OUTOFMEMORY;
        }

        return hr;
    }

    task_completion_event<tuple<HRESULT, string>> const& GetCompletionEvent() const
    {
        return completionEvent; 
    }

    int GetStatusCode() const
    {
        return statusCode;
    }

    wstring GetReasonPhrase() const
    {
        return reasonPhrase;
    }

    wstring GetRedirectURL() const
    {
        return redirecturl;
    }

private:
    ~HttpRequestStringCallback()
    {
        if (cancellationToken != cancellation_token::none())
        {
            cancellationToken.deregister_callback(registrationToken);
        }
    }

    cancellation_token cancellationToken;
    cancellation_token_registration registrationToken;
    ComPtr<IXMLHTTPRequest2> request;
    task_completion_event<tuple<HRESULT, string>> completionEvent;
    int statusCode;
    wstring reasonPhrase;
    wstring redirecturl;
};
#endif

NS_CC_EXT_BEGIN

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
static pthread_t        s_networkThread;

static pthread_mutex_t  s_requestQueueMutex;
static pthread_mutex_t  s_responseQueueMutex;
static pthread_mutex_t		s_SleepMutex;
static pthread_cond_t		s_SleepCondition;

static char s_errorBuffer[CURL_ERROR_SIZE];

#else
static std::mutex  s_requestQueueMutex;
static std::mutex  s_responseQueueMutex;
static std::mutex  s_SleepMutex;
static std::condition_variable  s_SleepCondition;

const wchar_t *s_errorBuffer;
#endif

typedef size_t (*write_callback)(void *ptr, size_t size, size_t nmemb, void *stream);
static unsigned long    s_asyncRequestCount = 0;

#if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8))
typedef int int32_t;
#endif

static bool need_quit = false;
static CCArray* s_requestQueue = NULL;
static CCArray* s_responseQueue = NULL;
static CCHttpClient *s_pHttpClient = NULL; // pointer to singleton

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

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
static int processGetTask(CCHttpRequest *request, write_callback callback, void *stream, int32_t *errorCode, write_callback headerCallback, void *headerStream);
static int processPostTask(CCHttpRequest *request, write_callback callback, void *stream, int32_t *errorCode, write_callback headerCallback, void *headerStream);
static int processPutTask(CCHttpRequest *request, write_callback callback, void *stream, int32_t *errorCode, write_callback headerCallback, void *headerStream);
static int processDeleteTask(CCHttpRequest *request, write_callback callback, void *stream, int32_t *errorCode, write_callback headerCallback, void *headerStream);
#else
int processHttpTask(CCHttpRequest *request, write_callback callback, void *stream, int32_t *errorCode,write_callback headerCallback, void *headerStream);
#endif

// Worker thread



#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
static void* networkThread(void *data)
#else
static void networkThread()
#endif
{    
    CCHttpRequest *request = NULL;

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	std::unique_lock<std::mutex> lk(s_SleepMutex);
	#endif

    while (true) 
    {
        if (need_quit)
        {
            break;
        }
        
        // step 1: send http request if the requestQueue isn't empty
        request = NULL;
        
		#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
        pthread_mutex_lock(&s_requestQueueMutex); //Get request task from queue
		#else
		s_requestQueueMutex.lock();
		#endif
        if (0 != s_requestQueue->count())
        {
            request = dynamic_cast<CCHttpRequest*>(s_requestQueue->objectAtIndex(0));
            s_requestQueue->removeObjectAtIndex(0);  
            // request's refcount = 1 here
        }
		#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
        pthread_mutex_unlock(&s_requestQueueMutex);
		#else
		s_requestQueueMutex.unlock();
		#endif
        
        
        if (NULL == request)
        {
        	// Wait for http request tasks from main thread
			#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
			pthread_cond_wait(&s_SleepCondition, &s_SleepMutex);
			#else
			s_SleepCondition.wait(lk);
			#endif
            continue;
        }
        
        // step 2: libcurl sync access
        
        // Create a HttpResponse object, the default setting is http access failed
        CCHttpResponse *response = new CCHttpResponse(request);
        
        // request's refcount = 2 here, it's retained by HttpRespose constructor
        request->release();
        // ok, refcount = 1 now, only HttpResponse hold it.
        
        int32_t responseCode = -1;
        int retValue = 0;

        // Process the request -> get response packet
		#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
        switch (request->getRequestType())
        {
			
            case CCHttpRequest::kHttpGet: // HTTP GET
                retValue = processGetTask(request,
                                          writeData, 
                                          response->getResponseData(), 
                                          &responseCode,
                                          writeHeaderData,
                                          response->getResponseHeader());
                break;
            
            case CCHttpRequest::kHttpPost: // HTTP POST
                retValue = processPostTask(request,
                                           writeData, 
                                           response->getResponseData(), 
                                           &responseCode,
                                           writeHeaderData,
                                           response->getResponseHeader());
                break;

            case CCHttpRequest::kHttpPut:
                retValue = processPutTask(request,
                                          writeData,
                                          response->getResponseData(),
                                          &responseCode,
                                          writeHeaderData,
                                          response->getResponseHeader());
                break;

            case CCHttpRequest::kHttpDelete:
                retValue = processDeleteTask(request,
                                             writeData,
                                             response->getResponseData(),
                                             &responseCode,
                                             writeHeaderData,
                                             response->getResponseHeader());
                break;
            
            default:
                CCAssert(true, "CCHttpClient: unkown request type, only GET and POSt are supported");
                break;

        }
		#else
        retValue = processHttpTask(request,
                                   writeData,
                                   response->getResponseData(),
                                   &responseCode,
                                   writeHeaderData,
                                   response->getResponseHeader());   
		#endif

        // write data to HttpResponse
        response->setResponseCode(responseCode);
        
        if (retValue != 0) 
        {
            response->setSucceed(false);
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
			response->setErrorBuffer(s_errorBuffer);
#endif //must fix for winrt and wp8
        }
        else
        {
            response->setSucceed(true);
        }

        
        // add response packet into queue
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
		pthread_mutex_lock(&s_responseQueueMutex);
#else
		s_responseQueueMutex.lock();
#endif
		s_responseQueue->addObject(response);
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
		pthread_mutex_unlock(&s_responseQueueMutex);
#else
		s_responseQueueMutex.unlock();
#endif

        // resume dispatcher selector
        CCDirector::sharedDirector()->getScheduler()->resumeTarget(CCHttpClient::getInstance());
    }
    
    // cleanup: if worker thread received quit signal, clean up un-completed request queue
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
	pthread_mutex_lock(&s_requestQueueMutex);
#else
	s_requestQueueMutex.lock();
#endif
    s_requestQueue->removeAllObjects();
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
    pthread_mutex_unlock(&s_requestQueueMutex);
#else
	s_requestQueueMutex.lock();
#endif
	s_asyncRequestCount -= s_requestQueue->count();
    
    if (s_requestQueue != NULL) {
        
		#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
        pthread_mutex_destroy(&s_requestQueueMutex);
        pthread_mutex_destroy(&s_responseQueueMutex);
        
        pthread_mutex_destroy(&s_SleepMutex);
        pthread_cond_destroy(&s_SleepCondition);
		#endif

        s_requestQueue->release();
        s_requestQueue = NULL;
        s_responseQueue->release();
        s_responseQueue = NULL;
    }

	#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
    pthread_exit(NULL);
	return 0;
	#endif
    
}

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
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
    code = curl_easy_setopt(handle, CURLOPT_TIMEOUT, CCHttpClient::getInstance()->getTimeoutForRead());
    if (code != CURLE_OK) {
        return false;
    }
    code = curl_easy_setopt(handle, CURLOPT_CONNECTTIMEOUT, CCHttpClient::getInstance()->getTimeoutForConnect());
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

class CURLRaii
{
    /// Instance of CURL
    CURL *m_curl;
    /// Keeps custom header data
    curl_slist *m_headers;
public:
    CURLRaii()
        : m_curl(curl_easy_init())
        , m_headers(NULL)
    {
    }

    ~CURLRaii()
    {
        if (m_curl)
            curl_easy_cleanup(m_curl);
        /* free the linked list for header data */
        if (m_headers)
            curl_slist_free_all(m_headers);
    }

    template <class T>
    bool setOption(CURLoption option, T data)
    {
        return CURLE_OK == curl_easy_setopt(m_curl, option, data);
    }

    /**
     * @brief Inits CURL instance for common usage
     * @param request Null not allowed
     * @param callback Response write callback
     * @param stream Response write stream
     */
    bool init(CCHttpRequest *request, write_callback callback, void *stream, write_callback headerCallback, void *headerStream)
    {
        if (!m_curl)
            return false;
        if (!configureCURL(m_curl))
            return false;

        /* get custom header data (if set) */
       	std::vector<std::string> headers=request->getHeaders();
        if(!headers.empty())
        {
            /* append custom headers one by one */
            for (std::vector<std::string>::iterator it = headers.begin(); it != headers.end(); ++it)
                m_headers = curl_slist_append(m_headers,it->c_str());
            /* set custom headers for curl */
            if (!setOption(CURLOPT_HTTPHEADER, m_headers))
                return false;
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
        if (CURLE_OK != curl_easy_perform(m_curl))
            return false;
        CURLcode code = curl_easy_getinfo(m_curl, CURLINFO_RESPONSE_CODE, responseCode);
        if (code != CURLE_OK || *responseCode != 200)
            return false;
        
        // Get some mor data.
        
        return true;
    }
};

//Process Get Request
static int processGetTask(CCHttpRequest *request, write_callback callback, void *stream, int32_t *responseCode, write_callback headerCallback, void *headerStream)
{
    CURLRaii curl;
    bool ok = curl.init(request, callback, stream, headerCallback, headerStream)
            && curl.setOption(CURLOPT_FOLLOWLOCATION, true)
            && curl.perform(responseCode);
    return ok ? 0 : 1;
}

//Process POST Request
static int processPostTask(CCHttpRequest *request, write_callback callback, void *stream, int32_t *responseCode, write_callback headerCallback, void *headerStream)
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
static int processPutTask(CCHttpRequest *request, write_callback callback, void *stream, int32_t *responseCode, write_callback headerCallback, void *headerStream)
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
static int processDeleteTask(CCHttpRequest *request, write_callback callback, void *stream, int32_t *responseCode, write_callback headerCallback, void *headerStream)
{
    CURLRaii curl;
    bool ok = curl.init(request, callback, stream, headerCallback, headerStream)
            && curl.setOption(CURLOPT_CUSTOMREQUEST, "DELETE")
            && curl.setOption(CURLOPT_FOLLOWLOCATION, true)
            && curl.perform(responseCode);
    return ok ? 0 : 1;
}

#else


//Process HTTP Task
int processHttpTask(CCHttpRequest *request, write_callback callback, void *stream, int32_t *responseCode, write_callback headerCallback, void *headerStream)
{
    // Create an IXMLHTTPRequest2 object.
    IXMLHTTPRequest2  *xhr;
    HRESULT res = CoCreateInstance(CLSID_XmlHttpRequest, nullptr, CLSCTX_INPROC, IID_PPV_ARGS(&xhr));
    if(res != 0) return -1;
    concurrency::cancellation_token cancellationToken = concurrency::cancellation_token::none();
    int length = 0;

    IStream *postStream;
    IStream **ppostStream = &postStream;
    res = CreateStreamOnHGlobal(NULL, TRUE, &postStream);

    if(res != 0) return -1;

    auto stringCallback = Make<HttpRequestStringCallback>(xhr, cancellationToken);
    auto completionTask = create_task(stringCallback->GetCompletionEvent());
    
    string url = string(request->getUrl());
    wstring wurl = wstring(url.begin(),url.end());
    ULONG written= 0;
	PCWSTR requestType = L"UNKNOWN";
    
	if(request->getRequestType() == CCHttpRequest::kHttpPost)
	  {
		requestType = L"POST";
		string srd = string(request->getRequestData(),request->getRequestDataSize());
        postStream->Write(srd.c_str(), srd.length(), &written);
    }
    else if(request->getRequestType() == CCHttpRequest::kHttpGet) requestType = L"GET";
    
    res = CoCreateInstance(CLSID_XmlHttpRequest, nullptr, CLSCTX_INPROC, IID_PPV_ARGS(&xhr));
    if (res != 0) return -1;

    std::vector<std::string> headers=request->getHeaders();

    res = xhr->Open(requestType, wurl.c_str(), stringCallback.Get(), nullptr, nullptr, nullptr, nullptr);

   	if(headers.size() != 0)
	    for(std::vector<std::string>::iterator it = headers.begin(); it != headers.end(); ++it)  {

			wstring head = wstring(it->begin(), it->end());
			std::wstring delimiter = L":";
			size_t pos = 0;

			pos = head.find(delimiter);
			std::wstring left = head.substr(0, pos); // token is all left of ":"
			head.erase(0, pos + delimiter.length());

			res = xhr->SetRequestHeader(left.c_str(), head.c_str());

		}

    res = xhr->Send(postStream, length);

    auto t = completionTask.then([&, stringCallback](tuple<HRESULT, string> resultTuple)
    {
        if(S_FALSE == std::get<0>(resultTuple))
        {

        *responseCode = stringCallback->GetStatusCode();

        WCHAR *pwszHeaderValue = NULL;
        xhr->GetAllResponseHeaders(&pwszHeaderValue);

        wstring head = wstring(pwszHeaderValue);

        *(std::vector<char>*)headerStream = std::vector<char>(head.begin(), head.end());
        *(std::vector<char>*)stream = std::vector<char>(std::get<1>(resultTuple).begin(),std::get<1>(resultTuple).end());

        }
        else
        {
            *responseCode = -1;
            *(std::vector<char>*)headerStream = std::vector<char>();
            *(std::vector<char>*)stream = std::vector<char>();
        }

    });
    
    t.wait();
    return 0;
}

#endif
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
    CCAssert(s_pHttpClient, "");
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(CCHttpClient::dispatchResponseCallbacks), s_pHttpClient);
    s_pHttpClient->release();
}

CCHttpClient::CCHttpClient()
: _timeoutForConnect(30)
, _timeoutForRead(60)
{
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(
                    schedule_selector(CCHttpClient::dispatchResponseCallbacks), this, 0, false);
    CCDirector::sharedDirector()->getScheduler()->pauseTarget(this);
}

CCHttpClient::~CCHttpClient()
{
    need_quit = true;
    
    if (s_requestQueue != NULL) {

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
    	pthread_cond_signal(&s_SleepCondition);
#else
		s_SleepCondition.notify_all();
#endif
    }
    
    s_pHttpClient = NULL;
}

//Lazy create semaphore & mutex & thread
bool CCHttpClient::lazyInitThreadSemphore()
{
    if (s_requestQueue != NULL) {
        return true;
    } else {
        
        s_requestQueue = new CCArray();
        s_requestQueue->init();
        
        s_responseQueue = new CCArray();
        s_responseQueue->init();

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
        
        pthread_mutex_init(&s_requestQueueMutex, NULL);
        pthread_mutex_init(&s_responseQueueMutex, NULL);
        
        pthread_mutex_init(&s_SleepMutex, NULL);
        pthread_cond_init(&s_SleepCondition, NULL);

        pthread_create(&s_networkThread, NULL, networkThread, NULL);
        pthread_detach(s_networkThread);

#else

		std::thread s_networkThread(networkThread);
        s_networkThread.detach();
#endif

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

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
    pthread_mutex_lock(&s_requestQueueMutex);
#else
	s_requestQueueMutex.lock();
#endif

	s_requestQueue->addObject(request);

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
    pthread_mutex_unlock(&s_requestQueueMutex);
#else
	s_requestQueueMutex.unlock();
#endif

	// Notify thread start to work
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
    pthread_cond_signal(&s_SleepCondition);
#else
    s_SleepCondition.notify_one();
#endif
}

// Poll and notify main thread if responses exists in queue
void CCHttpClient::dispatchResponseCallbacks(float delta)
{
    // CCLog("CCHttpClient::dispatchResponseCallbacks is running");
    
    CCHttpResponse* response = NULL;

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
    pthread_mutex_lock(&s_responseQueueMutex);
#else
	s_responseQueueMutex.lock();
#endif
	if (s_responseQueue->count())
    {
        response = dynamic_cast<CCHttpResponse*>(s_responseQueue->objectAtIndex(0));
        s_responseQueue->removeObjectAtIndex(0);
    }

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
	pthread_mutex_unlock(&s_responseQueueMutex);
#else
	s_responseQueueMutex.unlock();
#endif

	if (response)
    {
        --s_asyncRequestCount;
        
        CCHttpRequest *request = response->getHttpRequest();
        CCObject *pTarget = request->getTarget();
        SEL_HttpResponse pSelector = request->getSelector();

        if (pTarget && pSelector) 
        {
            (pTarget->*pSelector)(this, response);
        }
        
        response->release();
    }
    
    if (0 == s_asyncRequestCount) 
    {
        CCDirector::sharedDirector()->getScheduler()->pauseTarget(this);
    }
    
}

//check if Internet's connected
/*
int CCHttpClient::IsInternetConnected()
{
    int result = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    /*LPDWORD x;
    bool thing = (bool)InternetGetConnectedState(x, 0);
    if(thing)
    {
        result = true;
    }*//*
    result = 1;
#elif  (CC_TARGET_PLATFORM == CC_PLATFORM_WIN8_METRO)
    Windows::Foundation::Collections::IVectorView<ConnectionProfile^>^ connectionProfiles = Windows::Networking::Connectivity::NetworkInformation::GetConnectionProfiles();
    if (connectionProfiles->Size != 0)
    {
        for (int i = 0; i < connectionProfiles->Size; i++)
        {
            if(connectionProfiles->GetAt(i)->GetNetworkConnectivityLevel() == NetworkConnectivityLevel::InternetAccess)
            {
                result = 1;

                //Platform::IBox<unsigned int> ^ emptylimit;// = Platform::IBox<unsigned int>0;
                //Platform::String ^ vall = connectionProfiles->GetAt(i)->GetDataPlanStatus()->MaxTransferSizeInMegabytes->ToString();

                ConnectionCost ^cost = connectionProfiles->GetAt(i)->GetConnectionCost();


                Platform::String ^ vall = cost->NetworkCostType.ToString();
                //int he = 20;
                std::wstring wvall = std::wstring(vall->Begin(),vall->Length());
                std::string *cvall = new std::string(wvall.begin(),wvall.end());
                

                
                if (cvall->compare("Unrestricted"))
                    {
                        result = 2;
                    }
            
                // Maximum transfer size is limited
                // Suspend transfers exceeding the size and warn the user
            
            }
        }
    }
#elif  (CC_TARGET_PLATFORM == CC_PLATFORM_WINPHONE)
result = 1;

#endif
    return result;
}
*/

NS_CC_EXT_END




