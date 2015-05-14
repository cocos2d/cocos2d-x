#ifndef __cocos2dx_experimental_h__
#define __cocos2dx_experimental_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_cocos2d_experimental_SpritePolygon_class;
extern JSObject *jsb_cocos2d_experimental_SpritePolygon_prototype;

bool js_cocos2dx_experimental_SpritePolygon_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_experimental_SpritePolygon_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_experimental_SpritePolygon(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_experimental(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_experimental_SpritePolygon_setTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_SpritePolygon_initWithTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_SpritePolygon_showDebug(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_SpritePolygon_getTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_SpritePolygon_getArea(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_SpritePolygon_initWithMarching(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_SpritePolygon_getVertCount(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_SpritePolygon_getTrianglesCount(JSContext *cx, uint32_t argc, jsval *vp);
#endif

