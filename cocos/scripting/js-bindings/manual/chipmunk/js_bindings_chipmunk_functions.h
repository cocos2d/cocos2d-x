/*
* AUTOGENERATED FILE. DO NOT EDIT IT
* Generated by "generate_js_bindings.py -c chipmunk_jsb.ini" on 2012-11-07
* Script version: v0.3
*/
#include "js_bindings_config.h"
#ifdef JSB_INCLUDE_CHIPMUNK
#include "js_bindings_chipmunk_manual.h"

#ifdef __cplusplus
extern "C" {
#endif
bool JSB_cpArbiterGetCount(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpArbiterGetDepth(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpArbiterGetElasticity(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpArbiterGetFriction(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpArbiterGetNormal(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpArbiterGetPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpArbiterGetSurfaceVelocity(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpArbiterIgnore(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpArbiterIsFirstContact(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpArbiterSetElasticity(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpArbiterSetFriction(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpArbiterSetSurfaceVelocity(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpArbiterTotalImpulse(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpArbiterTotalImpulseWithFriction(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpArbiterTotalKE(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpAreaForCircle(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpAreaForSegment(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBBArea(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBBClampVect(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBBContainsBB(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBBContainsVect(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBBExpand(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBBIntersects(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBBIntersectsSegment(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBBMerge(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBBMergedArea(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBBNew(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBBNewForCircle(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBBSegmentQuery(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBBWrapVect(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyActivate(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyActivateStatic(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyApplyForce(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyApplyImpulse(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyDestroy(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyFree(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyGetAngVel(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyGetAngVelLimit(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyGetAngle(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyGetForce(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyGetMass(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyGetMoment(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyGetPos(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyGetRot(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyGetSpace(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyGetTorque(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyGetVel(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyGetVelAtLocalPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyGetVelAtWorldPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyGetVelLimit(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyInit(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyInitStatic(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyIsRogue(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyIsSleeping(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyIsStatic(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyKineticEnergy(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyLocal2World(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyNew(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyNewStatic(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyResetForces(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodySetAngVel(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodySetAngVelLimit(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodySetAngle(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodySetForce(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodySetMass(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodySetMoment(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodySetPos(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodySetTorque(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodySetVel(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodySetVelLimit(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodySleep(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodySleepWithGroup(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyUpdatePosition(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyUpdateVelocity(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBodyWorld2Local(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBoxShapeNew(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpBoxShapeNew2(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpCircleShapeGetOffset(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpCircleShapeGetRadius(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpCircleShapeNew(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpConstraintActivateBodies(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpConstraintDestroy(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpConstraintFree(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpConstraintGetA(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpConstraintGetB(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpConstraintGetErrorBias(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpConstraintGetImpulse(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpConstraintGetMaxBias(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpConstraintGetMaxForce(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpConstraintGetSpace(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpConstraintSetErrorBias(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpConstraintSetMaxBias(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpConstraintSetMaxForce(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpDampedRotarySpringGetDamping(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpDampedRotarySpringGetRestAngle(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpDampedRotarySpringGetStiffness(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpDampedRotarySpringNew(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpDampedRotarySpringSetDamping(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpDampedRotarySpringSetRestAngle(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpDampedRotarySpringSetStiffness(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpDampedSpringGetAnchr1(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpDampedSpringGetAnchr2(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpDampedSpringGetDamping(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpDampedSpringGetRestLength(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpDampedSpringGetStiffness(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpDampedSpringNew(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpDampedSpringSetAnchr1(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpDampedSpringSetAnchr2(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpDampedSpringSetDamping(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpDampedSpringSetRestLength(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpDampedSpringSetStiffness(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpGearJointGetPhase(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpGearJointGetRatio(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpGearJointNew(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpGearJointSetPhase(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpGearJointSetRatio(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpGrooveJointGetAnchr2(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpGrooveJointGetGrooveA(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpGrooveJointGetGrooveB(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpGrooveJointNew(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpGrooveJointSetAnchr2(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpGrooveJointSetGrooveA(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpGrooveJointSetGrooveB(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpInitChipmunk(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpMomentForBox(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpMomentForBox2(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpMomentForCircle(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpMomentForSegment(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpPinJointGetAnchr1(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpPinJointGetAnchr2(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpPinJointGetDist(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpPinJointNew(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpPinJointSetAnchr1(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpPinJointSetAnchr2(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpPinJointSetDist(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpPivotJointGetAnchr1(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpPivotJointGetAnchr2(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpPivotJointNew(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpPivotJointNew2(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpPivotJointSetAnchr1(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpPivotJointSetAnchr2(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpPolyShapeGetNumVerts(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpPolyShapeGetVert(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpRatchetJointGetAngle(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpRatchetJointGetPhase(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpRatchetJointGetRatchet(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpRatchetJointNew(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpRatchetJointSetAngle(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpRatchetJointSetPhase(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpRatchetJointSetRatchet(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpResetShapeIdCounter(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpRotaryLimitJointGetMax(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpRotaryLimitJointGetMin(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpRotaryLimitJointNew(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpRotaryLimitJointSetMax(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpRotaryLimitJointSetMin(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSegmentShapeGetA(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSegmentShapeGetB(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSegmentShapeGetNormal(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSegmentShapeGetRadius(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSegmentShapeNew(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSegmentShapeSetNeighbors(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeCacheBB(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeDestroy(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeFree(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeGetBB(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeGetBody(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeGetCollisionType(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeGetElasticity(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeGetFriction(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeGetGroup(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeGetLayers(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeGetSensor(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeGetSpace(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeGetSurfaceVelocity(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapePointQuery(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeSetBody(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeSetCollisionType(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeSetElasticity(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeSetFriction(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeSetGroup(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeSetLayers(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeSetSensor(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeSetSurfaceVelocity(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpShapeUpdate(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSimpleMotorGetRate(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSimpleMotorNew(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSimpleMotorSetRate(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSlideJointGetAnchr1(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSlideJointGetAnchr2(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSlideJointGetMax(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSlideJointGetMin(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSlideJointNew(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSlideJointSetAnchr1(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSlideJointSetAnchr2(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSlideJointSetMax(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSlideJointSetMin(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceActivateShapesTouchingShape(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceAddBody(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceAddConstraint(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceAddShape(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceAddStaticShape(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceContainsBody(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceContainsConstraint(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceContainsShape(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceDestroy(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceFree(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceGetCollisionBias(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceGetCollisionPersistence(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceGetCollisionSlop(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceGetCurrentTimeStep(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceGetDamping(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceGetEnableContactGraph(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceGetGravity(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceGetIdleSpeedThreshold(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceGetIterations(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceGetSleepTimeThreshold(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceGetStaticBody(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceInit(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceIsLocked(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceNew(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpacePointQueryFirst(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceReindexShape(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceReindexShapesForBody(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceReindexStatic(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceRemoveBody(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceRemoveConstraint(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceRemoveShape(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceRemoveStaticShape(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceSetCollisionBias(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceSetCollisionPersistence(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceSetCollisionSlop(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceSetDamping(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceSetEnableContactGraph(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceSetGravity(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceSetIdleSpeedThreshold(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceSetIterations(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceSetSleepTimeThreshold(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceStep(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpSpaceUseSpatialHash(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpfabs(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpfclamp(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpfclamp01(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpflerp(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpflerpconst(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpfmax(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpfmin(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvadd(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvclamp(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvcross(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvdist(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvdistsq(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvdot(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpveql(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvforangle(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvlength(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvlengthsq(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvlerp(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvlerpconst(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvmult(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvnear(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvneg(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvnormalize(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvnormalize_safe(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvperp(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvproject(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvrotate(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvrperp(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvslerp(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvslerpconst(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvsub(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvtoangle(JSContext *cx, uint32_t argc, jsval *vp);
bool JSB_cpvunrotate(JSContext *cx, uint32_t argc, jsval *vp);

#ifdef __cplusplus
}
#endif


#endif // JSB_INCLUDE_CHIPMUNK
