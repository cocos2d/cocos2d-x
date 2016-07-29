/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "scripting/js-bindings/manual/physics3d/jsb_cocos2dx_physics3d_manual.h"
#include "base/ccConfig.h"
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION

#include "scripting/js-bindings/auto/jsb_cocos2dx_physics3d_auto.hpp"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "physics3d/CCPhysics3D.h"

using namespace cocos2d;

bool jsval_to_physics3DRigidBodyDes(JSContext* cx, JS::HandleValue v, Physics3DRigidBodyDes* des)
{
    JS::RootedObject jsobj(cx, v.toObjectOrNull());
    JS::RootedValue tmp(cx);

    if(JS_GetProperty(cx, jsobj, "mass", &tmp))
    {
        des->mass = tmp.toNumber();
    }
    if(JS_GetProperty(cx, jsobj, "shape", &tmp))
    {
        JS::RootedObject tmpObj(cx, tmp.toObjectOrNull());
        js_proxy_t* proxy = jsb_get_js_proxy(tmpObj);
        des->shape = proxy ? (cocos2d::Physics3DShape*)proxy->ptr : nullptr;
    }
    if(JS_GetProperty(cx, jsobj, "localInertia", &tmp))
    {
        Vec3 v3;
        jsval_to_vector3(cx, tmp, &v3);
        des->localInertia = v3;
    }
    if(JS_GetProperty(cx, jsobj, "originalTransform", &tmp))
    {
        Mat4 m4;
        jsval_to_matrix(cx, tmp, &m4);
        des->originalTransform = m4;
    }
    if(JS_GetProperty(cx, jsobj, "disableSleep", &tmp))
    {
        des->disableSleep = tmp.toBoolean();
    }
    return true;
}

bool js_cocos2dx_PhysicsSprite3D_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2)
    {
        std::string arg0;
        cocos2d::Physics3DRigidBodyDes arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_physics3DRigidBodyDes(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_PhysicsSprite3D_create : Error processing arguments");
        cocos2d::PhysicsSprite3D* ret = cocos2d::PhysicsSprite3D::create(arg0, &arg1);
        
        JS::RootedObject jsobj(cx, js_get_or_create_jsobject<cocos2d::PhysicsSprite3D>(cx, ret));
        jsval jsret = OBJECT_TO_JSVAL(jsobj);

        args.rval().set(jsret);
        return true;
    }
    if (argc == 3)
    {
        std::string arg0;
        cocos2d::Physics3DRigidBodyDes arg1;
        cocos2d::Vec3 arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_physics3DRigidBodyDes(cx, args.get(1), &arg1);
        ok &= jsval_to_vector3(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_PhysicsSprite3D_create : Error processing arguments");
        cocos2d::PhysicsSprite3D* ret = cocos2d::PhysicsSprite3D::create(arg0, &arg1, arg2);
        
        JS::RootedObject jsobj(cx, js_get_or_create_jsobject<cocos2d::PhysicsSprite3D>(cx, ret));
        jsval jsret = OBJECT_TO_JSVAL(jsobj);

        args.rval().set(jsret);
        return true;
    }
    if (argc == 4)
    {
        std::string arg0;
        cocos2d::Physics3DRigidBodyDes arg1;
        cocos2d::Vec3 arg2;
        cocos2d::Quaternion arg3;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_physics3DRigidBodyDes(cx, args.get(1), &arg1);
        ok &= jsval_to_vector3(cx, args.get(2), &arg2);
        ok &= jsval_to_quaternion(cx, args.get(3), &arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_PhysicsSprite3D_create : Error processing arguments");
        cocos2d::PhysicsSprite3D* ret = cocos2d::PhysicsSprite3D::create(arg0, &arg1, arg2, arg3);
        
        JS::RootedObject jsobj(cx, js_get_or_create_jsobject<cocos2d::PhysicsSprite3D>(cx, ret));
        jsval jsret = OBJECT_TO_JSVAL(jsobj);

        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_physics3d_PhysicsSprite3D_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_physics3d_Physics3DRigidBody_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 1)
    {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        bool ok = true;
        cocos2d::Physics3DRigidBodyDes arg0;
        ok &= jsval_to_physics3DRigidBodyDes(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_create : Error processing arguments");
        cocos2d::Physics3DRigidBody* ret = cocos2d::Physics3DRigidBody::create(&arg0);
        
        JS::RootedObject jsobj(cx, js_get_or_create_jsobject<cocos2d::Physics3DRigidBody>(cx, ret));
        jsval jsret = OBJECT_TO_JSVAL(jsobj);

        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_create : wrong number of arguments");
    return false;
}

std::vector<Vec3> jsval_to_std_vector_vec3(JSContext* cx, JS::HandleValue v)
{
    std::vector<Vec3> ret;
    JS::RootedObject jsobj(cx, v.toObjectOrNull());
    uint32_t length;
    JS_GetArrayLength(cx, jsobj, &length);
    ret.reserve(length);

    for(size_t i = 0; i < length; ++i)
    {
        JS::RootedValue element(cx);
        JS_GetElement(cx, jsobj, (uint32_t)i, &element);

        Vec3 v3;
        jsval_to_vector3(cx, element, &v3);
        ret.push_back(v3);
    }
    return ret;
}

bool js_cocos2dx_physics3d_Physics3dShape_initMesh(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 2)
    {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

        JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
        js_proxy_t *proxy = jsb_get_js_proxy(obj);
        cocos2d::Physics3DShape* cobj = (cocos2d::Physics3DShape *)(proxy ? proxy->ptr : NULL);
        JSB_PRECONDITION2(cobj, cx, false, "js_cocos2dx_physics3d_Physics3DShape_initMesh : Invalid Native Object");

        std::vector<Vec3> arg0 = jsval_to_std_vector_vec3(cx, args.get(0));
        int arg1;

        bool ok = jsval_to_int(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DShape_initMesh : Error processing arguments");

        bool ret = cobj->initMesh(&arg0[0], arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DShape_initMesh : wrong number of arguments");
    return false;
}

bool js_cocos2dx_physics3d_Physics3dShape_createMesh(JSContext *cx, uint32_t argc, jsval *vp)
{
    if(argc == 2)
    {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

        std::vector<Vec3> arg0 = jsval_to_std_vector_vec3(cx, args.get(0));
        int arg1;

        bool ok = jsval_to_int(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3dShape_createMesh : Error processing arguments");
        
        Physics3DShape* ret = Physics3DShape::createMesh(&arg0[0], arg1);
        JS::RootedObject jsobj(cx, js_get_or_create_jsobject<cocos2d::Physics3DShape>(cx, ret));
        jsval jsret = OBJECT_TO_JSVAL(jsobj);

        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3dShape_createMesh : wrong number of arguments");
    return false;
}

jsval physics3d_collisionPoint_to_jsval(JSContext*cx, const Physics3DCollisionInfo::CollisionPoint& point)
{
    JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));

    JS::RootedValue prop(cx, vector3_to_jsval(cx, point.localPositionOnA));
    JS_DefineProperty(cx, tmp, "localPositionOnA", prop, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    prop.set(vector3_to_jsval(cx, point.localPositionOnB));
    JS_DefineProperty(cx, tmp, "localPositionOnB", prop, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    prop.set(vector3_to_jsval(cx, point.worldPositionOnA));
    JS_DefineProperty(cx, tmp, "worldPositionOnA", prop, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    prop.set(vector3_to_jsval(cx, point.worldPositionOnB));
    JS_DefineProperty(cx, tmp, "worldPositionOnB", prop, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    prop.set(vector3_to_jsval(cx, point.worldNormalOnB));
    JS_DefineProperty(cx, tmp, "worldNormalOnB", prop, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    return OBJECT_TO_JSVAL(tmp);
}

jsval physics3d_collisioninfo_to_jsval(JSContext* cx, const Physics3DCollisionInfo& ci)
{
    JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));
    
    JS::RootedObject jsobj(cx, js_get_or_create_jsobject<cocos2d::Physics3DObject>(cx, ci.objA));
    JS::RootedValue prop(cx, OBJECT_TO_JSVAL(jsobj));
    JS_DefineProperty(cx, tmp, "objA", prop, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    jsobj.set(js_get_or_create_jsobject<cocos2d::Physics3DObject>(cx, ci.objB));
    prop.set(OBJECT_TO_JSVAL(jsobj));
    JS_DefineProperty(cx, tmp, "objB", prop, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    JS::RootedObject jsarr(cx, JS_NewArrayObject(cx, ci.collisionPointList.size()));
    uint32_t i = 0;
    for(auto iter = ci.collisionPointList.begin(); iter != ci.collisionPointList.end(); ++iter)
    {
        JS::RootedValue element(cx, physics3d_collisionPoint_to_jsval(cx, *iter));
        JS_SetElement(cx, jsarr, i++, element);
    }
    prop.set(OBJECT_TO_JSVAL(jsarr));
    JS_DefineProperty(cx, tmp, "collisionPointList", prop, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    return OBJECT_TO_JSVAL(tmp);
}

bool jsb_cocos2d_Physics3DObject_setCollisionCallback(JSContext *cx, uint32_t argc, jsval *vp)
{
    if(argc == 2)
    {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

        JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
        js_proxy_t *proxy = jsb_get_js_proxy(obj);
        cocos2d::Physics3DObject* cobj = (cocos2d::Physics3DObject *)(proxy ? proxy->ptr : NULL);
        JSB_PRECONDITION2( cobj, cx, false, "jsb_cocos2d_Physics3DObject_setCollisionCallback : Invalid Native Object");

        std::function<void(const Physics3DCollisionInfo &)> arg0;
        JS::RootedObject jstarget(cx, args.get(1).toObjectOrNull());
        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, jstarget, args.get(0)));
        auto lambda = [=](const Physics3DCollisionInfo &ci) -> void {
            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

            jsval jsci = physics3d_collisioninfo_to_jsval(cx, ci);
            JS::RootedValue rval(cx);
            bool ok = func->invoke(1, &jsci, &rval);
            if (!ok && JS_IsExceptionPending(cx))
            {
                JS_ReportPendingException(cx);
            }
        };
        arg0 = lambda;
        cobj->setCollisionCallback(arg0);

        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3dShape_createMesh : wrong number of arguments");
    return false;
}

bool js_cocos2dx_physics3d_Physics3dShape_initHeightfield(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 8 || argc == 9)
    {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

        JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
        js_proxy_t *proxy = jsb_get_js_proxy(obj);
        cocos2d::Physics3DShape* cobj = (cocos2d::Physics3DShape *)(proxy ? proxy->ptr : NULL);
        JSB_PRECONDITION2(cobj, cx, false, "js_cocos2dx_physics3d_Physics3DShape_initHeightfield : Invalid Native Object");

        bool ok = true;
        int arg0;
        int arg1;
        std::vector<float> arg2;
        double arg3;
        double arg4;
        double arg5;
        bool arg6;
        bool arg7;
        bool arg8;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_std_vector_float(cx, args.get(2), &arg2);
        ok &= JS::ToNumber(cx, args.get(3), &arg3) && !std::isnan(arg3);
        ok &= JS::ToNumber(cx, args.get(4), &arg4) && !std::isnan(arg4);
        ok &= JS::ToNumber(cx, args.get(5), &arg5) && !std::isnan(arg5);
        arg6 = JS::ToBoolean(args.get(6));
        arg7 = JS::ToBoolean(args.get(7));
        if (argc == 9)
            arg8 = JS::ToBoolean(args.get(8));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DShape_initHeightfield : Error processing arguments");

        bool ret = false;
        if (argc == 8)
            ret = cobj->initHeightfield(arg0, arg1, &arg2[0], arg3, arg4, arg5, arg6, arg7, false);
        else if (argc == 9)
            ret = cobj->initHeightfield(arg0, arg1, &arg2[0], arg3, arg4, arg5, arg6, arg7, arg8);

        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DShape_initHeightfield : wrong number of arguments");
    return false;
}

bool js_cocos2dx_physics3d_Physics3dShape_createHeightfield(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 8 || argc == 9)
    {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        bool ok = true;
        int arg0;
        int arg1;
        std::vector<float> arg2;
        double arg3;
        double arg4;
        double arg5;
        bool arg6;
        bool arg7;
        bool arg8;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_std_vector_float(cx, args.get(2), &arg2);
        ok &= JS::ToNumber( cx, args.get(3), &arg3) && !std::isnan(arg3);
        ok &= JS::ToNumber( cx, args.get(4), &arg4) && !std::isnan(arg4);
        ok &= JS::ToNumber( cx, args.get(5), &arg5) && !std::isnan(arg5);
        arg6 = JS::ToBoolean(args.get(6));
        arg7 = JS::ToBoolean(args.get(7));
        if(argc == 9)
            arg8 = JS::ToBoolean(args.get(8));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DShape_createHeightfield : Error processing arguments");

        cocos2d::Physics3DShape* ret = nullptr;
        if(argc == 8)
            ret = cocos2d::Physics3DShape::createHeightfield(arg0, arg1, &arg2[0], arg3, arg4, arg5, arg6, arg7);
        else if(argc == 9)
            ret = cocos2d::Physics3DShape::createHeightfield(arg0, arg1, &arg2[0], arg3, arg4, arg5, arg6, arg7, arg8);
        
        JS::RootedObject jsobj(cx, js_get_or_create_jsobject<cocos2d::Physics3DShape>(cx, ret));
        jsval jsret = OBJECT_TO_JSVAL(jsobj);

        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DShape_createHeightfield : wrong number of arguments");
    return false;
}


bool jsval_to_Physics3DWorld_HitResult(JSContext *cx, JS::HandleValue v, cocos2d::Physics3DWorld::HitResult* ret)
{
    JS::RootedObject tmp(cx);
    JS::RootedValue jshitPosition(cx);
    JS::RootedValue jshitNormal(cx);
    JS::RootedValue jshitObject(cx);
    
    bool ok = v.isObject() &&
    JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "hitPosition", &jshitPosition) &&
    JS_GetProperty(cx, tmp, "hitNormal", &jshitNormal) &&
    JS_GetProperty(cx, tmp, "hitObj", &jshitObject) &&
    jsval_to_vector3(cx, jshitPosition, &(ret->hitPosition)) &&
    jsval_to_vector3(cx, jshitNormal, &(ret->hitNormal));

    JSB_PRECONDITION2(ok, cx, false, "jsval_to_Physics3DWorld_HitResult : Error processing arguments");
    
    tmp.set(jshitObject.toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(tmp);
    ret->hitObj = (cocos2d::Physics3DObject *)(proxy ? proxy->ptr : nullptr);
    
    return true;
}

jsval Physics3DWorld_HitResult_to_jsval(JSContext *cx, const cocos2d::Physics3DWorld::HitResult& v)
{
    JS::RootedObject proto(cx);
    JS::RootedObject parent(cx);
    JS::RootedObject tmp(cx, JS_NewObject(cx, nullptr, proto, parent));
    if (!tmp) return JSVAL_NULL;
    JS::RootedValue hitPosition(cx, vector3_to_jsval(cx, v.hitPosition));
    JS::RootedValue hitNormal(cx, vector3_to_jsval(cx, v.hitNormal));
    JS::RootedValue hitobject(cx);
    
    if (v.hitObj)
    {
        JS::RootedObject jsobj(cx, js_get_or_create_jsobject<cocos2d::Physics3DObject>(cx, v.hitObj));
        hitobject.set(OBJECT_TO_JSVAL(jsobj));
    }
    
    bool ok = JS_DefineProperty(cx, tmp, "hitPosition", hitPosition, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "hitNormal", hitNormal, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "hitObj", hitobject, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

bool js_cocos2dx_physics3d_Physics3DWorld_rayCast(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DWorld* cobj = (cocos2d::Physics3DWorld *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_rayCast : Invalid Native Object");
    if (argc >= 2) {
        cocos2d::Vec3 arg0;
        cocos2d::Vec3 arg1;
        cocos2d::Physics3DWorld::HitResult ret;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        ok &= jsval_to_vector3(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_rayCast : Error processing arguments");
        bool succeed = cobj->rayCast(arg0, arg1, &ret);
        
        if (succeed)
        {
            jsval jsret = JSVAL_NULL;
            jsret = Physics3DWorld_HitResult_to_jsval(cx, ret);
            args.rval().set(jsret);
        }
        else
        {
            args.rval().set(JSVAL_FALSE);
        }
        return true;
    }
    
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DWorld_rayCast : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}

void register_all_cocos2dx_physics3d_manual(JSContext *cx, JS::HandleObject global)
{
    JS::RootedObject ccObj(cx);
    get_or_create_js_obj(cx, global, "jsb", &ccObj);

    JS::RootedValue tmpVal(cx);
    JS_GetProperty(cx, ccObj, "PhysicsSprite3D", &tmpVal);
    JS::RootedObject tmpObj(cx, tmpVal.toObjectOrNull());
    JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_PhysicsSprite3D_create, 2, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_GetProperty(cx, ccObj, "Physics3DRigidBody", &tmpVal);
    tmpObj.set(tmpVal.toObjectOrNull());
    JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_physics3d_Physics3DRigidBody_create, 1, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_GetProperty(cx, ccObj, "Physics3DShape", &tmpVal);
    tmpObj.set(tmpVal.toObjectOrNull());
    JS_DefineFunction(cx, tmpObj, "createMesh", js_cocos2dx_physics3d_Physics3dShape_createMesh, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "createHeightfield", js_cocos2dx_physics3d_Physics3dShape_createHeightfield, 8, JSPROP_READONLY | JSPROP_PERMANENT);

    tmpObj.set(jsb_cocos2d_Physics3DShape_prototype);
    JS_DefineFunction(cx, tmpObj, "initMesh", js_cocos2dx_physics3d_Physics3dShape_initMesh, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "initHeightfield", js_cocos2dx_physics3d_Physics3dShape_initHeightfield, 8, JSPROP_READONLY | JSPROP_PERMANENT);

    tmpObj.set(jsb_cocos2d_Physics3DObject_prototype);
    JS_DefineFunction(cx, tmpObj, "setCollisionCallback", jsb_cocos2d_Physics3DObject_setCollisionCallback, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    
    tmpObj.set(jsb_cocos2d_Physics3DWorld_prototype);
    JS_DefineFunction(cx, tmpObj, "rayCast", js_cocos2dx_physics3d_Physics3DWorld_rayCast, 2, JSPROP_READONLY | JSPROP_PERMANENT);
}

#endif //CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
