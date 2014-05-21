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

NS_CC_BEGIN

namespace network {

/** 
 @brief 定义了用户会在onHttpCompleted(sender, HttpResponse) 回调中接收的对象
 请移步 tests/test-cpp/Classes/ExtensionTest/NetworkTest/HttpClientTest.cpp 作为参考
 @since v2.0.2
 */
class HttpResponse : public cocos2d::Ref
{
public:
    /** 构造函数，被HttpClient内部使用，用户不需要手动创建HttpResponse
     @param 请求引导这个响应的相符的HttpRequest
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
    }
    
    /** 析构函数，会被HttpClient内部调用，
     用户不需要手动销毁HttpResponse对象
     */
    virtual ~HttpResponse()
    {
        if (_pHttpRequest)
        {
            _pHttpRequest->release();
        }
    }
    
    /** 覆写autorelease方法来避免开发者调用 */
    cocos2d::Ref* autorelease(void)
    {
        CCASSERT(false, "HttpResponse is used between network thread and ui thread \
                        therefore, autorelease is forbidden here");
        return NULL;
    }
    
    // getters，会被用户调用
    
    /** 得到导致这个响应的相符的HttpRequest，
        这里没有对应的setter方法，因为已经在类的构造函数中设置了
     */
    inline HttpRequest* getHttpRequest()
    {
        return _pHttpRequest;
    }
        
    /** 方便查看http请求是否成功的返回了，
        虽然用户可以通过判断(http return code = 200)来确定，我们依然想要一个更简单的方式
        如果这个getter返回false，你可以调用getResponseCode 和 getErrorBuffer来看到更多细节
     */
    inline bool isSucceed()
    {
        return _succeed;
    };
    
    /** 获取http响应的raw数据 */
    inline std::vector<char>* getResponseData()
    {
        return &_responseData;
    }
    
    /** 获取Rawheader **/
    inline std::vector<char>* getResponseHeader()
    {
        return &_responseHeader;
    }

    /** 获取http相应的errorCode
     *  我知道你想要看见http 200 :)
     */
    inline long getResponseCode()
    {
        return _responseCode;
    }

    /** Get the error buffer which will tell you more about the reason why http request failed
     */
    /** 得到错误缓存，能够告诉你更多关于http请求失败的原因
     */
    inline const char* getErrorBuffer()
    {
        return _errorBuffer.c_str();
    }
    
    // setters，会被HttpClient调用
    // 用户应该避免调用这些方法 
    
    
    /** 如果http请求返回成功则设置
     虽然用户能判断它(http code == 200)，我们依然想要一个更简单的方式
     这个setter主要被用在HttpClient里面，用户不得直接设置它
     */
    inline void setSucceed(bool value)
    {
        _succeed = value;
    };
    
    
    /** 设置http响应的raw buffer，被HttpClient所使用
     */
    inline void setResponseData(std::vector<char>* data)
    {
        _responseData = *data;
    }
    
    /** 设置http响应Header的raw buffer，被HttpClient所使用
     */
    inline void setResponseHeader(std::vector<char>* data)
    {
        _responseHeader = *data;
    }
    
    
    /** 设置http响应errorCode
     */
    inline void setResponseCode(long value)
    {
        _responseCode = value;
    }
    
    
    /** 设置error buffer，会告诉你更多为什么http请求失败的原因
     */
    inline void setErrorBuffer(const char* value)
    {
        _errorBuffer.clear();
        _errorBuffer.assign(value);
    };
    
protected:
    bool initWithRequest(HttpRequest* request);
    
    // 属性
    HttpRequest*        _pHttpRequest;      /// 导致这个响应的相应请求指针
    bool                _succeed;           /// 简单的表明http请求是否成功
    std::vector<char>   _responseData;      /// 返回的raw数据。你也可以转成一个字符串
    std::vector<char>   _responseHeader;    /// 返回的raw header数据。你也可以转成一个字符串
    long                _responseCode;      /// librurl返回的状态码，例如：200、404
    std::string         _errorBuffer;       /// 如果 _responseCode != 200, 请从_errorBuffer里面寻找原因
    
};

}

NS_CC_END

#endif //__HTTP_RESPONSE_H__
