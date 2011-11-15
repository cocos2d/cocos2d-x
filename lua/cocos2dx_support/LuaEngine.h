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
#ifndef __LUA_ENGINE_H__
#define __LUA_ENGINE_H__

#include "CCScriptSupport.h"
#include "cocos2d.h"

class LuaEngine : public cocos2d::CCScriptEngineProtocol
{
public:
	virtual ~LuaEngine();

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
    // add a search path  
    virtual bool addSearchPath(const char* pszPath);
};

#endif // __LUA_ENGINE_H__
