#include "base/ccConfig.h"
#ifndef __cocos2dx_network_h__
#define __cocos2dx_network_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_cocos2d_network_Downloader_class;
extern JSObject *jsb_cocos2d_network_Downloader_prototype;

bool js_cocos2dx_network_Downloader_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_network_Downloader_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_network_Downloader(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_network(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_network_Downloader_setOnTaskError(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_network_Downloader_setOnTaskProgress(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_network_Downloader_createDownloadFileTask(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_network_Downloader_setOnFileTaskSuccess(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_network_Downloader_Downloader(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __cocos2dx_network_h__
