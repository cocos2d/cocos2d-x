/*
 * Created by Chris Hannon 2014 http://www.channon.us
 * Copyright (c) 2014 Chukong Technologies Inc.
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

#include "jsb_socketio.h"
#include "jsb_helper.h"
#include "cocos2d.h"
#include "network/WebSocket.h"
#include "network/SocketIO.h"
#include "spidermonkey_specifics.h"
#include "ScriptingCore.h"
#include "cocos2d_specifics.hpp"

using namespace cocos2d::network;

class JSB_SIOEvent : public cocos2d::Object {
public:
    JSB_SIOEvent();
    virtual ~JSB_SIOEvent();
    void setJSCallbackFunc(jsval obj);
    const jsval& getJSCallbackFunc() const;
    
private:
    jsval _jsCallback;
    jsval _extraData;

};

JSB_SIOEvent::JSB_SIOEvent()
: _jsCallback(JSVAL_VOID), _extraData(JSVAL_VOID)
{

}

JSB_SIOEvent::~JSB_SIOEvent()
{
    JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
    JS_RemoveValueRoot(cx, &_jsCallback);
}

void JSB_SIOEvent::setJSCallbackFunc(jsval func) {
    _jsCallback = func;
    JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
    // Root the callback function.
    JS_AddNamedValueRoot(cx, &_jsCallback, "JSB_SIOEvent_callback_func");
}

const jsval& JSB_SIOEvent::getJSCallbackFunc() const
{
    return _jsCallback;
}

//c++11 map to callbacks
typedef std::unordered_map<std::string, JSB_SIOEvent> JSB_SIOEventRegistry;

class JSB_SocketIODelegate : public SocketIO::SIODelegate {
public:

    JSB_SocketIODelegate() {
        JSB_SIOEvent tmp;
        std::string s = "default";
        _eventRegistry[s] = tmp;
    }
    
    virtual void onConnect(SIOClient* client) {
        CCLOG("JSB SocketIO::SIODelegate->onConnect method called from native");

        this->fireEventToScript(client, "connect", "");

    }

    virtual void onMessage(SIOClient* client, const std::string& data) {
        CCLOG("JSB SocketIO::SIODelegate->onMessage method called from native with data: %s", data.c_str());
        
        this->fireEventToScript(client, "message", data);

    }

    virtual void onClose(SIOClient* client) {
        CCLOG("JSB SocketIO::SIODelegate->onClose method called from native");
        
        this->fireEventToScript(client, "disconnect", "");

    }

    virtual void onError(SIOClient* client, const std::string& data) {
        CCLOG("JSB SocketIO::SIODelegate->onError method called from native with data: %s", data.c_str());

        this->fireEventToScript(client, "error", data);

    }

    virtual void fireEventToScript(SIOClient* client, const std::string& eventName, const std::string& data) {
        CCLOG("JSB SocketIO::SIODelegate->fireEventToScript method called from native with name '%s' data: %s", eventName.c_str(), data.c_str());

        js_proxy_t * p = jsb_get_native_proxy(client);
        if (!p) return;

        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();

        jsval args;
        if(data == "") {
            args = JSVAL_NULL;
        } else {
            args = std_string_to_jsval(cx, data);
        }

        //ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), eventName.c_str(), 1, &args);
        
        JSB_SIOEventRegistry::iterator it = _eventRegistry.find(eventName);
        
        if(it != _eventRegistry.end()) {
            JSB_SIOEvent e = it->second;
            ScriptingCore::getInstance()->executeJSFunctionWithThisObj(OBJECT_TO_JSVAL(p->obj), e.getJSCallbackFunc(), 1, &args);
        }
        
    }

    void setJSDelegate(JSObject* pJSDelegate) {
        _JSDelegate = pJSDelegate;
    }

    void addEvent(const std::string& eventName, JSB_SIOEvent jsevent) {
        _eventRegistry[eventName] = jsevent;
    }

private:
    JSObject* _JSDelegate;

    JSB_SIOEventRegistry _eventRegistry;

};

JSClass  *js_cocos2dx_socketio_class;
JSObject *js_cocos2dx_socketio_prototype;

void js_cocos2dx_SocketIO_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOG("jsbindings: finalizing JS object %p (SocketIO)", obj);
}

bool js_cocos2dx_SocketIO_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS_ReportError(cx, "SocketIO isn't meant to be instantiated, use SocketIO.connect() instead");

    return false;
}

bool js_cocos2dx_SocketIO_connect(JSContext* cx, uint32_t argc, jsval* vp){
    CCLOG("JSB SocketIO.connect method called");

    jsval *argv = JS_ARGV(cx, vp);

    if (argc == 1 || argc == 2) {
        
        std::string url;
        
        do {
            bool ok = jsval_to_std_string(cx, argv[0], &url);
            JSB_PRECONDITION2( ok, cx, false, "Error processing arguments");
        } while (0);
        
        JSB_SocketIODelegate* siodelegate = new JSB_SocketIODelegate();
        
        CCLOG("Calling native SocketIO.connect method");
        SIOClient* ret = SocketIO::connect(*siodelegate, url);
        
        jsval jsret;
        do{
            if (ret) {
                // link the native object with the javascript object
                js_proxy_t *p;
                HASH_FIND_PTR(_native_js_global_ht, &ret, p);
                if(!p) {
                    //previous connection not found, create a new one
                    JSObject *obj = JS_NewObject(cx, js_cocos2dx_socketio_class, js_cocos2dx_socketio_prototype, NULL);
                    p = jsb_new_proxy(ret, obj);
                    JS_AddNamedObjectRoot(cx, &p->obj, "SocketIO");
                    siodelegate->setJSDelegate(p->obj);
                }
                                
                jsret = OBJECT_TO_JSVAL(p->obj);
                
            }
            else{
                jsret = JSVAL_NULL;
            }
        } while(0);
        JS_SET_RVAL(cx, vp, jsret);

        return true;

    }

    JS_ReportError(cx, "JSB SocketIO.connect: Wrong number of arguments");
    return false;
}

bool js_cocos2dx_SocketIO_send(JSContext* cx, uint32_t argc, jsval* vp){
    CCLOG("JSB SocketIO.send method called");

    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SIOClient* cobj = (SIOClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if (argc == 1) {

        std::string payload;
        
        do {
            bool ok = jsval_to_std_string(cx, argv[0], &payload);
            JSB_PRECONDITION2( ok, cx, false, "Error processing arguments");
        } while (0);

        CCLOG("JSB SocketIO send mesage: %s", payload.c_str());

        cobj->send(payload);

        return true;

    }

    JS_ReportError(cx, "Wrong number of arguments");
    return false;

}

bool js_cocos2dx_SocketIO_emit(JSContext* cx, uint32_t argc, jsval* vp){
    CCLOG("JSB SocketIO.emit method called");

    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj); 
    SIOClient* cobj = (SIOClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if (argc == 2) {

        std::string eventName;
        
        do {
            bool ok = jsval_to_std_string(cx, argv[0], &eventName);
            JSB_PRECONDITION2( ok, cx, false, "Error processing arguments");
        } while (0);
        
        std::string payload;
        
        do {
            bool ok = jsval_to_std_string(cx, argv[1], &payload);
            JSB_PRECONDITION2( ok, cx, false, "Error processing arguments");
        } while (0);

        CCLOG("JSB SocketIO emit event '%s' with payload: %s", eventName.c_str(), payload.c_str());

        cobj->emit(eventName, payload);

        return true;

    }

    JS_ReportError(cx, "JSB SocketIO.emit: Wrong number of arguments");
    return false;

}

bool js_cocos2dx_SocketIO_disconnect(JSContext* cx, uint32_t argc, jsval* vp){
    CCLOG("JSB SocketIO.disconnect method called");

    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SIOClient* cobj = (SIOClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if(argc == 0) {

        cobj->disconnect();
        JS_SET_RVAL(cx, vp, JSVAL_NULL);
        return true;
    }

    JS_ReportError(cx, "JSB SocketIO.disconnect: Wrong number of arguments");
    return false;

}

bool js_cocos2dx_SocketIO_close(JSContext* cx, uint32_t argc, jsval* vp){
    CCLOG("JSB SocketIO.close method called");

    if(argc == 0) {

        //This method was previously implemented to take care of the HTTPClient instance not being destroyed properly
        //SocketIO::close();

        JS_SET_RVAL(cx, vp, JSVAL_NULL);
        return true;
    }

    JS_ReportError(cx, "JSB SocketIO.close: Wrong number of arguments");
    return false;

}

static bool _js_set_SIOClient_tag(JSContext* cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp)
{
     CCLOG("JSB SocketIO.setTag method called");
    JSObject* jsobj = obj.get();
    js_proxy_t *proxy = jsb_get_js_proxy(jsobj);
    SIOClient* cobj = (SIOClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    
    if (cobj) {
        std::string out = "";

        jsval_to_std_string(cx, vp, &out);
        cobj->setTag(out.c_str());
        return true;
    } else {
        JS_ReportError(cx, "Error: SocketIO instance is invalid.");
        return false;
    }

}

static bool _js_get_SIOClient_tag(JSContext* cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
    CCLOG("JSB SocketIO.getTag method called");
    JSObject* jsobj = obj.get();
    js_proxy_t *proxy = jsb_get_js_proxy(jsobj);
    SIOClient* cobj = (SIOClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    
    if (cobj) {
        vp.set(std_string_to_jsval(cx, cobj->getTag()));
        return true;
    } else {
        JS_ReportError(cx, "Error: SocketIO instance is invalid.");
        return false;
    }

}


bool js_cocos2dx_SocketIO_on(JSContext* cx, uint32_t argc, jsval* vp){
    CCLOG("JSB SocketIO.on method called");

    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SIOClient* cobj = (SIOClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if(argc == 2) {

        std::string eventName;
        
        do {
            bool ok = jsval_to_std_string(cx, argv[0], &eventName);
            JSB_PRECONDITION2( ok, cx, false, "Error processing arguments");
        } while (0);

        CCLOG("JSB SocketIO eventName to: '%s'", eventName.c_str());

        JSB_SIOEvent tmpCobj; 
        tmpCobj.setJSCallbackFunc(argv[1]);

        ((JSB_SocketIODelegate *)cobj->getDelegate())->addEvent(eventName, tmpCobj);

        JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(proxy->obj));

        JS_SetReservedSlot(proxy->obj, 0, argv[1]);
            
        return true;
    }

    JS_ReportError(cx, "JSB SocketIO.close: Wrong number of arguments");
    return false;

}

void register_jsb_socketio(JSContext *cx, JSObject *global) {

    js_cocos2dx_socketio_class = (JSClass *)calloc(1, sizeof(JSClass));
    js_cocos2dx_socketio_class->name = "SocketIO";
    js_cocos2dx_socketio_class->addProperty = JS_PropertyStub;
    js_cocos2dx_socketio_class->delProperty = JS_DeletePropertyStub;
    js_cocos2dx_socketio_class->getProperty = JS_PropertyStub;
    js_cocos2dx_socketio_class->setProperty = JS_StrictPropertyStub;
    js_cocos2dx_socketio_class->enumerate = JS_EnumerateStub;
    js_cocos2dx_socketio_class->resolve = JS_ResolveStub;
    js_cocos2dx_socketio_class->convert = JS_ConvertStub;
    js_cocos2dx_socketio_class->finalize = js_cocos2dx_SocketIO_finalize;
    js_cocos2dx_socketio_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_BINDED_PROP_DEF_ACCESSOR(SIOClient, tag),
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("send", js_cocos2dx_SocketIO_send, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("emit", js_cocos2dx_SocketIO_emit, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("disconnect", js_cocos2dx_SocketIO_disconnect, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("on", js_cocos2dx_SocketIO_on, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    
    static JSFunctionSpec st_funcs[] = {
        JS_FN("connect", js_cocos2dx_SocketIO_connect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("close", js_cocos2dx_SocketIO_close, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    js_cocos2dx_socketio_prototype = JS_InitClass(
                                                cx, global,
                                                NULL,
                                                js_cocos2dx_socketio_class,
                                                js_cocos2dx_SocketIO_constructor, 0, // constructor
                                                properties,
                                                funcs,
                                                NULL, // no static properties
                                                st_funcs);
    
    JSObject* jsclassObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return SocketIO; })()"));

}

