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
};

class CC_DLL CCScriptEngineManager
{
public:
	CCScriptEngineManager();
	virtual ~CCScriptEngineManager();

	void registerScriptEngine(CCScriptEngineProtocol *pScriptEngine);
	CCScriptEngineProtocol* getScriptEngine();

	static CCScriptEngineManager* sharedScriptEngineManager();

private:
	CCScriptEngineProtocol *m_pScriptEngine;
};

NS_CC_END;

#endif // __SCRIPT_SUPPORT_H__
