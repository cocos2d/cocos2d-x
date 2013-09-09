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

    virtual void didAccelerate(Acceleration* accelerationValue);

    // Overrides
    virtual bool ccTouchBegan(Touch *touch, Event *event) override;
    virtual void ccTouchMoved(Touch *touch, Event *event) override;
    virtual void ccTouchEnded(Touch *touch, Event *event) override;
    virtual void ccTouchCancelled(Touch *touch, Event *event) override;
    virtual void ccTouchesBegan(Set *touches, Event *event) override;
    virtual void ccTouchesMoved(Set *touches, Event *event) override;
    virtual void ccTouchesEnded(Set *touches, Event *event) override;
    virtual void ccTouchesCancelled(Set *touches, Event *event) override;

protected:   
    bool _touchEnabled;
    bool _accelerometerEnabled;
    bool _keypadEnabled;
    
private:
     int _touchPriority;
    Touch::DispatchMode _touchMode;
};

NS_CC_EXT_END

#endif  // __FUNDATION__CCCOMPONENT_H__
