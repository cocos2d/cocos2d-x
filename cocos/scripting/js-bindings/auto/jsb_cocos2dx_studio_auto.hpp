#include "base/ccConfig.h"
#ifndef __cocos2dx_studio_h__
#define __cocos2dx_studio_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_cocostudio_ActionObject_class;
extern JSObject *jsb_cocostudio_ActionObject_prototype;

bool js_cocos2dx_studio_ActionObject_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ActionObject_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ActionObject(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ActionObject_setCurrentTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_pause(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_setName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_setUnitTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_getTotalTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_getName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_stop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_play(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_getCurrentTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_removeActionNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_getLoop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_initWithBinary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_addActionNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_getUnitTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_isPlaying(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_updateToFrameByTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_setLoop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_simulationActionUpdate(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionObject_ActionObject(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_ActionManagerEx_class;
extern JSObject *jsb_cocostudio_ActionManagerEx_prototype;

bool js_cocos2dx_studio_ActionManagerEx_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ActionManagerEx_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ActionManagerEx(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ActionManagerEx_stopActionByName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionManagerEx_getActionByName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionManagerEx_initWithBinary(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionManagerEx_playActionByName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionManagerEx_releaseActions(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionManagerEx_destroyInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionManagerEx_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_BaseData_class;
extern JSObject *jsb_cocostudio_BaseData_prototype;

bool js_cocos2dx_studio_BaseData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_BaseData_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_BaseData(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_BaseData_getColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BaseData_setColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BaseData_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BaseData_BaseData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_MovementData_class;
extern JSObject *jsb_cocostudio_MovementData_prototype;

bool js_cocos2dx_studio_MovementData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_MovementData_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_MovementData(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_MovementData_getMovementBoneData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_MovementData_addMovementBoneData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_MovementData_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_MovementData_MovementData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_AnimationData_class;
extern JSObject *jsb_cocostudio_AnimationData_prototype;

bool js_cocos2dx_studio_AnimationData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_AnimationData_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_AnimationData(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_AnimationData_getMovement(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_AnimationData_getMovementCount(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_AnimationData_addMovement(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_AnimationData_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_AnimationData_AnimationData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_ContourData_class;
extern JSObject *jsb_cocostudio_ContourData_prototype;

bool js_cocos2dx_studio_ContourData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ContourData_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ContourData(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ContourData_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ContourData_addVertex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ContourData_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ContourData_ContourData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_TextureData_class;
extern JSObject *jsb_cocostudio_TextureData_prototype;

bool js_cocos2dx_studio_TextureData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_TextureData_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_TextureData(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_TextureData_getContourData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_TextureData_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_TextureData_addContourData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_TextureData_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_TextureData_TextureData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_ProcessBase_class;
extern JSObject *jsb_cocostudio_ProcessBase_prototype;

bool js_cocos2dx_studio_ProcessBase_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ProcessBase_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ProcessBase(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ProcessBase_play(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ProcessBase_pause(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ProcessBase_getRawDuration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ProcessBase_resume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ProcessBase_setIsComplete(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ProcessBase_stop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ProcessBase_update(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ProcessBase_getCurrentFrameIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ProcessBase_isComplete(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ProcessBase_getCurrentPercent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ProcessBase_setIsPause(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ProcessBase_getProcessScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ProcessBase_isPause(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ProcessBase_isPlaying(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ProcessBase_setProcessScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ProcessBase_setIsPlaying(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ProcessBase_ProcessBase(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_Tween_class;
extern JSObject *jsb_cocostudio_Tween_prototype;

bool js_cocos2dx_studio_Tween_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_Tween_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_Tween(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_Tween_getAnimation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Tween_gotoAndPause(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Tween_play(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Tween_gotoAndPlay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Tween_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Tween_setAnimation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Tween_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Tween_Tween(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_ColliderFilter_class;
extern JSObject *jsb_cocostudio_ColliderFilter_prototype;

bool js_cocos2dx_studio_ColliderFilter_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ColliderFilter_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ColliderFilter(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);

extern JSClass  *jsb_cocostudio_ColliderBody_class;
extern JSObject *jsb_cocostudio_ColliderBody_prototype;

bool js_cocos2dx_studio_ColliderBody_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ColliderBody_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ColliderBody(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);

extern JSClass  *jsb_cocostudio_ColliderDetector_class;
extern JSObject *jsb_cocostudio_ColliderDetector_prototype;

bool js_cocos2dx_studio_ColliderDetector_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ColliderDetector_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ColliderDetector(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ColliderDetector_getBone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ColliderDetector_getActive(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ColliderDetector_getColliderBodyList(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ColliderDetector_updateTransform(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ColliderDetector_removeAll(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ColliderDetector_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ColliderDetector_setActive(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ColliderDetector_setBone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ColliderDetector_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_DecorativeDisplay_class;
extern JSObject *jsb_cocostudio_DecorativeDisplay_prototype;

bool js_cocos2dx_studio_DecorativeDisplay_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_DecorativeDisplay_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_DecorativeDisplay(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_DecorativeDisplay_getColliderDetector(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DecorativeDisplay_getDisplay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DecorativeDisplay_setDisplay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DecorativeDisplay_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DecorativeDisplay_setDisplayData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DecorativeDisplay_getDisplayData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DecorativeDisplay_setColliderDetector(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DecorativeDisplay_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_DisplayManager_class;
extern JSObject *jsb_cocostudio_DisplayManager_prototype;

bool js_cocos2dx_studio_DisplayManager_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_DisplayManager_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_DisplayManager(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_DisplayManager_getCurrentDecorativeDisplay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_getDisplayRenderNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_getAnchorPointInPoints(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_setCurrentDecorativeDisplay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_getDisplayRenderNodeType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_removeDisplay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_setForceChangeDisplay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_getContentSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_getBoundingBox(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_addDisplay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_containPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_initDisplayList(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_changeDisplayWithIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_changeDisplayWithName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_isForceChangeDisplay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_getDecorativeDisplayByIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_getCurrentDisplayIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_getAnchorPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_getDecorativeDisplayList(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_isVisible(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_setVisible(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_DisplayManager_DisplayManager(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_Bone_class;
extern JSObject *jsb_cocostudio_Bone_prototype;

bool js_cocos2dx_studio_Bone_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_Bone_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_Bone(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_Bone_isTransformDirty(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_isIgnoreMovementBoneData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_updateZOrder(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_getDisplayRenderNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_isBlendDirty(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_addChildBone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_getWorldInfo(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_getTween(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_getParentBone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_updateColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_setTransformDirty(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_getDisplayRenderNodeType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_removeDisplay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_setBoneData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_setParentBone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_addDisplay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_setIgnoreMovementBoneData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_removeFromParent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_getColliderDetector(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_getChildArmature(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_changeDisplayWithIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_changeDisplayWithName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_setArmature(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_setBlendDirty(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_removeChildBone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_setChildArmature(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_getNodeToArmatureTransform(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_getDisplayManager(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_getArmature(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Bone_Bone(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_BatchNode_class;
extern JSObject *jsb_cocostudio_BatchNode_prototype;

bool js_cocos2dx_studio_BatchNode_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_BatchNode_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_BatchNode(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_BatchNode_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_ArmatureAnimation_class;
extern JSObject *jsb_cocostudio_ArmatureAnimation_prototype;

bool js_cocos2dx_studio_ArmatureAnimation_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ArmatureAnimation_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ArmatureAnimation(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ArmatureAnimation_getSpeedScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureAnimation_play(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureAnimation_gotoAndPause(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureAnimation_playWithIndexes(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureAnimation_setAnimationData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureAnimation_setSpeedScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureAnimation_getAnimationData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureAnimation_gotoAndPlay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureAnimation_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureAnimation_playWithNames(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureAnimation_getMovementCount(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureAnimation_playWithIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureAnimation_getCurrentMovementID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureAnimation_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureAnimation_ArmatureAnimation(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_ArmatureDataManager_class;
extern JSObject *jsb_cocostudio_ArmatureDataManager_prototype;

bool js_cocos2dx_studio_ArmatureDataManager_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ArmatureDataManager_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ArmatureDataManager(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ArmatureDataManager_getAnimationDatas(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureDataManager_removeAnimationData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureDataManager_addArmatureData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureDataManager_addArmatureFileInfo(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureDataManager_removeArmatureFileInfo(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureDataManager_getTextureData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureDataManager_getArmatureData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureDataManager_getAnimationData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureDataManager_addAnimationData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureDataManager_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureDataManager_removeArmatureData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureDataManager_getArmatureDatas(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureDataManager_removeTextureData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureDataManager_addTextureData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureDataManager_isAutoLoadSpriteFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureDataManager_addSpriteFrameFromFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureDataManager_destroyInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ArmatureDataManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_Armature_class;
extern JSObject *jsb_cocostudio_Armature_prototype;

bool js_cocos2dx_studio_Armature_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_Armature_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_Armature(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_Armature_getBone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_changeBoneParent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_setAnimation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_getBoneAtPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_getArmatureTransformDirty(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_setVersion(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_updateOffsetPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_getParentBone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_removeBone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_getBatchNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_setParentBone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_setBatchNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_setArmatureData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_addBone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_getArmatureData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_getBoundingBox(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_getVersion(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_getAnimation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_getOffsetPoints(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_getBoneDic(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Armature_Armature(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_Skin_class;
extern JSObject *jsb_cocostudio_Skin_prototype;

bool js_cocos2dx_studio_Skin_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_Skin_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_Skin(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_Skin_getBone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Skin_getNodeToWorldTransformAR(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Skin_getDisplayName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Skin_updateArmatureTransform(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Skin_setBone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Skin_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Skin_createWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Skin_Skin(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_ComAttribute_class;
extern JSObject *jsb_cocostudio_ComAttribute_prototype;

bool js_cocos2dx_studio_ComAttribute_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ComAttribute_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ComAttribute(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ComAttribute_getFloat(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAttribute_getBool(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAttribute_getString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAttribute_setFloat(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAttribute_setString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAttribute_setInt(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAttribute_parse(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAttribute_getInt(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAttribute_setBool(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAttribute_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAttribute_ComAttribute(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_ComAudio_class;
extern JSObject *jsb_cocostudio_ComAudio_prototype;

bool js_cocos2dx_studio_ComAudio_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ComAudio_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ComAudio(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ComAudio_stopAllEffects(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_getEffectsVolume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_stopEffect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_getBackgroundMusicVolume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_willPlayBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_setBackgroundMusicVolume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_end(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_start(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_stopBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_pauseBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_isBackgroundMusicPlaying(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_isLoop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_resumeAllEffects(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_pauseAllEffects(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_preloadBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_playBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_stop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_playEffect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_preloadEffect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_setLoop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_unloadEffect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_rewindBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_pauseEffect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_resumeBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_setFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_setEffectsVolume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_getFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_resumeEffect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComAudio_ComAudio(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_InputDelegate_class;
extern JSObject *jsb_cocostudio_InputDelegate_prototype;

bool js_cocos2dx_studio_InputDelegate_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_InputDelegate_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_InputDelegate(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_InputDelegate_isAccelerometerEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InputDelegate_setKeypadEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InputDelegate_getTouchMode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InputDelegate_setAccelerometerEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InputDelegate_isKeypadEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InputDelegate_isTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InputDelegate_setTouchPriority(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InputDelegate_getTouchPriority(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InputDelegate_setTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InputDelegate_setTouchMode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_ComController_class;
extern JSObject *jsb_cocostudio_ComController_prototype;

bool js_cocos2dx_studio_ComController_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ComController_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ComController(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ComController_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComController_ComController(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_ComRender_class;
extern JSObject *jsb_cocostudio_ComRender_prototype;

bool js_cocos2dx_studio_ComRender_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ComRender_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ComRender(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ComRender_setNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComRender_getNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComRender_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComRender_ComRender(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_Frame_class;
extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

bool js_cocos2dx_studio_Frame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_Frame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_Frame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_Frame_clone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_setTweenType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_setNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_setTimeline(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_isEnterWhenPassed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_getTweenType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_getFrameIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_apply(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_isTween(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_setFrameIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_setTween(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_getTimeline(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Frame_getNode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_VisibleFrame_class;
extern JSObject *jsb_cocostudio_timeline_VisibleFrame_prototype;

bool js_cocos2dx_studio_VisibleFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_VisibleFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_VisibleFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_VisibleFrame_isVisible(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_VisibleFrame_setVisible(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_VisibleFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_VisibleFrame_VisibleFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_TextureFrame_class;
extern JSObject *jsb_cocostudio_timeline_TextureFrame_prototype;

bool js_cocos2dx_studio_TextureFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_TextureFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_TextureFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_TextureFrame_getTextureName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_TextureFrame_setTextureName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_TextureFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_TextureFrame_TextureFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_RotationFrame_class;
extern JSObject *jsb_cocostudio_timeline_RotationFrame_prototype;

bool js_cocos2dx_studio_RotationFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_RotationFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_RotationFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_RotationFrame_setRotation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_RotationFrame_getRotation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_RotationFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_RotationFrame_RotationFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_SkewFrame_class;
extern JSObject *jsb_cocostudio_timeline_SkewFrame_prototype;

bool js_cocos2dx_studio_SkewFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_SkewFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_SkewFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_SkewFrame_getSkewY(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_SkewFrame_setSkewX(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_SkewFrame_setSkewY(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_SkewFrame_getSkewX(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_SkewFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_SkewFrame_SkewFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_RotationSkewFrame_class;
extern JSObject *jsb_cocostudio_timeline_RotationSkewFrame_prototype;

bool js_cocos2dx_studio_RotationSkewFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_RotationSkewFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_RotationSkewFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_RotationSkewFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_RotationSkewFrame_RotationSkewFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_PositionFrame_class;
extern JSObject *jsb_cocostudio_timeline_PositionFrame_prototype;

bool js_cocos2dx_studio_PositionFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_PositionFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_PositionFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_PositionFrame_getX(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_PositionFrame_getY(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_PositionFrame_setPosition(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_PositionFrame_setX(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_PositionFrame_setY(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_PositionFrame_getPosition(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_PositionFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_PositionFrame_PositionFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_ScaleFrame_class;
extern JSObject *jsb_cocostudio_timeline_ScaleFrame_prototype;

bool js_cocos2dx_studio_ScaleFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ScaleFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ScaleFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ScaleFrame_setScaleY(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ScaleFrame_setScaleX(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ScaleFrame_getScaleY(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ScaleFrame_getScaleX(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ScaleFrame_setScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ScaleFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ScaleFrame_ScaleFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_AnchorPointFrame_class;
extern JSObject *jsb_cocostudio_timeline_AnchorPointFrame_prototype;

bool js_cocos2dx_studio_AnchorPointFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_AnchorPointFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_AnchorPointFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_AnchorPointFrame_setAnchorPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_AnchorPointFrame_getAnchorPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_AnchorPointFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_AnchorPointFrame_AnchorPointFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_InnerActionFrame_class;
extern JSObject *jsb_cocostudio_timeline_InnerActionFrame_prototype;

bool js_cocos2dx_studio_InnerActionFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_InnerActionFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_InnerActionFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_InnerActionFrame_getEndFrameIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_getStartFrameIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_getInnerActionType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_setEndFrameIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_setEnterWithName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_setSingleFrameIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_setStartFrameIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_getSingleFrameIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_setInnerActionType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_setAnimationName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_InnerActionFrame_InnerActionFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_ColorFrame_class;
extern JSObject *jsb_cocostudio_timeline_ColorFrame_prototype;

bool js_cocos2dx_studio_ColorFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ColorFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ColorFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ColorFrame_getColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ColorFrame_setColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ColorFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ColorFrame_ColorFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_AlphaFrame_class;
extern JSObject *jsb_cocostudio_timeline_AlphaFrame_prototype;

bool js_cocos2dx_studio_AlphaFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_AlphaFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_AlphaFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_AlphaFrame_getAlpha(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_AlphaFrame_setAlpha(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_AlphaFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_AlphaFrame_AlphaFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_EventFrame_class;
extern JSObject *jsb_cocostudio_timeline_EventFrame_prototype;

bool js_cocos2dx_studio_EventFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_EventFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_EventFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_EventFrame_setEvent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_EventFrame_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_EventFrame_getEvent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_EventFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_EventFrame_EventFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_ZOrderFrame_class;
extern JSObject *jsb_cocostudio_timeline_ZOrderFrame_prototype;

bool js_cocos2dx_studio_ZOrderFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ZOrderFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ZOrderFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ZOrderFrame_getZOrder(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ZOrderFrame_setZOrder(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ZOrderFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ZOrderFrame_ZOrderFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_BlendFuncFrame_class;
extern JSObject *jsb_cocostudio_timeline_BlendFuncFrame_prototype;

bool js_cocos2dx_studio_BlendFuncFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_BlendFuncFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_BlendFuncFrame(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_BlendFuncFrame_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BlendFuncFrame_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BlendFuncFrame_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BlendFuncFrame_BlendFuncFrame(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_Timeline_class;
extern JSObject *jsb_cocostudio_timeline_Timeline_prototype;

bool js_cocos2dx_studio_Timeline_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_Timeline_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_Timeline(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_Timeline_clone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_gotoFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_setNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_getActionTimeline(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_insertFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_setActionTag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_addFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_getFrames(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_getActionTag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_getNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_removeFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_setActionTimeline(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_stepToFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_Timeline_Timeline(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_ActionTimelineData_class;
extern JSObject *jsb_cocostudio_timeline_ActionTimelineData_prototype;

bool js_cocos2dx_studio_ActionTimelineData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ActionTimelineData_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ActionTimelineData(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ActionTimelineData_setActionTag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimelineData_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimelineData_getActionTag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimelineData_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimelineData_ActionTimelineData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_ActionTimeline_class;
extern JSObject *jsb_cocostudio_timeline_ActionTimeline_prototype;

bool js_cocos2dx_studio_ActionTimeline_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ActionTimeline_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ActionTimeline(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ActionTimeline_setFrameEventCallFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_clearFrameEndCallFuncs(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_setAnimationEndCallFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_addTimeline(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_getCurrentFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_getStartFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_pause(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_start(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_removeTimeline(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_setLastFrameCallFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_IsAnimationInfoExists(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_getTimelines(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_play(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_getAnimationInfo(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_resume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_addFrameEndCallFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_removeAnimationInfo(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_getTimeSpeed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_addAnimationInfo(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_getDuration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_gotoFrameAndPause(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_isPlaying(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFuncs(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_gotoFrameAndPlay(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_clearFrameEventCallFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_getEndFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_setTimeSpeed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_clearLastFrameCallFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_setDuration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_setCurrentFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ActionTimeline_ActionTimeline(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_BoneNode_class;
extern JSObject *jsb_cocostudio_timeline_BoneNode_prototype;

bool js_cocos2dx_studio_BoneNode_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_BoneNode_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_BoneNode(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_BoneNode_getDebugDrawWidth(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_getChildBones(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_getAllSubBones(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_setDebugDrawEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_getVisibleSkinsRect(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_getAllSubSkins(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_displaySkin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_isDebugDrawEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_addSkin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_getRootSkeletonNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_setDebugDrawLength(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_getSkins(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_getVisibleSkins(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_setDebugDrawWidth(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_getDebugDrawLength(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_setDebugDrawColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_getDebugDrawColor(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_BoneNode_BoneNode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_timeline_SkeletonNode_class;
extern JSObject *jsb_cocostudio_timeline_SkeletonNode_prototype;

bool js_cocos2dx_studio_SkeletonNode_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_SkeletonNode_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_SkeletonNode(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_SkeletonNode_getBoneNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_SkeletonNode_changeSkins(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_SkeletonNode_addSkinGroup(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_SkeletonNode_getAllSubBonesMap(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_SkeletonNode_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_SkeletonNode_SkeletonNode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocostudio_ComExtensionData_class;
extern JSObject *jsb_cocostudio_ComExtensionData_prototype;

bool js_cocos2dx_studio_ComExtensionData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_studio_ComExtensionData_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_studio_ComExtensionData(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_studio_ComExtensionData_setActionTag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComExtensionData_getCustomProperty(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComExtensionData_getActionTag(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComExtensionData_setCustomProperty(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComExtensionData_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_studio_ComExtensionData_ComExtensionData(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __cocos2dx_studio_h__
