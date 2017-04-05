/*
 * Copyright (c) 2014-2017 Chukong Technologies Inc.
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

#include "scripting/js-bindings/manual/jsb_event_dispatcher_manual.h"

#include "base/CCEventDispatcher.h"
#include "base/CCEventListenerFocus.h"
#include "base/CCEventListenerKeyboard.h"
#include "base/CCEventListenerMouse.h"
#include "base/CCEventListenerAcceleration.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEvent.h"
#include "base/CCEventCustom.h"
#include "scripting/js-bindings/manual/ScriptingCore.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"

USING_NS_CC;

bool js_EventListenerTouchOneByOne_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        auto ret = EventListenerTouchOneByOne::create();

        ret->onTouchBegan = [cx, ret](Touch* touch, Event* event) -> bool {
            JS::RootedValue jsret(cx);
            bool ok = ScriptingCore::getInstance()->handleTouchEvent(ret, EventTouch::EventCode::BEGAN, touch, event, &jsret);

            // Not found the method, just return false.
            if (!ok)
                return false;

            if (jsret.isBoolean()) {
                return jsret.toBoolean();
            } else {
                return false;
            }
        };

        ret->onTouchMoved = [ret](Touch* touch, Event* event) {
            ScriptingCore::getInstance()->handleTouchEvent(ret, EventTouch::EventCode::MOVED, touch, event);
        };

        ret->onTouchEnded = [ret](Touch* touch, Event* event) {
            ScriptingCore::getInstance()->handleTouchEvent(ret, EventTouch::EventCode::ENDED, touch, event);
        };

        ret->onTouchCancelled = [ret](Touch* touch, Event* event) {
            ScriptingCore::getInstance()->handleTouchEvent(ret, EventTouch::EventCode::CANCELLED, touch, event);
        };

        JS::RootedValue jsret(cx, OBJECT_TO_JSVAL(js_get_or_create_jsobject<EventListenerTouchOneByOne>(cx, ret)));
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

bool js_EventListenerTouchAllAtOnce_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        auto ret = EventListenerTouchAllAtOnce::create();

        ret->onTouchesBegan = [ret](const std::vector<Touch*>& touches, Event* event) {
            ScriptingCore::getInstance()->handleTouchesEvent(ret, EventTouch::EventCode::BEGAN, touches, event);
        };

        ret->onTouchesMoved = [ret](const std::vector<Touch*>& touches, Event* event) {
            ScriptingCore::getInstance()->handleTouchesEvent(ret, EventTouch::EventCode::MOVED, touches, event);
        };

        ret->onTouchesEnded = [ret](const std::vector<Touch*>& touches, Event* event) {
            ScriptingCore::getInstance()->handleTouchesEvent(ret, EventTouch::EventCode::ENDED, touches, event);
        };

        ret->onTouchesCancelled = [ret](const std::vector<Touch*>& touches, Event* event) {
            ScriptingCore::getInstance()->handleTouchesEvent(ret, EventTouch::EventCode::CANCELLED, touches, event);
        };

        JS::RootedValue jsret(cx, OBJECT_TO_JSVAL(js_get_or_create_jsobject<EventListenerTouchAllAtOnce>(cx, ret)));
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

bool js_EventListenerMouse_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        auto ret = EventListenerMouse::create();

        ret->onMouseDown = [ret](Event* event) {
            ScriptingCore::getInstance()->handleMouseEvent(ret, EventMouse::MouseEventType::MOUSE_DOWN, event);
        };

        ret->onMouseUp = [ret](Event* event) {
            ScriptingCore::getInstance()->handleMouseEvent(ret, EventMouse::MouseEventType::MOUSE_UP, event);
        };

        ret->onMouseMove = [ret](Event* event) {
            ScriptingCore::getInstance()->handleMouseEvent(ret, EventMouse::MouseEventType::MOUSE_MOVE, event);
        };

        ret->onMouseScroll = [ret](Event* event) {
            ScriptingCore::getInstance()->handleMouseEvent(ret, EventMouse::MouseEventType::MOUSE_SCROLL, event);
        };

        JS::RootedValue jsret(cx, OBJECT_TO_JSVAL(js_get_or_create_jsobject<EventListenerMouse>(cx, ret)));
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

bool js_EventListenerKeyboard_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        auto ret = EventListenerKeyboard::create();

        ret->onKeyPressed = [ret](EventKeyboard::KeyCode keyCode, Event* event) {
            ScriptingCore::getInstance()->handleKeyboardEvent(ret, keyCode, true, event);
        };

        ret->onKeyReleased = [ret](EventKeyboard::KeyCode keyCode, Event* event) {
            ScriptingCore::getInstance()->handleKeyboardEvent(ret, keyCode, false, event);
        };

        JS::RootedValue jsret(cx, OBJECT_TO_JSVAL(js_get_or_create_jsobject<EventListenerKeyboard>(cx, ret)));
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

bool js_EventListenerAcceleration_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::function<void (Acceleration *, Event *)> arg0;
        JSFunctionWrapper *wrapper = nullptr;
        do {
            if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
            {
                JS::RootedObject jstarget(cx, args.thisv().toObjectOrNull());
                std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, jstarget, args.get(0)));
                wrapper = func.get();
                auto lambda = [=](Acceleration* acc, Event* event) -> void {
                    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
                    jsval largv[2];
                    largv[0] = ccacceleration_to_jsval(cx, *acc);
                    if (event) {
                        js_type_class_t *typeClassEvent = js_get_type_from_native<Event>(event);
                        largv[1] = OBJECT_TO_JSVAL(jsb_get_or_create_weak_jsobject(cx, event, typeClassEvent));
                    } else {
                        largv[1] = JSVAL_NULL;
                    };
                    JS::RootedValue rval(cx);
                    bool succeed = func->invoke(2, &largv[0], &rval);
                    if (!succeed && JS_IsExceptionPending(cx)) {
                        JS_ReportPendingException(cx);
                    }
                };
                arg0 = lambda;
            }
            else
            {
                arg0 = nullptr;
            }
        } while(0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_EventListenerAcceleration_create : Error processing arguments");
        
        auto ret = EventListenerAcceleration::create(arg0);
        JS::RootedValue jsret(cx, OBJECT_TO_JSVAL(js_get_or_create_jsobject<EventListenerAcceleration>(cx, ret)));
        if (wrapper)
        {
            wrapper->setOwner(cx, jsret);
        }
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_EventListenerAcceleration_create : wrong number of arguments");
    return false;
}

bool js_EventListenerFocus_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    if(argc == 0)
    {
        auto ret = EventListenerFocus::create();
        ret->onFocusChanged = [ret](ui::Widget* widgetLoseFocus, ui::Widget* widgetGetFocus){
            ScriptingCore::getInstance()->handleFocusEvent(ret, widgetLoseFocus, widgetGetFocus);
        };

        JS::RootedValue jsret(cx, OBJECT_TO_JSVAL(js_get_or_create_jsobject<EventListenerFocus>(cx, ret)));

        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

bool js_EventListenerCustom_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::function<void (cocos2d::EventCustom *)> arg1;
        JSFunctionWrapper *wrapper = nullptr;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        do {
            if(JS_TypeOfValue(cx, args.get(1)) == JSTYPE_FUNCTION)
            {
                JS::RootedObject jstarget(cx, args.thisv().toObjectOrNull());
                std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, jstarget, args.get(1)));
                wrapper = func.get();
                auto lambda = [=](EventCustom* event) -> void {
                    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
                    jsval largv[1];
                    if (event) {
                        js_type_class_t *typeClassEvent = js_get_type_from_native<EventCustom>(event);
                        largv[0] = OBJECT_TO_JSVAL(jsb_get_or_create_weak_jsobject(cx, event, typeClassEvent));
                    } else {
                        largv[0] = JSVAL_NULL;
                    };
                    JS::RootedValue rval(cx);
                    bool succeed = func->invoke(JS::HandleValueArray::fromMarkedLocation(1, largv), &rval);
                    if (!succeed && JS_IsExceptionPending(cx)) {
                        JS_ReportPendingException(cx);
                    }
                };
                arg1 = lambda;
            }
            else
            {
                arg1 = nullptr;
            }
        } while(0)
        ;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_EventListenerCustom_create : Error processing arguments");

        auto ret = EventListenerCustom::create(arg0, arg1);
        JS::RootedValue jsret(cx, OBJECT_TO_JSVAL(js_get_or_create_jsobject<EventListenerCustom>(cx, ret)));
        if (wrapper)
        {
            wrapper->setOwner(cx, jsret);
        }
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_EventListenerCustom_create : wrong number of arguments");
    return false;
}

bool js_EventDispatcher_addCustomEventListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::EventDispatcher* cobj = (cocos2d::EventDispatcher *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_EventDispatcher_addCustomEventListener : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::function<void (cocos2d::EventCustom *)> arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        do {
            if(JS_TypeOfValue(cx, args.get(1)) == JSTYPE_FUNCTION)
            {
                JS::RootedObject jstarget(cx, args.thisv().toObjectOrNull());
                std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, jstarget, args.get(1), args.thisv()));
                auto lambda = [=](cocos2d::EventCustom* event) -> void {
                    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
                    jsval largv[1];
                    if (event) {
                        js_type_class_t *typeClassEvent = js_get_type_from_native<EventCustom>(event);
                        largv[0] = OBJECT_TO_JSVAL(jsb_get_or_create_weak_jsobject(cx, event, typeClassEvent));
                    } else {
                        largv[0] = JSVAL_NULL;
                    };
                    JS::RootedValue rval(cx);
                    bool succeed = func->invoke(JS::HandleValueArray::fromMarkedLocation(1, largv), &rval);
                    if (!succeed && JS_IsExceptionPending(cx)) {
                        JS_ReportPendingException(cx);
                    }
                };
                arg1 = lambda;
            }
            else
            {
                arg1 = nullptr;
            }
        } while(0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_EventDispatcher_addCustomEventListener : Error processing arguments");
        cocos2d::EventListenerCustom* ret = cobj->addCustomEventListener(arg0, arg1);
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<EventListenerCustom>(cx, ret));
            args.rval().set(jsret);
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }
    
    JS_ReportError(cx, "js_cocos2dx_EventDispatcher_addCustomEventListener : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
