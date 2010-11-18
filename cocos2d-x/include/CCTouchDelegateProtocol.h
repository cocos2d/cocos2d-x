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

#ifndef __TOUCH_DISPATHCHER_CCTOUCH_DELEGATE_PROTOCOL_H__
#define __TOUCH_DISPATHCHER_CCTOUCH_DELEGATE_PROTOCOL_H__

#include "NSObject.h"
#include "ccxCommon.h"

namespace   cocos2d {

typedef enum
{
	ccTouchDelegateStandardBit = 1 << 0,
	ccTouchDelegateTargetedBit = 1 << 1,
	ccTouchDeletateAllBit      = (ccTouchDelegateStandardBit | ccTouchDelegateTargetedBit),
} ccTouchDelegateFlag;

class CCTouch;
class UIEvent;
class NSSet;
class CCX_DLL CCTouchDelegate
{
protected:
	ccTouchDelegateFlag m_eTouchDelegateType;

public:
	inline ccTouchDelegateFlag getTouchDelegateType(void) { return m_eTouchDelegateType; }
	//! call the release() in child(layer or menu)
	virtual void destroy(void) {}
	//! call the retain() in child (layer or menu)
	virtual void keep(void) {}

	virtual bool ccTouchBegan(CCTouch *pTouch, UIEvent *pEvent) { return false;};

	// optional
	virtual void ccTouchMoved(CCTouch *pTouch, UIEvent *pEvent) {}
	virtual void ccTouchEnded(CCTouch *pTouch, UIEvent *pEvent) {}
	virtual void ccTouchCancelled(CCTouch *pTouch, UIEvent *pEvent) {}

	// optional
 	virtual void ccTouchesBegan(NSSet *pTouches, UIEvent *pEvent) {}
 	virtual void ccTouchesMoved(NSSet *pTouches, UIEvent *pEvent) {}
 	virtual void ccTouchesEnded(NSSet *pTouches, UIEvent *pEvent) {}
 	virtual void ccTouchesCancelled(NSSet *pTouches, UIEvent *pEvent) {}
};
/**
 @brief
 Using this type of delegate results in two benefits:
 - 1. You don't need to deal with NSSets, the dispatcher does the job of splitting
 them. You get exactly one UITouch per call.
 - 2. You can *claim* a UITouch by returning YES in ccTouchBegan. Updates of claimed
 touches are sent only to the delegate(s) that claimed them. So if you get a move/
 ended/cancelled update you're sure it's your touch. This frees you from doing a
 lot of checks when doing multi-touch. 

 (The name TargetedTouchDelegate relates to updates "targeting" their specific
 handler, without bothering the other handlers.)
 @since v0.8
 */
 class CCX_DLL CCTargetedTouchDelegate : public CCTouchDelegate
 {
 public:
 	CCTargetedTouchDelegate() { m_eTouchDelegateType = ccTouchDelegateTargetedBit; }
 	/** Return YES to claim the touch.
 	 @since v0
	 */
 	virtual bool ccTouchBegan(CCTouch *pTouch, UIEvent *pEvent) { return false;};
 
 	// optional
 	virtual void ccTouchMoved(CCTouch *pTouch, UIEvent *pEvent) {}
 	virtual void ccTouchEnded(CCTouch *pTouch, UIEvent *pEvent) {}
 	virtual void ccTouchCancelled(CCTouch *pTouch, UIEvent *pEvent) {}
 };
 
/** @brief
 This type of delegate is the same one used by CocoaTouch. You will receive all the events (Began,Moved,Ended,Cancelled).
 @since v0.8
 */
 class CCX_DLL CCStandardTouchDelegate : public CCTouchDelegate
 {
 public:
 	CCStandardTouchDelegate() { m_eTouchDelegateType = ccTouchDelegateTargetedBit; }
 	// optional
 	virtual void ccTouchesBegan(NSSet *pTouches, UIEvent *pEvent) {}
 	virtual void ccTouchesMoved(NSSet *pTouches, UIEvent *pEvent) {}
 	virtual void ccTouchesEnded(NSSet *pTouches, UIEvent *pEvent) {}
 	virtual void ccTouchesCancelled(NSSet *pTouches, UIEvent *pEvent) {}
 };

}//namespace   cocos2d 

#endif // __TOUCH_DISPATHCHER_CCTOUCH_DELEGATE_PROTOCOL_H__
