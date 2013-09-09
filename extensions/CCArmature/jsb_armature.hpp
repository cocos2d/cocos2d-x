#ifndef __jsb_armature_h__
#define __jsb_armature_h__

#include "jsapi.h"
#include "jsfriendapi.h"
#include "cocos2d_specifics.hpp"
#include "CCArmature.h"
#include "CCArmatureAnimation.h"
#include "CCArmatureDataManager.h"
#include "CCSkin.h"
#include "CCBone.h"
#include "jsb_cocos2dx_auto.hpp"

extern JSClass  *jsb_CCBone_class;
extern JSObject *jsb_CCBone_prototype;

JSBool js_jsb_armature_CCBone_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_armature_CCBone_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_armature_CCBone(JSContext *cx, JSObject *global);
void register_all_jsb_armature(JSContext* cx, JSObject* obj);
JSBool js_jsb_armature_CCBone_nodeToWorldTransform(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_isTransformDirty(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_updateZOrder(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_getDisplayRenderNode(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_getTween(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_getParentBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_getBlendType(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_updateColor(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_getName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_setTransformDirty(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_addChildBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_updateDisplayedOpacity(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_setParentBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_setZOrder(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_getIgnoreMovementBoneData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_setIgnoreMovementBoneData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_setName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_removeFromParent(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_getChildArmature(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_update(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_setDisplayManager(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_getTweenData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_setBoneData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_setArmature(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_addDisplay(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_removeChildBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_setChildArmature(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_getDisplayManager(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_getArmature(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_setBlendType(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_changeDisplayByIndex(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_nodeToArmatureTransform(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_updateDisplayedColor(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_getBoneData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCBone_CCBone(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CCArmatureAnimation_class;
extern JSObject *jsb_CCArmatureAnimation_prototype;

JSBool js_jsb_armature_CCArmatureAnimation_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_armature_CCArmatureAnimation_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_armature_CCArmatureAnimation(JSContext *cx, JSObject *global);
void register_all_jsb_armature(JSContext* cx, JSObject* obj);
JSBool js_jsb_armature_CCArmatureAnimation_getSpeedScale(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureAnimation_getAnimationScale(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureAnimation_play(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureAnimation_pause(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureAnimation_setAnimationScale(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureAnimation_resume(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureAnimation_stop(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureAnimation_setAnimationData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureAnimation_setSpeedScale(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureAnimation_update(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureAnimation_getAnimationData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureAnimation_playByIndex(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureAnimation_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureAnimation_getMovementCount(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureAnimation_getCurrentMovementID(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureAnimation_setAnimationInternal(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureAnimation_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureAnimation_CCArmatureAnimation(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_Armature_CCArmatureAnimation_CCArmatureAnimation(JSContext *cx, uint32_t argc, jsval *vp);

class JSArmatureWrapper: public JSCallbackWrapper {
public:
    JSArmatureWrapper();
    virtual ~JSArmatureWrapper();
    
    virtual void setJSCallbackThis(jsval thisObj);
    
    void movementCallbackFunc(cocos2d::extension::CCArmature * pArmature, cocos2d::extension::MovementEventType pMovementEventType, const char *pMovementId);
    void frameCallbackFunc(cocos2d::extension::CCBone *pBone, const char *frameEventName, int originFrameIndex, int currentFrameIndex);
    void addArmatureFileInfoAsyncCallbackFunc(float percent);
    
private:
    bool m_bNeedUnroot;
};

extern JSClass  *jsb_CCArmature_class;
extern JSObject *jsb_CCArmature_prototype;

JSBool js_jsb_armature_CCArmature_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_armature_CCArmature_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_armature_CCArmature(JSContext *cx, JSObject *global);
void register_all_jsb_armature(JSContext* cx, JSObject* obj);
JSBool js_jsb_armature_CCArmature_getBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_changeBoneParent(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_setAnimation(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_getBoneAtPoint(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_getBatchNode(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_setVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_updateOffsetPoint(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_getParentBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_setName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_removeBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_getArmatureTransformDirty(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_getName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_visit(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_setParentBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_setBatchNode(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_draw(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_nodeToParentTransform(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_setArmatureData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_setTextureAtlas(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_addBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_update(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_getArmatureData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_boundingBox(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_getVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_getAnimation(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_getBoneDic(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_getTextureAtlas(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmature_CCArmature(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CCArmatureDataManager_class;
extern JSObject *jsb_CCArmatureDataManager_prototype;

JSBool js_jsb_armature_CCArmatureDataManager_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_armature_CCArmatureDataManager_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_armature_CCArmatureDataManager(JSContext *cx, JSObject *global);
void register_all_jsb_armature(JSContext* cx, JSObject* obj);
JSBool js_jsb_armature_CCArmatureDataManager_getAnimationDatas(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureDataManager_removeAnimationData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureDataManager_addArmatureData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureDataManager_addArmatureFileInfo(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureDataManager_getTextureDatas(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureDataManager_getTextureData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureDataManager_getArmatureData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureDataManager_getAnimationData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureDataManager_removeAll(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureDataManager_addAnimationData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureDataManager_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureDataManager_removeArmatureData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureDataManager_getArmatureDatas(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureDataManager_removeTextureData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureDataManager_addTextureData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureDataManager_isAutoLoadSpriteFile(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureDataManager_addSpriteFrameFromFile(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureDataManager_purge(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCArmatureDataManager_sharedArmatureDataManager(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_CCSkin_class;
extern JSObject *jsb_CCSkin_prototype;

JSBool js_jsb_armature_CCSkin_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_jsb_armature_CCSkin_finalize(JSContext *cx, JSObject *obj);
void js_register_jsb_armature_CCSkin(JSContext *cx, JSObject *global);
void register_all_jsb_armature(JSContext* cx, JSObject* obj);
JSBool js_jsb_armature_CCSkin_getBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCSkin_nodeToWorldTransform(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCSkin_initWithFile(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCSkin_nodeToWorldTransformAR(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCSkin_updateTransform(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCSkin_getDisplayName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCSkin_updateArmatureTransform(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCSkin_initWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCSkin_setBone(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCSkin_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCSkin_createWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_jsb_armature_CCSkin_CCSkin(JSContext *cx, uint32_t argc, jsval *vp);
#endif

