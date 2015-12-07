#include "jsb_cocos2dx_navmesh_auto.hpp"
#if CC_USE_NAVMESH
#include "cocos2d_specifics.hpp"
#include "CCNavMesh.h"
#include "navmesh/jsb_cocos2dx_navmesh_conversions.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
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
JSClass  *jsb_cocos2d_NavMeshAgent_class;
JSObject *jsb_cocos2d_NavMeshAgent_prototype;

bool js_cocos2dx_navmesh_NavMeshAgent_setMaxSpeed(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_setMaxSpeed : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_setMaxSpeed : Error processing arguments");
        cobj->setMaxSpeed(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_setMaxSpeed : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_syncToNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_syncToNode : Invalid Native Object");
    if (argc == 0) {
        cobj->syncToNode();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_syncToNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_completeOffMeshLink(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_completeOffMeshLink : Invalid Native Object");
    if (argc == 0) {
        cobj->completeOffMeshLink();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_completeOffMeshLink : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_getSeparationWeight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_getSeparationWeight : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getSeparationWeight();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_getSeparationWeight : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_setAutoTraverseOffMeshLink(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_setAutoTraverseOffMeshLink : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_setAutoTraverseOffMeshLink : Error processing arguments");
        cobj->setAutoTraverseOffMeshLink(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_setAutoTraverseOffMeshLink : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_getCurrentVelocity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_getCurrentVelocity : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec3 ret = cobj->getCurrentVelocity();
        jsval jsret = JSVAL_NULL;
        jsret = vector3_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_getCurrentVelocity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_syncToAgent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_syncToAgent : Invalid Native Object");
    if (argc == 0) {
        cobj->syncToAgent();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_syncToAgent : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_isOnOffMeshLink(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_isOnOffMeshLink : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isOnOffMeshLink();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_isOnOffMeshLink : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_setSeparationWeight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_setSeparationWeight : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_setSeparationWeight : Error processing arguments");
        cobj->setSeparationWeight(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_setSeparationWeight : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_pause(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_pause : Invalid Native Object");
    if (argc == 0) {
        cobj->pause();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_pause : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_setAutoOrientation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_setAutoOrientation : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_setAutoOrientation : Error processing arguments");
        cobj->setAutoOrientation(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_setAutoOrientation : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_getHeight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_getHeight : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getHeight();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_getHeight : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_getMaxSpeed(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_getMaxSpeed : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMaxSpeed();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_getMaxSpeed : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_getCurrentOffMeshLinkData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_getCurrentOffMeshLinkData : Invalid Native Object");
    if (argc == 0) {
        cocos2d::OffMeshLinkData ret = cobj->getCurrentOffMeshLinkData();
        jsval jsret = JSVAL_NULL;
        jsret = offMeshLinkData_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_getCurrentOffMeshLinkData : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_getRadius(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_getRadius : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRadius();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_getRadius : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_setSyncFlag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_setSyncFlag : Invalid Native Object");
    if (argc == 1) {
        cocos2d::NavMeshAgent::NavMeshAgentSyncFlag arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_setSyncFlag : Error processing arguments");
        cobj->setSyncFlag(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_setSyncFlag : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_getSyncFlag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_getSyncFlag : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getSyncFlag();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_getSyncFlag : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_resume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_resume : Invalid Native Object");
    if (argc == 0) {
        cobj->resume();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_resume : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_stop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_stop : Invalid Native Object");
    if (argc == 0) {
        cobj->stop();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_stop : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_setMaxAcceleration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_setMaxAcceleration : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_setMaxAcceleration : Error processing arguments");
        cobj->setMaxAcceleration(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_setMaxAcceleration : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_setOrientationRefAxes(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_setOrientationRefAxes : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_setOrientationRefAxes : Error processing arguments");
        cobj->setOrientationRefAxes(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_setOrientationRefAxes : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_getMaxAcceleration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_getMaxAcceleration : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMaxAcceleration();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_getMaxAcceleration : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_setHeight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_setHeight : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_setHeight : Error processing arguments");
        cobj->setHeight(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_setHeight : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_getObstacleAvoidanceType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_getObstacleAvoidanceType : Invalid Native Object");
    if (argc == 0) {
        uint16_t ret = cobj->getObstacleAvoidanceType();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_getObstacleAvoidanceType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_getVelocity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_getVelocity : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec3 ret = cobj->getVelocity();
        jsval jsret = JSVAL_NULL;
        jsret = vector3_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_getVelocity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_setRadius(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_setRadius : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_setRadius : Error processing arguments");
        cobj->setRadius(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_setRadius : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_setObstacleAvoidanceType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshAgent* cobj = (cocos2d::NavMeshAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_setObstacleAvoidanceType : Invalid Native Object");
    if (argc == 1) {
        uint16_t arg0;
        ok &= jsval_to_uint16(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_setObstacleAvoidanceType : Error processing arguments");
        cobj->setObstacleAvoidanceType(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_setObstacleAvoidanceType : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshAgent_getNavMeshAgentComponentName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        const std::string& ret = cocos2d::NavMeshAgent::getNavMeshAgentComponentName();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_getNavMeshAgentComponentName : wrong number of arguments");
    return false;
}

bool js_cocos2dx_navmesh_NavMeshAgent_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::NavMeshAgentParam arg0;
        ok &= jsval_to_NavMeshAgentParam(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMeshAgent_create : Error processing arguments");

        auto ret = cocos2d::NavMeshAgent::create(arg0);
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::NavMeshAgent>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocos2d::NavMeshAgent"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshAgent_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_navmesh_NavMeshAgent_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::NavMeshAgent* cobj = new (std::nothrow) cocos2d::NavMeshAgent();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::NavMeshAgent>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::NavMeshAgent"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Component_prototype;

void js_register_cocos2dx_navmesh_NavMeshAgent(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_NavMeshAgent_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_NavMeshAgent_class->name = "NavMeshAgent";
    jsb_cocos2d_NavMeshAgent_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_NavMeshAgent_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_NavMeshAgent_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_NavMeshAgent_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_NavMeshAgent_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_NavMeshAgent_class->resolve = JS_ResolveStub;
    jsb_cocos2d_NavMeshAgent_class->convert = JS_ConvertStub;
    jsb_cocos2d_NavMeshAgent_class->finalize = jsb_ref_finalize;
    jsb_cocos2d_NavMeshAgent_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setMaxSpeed", js_cocos2dx_navmesh_NavMeshAgent_setMaxSpeed, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("syncToNode", js_cocos2dx_navmesh_NavMeshAgent_syncToNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("completeOffMeshLink", js_cocos2dx_navmesh_NavMeshAgent_completeOffMeshLink, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSeparationWeight", js_cocos2dx_navmesh_NavMeshAgent_getSeparationWeight, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAutoTraverseOffMeshLink", js_cocos2dx_navmesh_NavMeshAgent_setAutoTraverseOffMeshLink, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentVelocity", js_cocos2dx_navmesh_NavMeshAgent_getCurrentVelocity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("syncToAgent", js_cocos2dx_navmesh_NavMeshAgent_syncToAgent, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isOnOffMeshLink", js_cocos2dx_navmesh_NavMeshAgent_isOnOffMeshLink, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSeparationWeight", js_cocos2dx_navmesh_NavMeshAgent_setSeparationWeight, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pause", js_cocos2dx_navmesh_NavMeshAgent_pause, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAutoOrientation", js_cocos2dx_navmesh_NavMeshAgent_setAutoOrientation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getHeight", js_cocos2dx_navmesh_NavMeshAgent_getHeight, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaxSpeed", js_cocos2dx_navmesh_NavMeshAgent_getMaxSpeed, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentOffMeshLinkData", js_cocos2dx_navmesh_NavMeshAgent_getCurrentOffMeshLinkData, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRadius", js_cocos2dx_navmesh_NavMeshAgent_getRadius, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSyncFlag", js_cocos2dx_navmesh_NavMeshAgent_setSyncFlag, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSyncFlag", js_cocos2dx_navmesh_NavMeshAgent_getSyncFlag, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resume", js_cocos2dx_navmesh_NavMeshAgent_resume, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stop", js_cocos2dx_navmesh_NavMeshAgent_stop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaxAcceleration", js_cocos2dx_navmesh_NavMeshAgent_setMaxAcceleration, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setOrientationRefAxes", js_cocos2dx_navmesh_NavMeshAgent_setOrientationRefAxes, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaxAcceleration", js_cocos2dx_navmesh_NavMeshAgent_getMaxAcceleration, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setHeight", js_cocos2dx_navmesh_NavMeshAgent_setHeight, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getObstacleAvoidanceType", js_cocos2dx_navmesh_NavMeshAgent_getObstacleAvoidanceType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVelocity", js_cocos2dx_navmesh_NavMeshAgent_getVelocity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRadius", js_cocos2dx_navmesh_NavMeshAgent_setRadius, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setObstacleAvoidanceType", js_cocos2dx_navmesh_NavMeshAgent_setObstacleAvoidanceType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("getNavMeshAgentComponentName", js_cocos2dx_navmesh_NavMeshAgent_getNavMeshAgentComponentName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("create", js_cocos2dx_navmesh_NavMeshAgent_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Component_prototype);
    jsb_cocos2d_NavMeshAgent_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_NavMeshAgent_class,
        js_cocos2dx_navmesh_NavMeshAgent_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_cocos2d_NavMeshAgent_prototype);
    jsb_register_class<cocos2d::NavMeshAgent>(cx, jsb_cocos2d_NavMeshAgent_class, proto, parent_proto);
}

JSClass  *jsb_cocos2d_NavMeshObstacle_class;
JSObject *jsb_cocos2d_NavMeshObstacle_prototype;

bool js_cocos2dx_navmesh_NavMeshObstacle_getSyncFlag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshObstacle* cobj = (cocos2d::NavMeshObstacle *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshObstacle_getSyncFlag : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getSyncFlag();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshObstacle_getSyncFlag : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshObstacle_initWith(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshObstacle* cobj = (cocos2d::NavMeshObstacle *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshObstacle_initWith : Invalid Native Object");
    if (argc == 2) {
        double arg0 = 0;
        double arg1 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMeshObstacle_initWith : Error processing arguments");
        bool ret = cobj->initWith(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshObstacle_initWith : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshObstacle_syncToObstacle(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshObstacle* cobj = (cocos2d::NavMeshObstacle *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshObstacle_syncToObstacle : Invalid Native Object");
    if (argc == 0) {
        cobj->syncToObstacle();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshObstacle_syncToObstacle : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshObstacle_syncToNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshObstacle* cobj = (cocos2d::NavMeshObstacle *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshObstacle_syncToNode : Invalid Native Object");
    if (argc == 0) {
        cobj->syncToNode();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshObstacle_syncToNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshObstacle_getHeight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshObstacle* cobj = (cocos2d::NavMeshObstacle *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshObstacle_getHeight : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getHeight();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshObstacle_getHeight : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshObstacle_setSyncFlag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshObstacle* cobj = (cocos2d::NavMeshObstacle *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshObstacle_setSyncFlag : Invalid Native Object");
    if (argc == 1) {
        cocos2d::NavMeshObstacle::NavMeshObstacleSyncFlag arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMeshObstacle_setSyncFlag : Error processing arguments");
        cobj->setSyncFlag(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshObstacle_setSyncFlag : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshObstacle_getRadius(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMeshObstacle* cobj = (cocos2d::NavMeshObstacle *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMeshObstacle_getRadius : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRadius();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshObstacle_getRadius : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMeshObstacle_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        double arg0 = 0;
        double arg1 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMeshObstacle_create : Error processing arguments");

        auto ret = cocos2d::NavMeshObstacle::create(arg0, arg1);
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::NavMeshObstacle>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocos2d::NavMeshObstacle"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshObstacle_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_navmesh_NavMeshObstacle_getNavMeshObstacleComponentName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        const std::string& ret = cocos2d::NavMeshObstacle::getNavMeshObstacleComponentName();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMeshObstacle_getNavMeshObstacleComponentName : wrong number of arguments");
    return false;
}

bool js_cocos2dx_navmesh_NavMeshObstacle_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::NavMeshObstacle* cobj = new (std::nothrow) cocos2d::NavMeshObstacle();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::NavMeshObstacle>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::NavMeshObstacle"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Component_prototype;

void js_register_cocos2dx_navmesh_NavMeshObstacle(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_NavMeshObstacle_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_NavMeshObstacle_class->name = "NavMeshObstacle";
    jsb_cocos2d_NavMeshObstacle_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_NavMeshObstacle_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_NavMeshObstacle_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_NavMeshObstacle_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_NavMeshObstacle_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_NavMeshObstacle_class->resolve = JS_ResolveStub;
    jsb_cocos2d_NavMeshObstacle_class->convert = JS_ConvertStub;
    jsb_cocos2d_NavMeshObstacle_class->finalize = jsb_ref_finalize;
    jsb_cocos2d_NavMeshObstacle_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getSyncFlag", js_cocos2dx_navmesh_NavMeshObstacle_getSyncFlag, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWith", js_cocos2dx_navmesh_NavMeshObstacle_initWith, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("syncToObstacle", js_cocos2dx_navmesh_NavMeshObstacle_syncToObstacle, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("syncToNode", js_cocos2dx_navmesh_NavMeshObstacle_syncToNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getHeight", js_cocos2dx_navmesh_NavMeshObstacle_getHeight, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSyncFlag", js_cocos2dx_navmesh_NavMeshObstacle_setSyncFlag, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRadius", js_cocos2dx_navmesh_NavMeshObstacle_getRadius, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_navmesh_NavMeshObstacle_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getNavMeshObstacleComponentName", js_cocos2dx_navmesh_NavMeshObstacle_getNavMeshObstacleComponentName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Component_prototype);
    jsb_cocos2d_NavMeshObstacle_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_NavMeshObstacle_class,
        js_cocos2dx_navmesh_NavMeshObstacle_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_cocos2d_NavMeshObstacle_prototype);
    jsb_register_class<cocos2d::NavMeshObstacle>(cx, jsb_cocos2d_NavMeshObstacle_class, proto, parent_proto);
}

JSClass  *jsb_cocos2d_NavMesh_class;
JSObject *jsb_cocos2d_NavMesh_prototype;

bool js_cocos2dx_navmesh_NavMesh_removeNavMeshObstacle(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMesh* cobj = (cocos2d::NavMesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMesh_removeNavMeshObstacle : Invalid Native Object");
    if (argc == 1) {
        cocos2d::NavMeshObstacle* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::NavMeshObstacle*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMesh_removeNavMeshObstacle : Error processing arguments");
        cobj->removeNavMeshObstacle(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMesh_removeNavMeshObstacle : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_navmesh_NavMesh_removeNavMeshAgent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMesh* cobj = (cocos2d::NavMesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMesh_removeNavMeshAgent : Invalid Native Object");
    if (argc == 1) {
        cocos2d::NavMeshAgent* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::NavMeshAgent*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMesh_removeNavMeshAgent : Error processing arguments");
        cobj->removeNavMeshAgent(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMesh_removeNavMeshAgent : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_navmesh_NavMesh_update(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMesh* cobj = (cocos2d::NavMesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMesh_update : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMesh_update : Error processing arguments");
        cobj->update(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMesh_update : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_navmesh_NavMesh_isDebugDrawEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMesh* cobj = (cocos2d::NavMesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMesh_isDebugDrawEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isDebugDrawEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMesh_isDebugDrawEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_navmesh_NavMesh_addNavMeshAgent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMesh* cobj = (cocos2d::NavMesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMesh_addNavMeshAgent : Invalid Native Object");
    if (argc == 1) {
        cocos2d::NavMeshAgent* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::NavMeshAgent*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMesh_addNavMeshAgent : Error processing arguments");
        cobj->addNavMeshAgent(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMesh_addNavMeshAgent : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_navmesh_NavMesh_addNavMeshObstacle(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMesh* cobj = (cocos2d::NavMesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMesh_addNavMeshObstacle : Invalid Native Object");
    if (argc == 1) {
        cocos2d::NavMeshObstacle* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::NavMeshObstacle*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMesh_addNavMeshObstacle : Error processing arguments");
        cobj->addNavMeshObstacle(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMesh_addNavMeshObstacle : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_navmesh_NavMesh_setDebugDrawEnable(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMesh* cobj = (cocos2d::NavMesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMesh_setDebugDrawEnable : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMesh_setDebugDrawEnable : Error processing arguments");
        cobj->setDebugDrawEnable(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMesh_setDebugDrawEnable : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_navmesh_NavMesh_debugDraw(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::NavMesh* cobj = (cocos2d::NavMesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_navmesh_NavMesh_debugDraw : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Renderer* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Renderer*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMesh_debugDraw : Error processing arguments");
        cobj->debugDraw(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMesh_debugDraw : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_navmesh_NavMesh_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_navmesh_NavMesh_create : Error processing arguments");

        auto ret = cocos2d::NavMesh::create(arg0, arg1);
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::NavMesh>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocos2d::NavMesh"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_navmesh_NavMesh_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_navmesh_NavMesh_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::NavMesh* cobj = new (std::nothrow) cocos2d::NavMesh();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::NavMesh>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::NavMesh"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


void js_register_cocos2dx_navmesh_NavMesh(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_NavMesh_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_NavMesh_class->name = "NavMesh";
    jsb_cocos2d_NavMesh_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_NavMesh_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_NavMesh_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_NavMesh_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_NavMesh_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_NavMesh_class->resolve = JS_ResolveStub;
    jsb_cocos2d_NavMesh_class->convert = JS_ConvertStub;
    jsb_cocos2d_NavMesh_class->finalize = jsb_ref_finalize;
    jsb_cocos2d_NavMesh_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("removeNavMeshObstacle", js_cocos2dx_navmesh_NavMesh_removeNavMeshObstacle, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeNavMeshAgent", js_cocos2dx_navmesh_NavMesh_removeNavMeshAgent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("update", js_cocos2dx_navmesh_NavMesh_update, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isDebugDrawEnabled", js_cocos2dx_navmesh_NavMesh_isDebugDrawEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addNavMeshAgent", js_cocos2dx_navmesh_NavMesh_addNavMeshAgent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addNavMeshObstacle", js_cocos2dx_navmesh_NavMesh_addNavMeshObstacle, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDebugDrawEnable", js_cocos2dx_navmesh_NavMesh_setDebugDrawEnable, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("debugDraw", js_cocos2dx_navmesh_NavMesh_debugDraw, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_navmesh_NavMesh_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_NavMesh_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocos2d_NavMesh_class,
        js_cocos2dx_navmesh_NavMesh_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_cocos2d_NavMesh_prototype);
    jsb_register_class<cocos2d::NavMesh>(cx, jsb_cocos2d_NavMesh_class, proto, JS::NullPtr());
}

void register_all_cocos2dx_navmesh(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "jsb", &ns);

    js_register_cocos2dx_navmesh_NavMeshObstacle(cx, ns);
    js_register_cocos2dx_navmesh_NavMeshAgent(cx, ns);
    js_register_cocos2dx_navmesh_NavMesh(cx, ns);
}

#endif //#if CC_USE_NAVMESH
