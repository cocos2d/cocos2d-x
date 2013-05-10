//
//  XMLHTTPRequest.cpp
//  XMLHttpRequest
//
//  Created by Zynga on May, 6th.
//
//  Heaviliy based on: https://github.com/funkaster/FakeWebGL/blob/master/FakeWebGL/WebGL/XMLHTTPRequest.cpp
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

#pragma mark - MinXmlHttpRequest

JSContext *cx;

struct thread_args
{
    MinXmlHttpRequest *obj;
    JSContext *cx;
};

/**
 *  gotHeader - Callback for curl request to retrieve header
 *
 */
size_t MinXmlHttpRequest::gotHeader(void* ptr, size_t size, size_t nmemb, void *userdata) {
	MinXmlHttpRequest* req = (MinXmlHttpRequest*)userdata;
	string header((const char*)ptr, size * nmemb);
	req->_gotHeader(header);
	return size * nmemb;
}

/**
 *  gotData - Callback for curl request to retrieve data
 *
 */
size_t MinXmlHttpRequest::gotData(char* ptr, size_t size, size_t nmemb, void *userdata) {
	MinXmlHttpRequest* req = (MinXmlHttpRequest*)userdata;
	req->_gotData(ptr, size * nmemb);
	return size * nmemb;
}

/**
 *  _gotData - Implementation for data retrieving.
 *
 */
void MinXmlHttpRequest::_gotData(char* ptr, size_t len) {
	data.write(ptr, len);
}

/**
 *  _gotHeader - Implementation for header retrieving.
 *
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
        http_value.erase(std::remove(http_value.begin(), http_value.end(), '\n'), http_value.end());
        
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
 *  _setRequestHeader - Set Request header for next call.
 *
 *
 */
void MinXmlHttpRequest::_setRequestHeader(const char* field, const char* value) {
    
    stringstream header_s;
    stringstream value_s;
    string header;
    
    map<string, string>::iterator iter = request_header.find(field);
    
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
 * _setCurlRequestHeader - If headers has been set, pass them to curl.
 *
 */
void MinXmlHttpRequest::_setCurlRequestHeader() {
    
    struct curl_slist *header = NULL;

    for (std::map<string,string>::iterator it = request_header.begin(); it != request_header.end(); ++it) {
        
        stringstream value_s;
        const char* value;
        
        value_s << it->first << ": " << it->second;
        value = value_s.str().c_str();
        
        curl_slist_append(header, value);
        
    }
    
    if (header != NULL) {
        curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headers);
    }
    
}

void MinXmlHttpRequest::handle_requestResponse(MinXmlHttpRequest *sender, cocos2d::extension::CCHttpResponse *response) {

    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        CCLog("%s completed", response->getHttpRequest()->getTag());
    }
    
    int statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    CCLog("response code: %d", statusCode);
    
    if (!response->isSucceed())
    {
        CCLog("response failed");
        CCLog("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    // store data
    std::vector<char> *buffer = response->getResponseData();
    char* concatenated = (char*) malloc(buffer->size() + 1);
    std::string s2(buffer->begin(), buffer->end());
    
    strcpy(concatenated, s2.c_str());
    
    CCLog("===");
    CCLog(concatenated);
    
    if (statusCode == 200)
    {
        //Succeeded
        status = 200;
        readyState = DONE;
    }
    else
    {
        //Failed
        status = 0;
    }
    
    js_proxy_t * p;
    void* ptr = (void*)this;
    JS_GET_PROXY(p, ptr);
    
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
 * _sendCurlRequest - Send out request and fire callback when done.
 *
 */
void MinXmlHttpRequest::_sendRequest(JSContext *cx) {
    
    cc_request->setResponseCallback(this, cocos2d::extension::SEL_HttpResponse(&MinXmlHttpRequest::handle_requestResponse));
    cocos2d::extension::CCHttpClient::getInstance()->send(cc_request);
    cc_request->release();
        // State has been changed. Run the callback function!
    if (onreadystateCallback) {
        JS_IsExceptionPending(cx) && JS_ReportPendingException(cx);
        jsval fval = OBJECT_TO_JSVAL(onreadystateCallback);
        jsval out;
        JS_CallFunctionValue(cx, NULL, fval, 0, NULL, &out);
    }
    
    //curl_easy_cleanup(curlHandle);
    
}

/**
 * MinXmlHttpRequest - Constructor initializes curl and stuff
 *
 */
MinXmlHttpRequest::MinXmlHttpRequest() : onreadystateCallback(cx, NULL), isNetwork(true) {
    
    http_header.clear();
    request_header.clear();
    headers = NULL;
    
    // curlHandle = curl_easy_init();
    cc_request = new cocos2d::extension::CCHttpRequest();
    
	/*curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, MinXmlHttpRequest::gotData);
	curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, this);
	curl_easy_setopt(curlHandle, CURLOPT_HEADERFUNCTION, MinXmlHttpRequest::gotHeader);
	curl_easy_setopt(curlHandle, CURLOPT_WRITEHEADER, this);
    curl_easy_setopt(curlHandle, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curlHandle, CURLOPT_SSL_VERIFYHOST, 0L);*/
    
}

/**
 * MinXmlHttpRequest - Destructor cleans up curl and stuff
 *
 */
MinXmlHttpRequest::~MinXmlHttpRequest() {

    http_header.clear();
    request_header.clear();

    if (cc_request) {
        cc_request->release();
    }
    /*if (curlHandle) {
		curl_easy_cleanup(curlHandle);
	}*/
}

/**
 *  Initialize Object and needed properties.
 *
 */
JS_BINDED_CLASS_GLUE_IMPL(MinXmlHttpRequest);

/**
 *  Implementation for the Javascript Constructor
 *
 */
JS_BINDED_CONSTRUCTOR_IMPL(MinXmlHttpRequest)
{
    MinXmlHttpRequest* req = new MinXmlHttpRequest();
    js_proxy_t *p;
    jsval out;
    
    JSObject *obj = JS_NewObject(cx, &MinXmlHttpRequest::js_class, MinXmlHttpRequest::js_proto, MinXmlHttpRequest::js_parent);
    
    if (obj) {
        JS_SetPrivate(obj, req);
        out = OBJECT_TO_JSVAL(obj);
    }

    JS_SET_RVAL(cx, vp, out);
    JS_NEW_PROXY(p, req, obj);
    
    JS_AddNamedObjectRoot(cx, &p->obj, "XMLHttpRequest");
    
    return JS_TRUE;
}

/**
 *  onreadystatechange - get Callback function for Javascript
 *
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
 *  onreadystatechange - Set Callback function coming from Javascript
 *
 *
 */
JS_BINDED_PROP_SET_IMPL(MinXmlHttpRequest, onreadystatechange)
{
    jsval callback = vp.get();
    if (callback != JSVAL_NULL) {
        onreadystateCallback = JSVAL_TO_OBJECT(callback);
    }
    return JS_TRUE;
}

/**
 *  upload - TODO
 *
 *  Placeholder for further implementations
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, upload)
{
    vp.set(JSVAL_NULL);
    return JS_TRUE;
}

/**
 *  upload - TODO
 *
 *  Placeholder for further implementations
 */
JS_BINDED_PROP_SET_IMPL(MinXmlHttpRequest, upload)
{
    vp.set(JSVAL_NULL);
    return JS_TRUE;
}

/**
 *  timeout - TODO
 *
 *  Placeholder for further implementations
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, timeout)
{
    vp.set(INT_TO_JSVAL(timeout));
    return JS_TRUE;
}

/**
 *  timeout - TODO
 *
 *  Placeholder for further implementations
 */
JS_BINDED_PROP_SET_IMPL(MinXmlHttpRequest, timeout)
{
    jsval timeout_ms = vp.get();
    
    timeout = JSVAL_TO_INT(timeout_ms);
    curl_easy_setopt(curlHandle, CURLOPT_CONNECTTIMEOUT_MS, timeout);
    return JS_TRUE;
    
}

/**
 *  responseType - get response type for actual XHR
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
 *  responseXML - TODO
 *
 *  Placeholder for further implementation.
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, responseXML)
{
    vp.set(JSVAL_NULL);
    return JS_TRUE;
}

/**
 *  responseType - set response type for actual XHR
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
 *  readyState - get readyState for actual XHR
 *
 *
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, readyState)
{
    vp.set(INT_TO_JSVAL(readyState));
    return JS_TRUE;
}

/**
 *  status - get status for actual XHR
 *
 *
 */
JS_BINDED_PROP_GET_IMPL(MinXmlHttpRequest, status)
{
    vp.set(INT_TO_JSVAL(status));
    return JS_TRUE;
}

/**
 *  statusText - get statusText for actual XHR
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
 *  withCredentials - get value of withCredentials property.
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
 *  responseText - get (raw) responseText
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
 *  response - get response of latest XHR
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
 *  open - initialize new xhr.
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
        /*if ((url.length() > 7 && url.compare(0, 7, "http://") == 0) ||
            (url.length() > 8 && url.compare(0, 8, "https://") == 0))
        {*/
        
        if (meth.compare("post") == 0 || meth.compare("POST") == 0) {
            cc_request->setRequestType(cocos2d::extension::CCHttpRequest::kHttpPost);
            //curl_easy_setopt(curlHandle, CURLOPT_POST, 1);
        }
        else {
            cc_request->setRequestType(cocos2d::extension::CCHttpRequest::kHttpGet);
            //curl_easy_setopt(curlHandle, CURLOPT_POST, 0);
        }
        
        cc_request->setUrl(url.c_str());
        //curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
        
        isNetwork = true;
        readyState = OPENED;
        
        return JS_TRUE;
    }
    
    JS_ReportError(cx, "invalid call: %s", __FUNCTION__);
    return JS_FALSE;
    
}

/**
 *  send - send xhr
 *
 */
JS_BINDED_FUNC_IMPL(MinXmlHttpRequest, send)
{

    JSString *str;
    pthread_t thread;
    int iret;
    struct thread_args *thread_arguments;//(struct Node *)malloc(sizeof(struct Node))
    
    thread_arguments = (struct thread_args *)malloc(sizeof(struct thread_args));
    
    // Clean up header map. New request, new headers!
    http_header.clear();
    
    if (!JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "S", &str)) {
        return JS_FALSE;
    };
        
    if (meth.compare("post") == 0 || meth.compare("POST") == 0) {
        
        char *data = JS_EncodeString(cx, str);
        cc_request->setRequestData(data, strlen(data));
        //curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, data);

        
    }
    
    // Set Headers if needed.
    //_setCurlRequestHeader();
    _sendRequest(cx);
        
    return JS_TRUE;
}

/**
 *  getAllResponseHeaders - Get all response headers as a string
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
 *  getResponseHeader - Get all response headers as a string
 *
 */
JS_BINDED_FUNC_IMPL(MinXmlHttpRequest, getResponseHeader)
{
    
    JSString *header_value;
    
    if (!JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "S", &header_value)) {
        return JS_FALSE;
    };
    
    char *data = JS_EncodeString(cx, header_value);
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
 *  setRequestHeader - Set the given Fields to request Header.
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
 * overrideMimeType - TODO!
 *
 * Just a placeholder for further implementations.
 */
JS_BINDED_FUNC_IMPL(MinXmlHttpRequest, overrideMimeType)
{
    
    return JS_TRUE;
    
}

/**
 *  destructor for Javascript
 *
 */
void basic_object_finalize(JSFreeOp *freeOp, JSObject *obj) {
    JSBindedObject* native = dynamic_cast<JSBindedObject*>((JSBindedObject*)JS_GetPrivate(obj));
	if (native) {
		delete native;
	}
    return;
}

/**
 *  getGlobalContext - retrieve the global Javascript Context object.
 *
 */
JSContext* getGlobalContext() {
	return cx;
}

/**
 *  _js_register - Register XMLHttpRequest to be usable in JS and add properties and Mehtods.
 *
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
        JS_BINDED_PROP_DEF_GETTER(MinXmlHttpRequest, response),
        {0, 0, 0, 0, 0}
    };
    
    static JSFunctionSpec funcs[] = {
        JS_BINDED_FUNC_FOR_DEF(MinXmlHttpRequest, open),
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

