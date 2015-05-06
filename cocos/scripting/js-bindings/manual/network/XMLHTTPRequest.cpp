/*
 * Created by Rolando Abarca 2012.
 * Copyright (c) 2012 Rolando Abarca. All rights reserved.
 * Copyright (c) 2013 Zynga Inc. All rights reserved.
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * Heavy based on: https://github.com/funkaster/FakeWebGL/blob/master/FakeWebGL/WebGL/XMLHTTPRequest.cpp
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


#include "XMLHTTPRequest.h"
#include <string>
#include <algorithm>

using namespace std;


//#pragma mark - MinXmlHttpRequest

/**
 *  @brief Implementation for header retrieving.
 *  @param header 
 */
void MinXmlHttpRequest::_gotHeader(string header)
{
    // Get Header and Set StatusText
    // Split String into Tokens
    char * cstr = new char [header.length()+1];
    
    // check for colon.
    size_t found_header_field = header.find_first_of(":");
    
    if (found_header_field != std::string::npos)
    {
        // Found a header field.
        string http_field;
        string http_value;
        
        http_field = header.substr(0,found_header_field);
        http_value = header.substr(found_header_field+1, header.length());
        
        // Get rid of all \n
        if (!http_value.empty() && http_value[http_value.size() - 1] == '\n') {
            http_value.erase(http_value.size() - 1);
        }

        // Get rid of leading space (header is field: value format)
        if (!http_value.empty() && http_value[0] == ' ') {
            http_value.erase(0, 1);
        }
        
        // Transform field name to lower case as they are case-insensitive
        std::transform(http_field.begin(), http_field.end(), http_field.begin(), ::tolower);
        
        _httpHeader[http_field] = http_value;
        
    }
    else
    {
        // Seems like we have the response Code! Parse it and check for it.
        char * pch;
        strcpy(cstr, header.c_str());
        
        pch = strtok(cstr," ");
        while (pch != NULL)
        {
            
            stringstream ss;
            string val;
            
            ss << pch;
            val = ss.str();
            size_t found_http = val.find("HTTP");
            
            // Check for HTTP Header to set statusText
            if (found_http != std::string::npos) {
                
                stringstream mystream;
                
                // Get Response Status
                pch = strtok (NULL, " ");
                mystream << pch;

                pch = strtok (NULL, " ");
                mystream << " " << pch;
                
                _statusText = mystream.str();
                
            }
            
            pch = strtok (NULL, " ");
        }
    }
    
    CC_SAFE_DELETE_ARRAY(cstr);
}

/**
 *  @brief Set Request header for next call.
 *  @param field  Name of the Header to be set.
 *  @param value  Value of the Headerfield
 */
void MinXmlHttpRequest::_setRequestHeader(const char* field, const char* value)
{
    stringstream header_s;
    stringstream value_s;
    string header;
    
    auto iter = _requestHeader.find(field);
    
    // Concatenate values when header exists.
    if (iter != _requestHeader.end())
    {
        value_s << iter->second << "," << value;
    }
    else
    {
        value_s << value;
    }
    
    _requestHeader[field] = value_s.str();
}

/**
 * @brief  If headers has been set, pass them to curl.
 * 
 */
void MinXmlHttpRequest::_setHttpRequestHeader()
{
    std::vector<string> header;

    for (auto it = _requestHeader.begin(); it != _requestHeader.end(); ++it)
    {
        const char* first = it->first.c_str();
        const char* second = it->second.c_str();
        size_t len = sizeof(char) * (strlen(first) + 3 + strlen(second));
        char* test = (char*) malloc(len);
        memset(test, 0,len);
        
        strcpy(test, first);
        strcpy(test + strlen(first) , ": ");
        strcpy(test + strlen(first) + 2, second);

        header.push_back(test);
        
        free(test);
        
    }
    
    if (!header.empty())
    {
        _httpRequest->setHeaders(header);
    }
    
}

void MinXmlHttpRequest::_setHttpRequestData(const char *data, size_t len)
{
    if (len > 0 &&
        (_meth.compare("post") == 0 || _meth.compare("POST") == 0 ||
         _meth.compare("put") == 0 || _meth.compare("PUT") == 0))
    {
        _httpRequest->setRequestData(data, len);
    }
}

/**
 *  @brief Callback for HTTPRequest. Handles the response and invokes Callback.
 *  @param sender   Object which initialized callback
 *  @param respone  Response object
 */
void MinXmlHttpRequest::handle_requestResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
    _elapsedTime = 0;
    _scheduler->unscheduleAllForTarget(this);
    
    if(_isAborted || _readyState == UNSENT)
    {
        return;
    }

    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        CCLOG("%s completed", response->getHttpRequest()->getTag());
    }
    
    long statusCode = response->getResponseCode();
    char statusString[64] = {0};
    sprintf(statusString, "HTTP Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag());
    
    if (!response->isSucceed())
    {
        CCLOG("Response failed, error buffer: %s", response->getErrorBuffer());
        if (statusCode == 0 || statusCode == -1)
        {
            _errorFlag = true;
            _status = 0;
            _statusText.clear();
            _notify(_onerrorCallback);
            _notify(_onloadendCallback);
            return;
        }
    }
    
    // set header
    std::vector<char> *headers = response->getResponseHeader();
    
    std::string header(headers->begin(), headers->end());
    
    std::istringstream stream(header);
    std::string line;
    while(std::getline(stream, line)) {
        _gotHeader(line);
    }
    
    /** get the response data **/
    std::vector<char> *buffer = response->getResponseData();

    _status = statusCode;
    _readyState = DONE;
        
    _dataSize = static_cast<uint32_t>(buffer->size());
    CC_SAFE_FREE(_data);
    _data = (char*) malloc(_dataSize + 1);
    _data[_dataSize] = '\0';
    memcpy((void*)_data, (const void*)buffer->data(), _dataSize);
    
    _notify(_onreadystateCallback);
    _notify(_onloadCallback);
    _notify(_onloadendCallback);
}
/**
 * @brief   Send out request and fire callback when done.
 * @param cx    Javascript context
 */
void MinXmlHttpRequest::_sendRequest(JSContext *cx)
{
    _httpRequest->setResponseCallback(this, httpresponse_selector(MinXmlHttpRequest::handle_requestResponse));
    cocos2d::network::HttpClient::getInstance()->sendImmediate(_httpRequest);
    _httpRequest->release();
}

/**
 * @brief  Constructor initializes cchttprequest and stuff
 *
 */
MinXmlHttpRequest::MinXmlHttpRequest()
: _url()
, _cx(ScriptingCore::getInstance()->getGlobalContext())
, _meth()
, _type()
, _data(nullptr)
, _dataSize()
, _onreadystateCallback(nullptr)
, _onloadstartCallback(nullptr)
, _onabortCallback(nullptr)
, _onerrorCallback(nullptr)
, _onloadCallback(nullptr)
, _onloadendCallback(nullptr)
, _ontimeoutCallback(nullptr)
, _readyState(UNSENT)
, _status(0)
, _statusText()
, _responseType()
, _timeout(0)
, _elapsedTime(.0)
, _isAsync()
, _httpRequest(new cocos2d::network::HttpRequest())
, _isNetwork(true)
, _withCredentialsValue(true)
, _errorFlag(false)
, _httpHeader()
, _requestHeader()
, _isAborted(false)
{
    _scheduler = cocos2d::Director::getInstance()->getScheduler();
    _scheduler->retain();
}

/**
 * @brief Destructor cleans up _httpRequest and stuff
 *
 */
MinXmlHttpRequest::~MinXmlHttpRequest()
{

#define SAFE_REMOVE_OBJECT(callback) if (callback != NULL)\
    {\
        JS::RemoveObjectRoot(_cx, &callback);\
    }

    SAFE_REMOVE_OBJECT(_onreadystateCallback);
    SAFE_REMOVE_OBJECT(_onloadstartCallback);
    SAFE_REMOVE_OBJECT(_onloadendCallback);
    SAFE_REMOVE_OBJECT(_onloadCallback);
    SAFE_REMOVE_OBJECT(_onerrorCallback);
    SAFE_REMOVE_OBJECT(_onabortCallback);
    SAFE_REMOVE_OBJECT(_ontimeoutCallback);
    
    if (_httpRequest)
    {
        // We don't need to release _httpRequest here since it will be released in the http callback.
//        _httpRequest->release();
    }

    CC_SAFE_FREE(_data);
    CC_SAFE_RELEASE_NULL(_scheduler);
}

/**
 *  @brief Initialize Object and needed properties.
 *
 */
JS_BINDED_CLASS_GLUE_IMPL(MinXmlHttpRequest);

/**
 *  @brief Implementation for the Javascript Constructor
 *
 */
JS_BINDED_CONSTRUCTOR_IMPL(MinXmlHttpRequest)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    MinXmlHttpRequest* req = new MinXmlHttpRequest();
    req->autorelease();
    
    js_proxy_t *p;
    jsval out;
    
    JSObject *obj = JS_NewObject(cx, &MinXmlHttpRequest::js_class, JS::RootedObject(cx, MinXmlHttpRequest::js_proto), JS::RootedObject(cx, MinXmlHttpRequest::js_parent));
    
    if (obj) {
        JS_SetPrivate(obj, req);
        out = OBJECT_TO_JSVAL(obj);
    }

    args.rval().set(out);
    p =jsb_new_proxy(req, obj);
    
    JS::AddNamedObjectRoot(cx, &p->obj, "XMLHttpRequest");
    return true;
}


/**
 *  @brief Get Callback function for Javascript
 *  @brief Set Callback function coming from Javascript
 *
 */
#define GETTER_SETTER_FOR_CALLBACK_PROP(x,y) JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, x)\
{\
    if (y)\
    {\
        jsval out = OBJECT_TO_JSVAL(y);\
        args.rval().set(out);\
    }\
    else\
    {\
        args.rval().set(JSVAL_NULL);\
    }\
    return true;\
}\
JS_BINDED_PROP_SET_IMPL(MinXmlHttpRequest, x)\
{\
    jsval callback = args.get(0);\
    if (callback != JSVAL_NULL)\
    {\
        y = callback.toObjectOrNull();\
        JS::AddNamedObjectRoot(cx, &y, #y);\
    }\
    return true;\
}


GETTER_SETTER_FOR_CALLBACK_PROP(onreadystatechange, _onreadystateCallback)
GETTER_SETTER_FOR_CALLBACK_PROP(onloadstart, _onloadstartCallback)
GETTER_SETTER_FOR_CALLBACK_PROP(onabort, _onabortCallback)
GETTER_SETTER_FOR_CALLBACK_PROP(onerror, _onerrorCallback)
GETTER_SETTER_FOR_CALLBACK_PROP(onload, _onloadCallback)
GETTER_SETTER_FOR_CALLBACK_PROP(onloadend, _onloadendCallback)
GETTER_SETTER_FOR_CALLBACK_PROP(ontimeout, _ontimeoutCallback)


/**
 *  @brief upload getter - TODO
 *
 *  Placeholder for further implementations!!
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, upload)
{
    args.rval().set(JSVAL_NULL);
    return true;
}

/**
 *  @brief upload setter - TODO
 *
 *  Placeholder for further implementations
 */
JS_BINDED_PROP_SET_IMPL(MinXmlHttpRequest, upload)
{
    args.rval().set(JSVAL_NULL);
    return true;
}

/**
 *  @brief timeout getter - TODO
 *
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, timeout)
{
    args.rval().set(long_long_to_jsval(cx, _timeout));
    return true;
}

/**
 *  @brief timeout setter - TODO
 *
 */
JS_BINDED_PROP_SET_IMPL(MinXmlHttpRequest, timeout)
{
    long long tmp;
    jsval_to_long_long(cx, args.get(0), &tmp);
    _timeout = (unsigned long long)tmp;
    return true;
    
}

/**
 *  @brief  get response type for actual XHR
 *
 *
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, responseType)
{
    JSString* str = JS_NewStringCopyN(cx, "", 0);
    args.rval().set(STRING_TO_JSVAL(str));
    return true;
}

/**
 *  @brief  responseXML getter - TODO
 *
 *  Placeholder for further implementation.
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, responseXML)
{
    args.rval().set(JSVAL_NULL);
    return true;
}

/**
 *  @brief  set response type for actual XHR
 *
 *
 */
JS_BINDED_PROP_SET_IMPL(MinXmlHttpRequest, responseType)
{
    jsval type = args.get(0);
    if (type.isString()) {
        JSString* str = type.toString();
        bool equal;
        
        JS_StringEqualsAscii(cx, str, "text", &equal);
        if (equal)
        {
            _responseType = ResponseType::STRING;
            return true;
        }
        
        JS_StringEqualsAscii(cx, str, "arraybuffer", &equal);
        if (equal)
        {
            _responseType = ResponseType::ARRAY_BUFFER;
            return true;
        }
        
        JS_StringEqualsAscii(cx, str, "json", &equal);
        if (equal)
        {
            _responseType = ResponseType::JSON;
            return true;
        }
        // ignore the rest of the response types for now
        return true;
    }
    JS_ReportError(cx, "Invalid response type");
    return false;
}

/**
 * @brief get readyState for actual XHR
 *
 *
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, readyState)
{
    args.rval().set(INT_TO_JSVAL(_readyState));
    return true;
}

/**
 *  @brief get status for actual XHR
 *
 *
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, status)
{
    args.rval().set(INT_TO_JSVAL(_status));
    return true;
}

/**
 *  @brief get statusText for actual XHR
 *
 *
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, statusText)
{
    jsval strVal = std_string_to_jsval(cx, _statusText);
    
    if (strVal != JSVAL_NULL)
    {
        args.rval().set(strVal);
        return true;
    }
    else
    {
        JS_ReportError(cx, "Error trying to create JSString from data");
        return false;
    }
}

/**
 *  @brief  get value of withCredentials property.
 *
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, withCredentials)
{
    args.rval().set(BOOLEAN_TO_JSVAL(_withCredentialsValue));
    return true;
}

/**
 *  withCredentials - set value of withCredentials property.
 *
 */
JS_BINDED_PROP_SET_IMPL(MinXmlHttpRequest, withCredentials)
{
    jsval credential = args.get(0);
    if (credential != JSVAL_NULL)
    {
        _withCredentialsValue = credential.toBoolean();
    }
    
    return true;
}

/**
 *  @brief  get (raw) responseText
 *
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, responseText)
{
    if (_data)
    {
        jsval strVal = std_string_to_jsval(cx, _data);

        if (strVal != JSVAL_NULL)
        {
            args.rval().set(strVal);
            return true;
        }
    }

    CCLOGERROR("ResponseText was empty, probably there is a network error!");
    
    // Return an empty string
    args.rval().set(std_string_to_jsval(cx, ""));

    return true;
}

/**
 *  @brief get response of latest XHR
 *
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, response)
{
    if (_responseType == ResponseType::STRING)
    {
        return _js_get_responseText(cx, args);
    }
    else
    {
        if (_readyState != DONE || _errorFlag)
        {
            args.rval().set(JSVAL_NULL);
            return true;
        }
        
        if (_responseType == ResponseType::JSON)
        {
            JS::RootedValue outVal(cx);
            
            jsval strVal = std_string_to_jsval(cx, _data);

            //size_t utf16Count = 0;
            //const jschar* utf16Buf = JS_GetStringCharsZAndLength(cx, JSVAL_TO_STRING(strVal), &utf16Count);
            //bool ok = JS_ParseJSON(cx, utf16Buf, static_cast<uint32_t>(utf16Count), &outVal);
            bool ok = JS_ParseJSON(cx, JS::RootedString(cx, strVal.toString()), &outVal);
            
            if (ok)
            {
                args.rval().set(outVal);
                return true;
            }
        }
        else if (_responseType == ResponseType::ARRAY_BUFFER)
        {
            JSObject* tmp = JS_NewArrayBuffer(cx, _dataSize);
            uint8_t* tmpData = JS_GetArrayBufferData(tmp);
            memcpy((void*)tmpData, (const void*)_data, _dataSize);
            jsval outVal = OBJECT_TO_JSVAL(tmp);

            args.rval().set(outVal);
            return true;
        }
        // by default, return text
        return _js_get_responseText(cx, args);
    }
}

/**
 *  @brief initialize new xhr.
 *  TODO: doesn't supprot username, password arguments now
 *        http://www.w3.org/TR/XMLHttpRequest/#the-open()-method
 *
 */
JS_BINDED_FUNC_IMPL(MinXmlHttpRequest, open)
{
    if (argc >= 2)
    {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        const char* method;
        const char* urlstr;
        bool async = true;
        JSString* jsMethod = JS::ToString( cx, args.get(0) );
        JSString* jsURL = JS::ToString( cx, args.get(1) );
        
        if (argc > 2) {
            async = JS::ToBoolean( args.get(2) );
        }
        
        JSStringWrapper w1(jsMethod);
        JSStringWrapper w2(jsURL);
        method = w1.get();
        urlstr = w2.get();
        
        _url = urlstr;
        _meth = method;
        _readyState = 1;
        _isAsync = async;
        
        if (_url.length() > 5 && _url.compare(_url.length() - 5, 5, ".json") == 0)
        {
            _responseType = ResponseType::JSON;
        }
        
        
        {
            auto requestType =
              (_meth.compare("get") == 0 || _meth.compare("GET") == 0) ? cocos2d::network::HttpRequest::Type::GET : (
              (_meth.compare("post") == 0 || _meth.compare("POST") == 0) ? cocos2d::network::HttpRequest::Type::POST : (
              (_meth.compare("put") == 0 || _meth.compare("PUT") == 0) ? cocos2d::network::HttpRequest::Type::PUT : (
              (_meth.compare("delete") == 0 || _meth.compare("DELETE") == 0) ? cocos2d::network::HttpRequest::Type::DELETE : (
                cocos2d::network::HttpRequest::Type::UNKNOWN))));

            _httpRequest->setRequestType(requestType);
            _httpRequest->setUrl(_url.c_str());
        }
        
       printf("[XMLHttpRequest] %s %s\n", _meth.c_str(), _url.c_str());
        
        _isNetwork = true;
        _readyState = OPENED;
        _status = 0;
        _isAborted = false;
        
        return true;
    }
    
    JS_ReportError(cx, "invalid call: %s", __FUNCTION__);
    return false;
    
}

/**
 *  @brief  send xhr
 *
 */
JS_BINDED_FUNC_IMPL(MinXmlHttpRequest, send)
{
    std::string data;
    
    // Clean up header map. New request, new headers!
    _httpHeader.clear();

    _errorFlag = false;
    
    if (argc == 1)
    {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        if (args.get(0).isString())
        {
            JSStringWrapper strWrap(args.get(0).toString());
            data = strWrap.get();
            _setHttpRequestData(data.c_str(), static_cast<size_t>(data.length()));
        }
        else if (args.get(0).isObject())
        {
            JSObject *obj = args.get(0).toObjectOrNull();
            if (JS_IsArrayBufferObject(obj))
            {
                _setHttpRequestData((const char *)JS_GetArrayBufferData(obj), JS_GetArrayBufferByteLength(obj));
            }
            else if (JS_IsArrayBufferViewObject(obj))
            {
                _setHttpRequestData((const char *)JS_GetArrayBufferViewData(obj), JS_GetArrayBufferViewByteLength(obj));
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    _setHttpRequestHeader();
    _sendRequest(cx);
    _notify(_onloadstartCallback);
    
    //begin schedule for timeout
    if(_timeout > 0)
    {
        _scheduler->scheduleUpdate(this, 0, false);
    }

    return true;
}

void MinXmlHttpRequest::update(float dt)
{
    _elapsedTime += dt;
    if(_elapsedTime * 1000 >= _timeout)
    {
        _notify(_ontimeoutCallback);
        _elapsedTime = 0;
        _readyState = UNSENT;
        _scheduler->unscheduleAllForTarget(this);
    }
}

/**
 *  @brief abort function
 *
 */
JS_BINDED_FUNC_IMPL(MinXmlHttpRequest, abort)
{
    //1.Terminate the request.
    _isAborted = true;

    //2.If the state is UNSENT, OPENED with the send() flag being unset, or DONE go to the next step.
    //nothing to do

    //3.Change the state to UNSENT.
    _readyState = UNSENT;
    
    _notify(_onabortCallback);
    
    return true;
}

/**
 *  @brief Get all response headers as a string
 *
 */
JS_BINDED_FUNC_IMPL(MinXmlHttpRequest, getAllResponseHeaders)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    stringstream responseheaders;
    string responseheader;
    
    for (auto it = _httpHeader.begin(); it != _httpHeader.end(); ++it)
    {
        responseheaders << it->first << ": " << it->second << "\n";
    }
    
    responseheader = responseheaders.str();
    
    jsval strVal = std_string_to_jsval(cx, responseheader);
    if (strVal != JSVAL_NULL)
    {
        args.rval().set(strVal);
        return true;
    }
    else
    {
        JS_ReportError(cx, "Error trying to create JSString from data");
        return false;
    }
    
    return true;
}

/**
 *  @brief Get all response headers as a string
 *
 */
JS_BINDED_FUNC_IMPL(MinXmlHttpRequest, getResponseHeader)
{
    JSString *header_value;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (!args.get(0).isString()) {
        return false;
    };
    header_value = args.get(0).toString();
    
    std::string data;
    JSStringWrapper strWrap(header_value);
    data = strWrap.get();
    
    stringstream streamdata;
    
    streamdata << data;

    string value = streamdata.str();
    std::transform(value.begin(), value.end(), value.begin(), ::tolower);
    
    auto iter = _httpHeader.find(value);
    if (iter != _httpHeader.end())
    {
        jsval js_ret_val =  std_string_to_jsval(cx, iter->second);
        args.rval().set(js_ret_val);
        return true;
    }
    else {
        args.rval().setUndefined();
        return true;
    }
}

/**
 *  @brief Set the given Fields to request Header.
 *
 *
 */
JS_BINDED_FUNC_IMPL(MinXmlHttpRequest, setRequestHeader)
{
    if (argc >= 2)
    {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        const char* field;
        const char* value;
        
        JSString* jsField = JS::ToString( cx, args.get(0) );
        JSString* jsValue = JS::ToString( cx, args.get(1) );
        
        JSStringWrapper w1(jsField);
        JSStringWrapper w2(jsValue);
        field = w1.get();
        value = w2.get();
        
        // Populate the request_header map.
        _setRequestHeader(field, value);
        
        return true;
    }
     
    return false;
    
}

/**
 * @brief overrideMimeType function - TODO!
 *
 * Just a placeholder for further implementations.
 */
JS_BINDED_FUNC_IMPL(MinXmlHttpRequest, overrideMimeType)
{
    return true;
}

/**
 *  @brief destructor for Javascript
 *
 */
static void basic_object_finalize(JSFreeOp *freeOp, JSObject *obj)
{
   CCLOG("basic_object_finalize %p ...", obj);
}

void MinXmlHttpRequest::_notify(JSObject * callback)
{
    js_proxy_t * p;
    void* ptr = (void*)this;
    p = jsb_get_native_proxy(ptr);

    if(p)
    {
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        
        if (callback)
        {
            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
            //JS_IsExceptionPending(cx) && JS_ReportPendingException(cx);
            JS::RootedValue fval(cx, OBJECT_TO_JSVAL(callback));
            JS::RootedValue out(cx);
            JS_CallFunctionValue(cx, JS::NullPtr(), fval, JS::HandleValueArray::empty(), &out);
        }
        
    }
}

/**
 *  @brief Register XMLHttpRequest to be usable in JS and add properties and Mehtods.
 *  @param cx   Global Spidermonkey JS Context.
 *  @param global   Global Spidermonkey Javascript object.
 */
void MinXmlHttpRequest::_js_register(JSContext *cx, JS::HandleObject global)
{
    JSClass jsclass = {
        "XMLHttpRequest", JSCLASS_HAS_PRIVATE, JS_PropertyStub,
        JS_DeletePropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
        JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub,
        basic_object_finalize
    };
    
    MinXmlHttpRequest::js_class = jsclass;
    static JSPropertySpec props[] = {
        JS_BINDED_PROP_DEF_ACCESSOR(MinXmlHttpRequest, onloadstart),
        JS_BINDED_PROP_DEF_ACCESSOR(MinXmlHttpRequest, onabort),
        JS_BINDED_PROP_DEF_ACCESSOR(MinXmlHttpRequest, onerror),
        JS_BINDED_PROP_DEF_ACCESSOR(MinXmlHttpRequest, onload),
        JS_BINDED_PROP_DEF_ACCESSOR(MinXmlHttpRequest, onloadend),
        JS_BINDED_PROP_DEF_ACCESSOR(MinXmlHttpRequest, ontimeout),
        JS_BINDED_PROP_DEF_ACCESSOR(MinXmlHttpRequest, onreadystatechange),
        JS_BINDED_PROP_DEF_ACCESSOR(MinXmlHttpRequest, responseType),
        JS_BINDED_PROP_DEF_ACCESSOR(MinXmlHttpRequest, withCredentials),
        JS_BINDED_PROP_DEF_ACCESSOR(MinXmlHttpRequest, timeout),
        JS_BINDED_PROP_DEF_GETTER(MinXmlHttpRequest, readyState),
        JS_BINDED_PROP_DEF_GETTER(MinXmlHttpRequest, status),
        JS_BINDED_PROP_DEF_GETTER(MinXmlHttpRequest, statusText),
        JS_BINDED_PROP_DEF_GETTER(MinXmlHttpRequest, responseText),
        JS_BINDED_PROP_DEF_GETTER(MinXmlHttpRequest, responseXML),
        JS_BINDED_PROP_DEF_GETTER(MinXmlHttpRequest, response),
        JS_PS_END
    };
    
    static JSFunctionSpec funcs[] = {
        JS_BINDED_FUNC_FOR_DEF(MinXmlHttpRequest, open),
        JS_BINDED_FUNC_FOR_DEF(MinXmlHttpRequest, abort),
        JS_BINDED_FUNC_FOR_DEF(MinXmlHttpRequest, send),
        JS_BINDED_FUNC_FOR_DEF(MinXmlHttpRequest, setRequestHeader),
        JS_BINDED_FUNC_FOR_DEF(MinXmlHttpRequest, getAllResponseHeaders),
        JS_BINDED_FUNC_FOR_DEF(MinXmlHttpRequest, getResponseHeader),
        JS_BINDED_FUNC_FOR_DEF(MinXmlHttpRequest, overrideMimeType),
        JS_FS_END
    };
    
    MinXmlHttpRequest::js_parent = nullptr;
    MinXmlHttpRequest::js_proto = JS_InitClass(cx, global, JS::NullPtr(), &MinXmlHttpRequest::js_class , MinXmlHttpRequest::_js_constructor, 0, props, funcs, nullptr, nullptr);
    
}

