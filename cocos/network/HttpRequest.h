/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#include <string>
#include <vector>
#include "base/CCRef.h"
#include "base/ccMacros.h"

/**
 * @addtogroup network
 * @{
 */

NS_CC_BEGIN

namespace network {

class HttpClient;
class HttpResponse;

typedef std::function<void(HttpClient* client, HttpResponse* response)> ccHttpRequestCallback;
typedef void (cocos2d::Ref::*SEL_HttpResponse)(HttpClient* client, HttpResponse* response);
#define httpresponse_selector(_SELECTOR) (cocos2d::network::SEL_HttpResponse)(&_SELECTOR)

/**
 * Defines the object which users must packed for HttpClient::send(HttpRequest*) method.
 * Please refer to tests/test-cpp/Classes/ExtensionTest/NetworkTest/HttpClientTest.cpp as a sample
 * @since v2.0.2
 *
 * @lua NA
 */

class CC_DLL HttpRequest : public Ref
{
public:
    /**
     * The HttpRequest type enum used in the HttpRequest::setRequestType.
     */
    enum class Type
    {
        GET,
        POST,
        PUT,
        DELETE,
        UNKNOWN,
    };

    /**
     *  Constructor.
     *   Because HttpRequest object will be used between UI thread and network thread,
         requestObj->autorelease() is forbidden to avoid crashes in AutoreleasePool
         new/retain/release still works, which means you need to release it manually
         Please refer to HttpRequestTest.cpp to find its usage.
     */
    HttpRequest()
        : _requestType(Type::UNKNOWN)
        , _pTarget(nullptr)
        , _pSelector(nullptr)
        , _pCallback(nullptr)
        , _pUserData(nullptr)
    {
    }

    /** Destructor. */
    virtual ~HttpRequest()
    {
        if (_pTarget)
        {
            _pTarget->release();
        }
    }

    /**
     * Override autorelease method to avoid developers to call it.
     * If this function was called, it would trigger assert in debug mode
     *
     * @return Ref* always return nullptr.
     */
    Ref* autorelease()
    {
        CCASSERT(false, "HttpResponse is used between network thread and ui thread \
                 therefore, autorelease is forbidden here");
        return nullptr;
    }

    // setter/getters for properties

    /**
     * Set request type of HttpRequest object before being sent,now it support the enum value of HttpRequest::Type.
     *
     * @param type the request type.
     */
    void setRequestType(Type type)
    {
        _requestType = type;
    }

    /**
     * Get the request type of HttpRequest object.
     *
     * @return HttpRequest::Type.
     */
    Type getRequestType() const
    {
        return _requestType;
    }

    /**
     * Set the url address of HttpRequest object.
     * The url value could be like these: "http://httpbin.org/ip" or "https://httpbin.org/get"
     *
     * @param url the string object.
     */
    void setUrl(const std::string& url)
    {
        _url = url;
    }

    /**
     * Get the url address of HttpRequest object.
     *
     * @return const char* the pointer of _url.
     */
    const char* getUrl() const
    {
        return _url.c_str();
    }

    /**
     * Set the request data of HttpRequest object.
     *
     * @param buffer the buffer of request data, it support binary data.
     * @param len    the size of request data.
     */
    void setRequestData(const char* buffer, size_t len)
    {
        _requestData.assign(buffer, buffer + len);
    }

    /**
     * Get the request data pointer of HttpRequest object.
     *
     * @return char* the request data pointer.
     */
    char* getRequestData()
    {
        if(!_requestData.empty())
            return _requestData.data();

        return nullptr;
    }

    /**
     * Get the size of request data
     *
     * @return ssize_t the size of request data
     */
    ssize_t getRequestDataSize() const
    {
        return _requestData.size();
    }

    /**
     * Set a string tag to identify your request.
     * This tag can be found in HttpResponse->getHttpRequest->getTag().
     *
     * @param tag the string object.
     */
    void setTag(const std::string& tag)
    {
        _tag = tag;
    }

    /**
     * Get the string tag to identify the request.
     * The best practice is to use it in your MyClass::onMyHttpRequestCompleted(sender, HttpResponse*) callback.
     *
     * @return const char* the pointer of _tag
     */
    const char* getTag() const
    {
        return _tag.c_str();
    }

    /**
     * Set user-customed data of HttpRequest object.
     * You can attach a customed data in each request, and get it back in response callback.
     * But you need to new/delete the data pointer manually.
     *
     * @param pUserData the string pointer
     */
    void setUserData(void* pUserData)
    {
        _pUserData = pUserData;
    }

    /**
     * Get the user-customed data pointer which were pre-setted.
     * Don't forget to delete it. HttpClient/HttpResponse/HttpRequest will do nothing with this pointer.
     *
     * @return void* the pointer of user-customed data.
     */
    void* getUserData() const
    {
        return _pUserData;
    }
    
    /**
     * Set the target and related callback selector of HttpRequest object.
     * When response come back, we would call (pTarget->*pSelector) to process response data.
     *
     * @param pTarget the target object pointer.
     * @param pSelector the SEL_HttpResponse function.
     */
    void setResponseCallback(Ref* pTarget, SEL_HttpResponse pSelector)
    {
        doSetResponseCallback(pTarget, pSelector);
    }
    /**
     * Set response callback function of HttpRequest object.
     * When response come back, we would call _pCallback to process response data.
     *
     * @param callback the ccHttpRequestCallback function.
     */
    void setResponseCallback(const ccHttpRequestCallback& callback)
    {
        _pCallback = callback;
    }
    
    /** 
     * Get the target of callback selector function, mainly used by HttpClient.
     *
     * @return Ref* the target of callback selector function
     */
    Ref* getTarget() const
    {
        return _pTarget;
    }

    /**
     * This sub class is just for migration SEL_CallFuncND to SEL_HttpResponse,someday this way will be removed.
     *
     * @lua NA
     */
    class _prxy
    {
    public:
        /** Constructor. */
        _prxy( SEL_HttpResponse cb ) :_cb(cb) {}
        /** Destructor. */
        ~_prxy(){};
        operator SEL_HttpResponse() const { return _cb; }
    protected:
        SEL_HttpResponse _cb;
    };

    /**
     * Get _prxy object by the _pSelector.
     *
     * @return _prxy the _prxy object
     */
    _prxy getSelector() const
    {
        return _prxy(_pSelector);
    }

    /**
     * Get ccHttpRequestCallback callback function.
     *
     * @return const ccHttpRequestCallback& ccHttpRequestCallback callback function.
     */
    const ccHttpRequestCallback& getCallback() const
    {
        return _pCallback;
    }

    /**
     * Set custom-defined headers.
     *
     * @param headers The string vector of custom-defined headers.
     */
    void setHeaders(const std::vector<std::string>& headers)
    {
        _headers = headers;
    }

    /**
     * Get custom headers.
     *
     * @return std::vector<std::string> the string vector of custom-defined headers.
     */
    std::vector<std::string> getHeaders() const
    {
        return _headers;
    }

private:
    void doSetResponseCallback(Ref* pTarget, SEL_HttpResponse pSelector)
    {
        if (_pTarget)
        {
            _pTarget->release();
        }
        
        _pTarget = pTarget;
        _pSelector = pSelector;
        if (_pTarget)
        {
            _pTarget->retain();
        }
    }

protected:
    // properties
    Type                        _requestType;    /// kHttpRequestGet, kHttpRequestPost or other enums
    std::string                 _url;            /// target url that this request is sent to
    std::vector<char>           _requestData;    /// used for POST
    std::string                 _tag;            /// user defined tag, to identify different requests in response callback
    Ref*                        _pTarget;        /// callback target of pSelector function
    SEL_HttpResponse            _pSelector;      /// callback function, e.g. MyLayer::onHttpResponse(HttpClient *sender, HttpResponse * response)
    ccHttpRequestCallback       _pCallback;      /// C++11 style callbacks
    void*                       _pUserData;      /// You can add your customed data here
    std::vector<std::string>    _headers;        /// custom http headers
};

}

NS_CC_END

// end group
/// @}

#endif //__HTTP_REQUEST_H__

