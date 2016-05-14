#include "base/ccConfig.h"
#ifndef __cocos2dx_3d_extension_h__
#define __cocos2dx_3d_extension_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_cocos2d_ParticleSystem3D_class;
extern JSObject *jsb_cocos2d_ParticleSystem3D_prototype;

bool js_cocos2dx_3d_extension_ParticleSystem3D_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_3d_extension_ParticleSystem3D_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_3d_extension_ParticleSystem3D(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_3d_extension(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_3d_extension_ParticleSystem3D_resumeParticleSystem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_ParticleSystem3D_startParticleSystem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_ParticleSystem3D_isEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_ParticleSystem3D_getRender(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_ParticleSystem3D_isKeepLocal(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_ParticleSystem3D_setEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_ParticleSystem3D_getParticleQuota(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_ParticleSystem3D_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_ParticleSystem3D_pauseParticleSystem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_ParticleSystem3D_getState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_ParticleSystem3D_getAliveParticleCount(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_ParticleSystem3D_setParticleQuota(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_ParticleSystem3D_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_ParticleSystem3D_stopParticleSystem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_ParticleSystem3D_setKeepLocal(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_ParticleSystem3D_ParticleSystem3D(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_PUParticleSystem3D_class;
extern JSObject *jsb_cocos2d_PUParticleSystem3D_prototype;

bool js_cocos2dx_3d_extension_PUParticleSystem3D_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_3d_extension_PUParticleSystem3D_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_3d_extension_PUParticleSystem3D(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_3d_extension(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_initWithFilePath(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getParticleSystemScaleVelocity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_setEmittedSystemQuota(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getDefaultDepth(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getEmittedSystemQuota(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_initWithFilePathAndMaterialPath(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_clearAllParticles(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getMaterialName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_calulateRotationOffset(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getMaxVelocity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_forceUpdate(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getTimeElapsedSinceStart(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getEmittedEmitterQuota(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_isMarkedForEmission(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getDefaultWidth(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_setEmittedEmitterQuota(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_setMarkedForEmission(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_clone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_setDefaultWidth(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_copyAttributesTo(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_setMaterialName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getParentParticleSystem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_setMaxVelocity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getDefaultHeight(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getDerivedPosition(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_rotationOffset(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getDerivedOrientation(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_removeAllEmitter(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_setParticleSystemScaleVelocity(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getDerivedScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_setDefaultHeight(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_removeAllListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_initSystem(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_setDefaultDepth(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_extension_PUParticleSystem3D_PUParticleSystem3D(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __cocos2dx_3d_extension_h__
