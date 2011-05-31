/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2009      Valentin Milea

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

#ifndef __TOUCH_DISPATHCHER_CCTOUCH_DELEGATE_PROTOCOL_H__
#define __TOUCH_DISPATHCHER_CCTOUCH_DELEGATE_PROTOCOL_H__

#include "CCObject.h"
#include "ccConfig.h"
#if CC_ENABLE_LUA
#include "CCMutableDictionary.h"
#include "CCString.h"
#include "../Ndscript/CCLuaSrcipt.h"
#endif
namespace   cocos2d {

typedef enum
{
	ccTouchDelegateStandardBit = 1 << 0,
	ccTouchDelegateTargetedBit = 1 << 1,
	ccTouchDelegateAllBit      = (ccTouchDelegateStandardBit | ccTouchDelegateTargetedBit),
} ccTouchDelegateFlag;

class CCTouch;
class CCEvent;
class CCSet;
class CCTouchDispatcher;
	
class CC_DLL CCTouchDelegate
{
protected:
	ccTouchDelegateFlag m_eTouchDelegateType;
#if CC_ENABLE_LUA
	CCMutableDictionary<int, cocos2d::CCString*> *m_pEventDictionary;
#endif
public:
	friend class CCTouchDispatcher; // only CCTouchDispatcher & children can change m_eTouchDelegateType
	inline ccTouchDelegateFlag getTouchDelegateType(void) { return m_eTouchDelegateType; }
	
	//! call the release() in child(layer or menu)
	virtual void destroy(void) {}
	//! call the retain() in child (layer or menu)
	virtual void keep(void) {}

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) { return false;};
	// optional

	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {}
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {}
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {}

	// optional
 	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {}
 	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent) {}
 	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {}
 	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent) {}

#if CC_ENABLE_LUA
	//use for lua register event 
	/*
	szEventName must be one of follow value 
	{ "ccTouchBegan" "ccTouchMoved" "ccTouchEnded" "ccTouchCancelled" }
	*/
	

	void registerLuaTouchEvent(const char* szEventName, const char* fn)
	{
		if (szEventName == NULL || strlen(szEventName) == 0 || fn == NULL || strlen(fn) == 0)
		{
			CCLog("registerEvent input parameter error ");
			return ;
		}

		std::string strEventType[] = {"ccTouchBegan", "ccTouchMoved", "ccTouchEnded", "ccTouchCancelled", 
		"ccMulTouchBegan", "ccMulTouchMoved", "ccMulTouchEnded", "ccMulTouchCancelled"};
		int nSize = sizeof(strEventType);
		int nType = -1;
		for(int i = 0; i < nSize; i++)
		{
			if (strcmp(strEventType[i].c_str(), szEventName) == 0)
			{
				nType = i;
				break;
			}
		}
		if(nType != -1)
		{
			if (m_pEventDictionary == NULL)
			{
				m_pEventDictionary = new CCMutableDictionary<int, cocos2d::CCString*>();
			}

			if (m_pEventDictionary->objectForKey(nType) == NULL)
			{
				CCString *pStr = new CCString(fn);
				m_pEventDictionary->setObject(pStr, nType);
			}
			else
			{
				CCLog("registerEvent %s already exist", szEventName);
			}
		}
	}
	CCString* getLuaEvent(int nType)
	{
		if (m_pEventDictionary == NULL)
		{
			return NULL;
		}
		CCString *pfn = NULL;
		pfn = m_pEventDictionary->objectForKey(nType);
		return pfn;

	}
	void excuteLuaTouchEvent(CCString* pLuafn, CCTouch *pTouch)
	{
		if (pLuafn)
		{
			CCLuaScriptModule::sharedLuaScriptModule()->executeTouch(pLuafn->m_sString.c_str(), pTouch);
		}
	}

	void excuteLuaTouchesEvent(CCString* pLuafn, CCSet *pTouches)
	{
		if (pLuafn)
		{
			CCLuaScriptModule::sharedLuaScriptModule()->executeTouchesEvent(pLuafn->m_sString.c_str(), pTouches);
		}
	}
	CCTouchDelegate(){m_pEventDictionary = NULL;}
	~CCTouchDelegate()
	{
		if (m_pEventDictionary)
		{
			delete m_pEventDictionary;
			m_pEventDictionary = NULL;
		}

	}
#endif
};
/**
 @brief
 Using this type of delegate results in two benefits:
 - 1. You don't need to deal with CCSets, the dispatcher does the job of splitting
 them. You get exactly one UITouch per call.
 - 2. You can *claim* a UITouch by returning YES in ccTouchBegan. Updates of claimed
 touches are sent only to the delegate(s) that claimed them. So if you get a move/
 ended/cancelled update you're sure it's your touch. This frees you from doing a
 lot of checks when doing multi-touch. 

 (The name TargetedTouchDelegate relates to updates "targeting" their specific
 handler, without bothering the other handlers.)
 @since v0.8
 */
 class CC_DLL CCTargetedTouchDelegate : public CCTouchDelegate
 {
 public:
 	CCTargetedTouchDelegate() { m_eTouchDelegateType = ccTouchDelegateTargetedBit; }
 	/** Return YES to claim the touch.
 	 @since v0
	 */
 	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) { return false;};
 
 	// optional
 	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {}
 	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {}
 	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {}
 };
 
/** @brief
 This type of delegate is the same one used by CocoaTouch. You will receive all the events (Began,Moved,Ended,Cancelled).
 @since v0.8
 */
 class CC_DLL CCStandardTouchDelegate : public CCTouchDelegate
 {
 public:
 	CCStandardTouchDelegate() { m_eTouchDelegateType = ccTouchDelegateStandardBit; }
 	// optional
 	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {}
 	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent) {}
 	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {}
 	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent) {}
 };

}//namespace   cocos2d 

#endif // __TOUCH_DISPATHCHER_CCTOUCH_DELEGATE_PROTOCOL_H__
