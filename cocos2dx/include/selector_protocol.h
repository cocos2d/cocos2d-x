/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#ifndef __COCOA_SELECTOR_PROTOCOL_H__
#define __COCOA_SELECTOR_PROTOCOL_H__

#include "ccTypes.h"
#include "CCObject.h"
#include <string>

#ifdef  ENABLE_LUA
#include "../lua_support/CCLuaSrcipt.h"
#endif


namespace   cocos2d {
class CCNode;
class CCEvent;

#ifdef  ENABLE_LUA
enum ccScriptFuncType
{
	ccSEL_Update,
	ccSEL_Tick,
	ccSEL_CallFunc,
	ccSEL_CallFuncN,
	ccSEL_CallFuncND,
	ccSEL_MenuHandler,
	ccSEL_EventHandler,
	ccSEL_Max,
};
class CC_DLL CCScriptSelector
{
public:
	std::string m_scriptFunc[ccSEL_Max];
	inline bool registerScriptSelector(const char* szType, const char* szSeletor)
	{
		if (szType == NULL || szSeletor == NULL || strlen(szType) == 0 || strlen(szSeletor) == 0)
		{
			CCLog("registerScriptSelector input parameter error");
			return false;
		}
		std::string strType[] ={"SEL_Update", "SEL_Tick", "SEL_CallFunc", "SEL_CallFuncN", \
			"SEL_CallFuncND", "SEL_CallFuncO", "SEL_MenuHandler", "SEL_EventHandler"};
		int nType = -1;
		for (int i = 0; i < sizeof(strType); i++)
		{
			if (strcmp(strType[i].c_str(), szType) == 0)
			{
				nType = i;
				break;
			}
		}
		if (nType == -1)
		{
			CCLog("registerScriptSelector function type error");
			return false;
		}
		else
		{
			m_scriptFunc[nType] = szSeletor;
		}
		return true;
	}
};
#endif
#ifdef  ENABLE_LUA
class CC_DLL SelectorProtocol:public CCScriptSelector
#else
class CC_DLL SelectorProtocol
#endif
{
public:
	SelectorProtocol(){};
	virtual void update(ccTime dt) {};
	virtual void tick(ccTime dt){};
	virtual void callfunc(){};
	virtual void callfunc(CCNode* pSender){};
	virtual void callfunc(CCNode* pSender, void* pData){};
	virtual void menuHandler(CCObject* pSender){};
    virtual void eventHandler(CCEvent* pEvent) {};

	// the child call responding retain/release function
	virtual void selectorProtocolRetain(void) {};
	virtual void selectorProtocolRelease(void) {};
};

class CCNode;
typedef void (SelectorProtocol::*SEL_SCHEDULE)(ccTime);

typedef void (SelectorProtocol::*SEL_CallFunc)();
typedef void (SelectorProtocol::*SEL_CallFuncN)(CCNode*);
typedef void (SelectorProtocol::*SEL_CallFuncND)(CCNode*, void*);
typedef void (SelectorProtocol::*SEL_CallFuncO)(CCObject*);
typedef void (SelectorProtocol::*SEL_MenuHandler)(CCObject*);
typedef void (SelectorProtocol::*SEL_EventHandler)(CCEvent*);

//  #define schedule_selector(_SELECTOR) (SEL_SCHEDULE)(*((SEL_SCHEDULE*)(&(&_SELECTOR))) )
//  #define callfunc_selector(_SELECTOR) (SEL_CallFunc)(*((SEL_CallFunc*)(&(&_SELECTOR))) )
//  #define callfuncN_selector(_SELECTOR) (SEL_CallFuncN)(*((SEL_CallFuncN*)(&(&_SELECTOR))) )
//  #define callfuncND_selector(_SELECTOR) (SEL_CallFuncND)(*((SEL_CallFuncND*)(&(&_SELECTOR))) )
//  #define menu_selector(_SELECTOR) (SEL_MenuHandler)(*((SEL_MenuHandler*)(&(&_SELECTOR)))

  #define schedule_selector(_SELECTOR) (SEL_SCHEDULE)(&_SELECTOR)
  #define callfunc_selector(_SELECTOR) (SEL_CallFunc)(&_SELECTOR)
  #define callfuncN_selector(_SELECTOR) (SEL_CallFuncN)(&_SELECTOR)
  #define callfuncND_selector(_SELECTOR) (SEL_CallFuncND)(&_SELECTOR)
  #define callfuncO_selector(_SELECTOR) (SEL_CallFuncO)(&_SELECTOR)
  #define menu_selector(_SELECTOR) (SEL_MenuHandler)(&_SELECTOR)
  #define event_selector(_SELECTOR) (SEL_EventHandler)(&_SELECTOR)


inline void schedule_SCHEDULE(SelectorProtocol* pSel,SEL_SCHEDULE pfn, ccTime cc, std::string & strluafnc) 
{
	if (pSel && pfn)
	{
		(pSel->*pfn)(cc);
	}
	else
	{
#ifdef  ENABLE_LUA
		CCLuaScriptModule::sharedLuaScriptModule()->executeSchedule(strluafnc, cc);
#endif

	}
}

inline void schedule_CallFunc(SelectorProtocol* pSel,SEL_CallFunc pfn, std::string & strluafnc)
{
	if (pSel && pfn)
	{
		(pSel->*pfn)();
	}
	else
	{
#ifdef  ENABLE_LUA
		CCLuaScriptModule::sharedLuaScriptModule()->executeCallFunc(strluafnc);
#endif

	}
}
inline void schedule_CallFuncN(SelectorProtocol* pSel,SEL_CallFuncN pfn, CCNode* pNode, std::string & strluafnc)
{
	if (pSel && pfn)
	{
		(pSel->*pfn)(pNode);
	}
	else
	{
#ifdef  ENABLE_LUA
		CCLuaScriptModule::sharedLuaScriptModule()->executeCallFuncN(strluafnc, pNode);
#endif
	}
}

inline void schedule_CallFuncND(SelectorProtocol* pSel,SEL_CallFuncND pfn, CCNode* pNode, void* pdata, std::string & strluafnc)
{
	if (pSel && pfn)
	{
		(pSel->*pfn)(pNode, pdata);
	}
	else
	{
#ifdef  ENABLE_LUA
		CCLuaScriptModule::sharedLuaScriptModule()->executeCallFuncND(strluafnc, pNode, pdata);
#endif
	}
}

inline void schedule_MenuHandler(SelectorProtocol* pSel,SEL_MenuHandler pfn, CCObject* pobj, std::string & strluafnc)
{
	if (pSel && pfn)
	{
		(pSel->*pfn)(pobj);
	}
	else
	{
#ifdef  ENABLE_LUA
		CCLuaScriptModule::sharedLuaScriptModule()->executeMenuHandler(strluafnc.c_str(), pobj);
#endif
	}
}
inline void schedule_CallFuncO(SelectorProtocol* pSel,SEL_MenuHandler pfn, CCObject* pobj, std::string & strluafnc)
{
	schedule_MenuHandler(pSel, pfn, pobj, strluafnc);
}


inline void schedule_EventHandler(SelectorProtocol* pSel,SEL_EventHandler pfn, CCEvent* pEvent, std::string & strluafnc)
{
	if (pSel && pfn)
	{
		(pSel->*pfn)(pEvent);
	}
	else
	{
#ifdef  ENABLE_LUA
		CCLuaScriptModule::sharedLuaScriptModule()->executeEventHandler(strluafnc, pEvent);
#endif

	}
}



}//namespace   cocos2d 

#endif // __COCOA_SELECTOR_PROTOCOL_H__
