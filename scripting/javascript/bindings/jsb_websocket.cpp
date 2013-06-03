/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
Copyright (c) 2013 James Chen

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

#include "jsb_websocket.h"
#include "cocos2d.h"
#include "WebSocket.h"
#include "spidermonkey_specifics.h"
#include "ScriptingCore.h"
#include "cocos2d_specifics.hpp"

USING_NS_CC_EXT;

/*
 [Constructor(in DOMString url, in optional DOMString protocols)]
 [Constructor(in DOMString url, in optional DOMString[] protocols)]
 interface WebSocket {
 readonly attribute DOMString url;
 
 // ready state
 const unsigned short CONNECTING = 0;
 const unsigned short OPEN = 1;
 const unsigned short CLOSING = 2;
 const unsigned short CLOSED = 3;
 readonly attribute unsigned short readyState;
 readonly attribute unsigned long bufferedAmount;
 
 // networking
 attribute Function onopen;
 attribute Function onmessage;
 attribute Function onerror;
 attribute Function onclose;
 readonly attribute DOMString protocol;
 void send(in DOMString data);
 void close();
 };
 WebSocket implements EventTarget;
 */

class JSB_WebSocketDelegate : public WebSocket::Delegate
{
public:
    
    virtual void onOpen(WebSocket* ws)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, ws);
        if (!p) return;
        
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JSObject* jsobj = JS_NewObject(cx, NULL, NULL, NULL);
        jsval vp = c_string_to_jsval(cx, "open");
        JS_SetProperty(cx, jsobj, "type", &vp);
        
        jsval args = OBJECT_TO_JSVAL(jsobj);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "onopen", 1, &args);
    }
    
    virtual void onMessage(WebSocket* ws, const WebSocket::Data& data)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, ws);
        if (!p) return;
        
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JSObject* jsobj = JS_NewObject(cx, NULL, NULL, NULL);
        jsval vp = c_string_to_jsval(cx, "message");
        JS_SetProperty(cx, jsobj, "type", &vp);
        
        jsval args = OBJECT_TO_JSVAL(jsobj);
        
        if (data.isBinary)
        {// data is binary
            JSObject* buffer = JS_NewArrayBuffer(cx, data.len);
            uint8_t* bufdata = JS_GetArrayBufferData(buffer);
            memcpy((void*)bufdata, (void*)data.bytes, data.len);
            jsval dataVal = OBJECT_TO_JSVAL(buffer);
            JS_SetProperty(cx, jsobj, "data", &dataVal);
        }
        else
        {// data is string
            jsval dataVal = c_string_to_jsval(cx, data.bytes);
            JS_SetProperty(cx, jsobj, "data", &dataVal);
        }

        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "onmessage", 1, &args);
    }
    
    virtual void onClose(WebSocket* ws)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, ws);
        if (!p) return;
        
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JSObject* jsobj = JS_NewObject(cx, NULL, NULL, NULL);
        jsval vp = c_string_to_jsval(cx, "close");
        JS_SetProperty(cx, jsobj, "type", &vp);
        
        jsval args = OBJECT_TO_JSVAL(jsobj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "onclose", 1, &args);

        js_proxy_t* jsproxy;
        JS_GET_NATIVE_PROXY(jsproxy, p->obj);
        JS_RemoveObjectRoot(cx, &jsproxy->obj);
        JS_REMOVE_PROXY(p, jsproxy);
        CC_SAFE_DELETE(ws);
    }
    
    virtual void onError(WebSocket* ws, const WebSocket::ErrorCode& error)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, ws);
        if (!p) return;
        
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JSObject* jsobj = JS_NewObject(cx, NULL, NULL, NULL);
        jsval vp = c_string_to_jsval(cx, "error");
        JS_SetProperty(cx, jsobj, "type", &vp);
        
        jsval args = OBJECT_TO_JSVAL(jsobj);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "onerror", 1, &args);
    }
    
    void setJSDelegate(JSObject* pJSDelegate)
    {
        m_pJSDelegate = pJSDelegate;
    }
private:
    JSObject* m_pJSDelegate;
};

JSClass  *js_cocos2dx_websocket_class;
JSObject *js_cocos2dx_websocket_prototype;

void js_cocos2dx_WebSocket_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOG("jsbindings: finalizing JS object %p (WebSocket)", obj);
}

JSBool js_cocos2dx_extension_WebSocket_send(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	WebSocket* cobj = (WebSocket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");

	if(argc == 1){
        do
        {
            if (JSVAL_IS_STRING(argv[0]))
            {
                std::string data;
                jsval_to_std_string(cx, argv[0], &data);
                cobj->send(data);
                break;
            }

            if (argv[0].isObject())
            {
                uint8_t *bufdata = NULL;
                uint32_t len = 0;
                
                JSObject* jsobj = JSVAL_TO_OBJECT(argv[0]);
                if (JS_IsArrayBufferObject(jsobj))
                {
                    bufdata = JS_GetArrayBufferData(jsobj);
                    len = JS_GetArrayBufferByteLength(jsobj);
                }
                else if (JS_IsArrayBufferViewObject(jsobj))
                {
                    bufdata = (uint8_t*)JS_GetArrayBufferViewData(jsobj);
                    len = JS_GetArrayBufferViewByteLength(jsobj);
                }
                
                if (bufdata && len > 0)
                {
                    cobj->send(bufdata, len);
                    break;
                }
            }
            
            JS_ReportError(cx, "data type to be sent is unsupported.");

        } while (0);
        
		JS_SET_RVAL(cx, vp, JSVAL_VOID);

		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_TRUE;
}

JSBool js_cocos2dx_extension_WebSocket_close(JSContext *cx, uint32_t argc, jsval *vp){
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	WebSocket* cobj = (WebSocket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
	if(argc == 0){
		cobj->close();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}

JSBool js_cocos2dx_extension_WebSocket_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    
	if (argc == 1 || argc == 2)
    {

		std::string url;
		
		do {
			JSBool ok = jsval_to_std_string(cx, argv[0], &url);
			JSB_PRECONDITION2( ok, cx, JS_FALSE, "Error processing arguments");
		} while (0);
        
		JSObject *obj = JS_NewObject(cx, js_cocos2dx_websocket_class, js_cocos2dx_websocket_prototype, NULL);
		
        
		cocos2d::extension::WebSocket* cobj = new cocos2d::extension::WebSocket();
        JSB_WebSocketDelegate* delegate = new JSB_WebSocketDelegate();
        delegate->setJSDelegate(obj);
        
        if (argc == 2)
        {
            std::vector<std::string> protocols;
            
            if (JSVAL_IS_STRING(argv[1]))
            {
                std::string protocol;
                do {
                    JSBool ok = jsval_to_std_string(cx, argv[1], &protocol);
                    JSB_PRECONDITION2( ok, cx, JS_FALSE, "Error processing arguments");
                } while (0);
                protocols.push_back(protocol);
            }
            else if (argv[1].isObject())
            {
                JSBool ok = JS_TRUE;
                JSObject* arg2 = JSVAL_TO_OBJECT(argv[1]);
                JSB_PRECONDITION(JS_IsArrayObject( cx, arg2 ),  "Object must be an array");
                
                uint32_t len = 0;
                JS_GetArrayLength(cx, arg2, &len);
                
                for( uint32_t i=0; i< len;i++ )
                {
                    jsval valarg;
                    JS_GetElement(cx, arg2, i, &valarg);
                    std::string protocol;
                    do {
                        ok = jsval_to_std_string(cx, valarg, &protocol);
                        JSB_PRECONDITION2( ok, cx, JS_FALSE, "Error processing arguments");
                    } while (0);
                    
                    protocols.push_back(protocol);
                }
            }
            cobj->init(*delegate, url, &protocols);
        }
        else
        {
            cobj->init(*delegate, url);
        }
        
        
        JS_DefineProperty(cx, obj, "URL", argv[0]
                          , NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_READONLY);
        
		//protocol not support yet (always return "")
		JS_DefineProperty(cx, obj, "protocol", c_string_to_jsval(cx, "")
                          , NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_READONLY);
        
        // link the native object with the javascript object
		js_proxy_t *p;
		JS_NEW_PROXY(p, cobj, obj);
        JS_AddNamedObjectRoot(cx, &p->obj, "WebSocket");
        
        JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return JS_TRUE;
	}
    
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}

static JSBool js_cocos2dx_extension_WebSocket_get_readyState(JSContext *cx, JSHandleObject obj, JSHandleId id, JSMutableHandleValue vp)
{
    JSObject* jsobj = obj.get();
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, jsobj);
	WebSocket* cobj = (WebSocket *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (cobj) {
        vp.set(INT_TO_JSVAL((int)cobj->getReadyState()));
        return JS_TRUE;
    } else {
        JS_ReportError(cx, "Error: WebSocket instance is invalid.");
        return JS_FALSE;
    }
}

void register_jsb_websocket(JSContext *cx, JSObject *global) {
    
    js_cocos2dx_websocket_class = (JSClass *)calloc(1, sizeof(JSClass));
    js_cocos2dx_websocket_class->name = "WebSocket";
    js_cocos2dx_websocket_class->addProperty = JS_PropertyStub;
    js_cocos2dx_websocket_class->delProperty = JS_PropertyStub;
    js_cocos2dx_websocket_class->getProperty = JS_PropertyStub;
    js_cocos2dx_websocket_class->setProperty = JS_StrictPropertyStub;
    js_cocos2dx_websocket_class->enumerate = JS_EnumerateStub;
    js_cocos2dx_websocket_class->resolve = JS_ResolveStub;
    js_cocos2dx_websocket_class->convert = JS_ConvertStub;
    js_cocos2dx_websocket_class->finalize = js_cocos2dx_WebSocket_finalize;
    js_cocos2dx_websocket_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] = {
        {"readyState", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_cocos2dx_extension_WebSocket_get_readyState), NULL},
        {0, 0, 0, 0, 0}
    };
    
    static JSFunctionSpec funcs[] = {
        JS_FN("send",js_cocos2dx_extension_WebSocket_send, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("close",js_cocos2dx_extension_WebSocket_close, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    
    static JSFunctionSpec st_funcs[] = {
        JS_FS_END
    };
    
    js_cocos2dx_websocket_prototype = JS_InitClass(
                                                cx, global,
                                                NULL,
                                                js_cocos2dx_websocket_class,
                                                js_cocos2dx_extension_WebSocket_constructor, 0, // constructor
                                                properties,
                                                funcs,
                                                NULL, // no static properties
                                                st_funcs);
    
    JSObject* jsclassObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return WebSocket; })()"));

    JS_DefineProperty(cx, jsclassObj, "CONNECTING", INT_TO_JSVAL((int)WebSocket::kStateConnecting)
                      , NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_READONLY);
	JS_DefineProperty(cx, jsclassObj, "OPEN", INT_TO_JSVAL((int)WebSocket::kStateOpen)
                      , NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_READONLY);
	JS_DefineProperty(cx, jsclassObj, "CLOSING", INT_TO_JSVAL((int)WebSocket::kStateClosing)
                      , NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_READONLY);
	JS_DefineProperty(cx, jsclassObj, "CLOSED", INT_TO_JSVAL((int)WebSocket::kStateClosed)
                      , NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_READONLY);
    
    // make the class enumerable in the registered namespace
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "WebSocket", JSPROP_ENUMERATE | JSPROP_READONLY, &found);
}


