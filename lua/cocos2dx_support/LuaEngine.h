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

#else
    #define LUA_DLL

#endif  // CC_PLATFORM_WIN32

class LUA_DLL LuaEngine : public cocos2d::CCScriptEngineProtocol
{
public:

	// functions for excute touch event
	virtual bool executeTouchEvent(const char *pszFuncName, cocos2d::CCTouch *pTouch);
	virtual bool executeTouchesEvent(const char *pszFuncName, cocos2d::CCSet *pTouches);

	// functions for CCCallFuncX
	virtual bool executeCallFunc(const char *pszFuncName);
	virtual bool executeCallFuncN(const char *pszFuncName, cocos2d::CCNode *pNode);
	virtual bool executeCallFuncND(const char *pszFuncName, cocos2d::CCNode *pNode, void *pData);
	virtual bool executeCallFunc0(const char *pszFuncName, cocos2d::CCObject *pObject);

	// excute a script function without params
	virtual int executeFuction(const char *pszFuncName);
	// excute a script file
	virtual bool executeScriptFile(const char* pszFileName);
	// excute script from string
	virtual bool executeString(const char* pszCodes);

	// execute a schedule function
	virtual bool executeSchedule(const char* pszFuncName, cocos2d::ccTime t);
};

#endif // __LUA_ENGINE_H__
