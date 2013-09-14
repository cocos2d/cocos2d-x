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
    /**
     * @js NA
     * @lua NA
     */
    virtual void didAccelerate(Acceleration* accelerationValue);

    // Overrides
    /**
     * @js NA
     * @lua NA
     */
    virtual bool ccTouchBegan(Touch *touch, Event *event) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void ccTouchMoved(Touch *touch, Event *event) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void ccTouchEnded(Touch *touch, Event *event) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void ccTouchCancelled(Touch *touch, Event *event) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void ccTouchesBegan(Set *touches, Event *event) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void ccTouchesMoved(Set *touches, Event *event) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void ccTouchesEnded(Set *touches, Event *event) override;
    /**
     * @js NA
     * @lua NA
     */
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
