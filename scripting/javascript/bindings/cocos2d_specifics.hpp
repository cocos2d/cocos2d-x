#ifndef __JS_COCOS2D_X_SPECIFICS_H__
#define __JS_COCOS2D_X_SPECIFICS_H__

#include "jsapi.h"
#include "ScriptingCore.h"


/**
 * You don't need to manage the returned pointer. They live for the whole life of
 * the app.
 */
template <class T>
inline js_type_class_t *js_get_type_from_native(T* native_obj) {
    js_type_class_t *typeProxy;
    long typeId = reinterpret_cast<long>(typeid(*native_obj).name());
    HASH_FIND_INT(_js_global_type_ht, &typeId, typeProxy);
    if (!typeProxy) {
        TypeInfo *typeInfo = dynamic_cast<TypeInfo *>(native_obj);
        if (typeInfo) {
            typeId = typeInfo->getClassTypeInfo();
        } else {
            typeId = reinterpret_cast<long>(typeid(T).name());
        }
        HASH_FIND_INT(_js_global_type_ht, &typeId, typeProxy);
    }
    return typeProxy;
}

/**
 * The returned pointer should be deleted using JS_REMOVE_PROXY. Most of the
 * time you do that in the C++ destructor.
 */
template<class T>
inline js_proxy_t *js_get_or_create_proxy(JSContext *cx, T *native_obj) {
    js_proxy_t *proxy;
    HASH_FIND_PTR(_native_js_global_ht, &native_obj, proxy);
    if (!proxy) {
        js_type_class_t *typeProxy = js_get_type_from_native<T>(native_obj);
        assert(typeProxy);
        JSObject* js_obj = JS_NewObject(cx, typeProxy->jsclass, typeProxy->proto, typeProxy->parentProto);
        JS_NEW_PROXY(proxy, native_obj, js_obj);
#ifdef DEBUG
        JS_AddNamedObjectRoot(cx, &proxy->obj, typeid(*native_obj).name());
#else
        JS_AddObjectRoot(cx, &proxy->obj);
#endif
        return proxy;
    } else {
        return proxy;
    }
    return NULL;
}

jsval anonEvaluate(JSContext *cx, JSObject *thisObj, const char* string);
void register_cocos2dx_js_extensions(JSContext* cx, JSObject* obj);

class JSCallFunc: public CCObject {
public:
    JSCallFunc(jsval func): jsCallback(func) {}
    JSCallFunc() { extraData = NULL; }
    ~JSCallFunc(){}
    void setJSCallbackFunc(jsval obj);
    void setJSCallbackThis(jsval thisObj);
    void setExtraDataField(jsval data);
    static void dumpNamedRoot(const char *name, void *addr, JSGCRootType type, void *data);
    
    void callbackFunc(CCNode *node) const {
        
        js_proxy_t *p;
        JS_GET_PROXY(p, node);
        jsval retObj = OBJECT_TO_JSVAL(p->obj);
        if(extraData != NULL) {
            ScriptingCore::getInstance()->executeJSFunctionWithThisObj(jsThisObj,
                                                                   jsCallback,
                                                                   *extraData);
        } else {
            ScriptingCore::getInstance()->executeJSFunctionWithThisObj(jsThisObj,
                                                                       jsCallback,
                                                                       retObj);
        } 
    }
private:
    jsval jsCallback;
    jsval jsThisObj;
    jsval *extraData;
};

class JSTouchDelegate: public CCTouchDelegate, public CCNode {
    public:
        void setJSObject(JSObject *obj);
        void registerStandardDelegate();
        void registerTargettedDelegate(int priority, bool swallowsTouches);
    
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
        CC_UNUSED_PARAM(pTouch); 
        CC_UNUSED_PARAM(pEvent); 
        jsval retval; 
        ScriptingCore::getInstance()->executeCustomTouchEvent(CCTOUCHBEGAN, 
                                                        pTouch, _mObj, retval);
        if(JSVAL_IS_BOOLEAN(retval)) {
            return JSVAL_TO_BOOLEAN(retval);
        } return false;
    };
    // optional
    
    void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
        CC_UNUSED_PARAM(pTouch); 
        CC_UNUSED_PARAM(pEvent);
        jsval retval; 
        ScriptingCore::getInstance()->executeCustomTouchEvent(CCTOUCHMOVED, 
                                                              pTouch, _mObj);
    }
    
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
        CC_UNUSED_PARAM(pTouch); 
        CC_UNUSED_PARAM(pEvent);
        ScriptingCore::getInstance()->executeCustomTouchEvent(CCTOUCHENDED, 
                                                              pTouch, _mObj);
    }
    
    void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {
        CC_UNUSED_PARAM(pTouch); 
        CC_UNUSED_PARAM(pEvent);
        ScriptingCore::getInstance()->executeCustomTouchEvent(CCTOUCHCANCELLED, 
                                                              pTouch, _mObj);
    }
    
    // optional
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {
        CC_UNUSED_PARAM(pTouches); 
        CC_UNUSED_PARAM(pEvent);
        ScriptingCore::getInstance()->executeCustomTouchesEvent(CCTOUCHBEGAN, 
                                                              pTouches, _mObj);
    }
    
    void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent) {
        CC_UNUSED_PARAM(pTouches); 
        CC_UNUSED_PARAM(pEvent);
        ScriptingCore::getInstance()->executeCustomTouchesEvent(CCTOUCHMOVED, 
                                                                pTouches, _mObj);        
    }
    void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {
        CC_UNUSED_PARAM(pTouches); 
        CC_UNUSED_PARAM(pEvent);
        ScriptingCore::getInstance()->executeCustomTouchesEvent(CCTOUCHENDED, 
                                                                pTouches, _mObj);
    }
    void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent) {
        CC_UNUSED_PARAM(pTouches); 
        CC_UNUSED_PARAM(pEvent);
        ScriptingCore::getInstance()->executeCustomTouchesEvent(CCTOUCHCANCELLED, 
                                                                pTouches, _mObj);
    }
    private:
        JSObject *_mObj;    
};



#endif
