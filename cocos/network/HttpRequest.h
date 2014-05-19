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

NS_CC_BEGIN

namespace network {

class HttpClient;
class HttpResponse;

typedef std::function<void(HttpClient* client, HttpResponse* response)> ccHttpRequestCallback;
typedef void (cocos2d::Ref::*SEL_HttpResponse)(HttpClient* client, HttpResponse* response);
#define httpresponse_selector(_SELECTOR) (cocos2d::network::SEL_HttpResponse)(&_SELECTOR)

/** 
 @brief 定义了用户必须为 HttpClient::send(HttpRequest*) 方法打包的对象
 请移步 tests/test-cpp/Classes/ExtensionTest/NetworkTest/HttpClientTest.cpp 作为参考
 @since v2.0.2
 */

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#ifdef DELETE
#undef DELETE
#endif
#endif

class HttpRequest : public Ref
{
public:
    /** 在setRequestType(param)时使用这个枚举类型作为参数 */
    enum class Type
    {
        GET,
        POST,
        PUT,
        DELETE,
        UNKNOWN,
    };
    
    /** 构造
        因为 HttpRequset 对象会被用在UI线程和network线程之间，
        为了避免崩溃，在AutoreleasePool中，requestObj->autorelease()是被禁止的
        new/retain/release 依然工作，意味着你需要手动释放它。
        请移步 HttpRequestTest.cpp 找到用例
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
    
    /** 析构 */
    virtual ~HttpRequest()
    {
        if (_pTarget)
        {
            _pTarget->release();
        }
    };
    
    /** 复写 autorelease 方法来避免开发者调用它 */
    Ref* autorelease(void)
    {
        CCASSERT(false, "HttpResponse is used between network thread and ui thread \
                 therefore, autorelease is forbidden here");
        return NULL;
    }
            
    // 属性的 setter/getters
     
    /** 在发送之前，HttpRequest对象的必填字段
        目前支持 kHttpGet & kHttpPost 
     */
    inline void setRequestType(Type type)
    {
        _requestType = type;
    };
    /** 取回 kHttpGet/Post/... 的枚举值*/
    inline Type getRequestType()
    {
        return _requestType;
    };
    
    /** 在发送之前，HttpRequest对象的必填字段
     */
    inline void setUrl(const char* url)
    {
        _url = url;
    };
    /** 取回设置的url */
    inline const char* getUrl()
    {
        return _url.c_str();
    };
    
    /** 可选字段。你可以在这里设置你的post数据
     */
    inline void setRequestData(const char* buffer, size_t len)
    {
        _requestData.assign(buffer, buffer + len);
    };
    /** 取回请求数据的指针 */
    inline char* getRequestData()
    {
        if(_requestData.size() != 0)
            return &(_requestData.front());

        return nullptr;
    }
    /** 取回请求数据的大小 */
    inline ssize_t getRequestDataSize()
    {
        return _requestData.size();
    }
    
    /** 可选字段。你可以设置一个string tag来标记你的请求，这个tag能通过HttpResponse->getHttpRequest->getTag()被找到。
     */
    inline void setTag(const char* tag)
    {
        _tag = tag;
    };
    /** 获取string tag来认出请求。
        最佳实践是在你的 MyClass::onMyHttpRequestCompleted(sender, HttpResponse*) callback 中使用
     */
    inline const char* getTag()
    {
        return _tag.c_str();
    };
    
    /** 可选字段。你可以在每个请求中附上自定义的数据，并在响应回调中获取它。
        但是你需要手动 new/delete 数据指针
     */
    inline void setUserData(void* pUserData)
    {
        _pUserData = pUserData;
    };
    /** 获取预先设定好的自定义数据指针。
        不要忘了删除它。HttpClient/HttpResponse/HttpRequest 不会对这个指针做任何处理
     */
    inline void* getUserData()
    {
        return _pUserData;
    };
    
    /** 必填字段。你应该在ack http 请求完成设置回调selector函数(You should set the callback selector function at ack the http request completed)
     */
    CC_DEPRECATED_ATTRIBUTE inline void setResponseCallback(Ref* pTarget, SEL_CallFuncND pSelector)
    {
        setResponseCallback(pTarget, (SEL_HttpResponse) pSelector);
    }

    CC_DEPRECATED_ATTRIBUTE inline void setResponseCallback(Ref* pTarget, SEL_HttpResponse pSelector)
    {
        _pTarget = pTarget;
        _pSelector = pSelector;
        
        if (_pTarget)
        {
            _pTarget->retain();
        }
    }
    
    inline void setResponseCallback(const ccHttpRequestCallback& callback)
    {
        _pCallback = callback;
    }
    
    /** 得到回调selector函数的目标，主要被HttpClient使用 */
    inline Ref* getTarget()
    {
        return _pTarget;
    }

    /* 这个内部类仅仅为了将 SEL_CallFuncND 迁移到 SEL_HttpResponse,
       在未来某天会被去掉 */
    class _prxy
    {
    public:
        _prxy( SEL_HttpResponse cb ) :_cb(cb) {}
        ~_prxy(){};
        operator SEL_HttpResponse() const { return _cb; }
        CC_DEPRECATED_ATTRIBUTE operator SEL_CallFuncND()   const { return (SEL_CallFuncND) _cb; }
    protected:
        SEL_HttpResponse _cb;
    };
    
    /** 得到回调selector函数的指针，主要被HttpClient使用 */
    inline _prxy getSelector()
    {
        return _prxy(_pSelector);
    }
    
    inline const ccHttpRequestCallback& getCallback()
    {
        return _pCallback;
    }
    
    /** 设置任何自定义头部 **/
    inline void setHeaders(std::vector<std::string> pHeaders)
   	{
   		_headers=pHeaders;
   	}
   
    /** 获取自定义头部 **/
   	inline std::vector<std::string> getHeaders()
   	{
   		return _headers;
   	}
    
protected:
    // 属性
    Type                        _requestType;    /// kHttpRequestGet, kHttpRequestPost 或者其他枚举类型
    std::string                 _url;            /// 这个请求发送的目标url
    std::vector<char>           _requestData;    /// 用于POST
    std::string                 _tag;            /// 用户定义的tag，用来在响应回调中识别不同的请求
    Ref*                        _pTarget;        /// pSelector 函数的回调目标
    SEL_HttpResponse            _pSelector;      /// 回调函数，例如：MyLayer::onHttpResponse(HttpClient *sender, HttpResponse * response)
    ccHttpRequestCallback       _pCallback;      /// C++11 风格的回调
    void*                       _pUserData;      /// 你可以在这里添加你的自定义数据
    std::vector<std::string>    _headers;		 /// 自定义的http头部 
};

}

NS_CC_END

#endif //__HTTP_REQUEST_H__
