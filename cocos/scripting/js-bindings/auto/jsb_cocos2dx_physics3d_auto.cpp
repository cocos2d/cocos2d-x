#include "jsb_cocos2dx_physics3d_auto.hpp"
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
#include "cocos2d_specifics.hpp"
#include "CCPhysics3D.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    JS::RootedObject global(cx, ScriptingCore::getInstance()->getGlobalObject());
    isNewValid = JS_GetProperty(cx, global, "initializing", &initializing) && initializing.toBoolean();
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JS::RootedObject proto(cx, typeClass->proto.get());
        JS::RootedObject parent(cx, typeClass->parentProto.get());
        JS::RootedObject _tmp(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
        
        args.rval().set(OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;    
}
JSClass  *jsb_cocos2d_Physics3DShape_class;
JSObject *jsb_cocos2d_Physics3DShape_prototype;

bool js_cocos2dx_physics3d_Physics3DShape_getbtShape(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DShape* cobj = (cocos2d::Physics3DShape *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DShape_getbtShape : Invalid Native Object");
    if (argc == 0) {
        btCollisionShape* ret = cobj->getbtShape();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<btCollisionShape>(cx, (btCollisionShape*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DShape_getbtShape : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DShape_getShapeType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DShape* cobj = (cocos2d::Physics3DShape *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DShape_getShapeType : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getShapeType();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DShape_getShapeType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DShape_createBox(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DShape_createBox : Error processing arguments");
        cocos2d::Physics3DShape* ret = cocos2d::Physics3DShape::createBox(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DShape>(cx, (cocos2d::Physics3DShape*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DShape_createBox : wrong number of arguments");
    return false;
}

bool js_cocos2dx_physics3d_Physics3DShape_createCylinder(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        double arg0;
        double arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DShape_createCylinder : Error processing arguments");
        cocos2d::Physics3DShape* ret = cocos2d::Physics3DShape::createCylinder(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DShape>(cx, (cocos2d::Physics3DShape*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DShape_createCylinder : wrong number of arguments");
    return false;
}

bool js_cocos2dx_physics3d_Physics3DShape_createConvexHull(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        const cocos2d::Vec3* arg0;
        int arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (const cocos2d::Vec3*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DShape_createConvexHull : Error processing arguments");
        cocos2d::Physics3DShape* ret = cocos2d::Physics3DShape::createConvexHull(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DShape>(cx, (cocos2d::Physics3DShape*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DShape_createConvexHull : wrong number of arguments");
    return false;
}

bool js_cocos2dx_physics3d_Physics3DShape_createCapsule(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        double arg0;
        double arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DShape_createCapsule : Error processing arguments");
        cocos2d::Physics3DShape* ret = cocos2d::Physics3DShape::createCapsule(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DShape>(cx, (cocos2d::Physics3DShape*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DShape_createCapsule : wrong number of arguments");
    return false;
}

bool js_cocos2dx_physics3d_Physics3DShape_createSphere(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DShape_createSphere : Error processing arguments");
        cocos2d::Physics3DShape* ret = cocos2d::Physics3DShape::createSphere(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DShape>(cx, (cocos2d::Physics3DShape*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DShape_createSphere : wrong number of arguments");
    return false;
}



void js_cocos2d_Physics3DShape_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Physics3DShape)", obj);
}

void js_register_cocos2dx_physics3d_Physics3DShape(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Physics3DShape_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Physics3DShape_class->name = "Physics3DShape";
    jsb_cocos2d_Physics3DShape_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3DShape_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Physics3DShape_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3DShape_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Physics3DShape_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Physics3DShape_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Physics3DShape_class->convert = JS_ConvertStub;
    jsb_cocos2d_Physics3DShape_class->finalize = js_cocos2d_Physics3DShape_finalize;
    jsb_cocos2d_Physics3DShape_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getbtShape", js_cocos2dx_physics3d_Physics3DShape_getbtShape, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getShapeType", js_cocos2dx_physics3d_Physics3DShape_getShapeType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("createBox", js_cocos2dx_physics3d_Physics3DShape_createBox, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createCylinder", js_cocos2dx_physics3d_Physics3DShape_createCylinder, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createConvexHull", js_cocos2dx_physics3d_Physics3DShape_createConvexHull, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createCapsule", js_cocos2dx_physics3d_Physics3DShape_createCapsule, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createSphere", js_cocos2dx_physics3d_Physics3DShape_createSphere, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_Physics3DShape_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_cocos2d_Physics3DShape_class,
        dummy_constructor<cocos2d::Physics3DShape>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Physics3DShape", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::Physics3DShape> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_Physics3DShape_class;
        p->proto = jsb_cocos2d_Physics3DShape_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_Physics3DObject_class;
JSObject *jsb_cocos2d_Physics3DObject_prototype;

bool js_cocos2dx_physics3d_Physics3DObject_setUserData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DObject* cobj = (cocos2d::Physics3DObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DObject_setUserData : Invalid Native Object");
    if (argc == 1) {
        void* arg0;
        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DObject_setUserData : Error processing arguments");
        cobj->setUserData(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DObject_setUserData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DObject_getUserData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DObject* cobj = (cocos2d::Physics3DObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DObject_getUserData : Invalid Native Object");
    if (argc == 0) {
        void* ret = cobj->getUserData();
        jsval jsret = JSVAL_NULL;
        #pragma warning NO CONVERSION FROM NATIVE FOR void*;
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DObject_getUserData : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DObject_getObjType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DObject* cobj = (cocos2d::Physics3DObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DObject_getObjType : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getObjType();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DObject_getObjType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DObject_setPhysicsWorld(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DObject* cobj = (cocos2d::Physics3DObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DObject_setPhysicsWorld : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Physics3DWorld* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Physics3DWorld*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DObject_setPhysicsWorld : Error processing arguments");
        cobj->setPhysicsWorld(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DObject_setPhysicsWorld : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DObject_getWorldTransform(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DObject* cobj = (cocos2d::Physics3DObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DObject_getWorldTransform : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Mat4 ret = cobj->getWorldTransform();
        jsval jsret = JSVAL_NULL;
        jsret = matrix_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DObject_getWorldTransform : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DObject_getPhysicsWorld(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DObject* cobj = (cocos2d::Physics3DObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DObject_getPhysicsWorld : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Physics3DWorld* ret = cobj->getPhysicsWorld();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DWorld>(cx, (cocos2d::Physics3DWorld*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DObject_getPhysicsWorld : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DObject_setMask(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DObject* cobj = (cocos2d::Physics3DObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DObject_setMask : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DObject_setMask : Error processing arguments");
        cobj->setMask(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DObject_setMask : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DObject_getCollisionCallback(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DObject* cobj = (cocos2d::Physics3DObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DObject_getCollisionCallback : Invalid Native Object");
    if (argc == 0) {
        const std::function<void (const cocos2d::Physics3DCollisionInfo &)>& ret = cobj->getCollisionCallback();
        jsval jsret = JSVAL_NULL;
        #pragma warning NO CONVERSION FROM NATIVE FOR std::function;
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DObject_getCollisionCallback : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DObject_getMask(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DObject* cobj = (cocos2d::Physics3DObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DObject_getMask : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->getMask();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DObject_getMask : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DObject_needCollisionCallback(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DObject* cobj = (cocos2d::Physics3DObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DObject_needCollisionCallback : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->needCollisionCallback();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DObject_needCollisionCallback : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}


void js_cocos2d_Physics3DObject_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Physics3DObject)", obj);
}

void js_register_cocos2dx_physics3d_Physics3DObject(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Physics3DObject_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Physics3DObject_class->name = "Physics3DObject";
    jsb_cocos2d_Physics3DObject_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3DObject_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Physics3DObject_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3DObject_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Physics3DObject_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Physics3DObject_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Physics3DObject_class->convert = JS_ConvertStub;
    jsb_cocos2d_Physics3DObject_class->finalize = js_cocos2d_Physics3DObject_finalize;
    jsb_cocos2d_Physics3DObject_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setUserData", js_cocos2dx_physics3d_Physics3DObject_setUserData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUserData", js_cocos2dx_physics3d_Physics3DObject_getUserData, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getObjType", js_cocos2dx_physics3d_Physics3DObject_getObjType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPhysicsWorld", js_cocos2dx_physics3d_Physics3DObject_setPhysicsWorld, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getWorldTransform", js_cocos2dx_physics3d_Physics3DObject_getWorldTransform, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPhysicsWorld", js_cocos2dx_physics3d_Physics3DObject_getPhysicsWorld, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMask", js_cocos2dx_physics3d_Physics3DObject_setMask, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCollisionCallback", js_cocos2dx_physics3d_Physics3DObject_getCollisionCallback, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMask", js_cocos2dx_physics3d_Physics3DObject_getMask, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("needCollisionCallback", js_cocos2dx_physics3d_Physics3DObject_needCollisionCallback, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocos2d_Physics3DObject_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_cocos2d_Physics3DObject_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Physics3DObject", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::Physics3DObject> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_Physics3DObject_class;
        p->proto = jsb_cocos2d_Physics3DObject_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_Physics3DRigidBody_class;
JSObject *jsb_cocos2d_Physics3DRigidBody_prototype;

bool js_cocos2dx_physics3d_Physics3DRigidBody_setGravity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setGravity : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setGravity : Error processing arguments");
        cobj->setGravity(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_setGravity : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_getFriction(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getFriction : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getFriction();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_getFriction : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_setAngularFactor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    cocos2d::Physics3DRigidBody* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setAngularFactor : Invalid Native Object");
    do {
        if (argc == 1) {
            double arg0;
            ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
            if (!ok) { ok = true; break; }
            cobj->setAngularFactor(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            cocos2d::Vec3 arg0;
            ok &= jsval_to_vector3(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cobj->setAngularFactor(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_setAngularFactor : wrong number of arguments");
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_addConstraint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_addConstraint : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Physics3DConstraint* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Physics3DConstraint*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_addConstraint : Error processing arguments");
        cobj->addConstraint(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_addConstraint : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_getRigidBody(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getRigidBody : Invalid Native Object");
    if (argc == 0) {
        btRigidBody* ret = cobj->getRigidBody();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<btRigidBody>(cx, (btRigidBody*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_getRigidBody : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_getTotalForce(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getTotalForce : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec3 ret = cobj->getTotalForce();
        jsval jsret = JSVAL_NULL;
        jsret = vector3_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_getTotalForce : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_getConstraintCount(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getConstraintCount : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->getConstraintCount();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_getConstraintCount : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_applyCentralForce(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_applyCentralForce : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_applyCentralForce : Error processing arguments");
        cobj->applyCentralForce(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_applyCentralForce : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_setMassProps(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setMassProps : Invalid Native Object");
    if (argc == 2) {
        double arg0;
        cocos2d::Vec3 arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= jsval_to_vector3(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setMassProps : Error processing arguments");
        cobj->setMassProps(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_setMassProps : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_setFriction(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setFriction : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setFriction : Error processing arguments");
        cobj->setFriction(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_setFriction : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_setKinematic(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setKinematic : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setKinematic : Error processing arguments");
        cobj->setKinematic(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_setKinematic : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_setDamping(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setDamping : Invalid Native Object");
    if (argc == 2) {
        double arg0;
        double arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setDamping : Error processing arguments");
        cobj->setDamping(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_setDamping : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_applyImpulse(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_applyImpulse : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Vec3 arg0;
        cocos2d::Vec3 arg1;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        ok &= jsval_to_vector3(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_applyImpulse : Error processing arguments");
        cobj->applyImpulse(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_applyImpulse : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_isKinematic(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_isKinematic : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isKinematic();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_isKinematic : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_applyTorque(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_applyTorque : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_applyTorque : Error processing arguments");
        cobj->applyTorque(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_applyTorque : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_setCcdMotionThreshold(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setCcdMotionThreshold : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setCcdMotionThreshold : Error processing arguments");
        cobj->setCcdMotionThreshold(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_setCcdMotionThreshold : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_setRollingFriction(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setRollingFriction : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setRollingFriction : Error processing arguments");
        cobj->setRollingFriction(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_setRollingFriction : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_getCcdMotionThreshold(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getCcdMotionThreshold : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getCcdMotionThreshold();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_getCcdMotionThreshold : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_getLinearFactor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getLinearFactor : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec3 ret = cobj->getLinearFactor();
        jsval jsret = JSVAL_NULL;
        jsret = vector3_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_getLinearFactor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_applyDamping(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_applyDamping : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_applyDamping : Error processing arguments");
        cobj->applyDamping(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_applyDamping : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_getAngularVelocity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getAngularVelocity : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec3 ret = cobj->getAngularVelocity();
        jsval jsret = JSVAL_NULL;
        jsret = vector3_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_getAngularVelocity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_init : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Physics3DRigidBodyDes* arg0;
        #pragma warning NO CONVERSION TO NATIVE FOR Physics3DRigidBodyDes*
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_init : Error processing arguments");
        bool ret = cobj->init(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_init : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_applyTorqueImpulse(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_applyTorqueImpulse : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_applyTorqueImpulse : Error processing arguments");
        cobj->applyTorqueImpulse(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_applyTorqueImpulse : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_setActive(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setActive : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setActive : Error processing arguments");
        cobj->setActive(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_setActive : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_setLinearFactor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setLinearFactor : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setLinearFactor : Error processing arguments");
        cobj->setLinearFactor(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_setLinearFactor : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_setLinearVelocity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setLinearVelocity : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setLinearVelocity : Error processing arguments");
        cobj->setLinearVelocity(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_setLinearVelocity : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_getLinearVelocity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getLinearVelocity : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec3 ret = cobj->getLinearVelocity();
        jsval jsret = JSVAL_NULL;
        jsret = vector3_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_getLinearVelocity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_setCcdSweptSphereRadius(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setCcdSweptSphereRadius : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setCcdSweptSphereRadius : Error processing arguments");
        cobj->setCcdSweptSphereRadius(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_setCcdSweptSphereRadius : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_applyForce(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_applyForce : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Vec3 arg0;
        cocos2d::Vec3 arg1;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        ok &= jsval_to_vector3(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_applyForce : Error processing arguments");
        cobj->applyForce(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_applyForce : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_setAngularVelocity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setAngularVelocity : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setAngularVelocity : Error processing arguments");
        cobj->setAngularVelocity(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_setAngularVelocity : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_applyCentralImpulse(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_applyCentralImpulse : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_applyCentralImpulse : Error processing arguments");
        cobj->applyCentralImpulse(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_applyCentralImpulse : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_getGravity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getGravity : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec3 ret = cobj->getGravity();
        jsval jsret = JSVAL_NULL;
        jsret = vector3_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_getGravity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_getRollingFriction(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getRollingFriction : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRollingFriction();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_getRollingFriction : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_setCenterOfMassTransform(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setCenterOfMassTransform : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Mat4 arg0;
        ok &= jsval_to_matrix(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setCenterOfMassTransform : Error processing arguments");
        cobj->setCenterOfMassTransform(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_setCenterOfMassTransform : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_setInvInertiaDiagLocal(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setInvInertiaDiagLocal : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setInvInertiaDiagLocal : Error processing arguments");
        cobj->setInvInertiaDiagLocal(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_setInvInertiaDiagLocal : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_removeConstraint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    cocos2d::Physics3DRigidBody* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_removeConstraint : Invalid Native Object");
    do {
        if (argc == 1) {
            unsigned int arg0;
            ok &= jsval_to_uint32(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cobj->removeConstraint(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            cocos2d::Physics3DConstraint* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Physics3DConstraint*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cobj->removeConstraint(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_removeConstraint : wrong number of arguments");
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_getTotalTorque(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getTotalTorque : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec3 ret = cobj->getTotalTorque();
        jsval jsret = JSVAL_NULL;
        jsret = vector3_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_getTotalTorque : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_getInvMass(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getInvMass : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getInvMass();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_getInvMass : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_getConstraint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getConstraint : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getConstraint : Error processing arguments");
        cocos2d::Physics3DConstraint* ret = cobj->getConstraint(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DConstraint>(cx, (cocos2d::Physics3DConstraint*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_getConstraint : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_getRestitution(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getRestitution : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRestitution();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_getRestitution : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_getCcdSweptSphereRadius(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getCcdSweptSphereRadius : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getCcdSweptSphereRadius();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_getCcdSweptSphereRadius : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_getHitFraction(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getHitFraction : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getHitFraction();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_getHitFraction : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_getAngularDamping(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getAngularDamping : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getAngularDamping();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_getAngularDamping : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_getInvInertiaDiagLocal(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getInvInertiaDiagLocal : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec3 ret = cobj->getInvInertiaDiagLocal();
        jsval jsret = JSVAL_NULL;
        jsret = vector3_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_getInvInertiaDiagLocal : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_getCenterOfMassTransform(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getCenterOfMassTransform : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Mat4 ret = cobj->getCenterOfMassTransform();
        jsval jsret = JSVAL_NULL;
        jsret = matrix_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_getCenterOfMassTransform : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_getAngularFactor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getAngularFactor : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec3 ret = cobj->getAngularFactor();
        jsval jsret = JSVAL_NULL;
        jsret = vector3_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_getAngularFactor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_setRestitution(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setRestitution : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setRestitution : Error processing arguments");
        cobj->setRestitution(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_setRestitution : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_setHitFraction(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setHitFraction : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_setHitFraction : Error processing arguments");
        cobj->setHitFraction(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_setHitFraction : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_getLinearDamping(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DRigidBody* cobj = (cocos2d::Physics3DRigidBody *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DRigidBody_getLinearDamping : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getLinearDamping();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DRigidBody_getLinearDamping : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DRigidBody_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::Physics3DRigidBody* cobj = new (std::nothrow) cocos2d::Physics3DRigidBody();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::Physics3DRigidBody> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::Physics3DRigidBody");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Physics3DObject_prototype;

void js_cocos2d_Physics3DRigidBody_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Physics3DRigidBody)", obj);
}

void js_register_cocos2dx_physics3d_Physics3DRigidBody(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Physics3DRigidBody_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Physics3DRigidBody_class->name = "Physics3DRigidBody";
    jsb_cocos2d_Physics3DRigidBody_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3DRigidBody_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Physics3DRigidBody_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3DRigidBody_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Physics3DRigidBody_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Physics3DRigidBody_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Physics3DRigidBody_class->convert = JS_ConvertStub;
    jsb_cocos2d_Physics3DRigidBody_class->finalize = js_cocos2d_Physics3DRigidBody_finalize;
    jsb_cocos2d_Physics3DRigidBody_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setGravity", js_cocos2dx_physics3d_Physics3DRigidBody_setGravity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFriction", js_cocos2dx_physics3d_Physics3DRigidBody_getFriction, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAngularFactor", js_cocos2dx_physics3d_Physics3DRigidBody_setAngularFactor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addConstraint", js_cocos2dx_physics3d_Physics3DRigidBody_addConstraint, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRigidBody", js_cocos2dx_physics3d_Physics3DRigidBody_getRigidBody, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTotalForce", js_cocos2dx_physics3d_Physics3DRigidBody_getTotalForce, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getConstraintCount", js_cocos2dx_physics3d_Physics3DRigidBody_getConstraintCount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("applyCentralForce", js_cocos2dx_physics3d_Physics3DRigidBody_applyCentralForce, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMassProps", js_cocos2dx_physics3d_Physics3DRigidBody_setMassProps, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFriction", js_cocos2dx_physics3d_Physics3DRigidBody_setFriction, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setKinematic", js_cocos2dx_physics3d_Physics3DRigidBody_setKinematic, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDamping", js_cocos2dx_physics3d_Physics3DRigidBody_setDamping, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("applyImpulse", js_cocos2dx_physics3d_Physics3DRigidBody_applyImpulse, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isKinematic", js_cocos2dx_physics3d_Physics3DRigidBody_isKinematic, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("applyTorque", js_cocos2dx_physics3d_Physics3DRigidBody_applyTorque, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCcdMotionThreshold", js_cocos2dx_physics3d_Physics3DRigidBody_setCcdMotionThreshold, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRollingFriction", js_cocos2dx_physics3d_Physics3DRigidBody_setRollingFriction, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCcdMotionThreshold", js_cocos2dx_physics3d_Physics3DRigidBody_getCcdMotionThreshold, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLinearFactor", js_cocos2dx_physics3d_Physics3DRigidBody_getLinearFactor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("applyDamping", js_cocos2dx_physics3d_Physics3DRigidBody_applyDamping, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAngularVelocity", js_cocos2dx_physics3d_Physics3DRigidBody_getAngularVelocity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_physics3d_Physics3DRigidBody_init, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("applyTorqueImpulse", js_cocos2dx_physics3d_Physics3DRigidBody_applyTorqueImpulse, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setActive", js_cocos2dx_physics3d_Physics3DRigidBody_setActive, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLinearFactor", js_cocos2dx_physics3d_Physics3DRigidBody_setLinearFactor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLinearVelocity", js_cocos2dx_physics3d_Physics3DRigidBody_setLinearVelocity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLinearVelocity", js_cocos2dx_physics3d_Physics3DRigidBody_getLinearVelocity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCcdSweptSphereRadius", js_cocos2dx_physics3d_Physics3DRigidBody_setCcdSweptSphereRadius, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("applyForce", js_cocos2dx_physics3d_Physics3DRigidBody_applyForce, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAngularVelocity", js_cocos2dx_physics3d_Physics3DRigidBody_setAngularVelocity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("applyCentralImpulse", js_cocos2dx_physics3d_Physics3DRigidBody_applyCentralImpulse, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getGravity", js_cocos2dx_physics3d_Physics3DRigidBody_getGravity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRollingFriction", js_cocos2dx_physics3d_Physics3DRigidBody_getRollingFriction, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCenterOfMassTransform", js_cocos2dx_physics3d_Physics3DRigidBody_setCenterOfMassTransform, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setInvInertiaDiagLocal", js_cocos2dx_physics3d_Physics3DRigidBody_setInvInertiaDiagLocal, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeConstraint", js_cocos2dx_physics3d_Physics3DRigidBody_removeConstraint, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTotalTorque", js_cocos2dx_physics3d_Physics3DRigidBody_getTotalTorque, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInvMass", js_cocos2dx_physics3d_Physics3DRigidBody_getInvMass, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getConstraint", js_cocos2dx_physics3d_Physics3DRigidBody_getConstraint, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRestitution", js_cocos2dx_physics3d_Physics3DRigidBody_getRestitution, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCcdSweptSphereRadius", js_cocos2dx_physics3d_Physics3DRigidBody_getCcdSweptSphereRadius, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getHitFraction", js_cocos2dx_physics3d_Physics3DRigidBody_getHitFraction, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAngularDamping", js_cocos2dx_physics3d_Physics3DRigidBody_getAngularDamping, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInvInertiaDiagLocal", js_cocos2dx_physics3d_Physics3DRigidBody_getInvInertiaDiagLocal, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCenterOfMassTransform", js_cocos2dx_physics3d_Physics3DRigidBody_getCenterOfMassTransform, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAngularFactor", js_cocos2dx_physics3d_Physics3DRigidBody_getAngularFactor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRestitution", js_cocos2dx_physics3d_Physics3DRigidBody_setRestitution, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setHitFraction", js_cocos2dx_physics3d_Physics3DRigidBody_setHitFraction, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLinearDamping", js_cocos2dx_physics3d_Physics3DRigidBody_getLinearDamping, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocos2d_Physics3DRigidBody_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Physics3DObject_prototype),
        jsb_cocos2d_Physics3DRigidBody_class,
        js_cocos2dx_physics3d_Physics3DRigidBody_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Physics3DRigidBody", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::Physics3DRigidBody> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_Physics3DRigidBody_class;
        p->proto = jsb_cocos2d_Physics3DRigidBody_prototype;
        p->parentProto = jsb_cocos2d_Physics3DObject_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_Physics3DComponent_class;
JSObject *jsb_cocos2d_Physics3DComponent_prototype;

bool js_cocos2dx_physics3d_Physics3DComponent_syncNodeToPhysics(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DComponent* cobj = (cocos2d::Physics3DComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DComponent_syncNodeToPhysics : Invalid Native Object");
    if (argc == 0) {
        cobj->syncNodeToPhysics();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DComponent_syncNodeToPhysics : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DComponent_addToPhysicsWorld(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DComponent* cobj = (cocos2d::Physics3DComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DComponent_addToPhysicsWorld : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Physics3DWorld* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Physics3DWorld*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DComponent_addToPhysicsWorld : Error processing arguments");
        cobj->addToPhysicsWorld(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DComponent_addToPhysicsWorld : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DComponent_syncPhysicsToNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DComponent* cobj = (cocos2d::Physics3DComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DComponent_syncPhysicsToNode : Invalid Native Object");
    if (argc == 0) {
        cobj->syncPhysicsToNode();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DComponent_syncPhysicsToNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DComponent_getPhysics3DObject(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DComponent* cobj = (cocos2d::Physics3DComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DComponent_getPhysics3DObject : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Physics3DObject* ret = cobj->getPhysics3DObject();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DObject>(cx, (cocos2d::Physics3DObject*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DComponent_getPhysics3DObject : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DComponent_setPhysics3DObject(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DComponent* cobj = (cocos2d::Physics3DComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DComponent_setPhysics3DObject : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Physics3DObject* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Physics3DObject*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DComponent_setPhysics3DObject : Error processing arguments");
        cobj->setPhysics3DObject(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DComponent_setPhysics3DObject : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DComponent_setSyncFlag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DComponent* cobj = (cocos2d::Physics3DComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DComponent_setSyncFlag : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Physics3DComponent::PhysicsSyncFlag arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DComponent_setSyncFlag : Error processing arguments");
        cobj->setSyncFlag(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DComponent_setSyncFlag : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DComponent_setTransformInPhysics(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DComponent* cobj = (cocos2d::Physics3DComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DComponent_setTransformInPhysics : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Vec3 arg0;
        cocos2d::Quaternion arg1;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        ok &= jsval_to_quaternion(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DComponent_setTransformInPhysics : Error processing arguments");
        cobj->setTransformInPhysics(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DComponent_setTransformInPhysics : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DComponent_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            cocos2d::Physics3DObject* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Physics3DObject*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DComponent* ret = cocos2d::Physics3DComponent::create(arg0);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DComponent>(cx, (cocos2d::Physics3DComponent*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    do {
        if (argc == 2) {
            cocos2d::Physics3DObject* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Physics3DObject*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Vec3 arg1;
            ok &= jsval_to_vector3(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DComponent* ret = cocos2d::Physics3DComponent::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DComponent>(cx, (cocos2d::Physics3DComponent*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    do {
        if (argc == 3) {
            cocos2d::Physics3DObject* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Physics3DObject*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Vec3 arg1;
            ok &= jsval_to_vector3(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::Quaternion arg2;
            ok &= jsval_to_quaternion(cx, args.get(2), &arg2);
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DComponent* ret = cocos2d::Physics3DComponent::create(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DComponent>(cx, (cocos2d::Physics3DComponent*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 0) {
            cocos2d::Physics3DComponent* ret = cocos2d::Physics3DComponent::create();
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DComponent>(cx, (cocos2d::Physics3DComponent*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DComponent_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_physics3d_Physics3DComponent_getPhysics3DComponentName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::string& ret = cocos2d::Physics3DComponent::getPhysics3DComponentName();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DComponent_getPhysics3DComponentName : wrong number of arguments");
    return false;
}

bool js_cocos2dx_physics3d_Physics3DComponent_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::Physics3DComponent* cobj = new (std::nothrow) cocos2d::Physics3DComponent();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::Physics3DComponent> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::Physics3DComponent");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Component_prototype;

void js_cocos2d_Physics3DComponent_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Physics3DComponent)", obj);
}

void js_register_cocos2dx_physics3d_Physics3DComponent(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Physics3DComponent_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Physics3DComponent_class->name = "Physics3DComponent";
    jsb_cocos2d_Physics3DComponent_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3DComponent_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Physics3DComponent_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3DComponent_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Physics3DComponent_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Physics3DComponent_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Physics3DComponent_class->convert = JS_ConvertStub;
    jsb_cocos2d_Physics3DComponent_class->finalize = js_cocos2d_Physics3DComponent_finalize;
    jsb_cocos2d_Physics3DComponent_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("syncNodeToPhysics", js_cocos2dx_physics3d_Physics3DComponent_syncNodeToPhysics, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addToPhysicsWorld", js_cocos2dx_physics3d_Physics3DComponent_addToPhysicsWorld, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("syncPhysicsToNode", js_cocos2dx_physics3d_Physics3DComponent_syncPhysicsToNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPhysics3DObject", js_cocos2dx_physics3d_Physics3DComponent_getPhysics3DObject, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPhysics3DObject", js_cocos2dx_physics3d_Physics3DComponent_setPhysics3DObject, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSyncFlag", js_cocos2dx_physics3d_Physics3DComponent_setSyncFlag, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTransformInPhysics", js_cocos2dx_physics3d_Physics3DComponent_setTransformInPhysics, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_physics3d_Physics3DComponent_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPhysics3DComponentName", js_cocos2dx_physics3d_Physics3DComponent_getPhysics3DComponentName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_Physics3DComponent_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Component_prototype),
        jsb_cocos2d_Physics3DComponent_class,
        js_cocos2dx_physics3d_Physics3DComponent_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Physics3DComponent", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::Physics3DComponent> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_Physics3DComponent_class;
        p->proto = jsb_cocos2d_Physics3DComponent_prototype;
        p->parentProto = jsb_cocos2d_Component_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_PhysicsSprite3D_class;
JSObject *jsb_cocos2d_PhysicsSprite3D_prototype;

bool js_cocos2dx_physics3d_PhysicsSprite3D_syncNodeToPhysics(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PhysicsSprite3D* cobj = (cocos2d::PhysicsSprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_PhysicsSprite3D_syncNodeToPhysics : Invalid Native Object");
    if (argc == 0) {
        cobj->syncNodeToPhysics();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_PhysicsSprite3D_syncNodeToPhysics : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_PhysicsSprite3D_syncPhysicsToNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PhysicsSprite3D* cobj = (cocos2d::PhysicsSprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_PhysicsSprite3D_syncPhysicsToNode : Invalid Native Object");
    if (argc == 0) {
        cobj->syncPhysicsToNode();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_PhysicsSprite3D_syncPhysicsToNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_PhysicsSprite3D_getPhysicsObj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PhysicsSprite3D* cobj = (cocos2d::PhysicsSprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_PhysicsSprite3D_getPhysicsObj : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Physics3DObject* ret = cobj->getPhysicsObj();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DObject>(cx, (cocos2d::Physics3DObject*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_PhysicsSprite3D_getPhysicsObj : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_PhysicsSprite3D_setSyncFlag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PhysicsSprite3D* cobj = (cocos2d::PhysicsSprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_PhysicsSprite3D_setSyncFlag : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Physics3DComponent::PhysicsSyncFlag arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_PhysicsSprite3D_setSyncFlag : Error processing arguments");
        cobj->setSyncFlag(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_PhysicsSprite3D_setSyncFlag : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_PhysicsSprite3D_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::PhysicsSprite3D* cobj = new (std::nothrow) cocos2d::PhysicsSprite3D();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::PhysicsSprite3D> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::PhysicsSprite3D");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Sprite3D_prototype;

void js_cocos2d_PhysicsSprite3D_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PhysicsSprite3D)", obj);
}

void js_register_cocos2dx_physics3d_PhysicsSprite3D(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_PhysicsSprite3D_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_PhysicsSprite3D_class->name = "PhysicsSprite3D";
    jsb_cocos2d_PhysicsSprite3D_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_PhysicsSprite3D_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_PhysicsSprite3D_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_PhysicsSprite3D_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_PhysicsSprite3D_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_PhysicsSprite3D_class->resolve = JS_ResolveStub;
    jsb_cocos2d_PhysicsSprite3D_class->convert = JS_ConvertStub;
    jsb_cocos2d_PhysicsSprite3D_class->finalize = js_cocos2d_PhysicsSprite3D_finalize;
    jsb_cocos2d_PhysicsSprite3D_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("syncNodeToPhysics", js_cocos2dx_physics3d_PhysicsSprite3D_syncNodeToPhysics, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("syncPhysicsToNode", js_cocos2dx_physics3d_PhysicsSprite3D_syncPhysicsToNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPhysicsObj", js_cocos2dx_physics3d_PhysicsSprite3D_getPhysicsObj, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSyncFlag", js_cocos2dx_physics3d_PhysicsSprite3D_setSyncFlag, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocos2d_PhysicsSprite3D_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Sprite3D_prototype),
        jsb_cocos2d_PhysicsSprite3D_class,
        js_cocos2dx_physics3d_PhysicsSprite3D_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "PhysicsSprite3D", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::PhysicsSprite3D> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_PhysicsSprite3D_class;
        p->proto = jsb_cocos2d_PhysicsSprite3D_prototype;
        p->parentProto = jsb_cocos2d_Sprite3D_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_Physics3DWorld_class;
JSObject *jsb_cocos2d_Physics3DWorld_prototype;

bool js_cocos2dx_physics3d_Physics3DWorld_setGravity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DWorld* cobj = (cocos2d::Physics3DWorld *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_setGravity : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_setGravity : Error processing arguments");
        cobj->setGravity(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DWorld_setGravity : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DWorld_stepSimulate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DWorld* cobj = (cocos2d::Physics3DWorld *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_stepSimulate : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_stepSimulate : Error processing arguments");
        cobj->stepSimulate(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DWorld_stepSimulate : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DWorld_needCollisionChecking(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DWorld* cobj = (cocos2d::Physics3DWorld *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_needCollisionChecking : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->needCollisionChecking();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DWorld_needCollisionChecking : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DWorld_collisionChecking(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DWorld* cobj = (cocos2d::Physics3DWorld *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_collisionChecking : Invalid Native Object");
    if (argc == 0) {
        cobj->collisionChecking();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DWorld_collisionChecking : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DWorld_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DWorld* cobj = (cocos2d::Physics3DWorld *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_init : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Physics3DWorldDes* arg0;
        #pragma warning NO CONVERSION TO NATIVE FOR Physics3DWorldDes*
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_init : Error processing arguments");
        bool ret = cobj->init(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DWorld_init : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DWorld_removeAllPhysics3DObjects(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DWorld* cobj = (cocos2d::Physics3DWorld *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_removeAllPhysics3DObjects : Invalid Native Object");
    if (argc == 0) {
        cobj->removeAllPhysics3DObjects();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DWorld_removeAllPhysics3DObjects : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DWorld_isDebugDrawEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DWorld* cobj = (cocos2d::Physics3DWorld *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_isDebugDrawEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isDebugDrawEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DWorld_isDebugDrawEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DWorld_removeAllPhysics3DConstraints(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DWorld* cobj = (cocos2d::Physics3DWorld *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_removeAllPhysics3DConstraints : Invalid Native Object");
    if (argc == 0) {
        cobj->removeAllPhysics3DConstraints();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DWorld_removeAllPhysics3DConstraints : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DWorld_getGravity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DWorld* cobj = (cocos2d::Physics3DWorld *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_getGravity : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec3 ret = cobj->getGravity();
        jsval jsret = JSVAL_NULL;
        jsret = vector3_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DWorld_getGravity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DWorld_removePhysics3DConstraint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DWorld* cobj = (cocos2d::Physics3DWorld *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_removePhysics3DConstraint : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Physics3DConstraint* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Physics3DConstraint*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_removePhysics3DConstraint : Error processing arguments");
        cobj->removePhysics3DConstraint(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DWorld_removePhysics3DConstraint : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DWorld_addPhysics3DObject(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DWorld* cobj = (cocos2d::Physics3DWorld *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_addPhysics3DObject : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Physics3DObject* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Physics3DObject*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_addPhysics3DObject : Error processing arguments");
        cobj->addPhysics3DObject(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DWorld_addPhysics3DObject : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DWorld_setDebugDrawEnable(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DWorld* cobj = (cocos2d::Physics3DWorld *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_setDebugDrawEnable : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_setDebugDrawEnable : Error processing arguments");
        cobj->setDebugDrawEnable(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DWorld_setDebugDrawEnable : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DWorld_removePhysics3DObject(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DWorld* cobj = (cocos2d::Physics3DWorld *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_removePhysics3DObject : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Physics3DObject* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Physics3DObject*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_removePhysics3DObject : Error processing arguments");
        cobj->removePhysics3DObject(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DWorld_removePhysics3DObject : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DWorld_getPhysicsObject(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DWorld* cobj = (cocos2d::Physics3DWorld *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_getPhysicsObject : Invalid Native Object");
    if (argc == 1) {
        const btCollisionObject* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (const btCollisionObject*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_getPhysicsObject : Error processing arguments");
        cocos2d::Physics3DObject* ret = cobj->getPhysicsObject(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DObject>(cx, (cocos2d::Physics3DObject*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DWorld_getPhysicsObject : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DWorld_addPhysics3DConstraint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DWorld* cobj = (cocos2d::Physics3DWorld *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_addPhysics3DConstraint : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Physics3DConstraint* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Physics3DConstraint*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_addPhysics3DConstraint : Error processing arguments");
        cobj->addPhysics3DConstraint(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        cocos2d::Physics3DConstraint* arg0;
        bool arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Physics3DConstraint*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_addPhysics3DConstraint : Error processing arguments");
        cobj->addPhysics3DConstraint(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DWorld_addPhysics3DConstraint : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DWorld_debugDraw(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DWorld* cobj = (cocos2d::Physics3DWorld *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_debugDraw : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Renderer* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Renderer*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_debugDraw : Error processing arguments");
        cobj->debugDraw(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DWorld_debugDraw : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DWorld_sweepShape(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DWorld* cobj = (cocos2d::Physics3DWorld *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_sweepShape : Invalid Native Object");
    if (argc == 4) {
        cocos2d::Physics3DShape* arg0;
        cocos2d::Mat4 arg1;
        cocos2d::Mat4 arg2;
        cocos2d::Physics3DWorld::HitResult* arg3;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Physics3DShape*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_matrix(cx, args.get(1), &arg1);
        ok &= jsval_to_matrix(cx, args.get(2), &arg2);
        #pragma warning NO CONVERSION TO NATIVE FOR HitResult*
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_sweepShape : Error processing arguments");
        bool ret = cobj->sweepShape(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DWorld_sweepShape : wrong number of arguments: %d, was expecting %d", argc, 4);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DWorld_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Physics3DWorldDes* arg0;
        #pragma warning NO CONVERSION TO NATIVE FOR Physics3DWorldDes*
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DWorld_create : Error processing arguments");
        cocos2d::Physics3DWorld* ret = cocos2d::Physics3DWorld::create(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DWorld>(cx, (cocos2d::Physics3DWorld*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DWorld_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_physics3d_Physics3DWorld_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::Physics3DWorld* cobj = new (std::nothrow) cocos2d::Physics3DWorld();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::Physics3DWorld> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::Physics3DWorld");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}



void js_cocos2d_Physics3DWorld_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Physics3DWorld)", obj);
}

void js_register_cocos2dx_physics3d_Physics3DWorld(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Physics3DWorld_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Physics3DWorld_class->name = "Physics3DWorld";
    jsb_cocos2d_Physics3DWorld_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3DWorld_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Physics3DWorld_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3DWorld_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Physics3DWorld_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Physics3DWorld_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Physics3DWorld_class->convert = JS_ConvertStub;
    jsb_cocos2d_Physics3DWorld_class->finalize = js_cocos2d_Physics3DWorld_finalize;
    jsb_cocos2d_Physics3DWorld_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setGravity", js_cocos2dx_physics3d_Physics3DWorld_setGravity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stepSimulate", js_cocos2dx_physics3d_Physics3DWorld_stepSimulate, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("needCollisionChecking", js_cocos2dx_physics3d_Physics3DWorld_needCollisionChecking, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("collisionChecking", js_cocos2dx_physics3d_Physics3DWorld_collisionChecking, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_physics3d_Physics3DWorld_init, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeAllPhysics3DObjects", js_cocos2dx_physics3d_Physics3DWorld_removeAllPhysics3DObjects, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isDebugDrawEnabled", js_cocos2dx_physics3d_Physics3DWorld_isDebugDrawEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeAllPhysics3DConstraints", js_cocos2dx_physics3d_Physics3DWorld_removeAllPhysics3DConstraints, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getGravity", js_cocos2dx_physics3d_Physics3DWorld_getGravity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removePhysics3DConstraint", js_cocos2dx_physics3d_Physics3DWorld_removePhysics3DConstraint, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addPhysics3DObject", js_cocos2dx_physics3d_Physics3DWorld_addPhysics3DObject, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDebugDrawEnable", js_cocos2dx_physics3d_Physics3DWorld_setDebugDrawEnable, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removePhysics3DObject", js_cocos2dx_physics3d_Physics3DWorld_removePhysics3DObject, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPhysicsObject", js_cocos2dx_physics3d_Physics3DWorld_getPhysicsObject, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addPhysics3DConstraint", js_cocos2dx_physics3d_Physics3DWorld_addPhysics3DConstraint, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("debugDraw", js_cocos2dx_physics3d_Physics3DWorld_debugDraw, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("sweepShape", js_cocos2dx_physics3d_Physics3DWorld_sweepShape, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_physics3d_Physics3DWorld_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_Physics3DWorld_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_cocos2d_Physics3DWorld_class,
        js_cocos2dx_physics3d_Physics3DWorld_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Physics3DWorld", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::Physics3DWorld> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_Physics3DWorld_class;
        p->proto = jsb_cocos2d_Physics3DWorld_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_Physics3DConstraint_class;
JSObject *jsb_cocos2d_Physics3DConstraint_prototype;

bool js_cocos2dx_physics3d_Physics3DConstraint_setEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConstraint* cobj = (cocos2d::Physics3DConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConstraint_setEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DConstraint_setEnabled : Error processing arguments");
        cobj->setEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConstraint_setEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConstraint_setBreakingImpulse(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConstraint* cobj = (cocos2d::Physics3DConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConstraint_setBreakingImpulse : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DConstraint_setBreakingImpulse : Error processing arguments");
        cobj->setBreakingImpulse(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConstraint_setBreakingImpulse : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConstraint_getUserData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConstraint* cobj = (cocos2d::Physics3DConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConstraint_getUserData : Invalid Native Object");
    if (argc == 0) {
        void* ret = cobj->getUserData();
        jsval jsret = JSVAL_NULL;
        #pragma warning NO CONVERSION FROM NATIVE FOR void*;
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConstraint_getUserData : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConstraint_getBreakingImpulse(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConstraint* cobj = (cocos2d::Physics3DConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConstraint_getBreakingImpulse : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getBreakingImpulse();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConstraint_getBreakingImpulse : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConstraint_getBodyA(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConstraint* cobj = (cocos2d::Physics3DConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConstraint_getBodyA : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Physics3DRigidBody* ret = cobj->getBodyA();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DRigidBody>(cx, (cocos2d::Physics3DRigidBody*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConstraint_getBodyA : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConstraint_isEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConstraint* cobj = (cocos2d::Physics3DConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConstraint_isEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConstraint_isEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConstraint_getOverrideNumSolverIterations(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConstraint* cobj = (cocos2d::Physics3DConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConstraint_getOverrideNumSolverIterations : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getOverrideNumSolverIterations();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConstraint_getOverrideNumSolverIterations : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConstraint_getBodyB(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConstraint* cobj = (cocos2d::Physics3DConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConstraint_getBodyB : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Physics3DRigidBody* ret = cobj->getBodyB();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DRigidBody>(cx, (cocos2d::Physics3DRigidBody*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConstraint_getBodyB : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConstraint_setOverrideNumSolverIterations(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConstraint* cobj = (cocos2d::Physics3DConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConstraint_setOverrideNumSolverIterations : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DConstraint_setOverrideNumSolverIterations : Error processing arguments");
        cobj->setOverrideNumSolverIterations(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConstraint_setOverrideNumSolverIterations : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConstraint_getConstraintType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConstraint* cobj = (cocos2d::Physics3DConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConstraint_getConstraintType : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getConstraintType();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConstraint_getConstraintType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConstraint_setUserData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConstraint* cobj = (cocos2d::Physics3DConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConstraint_setUserData : Invalid Native Object");
    if (argc == 1) {
        void* arg0;
        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DConstraint_setUserData : Error processing arguments");
        cobj->setUserData(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConstraint_setUserData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConstraint_getbtContraint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConstraint* cobj = (cocos2d::Physics3DConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConstraint_getbtContraint : Invalid Native Object");
    if (argc == 0) {
        btTypedConstraint* ret = cobj->getbtContraint();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<btTypedConstraint>(cx, (btTypedConstraint*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConstraint_getbtContraint : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}


void js_cocos2d_Physics3DConstraint_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Physics3DConstraint)", obj);
}

void js_register_cocos2dx_physics3d_Physics3DConstraint(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Physics3DConstraint_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Physics3DConstraint_class->name = "Physics3DConstraint";
    jsb_cocos2d_Physics3DConstraint_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3DConstraint_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Physics3DConstraint_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3DConstraint_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Physics3DConstraint_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Physics3DConstraint_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Physics3DConstraint_class->convert = JS_ConvertStub;
    jsb_cocos2d_Physics3DConstraint_class->finalize = js_cocos2d_Physics3DConstraint_finalize;
    jsb_cocos2d_Physics3DConstraint_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setEnabled", js_cocos2dx_physics3d_Physics3DConstraint_setEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBreakingImpulse", js_cocos2dx_physics3d_Physics3DConstraint_setBreakingImpulse, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUserData", js_cocos2dx_physics3d_Physics3DConstraint_getUserData, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBreakingImpulse", js_cocos2dx_physics3d_Physics3DConstraint_getBreakingImpulse, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBodyA", js_cocos2dx_physics3d_Physics3DConstraint_getBodyA, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isEnabled", js_cocos2dx_physics3d_Physics3DConstraint_isEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getOverrideNumSolverIterations", js_cocos2dx_physics3d_Physics3DConstraint_getOverrideNumSolverIterations, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBodyB", js_cocos2dx_physics3d_Physics3DConstraint_getBodyB, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setOverrideNumSolverIterations", js_cocos2dx_physics3d_Physics3DConstraint_setOverrideNumSolverIterations, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getConstraintType", js_cocos2dx_physics3d_Physics3DConstraint_getConstraintType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setUserData", js_cocos2dx_physics3d_Physics3DConstraint_setUserData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getbtContraint", js_cocos2dx_physics3d_Physics3DConstraint_getbtContraint, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocos2d_Physics3DConstraint_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_cocos2d_Physics3DConstraint_class,
        dummy_constructor<cocos2d::Physics3DConstraint>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Physics3DConstraint", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::Physics3DConstraint> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_Physics3DConstraint_class;
        p->proto = jsb_cocos2d_Physics3DConstraint_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_Physics3DPointToPointConstraint_class;
JSObject *jsb_cocos2d_Physics3DPointToPointConstraint_prototype;

bool js_cocos2dx_physics3d_Physics3DPointToPointConstraint_getPivotPointInA(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DPointToPointConstraint* cobj = (cocos2d::Physics3DPointToPointConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DPointToPointConstraint_getPivotPointInA : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec3 ret = cobj->getPivotPointInA();
        jsval jsret = JSVAL_NULL;
        jsret = vector3_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DPointToPointConstraint_getPivotPointInA : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DPointToPointConstraint_getPivotPointInB(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DPointToPointConstraint* cobj = (cocos2d::Physics3DPointToPointConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DPointToPointConstraint_getPivotPointInB : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec3 ret = cobj->getPivotPointInB();
        jsval jsret = JSVAL_NULL;
        jsret = vector3_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DPointToPointConstraint_getPivotPointInB : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DPointToPointConstraint_setPivotPointInA(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DPointToPointConstraint* cobj = (cocos2d::Physics3DPointToPointConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DPointToPointConstraint_setPivotPointInA : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DPointToPointConstraint_setPivotPointInA : Error processing arguments");
        cobj->setPivotPointInA(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DPointToPointConstraint_setPivotPointInA : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DPointToPointConstraint_setPivotPointInB(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DPointToPointConstraint* cobj = (cocos2d::Physics3DPointToPointConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DPointToPointConstraint_setPivotPointInB : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DPointToPointConstraint_setPivotPointInB : Error processing arguments");
        cobj->setPivotPointInB(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DPointToPointConstraint_setPivotPointInB : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DPointToPointConstraint_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 4) {
            cocos2d::Physics3DRigidBody* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DRigidBody* arg1;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(1).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Vec3 arg2;
            ok &= jsval_to_vector3(cx, args.get(2), &arg2);
            if (!ok) { ok = true; break; }
            cocos2d::Vec3 arg3;
            ok &= jsval_to_vector3(cx, args.get(3), &arg3);
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DPointToPointConstraint* ret = cocos2d::Physics3DPointToPointConstraint::create(arg0, arg1, arg2, arg3);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DPointToPointConstraint>(cx, (cocos2d::Physics3DPointToPointConstraint*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 2) {
            cocos2d::Physics3DRigidBody* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Vec3 arg1;
            ok &= jsval_to_vector3(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DPointToPointConstraint* ret = cocos2d::Physics3DPointToPointConstraint::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DPointToPointConstraint>(cx, (cocos2d::Physics3DPointToPointConstraint*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DPointToPointConstraint_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_physics3d_Physics3DPointToPointConstraint_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::Physics3DPointToPointConstraint* cobj = new (std::nothrow) cocos2d::Physics3DPointToPointConstraint();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::Physics3DPointToPointConstraint> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::Physics3DPointToPointConstraint");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Physics3DConstraint_prototype;

void js_cocos2d_Physics3DPointToPointConstraint_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Physics3DPointToPointConstraint)", obj);
}

void js_register_cocos2dx_physics3d_Physics3DPointToPointConstraint(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Physics3DPointToPointConstraint_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Physics3DPointToPointConstraint_class->name = "Physics3DPointToPointConstraint";
    jsb_cocos2d_Physics3DPointToPointConstraint_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3DPointToPointConstraint_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Physics3DPointToPointConstraint_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3DPointToPointConstraint_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Physics3DPointToPointConstraint_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Physics3DPointToPointConstraint_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Physics3DPointToPointConstraint_class->convert = JS_ConvertStub;
    jsb_cocos2d_Physics3DPointToPointConstraint_class->finalize = js_cocos2d_Physics3DPointToPointConstraint_finalize;
    jsb_cocos2d_Physics3DPointToPointConstraint_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getPivotPointInA", js_cocos2dx_physics3d_Physics3DPointToPointConstraint_getPivotPointInA, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPivotPointInB", js_cocos2dx_physics3d_Physics3DPointToPointConstraint_getPivotPointInB, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPivotPointInA", js_cocos2dx_physics3d_Physics3DPointToPointConstraint_setPivotPointInA, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPivotPointInB", js_cocos2dx_physics3d_Physics3DPointToPointConstraint_setPivotPointInB, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_physics3d_Physics3DPointToPointConstraint_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_Physics3DPointToPointConstraint_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Physics3DConstraint_prototype),
        jsb_cocos2d_Physics3DPointToPointConstraint_class,
        js_cocos2dx_physics3d_Physics3DPointToPointConstraint_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Physics3DPointToPointConstraint", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::Physics3DPointToPointConstraint> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_Physics3DPointToPointConstraint_class;
        p->proto = jsb_cocos2d_Physics3DPointToPointConstraint_prototype;
        p->parentProto = jsb_cocos2d_Physics3DConstraint_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_Physics3DHingeConstraint_class;
JSObject *jsb_cocos2d_Physics3DHingeConstraint_prototype;

bool js_cocos2dx_physics3d_Physics3DHingeConstraint_getHingeAngle(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    cocos2d::Physics3DHingeConstraint* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::Physics3DHingeConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getHingeAngle : Invalid Native Object");
    do {
        if (argc == 2) {
            cocos2d::Mat4 arg0;
            ok &= jsval_to_matrix(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::Mat4 arg1;
            ok &= jsval_to_matrix(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            double ret = cobj->getHingeAngle(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            jsret = DOUBLE_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 0) {
            double ret = cobj->getHingeAngle();
            jsval jsret = JSVAL_NULL;
            jsret = DOUBLE_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getHingeAngle : wrong number of arguments");
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_getMotorTargetVelosity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DHingeConstraint* cobj = (cocos2d::Physics3DHingeConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getMotorTargetVelosity : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMotorTargetVelosity();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getMotorTargetVelosity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_getFrameOffsetA(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DHingeConstraint* cobj = (cocos2d::Physics3DHingeConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getFrameOffsetA : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Mat4 ret = cobj->getFrameOffsetA();
        jsval jsret = JSVAL_NULL;
        jsret = matrix_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getFrameOffsetA : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_getFrameOffsetB(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DHingeConstraint* cobj = (cocos2d::Physics3DHingeConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getFrameOffsetB : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Mat4 ret = cobj->getFrameOffsetB();
        jsval jsret = JSVAL_NULL;
        jsret = matrix_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getFrameOffsetB : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_setMaxMotorImpulse(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DHingeConstraint* cobj = (cocos2d::Physics3DHingeConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setMaxMotorImpulse : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setMaxMotorImpulse : Error processing arguments");
        cobj->setMaxMotorImpulse(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setMaxMotorImpulse : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_enableAngularMotor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DHingeConstraint* cobj = (cocos2d::Physics3DHingeConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_enableAngularMotor : Invalid Native Object");
    if (argc == 3) {
        bool arg0;
        double arg1;
        double arg2;
        arg0 = JS::ToBoolean(args.get(0));
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_enableAngularMotor : Error processing arguments");
        cobj->enableAngularMotor(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_enableAngularMotor : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_getUpperLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DHingeConstraint* cobj = (cocos2d::Physics3DHingeConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getUpperLimit : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getUpperLimit();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getUpperLimit : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_getMaxMotorImpulse(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DHingeConstraint* cobj = (cocos2d::Physics3DHingeConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getMaxMotorImpulse : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMaxMotorImpulse();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getMaxMotorImpulse : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_getLowerLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DHingeConstraint* cobj = (cocos2d::Physics3DHingeConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getLowerLimit : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getLowerLimit();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getLowerLimit : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_setUseFrameOffset(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DHingeConstraint* cobj = (cocos2d::Physics3DHingeConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setUseFrameOffset : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setUseFrameOffset : Error processing arguments");
        cobj->setUseFrameOffset(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setUseFrameOffset : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_getEnableAngularMotor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DHingeConstraint* cobj = (cocos2d::Physics3DHingeConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getEnableAngularMotor : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getEnableAngularMotor();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getEnableAngularMotor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_enableMotor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DHingeConstraint* cobj = (cocos2d::Physics3DHingeConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_enableMotor : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_enableMotor : Error processing arguments");
        cobj->enableMotor(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_enableMotor : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_getBFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DHingeConstraint* cobj = (cocos2d::Physics3DHingeConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getBFrame : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Mat4 ret = cobj->getBFrame();
        jsval jsret = JSVAL_NULL;
        jsret = matrix_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getBFrame : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_setFrames(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DHingeConstraint* cobj = (cocos2d::Physics3DHingeConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setFrames : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Mat4 arg0;
        cocos2d::Mat4 arg1;
        ok &= jsval_to_matrix(cx, args.get(0), &arg0);
        ok &= jsval_to_matrix(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setFrames : Error processing arguments");
        cobj->setFrames(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setFrames : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_getUseFrameOffset(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DHingeConstraint* cobj = (cocos2d::Physics3DHingeConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getUseFrameOffset : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getUseFrameOffset();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getUseFrameOffset : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_setAngularOnly(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DHingeConstraint* cobj = (cocos2d::Physics3DHingeConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setAngularOnly : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setAngularOnly : Error processing arguments");
        cobj->setAngularOnly(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setAngularOnly : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_setLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DHingeConstraint* cobj = (cocos2d::Physics3DHingeConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setLimit : Invalid Native Object");
    if (argc == 2) {
        double arg0;
        double arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setLimit : Error processing arguments");
        cobj->setLimit(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 3) {
        double arg0;
        double arg1;
        double arg2;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setLimit : Error processing arguments");
        cobj->setLimit(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 4) {
        double arg0;
        double arg1;
        double arg2;
        double arg3;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= JS::ToNumber( cx, args.get(3), &arg3) && !isnan(arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setLimit : Error processing arguments");
        cobj->setLimit(arg0, arg1, arg2, arg3);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 5) {
        double arg0;
        double arg1;
        double arg2;
        double arg3;
        double arg4;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= JS::ToNumber( cx, args.get(3), &arg3) && !isnan(arg3);
        ok &= JS::ToNumber( cx, args.get(4), &arg4) && !isnan(arg4);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setLimit : Error processing arguments");
        cobj->setLimit(arg0, arg1, arg2, arg3, arg4);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setLimit : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_setMotorTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    cocos2d::Physics3DHingeConstraint* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::Physics3DHingeConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setMotorTarget : Invalid Native Object");
    do {
        if (argc == 2) {
            double arg0;
            ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
            if (!ok) { ok = true; break; }
            double arg1;
            ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
            if (!ok) { ok = true; break; }
            cobj->setMotorTarget(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            cocos2d::Quaternion arg0;
            ok &= jsval_to_quaternion(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            double arg1;
            ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
            if (!ok) { ok = true; break; }
            cobj->setMotorTarget(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setMotorTarget : wrong number of arguments");
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_getAngularOnly(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DHingeConstraint* cobj = (cocos2d::Physics3DHingeConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getAngularOnly : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getAngularOnly();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getAngularOnly : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_setAxis(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DHingeConstraint* cobj = (cocos2d::Physics3DHingeConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setAxis : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setAxis : Error processing arguments");
        cobj->setAxis(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_setAxis : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_getAFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DHingeConstraint* cobj = (cocos2d::Physics3DHingeConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getAFrame : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Mat4 ret = cobj->getAFrame();
        jsval jsret = JSVAL_NULL;
        jsret = matrix_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_getAFrame : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 3) {
            cocos2d::Physics3DRigidBody* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Vec3 arg1;
            ok &= jsval_to_vector3(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::Vec3 arg2;
            ok &= jsval_to_vector3(cx, args.get(2), &arg2);
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DHingeConstraint* ret = cocos2d::Physics3DHingeConstraint::create(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DHingeConstraint>(cx, (cocos2d::Physics3DHingeConstraint*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    do {
        if (argc == 4) {
            cocos2d::Physics3DRigidBody* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Vec3 arg1;
            ok &= jsval_to_vector3(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::Vec3 arg2;
            ok &= jsval_to_vector3(cx, args.get(2), &arg2);
            if (!ok) { ok = true; break; }
            bool arg3;
            arg3 = JS::ToBoolean(args.get(3));
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DHingeConstraint* ret = cocos2d::Physics3DHingeConstraint::create(arg0, arg1, arg2, arg3);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DHingeConstraint>(cx, (cocos2d::Physics3DHingeConstraint*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 2) {
            cocos2d::Physics3DRigidBody* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Mat4 arg1;
            ok &= jsval_to_matrix(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DHingeConstraint* ret = cocos2d::Physics3DHingeConstraint::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DHingeConstraint>(cx, (cocos2d::Physics3DHingeConstraint*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    do {
        if (argc == 3) {
            cocos2d::Physics3DRigidBody* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Mat4 arg1;
            ok &= jsval_to_matrix(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            bool arg2;
            arg2 = JS::ToBoolean(args.get(2));
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DHingeConstraint* ret = cocos2d::Physics3DHingeConstraint::create(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DHingeConstraint>(cx, (cocos2d::Physics3DHingeConstraint*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 6) {
            cocos2d::Physics3DRigidBody* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DRigidBody* arg1;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(1).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Vec3 arg2;
            ok &= jsval_to_vector3(cx, args.get(2), &arg2);
            if (!ok) { ok = true; break; }
            cocos2d::Vec3 arg3;
            ok &= jsval_to_vector3(cx, args.get(3), &arg3);
            if (!ok) { ok = true; break; }
            cocos2d::Vec3 arg4;
            ok &= jsval_to_vector3(cx, args.get(4), &arg4);
            if (!ok) { ok = true; break; }
            cocos2d::Vec3 arg5;
            ok &= jsval_to_vector3(cx, args.get(5), &arg5);
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DHingeConstraint* ret = cocos2d::Physics3DHingeConstraint::create(arg0, arg1, arg2, arg3, arg4, arg5);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DHingeConstraint>(cx, (cocos2d::Physics3DHingeConstraint*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    do {
        if (argc == 7) {
            cocos2d::Physics3DRigidBody* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DRigidBody* arg1;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(1).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Vec3 arg2;
            ok &= jsval_to_vector3(cx, args.get(2), &arg2);
            if (!ok) { ok = true; break; }
            cocos2d::Vec3 arg3;
            ok &= jsval_to_vector3(cx, args.get(3), &arg3);
            if (!ok) { ok = true; break; }
            cocos2d::Vec3 arg4;
            ok &= jsval_to_vector3(cx, args.get(4), &arg4);
            if (!ok) { ok = true; break; }
            cocos2d::Vec3 arg5;
            ok &= jsval_to_vector3(cx, args.get(5), &arg5);
            if (!ok) { ok = true; break; }
            bool arg6;
            arg6 = JS::ToBoolean(args.get(6));
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DHingeConstraint* ret = cocos2d::Physics3DHingeConstraint::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DHingeConstraint>(cx, (cocos2d::Physics3DHingeConstraint*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 4) {
            cocos2d::Physics3DRigidBody* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DRigidBody* arg1;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(1).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Mat4 arg2;
            ok &= jsval_to_matrix(cx, args.get(2), &arg2);
            if (!ok) { ok = true; break; }
            cocos2d::Mat4 arg3;
            ok &= jsval_to_matrix(cx, args.get(3), &arg3);
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DHingeConstraint* ret = cocos2d::Physics3DHingeConstraint::create(arg0, arg1, arg2, arg3);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DHingeConstraint>(cx, (cocos2d::Physics3DHingeConstraint*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    do {
        if (argc == 5) {
            cocos2d::Physics3DRigidBody* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DRigidBody* arg1;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(1).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Mat4 arg2;
            ok &= jsval_to_matrix(cx, args.get(2), &arg2);
            if (!ok) { ok = true; break; }
            cocos2d::Mat4 arg3;
            ok &= jsval_to_matrix(cx, args.get(3), &arg3);
            if (!ok) { ok = true; break; }
            bool arg4;
            arg4 = JS::ToBoolean(args.get(4));
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DHingeConstraint* ret = cocos2d::Physics3DHingeConstraint::create(arg0, arg1, arg2, arg3, arg4);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DHingeConstraint>(cx, (cocos2d::Physics3DHingeConstraint*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DHingeConstraint_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_physics3d_Physics3DHingeConstraint_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::Physics3DHingeConstraint* cobj = new (std::nothrow) cocos2d::Physics3DHingeConstraint();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::Physics3DHingeConstraint> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::Physics3DHingeConstraint");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Physics3DConstraint_prototype;

void js_cocos2d_Physics3DHingeConstraint_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Physics3DHingeConstraint)", obj);
}

void js_register_cocos2dx_physics3d_Physics3DHingeConstraint(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Physics3DHingeConstraint_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Physics3DHingeConstraint_class->name = "Physics3DHingeConstraint";
    jsb_cocos2d_Physics3DHingeConstraint_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3DHingeConstraint_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Physics3DHingeConstraint_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3DHingeConstraint_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Physics3DHingeConstraint_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Physics3DHingeConstraint_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Physics3DHingeConstraint_class->convert = JS_ConvertStub;
    jsb_cocos2d_Physics3DHingeConstraint_class->finalize = js_cocos2d_Physics3DHingeConstraint_finalize;
    jsb_cocos2d_Physics3DHingeConstraint_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getHingeAngle", js_cocos2dx_physics3d_Physics3DHingeConstraint_getHingeAngle, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMotorTargetVelosity", js_cocos2dx_physics3d_Physics3DHingeConstraint_getMotorTargetVelosity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFrameOffsetA", js_cocos2dx_physics3d_Physics3DHingeConstraint_getFrameOffsetA, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFrameOffsetB", js_cocos2dx_physics3d_Physics3DHingeConstraint_getFrameOffsetB, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaxMotorImpulse", js_cocos2dx_physics3d_Physics3DHingeConstraint_setMaxMotorImpulse, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("enableAngularMotor", js_cocos2dx_physics3d_Physics3DHingeConstraint_enableAngularMotor, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUpperLimit", js_cocos2dx_physics3d_Physics3DHingeConstraint_getUpperLimit, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaxMotorImpulse", js_cocos2dx_physics3d_Physics3DHingeConstraint_getMaxMotorImpulse, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLowerLimit", js_cocos2dx_physics3d_Physics3DHingeConstraint_getLowerLimit, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setUseFrameOffset", js_cocos2dx_physics3d_Physics3DHingeConstraint_setUseFrameOffset, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEnableAngularMotor", js_cocos2dx_physics3d_Physics3DHingeConstraint_getEnableAngularMotor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("enableMotor", js_cocos2dx_physics3d_Physics3DHingeConstraint_enableMotor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBFrame", js_cocos2dx_physics3d_Physics3DHingeConstraint_getBFrame, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFrames", js_cocos2dx_physics3d_Physics3DHingeConstraint_setFrames, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUseFrameOffset", js_cocos2dx_physics3d_Physics3DHingeConstraint_getUseFrameOffset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAngularOnly", js_cocos2dx_physics3d_Physics3DHingeConstraint_setAngularOnly, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLimit", js_cocos2dx_physics3d_Physics3DHingeConstraint_setLimit, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMotorTarget", js_cocos2dx_physics3d_Physics3DHingeConstraint_setMotorTarget, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAngularOnly", js_cocos2dx_physics3d_Physics3DHingeConstraint_getAngularOnly, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAxis", js_cocos2dx_physics3d_Physics3DHingeConstraint_setAxis, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAFrame", js_cocos2dx_physics3d_Physics3DHingeConstraint_getAFrame, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_physics3d_Physics3DHingeConstraint_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_Physics3DHingeConstraint_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Physics3DConstraint_prototype),
        jsb_cocos2d_Physics3DHingeConstraint_class,
        js_cocos2dx_physics3d_Physics3DHingeConstraint_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Physics3DHingeConstraint", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::Physics3DHingeConstraint> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_Physics3DHingeConstraint_class;
        p->proto = jsb_cocos2d_Physics3DHingeConstraint_prototype;
        p->parentProto = jsb_cocos2d_Physics3DConstraint_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_Physics3DSliderConstraint_class;
JSObject *jsb_cocos2d_Physics3DSliderConstraint_prototype;

bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setPoweredAngMotor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setPoweredAngMotor : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setPoweredAngMotor : Error processing arguments");
        cobj->setPoweredAngMotor(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setPoweredAngMotor : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingLimAng(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingLimAng : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getDampingLimAng();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingLimAng : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionOrthoLin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionOrthoLin : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionOrthoLin : Error processing arguments");
        cobj->setRestitutionOrthoLin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionOrthoLin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionDirLin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionDirLin : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionDirLin : Error processing arguments");
        cobj->setRestitutionDirLin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionDirLin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getLinearPos(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getLinearPos : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getLinearPos();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getLinearPos : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getFrameOffsetA(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getFrameOffsetA : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Mat4 ret = cobj->getFrameOffsetA();
        jsval jsret = JSVAL_NULL;
        jsret = matrix_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getFrameOffsetA : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getFrameOffsetB(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getFrameOffsetB : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Mat4 ret = cobj->getFrameOffsetB();
        jsval jsret = JSVAL_NULL;
        jsret = matrix_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getFrameOffsetB : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setPoweredLinMotor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setPoweredLinMotor : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setPoweredLinMotor : Error processing arguments");
        cobj->setPoweredLinMotor(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setPoweredLinMotor : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingDirAng(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingDirAng : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getDampingDirAng();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingDirAng : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionLimLin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionLimLin : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRestitutionLimLin();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionLimLin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessOrthoAng(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessOrthoAng : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getSoftnessOrthoAng();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessOrthoAng : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessOrthoLin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessOrthoLin : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessOrthoLin : Error processing arguments");
        cobj->setSoftnessOrthoLin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessOrthoLin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessLimLin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessLimLin : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessLimLin : Error processing arguments");
        cobj->setSoftnessLimLin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessLimLin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getAngularPos(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getAngularPos : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getAngularPos();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getAngularPos : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionLimAng(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionLimAng : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionLimAng : Error processing arguments");
        cobj->setRestitutionLimAng(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionLimAng : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setUpperLinLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setUpperLinLimit : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setUpperLinLimit : Error processing arguments");
        cobj->setUpperLinLimit(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setUpperLinLimit : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingDirLin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingDirLin : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingDirLin : Error processing arguments");
        cobj->setDampingDirLin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingDirLin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getUpperAngLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getUpperAngLimit : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getUpperAngLimit();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getUpperAngLimit : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingDirLin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingDirLin : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getDampingDirLin();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingDirLin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessDirAng(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessDirAng : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getSoftnessDirAng();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessDirAng : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getPoweredAngMotor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getPoweredAngMotor : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getPoweredAngMotor();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getPoweredAngMotor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setLowerAngLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setLowerAngLimit : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setLowerAngLimit : Error processing arguments");
        cobj->setLowerAngLimit(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setLowerAngLimit : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setUpperAngLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setUpperAngLimit : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setUpperAngLimit : Error processing arguments");
        cobj->setUpperAngLimit(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setUpperAngLimit : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setTargetLinMotorVelocity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setTargetLinMotorVelocity : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setTargetLinMotorVelocity : Error processing arguments");
        cobj->setTargetLinMotorVelocity(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setTargetLinMotorVelocity : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingLimAng(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingLimAng : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingLimAng : Error processing arguments");
        cobj->setDampingLimAng(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingLimAng : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionLimAng(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionLimAng : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRestitutionLimAng();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionLimAng : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getUseFrameOffset(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getUseFrameOffset : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getUseFrameOffset();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getUseFrameOffset : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessOrthoLin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessOrthoLin : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getSoftnessOrthoLin();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessOrthoLin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingOrthoAng(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingOrthoAng : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getDampingOrthoAng();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingOrthoAng : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setUseFrameOffset(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setUseFrameOffset : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setUseFrameOffset : Error processing arguments");
        cobj->setUseFrameOffset(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setUseFrameOffset : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setLowerLinLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setLowerLinLimit : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setLowerLinLimit : Error processing arguments");
        cobj->setLowerLinLimit(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setLowerLinLimit : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionDirLin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionDirLin : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRestitutionDirLin();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionDirLin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getTargetLinMotorVelocity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getTargetLinMotorVelocity : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getTargetLinMotorVelocity();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getTargetLinMotorVelocity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getLowerLinLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getLowerLinLimit : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getLowerLinLimit();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getLowerLinLimit : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessLimLin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessLimLin : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getSoftnessLimLin();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessLimLin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingOrthoAng(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingOrthoAng : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingOrthoAng : Error processing arguments");
        cobj->setDampingOrthoAng(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingOrthoAng : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessDirAng(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessDirAng : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessDirAng : Error processing arguments");
        cobj->setSoftnessDirAng(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessDirAng : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getPoweredLinMotor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getPoweredLinMotor : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getPoweredLinMotor();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getPoweredLinMotor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionOrthoAng(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionOrthoAng : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionOrthoAng : Error processing arguments");
        cobj->setRestitutionOrthoAng(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionOrthoAng : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingDirAng(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingDirAng : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingDirAng : Error processing arguments");
        cobj->setDampingDirAng(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingDirAng : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setFrames(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setFrames : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Mat4 arg0;
        cocos2d::Mat4 arg1;
        ok &= jsval_to_matrix(cx, args.get(0), &arg0);
        ok &= jsval_to_matrix(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setFrames : Error processing arguments");
        cobj->setFrames(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setFrames : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionOrthoAng(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionOrthoAng : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRestitutionOrthoAng();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionOrthoAng : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getMaxAngMotorForce(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getMaxAngMotorForce : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMaxAngMotorForce();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getMaxAngMotorForce : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingOrthoLin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingOrthoLin : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getDampingOrthoLin();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingOrthoLin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getUpperLinLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getUpperLinLimit : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getUpperLinLimit();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getUpperLinLimit : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setMaxLinMotorForce(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setMaxLinMotorForce : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setMaxLinMotorForce : Error processing arguments");
        cobj->setMaxLinMotorForce(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setMaxLinMotorForce : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionOrthoLin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionOrthoLin : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRestitutionOrthoLin();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionOrthoLin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setTargetAngMotorVelocity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setTargetAngMotorVelocity : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setTargetAngMotorVelocity : Error processing arguments");
        cobj->setTargetAngMotorVelocity(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setTargetAngMotorVelocity : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessLimAng(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessLimAng : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getSoftnessLimAng();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessLimAng : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionDirAng(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionDirAng : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionDirAng : Error processing arguments");
        cobj->setRestitutionDirAng(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionDirAng : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingLimLin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingLimLin : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getDampingLimLin();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingLimLin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getLowerAngLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getLowerAngLimit : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getLowerAngLimit();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getLowerAngLimit : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionDirAng(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionDirAng : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRestitutionDirAng();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionDirAng : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getTargetAngMotorVelocity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getTargetAngMotorVelocity : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getTargetAngMotorVelocity();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getTargetAngMotorVelocity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionLimLin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionLimLin : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionLimLin : Error processing arguments");
        cobj->setRestitutionLimLin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionLimLin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getMaxLinMotorForce(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getMaxLinMotorForce : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMaxLinMotorForce();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getMaxLinMotorForce : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingOrthoLin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingOrthoLin : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingOrthoLin : Error processing arguments");
        cobj->setDampingOrthoLin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingOrthoLin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessOrthoAng(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessOrthoAng : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessOrthoAng : Error processing arguments");
        cobj->setSoftnessOrthoAng(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessOrthoAng : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingLimLin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingLimLin : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingLimLin : Error processing arguments");
        cobj->setDampingLimLin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingLimLin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessDirLin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessDirLin : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessDirLin : Error processing arguments");
        cobj->setSoftnessDirLin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessDirLin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setMaxAngMotorForce(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setMaxAngMotorForce : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setMaxAngMotorForce : Error processing arguments");
        cobj->setMaxAngMotorForce(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setMaxAngMotorForce : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessDirLin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessDirLin : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getSoftnessDirLin();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessDirLin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessLimAng(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessLimAng : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessLimAng : Error processing arguments");
        cobj->setSoftnessLimAng(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessLimAng : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_getUseLinearReferenceFrameA(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DSliderConstraint* cobj = (cocos2d::Physics3DSliderConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getUseLinearReferenceFrameA : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getUseLinearReferenceFrameA();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_getUseLinearReferenceFrameA : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DSliderConstraint_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 5) {
        cocos2d::Physics3DRigidBody* arg0;
        cocos2d::Physics3DRigidBody* arg1;
        cocos2d::Mat4 arg2;
        cocos2d::Mat4 arg3;
        bool arg4;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_matrix(cx, args.get(2), &arg2);
        ok &= jsval_to_matrix(cx, args.get(3), &arg3);
        arg4 = JS::ToBoolean(args.get(4));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DSliderConstraint_create : Error processing arguments");
        cocos2d::Physics3DSliderConstraint* ret = cocos2d::Physics3DSliderConstraint::create(arg0, arg1, arg2, arg3, arg4);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DSliderConstraint>(cx, (cocos2d::Physics3DSliderConstraint*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DSliderConstraint_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_physics3d_Physics3DSliderConstraint_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::Physics3DSliderConstraint* cobj = new (std::nothrow) cocos2d::Physics3DSliderConstraint();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::Physics3DSliderConstraint> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::Physics3DSliderConstraint");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Physics3DConstraint_prototype;

void js_cocos2d_Physics3DSliderConstraint_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Physics3DSliderConstraint)", obj);
}

void js_register_cocos2dx_physics3d_Physics3DSliderConstraint(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Physics3DSliderConstraint_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Physics3DSliderConstraint_class->name = "Physics3DSliderConstraint";
    jsb_cocos2d_Physics3DSliderConstraint_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3DSliderConstraint_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Physics3DSliderConstraint_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3DSliderConstraint_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Physics3DSliderConstraint_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Physics3DSliderConstraint_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Physics3DSliderConstraint_class->convert = JS_ConvertStub;
    jsb_cocos2d_Physics3DSliderConstraint_class->finalize = js_cocos2d_Physics3DSliderConstraint_finalize;
    jsb_cocos2d_Physics3DSliderConstraint_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setPoweredAngMotor", js_cocos2dx_physics3d_Physics3DSliderConstraint_setPoweredAngMotor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDampingLimAng", js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingLimAng, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRestitutionOrthoLin", js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionOrthoLin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRestitutionDirLin", js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionDirLin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLinearPos", js_cocos2dx_physics3d_Physics3DSliderConstraint_getLinearPos, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFrameOffsetA", js_cocos2dx_physics3d_Physics3DSliderConstraint_getFrameOffsetA, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFrameOffsetB", js_cocos2dx_physics3d_Physics3DSliderConstraint_getFrameOffsetB, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPoweredLinMotor", js_cocos2dx_physics3d_Physics3DSliderConstraint_setPoweredLinMotor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDampingDirAng", js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingDirAng, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRestitutionLimLin", js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionLimLin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSoftnessOrthoAng", js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessOrthoAng, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSoftnessOrthoLin", js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessOrthoLin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSoftnessLimLin", js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessLimLin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAngularPos", js_cocos2dx_physics3d_Physics3DSliderConstraint_getAngularPos, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRestitutionLimAng", js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionLimAng, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setUpperLinLimit", js_cocos2dx_physics3d_Physics3DSliderConstraint_setUpperLinLimit, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDampingDirLin", js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingDirLin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUpperAngLimit", js_cocos2dx_physics3d_Physics3DSliderConstraint_getUpperAngLimit, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDampingDirLin", js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingDirLin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSoftnessDirAng", js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessDirAng, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPoweredAngMotor", js_cocos2dx_physics3d_Physics3DSliderConstraint_getPoweredAngMotor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLowerAngLimit", js_cocos2dx_physics3d_Physics3DSliderConstraint_setLowerAngLimit, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setUpperAngLimit", js_cocos2dx_physics3d_Physics3DSliderConstraint_setUpperAngLimit, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTargetLinMotorVelocity", js_cocos2dx_physics3d_Physics3DSliderConstraint_setTargetLinMotorVelocity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDampingLimAng", js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingLimAng, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRestitutionLimAng", js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionLimAng, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUseFrameOffset", js_cocos2dx_physics3d_Physics3DSliderConstraint_getUseFrameOffset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSoftnessOrthoLin", js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessOrthoLin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDampingOrthoAng", js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingOrthoAng, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setUseFrameOffset", js_cocos2dx_physics3d_Physics3DSliderConstraint_setUseFrameOffset, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLowerLinLimit", js_cocos2dx_physics3d_Physics3DSliderConstraint_setLowerLinLimit, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRestitutionDirLin", js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionDirLin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTargetLinMotorVelocity", js_cocos2dx_physics3d_Physics3DSliderConstraint_getTargetLinMotorVelocity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLowerLinLimit", js_cocos2dx_physics3d_Physics3DSliderConstraint_getLowerLinLimit, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSoftnessLimLin", js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessLimLin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDampingOrthoAng", js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingOrthoAng, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSoftnessDirAng", js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessDirAng, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPoweredLinMotor", js_cocos2dx_physics3d_Physics3DSliderConstraint_getPoweredLinMotor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRestitutionOrthoAng", js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionOrthoAng, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDampingDirAng", js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingDirAng, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFrames", js_cocos2dx_physics3d_Physics3DSliderConstraint_setFrames, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRestitutionOrthoAng", js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionOrthoAng, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaxAngMotorForce", js_cocos2dx_physics3d_Physics3DSliderConstraint_getMaxAngMotorForce, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDampingOrthoLin", js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingOrthoLin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUpperLinLimit", js_cocos2dx_physics3d_Physics3DSliderConstraint_getUpperLinLimit, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaxLinMotorForce", js_cocos2dx_physics3d_Physics3DSliderConstraint_setMaxLinMotorForce, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRestitutionOrthoLin", js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionOrthoLin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTargetAngMotorVelocity", js_cocos2dx_physics3d_Physics3DSliderConstraint_setTargetAngMotorVelocity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSoftnessLimAng", js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessLimAng, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRestitutionDirAng", js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionDirAng, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDampingLimLin", js_cocos2dx_physics3d_Physics3DSliderConstraint_getDampingLimLin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLowerAngLimit", js_cocos2dx_physics3d_Physics3DSliderConstraint_getLowerAngLimit, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRestitutionDirAng", js_cocos2dx_physics3d_Physics3DSliderConstraint_getRestitutionDirAng, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTargetAngMotorVelocity", js_cocos2dx_physics3d_Physics3DSliderConstraint_getTargetAngMotorVelocity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRestitutionLimLin", js_cocos2dx_physics3d_Physics3DSliderConstraint_setRestitutionLimLin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaxLinMotorForce", js_cocos2dx_physics3d_Physics3DSliderConstraint_getMaxLinMotorForce, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDampingOrthoLin", js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingOrthoLin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSoftnessOrthoAng", js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessOrthoAng, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDampingLimLin", js_cocos2dx_physics3d_Physics3DSliderConstraint_setDampingLimLin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSoftnessDirLin", js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessDirLin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaxAngMotorForce", js_cocos2dx_physics3d_Physics3DSliderConstraint_setMaxAngMotorForce, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSoftnessDirLin", js_cocos2dx_physics3d_Physics3DSliderConstraint_getSoftnessDirLin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSoftnessLimAng", js_cocos2dx_physics3d_Physics3DSliderConstraint_setSoftnessLimAng, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUseLinearReferenceFrameA", js_cocos2dx_physics3d_Physics3DSliderConstraint_getUseLinearReferenceFrameA, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_physics3d_Physics3DSliderConstraint_create, 5, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_Physics3DSliderConstraint_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Physics3DConstraint_prototype),
        jsb_cocos2d_Physics3DSliderConstraint_class,
        js_cocos2dx_physics3d_Physics3DSliderConstraint_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Physics3DSliderConstraint", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::Physics3DSliderConstraint> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_Physics3DSliderConstraint_class;
        p->proto = jsb_cocos2d_Physics3DSliderConstraint_prototype;
        p->parentProto = jsb_cocos2d_Physics3DConstraint_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_Physics3DConeTwistConstraint_class;
JSObject *jsb_cocos2d_Physics3DConeTwistConstraint_prototype;

bool js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getBFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConeTwistConstraint* cobj = (cocos2d::Physics3DConeTwistConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getBFrame : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Mat4 ret = cobj->getBFrame();
        jsval jsret = JSVAL_NULL;
        jsret = matrix_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getBFrame : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setFixThresh(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConeTwistConstraint* cobj = (cocos2d::Physics3DConeTwistConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setFixThresh : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setFixThresh : Error processing arguments");
        cobj->setFixThresh(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setFixThresh : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getFrameOffsetB(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConeTwistConstraint* cobj = (cocos2d::Physics3DConeTwistConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getFrameOffsetB : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Mat4 ret = cobj->getFrameOffsetB();
        jsval jsret = JSVAL_NULL;
        jsret = matrix_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getFrameOffsetB : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getFrameOffsetA(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConeTwistConstraint* cobj = (cocos2d::Physics3DConeTwistConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getFrameOffsetA : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Mat4 ret = cobj->getFrameOffsetA();
        jsval jsret = JSVAL_NULL;
        jsret = matrix_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getFrameOffsetA : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getFixThresh(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConeTwistConstraint* cobj = (cocos2d::Physics3DConeTwistConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getFixThresh : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getFixThresh();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getFixThresh : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getSwingSpan2(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConeTwistConstraint* cobj = (cocos2d::Physics3DConeTwistConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getSwingSpan2 : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getSwingSpan2();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getSwingSpan2 : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getSwingSpan1(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConeTwistConstraint* cobj = (cocos2d::Physics3DConeTwistConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getSwingSpan1 : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getSwingSpan1();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getSwingSpan1 : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setMaxMotorImpulse(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConeTwistConstraint* cobj = (cocos2d::Physics3DConeTwistConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setMaxMotorImpulse : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setMaxMotorImpulse : Error processing arguments");
        cobj->setMaxMotorImpulse(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setMaxMotorImpulse : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setFrames(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConeTwistConstraint* cobj = (cocos2d::Physics3DConeTwistConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setFrames : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Mat4 arg0;
        cocos2d::Mat4 arg1;
        ok &= jsval_to_matrix(cx, args.get(0), &arg0);
        ok &= jsval_to_matrix(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setFrames : Error processing arguments");
        cobj->setFrames(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setFrames : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getTwistAngle(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConeTwistConstraint* cobj = (cocos2d::Physics3DConeTwistConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getTwistAngle : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getTwistAngle();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getTwistAngle : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConeTwistConstraint_GetPointForAngle(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConeTwistConstraint* cobj = (cocos2d::Physics3DConeTwistConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_GetPointForAngle : Invalid Native Object");
    if (argc == 2) {
        double arg0;
        double arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_GetPointForAngle : Error processing arguments");
        cocos2d::Vec3 ret = cobj->GetPointForAngle(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = vector3_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_GetPointForAngle : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setMaxMotorImpulseNormalized(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConeTwistConstraint* cobj = (cocos2d::Physics3DConeTwistConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setMaxMotorImpulseNormalized : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setMaxMotorImpulseNormalized : Error processing arguments");
        cobj->setMaxMotorImpulseNormalized(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setMaxMotorImpulseNormalized : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getTwistSpan(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConeTwistConstraint* cobj = (cocos2d::Physics3DConeTwistConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getTwistSpan : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getTwistSpan();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getTwistSpan : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setDamping(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConeTwistConstraint* cobj = (cocos2d::Physics3DConeTwistConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setDamping : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setDamping : Error processing arguments");
        cobj->setDamping(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setDamping : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConeTwistConstraint* cobj = (cocos2d::Physics3DConeTwistConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setLimit : Invalid Native Object");
    if (argc == 3) {
        double arg0;
        double arg1;
        double arg2;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setLimit : Error processing arguments");
        cobj->setLimit(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 4) {
        double arg0;
        double arg1;
        double arg2;
        double arg3;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= JS::ToNumber( cx, args.get(3), &arg3) && !isnan(arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setLimit : Error processing arguments");
        cobj->setLimit(arg0, arg1, arg2, arg3);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 5) {
        double arg0;
        double arg1;
        double arg2;
        double arg3;
        double arg4;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= JS::ToNumber( cx, args.get(3), &arg3) && !isnan(arg3);
        ok &= JS::ToNumber( cx, args.get(4), &arg4) && !isnan(arg4);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setLimit : Error processing arguments");
        cobj->setLimit(arg0, arg1, arg2, arg3, arg4);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 6) {
        double arg0;
        double arg1;
        double arg2;
        double arg3;
        double arg4;
        double arg5;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        ok &= JS::ToNumber( cx, args.get(3), &arg3) && !isnan(arg3);
        ok &= JS::ToNumber( cx, args.get(4), &arg4) && !isnan(arg4);
        ok &= JS::ToNumber( cx, args.get(5), &arg5) && !isnan(arg5);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setLimit : Error processing arguments");
        cobj->setLimit(arg0, arg1, arg2, arg3, arg4, arg5);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setLimit : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getAFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConeTwistConstraint* cobj = (cocos2d::Physics3DConeTwistConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getAFrame : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Mat4 ret = cobj->getAFrame();
        jsval jsret = JSVAL_NULL;
        jsret = matrix_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getAFrame : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConeTwistConstraint_enableMotor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3DConeTwistConstraint* cobj = (cocos2d::Physics3DConeTwistConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_enableMotor : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_enableMotor : Error processing arguments");
        cobj->enableMotor(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_enableMotor : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConeTwistConstraint_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 4) {
            cocos2d::Physics3DRigidBody* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DRigidBody* arg1;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(1).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Mat4 arg2;
            ok &= jsval_to_matrix(cx, args.get(2), &arg2);
            if (!ok) { ok = true; break; }
            cocos2d::Mat4 arg3;
            ok &= jsval_to_matrix(cx, args.get(3), &arg3);
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DConeTwistConstraint* ret = cocos2d::Physics3DConeTwistConstraint::create(arg0, arg1, arg2, arg3);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DConeTwistConstraint>(cx, (cocos2d::Physics3DConeTwistConstraint*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 2) {
            cocos2d::Physics3DRigidBody* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Mat4 arg1;
            ok &= jsval_to_matrix(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DConeTwistConstraint* ret = cocos2d::Physics3DConeTwistConstraint::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DConeTwistConstraint>(cx, (cocos2d::Physics3DConeTwistConstraint*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3DConeTwistConstraint_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_physics3d_Physics3DConeTwistConstraint_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::Physics3DConeTwistConstraint* cobj = new (std::nothrow) cocos2d::Physics3DConeTwistConstraint();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::Physics3DConeTwistConstraint> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::Physics3DConeTwistConstraint");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Physics3DConstraint_prototype;

void js_cocos2d_Physics3DConeTwistConstraint_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Physics3DConeTwistConstraint)", obj);
}

void js_register_cocos2dx_physics3d_Physics3DConeTwistConstraint(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Physics3DConeTwistConstraint_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Physics3DConeTwistConstraint_class->name = "Physics3DConeTwistConstraint";
    jsb_cocos2d_Physics3DConeTwistConstraint_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3DConeTwistConstraint_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Physics3DConeTwistConstraint_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3DConeTwistConstraint_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Physics3DConeTwistConstraint_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Physics3DConeTwistConstraint_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Physics3DConeTwistConstraint_class->convert = JS_ConvertStub;
    jsb_cocos2d_Physics3DConeTwistConstraint_class->finalize = js_cocos2d_Physics3DConeTwistConstraint_finalize;
    jsb_cocos2d_Physics3DConeTwistConstraint_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getBFrame", js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getBFrame, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFixThresh", js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setFixThresh, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFrameOffsetB", js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getFrameOffsetB, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFrameOffsetA", js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getFrameOffsetA, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFixThresh", js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getFixThresh, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSwingSpan2", js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getSwingSpan2, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSwingSpan1", js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getSwingSpan1, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaxMotorImpulse", js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setMaxMotorImpulse, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFrames", js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setFrames, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTwistAngle", js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getTwistAngle, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("GetPointForAngle", js_cocos2dx_physics3d_Physics3DConeTwistConstraint_GetPointForAngle, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaxMotorImpulseNormalized", js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setMaxMotorImpulseNormalized, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTwistSpan", js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getTwistSpan, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDamping", js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setDamping, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLimit", js_cocos2dx_physics3d_Physics3DConeTwistConstraint_setLimit, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAFrame", js_cocos2dx_physics3d_Physics3DConeTwistConstraint_getAFrame, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("enableMotor", js_cocos2dx_physics3d_Physics3DConeTwistConstraint_enableMotor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_physics3d_Physics3DConeTwistConstraint_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_Physics3DConeTwistConstraint_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Physics3DConstraint_prototype),
        jsb_cocos2d_Physics3DConeTwistConstraint_class,
        js_cocos2dx_physics3d_Physics3DConeTwistConstraint_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Physics3DConeTwistConstraint", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::Physics3DConeTwistConstraint> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_Physics3DConeTwistConstraint_class;
        p->proto = jsb_cocos2d_Physics3DConeTwistConstraint_prototype;
        p->parentProto = jsb_cocos2d_Physics3DConstraint_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_Physics3D6DofConstraint_class;
JSObject *jsb_cocos2d_Physics3D6DofConstraint_prototype;

bool js_cocos2dx_physics3d_Physics3D6DofConstraint_setLinearLowerLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3D6DofConstraint* cobj = (cocos2d::Physics3D6DofConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3D6DofConstraint_setLinearLowerLimit : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3D6DofConstraint_setLinearLowerLimit : Error processing arguments");
        cobj->setLinearLowerLimit(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3D6DofConstraint_setLinearLowerLimit : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3D6DofConstraint_getLinearLowerLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3D6DofConstraint* cobj = (cocos2d::Physics3D6DofConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3D6DofConstraint_getLinearLowerLimit : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec3 ret = cobj->getLinearLowerLimit();
        jsval jsret = JSVAL_NULL;
        jsret = vector3_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3D6DofConstraint_getLinearLowerLimit : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3D6DofConstraint_getAngularUpperLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3D6DofConstraint* cobj = (cocos2d::Physics3D6DofConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3D6DofConstraint_getAngularUpperLimit : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec3 ret = cobj->getAngularUpperLimit();
        jsval jsret = JSVAL_NULL;
        jsret = vector3_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3D6DofConstraint_getAngularUpperLimit : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3D6DofConstraint_getUseFrameOffset(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3D6DofConstraint* cobj = (cocos2d::Physics3D6DofConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3D6DofConstraint_getUseFrameOffset : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getUseFrameOffset();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3D6DofConstraint_getUseFrameOffset : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3D6DofConstraint_getLinearUpperLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3D6DofConstraint* cobj = (cocos2d::Physics3D6DofConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3D6DofConstraint_getLinearUpperLimit : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec3 ret = cobj->getLinearUpperLimit();
        jsval jsret = JSVAL_NULL;
        jsret = vector3_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3D6DofConstraint_getLinearUpperLimit : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3D6DofConstraint_setAngularLowerLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3D6DofConstraint* cobj = (cocos2d::Physics3D6DofConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3D6DofConstraint_setAngularLowerLimit : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3D6DofConstraint_setAngularLowerLimit : Error processing arguments");
        cobj->setAngularLowerLimit(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3D6DofConstraint_setAngularLowerLimit : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3D6DofConstraint_isLimited(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3D6DofConstraint* cobj = (cocos2d::Physics3D6DofConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3D6DofConstraint_isLimited : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3D6DofConstraint_isLimited : Error processing arguments");
        bool ret = cobj->isLimited(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3D6DofConstraint_isLimited : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3D6DofConstraint_setUseFrameOffset(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3D6DofConstraint* cobj = (cocos2d::Physics3D6DofConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3D6DofConstraint_setUseFrameOffset : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3D6DofConstraint_setUseFrameOffset : Error processing arguments");
        cobj->setUseFrameOffset(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3D6DofConstraint_setUseFrameOffset : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3D6DofConstraint_setLinearUpperLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3D6DofConstraint* cobj = (cocos2d::Physics3D6DofConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3D6DofConstraint_setLinearUpperLimit : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3D6DofConstraint_setLinearUpperLimit : Error processing arguments");
        cobj->setLinearUpperLimit(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3D6DofConstraint_setLinearUpperLimit : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3D6DofConstraint_getAngularLowerLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3D6DofConstraint* cobj = (cocos2d::Physics3D6DofConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3D6DofConstraint_getAngularLowerLimit : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec3 ret = cobj->getAngularLowerLimit();
        jsval jsret = JSVAL_NULL;
        jsret = vector3_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3D6DofConstraint_getAngularLowerLimit : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_physics3d_Physics3D6DofConstraint_setAngularUpperLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Physics3D6DofConstraint* cobj = (cocos2d::Physics3D6DofConstraint *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_physics3d_Physics3D6DofConstraint_setAngularUpperLimit : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_physics3d_Physics3D6DofConstraint_setAngularUpperLimit : Error processing arguments");
        cobj->setAngularUpperLimit(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3D6DofConstraint_setAngularUpperLimit : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_physics3d_Physics3D6DofConstraint_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 3) {
            cocos2d::Physics3DRigidBody* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Mat4 arg1;
            ok &= jsval_to_matrix(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            bool arg2;
            arg2 = JS::ToBoolean(args.get(2));
            if (!ok) { ok = true; break; }
            cocos2d::Physics3D6DofConstraint* ret = cocos2d::Physics3D6DofConstraint::create(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3D6DofConstraint>(cx, (cocos2d::Physics3D6DofConstraint*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 5) {
            cocos2d::Physics3DRigidBody* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Physics3DRigidBody* arg1;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(1).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::Physics3DRigidBody*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Mat4 arg2;
            ok &= jsval_to_matrix(cx, args.get(2), &arg2);
            if (!ok) { ok = true; break; }
            cocos2d::Mat4 arg3;
            ok &= jsval_to_matrix(cx, args.get(3), &arg3);
            if (!ok) { ok = true; break; }
            bool arg4;
            arg4 = JS::ToBoolean(args.get(4));
            if (!ok) { ok = true; break; }
            cocos2d::Physics3D6DofConstraint* ret = cocos2d::Physics3D6DofConstraint::create(arg0, arg1, arg2, arg3, arg4);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3D6DofConstraint>(cx, (cocos2d::Physics3D6DofConstraint*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_physics3d_Physics3D6DofConstraint_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_physics3d_Physics3D6DofConstraint_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::Physics3D6DofConstraint* cobj = new (std::nothrow) cocos2d::Physics3D6DofConstraint();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::Physics3D6DofConstraint> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::Physics3D6DofConstraint");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Physics3DConstraint_prototype;

void js_cocos2d_Physics3D6DofConstraint_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Physics3D6DofConstraint)", obj);
}

void js_register_cocos2dx_physics3d_Physics3D6DofConstraint(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Physics3D6DofConstraint_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Physics3D6DofConstraint_class->name = "Physics3D6DofConstraint";
    jsb_cocos2d_Physics3D6DofConstraint_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3D6DofConstraint_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Physics3D6DofConstraint_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Physics3D6DofConstraint_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Physics3D6DofConstraint_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Physics3D6DofConstraint_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Physics3D6DofConstraint_class->convert = JS_ConvertStub;
    jsb_cocos2d_Physics3D6DofConstraint_class->finalize = js_cocos2d_Physics3D6DofConstraint_finalize;
    jsb_cocos2d_Physics3D6DofConstraint_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setLinearLowerLimit", js_cocos2dx_physics3d_Physics3D6DofConstraint_setLinearLowerLimit, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLinearLowerLimit", js_cocos2dx_physics3d_Physics3D6DofConstraint_getLinearLowerLimit, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAngularUpperLimit", js_cocos2dx_physics3d_Physics3D6DofConstraint_getAngularUpperLimit, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUseFrameOffset", js_cocos2dx_physics3d_Physics3D6DofConstraint_getUseFrameOffset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLinearUpperLimit", js_cocos2dx_physics3d_Physics3D6DofConstraint_getLinearUpperLimit, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAngularLowerLimit", js_cocos2dx_physics3d_Physics3D6DofConstraint_setAngularLowerLimit, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLimited", js_cocos2dx_physics3d_Physics3D6DofConstraint_isLimited, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setUseFrameOffset", js_cocos2dx_physics3d_Physics3D6DofConstraint_setUseFrameOffset, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLinearUpperLimit", js_cocos2dx_physics3d_Physics3D6DofConstraint_setLinearUpperLimit, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAngularLowerLimit", js_cocos2dx_physics3d_Physics3D6DofConstraint_getAngularLowerLimit, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAngularUpperLimit", js_cocos2dx_physics3d_Physics3D6DofConstraint_setAngularUpperLimit, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_physics3d_Physics3D6DofConstraint_create, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_Physics3D6DofConstraint_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Physics3DConstraint_prototype),
        jsb_cocos2d_Physics3D6DofConstraint_class,
        js_cocos2dx_physics3d_Physics3D6DofConstraint_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Physics3D6DofConstraint", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::Physics3D6DofConstraint> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_Physics3D6DofConstraint_class;
        p->proto = jsb_cocos2d_Physics3D6DofConstraint_prototype;
        p->parentProto = jsb_cocos2d_Physics3DConstraint_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_cocos2dx_physics3d(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "jsb", &ns);

    js_register_cocos2dx_physics3d_Physics3DConstraint(cx, ns);
    js_register_cocos2dx_physics3d_Physics3D6DofConstraint(cx, ns);
    js_register_cocos2dx_physics3d_Physics3DObject(cx, ns);
    js_register_cocos2dx_physics3d_Physics3DRigidBody(cx, ns);
    js_register_cocos2dx_physics3d_Physics3DWorld(cx, ns);
    js_register_cocos2dx_physics3d_Physics3DSliderConstraint(cx, ns);
    js_register_cocos2dx_physics3d_Physics3DComponent(cx, ns);
    js_register_cocos2dx_physics3d_Physics3DConeTwistConstraint(cx, ns);
    js_register_cocos2dx_physics3d_Physics3DPointToPointConstraint(cx, ns);
    js_register_cocos2dx_physics3d_PhysicsSprite3D(cx, ns);
    js_register_cocos2dx_physics3d_Physics3DHingeConstraint(cx, ns);
    js_register_cocos2dx_physics3d_Physics3DShape(cx, ns);
}

#endif //#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
