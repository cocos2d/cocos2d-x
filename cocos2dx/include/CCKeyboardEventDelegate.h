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

#ifndef __CCKEYBOARD_EVENT_DELEGATE_H__
#define __CCKEYBOARD_EVENT_DELEGATE_H__

#include "CCTouch.h"
#include "CCObject.h"

namespace cocos2d {

class CC_DLL CCKeyboardEventDelegate
{
public:
    //! call the release() in child layer
    virtual void KeyboardDestroy() {}
    //! call the retain() in child layer
    virtual void KeyboardKeep() {}

    /** called when the "keyUp" event is received.
    Return YES to avoid propagating the event to other delegates.
    */
    virtual bool ccKeyUp(CCEvent* pEvent) { return false; }

    /** called when the "keyDown" event is received.
    Return YES to avoid propagating the event to other delegates.
    */
    virtual bool ccKeyDown(CCEvent* pEvent) { return false; }

    /** called when the "flagsChanged" event is received.
    Return YES to avoid propagating the event to other delegates.
    */
    virtual bool ccFlagsChanged(CCEvent* pEvent) { return false; }
};

class CC_DLL CCKeyboardEventHandle : public CCObject
{
public:
    virtual ~CCKeyboardEventHandle(void);

    /** delegate */
    CCKeyboardEventDelegate* getDelegate();
    void setDelegate(CCKeyboardEventDelegate *pDelegate);

    /** initializes a CCKeyboardEventHandle with a delegate */
    virtual bool initWithDelegate(CCKeyboardEventDelegate *pDelegate);

public:
    /** allocates a CCKeyboardEventHandle with a delegate */
    static CCKeyboardEventHandle* handlerWithDelegate(CCKeyboardEventDelegate *pDelegate);

protected:
    CCKeyboardEventDelegate* m_pDelegate;
};

}

#endif
