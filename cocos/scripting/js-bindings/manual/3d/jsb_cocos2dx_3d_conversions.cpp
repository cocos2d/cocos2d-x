/*
 * Created by Huabin LING on 17/6/15.
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


#include "base/ccConfig.h"
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION

#include "jsapi.h"
#include "jsb_cocos2dx_3d_conversions.h"
#include "js_manual_conversions.h"
#include "CCPhysics3DShape.h"

bool jsval_to_Physics3DRigidBodyDes(JSContext *cx, JS::HandleValue v, cocos2d::Physics3DRigidBodyDes** bodyDes)
{
    JS::RootedObject tmp(cx);
    JS::RootedValue massValue(cx);
    JS::RootedValue localInertiaValue(cx);
    JS::RootedValue shapeValue(cx);
    JS::RootedValue originalTransformValue(cx);
    JS::RootedValue disableSleepValue(cx);
    double mass;
    cocos2d::Vec3 localInertia;
    cocos2d::Physics3DShape* shape = nullptr;
    cocos2d::Mat4 originalTransform;
    bool disableSleep;

    bool ok = v.isObject() &&
        JS_ValueToObject(cx, v, &tmp) &&
        JS_GetProperty(cx, tmp, "mass", &massValue) &&
        JS_GetProperty(cx, tmp, "localInertia", &localInertiaValue) &&
        JS_GetProperty(cx, tmp, "shape", &shapeValue) &&
        JS_GetProperty(cx, tmp, "originalTransform", &originalTransformValue) &&
        JS_GetProperty(cx, tmp, "disableSleep", &disableSleepValue) &&
        JS::ToNumber(cx, massValue, &mass) &&
        jsval_to_vector3(cx, localInertiaValue, &localInertia) &&
        jsval_to_matrix(cx, originalTransformValue, &originalTransform);


    js_proxy_t *jsProxy = jsb_get_js_proxy(shapeValue.toObjectOrNull());
    shape = (cocos2d::Physics3DShape*)(jsProxy ? jsProxy->ptr : nullptr);

    disableSleep = JS::ToBoolean(disableSleepValue);

    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");

    cocos2d::Physics3DRigidBodyDes *bodyDesPtr = new cocos2d::Physics3DRigidBodyDes();
    *bodyDes = bodyDesPtr;
    (*bodyDes)->mass = mass;
    (*bodyDes)->localInertia = localInertia;
    (*bodyDes)->shape = shape;
    (*bodyDes)->originalTransform = originalTransform;
    (*bodyDes)->disableSleep = disableSleep;

    return true;
}
#endif // CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION