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

#ifndef __HTTP_RESPONSE__
#define __HTTP_RESPONSE__

#include "network/HttpRequest.h"

/**
 * @addtogroup network
 * @{
 */

NS_CC_BEGIN

namespace network {

/** 
 * @brief @~english A HttpResponse class is wrapped to the related responsed data came back from the HttpClient.
 * @~chinese HttpResponse是对HttpClient返回的响应数据的封装。
 * @see samples/TestCpp/Classes/ExtensionTest/NetworkTest/HttpClientTest.cpp.
 * @since v2.0.2.
 * @lua NA
 */
class CC_DLL HttpResponse : public cocos2d::Ref
{
public:
    /** @~english
     * Constructor, it's used by HttpClient internal, users don't need to create HttpResponse manually.
     * @~chinese 
     * 构造函数,HttpResponse在HttpClient内部创建,用户不需要手动创建HttpResponse。
     * @param request @~english the corresponding HttpRequest which leads to this response.
     * @~chinese 对应的HttpRequest对象
     */
    HttpResponse(HttpRequest* request)
    {
        _pHttpRequest = request;
        if (_pHttpRequest)
        {
            _pHttpRequest->retain();
        }
        
        _succeed = false;
        _responseData.clear();
        _errorBuffer.clear();
        _responseDataString = "";
    }
    
    /** @~english
     * Destructor, it will be called in HttpClient internal.
     * Users don't need to desturct HttpResponse object manully.
     * @~chinese 
     * 析构函数时, 它也在HttpClient内部调用。
     * 用户不需手动的触发这个析构函数。
     */
    virtual ~HttpResponse()
    {
        if (_pHttpRequest)
        {
            _pHttpRequest->release();
        }
    }
    
    /** @~english
     * Override autorelease method to prevent developers from calling it.
     * If this method is called , it would trigger CCASSERT.
     * @~chinese 
     * 重写autorelease方法，以防开发者调用它。
     * 当这个方法被调用时,它将触发CCASSERT。
     * @return @~english always return nullptr.
     * @~chinese 始终返回nullptr。
     */
    cocos2d::Ref* autorelease(void)
    {
        CCASSERT(false, "HttpResponse is used between network thread and ui thread \
                        therefore, autorelease is forbidden here");
        return NULL;
    }
    
    // getters, will be called by users
    
    /** @~english
     * Get the corresponding HttpRequest object which leads to this response.
     * There's no paired setter for it, because it's already setted in class constructor.
     * @~chinese 
     * 获得对应这个响应的HttpRequest对象。
     * 这里没有对应的setter函数，因为_pHttpRequest是在构造函数中赋值的。
     * @return @~english the corresponding HttpRequest object which leads to this response.
     * @~chinese 对应这个响应的HttpRequest对象。
     */
    inline HttpRequest* getHttpRequest()
    {
        return _pHttpRequest;
    }
        
    /** @~english
     * To see if the HttpReqeust is returned successfully.
     * Althrough users can judge if (http response code == 200), we want an easier way.
     * If this getter returns false, you can call getResponseCode and getErrorBuffer to find more details.
     * @~chinese 
     * 判断HttpReqeust是否返回成功。
     * 虽然用户可以通过(response code == 200)是否成立来判断,但我们也需要一种更简单的方法。
     * 如果返回失败,可以通过调用getResponseCode和getErrorBuffer获取更多的细节。
     * @return @~english bool the flag that represent whether the http request return sucesssfully or not.
     * @~chinese 判断HttpReqeust是否返回成功的标记。
     */
    inline bool isSucceed()
    {
        return _succeed;
    };
    
    /** @~english
     * Get the http response data.
     * @~chinese 
     * 获取http响应数据。
     * @return @~english the pointer that point to the _responseData.
     * @~chinese 指向_responseData的指针。
     */
    inline std::vector<char>* getResponseData()
    {
        return &_responseData;
    }
    
    /**@~english
     * Get the response headers.
     * @~chinese 
     * 响应头。
     * @return @~english the pointer that point to the _responseHeader.
     * @~chinese 指向_responseHeader的指针。
     */
    inline std::vector<char>* getResponseHeader()
    {
        return &_responseHeader;
    }

    /** @~english
     * Get the http response code to judge whether response is sucessful or not.
     * If _responseCode is not 200, you should check the meaning for _responseCode by the net.
     * @~chinese 
     * 获取响应码用来判断响应成功与否。
     * 当_responseCode不为200时，你应当通过网络查找一下对应响应码的意义。
     * @return @~english the value of _responseCode
     * @~chinese _responseCode的价值
     */
    inline long getResponseCode()
    {
        return _responseCode;
    }

    /** @~english
     * Get the error buffer which will tell you more about the reason why http request failed.
     * @~chinese 
     * 获取错误缓存，它将更详细地描述HttpRequest失败的原因。
     * @return @~english the pointer that point to _errorBuffer.
     * @~chinese 指向_errorBuffer的指针。
     */
    inline const char* getErrorBuffer()
    {
        return _errorBuffer.c_str();
    }
    
    // setters, will be called by HttpClient
    // users should avoid invoking these methods
    
    
    /** @~english
     * Set whether the http request is returned successfully or not,
     * This setter is mainly used in HttpClient, users mustn't set it directly
     * @~chinese 
     * 设置http request是否成功的标记,
     * 这个setter在HttpClient中设置,用户不能直接调用。
     * @param value @~english the flag represent whether the http request is successful or not.
     * @~chinese 是否成功的标记。
     */
    inline void setSucceed(bool value)
    {
        _succeed = value;
    };
    
    
    /** @~english
     * Set the http response data buffer, it is used by HttpClient.
     * @~chinese 
     * 设置http响应的数据缓存,它由HttpClient调用。
     * @param data @~english the pointer point to the response data buffer.
     * @~chinese 指向response数据缓存区的指针。
     */
    inline void setResponseData(std::vector<char>* data)
    {
        _responseData = *data;
    }
    
    /** @~english
     * Set the http response headers buffer, it is used by HttpClient.
     * @~chinese 
     * 设置http的响应头缓存,它由HttpClient调用。
     * @param data @~english the pointer point to the response headers buffer.
     * @~chinese 指向response headers缓存区的指针。
     */
    inline void setResponseHeader(std::vector<char>* data)
    {
        _responseHeader = *data;
    }
    
    
    /** @~english
     * Set the http response code.
     * @~chinese 
     * 设置http响应码。
     * @param value @~english the http response code that represent whether the request is successful or not.
     * @~chinese http响应代码,表示请求成功与否。
     */
    inline void setResponseCode(long value)
    {
        _responseCode = value;
    }
    
    
    /** @~english
     * Set the error buffer which will tell you more the reason why http request failed.
     * @~chinese 
     * 设置http响应的错误缓存，它将会告诉你更多关于http请求失败的原因。
     * @param value @~english a string pointer that point to the reason.
     * @~chinese 指向错误缓存的指针。
     */
    inline void setErrorBuffer(const char* value)
    {
        _errorBuffer.clear();
        _errorBuffer.assign(value);
    };
    
    /**@~english
     * Set the response data by the string pointer and the defined size.
     * @~chinese 
     * 根据指定大小和字符串指针设置响应数据。
     * @param value @~english a string pointer that point to response data buffer.
     * @~chinese 指向响应数据缓存的指针。
     * @param n @~english the defined size that the response data buffer would be copied.
     * @~chinese 从value拷贝的响应数据的大小。
     */
    inline void setResponseDataString(const char* value, size_t n)
    {
        _responseDataString.clear();
        _responseDataString.assign(value, n);
    }
    
    /**@~english
     * Get the string pointer that point to the response data.
     * @~chinese 
     * 获取响应数据的字符串指针。
     * @return @~english the string pointer that point to the response data.
     * @~chinese 指向响应数据的字符串指针。
     */
    inline const char* getResponseDataString()
    {
        return _responseDataString.c_str();
    }
    
protected:
    bool initWithRequest(HttpRequest* request);
    
    // properties
    HttpRequest*        _pHttpRequest;  /// the corresponding HttpRequest pointer who leads to this response 
    bool                _succeed;       /// to indecate if the http reqeust is successful simply
    std::vector<char>   _responseData;  /// the returned raw data. You can also dump it as a string
    std::vector<char>   _responseHeader;  /// the returned raw header data. You can also dump it as a string
    long                _responseCode;    /// the status code returned from libcurl, e.g. 200, 404
    std::string         _errorBuffer;   /// if _responseCode != 200, please read _errorBuffer to find the reason
    std::string         _responseDataString; // the returned raw data. You can also dump it as a string
    
};

}

NS_CC_END

// end group
/// @}

#endif //__HTTP_RESPONSE_H__
