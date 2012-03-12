//
//  BaseBindings.h
//  TestCocos2dX
//
//  Created by Rolando Abarca on 12/2/11.
//  Copyright (c) 2011 Zynga Inc. All rights reserved.
//

#ifndef TestCocos2dX_BaseBindings_h
#define TestCocos2dX_BaseBindings_h

#include <JavaScriptCore/JavaScriptCore.h>
#include <map>
#include "cocos2d.h"
#include "Support.h"
#include <JavaScriptCore/JSCDebugger.h>

typedef JSValueRef (* jsMethod)(JSContextRef ctx,
								JSObjectRef function,
								JSObjectRef thisObject,
								size_t argumentCount,
								const JSValueRef arguments[],
								JSValueRef *exception);

// helper macros

/**
 * ScriptableObject boilerplate
 */
#define SCRIPTABLE_BOILERPLATE \
static JSStaticFunction* jsStaticFunctions(); \
static JSObjectRef jsConstructor(JSContextRef ctx, JSObjectRef constructor, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception); \
static bool jsHasProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName); \
static JSValueRef jsGetProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyNameJS, JSValueRef* exception); \
static JSValueRef jsSetProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyNameJS, JSValueRef* exception); \
bool   initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[]); \
void   jsUpdate(cocos2d::ccTime delta);

#define SCRIPTABLE_BOILERPLATE_CCNODE \
virtual void setParent(cocos2d::CCNode *var); \
virtual void onExit();

/**
 * ScriptableObject boilerplate implementation
 */
#define SCRIPTABLE_BOILERPLATE_CONSTRUCTOR_IMP(klass) \
JSObjectRef klass::jsConstructor(JSContextRef ctx, JSObjectRef constructor, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) \
{ \
	JSObjectRef obj = JSObjectMake(ctx, js_##klass##_class, NULL); \
	klass *cobj = new klass(); \
	if (cobj && cobj->initWithContext(ctx, obj, argumentCount, arguments)) \
	{ \
		S_TouchDelegate *delegate = dynamic_cast<S_TouchDelegate *>(cobj); \
		if (delegate) { delegate->m_TouchRegistered = false; } \
		JSObjectSetPrivate(obj, cobj); \
		return obj; \
	} \
	return NULL; \
}

#define SCRIPTABLE_BOILERPLATE_IMP(klass) \
SCRIPTABLE_BOILERPLATE_CONSTRUCTOR_IMP(klass) \
bool klass::jsHasProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName) \
{ \
	return false; \
} \
JSValueRef klass::jsGetProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyNameJS, JSValueRef* exception) \
{ \
	return JSValueMakeUndefined(ctx); \
} \
JSValueRef klass::jsSetProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyNameJS, JSValueRef* exception) \
{ \
	return JSValueMakeUndefined(ctx); \
}

#define SCRIPTABLE_BOILERPLATE_IMP_CCSCENE(klass, ccKlass) \
void klass::onExit() \
{ \
	ccKlass::onExit(); \
}

#define SCRIPTABLE_BOILERPLATE_IMP_CCNODE(klass, ccKlass) \
void klass::onExit() \
{ \
	S_TouchDelegate *delegate = dynamic_cast<S_TouchDelegate *>(this); \
	if (delegate && delegate->m_TouchRegistered) { \
		CCTouchDispatcher::sharedDispatcher()->removeDelegate(delegate); \
	} \
	ccKlass::onExit(); \
} \
void klass::setParent(CCNode *var) \
{ \
	JSContextRef ctx = ScriptingCore::getInstance().getGlobalContext(); \
	JSObjectRef thisObject = (JSObjectRef)this->getUserData(); \
	if (!var && thisObject) { \
		JSValueUnprotect(ctx, thisObject); \
	} else if (var && thisObject) { \
		JSValueProtect(ctx, thisObject); \
	} \
	CCNode::setParent(var); \
}

class S_TouchDelegate : public cocos2d::CCTouchDelegate
{
public:
	bool m_TouchRegistered;
	
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
};

class ScriptingCore : public JSCDebuggerDelegate
{
	JSGlobalContextRef	m_globalContext;
	JSObjectRef			m_globalObject;
	JSObjectRef			m_debugObject;
	JSObjectRef			m_cocos2dNamespace;
	std::map<int, bool> m_loadedFiles;
	
	JSCDebuggerController *m_debugController;
		
	// private constructor
	ScriptingCore();
	// do not auto-generate copy methods
	ScriptingCore(ScriptingCore const& copy);
	ScriptingCore& operator=(ScriptingCore const& copy);
	
public:
	~ScriptingCore();
	
	static ScriptingCore & getInstance()
	{
		static ScriptingCore instance;
		return instance;
	}
	
	/**
	 * loads and run a script
	 * @param fpath the full path of the script to be loaded
	 */
	void runScript(const char *fpath);
	
	/**
	 * @return the global context
	 */
	JSGlobalContextRef getGlobalContext() { return m_globalContext; };
	
	/**
	 * @return the global object
	 */
	JSObjectRef getGlobalObject() { return m_globalObject; };
	
	/**
	 * @param buff must be a valid pointer that can hold enough data (?)
	 * @return the exception formatted
	 */
	void formatException(JSValueRef exception, char *buff);

	/**
	 * just clear the hash that holds the scripts loaded
	 */
	void resetLoadedFiles();

	template <class T>
	JSClassRef registerClass(const char *name, JSClassRef parentClass);

	template <class T>
	JSClassRef registerClass(const char *name, JSClassRef parentClass, JSObjectRef namespaceObject);

	// DebuggerDelegate
	virtual void didReachException(const char *scriptURL, JSValueRef exception, int lineNumber);
	virtual void shouldPauseJS();
	virtual void didPause(DebuggerState *state);
};

#endif
