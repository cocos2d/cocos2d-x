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

/*
 //Http request type
 typedef enum {
 kHttpRequestGet,
 kHttpRequestPost,
 // kHttpRequestDownloadFile,
 } HttpRequestType;
 
 /// Http Request structure
 typedef struct {
 HttpRequestType             requestType;    /// kHttpRequestGet, kHttpRequestPost or other enums
 std::string                 url;            /// target url that this request is sent to
 std::vector<char>           requestData;    /// used for POST
 std::string                 tag;            /// user defined tag, to identify different requests in response callback
 cocos2d::CCObject*          pTarget;        /// callback target of pSelector function
 cocos2d::SEL_CallFuncND     pSelector;      /// callback function, e.g. MyLayer::onHttpResponse(CCObject *sender, void *data)
 void*                       pUserData;      /// You can add your customed data here
 } HttpRequestPacket;
 */


#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN

class HttpRequest : public cocos2d::CCObject
{
public:
    /** Use this enum type as param in setReqeustType(param) */
    typedef enum
    {
        kHttpGet,
        kHttpPost,
        kHttpUnkown,
    } HttpRequestType;
    
    HttpRequest()
    {
        _requestType = kHttpUnkown;
        _url.clear();
        _requestData.clear();
        _tag.clear();
        _pTarget = NULL;
        _pSelector = NULL;
        _pUserData = NULL;
    };
    
    virtual ~HttpRequest()
    {
        if (_pTarget)
        {
            _pTarget->release();
        }
    };
    
    /** override autorelease method to avoid developers to call it */
    CCObject* autorelease(void)
    {
        CCAssert(true, "HttpResponse is used between network thread and ui thread \
                 therefore, autorelease is forbidden here");
        return NULL;
    }
            
    // setter/getters for properties
    
    inline void setRequestType(HttpRequestType type)
    {
        _requestType = type;
    };
    inline HttpRequestType getRequestType()
    {
        return _requestType;
    };
    
    inline void setUrl(const char* url)
    {
        _url = url;
    };
    inline const char* getUrl()
    {
        return _url.c_str();
    };
    
    inline void setRequestData(const char* buffer, unsigned int len)
    {
        _requestData.assign(buffer, buffer + len);
    };
    inline char* getRequestData()
    {
        return &(_requestData.front());
    }
    inline int getRequestDataSize()
    {
        return _requestData.size();
    }
    
    inline void setTag(const char* tag)
    {
        _tag = tag;
    };
    inline const char* getTag()
    {
        return _tag.c_str();
    };
    
    inline void setUserData(void* pUserData)
    {
        _pUserData = pUserData;
    };
    inline void* getUserData()
    {
        return _pUserData;
    };
    
    inline void setResponseCallback(cocos2d::CCObject* pTarget, cocos2d::SEL_CallFuncND pSelector)
    {
        _pTarget = pTarget;
        _pSelector = pSelector;
        
        if (_pTarget)
        {
            _pTarget->retain();
        }
    }
    inline CCObject* getTarget()
    {
        return _pTarget;
    }
    inline cocos2d::SEL_CallFuncND getSelector()
    {
        return _pSelector;
    }
        
protected:
    // properties
    HttpRequestType             _requestType;    /// kHttpRequestGet, kHttpRequestPost or other enums
    std::string                 _url;            /// target url that this request is sent to
    std::vector<char>           _requestData;    /// used for POST
    std::string                 _tag;            /// user defined tag, to identify different requests in response callback
    cocos2d::CCObject*          _pTarget;        /// callback target of pSelector function
    cocos2d::SEL_CallFuncND     _pSelector;      /// callback function, e.g. MyLayer::onHttpResponse(CCObject *sender, void *data)
    void*                       _pUserData;      /// You can add your customed data here 
};

NS_CC_EXT_END

#endif //__HTTP_REQUEST_H__