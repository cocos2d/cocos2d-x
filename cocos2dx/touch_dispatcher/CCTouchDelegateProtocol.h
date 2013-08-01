/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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

#include "cocoa/CCObject.h"
#include "ccConfig.h"

NS_CC_BEGIN

class Touch;
class Event;
class Set;
class TouchDispatcher;

/**
 * @addtogroup input
 * @{
 */

class CC_DLL TouchDelegate
{
public:

    TouchDelegate() {}

    virtual ~TouchDelegate()
    {
    }

    virtual bool ccTouchBegan(Touch *pTouch, Event *pEvent) {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent); return false;};
    // optional

    virtual void ccTouchMoved(Touch *pTouch, Event *pEvent) {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    virtual void ccTouchEnded(Touch *pTouch, Event *pEvent) {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    virtual void ccTouchCancelled(Touch *pTouch, Event *pEvent) {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}

    // optional
     virtual void ccTouchesBegan(Set *pTouches, Event *pEvent) {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
     virtual void ccTouchesMoved(Set *pTouches, Event *pEvent) {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
     virtual void ccTouchesEnded(Set *pTouches, Event *pEvent) {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
     virtual void ccTouchesCancelled(Set *pTouches, Event *pEvent) {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}

};
/**
 @brief
 Using this type of delegate results in two benefits:
 - 1. You don't need to deal with Sets, the dispatcher does the job of splitting
 them. You get exactly one UITouch per call.
 - 2. You can *claim* a UITouch by returning true in ccTouchBegan. Updates of claimed
 touches are sent only to the delegate(s) that claimed them. So if you get a move/
 ended/canceled update you're sure it's your touch. This frees you from doing a
 lot of checks when doing multi-touch. 

 (The name TargetedTouchDelegate relates to updates "targeting" their specific
 handler, without bothering the other handlers.)
 @since v0.8
 */
 class CC_DLL TargetedTouchDelegate : public TouchDelegate
 {
 public:
     /** Return true to claim the touch.
      @since v0
     */
     virtual bool ccTouchBegan(Touch *pTouch, Event *pEvent) { CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);return false;};
 
     // optional
     virtual void ccTouchMoved(Touch *pTouch, Event *pEvent) {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
     virtual void ccTouchEnded(Touch *pTouch, Event *pEvent) {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
     virtual void ccTouchCancelled(Touch *pTouch, Event *pEvent) {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
 };
 
/** @brief
 This type of delegate is the same one used by CocoaTouch. You will receive all the events (Began,Moved,Ended,Canceled).
 @since v0.8
 */
 class CC_DLL StandardTouchDelegate : public TouchDelegate
 {
 public:
     // optional
     virtual void ccTouchesBegan(Set *pTouches, Event *pEvent) {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
     virtual void ccTouchesMoved(Set *pTouches, Event *pEvent) {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
     virtual void ccTouchesEnded(Set *pTouches, Event *pEvent) {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    virtual void ccTouchesCancelled(Set *pTouches, Event *pEvent) {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
 };

// end of input group
/// @}

NS_CC_END

#endif // __TOUCH_DISPATHCHER_CCTOUCH_DELEGATE_PROTOCOL_H__
