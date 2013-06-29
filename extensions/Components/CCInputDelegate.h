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

class InputDelegate : public TouchDelegate, public KeypadDelegate
{
protected:
    InputDelegate(void);
    virtual ~InputDelegate(void);
    
public:
    virtual bool ccTouchBegan(Touch *pTouch, Event *pEvent);
    virtual void ccTouchMoved(Touch *pTouch, Event *pEvent);
    virtual void ccTouchEnded(Touch *pTouch, Event *pEvent);
    virtual void ccTouchCancelled(Touch *pTouch, Event *pEvent);

    virtual void ccTouchesBegan(Set *pTouches, Event *pEvent);
    virtual void ccTouchesMoved(Set *pTouches, Event *pEvent);
    virtual void ccTouchesEnded(Set *pTouches, Event *pEvent);
    virtual void ccTouchesCancelled(Set *pTouches, Event *pEvent);
    
    virtual void didAccelerate(Acceleration* pAccelerationValue);
public:
    virtual bool isTouchEnabled();
    virtual void setTouchEnabled(bool value);
    
    virtual bool isAccelerometerEnabled();
    virtual void setAccelerometerEnabled(bool value);

    virtual bool isKeypadEnabled();
    virtual void setKeypadEnabled(bool value);
    
    virtual void setTouchMode(ccTouchesMode mode);
    virtual int getTouchMode();
    
    virtual void setTouchPriority(int priority);
    virtual int  getTouchPriority();
    
protected:   
    bool _touchEnabled;
    bool _accelerometerEnabled;
    bool _keypadEnabled;
    
private:
     int _touchPriority;
     ccTouchesMode _touchMode;
};

NS_CC_EXT_END

#endif  // __FUNDATION__CCCOMPONENT_H__
