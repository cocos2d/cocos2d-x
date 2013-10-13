/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "cocos2d.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN

class InputDelegate
{
protected:
    /**
     * @js NA
     * @lua NA
     */
    InputDelegate(void);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~InputDelegate(void);
    
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual bool isTouchEnabled() const;
    /**
     * @js NA
     * @lua NA
     */
    virtual void setTouchEnabled(bool value);
    /**
     * @js NA
     * @lua NA
     */
    virtual bool isAccelerometerEnabled() const;
    /**
     * @js NA
     * @lua NA
     */
    virtual void setAccelerometerEnabled(bool value);
    /**
     * @js NA
     * @lua NA
     */
    virtual bool isKeypadEnabled() const;
    /**
     * @js NA
     * @lua NA
     */
    virtual void setKeypadEnabled(bool value);
    /**
     * @js NA
     * @lua NA
     */
    virtual void setTouchMode(Touch::DispatchMode mode);
    /**
     * @js NA
     * @lua NA
     */
    virtual Touch::DispatchMode getTouchMode() const;
    /**
     * @js NA
     * @lua NA
     */
    virtual void setTouchPriority(int priority);
    /**
     * @js NA
     * @lua NA
     */
    virtual int  getTouchPriority() const;
 /** @deprecated Please override onAcceleration */
    CC_DEPRECATED_ATTRIBUTE virtual void didAccelerate(Acceleration* accelerationValue) final { CC_UNUSED_PARAM(accelerationValue); };
    // Deprecated touch callbacks.
    CC_DEPRECATED_ATTRIBUTE virtual bool ccTouchBegan(Touch *pTouch, Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent); return false;};
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchMoved(Touch *pTouch, Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchEnded(Touch *pTouch, Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchCancelled(Touch *pTouch, Event *pEvent) final {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesBegan(Set *pTouches, Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesMoved(Set *pTouches, Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesEnded(Set *pTouches, Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    CC_DEPRECATED_ATTRIBUTE virtual void ccTouchesCancelled(Set *pTouches, Event *pEvent) final {CC_UNUSED_PARAM(pTouches); CC_UNUSED_PARAM(pEvent);}
    
    virtual void onAcceleration(Acceleration* acc, Event* event) {};

    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {};
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {};
    
    virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchMoved(Touch *touch, Event *event);
    virtual void onTouchEnded(Touch *touch, Event *event);
    virtual void onTouchCancelled(Touch *touch, Event *event);
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *event);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *event);
    virtual void onTouchesCancelled(const std::vector<Touch*>& touches, Event *event);

protected:   
    bool _touchEnabled;
    EventListener* _touchListener;
    bool _accelerometerEnabled;
    EventListener*  _accelerometerListener;
    bool _keypadEnabled;
    EventListener*  _keyboardListener;
private:
     int _touchPriority;
    Touch::DispatchMode _touchMode;
};

NS_CC_EXT_END

#endif  // __FUNDATION__CCCOMPONENT_H__
