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

#ifndef __CCMOUSE_EVENT_DELEGATE_H__
#define __CCMOUSE_EVENT_DELEGATE_H__

#include "CCTouch.h"
#include "CCObject.h"

namespace   cocos2d {

class CC_DLL CCMouseEventDelegate
{
public:
    //! call the release() in child layer
    virtual void MouseDestroy() {}
    //! call the retain() in child layer
    virtual void MouseKeep() {}

    //
    // left
    //
    /** called when the "mouseDown" event is received.
    Return YES to avoid propagating the event to other delegates.
    */
    virtual bool ccMouseDown(CCEvent* pEvent) { return false; }

    /** called when the "mouseDragged" event is received.
    Return YES to avoid propagating the event to other delegates.
    */
    virtual bool ccMouseDragged(CCEvent* pEvent) { return false; }

    /** called when the "mouseMoved" event is received.
    Return YES to avoid propagating the event to other delegates.
    By default, "mouseMoved" is disabled. To enable it, send the "setAcceptsMouseMovedEvents:YES" message to the main window.
    */
    virtual bool ccMouseMoved(CCEvent* pEvent) { return false; }

    /** called when the "mouseUp" event is received.
    Return YES to avoid propagating the event to other delegates.
    */
    virtual bool ccMouseUp(CCEvent* pEvent) { return false; }


    //
    // right
    //

    /** called when the "rightMouseDown" event is received.
    Return YES to avoid propagating the event to other delegates.
    */
    virtual bool ccRightMouseDown(CCEvent* pEvent) { return false; }

    /** called when the "rightMouseDragged" event is received.
    Return YES to avoid propagating the event to other delegates.
    */
    virtual bool ccRightMouseDragged(CCEvent* pEvent) { return false; }

    /** called when the "rightMouseUp" event is received.
    Return YES to avoid propagating the event to other delegates.
    */
    virtual bool ccRightMouseUp(CCEvent* pEvent) { return false; }

    //
    // other
    //

    /** called when the "otherMouseDown" event is received.
    Return YES to avoid propagating the event to other delegates.
    */
    virtual bool ccOtherMouseDown(CCEvent* pEvent) { return false; }

    /** called when the "otherMouseDragged" event is received.
    Return YES to avoid propagating the event to other delegates.
    */
    virtual bool ccOtherMouseDragged(CCEvent* pEvent) { return false; }

    /** called when the "otherMouseUp" event is received.
    Return YES to avoid propagating the event to other delegates.
    */
    virtual bool ccOtherMouseUp(CCEvent* pEvent) { return false; }

    //
    // scroll wheel
    //

    /** called when the "scrollWheel" event is received.
    Return YES to avoid propagating the event to other delegates.
    */
    virtual bool ccScrollWheel(CCEvent *pEvent) { return false; }


    //
    // enter / exit
    //

    /** called when the "mouseEntered" event is received.
    Return YES to avoid propagating the event to other delegates.
    */
    virtual void ccMouseEntered(CCEvent *pEvent) {}

    /** called when the "mouseExited" event is received.
    Return YES to avoid propagating the event to other delegates.
    */
    virtual void ccMouseExited(CCEvent *pEvent) {}
};

class CC_DLL CCMouseEventHandle : public CCObject
{
public:
    virtual ~CCMouseEventHandle(void);

    /** delegate */
    CCMouseEventDelegate* getDelegate();
    void setDelegate(CCMouseEventDelegate *pDelegate);

    /** initializes a CCMouseEventHandle with a delegate */
    virtual bool initWithDelegate(CCMouseEventDelegate *pDelegate);

public:
    /** allocates a CCMouseEventHandle with a delegate */
    static CCMouseEventHandle* handlerWithDelegate(CCMouseEventDelegate *pDelegate);

protected:
    CCMouseEventDelegate* m_pDelegate;
};

} //namespace   cocos2d 

#endif // __CCMOUSE_EVENT_DELEGATE_H__
