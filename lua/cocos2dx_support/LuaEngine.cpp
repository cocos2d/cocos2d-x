/****************************************************************************
Copyright (c) 2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "LuaEngine.h"
#include "LuaEngineImpl.h"

using namespace cocos2d;

LuaEngine::~LuaEngine()
{
	CCLuaScriptModule::purgeSharedLuaScriptModule();
}

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
int LuaEngine::executeFuction(const char *pszFuncName)
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

bool LuaEngine::executeSchedule(const char* pszFuncName, ccTime t)
{
	return CCLuaScriptModule::sharedLuaScriptModule()->executeSchedule(pszFuncName, t);
}

bool LuaEngine::addSearchPath(const char* pszPath)
{
	return CCLuaScriptModule::sharedLuaScriptModule()->addSearchPath(pszPath);
}

