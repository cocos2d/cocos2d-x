//
//  S_CCScheduler.cpp
//  TestCocos2dX
//
//  Created by Rolando Abarca on 12/6/11.
//  Copyright (c) 2011 Zynga Inc. All rights reserved.
//

#include "S_CCScheduler.h"
#include "CCScheduler.h"

JSClassRef js_S_CCScheduler_class;

// will fetch the scheduled functions for that object and execute them
// void S_runScheduledFunctions(JSObjectRef object, cocos2d::ccTime delta);
std::map<int, JSScheduleCallback *, cmp_objects> _globalCallback;

JSObjectRef S_CCScheduler::jsConstructor(JSContextRef ctx, JSObjectRef constructor, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
	return NULL;
}

bool S_CCScheduler::jsHasProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName)
{
	return false;
}

JSValueRef S_CCScheduler::jsGetProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyNameJS, JSValueRef* exception)
{
	return JSValueMakeUndefined(ctx);
}

JSStaticFunction* S_CCScheduler::jsStaticFunctions()
{
	static JSStaticFunction funcs[] = {
		{"schedule", S_CCScheduler::jsSchedule, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{"unschedule", S_CCScheduler::jsUnschedule, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{0, 0, 0}
	};
	return funcs;
}

bool S_CCScheduler::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	return false;
}

/**
 * node.schedule(name, function () {
 *  // do something here. `this' represents `node'
 * });
 */
JS_STATIC_FUNC_IMP(S_CCScheduler, jsSchedule)
{
	static int nextTimerId = 1;

	if (argumentCount >= 2) {

		// turn the scheduling arguments into a JSScheduleCallback
		JSScheduleCallback *cb = new JSScheduleCallback();
		cb->callback = arguments[0];
		JSValueProtect(ctx, cb->callback);
		cb->id = nextTimerId++;
		if (argumentCount == 3) {
			JSValueProtect(ctx, arguments[2]);
			cb->thisObject = arguments[2];
		} else {
			cb->thisObject = NULL;
		}

		// save the timer callback in our list of global timer callbacks
		_globalCallback[cb->id] = cb;

		// schedule the event
		cocos2d::ccTime interval = JSValueToNumber(ctx, arguments[1], NULL) / 1000.0f; // convert ms to seconds

		CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(JSScheduleCallback::timerCallBack), cb, interval, false);

		return JSValueMakeNumber(ctx, cb->id);
	}

    return JSValueMakeUndefined(ctx);
}

JS_STATIC_FUNC_IMP(S_CCScheduler, jsUnschedule)
{
	if (argumentCount == 1) {
		/**
		 * what this should do: remove the key from the list of scheduled methods for that object
		 * if there are no more scheduled objects, unschedule this object
		 */
		int timerIdToRemove = JSValueToNumber(ctx, arguments[0], NULL);
		callback_map::iterator it = _globalCallback.find(timerIdToRemove);
		if (it != _globalCallback.end()) {
			JSScheduleCallback* cb = (*it).second;
			// unschedule the callback
			CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(JSScheduleCallback::timerCallBack), cb);
			_globalCallback.erase(it);
			JSValueUnprotect(ctx, cb->callback);
			cb->callback = NULL;
			if (cb->thisObject) JSValueUnprotect(ctx, cb->thisObject);
			cb->release(); // we created it, we need to release our reference
		}
	}
	return thisObject;
}

#pragma mark - JSScheduleCallback

JSScheduleCallback::~JSScheduleCallback()
{
}

void JSScheduleCallback::timerCallBack(ccTime dt)
{
	if (this->callback) {
		JSGlobalContextRef ctx = ScriptingCore::getInstance().getGlobalContext();
		JSObjectRef func = JSValueToObject(ctx, this->callback, NULL);
		// convert delta to milliseconds
		JSValueRef delta = JSValueMakeNumber(ctx, dt * 1000.0f);
		JSObjectCallAsFunction(ctx, func, (JSObjectRef)this->thisObject, 1, &delta, NULL);
	}
}
