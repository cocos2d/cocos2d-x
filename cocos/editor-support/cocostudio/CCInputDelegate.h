/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __CC_EXTENTIONS_CCINPUTDELEGATE_H__
#define __CC_EXTENTIONS_CCINPUTDELEGATE_H__

#include "platform/CCPlatformMacros.h"
#include "base/CCTouch.h"
#include "base/CCEvent.h"
#include "base/ccTypes.h"
#include "base/CCEventKeyboard.h"
#include "base/CCEventListener.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocos2d {
    class __Set;
}

namespace cocostudio {

/**
 *  @lua NA
 */
class CC_STUDIO_DLL InputDelegate
{
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    InputDelegate(void);
    /**
     * @js NA
     */
    virtual ~InputDelegate(void);
    
public:
    virtual bool isTouchEnabled() const;
    virtual void setTouchEnabled(bool value);
    virtual bool isAccelerometerEnabled() const;
    virtual void setAccelerometerEnabled(bool value);
    virtual bool isKeypadEnabled() const;
    virtual void setKeypadEnabled(bool value);
    virtual void setTouchMode(cocos2d::Touch::DispatchMode mode);
    virtual cocos2d::Touch::DispatchMode getTouchMode() const;
    virtual void setTouchPriority(int priority);
    virtual int  getTouchPriority() const;
 /** @deprecated Please override onAcceleration */
    /**
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void didAccelerate(cocos2d::Acceleration* accelerationValue) final { CC_UNUSED_PARAM(accelerationValue); };
    // Deprecated touch callbacks.
    /**
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual bool ccTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent); return false;};
    /**
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    /**
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    /**
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    /**
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesBegan(cocos2d::__Set *pTouches, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    /**
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesMoved(cocos2d::__Set *pTouches, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    /**
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesEnded(cocos2d::__Set *pTouches, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    /**
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesCancelled(cocos2d::__Set *pTouches, cocos2d::Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    /**
     * @js NA
     */
    virtual void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event) {};
    /**
     * @js NA
     */
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {};
    /**
     * @js NA
     */
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {};
    /**
     * @js NA
     */
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    /**
     * @js NA
     */
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    /**
     * @js NA
     */
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    /**
     * @js NA
     */
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
    /**
     * @js NA
     */
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    /**
     * @js NA
     */
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    /**
     * @js NA
     */
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    /**
     * @js NA
     */
    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);

protected:   
    bool _touchEnabled;
    cocos2d::EventListener* _touchListener;
    bool _accelerometerEnabled;
    cocos2d::EventListener*  _accelerometerListener;
    bool _keypadEnabled;
    cocos2d::EventListener*  _keyboardListener;
private:
     int _touchPriority;
    cocos2d::Touch::DispatchMode _touchMode;
};

}

#endif  // __CC_EXTENTIONS_CCINPUTDELEGATE_H__
