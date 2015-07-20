#include "base/ccConfig.h"
#ifndef __cocos2dx_3d_h__
#define __cocos2dx_3d_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_cocos2d_Animation3D_class;
extern JSObject *jsb_cocos2d_Animation3D_prototype;

bool js_cocos2dx_3d_Animation3D_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_3d_Animation3D_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_3d_Animation3D(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_3d(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_3d_Animation3D_initWithFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Animation3D_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Animation3D_getBoneCurveByName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Animation3D_getDuration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Animation3D_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Animation3D_Animation3D(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_Animate3D_class;
extern JSObject *jsb_cocos2d_Animate3D_prototype;

bool js_cocos2dx_3d_Animate3D_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_3d_Animate3D_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_3d_Animate3D(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_3d(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_3d_Animate3D_getSpeed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Animate3D_setQuality(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Animate3D_setWeight(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Animate3D_removeFromMap(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Animate3D_initWithFrames(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Animate3D_getOriginInterval(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Animate3D_setSpeed(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Animate3D_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Animate3D_setOriginInterval(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Animate3D_getWeight(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Animate3D_getQuality(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Animate3D_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Animate3D_getTransitionTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Animate3D_createWithFrames(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Animate3D_setTransitionTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Animate3D_Animate3D(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_AttachNode_class;
extern JSObject *jsb_cocos2d_AttachNode_prototype;

bool js_cocos2dx_3d_AttachNode_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_3d_AttachNode_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_3d_AttachNode(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_3d(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_3d_AttachNode_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_AttachNode_AttachNode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_BillBoard_class;
extern JSObject *jsb_cocos2d_BillBoard_prototype;

bool js_cocos2dx_3d_BillBoard_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_3d_BillBoard_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_3d_BillBoard(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_3d(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_3d_BillBoard_getMode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_BillBoard_setMode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_BillBoard_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_BillBoard_createWithTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_BillBoard_BillBoard(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_Mesh_class;
extern JSObject *jsb_cocos2d_Mesh_prototype;

bool js_cocos2dx_3d_Mesh_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_3d_Mesh_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_3d_Mesh(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_3d(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_3d_Mesh_setTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_getTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_getSkin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_getMaterial(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_getVertexSizeInBytes(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_setMaterial(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_getName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_getIndexFormat(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_getGLProgramState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_getVertexBuffer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_calculateAABB(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_hasVertexAttrib(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_getMeshIndexData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_setName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_getIndexCount(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_setMeshIndexData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_getMeshVertexAttribCount(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_setForce2DQueue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_getPrimitiveType(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_setSkin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_isVisible(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_getIndexBuffer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_setGLProgramState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_setVisible(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Mesh_Mesh(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_Skeleton3D_class;
extern JSObject *jsb_cocos2d_Skeleton3D_prototype;

bool js_cocos2dx_3d_Skeleton3D_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_3d_Skeleton3D_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_3d_Skeleton3D(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_3d(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_3d_Skeleton3D_removeAllBones(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Skeleton3D_addBone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Skeleton3D_getBoneByName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Skeleton3D_getRootBone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Skeleton3D_updateBoneMatrix(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Skeleton3D_getBoneByIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Skeleton3D_getRootCount(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Skeleton3D_getBoneIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Skeleton3D_getBoneCount(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Skeleton3D_Skeleton3D(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_Skybox_class;
extern JSObject *jsb_cocos2d_Skybox_prototype;

bool js_cocos2dx_3d_Skybox_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_3d_Skybox_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_3d_Skybox(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_3d(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_3d_Skybox_reload(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Skybox_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Skybox_setTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Skybox_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Skybox_Skybox(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_Sprite3D_class;
extern JSObject *jsb_cocos2d_Sprite3D_prototype;

bool js_cocos2dx_3d_Sprite3D_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_3d_Sprite3D_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_3d_Sprite3D(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_3d(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_3d_Sprite3D_setCullFaceEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_setTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_getLightMask(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_createAttachSprite3DNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_loadFromFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_getMaterial(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_setCullFace(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_addMesh(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_removeAllAttachNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_setMaterial(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_genGLProgramState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_getMesh(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_createSprite3DNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_getMeshCount(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_onAABBDirty(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_getMeshByIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_createNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_isForceDepthWrite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_getMeshIndexData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_setLightMask(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_afterAsyncLoad(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_loadFromCache(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_initFrom(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_getAttachNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_initWithFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_setForce2DQueue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_removeAttachNode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_getSkeleton(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_setForceDepthWrite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_getMeshByName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3D_Sprite3D(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_Sprite3DCache_class;
extern JSObject *jsb_cocos2d_Sprite3DCache_prototype;

bool js_cocos2dx_3d_Sprite3DCache_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_3d_Sprite3DCache_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_3d_Sprite3DCache(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_3d(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_3d_Sprite3DCache_removeSprite3DData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3DCache_removeAllSprite3DData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3DCache_destroyInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Sprite3DCache_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_Terrain_class;
extern JSObject *jsb_cocos2d_Terrain_prototype;

bool js_cocos2dx_3d_Terrain_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_3d_Terrain_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_3d_Terrain(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_3d(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_3d_Terrain_initHeightMap(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Terrain_setMaxDetailMapAmount(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Terrain_setDrawWire(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Terrain_setIsEnableFrustumCull(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Terrain_setDetailMap(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Terrain_resetHeightMap(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Terrain_setAlphaMap(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Terrain_setSkirtHeightRatio(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Terrain_convertToTerrainSpace(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Terrain_initTextures(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Terrain_initProperties(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Terrain_getHeight(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Terrain_setLODDistance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Terrain_getTerrainSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Terrain_getIntersectionPoint(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Terrain_getNormal(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Terrain_reload(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Terrain_getImageHeight(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Terrain_getMaxHeight(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Terrain_getMinHeight(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_TextureCube_class;
extern JSObject *jsb_cocos2d_TextureCube_prototype;

bool js_cocos2dx_3d_TextureCube_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_3d_TextureCube_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_3d_TextureCube(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_3d(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_3d_TextureCube_reloadTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_TextureCube_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_TextureCube_TextureCube(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_Bundle3D_class;
extern JSObject *jsb_cocos2d_Bundle3D_prototype;

bool js_cocos2dx_3d_Bundle3D_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_3d_Bundle3D_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_3d_Bundle3D(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_3d(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_3d_Bundle3D_load(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Bundle3D_loadSkinData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Bundle3D_clear(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Bundle3D_loadMaterials(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Bundle3D_loadMeshDatas(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Bundle3D_loadNodes(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Bundle3D_loadAnimationData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Bundle3D_createBundle(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Bundle3D_destroyBundle(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Bundle3D_loadObj(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_3d_Bundle3D_Bundle3D(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __cocos2dx_3d_h__
