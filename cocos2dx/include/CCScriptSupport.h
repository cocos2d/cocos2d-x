/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

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

#ifndef __SCRIPT_SUPPORT_H__
#define __SCRIPT_SUPPORT_H__

#include <string>
#include <vector>
#include <map>

#include "CCCommon.h"
#include "CCTouch.h"
#include "CCSet.h"
#include "CCNode.h"

/*
 * Only one script is support at a time.
 * Should we use more than one script at a time?
 */

NS_CC_BEGIN;

class CC_DLL CCScriptEngineProtocol
{
public:
	CCScriptEngineProtocol();

	// functions for excute touch event
	virtual bool executeTouchEvent(const char *pszFuncName, CCTouch *pTouch) = 0;
	virtual bool executeTouchesEvent(const char *pszFuncName, CCSet *pTouches) = 0;

	// functions for CCCallFuncX
	virtual bool executeCallFunc(const char *pszFuncName) = 0;
	virtual bool executeCallFuncN(const char *pszFuncName, CCNode *pNode) = 0;
	virtual bool executeCallFuncND(const char *pszFuncName, CCNode *pNode, void *pData) = 0;
	virtual bool executeCallFunc0(const char *pszFuncName, CCObject *pObject) = 0;

	// excute a script function without params
	virtual int executeFuction(const char *pszFuncName) = 0;
	// excute a script file
	virtual bool executeScriptFile(const char* pszFileName) = 0;
	// excute script from string
	virtual bool executeString(const char* pszCodes) = 0;

	// execute a schedule function
	virtual bool executeSchedule(const char* pszFuncName, ccTime t) = 0;
    // add a search path  
    virtual bool addSearchPath(const char* pszPath) = 0;
};

/**
 CCScriptEngineManager is a singleton which holds an object instance of CCScriptEngineProtocl
 It helps cocos2d-x and the user code to find back LuaEngine object
 @since v0.99.5-x-0.8.5
 */
class CC_DLL CCScriptEngineManager
{
public:
    static CCScriptEngineManager* sharedScriptEngineManager();
    
	void setScriptEngine(CCScriptEngineProtocol *pScriptEngine);
	CCScriptEngineProtocol* getScriptEngine();
    void removeScriptEngine();
    
private:
    CCScriptEngineManager();
	virtual ~CCScriptEngineManager();
    
	CCScriptEngineProtocol *m_pScriptEngine;
};

NS_CC_END;

#endif // __SCRIPT_SUPPORT_H__
