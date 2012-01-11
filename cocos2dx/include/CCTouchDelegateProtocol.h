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

#include <string>
#include <map>
#include "CCObject.h"
#include "ccConfig.h"
#include "CCScriptSupport.h"

namespace   cocos2d {

class CCTouch;
class CCEvent;
class CCSet;
class CCTouchDispatcher;
	
class CC_DLL CCTouchDelegate
{
protected:
	std::map<int, std::string> *m_pEventTypeFuncMap;

public:

	CCTouchDelegate() : m_pEventTypeFuncMap(NULL) {}

	virtual ~CCTouchDelegate()
	{
		CC_SAFE_DELETE(m_pEventTypeFuncMap);
	}

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent); return false;};
	// optional

	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}

	// optional
 	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
 	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
 	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
 	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}

	/*
	 * In TouchesTest, class Padle inherits from CCSprite and CCTargetedTouchDelegate.
	 * When it invoke  CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true),
	 * it will crash in CCTouchHandler::initWithDelegate() because of dynamic_cast() on android.
	 * I don't know why, so add these functions for the subclass to invoke it's own retain() and
	 * release().
	 * More detain info please refer issue #926(cocos2d-x).
	 */
	virtual void touchDelegateRetain() = 0;
	virtual void touchDelegateRelease() = 0;

	// functions for script call back
	inline void registerScriptTouchHandler(int eventType, const char* pszScriptFunctionName)
	{
		if (m_pEventTypeFuncMap == NULL)
		{
			m_pEventTypeFuncMap = new std::map<int, std::string>();
		}

		(*m_pEventTypeFuncMap)[eventType] = pszScriptFunctionName;
	}

	inline bool isScriptHandlerExist(int eventType)
	{
		if (m_pEventTypeFuncMap)
		{
			return (*m_pEventTypeFuncMap)[eventType].size() != 0;
		}

		return false;
	}

	inline void excuteScriptTouchHandler(int eventType, CCTouch *pTouch)
	{
		if (m_pEventTypeFuncMap && CCScriptEngineManager::sharedScriptEngineManager()->getScriptEngine())
		{
			CCScriptEngineManager::sharedScriptEngineManager()->getScriptEngine()->executeTouchEvent((*m_pEventTypeFuncMap)[eventType].c_str(),
				                                                                                     pTouch);
		}
		
	}

	inline void excuteScriptTouchesHandler(int eventType, CCSet *pTouches)
	{
		if (m_pEventTypeFuncMap && CCScriptEngineManager::sharedScriptEngineManager()->getScriptEngine())
		{
			CCScriptEngineManager::sharedScriptEngineManager()->getScriptEngine()->executeTouchesEvent((*m_pEventTypeFuncMap)[eventType].c_str(),
				                                                                                        pTouches);
		}
	}
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
 	/** Return YES to claim the touch.
 	 @since v0
	 */
 	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) { CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);return false;};
 
 	// optional
 	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
 	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
 	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
 };
 
/** @brief
 This type of delegate is the same one used by CocoaTouch. You will receive all the events (Began,Moved,Ended,Cancelled).
 @since v0.8
 */
 class CC_DLL CCStandardTouchDelegate : public CCTouchDelegate
 {
 public:
 	// optional
 	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
 	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
 	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
 };

}//namespace   cocos2d 

#endif // __TOUCH_DISPATHCHER_CCTOUCH_DELEGATE_PROTOCOL_H__
