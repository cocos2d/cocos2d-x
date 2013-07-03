#ifndef __JS_COCOS2D_X_SPECIFICS_H__
#define __JS_COCOS2D_X_SPECIFICS_H__

#include "jsapi.h"
#include "ScriptingCore.h"

class JSScheduleWrapper;

// JSScheduleWrapper* --> Array* since one js function may correspond to many targets.
// To debug this, you could refer to JSScheduleWrapper::dump function.
// It will prove that i'm right. :)
typedef struct jsScheduleFunc_proxy {
    JSObject* jsfuncObj;
    Array*  targets; 
    UT_hash_handle hh;
} schedFunc_proxy_t;

typedef struct jsScheduleTarget_proxy {
    JSObject* jsTargetObj;
    Array*  targets;
    UT_hash_handle hh;
} schedTarget_proxy_t;


typedef struct jsCallFuncTarget_proxy {
    void * ptr;
    Array *obj;
    UT_hash_handle hh;
} callfuncTarget_proxy_t;

extern schedFunc_proxy_t *_schedFunc_target_ht;
extern schedTarget_proxy_t *_schedObj_target_ht;

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
 * The returned pointer should be deleted using jsb_remove_proxy. Most of the
 * time you do that in the C++ destructor.
 */
template<class T>
inline js_proxy_t *js_get_or_create_proxy(JSContext *cx, T *native_obj) {
    js_proxy_t *proxy;
    HASH_FIND_PTR(_native_js_global_ht, &native_obj, proxy);
    if (!proxy) {
        js_type_class_t *typeProxy = js_get_type_from_native<T>(native_obj);
        // Return NULL if can't find its type rather than making an assert.
//        assert(typeProxy);
        if (!typeProxy) {
            CCLOGINFO("Could not find the type of native object.");
            return NULL;
        }
        
        JSObject* js_obj = JS_NewObject(cx, typeProxy->jsclass, typeProxy->proto, typeProxy->parentProto);
        proxy = jsb_new_proxy(native_obj, js_obj);
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


class JSCallbackWrapper: public Object {
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
    jsval _jsCallback;
    jsval _jsThisObj;
    jsval _extraData;
};


class JSCCBAnimationWrapper: public JSCallbackWrapper {
public:
    JSCCBAnimationWrapper() {}
    virtual ~JSCCBAnimationWrapper() {}
    
    void animationCompleteCallback() {
        
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        jsval retval = JSVAL_NULL;
        
        if(!JSVAL_IS_VOID(_jsCallback)  && !JSVAL_IS_VOID(_jsThisObj)) {
            JS_CallFunctionValue(cx, JSVAL_TO_OBJECT(_jsThisObj), _jsCallback, 0, NULL, &retval);
        }
    }
    
};


class JSCallFuncWrapper: public JSCallbackWrapper {
public:
    JSCallFuncWrapper() {}
    virtual ~JSCallFuncWrapper(void) {
        return;
    }

    static void setTargetForNativeNode(Node *pNode, JSCallFuncWrapper *target);
    static Array * getTargetForNativeNode(Node *pNode);

    void callbackFunc(Node *node);
};


class JSScheduleWrapper: public JSCallbackWrapper {
    
public:
    JSScheduleWrapper() : _pTarget(NULL), _pPureJSTarget(NULL), _priority(0), _isUpdateSchedule(false) {}
    virtual ~JSScheduleWrapper();

    static void setTargetForSchedule(jsval sched, JSScheduleWrapper *target);
    static Array * getTargetForSchedule(jsval sched);
    static void setTargetForJSObject(JSObject* jsTargetObj, JSScheduleWrapper *target);
    static Array * getTargetForJSObject(JSObject* jsTargetObj);
    
    // Remove all targets.
    static void removeAllTargets();
    // Remove all targets for priority.
    static void removeAllTargetsForMinPriority(int minPriority);
	// Remove all targets by js object from hash table(_schedFunc_target_ht and _schedObj_target_ht).	
    static void removeAllTargetsForJSObject(JSObject* jsTargetObj);
	// Remove the target by js object and the wrapper for native schedule.
    static void removeTargetForJSObject(JSObject* jsTargetObj, JSScheduleWrapper* target);
    static void dump();

    void pause();
    
    void scheduleFunc(float dt);
    virtual void update(float dt);
    
    Object* getTarget();
    void setTarget(Object* pTarget);
    
    void setPureJSTarget(JSObject* jstarget);
    JSObject* getPureJSTarget();
    
    void setPriority(int priority);
    int  getPriority();
    
    void setUpdateSchedule(bool isUpdateSchedule);
    bool isUpdateSchedule();
    
protected:
    Object* _pTarget;
    JSObject* _pPureJSTarget;
    int _priority;
    bool _isUpdateSchedule;
};


class JSTouchDelegate: public Object, public TouchDelegate
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

    bool ccTouchBegan(Touch *pTouch, Event *pEvent);
    void ccTouchMoved(Touch *pTouch, Event *pEvent);
    void ccTouchEnded(Touch *pTouch, Event *pEvent);
    void ccTouchCancelled(Touch *pTouch, Event *pEvent);
    
    // optional
    void ccTouchesBegan(Set *pTouches, Event *pEvent);
    void ccTouchesMoved(Set *pTouches, Event *pEvent);
    void ccTouchesEnded(Set *pTouches, Event *pEvent);
    void ccTouchesCancelled(Set *pTouches, Event *pEvent);

private:
    JSObject *_mObj;
    typedef std::map<JSObject*, JSTouchDelegate*> TouchDelegateMap;
    typedef std::pair<JSObject*, JSTouchDelegate*> TouchDelegatePair;
    static TouchDelegateMap sTouchDelegateMap;
};



#endif
