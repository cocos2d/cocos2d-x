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

#include "scripting/js-bindings/manual/navmesh/jsb_cocos2dx_navmesh_conversions.h"
#if CC_USE_NAVMESH
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "scripting/js-bindings/manual/js_manual_conversions.h"

bool jsval_to_NavMeshAgentParam(JSContext *cx, JS::HandleValue v, cocos2d::NavMeshAgentParam* ret)
{
    JS::RootedObject tmp(cx);
    JS::RootedValue jsr(cx);
    JS::RootedValue jsh(cx);
    JS::RootedValue jsmaxA(cx);
    JS::RootedValue jsmaxS(cx);
    JS::RootedValue jscQR(cx);
    JS::RootedValue jspOR(cx);
    JS::RootedValue jssW(cx);
    JS::RootedValue jsuF(cx);
    JS::RootedValue jsoAT(cx);
    JS::RootedValue jsqFT(cx);
    double radius, height, maxAcceleration, maxSpeed, collisionQueryRange, pathOptimizationRange, separationWeight, updateFlags, obstacleAvoidanceType, queryFilterType;
    bool ok = v.isObject() &&
    JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "radius", &jsr) &&
    JS_GetProperty(cx, tmp, "height", &jsh) &&
    JS_GetProperty(cx, tmp, "maxAcceleration", &jsmaxA) &&
    JS_GetProperty(cx, tmp, "maxSpeed", &jsmaxS) &&
    JS_GetProperty(cx, tmp, "collisionQueryRange", &jscQR) &&
    JS_GetProperty(cx, tmp, "pathOptimizationRange", &jspOR) &&
    JS_GetProperty(cx, tmp, "separationWeight", &jssW) &&
    JS_GetProperty(cx, tmp, "updateFlags", &jsuF) &&
    JS_GetProperty(cx, tmp, "obstacleAvoidanceType", &jsoAT) &&
    JS_GetProperty(cx, tmp, "queryFilterType", &jsqFT) &&
    JS::ToNumber(cx, jsr, &radius) &&
    JS::ToNumber(cx, jsh, &height) &&
    JS::ToNumber(cx, jsmaxA, &maxAcceleration) &&
    JS::ToNumber(cx, jsmaxS, &maxSpeed) &&
    JS::ToNumber(cx, jscQR, &collisionQueryRange) &&
    JS::ToNumber(cx, jspOR, &pathOptimizationRange) &&
    JS::ToNumber(cx, jssW, &separationWeight) &&
    JS::ToNumber(cx, jsuF, &updateFlags) &&
    JS::ToNumber(cx, jsoAT, &obstacleAvoidanceType) &&
    JS::ToNumber(cx, jsoAT, &queryFilterType);
    
    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
    
    ret->radius = (float)radius;
    ret->height = (float)height;
    ret->maxAcceleration = (float)maxAcceleration;
    ret->maxSpeed = (float)maxSpeed;
    ret->collisionQueryRange = (float)collisionQueryRange;
    ret->pathOptimizationRange = (float)pathOptimizationRange;
    ret->separationWeight = (float)separationWeight;
    ret->updateFlags = (unsigned char)updateFlags;
    ret->obstacleAvoidanceType = (unsigned char)obstacleAvoidanceType;
    ret->queryFilterType = (unsigned char)queryFilterType;
    return true;
}

jsval offMeshLinkData_to_jsval(JSContext* cx, const cocos2d::OffMeshLinkData& v)
{
    JS::RootedObject proto(cx);
    JS::RootedObject parent(cx);
    JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, proto, parent));
    if (!tmp) return JSVAL_NULL;
    JS::RootedValue jsstartPos(cx, vector3_to_jsval(cx, v.startPosition));
    JS::RootedValue jsendPos(cx, vector3_to_jsval(cx, v.endPosition));
    bool ok = JS_DefineProperty(cx, tmp, "startPosition", jsstartPos, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "endPosition", jsendPos, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}
#endif //#if CC_USE_NAVMESH