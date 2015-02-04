/*
 * Created by Huabin LING on 21/1/15.
 * Copyright (c) 2015 Chukong Technologies Inc.
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

#include "jsb_cocos2dx_studio_conversions.h"
#include "cocos2d_specifics.hpp"
#include "cocostudio/CocoStudio.h"

jsval animationInfo_to_jsval(JSContext* cx, const cocostudio::timeline::AnimationInfo& v)
{
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    bool ok = JS_DefineProperty(cx, tmp, "name", std_string_to_jsval(cx, v.name), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "startIndex", uint32_to_jsval(cx, v.startIndex), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "endIndex", uint32_to_jsval(cx, v.endIndex), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

bool jsval_to_animationInfo(JSContext* cx, jsval vp, cocostudio::timeline::AnimationInfo* ret)
{
    JS::RootedObject tmp(cx);
    JS::RootedValue jsName(cx);
    JS::RootedValue jsStartId(cx);
    JS::RootedValue jsEndId(cx);
    std::string name;
    double startIndex, endIndex;
    
    bool ok = vp.isObject() &&
    JS_ValueToObject(cx, JS::RootedValue(cx, vp), &tmp) &&
    JS_GetProperty(cx, tmp, "name", &jsName) &&
    JS_GetProperty(cx, tmp, "startIndex", &jsStartId) &&
    JS_GetProperty(cx, tmp, "endIndex", &jsEndId) &&
    JS::ToNumber(cx, jsStartId, &startIndex) &&
    JS::ToNumber(cx, jsEndId, &endIndex) &&
    jsval_to_std_string(cx, jsName, &name) &&
    !isnan(startIndex) && !isnan(endIndex);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->name = name;
    ret->startIndex = (int)startIndex;
    ret->endIndex = (int)endIndex;
    return true;
}
