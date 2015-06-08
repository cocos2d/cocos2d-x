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

#include "jsb_cocos2dx_physics3d_manual.h"

#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION

#include "jsb_cocos2dx_physics3d_auto.hpp"
#include "cocos2d_specifics.hpp"
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
        js_proxy_t* proxy = jsb_get_js_proxy(tmp.toObjectOrNull());
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

        js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::PhysicsSprite3D>(cx, (cocos2d::PhysicsSprite3D*)ret);
        jsval jsret = jsProxy ? OBJECT_TO_JSVAL(jsProxy->obj) : JSVAL_VOID;

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

        js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::PhysicsSprite3D>(cx, (cocos2d::PhysicsSprite3D*)ret);
        jsval jsret = jsProxy ? OBJECT_TO_JSVAL(jsProxy->obj) : JSVAL_VOID;

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

        js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::PhysicsSprite3D>(cx, (cocos2d::PhysicsSprite3D*)ret);
        jsval jsret = jsProxy ? OBJECT_TO_JSVAL(jsProxy->obj) : JSVAL_VOID;

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

        js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DRigidBody>(cx, (cocos2d::Physics3DRigidBody*)ret);
        jsval jsret = OBJECT_TO_JSVAL(jsProxy->obj);

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
        js_proxy_t* proxy = js_get_or_create_proxy<Physics3DShape>(cx, ret);
        jsval jsret = OBJECT_TO_JSVAL(proxy->obj);

        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3dShape_createMesh : wrong number of arguments");
    return false;
}

jsval physics3d_collisionPoint_to_jsval(JSContext*cx, const Physics3DCollisionInfo::CollisionPoint& point)
{
    JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));

    JS_DefineProperty(cx, tmp, "localPositionOnA", JS::RootedValue(cx, vector3_to_jsval(cx, point.localPositionOnA)), JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineProperty(cx, tmp, "localPositionOnB", JS::RootedValue(cx, vector3_to_jsval(cx, point.localPositionOnB)), JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineProperty(cx, tmp, "worldPositionOnA", JS::RootedValue(cx, vector3_to_jsval(cx, point.worldPositionOnA)), JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineProperty(cx, tmp, "worldPositionOnB", JS::RootedValue(cx, vector3_to_jsval(cx, point.worldPositionOnB)), JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineProperty(cx, tmp, "worldNormalOnB", JS::RootedValue(cx, vector3_to_jsval(cx, point.worldNormalOnB)), JSPROP_ENUMERATE | JSPROP_PERMANENT);

    return OBJECT_TO_JSVAL(tmp);
}

jsval physics3d_collisioninfo_to_jsval(JSContext* cx, const Physics3DCollisionInfo& ci)
{
    JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));

    js_proxy_t* proxy = js_get_or_create_proxy<Physics3DObject>(cx, ci.objA);
    JS_DefineProperty(cx, tmp, "objA", JS::RootedValue(cx, OBJECT_TO_JSVAL(proxy->obj)), JSPROP_ENUMERATE | JSPROP_PERMANENT);

    proxy = js_get_or_create_proxy<Physics3DObject>(cx, ci.objB);
    JS_DefineProperty(cx, tmp, "objB", JS::RootedValue(cx, OBJECT_TO_JSVAL(proxy->obj)), JSPROP_ENUMERATE | JSPROP_PERMANENT);

    JS::RootedObject jsarr(cx, JS_NewArrayObject(cx, ci.collisionPointList.size()));
    uint32_t i = 0;
    for(auto iter = ci.collisionPointList.begin(); iter != ci.collisionPointList.end(); ++iter)
    {
        JS::RootedValue element(cx, physics3d_collisionPoint_to_jsval(cx, *iter));
        JS_SetElement(cx, jsarr, i++, element);
    }
    JS_DefineProperty(cx, tmp, "collisionPointList", JS::RootedValue(cx, OBJECT_TO_JSVAL(jsarr)), JSPROP_ENUMERATE | JSPROP_PERMANENT);

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
        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.get(1).toObjectOrNull(), args.get(0)));
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
        ok &= JS::ToNumber( cx, args.get(3), &arg3) && !isnan(arg3);
        ok &= JS::ToNumber( cx, args.get(4), &arg4) && !isnan(arg4);
        ok &= JS::ToNumber( cx, args.get(5), &arg5) && !isnan(arg5);
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

        js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DShape>(cx, ret);
        jsval jsret = OBJECT_TO_JSVAL(jsProxy->obj);

        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DShape_createHeightfield : wrong number of arguments");
    return false;
}

void register_all_cocos2dx_physics3d_manual(JSContext *cx, JS::HandleObject global)
{
    JS::RootedObject ccObj(cx);
    get_or_create_js_obj(cx, global, "cc", &ccObj);

    JS::RootedValue tmpVal(cx);
    JS_GetProperty(cx, ccObj, "PhysicsSprite3D", &tmpVal);
    JS::RootedObject tmpObj(cx, tmpVal.toObjectOrNull());
    JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_PhysicsSprite3D_create, 2, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_GetProperty(cx, ccObj, "Physics3DRigidBody", &tmpVal);
    tmpObj = tmpVal.toObjectOrNull();
    JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_physics3d_Physics3DRigidBody_create, 1, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_GetProperty(cx, ccObj, "Physics3DShape", &tmpVal);
    tmpObj = tmpVal.toObjectOrNull();
    JS_DefineFunction(cx, tmpObj, "createMesh", js_cocos2dx_physics3d_Physics3dShape_createMesh, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "createHeightfield", js_cocos2dx_physics3d_Physics3dShape_createHeightfield, 8, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_DefineFunction(cx, JS::RootedObject(cx, jsb_cocos2d_Physics3DObject_prototype), "setCollisionCallback", jsb_cocos2d_Physics3DObject_setCollisionCallback, 2, JSPROP_READONLY | JSPROP_PERMANENT);
}

#endif //CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
