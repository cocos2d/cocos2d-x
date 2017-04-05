#include "base/ccConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#ifndef __cocos2dx_audioengine_h__
#define __cocos2dx_audioengine_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_cocos2d_experimental_AudioProfile_class;
extern JSObject *jsb_cocos2d_experimental_AudioProfile_prototype;

bool js_cocos2dx_audioengine_AudioProfile_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_audioengine_AudioProfile_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_audioengine_AudioProfile(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_audioengine(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_audioengine_AudioProfile_AudioProfile(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_cocos2d_experimental_AudioEngine_class;
extern JSObject *jsb_cocos2d_experimental_AudioEngine_prototype;

bool js_cocos2dx_audioengine_AudioEngine_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_audioengine_AudioEngine_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_audioengine_AudioEngine(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_audioengine(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_audioengine_AudioEngine_lazyInit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_setCurrentTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_getVolume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_uncache(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_resumeAll(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_stopAll(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_pause(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_end(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_getMaxAudioInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_getCurrentTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_setMaxAudioInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_isLoop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_pauseAll(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_uncacheAll(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_setVolume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_preload(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_play2d(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_getState(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_resume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_stop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_getDuration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_setLoop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_getDefaultProfile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_setFinishCallback(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_audioengine_AudioEngine_getProfile(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __cocos2dx_audioengine_h__
#endif //#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
