/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
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

/** @~english
 * Defines the object which users must packed for HttpClient::send(HttpRequest*) method.
 * @~chinese 
 * 一个请求数据封装类，用于HttpClient::send。
 * @see tests/test-cpp/Classes/ExtensionTest/NetworkTest/HttpClientTest.cpp
 * @since v2.0.2
 *
 * @lua NA
 */

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#ifdef DELETE
#undef DELETE
#endif
#endif

class CC_DLL HttpRequest : public Ref
{
public:
    /**@~english
     * The HttpRequest type enum used in the HttpRequest::setRequestType.
     * @~chinese 
     * HttpRequest枚举类，调用HttpRequest::setRequestType时用到。
     */
    enum class Type
    {
        GET,
        POST,
        PUT,
        DELETE,
        UNKNOWN,
    };
    
    /** @~english
     *  Constructor.
     *   Because HttpRequest object will be used between UI thead and network thread,
         requestObj->autorelease() is forbidden to avoid crashes in AutoreleasePool
         new/retain/release still works, which means you need to release it manually
     * @~chinese 
     * 构造函数。
     * 因为HttpRequest对象将会在UI线程和网络线程中使用，所以requestObj->autorelease()是被禁止的，这样可以避免AutoreleasePool中的崩溃。
     * new/retain/release还是有效，这意味着你需要手动的调用release函数。
     * @see httprequest.cpp。
     */
    HttpRequest()
    {
        _requestType = Type::UNKNOWN;
        _url.clear();
        _requestData.clear();
        _tag.clear();
        _pTarget = nullptr;
        _pSelector = nullptr;
        _pCallback = nullptr;
        _pUserData = nullptr;
    };
    
    /** @~english Destructor.  @~chinese 析构函数。*/
    virtual ~HttpRequest()
    {
        if (_pTarget)
        {
            _pTarget->release();
        }
    };
    
    /** @~english
     * Override autorelease method to avoid developers to call it.
     * If this function was called, it would trigger assert in debug mode
     *
     * @~chinese 
     * 重载autorelease函数避免开发者调用。
     * 如果这个函数被调用，在debug模式下将会触发assert
     * 
     * @return Ref* @~english always return nullptr.
     * @~chinese 始终返回nullptr。
     */
    Ref* autorelease(void)
    {
        CCASSERT(false, "HttpResponse is used between network thread and ui thread \
                 therefore, autorelease is forbidden here");
        return NULL;
    }
            
    // setter/getters for properties
     
    /** @~english
     * Set request type of HttpRequest object before being sent,now it support the enum value of HttpRequest::Type.
     *
     * @~chinese 
     * 在发送HttpRequest对象前，设置HttpRequest的类型值，它可以是HttpRequest::Type的枚举类型中的任意一个值。
     * 
     * @param type @~english the request type.
     * @~chinese 请求类型。
     */
    inline void setRequestType(Type type)
    {
        _requestType = type;
    };
    /** @~english
     * Get the request type of HttpRequest object.
     *
     * @~chinese 
     * 获取HttpRequest对象的请求类型。
     * 
     * @return @~english HttpRequest::Type.
     * @~chinese HttpRequest::Type。
     */
    inline Type getRequestType()
    {
        return _requestType;
    };
    
    /** @~english
     * Set the url address of HttpRequest object.
     * The url value could be like these: "http://httpbin.org/ip" or "https://httpbin.org/get"
     *
     * @~chinese
     * 设置HttpRequest对象的url。
     * url的值如下:“http://httpbin.org/ip”或“https://httpbin.org/get”
     * 
     * @param url @~english the string pointer to the url.
     * @~chinese url字符串指针。
     */
    inline void setUrl(const char* url)
    {
        _url = url;
    };
    /** @~english
     * Get the url address of HttpRequest object.
     *
     * @~chinese 
     * 获取HttpRequest对象的url字符串指针。
     * 
     * @return @~english const char* the pointer of _url.
     * @~chinese 指向url的字符串指针。
     */
    inline const char* getUrl()
    {
        return _url.c_str();
    };
    
    /** @~english
     * Set the request data of HttpRequest object.
     *
     * @~chinese 
     * 设置HttpRequest对象的请求数据。
     * 
     * @param buffer @~english the buffer of request data, it support binary data.
     * @~chinese 请求数据的缓存指针,它支持二进制数据。
     * @param len @~english the size of request data.
     * @~chinese 请求数据的大小。
     */
    inline void setRequestData(const char* buffer, size_t len)
    {
        _requestData.assign(buffer, buffer + len);
    };
    /** @~english
     * Get the request data pointer of HttpRequest object.
     *
     * @~chinese 
     * 获取HttpRequest对象请求数据的指针。
     * 
     * @return @~english char* the request data pointer.
     * @~chinese 指向请求数据的指针。
     */
    inline char* getRequestData()
    {
        if(_requestData.size() != 0)
            return &(_requestData.front());

        return nullptr;
    }
    /** @~english
     * Get the size of request data
     *
     * @~chinese 
     * 获得请求数据的大小
     * 
     * @return @~english ssize_t the size of request data
     * @~chinese 请求数据的大小
     */
    inline ssize_t getRequestDataSize()
    {
        return _requestData.size();
    }
    
    /** @~english
     * Set a string tag to identify your request.
     * This tag can be found in HttpResponse->getHttpRequest->getTag().
     *
     * @~chinese 
     * 设置字符串标签用于识别request。
     * 这个字符串标签可以通过HttpResponse->getHttpRequest->getTag()获得。
     * 
     * @param tag @~english the string pointer to tag
     * @~chinese 指向标签的字符串指针。
     */
    inline void setTag(const char* tag)
    {
        _tag = tag;
    };
    /** @~english
     * Get the string tag to identify the request.
     * The best practice is to use it in your MyClass::onMyHttpRequestCompleted(sender, HttpResponse*) callback.
     *
     * @~chinese 
     * 获取用于识别request的字符串标签。
     * 最佳的使用点是在MyClass::onMyHttpRequestCompleted(发送方,HttpResponse *)回调中使用。
     * 
     * @return @~english const char* the pointer of _tag
     * @~chinese 指向_tag的字符串指针
     */
    inline const char* getTag()
    {
        return _tag.c_str();
    };
    
    /**@~english
     * Set user-customed data of HttpRequest object.
     * You can attach a customed data in each request, and get it back in response callback.
     * But you need to new/delete the data pointer manully.
     *
     * @~chinese 
     * 设置HttpRequest对象的用户自定义数据。
     * 你可以在每一个request中附加一个自定义数据，然后在响应回调中取加这个数据。
     * 设置自定义数据，你需要手动地new/delete数据指针
     * 
     * @param pUserData @~english the pointer point to customed data
     * @~chinese 自定义数据指针
     */
    inline void setUserData(void* pUserData)
    {
        _pUserData = pUserData;
    };
    /** @~english
     * Get the user-customed data pointer which were pre-setted.
     * Don't forget to delete it. HttpClient/HttpResponse/HttpRequest will do nothing with this pointer.
     *
     * @~chinese 
     * 获取预设的用户自定义数据指针。
     * 不要忘记delete它。HttpClient、HttpResponse和HttpRequest都不会对这个指针进行处理。
     * 
     * @return @~english void* the pointer of user-customed data.
     * @~chinese 指向用户自定义数据的指针。
     */
    inline void* getUserData()
    {
        return _pUserData;
    };
    
    /**@~english
     * Set the target and related callback selector.
     * When response come back, it would call (pTarget->*pSelector) to process something.
     *
     * @~chinese 
     * 设置target和相关的回调函函数。
     * 当响应返回时,它将调用(pTarget->*pSelector)来处理一些事情。
     * 
     * @param pTarget @~english the target object pointer.
     * @~chinese 目标对象指针。
     * @param pSelector @~english the callback function.
     * @~chinese 回调函数。
     */
    CC_DEPRECATED_ATTRIBUTE inline void setResponseCallback(Ref* pTarget, SEL_CallFuncND pSelector)
    {
        setResponseCallback(pTarget, (SEL_HttpResponse) pSelector);
    }
    
    /**@~english
     * Set the target and related callback selector of HttpRequest object.
     * When response come back, we would call (pTarget->*pSelector) to process response data.
     *
     * @~chinese 
     * 设置target和相关回调函数。
     * 当响应返回时,我们将调用(pTarget->*pSelector)来处理响应数据。
     * 
     * @param pTarget @~english the target object pointer.
     * @~chinese 目标对象指针。
     * @param pSelector @~english the SEL_HttpResponse function.
     * @~chinese 回调函数。
     */
    CC_DEPRECATED_ATTRIBUTE inline void setResponseCallback(Ref* pTarget, SEL_HttpResponse pSelector)
    {
        _pTarget = pTarget;
        _pSelector = pSelector;
        
        if (_pTarget)
        {
            _pTarget->retain();
        }
    }
    /**@~english
     * Set response callback function of HttpRequest object.
     * When response come back, we would call _pCallback to process response data.
     *
     * @~chinese 
     * 设置HttpRequest对象的响应回调函数。
     * 当响应返回时,将会调用_pCallback来处理响应数据。
     * 
     * @param callback @~english the ccHttpRequestCallback function.
     * @~chinese ccHttpRequestCallback函数。
     */
    inline void setResponseCallback(const ccHttpRequestCallback& callback)
    {
        _pCallback = callback;
    }
    
    /** @~english
     * Get the target of callback selector funtion, mainly used by HttpClient.
     *
     * @~chinese 
     * 获取回调函数的target对象，主要用于HttpClient。
     * 
     * @return @~english Ref* the target of callback selector funtion
     * @~chinese 回调函数的target对象
     */
    inline Ref* getTarget()
    {
        return _pTarget;
    }

    /**@~english
     * This sub class is just for migration SEL_CallFuncND to SEL_HttpResponse,someday this way will be removed.
     * 
     * @~chinese 
     * 用于将SEL_CallFuncND转换成SEL_HttpResponse的子类，这个类将会被移除。
     * 
     * @lua NA
     */
    class _prxy
    {
    public:
        /** @~english Constructor.  @~chinese 构造函数。*/
        _prxy( SEL_HttpResponse cb ) :_cb(cb) {}
        /** @~english Destructor.  @~chinese 析构函数。*/
        ~_prxy(){};
        /** @~english operator override.  @~chinese 操作符重载。*/
        operator SEL_HttpResponse() const { return _cb; }
        CC_DEPRECATED_ATTRIBUTE operator SEL_CallFuncND()   const { return (SEL_CallFuncND) _cb; }
    protected:
        SEL_HttpResponse _cb;
    };
    
    /** @~english
     * Get _prxy object by the _pSelector.
     *
     * @~chinese 
     * 根据_pSelector获取_prxy对象。
     * 
     * @return @~english the _prxy object
     * @~chinese _prxy对象
     */
    inline _prxy getSelector()
    {
        return _prxy(_pSelector);
    }
    
    /**@~english
     * Get ccHttpRequestCallback callback function.
     *
     * @~chinese 
     * 获取ccHttpRequestCallback回调函数。
     * 
     * @return @~english ccHttpRequestCallback callback function.
     * @~chinese ccHttpRequestCallback回调函数。
     */
    inline const ccHttpRequestCallback& getCallback()
    {
        return _pCallback;
    }
    
    /** @~english
     * Set custom-defined headers.
     *
     * @~chinese 
     * 设置自定义的请求头。
     * 
     * @param pHeaders @~english the string vector of custom-defined headers.
     * @~chinese 包含自定义请求头的std::vector<std::string>。
     */
    inline void setHeaders(std::vector<std::string> pHeaders)
   	{
   		_headers=pHeaders;
   	}
   
    /** @~english
     * Get custom headers.
     *
     * @~chinese 
     * 获取自定义的请求头。
     * 
     * @return @~english the string vector of custom-defined headers.
     * @~chinese 包含自定义请求头的std::vector<std::string>。
     */
   	inline std::vector<std::string> getHeaders()
   	{
   		return _headers;
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
    std::vector<std::string>    _headers;		      /// custom http headers
};

}

NS_CC_END

// end group
/// @}

#endif //__HTTP_REQUEST_H__
