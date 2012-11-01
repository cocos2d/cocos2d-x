#ifndef __JS_COCOS2D_X_SPECIFICS_H__
#define __JS_COCOS2D_X_SPECIFICS_H__

#include "jsapi.h"
#include "ScriptingCore.h"

class JSScheduleWrapper;

typedef struct jsScheduleFunc_proxy {
    void * ptr;
    JSScheduleWrapper *obj;
    UT_hash_handle hh;
} schedFunc_proxy_t;

typedef struct jsScheduleTarget_proxy {
    void * ptr;
    CCArray *obj;
    UT_hash_handle hh;
} schedTarget_proxy_t;


typedef struct jsCallFuncTarget_proxy {
    void * ptr;
    CCArray *obj;
    UT_hash_handle hh;
} callfuncTarget_proxy_t;

extern schedFunc_proxy_t *_schedFunc_target_ht;
extern schedTarget_proxy_t *_schedTarget_native_ht;

extern callfuncTarget_proxy_t *_callfuncTarget_native_ht;

/**
 * You don't need to manage the returned pointer. They live for the whole life of
 * the app.
 */
template <class T>
inline js_type_class_t *js_get_type_from_native(T* native_obj) {
    js_type_class_t *typeProxy;
    long typeId = cocos2d::getHashCodeByString(typeid(*native_obj).name());
    HASH_FIND_INT(_js_global_type_ht, &typeId, typeProxy);
    if (!typeProxy) {
        cocos2d::TypeInfo *typeInfo = dynamic_cast<cocos2d::TypeInfo *>(native_obj);
        if (typeInfo) {
            typeId = typeInfo->getClassTypeInfo();
        } else {
            typeId = cocos2d::getHashCodeByString(typeid(T).name());
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


class JSCallbackWrapper: public CCObject {
public:
    JSCallbackWrapper() : jsCallback(JSVAL_VOID), jsThisObj(JSVAL_VOID), extraData(JSVAL_VOID) {}
    virtual ~JSCallbackWrapper(void) {}
    void setJSCallbackFunc(jsval obj);
    void setJSCallbackThis(jsval thisObj);
    void setJSExtraData(jsval data);
    
protected:
    jsval jsCallback;
    jsval jsThisObj;
    jsval extraData;
};


class JSCCBAnimationWrapper: public JSCallbackWrapper {
public:
    JSCCBAnimationWrapper() {}
    virtual ~JSCCBAnimationWrapper() {}
    
    void animationCompleteCallback() const {
        
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        jsval retval = JSVAL_NULL;
        
        if(!JSVAL_IS_VOID(jsCallback)  && !JSVAL_IS_VOID(jsThisObj)) {
            JS_CallFunctionValue(cx, JSVAL_TO_OBJECT(jsThisObj), jsCallback, 0, NULL, &retval);
        }
    }
    
};


class JSCallFuncWrapper: public JSCallbackWrapper {
public:
    JSCallFuncWrapper() {}
    virtual ~JSCallFuncWrapper(void) {
        return;
    }

    static void setTargetForNativeNode(CCNode *pNode, JSCallFuncWrapper *target);
    static CCArray * getTargetForNativeNode(CCNode *pNode);

    void callbackFunc(CCNode *node) const {
        
        jsval valArr[2];
        
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::CCNode>(cx, node);

        JS_AddValueRoot(cx, valArr);

        valArr[0] = OBJECT_TO_JSVAL(proxy->obj);
        if(!JSVAL_IS_VOID(extraData)) {
            valArr[1] = extraData;            
        } else {
            valArr[1] = JSVAL_NULL;
        }
        
        jsval retval;
        if(jsCallback != JSVAL_VOID && jsThisObj != JSVAL_VOID) {
            JS_CallFunctionValue(cx, JSVAL_TO_OBJECT(jsThisObj), jsCallback, 2, valArr, &retval);
        }
        
        JSCallFuncWrapper::setTargetForNativeNode(node, (JSCallFuncWrapper *)this);
        
        JS_RemoveValueRoot(cx, valArr);

    }

};


class JSScheduleWrapper: public JSCallbackWrapper {
    
public:
    JSScheduleWrapper() {}
    virtual ~JSScheduleWrapper() {
        return;
    }

    static void setTargetForSchedule(jsval sched, JSScheduleWrapper *target);
    static JSScheduleWrapper * getTargetForSchedule(jsval sched);
    static void setTargetForNativeNode(CCNode *pNode, JSScheduleWrapper *target);
    static CCArray * getTargetForNativeNode(CCNode *pNode);

    void pause();
    
    void scheduleFunc(float dt) const {
        
        jsval retval = JSVAL_NULL, data = DOUBLE_TO_JSVAL(dt);
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        
        JSBool ok = JS_AddValueRoot(cx, &data);
        if(!ok) {
            return;
        }
        
        if(!JSVAL_IS_VOID(jsCallback)  && !JSVAL_IS_VOID(jsThisObj)) {
            JS_CallFunctionValue(cx, JSVAL_TO_OBJECT(jsThisObj), jsCallback, 1, &data, &retval);
        }
        
        JS_RemoveValueRoot(cx, &data);
        
    }
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
        //jsval retval;
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
