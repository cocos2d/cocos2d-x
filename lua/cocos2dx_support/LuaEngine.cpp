#include "LuaEngine.h"
#include "CCLuaSrcipt.h"

using namespace cocos2d;

// functions for excute touch event
bool LuaEngine::excuteTouchEvent(const char *pszFuncName, CCTouch *pTouch)
{
	return CCLuaScriptModule::sharedLuaScriptModule()->executeTouch(pszFuncName, pTouch);
}

bool LuaEngine::excuteTouchesEvent(const char *pszFuncName, CCSet *pTouches)
{
	return CCLuaScriptModule::sharedLuaScriptModule()->executeTouchesEvent(pszFuncName, pTouches);
}

// functions for CCCallFuncX
bool LuaEngine::excuteCallFunc(const char *pszFuncName)
{
	return CCLuaScriptModule::sharedLuaScriptModule()->executeCallFunc(pszFuncName);
}

bool LuaEngine::excuteCallFuncN(const char *pszFuncName, CCNode *pNode)
{
	return CCLuaScriptModule::sharedLuaScriptModule()->executeCallFuncN(pszFuncName, pNode);
}

bool LuaEngine::excuteCallFuncND(const char *pszFuncName, CCNode *pNode, void *pData)
{
	return CCLuaScriptModule::sharedLuaScriptModule()->executeCallFuncND(pszFuncName, pNode, pData);
}

bool LuaEngine::excuteCallFunc0(const char *pszFuncName, CCObject *pObject)
{
	// use executeCallFuncN() to implement it
	return CCLuaScriptModule::sharedLuaScriptModule()->executeCallFuncO(pszFuncName, pObject);
}

// excute a script function without params
bool LuaEngine::excuteFuction(const char *pszFuncName)
{
	return CCLuaScriptModule::sharedLuaScriptModule()->executeScriptGlobal(pszFuncName);
}

// excute a script file
bool LuaEngine::excuteScriptFile(const char* pszFileName)
{
	return CCLuaScriptModule::sharedLuaScriptModule()->executeScriptFile(pszFileName);
}

// excute script from string
bool LuaEngine::excuteString(const char* pszCodes)
{
	return CCLuaScriptModule::sharedLuaScriptModule()->executeString(pszCodes);
}
