/*
 * Created by Chris Hannon 2014 http://www.channon.us
 * Copyright (c) 2014-2016 Chukong Technologies Inc.
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
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

#include "scripting/js-bindings/manual/network/jsb_socketio.h"
#include "scripting/js-bindings/manual/jsb_helper.h"

#include "network/WebSocket.h"
#include "network/SocketIO.h"
#include "scripting/js-bindings/manual/spidermonkey_specifics.h"
#include "scripting/js-bindings/manual/ScriptingCore.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"

using namespace cocos2d::network;

//c++11 map to callbacks
typedef std::unordered_map<std::string, std::shared_ptr<JSFunctionWrapper>> JSB_SIOCallbackRegistry;

class JSB_SocketIODelegate : public SocketIO::SIODelegate
{
public:

    JSB_SocketIODelegate()
    {
        std::string s = "default";
        _eventRegistry[s] = nullptr;
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        _JSDelegate.construct(cx);
    }
    
    ~JSB_SocketIODelegate()
    {
        _JSDelegate.destroyIfConstructed();
    }
    
    virtual void onConnect(SIOClient* client)
    {
        CCLOG("JSB SocketIO::SIODelegate->onConnect method called from native");
        this->fireEventToScript(client, "connect", "");
    }

    virtual void onMessage(SIOClient* client, const std::string& data)
    {
        CCLOG("JSB SocketIO::SIODelegate->onMessage method called from native with data: %s", data.c_str());
        this->fireEventToScript(client, "message", data);
    }

    virtual void onClose(SIOClient* client)
    {
        CCLOG("JSB SocketIO::SIODelegate->onClose method called from native");
        this->fireEventToScript(client, "disconnect", "");
    }

    virtual void onError(SIOClient* client, const std::string& data)
    {
        CCLOG("JSB SocketIO::SIODelegate->onError method called from native with data: %s", data.c_str());
        this->fireEventToScript(client, "error", data);
    }

    virtual void fireEventToScript(SIOClient* client, const std::string& eventName, const std::string& data)
    {
        CCLOG("JSB SocketIO::SIODelegate->fireEventToScript method called from native with name '%s' data: %s", eventName.c_str(), data.c_str());

        js_proxy_t * p = jsb_get_native_proxy(client);
        if (!p) return;

        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();

        jsval args;
        if(data == "")
        {
            args = JSVAL_NULL;
        } else
        {
            args = std_string_to_jsval(cx, data);
        }
        
        JSB_SIOCallbackRegistry::iterator it = _eventRegistry.find(eventName);
        
        if(it != _eventRegistry.end())
        {
            std::shared_ptr<JSFunctionWrapper> callback = it->second;
            if (callback != nullptr)
            {
                JS::RootedValue rval(cx);
                callback->invoke(1, &args, &rval);
            }
        }
        
    }

    void setJSDelegate(JS::HandleObject pJSDelegate)
    {
        _JSDelegate.ref() = pJSDelegate;
    }

    void addEvent(const std::string& eventName, std::shared_ptr<JSFunctionWrapper> callback)
    {
        _eventRegistry[eventName] = callback;
    }

private:
    mozilla::Maybe<JS::PersistentRootedObject> _JSDelegate;
    JSB_SIOCallbackRegistry _eventRegistry;

};

JSClass  *js_cocos2dx_socketio_class;
JSObject *js_cocos2dx_socketio_prototype;

void js_cocos2dx_SocketIO_finalize(JSFreeOp *fop, JSObject *obj)
{
    CCLOG("jsbindings: finalizing JS object %p (SocketIO)", obj);
}

bool js_cocos2dx_SocketIO_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS_ReportError(cx, "SocketIO isn't meant to be instantiated, use SocketIO.connect() instead");
    return false;
}

bool js_cocos2dx_SocketIO_connect(JSContext* cx, uint32_t argc, jsval* vp)
{
    CCLOG("JSB SocketIO.connect method called");

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc >= 1 && argc <= 3)
    {
        std::string url;
        std::string caFilePath;
        bool ok = false;
        
        ok = jsval_to_std_string(cx, args[0], &url);
        JSB_PRECONDITION2( ok, cx, false, "Error processing arguments");

        if (argc == 2)
        {
            if (args[1].isObject())
            {
                // Just ignore the option argument
            }
            else if (args[1].isString())
            {
                // Assume it's CA root file path
                ok = jsval_to_std_string(cx, args[1], &caFilePath);
                JSB_PRECONDITION2( ok, cx, false, "Error processing arguments");
            }
        }

        if (argc == 3)
        {
            // Just ignore the option argument

            if (args[2].isString())
            {
                // Assume it's CA root file path
                ok = jsval_to_std_string(cx, args[2], &caFilePath);
                JSB_PRECONDITION2( ok, cx, false, "Error processing arguments");
            }
        }
        
        JSB_SocketIODelegate* siodelegate = new (std::nothrow) JSB_SocketIODelegate();
        
        CCLOG("Calling native SocketIO.connect method");
        SIOClient* ret = SocketIO::connect(url, *siodelegate, caFilePath);
        
        jsval jsret;
        do
        {
            if (ret)
            {
                // link the native object with the javascript object
                js_proxy_t *p = jsb_get_native_proxy(ret);
                if(!p)
                {
                    //previous connection not found, create a new one
                    JS::RootedObject proto(cx, js_cocos2dx_socketio_prototype);
                    JS::RootedObject obj(cx, JS_NewObject(cx, js_cocos2dx_socketio_class, proto, JS::NullPtr()));
                    p = jsb_new_proxy(ret, obj);
                    JS::RootedObject jsdelegate(cx, p->obj);
                    siodelegate->setJSDelegate(jsdelegate);
                }
                jsret = OBJECT_TO_JSVAL(p->obj);
            }
            else
            {
                jsret = JSVAL_NULL;
            }
        } while(0);

        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "JSB SocketIO.connect: Wrong number of arguments");
    return false;
}

bool js_cocos2dx_SocketIO_send(JSContext* cx, uint32_t argc, jsval* vp)
{
    CCLOG("JSB SocketIO.send method called");

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SIOClient* cobj = (SIOClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if (argc >= 1)
    {
        std::vector<std::string> eventArgs;
        std::string payload;
        
        for(int idx = 0; idx < argc; idx++)
        {
            bool ok = jsval_to_std_string(cx, args.get(idx), &payload);
            JSB_PRECONDITION2( ok, cx, false, "Error processing arguments");
            eventArgs.push_back(payload);
        }

        CCLOG("JSB SocketIO send mesage: %s", payload.c_str());

        cobj->send(eventArgs);
        return true;

    }
    JS_ReportError(cx, "Wrong number of arguments");
    return false;
}

bool js_cocos2dx_SocketIO_emit(JSContext* cx, uint32_t argc, jsval* vp)
{
    CCLOG("JSB SocketIO.emit method called");

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj); 
    SIOClient* cobj = (SIOClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if (argc >= 2)
    {
        std::string eventName;

        do
        {
            bool ok = jsval_to_std_string(cx, args.get(0), &eventName);
            JSB_PRECONDITION2( ok, cx, false, "Error processing arguments");
        } while (0);
        
        std::vector<std::string> eventArgs;
        std::string payload;
        for(int idx = 1; idx < argc; idx ++) {
            bool ok = jsval_to_std_string(cx, args.get(idx), &payload);
            JSB_PRECONDITION2( ok, cx, false, "Error processing arguments");
            eventArgs.push_back(payload);
        }

        CCLOG("JSB SocketIO emit event '%s' with payload: %s", eventName.c_str(), payload.c_str());

        cobj->emit(eventName, eventArgs);
        return true;
    }
    JS_ReportError(cx, "JSB SocketIO.emit: Wrong number of arguments");
    return false;
}

bool js_cocos2dx_SocketIO_disconnect(JSContext* cx, uint32_t argc, jsval* vp)
{
    CCLOG("JSB SocketIO.disconnect method called");

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SIOClient* cobj = (SIOClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if(argc == 0)
    {
        cobj->disconnect();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "JSB SocketIO.disconnect: Wrong number of arguments");
    return false;
}

bool js_cocos2dx_SocketIO_close(JSContext* cx, uint32_t argc, jsval* vp)
{
    CCLOG("JSB SocketIO.close method called");

    if(argc == 0)
    {

        //This method was previously implemented to take care of the HTTPClient instance not being destroyed properly
        //SocketIO::close();
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "JSB SocketIO.close: Wrong number of arguments");
    return false;
}

static bool _js_set_SIOClient_tag(JSContext* cx, uint32_t argc, jsval* vp)
{
    CCLOG("JSB SocketIO.setTag method called");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsobj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(jsobj);
    SIOClient* cobj = (SIOClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    
    if (cobj)
    {
        std::string out = "";

        jsval_to_std_string(cx, args.get(0), &out);
        cobj->setTag(out.c_str());
        return true;
    } else
    {
        JS_ReportError(cx, "Error: SocketIO instance is invalid.");
        return false;
    }
}

static bool _js_get_SIOClient_tag(JSContext* cx, uint32_t argc, jsval* vp)
{
    CCLOG("JSB SocketIO.getTag method called");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject jsobj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(jsobj);
    SIOClient* cobj = (SIOClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    
    if (cobj)
    {
        args.rval().set(std_string_to_jsval(cx, cobj->getTag()));
        return true;
    } else
    {
        JS_ReportError(cx, "Error: SocketIO instance is invalid.");
        return false;
    }
}


bool js_cocos2dx_SocketIO_on(JSContext* cx, uint32_t argc, jsval* vp)
{
    CCLOG("JSB SocketIO.on method called");

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    SIOClient* cobj = (SIOClient *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if(argc == 2)
    {
        std::string eventName;
        do
        {
            bool ok = jsval_to_std_string(cx, args.get(0), &eventName);
            JSB_PRECONDITION2( ok, cx, false, "Error processing arguments");
        } while (0);

        CCLOG("JSB SocketIO eventName to: '%s'", eventName.c_str());
        
        std::shared_ptr<JSFunctionWrapper> callback(new JSFunctionWrapper(cx, obj, args.get(1), args.thisv()));

        ((JSB_SocketIODelegate *)cobj->getDelegate())->addEvent(eventName, callback);

        args.rval().set(OBJECT_TO_JSVAL(proxy->obj));
        JS_SetReservedSlot(proxy->obj, 0, args.get(1));
        return true;
    }
    JS_ReportError(cx, "JSB SocketIO.close: Wrong number of arguments");
    return false;
}

void register_jsb_socketio(JSContext *cx, JS::HandleObject global)
{
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

    static JSPropertySpec properties[] =
    {
        JS_PSGS("tag", _js_get_SIOClient_tag, _js_set_SIOClient_tag, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] =
    {
        JS_FN("send", js_cocos2dx_SocketIO_send, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("emit", js_cocos2dx_SocketIO_emit, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("disconnect", js_cocos2dx_SocketIO_disconnect, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("on", js_cocos2dx_SocketIO_on, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    
    static JSFunctionSpec st_funcs[] =
    {
        JS_FN("connect", js_cocos2dx_SocketIO_connect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("close", js_cocos2dx_SocketIO_close, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    js_cocos2dx_socketio_prototype = JS_InitClass(
                                                cx, global,
                                                JS::NullPtr(),
                                                js_cocos2dx_socketio_class,
                                                js_cocos2dx_SocketIO_constructor, 0, // constructor
                                                nullptr,
                                                funcs,
                                                properties,
                                                st_funcs);
    
    anonEvaluate(cx, global, "(function () { return SocketIO; })()").toObjectOrNull();
}

