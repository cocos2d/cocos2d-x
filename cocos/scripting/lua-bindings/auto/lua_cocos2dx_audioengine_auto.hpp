#include "base/ccConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
#ifndef __cocos2dx_audioengine_h__
#define __cocos2dx_audioengine_h__

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

int register_all_cocos2dx_audioengine(lua_State* tolua_S);































#endif // __cocos2dx_audioengine_h__
#endif //#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
