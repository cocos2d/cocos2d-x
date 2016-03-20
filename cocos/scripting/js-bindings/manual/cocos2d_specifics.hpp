/*
 * Copyright (c) 2012 Zynga Inc.
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
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

#ifndef __JS_COCOS2D_X_SPECIFICS_H__
#define __JS_COCOS2D_X_SPECIFICS_H__

#include "scripting/js-bindings/manual/ScriptingCore.h"
#include "platform/CCSAXParser.h"

class JSScheduleWrapper;

// JSScheduleWrapper* --> Array* since one js function may correspond to many targets.
// To debug this, you could refer to JSScheduleWrapper::dump function.
// It will prove that i'm right. :)
typedef struct jsScheduleFunc_proxy {
    JSObject* jsfuncObj;
    cocos2d::__Array*  targets;
    UT_hash_handle hh;
} schedFunc_proxy_t;

typedef struct jsScheduleTarget_proxy {
    JSObject* jsTargetObj;
    cocos2d::__Array*  targets;
    UT_hash_handle hh;
} schedTarget_proxy_t;


typedef struct jsCallFuncTarget_proxy {
    void * ptr;
    cocos2d::__Array *obj;
    UT_hash_handle hh;
} callfuncTarget_proxy_t;

extern schedFunc_proxy_t *_schedFunc_target_ht;
extern schedTarget_proxy_t *_schedObj_target_ht;
extern callfuncTarget_proxy_t *_callfuncTarget_native_ht;

extern JSClass  *jsb_FinalizeHook_class;
extern JSObject *jsb_FinalizeHook_prototype;

/**
 * You don't need to manage the returned pointer. They live for the whole life of
 * the app.
 */
template <class T>
inline js_type_class_t *js_get_type_from_native(T* native_obj) {
    bool found = false;
    std::string typeName = typeid(*native_obj).name();
    auto typeProxyIter = _js_global_type_map.find(typeName);
    if (typeProxyIter == _js_global_type_map.end())
    {
        typeName = typeid(T).name();
        typeProxyIter = _js_global_type_map.find(typeName);
        if (typeProxyIter != _js_global_type_map.end())
        {
            found = true;
        }
    }
    else
    {
        found = true;
    }
    return found ? typeProxyIter->second : nullptr;
}

/**
* get type from a cocos2d::Node, call function(js_get_type_from_native) above.
*/
CC_JS_DLL js_type_class_t *js_get_type_from_node(cocos2d::Node* native_obj);

/**
 * Gets or creates a JSObject based on native_obj.
 * If native_obj is subclass of Ref, it will use the jsb_ref functions.
 * Otherwise it will Root the newly created JSObject
 */
template<class T>
JSObject* js_get_or_create_jsobject(JSContext *cx, typename std::enable_if<!std::is_base_of<cocos2d::Ref,T>::value,T>::type *native_obj)
{
    js_type_class_t* typeClass = js_get_type_from_native<T>(native_obj);
    return jsb_get_or_create_weak_jsobject(cx, native_obj, typeClass, typeid(*native_obj).name());
}

/**
 * Gets or creates a JSObject based on native_obj.
 * If native_obj is subclass of Ref, it will use the jsb_ref functions.
 * Otherwise it will Root the newly created JSObject
 */
template<class T>
JSObject* js_get_or_create_jsobject(JSContext *cx, typename std::enable_if<std::is_base_of<cocos2d::Ref,T>::value,T>::type *native_obj)
{
    js_type_class_t* typeClass = js_get_type_from_native<T>(native_obj);
    return jsb_ref_get_or_create_jsobject(cx, native_obj, typeClass, typeid(*native_obj).name());
}

/**
 * Add a FinalizeHook object to the target object.
 * When the target object get garbage collected, its FinalizeHook's finalize function will be invoked.
 * In the finalize function, it mainly remove native/js proxys, release/delete the native object.
 * IMPORTANT: For Ref objects, please remember to retain the native object to correctly manage its reference count.
 */
void js_add_FinalizeHook(JSContext *cx, JS::HandleObject target);

void js_add_object_reference(JS::HandleValue owner, JS::HandleValue target);
void js_remove_object_reference(JS::HandleValue owner, JS::HandleValue target);
void js_add_object_root(JS::HandleValue target);
void js_remove_object_root(JS::HandleValue target);


JS::Value anonEvaluate(JSContext *cx, JS::HandleObject thisObj, const char* string);
void register_cocos2dx_js_core(JSContext* cx, JS::HandleObject obj);


class JSCallbackWrapper: public cocos2d::Ref {
public:
    JSCallbackWrapper();
    JSCallbackWrapper(JS::HandleValue owner);
    virtual ~JSCallbackWrapper();
    void setJSCallbackFunc(JS::HandleValue callback);
    void setJSCallbackThis(JS::HandleValue thisObj);
    void setJSExtraData(JS::HandleValue data);
    
    const jsval getJSCallbackFunc() const;
    const jsval getJSCallbackThis() const;
    const jsval getJSExtraData() const;
protected:
    JS::Heap<JS::Value> _owner;
    JS::Heap<JS::Value> _jsCallback;
    JS::Heap<JS::Value> _jsThisObj;
    JS::Heap<JS::Value> _extraData;
};


class JSScheduleWrapper: public JSCallbackWrapper {
    
public:
    JSScheduleWrapper();
    JSScheduleWrapper(JS::HandleValue owner);

    static void setTargetForSchedule(JS::HandleValue sched, JSScheduleWrapper *target);
    static cocos2d::__Array * getTargetForSchedule(JS::HandleValue sched);
    static void setTargetForJSObject(JS::HandleObject jsTargetObj, JSScheduleWrapper *target);
    static cocos2d::__Array * getTargetForJSObject(JS::HandleObject jsTargetObj);
    
    // Remove all targets.
    static void removeAllTargets();
    // Remove all targets for priority.
    static void removeAllTargetsForMinPriority(int minPriority);
    // Remove all targets by js object from hash table(_schedFunc_target_ht and _schedObj_target_ht).   
    static void removeAllTargetsForJSObject(JS::HandleObject jsTargetObj);
    // Remove the target by js object and the wrapper for native schedule.
    static void removeTargetForJSObject(JS::HandleObject jsTargetObj, JSScheduleWrapper* target);
    static void dump();

    void pause();
    
    void scheduleFunc(float dt);
    void update(float dt);
    
    Ref* getTarget();
    void setTarget(Ref* pTarget);
    
    void setPureJSTarget(JS::HandleObject jstarget);
    JSObject* getPureJSTarget();
    
    void setPriority(int priority);
    int  getPriority();
    
    void setUpdateSchedule(bool isUpdateSchedule);
    bool isUpdateSchedule();
    
protected:
    Ref* _pTarget;
    JS::Heap<JSObject*> _pPureJSTarget;
    int _priority;
    bool _isUpdateSchedule;
};


class JSTouchDelegate: public cocos2d::Ref
{
public:
    JSTouchDelegate();
    ~JSTouchDelegate();
    
    // Set the touch delegate to map by using the key (pJSObj).
    static void setDelegateForJSObject(JSObject* pJSObj, JSTouchDelegate* pDelegate);
    // Get the touch delegate by the key (pJSObj).
    static JSTouchDelegate* getDelegateForJSObject(JSObject* pJSObj);
    // Remove the delegate by the key (pJSObj).
    static void removeDelegateForJSObject(JSObject* pJSObj);

    void setJSObject(JS::HandleObject obj);
    void registerStandardDelegate(int priority);
    void registerTargetedDelegate(int priority, bool swallowsTouches);
    // unregister touch delegate.
    // Normally, developer should invoke cc.unregisterTouchDelegate() in when the scene exits.
    // So this function need to be binded.
    void unregisterTouchDelegate();

    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
    
    // optional
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);

private:
    JS::Heap<JSObject*> _obj;
    typedef std::unordered_map<JSObject*, JSTouchDelegate*> TouchDelegateMap;
    typedef std::pair<JSObject*, JSTouchDelegate*> TouchDelegatePair;
    static TouchDelegateMap sTouchDelegateMap;
    cocos2d::EventListenerTouchOneByOne*  _touchListenerOneByOne;
    cocos2d::EventListenerTouchAllAtOnce* _touchListenerAllAtOnce;
};


class __JSPlistDelegator: public cocos2d::SAXDelegator
{
public:
    static __JSPlistDelegator* getInstance() {
        static __JSPlistDelegator* pInstance = NULL;
        if (pInstance == NULL) {
            pInstance = new (std::nothrow) __JSPlistDelegator();
        }
        return pInstance;
    };
    
    ~__JSPlistDelegator();
    
    cocos2d::SAXParser* getParser();
    
    std::string parse(const std::string& path);
    std::string parseText(const std::string& text);
    
    // implement pure virtual methods of SAXDelegator
    void startElement(void *ctx, const char *name, const char **atts);
    void endElement(void *ctx, const char *name);
    void textHandler(void *ctx, const char *ch, int len);

private:
    cocos2d::SAXParser _parser;
    std::string _result;
    bool _isStoringCharacters;
    std::string _currentValue;
};

bool js_cocos2dx_Node_onEnter(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_Node_onExit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_Node_onEnterTransitionDidFinish(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_Node_onExitTransitionDidStart(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_Node_cleanup(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_Component_onEnter(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_Component_onExit(JSContext *cx, uint32_t argc, jsval *vp);

bool js_cocos2dx_retain(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_release(JSContext *cx, uint32_t argc, jsval *vp);

void get_or_create_js_obj(JSContext* cx, JS::HandleObject obj, const std::string &name, JS::MutableHandleObject jsObj);
void get_or_create_js_obj(const std::string &name, JS::MutableHandleObject jsObj);

#endif
