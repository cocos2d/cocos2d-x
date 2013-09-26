//
//  XMLHTTPRequest.cpp
//  XMLHttpRequest
//
//  Created by Zynga 2013
//
//  Heavy based on: https://github.com/funkaster/FakeWebGL/blob/master/FakeWebGL/WebGL/XMLHTTPRequest.cpp
//  Copyright (c) 2012 Rolando Abarca. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.


#include "XMLHTTPRequest.h"
#include <string>

using namespace std;

//#pragma mark - MinXmlHttpRequest

/**
 *  @brief Implementation for header retrieving.
 *  @param header 
 */
void MinXmlHttpRequest::_gotHeader(string header) {
	// Get Header and Set StatusText
    // Split String into Tokens
    char * cstr = new char [header.length()+1];
    
    // check for colon.
    unsigned found_header_field = header.find_first_of(":");
    
    if (found_header_field != std::string::npos) {
        
        // Found a header field.
        string http_field;
        string http_value;
        
        http_field = header.substr(0,found_header_field);
        http_value = header.substr(found_header_field+1, header.length());
        
        // Get rid of all \n
        if (!http_value.empty() && http_value[http_value.size() - 1] == '\n') {
        	http_value.erase(http_value.size() - 1);
        }
        
        http_header[http_field] = http_value;
        
    }
    else {
        
        // Seems like we have the response Code! Parse it and check for it.
        char * pch;
        std::strcpy(cstr, header.c_str());
        
        pch = strtok(cstr," ");
        while (pch != NULL)
        {
            
            stringstream ss;
            string val;
            
            ss << pch;
            val = ss.str();
            unsigned found_http = val.find("HTTP");
            
            // Check for HTTP Header to set statusText
            if (found_http != std::string::npos) {
                
                stringstream mystream;
                
                // Get Response Status
                pch = strtok (NULL, " ");
                mystream << pch;

                pch = strtok (NULL, " ");
                mystream << " " << pch;
                
                statusText = mystream.str();
                
            }
            
            pch = strtok (NULL, " ");
        }
        
    }

}

/**
 *  @brief Set Request header for next call.
 *  @param field  Name of the Header to be set.
 *  @param value  Value of the Headerfield
 */
void MinXmlHttpRequest::_setRequestHeader(const char* field, const char* value) {
    
    stringstream header_s;
    stringstream value_s;
    string header;
    
    map<string, string>::iterator iter = request_header.find(field);
    
    // Concatenate values when header exists.
    if (iter != request_header.end() ) {
        
        value_s << iter->second << "," << value;
        
    }
    else {
        value_s << value;
    }
    
    request_header[field] = value_s.str();
    return;
    
}

/**
 * @brief  If headers has been set, pass them to curl.
 * 
 */
void MinXmlHttpRequest::_setHttpRequestHeader() {
    
    std::vector<string> header;

    for (std::map<string,string>::iterator it = request_header.begin(); it != request_header.end(); ++it) {

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
    
    if (!header.empty()) {
        cc_request->setHeaders(header);
    }
    
}

/**
 *  @brief Callback for HTTPRequest. Handles the response and invokes Callback.
 *  @param sender   Object which initialized callback
 *  @param respone  Response object
 */
void MinXmlHttpRequest::handle_requestResponse(cocos2d::extension::CCHttpClient *sender, cocos2d::extension::CCHttpResponse *response) {

    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        CCLOG("%s completed", response->getHttpRequest()->getTag());
    }
    
    int statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    
    if (!response->isSucceed())
    {
        CCLOG("response failed");
        CCLOG("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    // set header
    std::vector<char> *headers = response->getResponseHeader();
    
    char* concatHeader = (char*) malloc(headers->size() + 1);
    std::string header(headers->begin(), headers->end());
    strcpy(concatHeader, header.c_str());
    
    std::istringstream stream(concatHeader);
    std::string line;
    while(std::getline(stream, line)) {
        _gotHeader(line);
    }
    
    /** get the response data **/
    std::vector<char> *buffer = response->getResponseData();
    char* concatenated = (char*) malloc(buffer->size() + 1);
    std::string s2(buffer->begin(), buffer->end());
    
    strcpy(concatenated, s2.c_str());
    
    if (statusCode == 200)
    {
        //Succeeded
        status = 200;
        readyState = DONE;
        data << concatenated;
        dataSize = buffer->size();
    }
    else
    {
        status = 0;
    }
    // Free Memory.
    free((void*) concatHeader);
    free((void*) concatenated);
    
    js_proxy_t * p;
    void* ptr = (void*)this;
    p = jsb_get_native_proxy(ptr);
    
    if(p){
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
       
        if (onreadystateCallback) {
            //JS_IsExceptionPending(cx) && JS_ReportPendingException(cx);
            jsval fval = OBJECT_TO_JSVAL(onreadystateCallback);
            jsval out;
            JS_CallFunctionValue(cx, NULL, fval, 0, NULL, &out);
        }
     
    }

}
/**
 * @brief   Send out request and fire callback when done.
 * @param cx    Javascript context
 */
void MinXmlHttpRequest::_sendRequest(JSContext *cx) {
    
    cc_request->setResponseCallback(this, httpresponse_selector(MinXmlHttpRequest::handle_requestResponse));
    cocos2d::extension::CCHttpClient::getInstance()->send(cc_request);
    cc_request->release();

}

/**
 * @brief  Constructor initializes cchttprequest and stuff
 *
 */
MinXmlHttpRequest::MinXmlHttpRequest() : onreadystateCallback(NULL), isNetwork(true) {
    
    http_header.clear();
    request_header.clear();
    withCredentialsValue = true;
    cx = ScriptingCore::getInstance()->getGlobalContext();
    cc_request = new cocos2d::extension::CCHttpRequest();
}

/**
 * @brief Destructor cleans up cc_request and stuff
 *
 */
MinXmlHttpRequest::~MinXmlHttpRequest() {

    http_header.clear();
    request_header.clear();

    if (onreadystateCallback != NULL)
    {
        JS_RemoveObjectRoot(cx, &onreadystateCallback);
    }
    
    if (cc_request) {
        // We don't need to release cc_request here since it will be released in the http callback.
//        cc_request->release();
    }

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
    MinXmlHttpRequest* req = new MinXmlHttpRequest();
    req->autorelease();
    
    js_proxy_t *p;
    jsval out;
    
    JSObject *obj = JS_NewObject(cx, &MinXmlHttpRequest::js_class, MinXmlHttpRequest::js_proto, MinXmlHttpRequest::js_parent);
    
    if (obj) {
        JS_SetPrivate(obj, req);
        out = OBJECT_TO_JSVAL(obj);
    }

    JS_SET_RVAL(cx, vp, out);
    p =jsb_new_proxy(req, obj);
    
    JS_AddNamedObjectRoot(cx, &p->obj, "XMLHttpRequest");
    return JS_TRUE;
}

/**
 *  @brief  get Callback function for Javascript
 * 
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, onreadystatechange)
{
    if (onreadystateCallback) {
        
        JSString *tmpstr = JS_NewStringCopyZ(cx, "1");
        jsval tmpval = STRING_TO_JSVAL(tmpstr);
        JS_SetProperty(cx, onreadystateCallback, "readyState", &tmpval);
        
        jsval out = OBJECT_TO_JSVAL(onreadystateCallback);
        vp.set(out);
        
    } else {
        vp.set(JSVAL_NULL);
    }
    return JS_TRUE;
}

/**
 *  @brief Set Callback function coming from Javascript
 *
 *
 */
JS_BINDED_PROP_SET_IMPL(MinXmlHttpRequest, onreadystatechange)
{
    jsval callback = vp.get();
    if (callback != JSVAL_NULL) {
        onreadystateCallback = JSVAL_TO_OBJECT(callback);
        JS_AddNamedObjectRoot(cx, &onreadystateCallback, "onreadystateCallback");
    }
    return JS_TRUE;
}

/**
 *  @brief upload getter - TODO
 *
 *  Placeholder for further implementations!!
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, upload)
{
    vp.set(JSVAL_NULL);
    return JS_TRUE;
}

/**
 *  @brief upload setter - TODO
 *
 *  Placeholder for further implementations
 */
JS_BINDED_PROP_SET_IMPL(MinXmlHttpRequest, upload)
{
    vp.set(JSVAL_NULL);
    return JS_TRUE;
}

/**
 *  @brief timeout getter - TODO
 *
 *  Placeholder for further implementations
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, timeout)
{
    vp.set(INT_TO_JSVAL(timeout));
    return JS_TRUE;
}

/**
 *  @brief timeout setter - TODO
 *
 *  Placeholder for further implementations
 */
JS_BINDED_PROP_SET_IMPL(MinXmlHttpRequest, timeout)
{
    jsval timeout_ms = vp.get();
    
    timeout = JSVAL_TO_INT(timeout_ms);
    //curl_easy_setopt(curlHandle, CURLOPT_CONNECTTIMEOUT_MS, timeout);
    return JS_TRUE;
    
}

/**
 *  @brief  get response type for actual XHR
 *
 *
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, responseType)
{
    JSString* str = JS_NewStringCopyN(cx, "", 0);
    vp.set(STRING_TO_JSVAL(str));
    return JS_TRUE;
}

/**
 *  @brief  responseXML getter - TODO
 *
 *  Placeholder for further implementation.
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, responseXML)
{
    vp.set(JSVAL_NULL);
    return JS_TRUE;
}

/**
 *  @brief  set response type for actual XHR
 *
 *
 */
JS_BINDED_PROP_SET_IMPL(MinXmlHttpRequest, responseType)
{
    jsval type = vp.get();
    if (type.isString()) {
        JSString* str = type.toString();
        JSBool equal;
        JS_StringEqualsAscii(cx, str, "text", &equal);
        if (equal) {
            responseType = kRequestResponseTypeString;
            return JS_TRUE;
        }
        JS_StringEqualsAscii(cx, str, "arraybuffer", &equal);
        if (equal) {
            responseType = kRequestResponseTypeArrayBuffer;
            return JS_TRUE;
        }
        JS_StringEqualsAscii(cx, str, "json", &equal);
        if (equal) {
            responseType = kRequestResponseTypeJSON;
            return JS_TRUE;
        }
        // ignore the rest of the response types for now
        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid response type");
    return JS_FALSE;
}

/**
 * @brief get readyState for actual XHR
 *
 *
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, readyState)
{
    vp.set(INT_TO_JSVAL(readyState));
    return JS_TRUE;
}

/**
 *  @brief get status for actual XHR
 *
 *
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, status)
{
    vp.set(INT_TO_JSVAL(status));
    return JS_TRUE;
}

/**
 *  @brief get statusText for actual XHR
 *
 *
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, statusText)
{
    JSString* str = JS_NewStringCopyZ(cx, statusText.c_str());//, dataSize);
    
    if (str) {
        vp.set(STRING_TO_JSVAL(str));
        return JS_TRUE;
    } else {
        JS_ReportError(cx, "Error trying to create JSString from data");
        return JS_FALSE;
    }
}

/**
 *  @brief  get value of withCredentials property.
 *
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, withCredentials)
{
    vp.set(BOOLEAN_TO_JSVAL(withCredentialsValue));
    return JS_TRUE;
}

/**
 *  withCredentials - set value of withCredentials property.
 *
 */
JS_BINDED_PROP_SET_IMPL(MinXmlHttpRequest, withCredentials)
{
    jsval credential = vp.get();
    if (credential != JSVAL_NULL) {
        withCredentialsValue = JSVAL_TO_BOOLEAN(credential);
    }
    
    return JS_TRUE;
}

/**
 *  @brief  get (raw) responseText
 *
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, responseText)
{
    JSString* str = JS_NewStringCopyZ(cx, data.str().c_str());//, dataSize);

    if (str) {
        vp.set(STRING_TO_JSVAL(str));
        //JS_ReportError(cx, "Result: %s", data.str().c_str());
        return JS_TRUE;
    } else {
        JS_ReportError(cx, "Error trying to create JSString from data");
        return JS_FALSE;
    }
}

/**
 *  @brief get response of latest XHR
 *
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, response)
{
    
    if (responseType == kRequestResponseTypeJSON) {
        jsval outVal;
        
        JSString* str = JS_NewStringCopyZ(cx, data.str().c_str());//, dataSize);
        if (JS_ParseJSON(cx, JS_GetStringCharsZ(cx, str), dataSize, &outVal)) {
            
            vp.set(outVal);
            return JS_TRUE;
        }
    } else if (responseType == kRequestResponseTypeArrayBuffer) {
        JSObject* tmp = JS_NewArrayBuffer(cx, dataSize);
        uint8_t* tmpData = JS_GetArrayBufferData(tmp);
        data.read((char*)tmpData, dataSize);
        jsval outVal = OBJECT_TO_JSVAL(tmp);

        vp.set(outVal);
        return JS_TRUE;
    }
    // by default, return text
    return _js_get_responseText(cx, id, vp);
}

/**
 *  @brief initialize new xhr.
 *
 */
JS_BINDED_FUNC_IMPL(MinXmlHttpRequest, open)
{
    
    if (argc >= 2) {
        jsval* argv = JS_ARGV(cx, vp);
        const char* method;
        const char* urlstr;
        JSBool async = true;
        JSString* jsMethod = JS_ValueToString(cx, argv[0]);
        JSString* jsURL = JS_ValueToString(cx, argv[1]);
        
        if (argc > 2) {
            JS_ValueToBoolean(cx, argv[2], &async);
        }
        
        JSStringWrapper w1(jsMethod);
        JSStringWrapper w2(jsURL);
        method = w1;
        urlstr = w2;
        
        url = urlstr;
        meth = method;
        readyState = 1;
        isAsync = async;
        
        if (url.length() > 5 && url.compare(url.length() - 5, 5, ".json") == 0) {
            responseType = kRequestResponseTypeJSON;
        }

        if (meth.compare("post") == 0 || meth.compare("POST") == 0) {
            cc_request->setRequestType(cocos2d::extension::CCHttpRequest::kHttpPost);
        }
        else {
            cc_request->setRequestType(cocos2d::extension::CCHttpRequest::kHttpGet);
        }
        
        cc_request->setUrl(url.c_str());
        
        isNetwork = true;
        readyState = OPENED;
        
        return JS_TRUE;
    }
    
    JS_ReportError(cx, "invalid call: %s", __FUNCTION__);
    return JS_FALSE;
    
}

/**
 *  @brief  send xhr
 *
 */
JS_BINDED_FUNC_IMPL(MinXmlHttpRequest, send)
{

    JSString *str = NULL;
    std::string data;
    
    // Clean up header map. New request, new headers!
    http_header.clear();
    if (argc == 1) {
        if (!JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "S", &str)) {
            return JS_FALSE;
        };
        JSStringWrapper strWrap(str);
        data = strWrap.get();
    }


    if (data.length() > 0 && (meth.compare("post") == 0 || meth.compare("POST") == 0)) {
        cc_request->setRequestData(data.c_str(), data.length());
    }

    _setHttpRequestHeader();
    _sendRequest(cx);

    return JS_TRUE;
}

/**
 *  @brief abort function Placeholder!
 *
 */
JS_BINDED_FUNC_IMPL(MinXmlHttpRequest, abort)
{
    return JS_TRUE;
}

/**
 *  @brief Get all response headers as a string
 *
 */
JS_BINDED_FUNC_IMPL(MinXmlHttpRequest, getAllResponseHeaders)
{
    stringstream responseheaders;
    string responseheader;
    
    for (std::map<string,string>::iterator it=http_header.begin(); it!=http_header.end(); ++it) {
        responseheaders << it->first << ": " << it->second << "\n";
    }
    
    responseheader = responseheaders.str();
    
    JSString* str = JS_NewStringCopyZ(cx, responseheader.c_str());
    
    if (str) {
        JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(str));
        return JS_TRUE;
    } else {
        JS_ReportError(cx, "Error trying to create JSString from data");
        return JS_FALSE;
    }
    
    return JS_TRUE;
}

/**
 *  @brief Get all response headers as a string
 *
 */
JS_BINDED_FUNC_IMPL(MinXmlHttpRequest, getResponseHeader)
{
    
    JSString *header_value;
    
    if (!JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "S", &header_value)) {
        return JS_FALSE;
    };
    
    std::string data;
    JSStringWrapper strWrap(header_value);
    data = strWrap.get();
    
    stringstream streamdata;
    
    streamdata << data;

    string value = streamdata.str();
    
    map<string, string>::iterator iter = http_header.find(value);
    if (iter != http_header.end() ) {
        
        JSString *js_ret_val = JS_NewStringCopyZ(cx, iter->second.c_str());
        
        // iter->second
        JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(js_ret_val));
        return JS_TRUE;
    }
    else {
        JS_SET_RVAL(cx, vp, JSVAL_NULL);
        return JS_TRUE;
    }
    
}

/**
 *  @brief Set the given Fields to request Header.
 *
 *
 */
JS_BINDED_FUNC_IMPL(MinXmlHttpRequest, setRequestHeader)
{
    
    if (argc >= 2) {
        jsval* argv = JS_ARGV(cx, vp);
        const char* field;
        const char* value;
        
        JSString* jsField = JS_ValueToString(cx, argv[0]);
        JSString* jsValue = JS_ValueToString(cx, argv[1]);
        
        JSStringWrapper w1(jsField);
        JSStringWrapper w2(jsValue);
        field = w1;
        value = w2;
        
        // Populate the request_header map.
        _setRequestHeader(field, value);
        
        return JS_TRUE;
    }
     
    return JS_FALSE;
    
}

/**
 * @brief overrideMimeType function - TODO!
 *
 * Just a placeholder for further implementations.
 */
JS_BINDED_FUNC_IMPL(MinXmlHttpRequest, overrideMimeType)
{
    return JS_TRUE;
}

/**
 *  @brief destructor for Javascript
 *
 */
static void basic_object_finalize(JSFreeOp *freeOp, JSObject *obj) {
    CCLOG("basic_object_finalize %p ...", obj);
}

/**
 *  @brief Register XMLHttpRequest to be usable in JS and add properties and Mehtods.
 *  @param cx   Global Spidermonkey JS Context.
 *  @param global   Global Spidermonkey Javascript object.
 */
void MinXmlHttpRequest::_js_register(JSContext *cx, JSObject *global) {
    
    JSClass js_class = {
        "XMLHttpRequest", JSCLASS_HAS_PRIVATE, JS_PropertyStub,
        JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
        JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub,
        basic_object_finalize, JSCLASS_NO_OPTIONAL_MEMBERS
    };
    
    MinXmlHttpRequest::js_class = js_class;
    static JSPropertySpec props[] = {
        JS_BINDED_PROP_DEF_ACCESSOR(MinXmlHttpRequest, onreadystatechange),
        JS_BINDED_PROP_DEF_ACCESSOR(MinXmlHttpRequest, responseType),
        JS_BINDED_PROP_DEF_ACCESSOR(MinXmlHttpRequest, withCredentials),
        JS_BINDED_PROP_DEF_GETTER(MinXmlHttpRequest, readyState),
        JS_BINDED_PROP_DEF_GETTER(MinXmlHttpRequest, status),
        JS_BINDED_PROP_DEF_GETTER(MinXmlHttpRequest, statusText),
        JS_BINDED_PROP_DEF_GETTER(MinXmlHttpRequest, responseText),
        JS_BINDED_PROP_DEF_GETTER(MinXmlHttpRequest, responseXML),
        JS_BINDED_PROP_DEF_GETTER(MinXmlHttpRequest, response),
        {0, 0, 0, 0, 0}
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
    
    MinXmlHttpRequest::js_parent = NULL;
    MinXmlHttpRequest::js_proto = JS_InitClass(cx, global, NULL, &MinXmlHttpRequest::js_class , MinXmlHttpRequest::_js_constructor, 0, props, funcs, NULL, NULL);
    
}

