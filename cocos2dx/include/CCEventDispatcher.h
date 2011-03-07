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

#ifndef __CCEVENT_DISPATCHER_H__
#define __CCEVENT_DISPATCHER_H__

#include "CCMouseEventDelegate.h"
#include "CCKeyboardEventDelegate.h"
#include "ccConfig.h"
#include "selector_protocol.h"

namespace   cocos2d {

struct _listEntry;

/** CCEventDispatcher

This is object is responsible for dispatching the events:
- Mouse events
- Keyboard events
- Touch events

Only available on Mac
*/
class CCEventDispatcher : public CCObject
{
public:
    static CCEventDispatcher* sharedDispatcher();
    bool init(void);

    /** Adds a mouse delegate to the dispatcher's list.
    Delegates with a lower priority value will be called before higher priority values.
    All the events will be propgated to all the delegates, unless the one delegate returns YES.

    IMPORTANT: The delegate will be retained.
    */
    void addMouseDelegate(CCMouseEventDelegate* pDelegate, int priority);

    /** removes a mouse delegate */
    void removeMouseDelegate(CCMouseEventDelegate* pDelegate);

    /** Removes all mouse delegates, releasing all the delegates */
    void removeAllMouseDelegates();

    /** Adds a Keyboard delegate to the dispatcher's list.
    Delegates with a lower priority value will be called before higher priority values.
    All the events will be propgated to all the delegates, unless the one delegate returns YES.

    IMPORTANT: The delegate will be retained.
    */
    void addKeyboardDelegate(CCKeyboardEventDelegate* pDelegate, int priority);

    /** removes a mouse delegate */
    void removeKeyboardDelegate(CCKeyboardEventDelegate* pDelegate);

    /** Removes all mouse delegates, releasing all the delegates */
    void removeAllKeyboardDelegates();

    /** Mouse events */
    // left
    void mouseDown(CCEvent *pEvent);
    void mouseMoved(CCEvent *pEvent);
    void mouseDragged(CCEvent *pEvent);
    void mouseUp(CCEvent *pEvent);

    // right
    void rightMouseDown(CCEvent *pEvent);
    void rightMouseDragged(CCEvent *pEvent);
    void rightMouseUp(CCEvent *pEvent);

    // other
    void otherMouseDown(CCEvent *pEvent);
    void otherMouseDragged(CCEvent *pEvent);
    void otherMouseUp(CCEvent *pEvent);

    // scroll Wheel
    void scrollWheel(CCEvent *pEvent);

    // Mouse enter / exit
    void mouseExited(CCEvent *pEvent);
    void mouseEntered(CCEvent *pEvent);

    /** keyboard events */
    void keyDown(CCEvent *pEvent);
    void keyUp(CCEvent *pEvent);
    void flagsChanged(CCEvent *pEvent);

    void touchesBeganWithEvent(CCEvent *pEvent);
    void touchesMovedWithEvent(CCEvent *pEvent);
    void touchesEndedWithEvent(CCEvent *pEvent);
    void touchesCancelledWithEvent(CCEvent *pEvent);

#if CC_DIRECTOR_MAC_USE_DISPLAY_LINK_THREAD
    void dispatchQueuedEvents();
    void queueEvent(CCEvent* pEvent, SEL_EventHandler selector);
#endif

    CC_PROPERTY(bool, m_bDispatchEvents, IsDispatchEvents)

protected:
    void addDelegate(CCObject* pHandle, int priority, _listEntry** pList);
    void removeAllDelegatesFromList(_listEntry** pList);

protected:
    struct _listEntry* m_pKeyboardDelegates;
    struct _listEntry* m_pMouseDelegates;
};

} //namespace   cocos2d 

#endif // __CCEVENT_DISPATCHER_H__
