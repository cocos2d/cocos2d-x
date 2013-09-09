#ifndef __jsb_CCDatas_h__
#define __jsb_CCDatas_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_CCBaseData_class;
extern JSObject *jsb_CCBaseData_prototype;

JSBool js_jsb_CCDatas_CCBaseData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_CCDatas_CCBaseData_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_CCDatas_CCBaseData(JSContext *cx, JSObject *global);
void register_all_jsb_CCDatas(JSContext* cx, JSObject* obj);
JSBool js_jsb_CCDatas_CCBaseData_getColor(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCBaseData_copy(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCBaseData_subtract(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCBaseData_setColor(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCBaseData_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCBaseData_CCBaseData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CCDisplayData_class;
extern JSObject *jsb_CCDisplayData_prototype;

JSBool js_jsb_CCDatas_CCDisplayData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_CCDatas_CCDisplayData_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_CCDatas_CCDisplayData(JSContext *cx, JSObject *global);
void register_all_jsb_CCDatas(JSContext* cx, JSObject* obj);
JSBool js_jsb_CCDatas_CCDisplayData_changeDisplayToTexture(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCDisplayData_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCDisplayData_CCDisplayData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CCSpriteDisplayData_class;
extern JSObject *jsb_CCSpriteDisplayData_prototype;

JSBool js_jsb_CCDatas_CCSpriteDisplayData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_CCDatas_CCSpriteDisplayData_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_CCDatas_CCSpriteDisplayData(JSContext *cx, JSObject *global);
void register_all_jsb_CCDatas(JSContext* cx, JSObject* obj);
JSBool js_jsb_CCDatas_CCSpriteDisplayData_copy(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCSpriteDisplayData_setParam(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCSpriteDisplayData_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCSpriteDisplayData_CCSpriteDisplayData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CCArmatureDisplayData_class;
extern JSObject *jsb_CCArmatureDisplayData_prototype;

JSBool js_jsb_CCDatas_CCArmatureDisplayData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_CCDatas_CCArmatureDisplayData_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_CCDatas_CCArmatureDisplayData(JSContext *cx, JSObject *global);
void register_all_jsb_CCDatas(JSContext* cx, JSObject* obj);
JSBool js_jsb_CCDatas_CCArmatureDisplayData_copy(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCArmatureDisplayData_setParam(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCArmatureDisplayData_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCArmatureDisplayData_CCArmatureDisplayData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CCParticleDisplayData_class;
extern JSObject *jsb_CCParticleDisplayData_prototype;

JSBool js_jsb_CCDatas_CCParticleDisplayData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_CCDatas_CCParticleDisplayData_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_CCDatas_CCParticleDisplayData(JSContext *cx, JSObject *global);
void register_all_jsb_CCDatas(JSContext* cx, JSObject* obj);
JSBool js_jsb_CCDatas_CCParticleDisplayData_copy(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCParticleDisplayData_setParam(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCParticleDisplayData_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCParticleDisplayData_CCParticleDisplayData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CCBoneData_class;
extern JSObject *jsb_CCBoneData_prototype;

JSBool js_jsb_CCDatas_CCBoneData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_CCDatas_CCBoneData_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_CCDatas_CCBoneData(JSContext *cx, JSObject *global);
void register_all_jsb_CCDatas(JSContext* cx, JSObject* obj);
JSBool js_jsb_CCDatas_CCBoneData_getDisplayData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCBoneData_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCBoneData_addDisplayData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCBoneData_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCBoneData_CCBoneData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CCArmatureData_class;
extern JSObject *jsb_CCArmatureData_prototype;

JSBool js_jsb_CCDatas_CCArmatureData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_CCDatas_CCArmatureData_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_CCDatas_CCArmatureData(JSContext *cx, JSObject *global);
void register_all_jsb_CCDatas(JSContext* cx, JSObject* obj);
JSBool js_jsb_CCDatas_CCArmatureData_addBoneData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCArmatureData_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCArmatureData_getBoneData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCArmatureData_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCArmatureData_CCArmatureData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CCFrameData_class;
extern JSObject *jsb_CCFrameData_prototype;

JSBool js_jsb_CCDatas_CCFrameData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_CCDatas_CCFrameData_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_CCDatas_CCFrameData(JSContext *cx, JSObject *global);
void register_all_jsb_CCDatas(JSContext* cx, JSObject* obj);
JSBool js_jsb_CCDatas_CCFrameData_copy(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCFrameData_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCFrameData_CCFrameData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CCMovementBoneData_class;
extern JSObject *jsb_CCMovementBoneData_prototype;

JSBool js_jsb_CCDatas_CCMovementBoneData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_CCDatas_CCMovementBoneData_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_CCDatas_CCMovementBoneData(JSContext *cx, JSObject *global);
void register_all_jsb_CCDatas(JSContext* cx, JSObject* obj);
JSBool js_jsb_CCDatas_CCMovementBoneData_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCMovementBoneData_getFrameData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCMovementBoneData_addFrameData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCMovementBoneData_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCMovementBoneData_CCMovementBoneData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CCMovementData_class;
extern JSObject *jsb_CCMovementData_prototype;

JSBool js_jsb_CCDatas_CCMovementData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_CCDatas_CCMovementData_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_CCDatas_CCMovementData(JSContext *cx, JSObject *global);
void register_all_jsb_CCDatas(JSContext* cx, JSObject* obj);
JSBool js_jsb_CCDatas_CCMovementData_getMovementBoneData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCMovementData_addMovementBoneData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCMovementData_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCMovementData_CCMovementData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CCAnimationData_class;
extern JSObject *jsb_CCAnimationData_prototype;

JSBool js_jsb_CCDatas_CCAnimationData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_CCDatas_CCAnimationData_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_CCDatas_CCAnimationData(JSContext *cx, JSObject *global);
void register_all_jsb_CCDatas(JSContext* cx, JSObject* obj);
JSBool js_jsb_CCDatas_CCAnimationData_getMovement(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCAnimationData_getMovementCount(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCAnimationData_addMovement(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCAnimationData_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCAnimationData_CCAnimationData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CCContourData_class;
extern JSObject *jsb_CCContourData_prototype;

JSBool js_jsb_CCDatas_CCContourData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_CCDatas_CCContourData_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_CCDatas_CCContourData(JSContext *cx, JSObject *global);
void register_all_jsb_CCDatas(JSContext* cx, JSObject* obj);
JSBool js_jsb_CCDatas_CCContourData_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCContourData_addVertex(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCContourData_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCContourData_CCContourData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CCTextureData_class;
extern JSObject *jsb_CCTextureData_prototype;

JSBool js_jsb_CCDatas_CCTextureData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_CCDatas_CCTextureData_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_CCDatas_CCTextureData(JSContext *cx, JSObject *global);
void register_all_jsb_CCDatas(JSContext* cx, JSObject* obj);
JSBool js_jsb_CCDatas_CCTextureData_getContourData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCTextureData_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCTextureData_addContourData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCTextureData_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_CCDatas_CCTextureData_CCTextureData(JSContext *cx, uint32_t argc, jsval *vp);
#endif

