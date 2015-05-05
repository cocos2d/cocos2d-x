#ifndef __cocos2dx_spine_h__
#define __cocos2dx_spine_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_spine_SkeletonRenderer_class;
extern JSObject *jsb_spine_SkeletonRenderer_prototype;

bool js_cocos2dx_spine_SkeletonRenderer_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_spine_SkeletonRenderer_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_spine_SkeletonRenderer(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_spine(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_spine_SkeletonRenderer_setTimeScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_getDebugSlotsEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_setAttachment(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_setBonesToSetupPose(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_isOpacityModifyRGB(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_initWithData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_setDebugSlotsEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_setSlotsToSetupPose(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_setOpacityModifyRGB(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_setToSetupPose(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_drawSkeleton(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_updateWorldTransform(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_initialize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_setDebugBonesEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_getDebugBonesEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_getTimeScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_initWithFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_setSkin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_getSkeleton(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_createWithFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonRenderer_SkeletonRenderer(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_spine_SkeletonAnimation_class;
extern JSObject *jsb_spine_SkeletonAnimation_prototype;

bool js_cocos2dx_spine_SkeletonAnimation_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_spine_SkeletonAnimation_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_spine_SkeletonAnimation(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_spine(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_spine_SkeletonAnimation_setStartListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonAnimation_setTrackEventListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonAnimation_getState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonAnimation_setTrackCompleteListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonAnimation_onTrackEntryEvent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonAnimation_setTrackStartListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonAnimation_update(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonAnimation_setCompleteListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonAnimation_setTrackEndListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonAnimation_setEventListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonAnimation_setMix(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonAnimation_setEndListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonAnimation_initialize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonAnimation_clearTracks(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonAnimation_clearTrack(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonAnimation_onAnimationStateEvent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonAnimation_createWithFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_spine_SkeletonAnimation_SkeletonAnimation(JSContext *cx, uint32_t argc, jsval *vp);
#endif

