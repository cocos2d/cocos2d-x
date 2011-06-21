#include "LuaEngine.h"
#include "LuaEngineImpl.h"

using namespace cocos2d;

// functions for excute touch event
bool LuaEngine::executeTouchEvent(const char *pszFuncName, CCTouch *pTouch)
{
	return CCLuaScriptModule::sharedLuaScriptModule()->executeTouch(pszFuncName, pTouch);
}

bool LuaEngine::executeTouchesEvent(const char *pszFuncName, CCSet *pTouches)
{
	return CCLuaScriptModule::sharedLuaScriptModule()->executeTouchesEvent(pszFuncName, pTouches);
}

// functions for CCCallFuncX
bool LuaEngine::executeCallFunc(const char *pszFuncName)
{
	return CCLuaScriptModule::sharedLuaScriptModule()->executeCallFunc(pszFuncName);
}

bool LuaEngine::executeCallFuncN(const char *pszFuncName, CCNode *pNode)
{
	return CCLuaScriptModule::sharedLuaScriptModule()->executeCallFuncN(pszFuncName, pNode);
}

bool LuaEngine::executeCallFuncND(const char *pszFuncName, CCNode *pNode, void *pData)
{
	return CCLuaScriptModule::sharedLuaScriptModule()->executeCallFuncND(pszFuncName, pNode, pData);
}

bool LuaEngine::executeCallFunc0(const char *pszFuncName, CCObject *pObject)
{
	// use executeCallFuncN() to implement it
	return CCLuaScriptModule::sharedLuaScriptModule()->executeCallFuncO(pszFuncName, pObject);
}

// excute a script function without params
bool LuaEngine::executeFuction(const char *pszFuncName)
{
	return CCLuaScriptModule::sharedLuaScriptModule()->executeScriptGlobal(pszFuncName);
}

// excute a script file
bool LuaEngine::executeScriptFile(const char* pszFileName)
{
	return CCLuaScriptModule::sharedLuaScriptModule()->executeScriptFile(pszFileName);
}

// excute script from string
bool LuaEngine::executeString(const char* pszCodes)
{
	return CCLuaScriptModule::sharedLuaScriptModule()->executeString(pszCodes);
}
