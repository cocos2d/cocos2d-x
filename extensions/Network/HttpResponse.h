/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 
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

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "HttpRequest.h"

NS_CC_EXT_BEGIN

class HttpResponse : public cocos2d::CCObject
{
public:
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
    virtual ~HttpResponse()
    {
        if (_pHttpRequest)
        {
            _pHttpRequest->release();
        }
    }
    
    /** override autorelease method to prevent developers from calling it */
    CCObject* autorelease(void)
    {
        CCAssert(true, "HttpResponse is used between network thread and ui thread \
                        therefore, autorelease is forbidden here");
        return NULL;
    }
    
    // setters,getters for properties
    inline HttpRequest* getHttpRequest()
    {
        return _pHttpRequest;
    }
    
    inline void setSucceed(bool value)
    {
        _succeed = value;
    };
    inline bool isSucceed()
    {
        return _succeed;
    };
        
    inline void setResponseData(std::vector<char>* data)
    {
        _responseData = *data;
    }
    inline std::vector<char>* getResponseData()
    {
        return &_responseData;
    }
    
    inline void setResponseCode(int value)
    {
        _responseCode = value;
    }
    inline int getResponseCode()
    {
        return _responseCode;
    }
    
    inline void setErrorBuffer(const char* value)
    {
        _errorBuffer.clear();
        _errorBuffer.assign(value);
    };
    inline const char* getErrorBuffer()
    {
        return _errorBuffer.c_str();
    }
    
protected:
    bool initWithRequest(HttpRequest* request);
    
    // properties
    HttpRequest*        _pHttpRequest;  /// the corresponding HttpRequest pointer who leads to this response 
    bool                _succeed;
    std::vector<char>   _responseData;
    int                 _responseCode;  /// the CURLcode returned from libcurl
    std::string         _errorBuffer;   /// if _responseCode != 200, please read _errorBuffer to find the reason 
};

NS_CC_EXT_END

#endif //__HTTP_RESPONSE_H__
