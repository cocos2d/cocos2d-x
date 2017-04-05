#include "base/ccConfig.h"
#if CC_USE_NAVMESH
#ifndef __cocos2dx_navmesh_h__
#define __cocos2dx_navmesh_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_cocos2d_NavMeshAgent_class;
extern JSObject *jsb_cocos2d_NavMeshAgent_prototype;

bool js_cocos2dx_navmesh_NavMeshAgent_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_navmesh_NavMeshAgent_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_navmesh_NavMeshAgent(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_navmesh(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_navmesh_NavMeshAgent_setMaxSpeed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_syncToNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_completeOffMeshLink(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_getSeparationWeight(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_setAutoTraverseOffMeshLink(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_getCurrentVelocity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_syncToAgent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_isOnOffMeshLink(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_setSeparationWeight(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_pause(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_setAutoOrientation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_getHeight(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_getMaxSpeed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_getCurrentOffMeshLinkData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_getRadius(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_setSyncFlag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_getSyncFlag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_resume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_stop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_setMaxAcceleration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_setOrientationRefAxes(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_getMaxAcceleration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_setHeight(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_getObstacleAvoidanceType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_getVelocity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_setRadius(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_setObstacleAvoidanceType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_getNavMeshAgentComponentName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshAgent_NavMeshAgent(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_NavMeshObstacle_class;
extern JSObject *jsb_cocos2d_NavMeshObstacle_prototype;

bool js_cocos2dx_navmesh_NavMeshObstacle_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_navmesh_NavMeshObstacle_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_navmesh_NavMeshObstacle(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_navmesh(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_navmesh_NavMeshObstacle_getSyncFlag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshObstacle_initWith(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshObstacle_syncToObstacle(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshObstacle_syncToNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshObstacle_getHeight(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshObstacle_setSyncFlag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshObstacle_getRadius(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshObstacle_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshObstacle_getNavMeshObstacleComponentName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMeshObstacle_NavMeshObstacle(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_NavMesh_class;
extern JSObject *jsb_cocos2d_NavMesh_prototype;

bool js_cocos2dx_navmesh_NavMesh_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_navmesh_NavMesh_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_navmesh_NavMesh(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_navmesh(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_navmesh_NavMesh_removeNavMeshObstacle(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMesh_removeNavMeshAgent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMesh_update(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMesh_isDebugDrawEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMesh_addNavMeshAgent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMesh_addNavMeshObstacle(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMesh_setDebugDrawEnable(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMesh_debugDraw(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMesh_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_navmesh_NavMesh_NavMesh(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __cocos2dx_navmesh_h__
#endif //#if CC_USE_NAVMESH
