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
class CCTouch;
class UIEvent;

class CCX_DLL CCTouchDelegate : virtual public NSObject
{
public:
	// for RTTI support
	virtual void v() {};
};

class CCX_DLL CCTargetedTouchDelegate : public CCTouchDelegate
{
public:
	/** Return YES to claim the touch.
	 @since v0.8
	 */
	virtual bool ccTouchBegan(CCTouch *pTouch, UIEvent *pEvent) { return false;};

	// optional
	virtual void ccTouchMoved(CCTouch *pTouch, UIEvent *pEvent) {}
	virtual void ccTouchEnded(CCTouch *pTouch, UIEvent *pEvent) {}
	virtual void ccTouchCancelled(CCTouch *pTouch, UIEvent *pEvent) {}
};

/**
 CCStandardTouchDelegate.
 
 This type of delegate is the same one used by CocoaTouch. You will receive all the events (Began,Moved,Ended,Cancelled).
 @since v0.8
*/

class NSSet;
class CCX_DLL CCStandardTouchDelegate : public CCTouchDelegate
{
public:
	// optional
	virtual void ccTouchesBegan(NSSet *pTouches, UIEvent *pEvent) {}
	virtual void ccTouchesMoved(NSSet *pTouches, UIEvent *pEvent) {}
	virtual void ccTouchesEnded(NSSet *pTouches, UIEvent *pEvent) {}
	virtual void ccTouchesCancelled(NSSet *pTouches, UIEvent *pEvent) {}
};
}//namespace   cocos2d 

#endif // __TOUCH_DISPATHCHER_CCTOUCH_DELEGATE_PROTOCOL_H__
