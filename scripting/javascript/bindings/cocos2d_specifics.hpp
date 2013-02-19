#ifndef __JS_COCOS2D_X_SPECIFICS_H__
#define __JS_COCOS2D_X_SPECIFICS_H__

#include "jsapi.h"
#include "ScriptingCore.h"

class JSScheduleWrapper;

// JSScheduleWrapper* --> CCArray* since one js function may correspond to many targets.
// To debug this, you could refer to JSScheduleWrapper::dump function.
// It will prove that i'm right. :)
typedef struct jsScheduleFunc_proxy {
    JSObject* jsfuncObj;
    CCArray*  targets; 
    UT_hash_handle hh;
} schedFunc_proxy_t;

typedef struct jsScheduleTarget_proxy {
    CCNode*   nativeObj;
    CCArray*  targets;
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
    JSCallbackWrapper();
    virtual ~JSCallbackWrapper();
    void setJSCallbackFunc(jsval obj);
    void setJSCallbackThis(jsval thisObj);
    void setJSExtraData(jsval data);
    
    const jsval& getJSCallbackFunc() const;
    const jsval& getJSCallbackThis() const;
    const jsval& getJSExtraData() const;
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

    void callbackFunc(CCNode *node) const;
};


class JSScheduleWrapper: public JSCallbackWrapper {
    
public:
    JSScheduleWrapper() : m_pTarget(NULL) {}
    virtual ~JSScheduleWrapper() {
        return;
    }

    static void setTargetForSchedule(jsval sched, JSScheduleWrapper *target);
    static CCArray * getTargetForSchedule(jsval sched);
    static void setTargetForNativeNode(CCNode *pNode, JSScheduleWrapper *target);
    static CCArray * getTargetForNativeNode(CCNode *pNode);
	// Remove all targets by native node from hash table(_schedFunc_target_ht and _schedTarget_native_ht).	
    static void removeAllTargetsForNatiaveNode(CCNode* pNode);
	// Remove the target by native node and the wrapper for native schedule.
    static void removeTargetForNativeNode(CCNode* pNode, JSScheduleWrapper* target);
    static void dump();

    void pause();
    
    void scheduleFunc(float dt) const;
    CCObject* getTarget();
    void setTarget(CCObject* pTarget);
protected:
    CCObject* m_pTarget;
};


class JSTouchDelegate: public CCObject, public CCTouchDelegate
{
public:
	// Set the touch delegate to map by using the key (pJSObj).
    static void setDelegateForJSObject(JSObject* pJSObj, JSTouchDelegate* pDelegate);
    // Get the touch delegate by the key (pJSObj).
	static JSTouchDelegate* getDelegateForJSObject(JSObject* pJSObj);
	// Remove the delegate by the key (pJSObj).
    static void removeDelegateForJSObject(JSObject* pJSObj);

    void setJSObject(JSObject *obj);
    void registerStandardDelegate();
    void registerTargettedDelegate(int priority, bool swallowsTouches);
	// unregister touch delegate.
	// Normally, developer should invoke cc.unregisterTouchDelegate() in when the scene exits.
	// So this function need to be binded.
    void unregisterTouchDelegate();

    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    // optional
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

private:
    JSObject *_mObj;
    typedef std::map<JSObject*, JSTouchDelegate*> TouchDelegateMap;
    typedef std::pair<JSObject*, JSTouchDelegate*> TouchDelegatePair;
    static TouchDelegateMap sTouchDelegateMap;
};



#endif
