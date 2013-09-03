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
    InputDelegate(void);
    virtual ~InputDelegate(void);
    
public:
    virtual bool isTouchEnabled() const;
    virtual void setTouchEnabled(bool value);
    
    virtual bool isAccelerometerEnabled() const;
    virtual void setAccelerometerEnabled(bool value);

    virtual bool isKeypadEnabled() const;
    virtual void setKeypadEnabled(bool value);
    
    virtual void setTouchMode(Touch::DispatchMode mode);
    virtual Touch::DispatchMode getTouchMode() const;
    
    virtual void setTouchPriority(int priority);
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

    virtual void onKeyPressed(KeyboardEvent::KeyCode keyCode, Event* event) {};
    virtual void onKeyReleased(KeyboardEvent::KeyCode keyCode, Event* event) {};
    
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
    int  _touchListenerId;
    bool _accelerometerEnabled;
    int  _accelerometerListenerId;
    bool _keypadEnabled;
    int  _keyboardListenerId;
private:
     int _touchPriority;
    Touch::DispatchMode _touchMode;
};

NS_CC_EXT_END

#endif  // __FUNDATION__CCCOMPONENT_H__
