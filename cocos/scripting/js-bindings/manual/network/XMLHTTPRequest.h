/*
 * Created by Rolando Abarca 2012.
 * Copyright (c) 2012 Rolando Abarca. All rights reserved.
 * Copyright (c) 2013 Zynga Inc. All rights reserved.
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * Heavy based on: https://github.com/funkaster/FakeWebGL/blob/master/FakeWebGL/WebGL/XMLHTTPRequest.h
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#ifndef __FAKE_XMLHTTPREQUEST_H__
#define __FAKE_XMLHTTPREQUEST_H__

#include "jsapi.h"
#include "jsfriendapi.h"
#include "network/HttpClient.h"
#include "js_bindings_config.h"
#include "ScriptingCore.h"
#include "jsb_helper.h"

class MinXmlHttpRequest : public cocos2d::Ref
{
public:
    enum class ResponseType
    {
        STRING,
        ARRAY_BUFFER,
        BLOB,
        DOCUMENT,
        JSON
    };

    // Ready States (http://www.w3.org/TR/XMLHttpRequest/#interface-xmlhttprequest)
    static const unsigned short UNSENT = 0;
    static const unsigned short OPENED = 1;
    static const unsigned short HEADERS_RECEIVED = 2;
    static const unsigned short LOADING = 3;
    static const unsigned short DONE = 4;

    MinXmlHttpRequest();
    ~MinXmlHttpRequest();
    
    JS_BINDED_CLASS_GLUE(MinXmlHttpRequest);
    JS_BINDED_CONSTRUCTOR(MinXmlHttpRequest);
    JS_BINDED_PROP_ACCESSOR(MinXmlHttpRequest, onloadstart);
    JS_BINDED_PROP_ACCESSOR(MinXmlHttpRequest, onreadystatechange);
    JS_BINDED_PROP_ACCESSOR(MinXmlHttpRequest, onabort);
    JS_BINDED_PROP_ACCESSOR(MinXmlHttpRequest, onerror);
    JS_BINDED_PROP_ACCESSOR(MinXmlHttpRequest, onload);
    JS_BINDED_PROP_ACCESSOR(MinXmlHttpRequest, onloadend);
    JS_BINDED_PROP_ACCESSOR(MinXmlHttpRequest, ontimeout);
    JS_BINDED_PROP_ACCESSOR(MinXmlHttpRequest, withCredentials);
    JS_BINDED_PROP_ACCESSOR(MinXmlHttpRequest, upload);
    JS_BINDED_PROP_ACCESSOR(MinXmlHttpRequest, timeout);
    JS_BINDED_PROP_ACCESSOR(MinXmlHttpRequest, responseType);
    JS_BINDED_PROP_GET(MinXmlHttpRequest, readyState);
    JS_BINDED_PROP_GET(MinXmlHttpRequest, status);
    JS_BINDED_PROP_GET(MinXmlHttpRequest, statusText);
    JS_BINDED_PROP_GET(MinXmlHttpRequest, responseText);
    JS_BINDED_PROP_GET(MinXmlHttpRequest, response);
    JS_BINDED_PROP_GET(MinXmlHttpRequest, responseXML);
    JS_BINDED_FUNC(MinXmlHttpRequest, open);
    JS_BINDED_FUNC(MinXmlHttpRequest, send);
    JS_BINDED_FUNC(MinXmlHttpRequest, abort);
    JS_BINDED_FUNC(MinXmlHttpRequest, getAllResponseHeaders);
    JS_BINDED_FUNC(MinXmlHttpRequest, getResponseHeader);
    JS_BINDED_FUNC(MinXmlHttpRequest, setRequestHeader);
    JS_BINDED_FUNC(MinXmlHttpRequest, overrideMimeType);

    void handle_requestResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

    void update(float dt);
private:
    void _gotHeader(std::string header);
    void _setRequestHeader(const char* field, const char* value);
    void _setHttpRequestHeader();
    void _setHttpRequestData(const char *data, size_t len);
    void _sendRequest(JSContext *cx);
    void _notify(JS::HandleObject callback);
    
    std::string                       _url;
    JSContext*                        _cx;
    std::string                       _meth;
    std::string                       _type;
    char*                             _data;
    uint32_t                          _dataSize;
    mozilla::Maybe<JS::PersistentRootedObject> _onloadstartCallback;
    mozilla::Maybe<JS::PersistentRootedObject> _onabortCallback;
    mozilla::Maybe<JS::PersistentRootedObject> _onerrorCallback;
    mozilla::Maybe<JS::PersistentRootedObject> _onloadCallback;
    mozilla::Maybe<JS::PersistentRootedObject> _onloadendCallback;
    mozilla::Maybe<JS::PersistentRootedObject> _ontimeoutCallback;
    mozilla::Maybe<JS::PersistentRootedObject> _onreadystateCallback;
    int                               _readyState;
    long                              _status;
    std::string                       _statusText;
    ResponseType                      _responseType;
    unsigned long long                _timeout;
    float                             _elapsedTime;
    bool                              _isAsync;
    cocos2d::network::HttpRequest*    _httpRequest;
    bool                              _isNetwork;
    bool                              _withCredentialsValue;
    bool                              _errorFlag;
    std::unordered_map<std::string, std::string>          _httpHeader;
    std::unordered_map<std::string, std::string>          _requestHeader;
    bool                              _isAborted;
    cocos2d::Scheduler*               _scheduler;
};

#endif
