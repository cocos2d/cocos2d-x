#ifndef __LUA_ENGINE_H__
#define __LUA_ENGINE_H__

#include "CCScriptSupport.h"
#include "cocos2d.h"

#ifdef _WINDOWS

#undef LUA_DLL
#if defined(_USRDLL)
#define LUA_DLL     __declspec(dllexport)
#else 		/* use a DLL library */
#define LUA_DLL     __declspec(dllimport)
#endif

#endif  // CC_PLATFORM_WIN32

class LUA_DLL LuaEngine : public cocos2d::CCScriptEngineProtocol
{
public:

	// functions for excute touch event
	virtual bool excuteTouchEvent(const char *pszFuncName, cocos2d::CCTouch *pTouch);
	virtual bool excuteTouchesEvent(const char *pszFuncName, cocos2d::CCSet *pTouches);

	// functions for CCCallFuncX
	virtual bool excuteCallFunc(const char *pszFuncName);
	virtual bool excuteCallFuncN(const char *pszFuncName, cocos2d::CCNode *pNode);
	virtual bool excuteCallFuncND(const char *pszFuncName, cocos2d::CCNode *pNode, void *pData);
	virtual bool excuteCallFunc0(const char *pszFuncName, cocos2d::CCObject *pObject);

	// excute a script function without params
	virtual bool excuteFuction(const char *pszFuncName);
	// excute a script file
	virtual bool excuteScriptFile(const char* pszFileName);
	// excute script from string
	virtual bool excuteString(const char* pszCodes);
};

#endif // __LUA_ENGINE_H__
