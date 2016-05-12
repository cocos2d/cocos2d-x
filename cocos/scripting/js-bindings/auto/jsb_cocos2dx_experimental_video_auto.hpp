#include "base/ccConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS) && !defined(CC_TARGET_OS_TVOS)
#ifndef __cocos2dx_experimental_video_h__
#define __cocos2dx_experimental_video_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_cocos2d_experimental_ui_VideoPlayer_class;
extern JSObject *jsb_cocos2d_experimental_ui_VideoPlayer_prototype;

bool js_cocos2dx_experimental_video_VideoPlayer_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_experimental_video_VideoPlayer_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_experimental_video_VideoPlayer(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_experimental_video(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_experimental_video_VideoPlayer_getFileName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_video_VideoPlayer_getURL(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_video_VideoPlayer_play(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_video_VideoPlayer_setKeepAspectRatioEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_video_VideoPlayer_stop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_video_VideoPlayer_setFullScreenEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_video_VideoPlayer_setFileName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_video_VideoPlayer_setURL(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_video_VideoPlayer_isKeepAspectRatioEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_video_VideoPlayer_onPlayEvent(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_video_VideoPlayer_isFullScreenEnabled(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_video_VideoPlayer_isPlaying(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_video_VideoPlayer_seekTo(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_video_VideoPlayer_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_video_VideoPlayer_VideoPlayer(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __cocos2dx_experimental_video_h__
#endif //#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS) && !defined(CC_TARGET_OS_TVOS)
