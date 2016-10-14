/*
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

#include "scripting/js-bindings/manual/jsb_event_dispatcher_manual.h"

#include "base/CCEventListenerFocus.h"
#include "base/CCEventListenerKeyboard.h"
#include "base/CCEventListenerMouse.h"
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

        jsval jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<EventListenerTouchOneByOne>(cx, ret));
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

        jsval jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<EventListenerTouchAllAtOnce>(cx, ret));
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

        jsval jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<EventListenerMouse>(cx, ret));
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

        jsval jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<EventListenerKeyboard>(cx, ret));
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
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

        jsval jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<EventListenerFocus>(cx, ret));

        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
