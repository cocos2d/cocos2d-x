/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org

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

#ifndef __CCSCRIPT_EVENT_DISPATCHER_H__
#define __CCSCRIPT_EVENT_DISPATCHER_H__

#include <map>
#include <vector>

#include "base/CCRef.h"

using namespace std;

NS_CC_BEGIN

class CC_DLL CCScriptHandlePair
{
public:
    int index;
    int listener;
    int tag;
    int priority;
    bool enabled;

    CCScriptHandlePair(int index_, int listener_, int tag_, int priority_)
    : index(index_)
    , listener(listener_)
    , tag(tag_)
    , priority(priority_)
    , enabled(true)
    {
    }
};

#define NODE_EVENT                  0
#define NODE_ENTER_FRAME_EVENT      1
#define NODE_TOUCH_EVENT            2
#define NODE_TOUCH_CAPTURE_EVENT    3
#define MENU_ITEM_CLICKED_EVENT     4
#define ACCELERATE_EVENT            5
#define KEYPAD_EVENT                6

#define NODE_TOUCH_CAPTURING_PHASE  0
#define NODE_TOUCH_TARGETING_PHASE  1


// listener handle -> listener pair
typedef vector<CCScriptHandlePair> CCScriptEventListenersForEvent;
typedef CCScriptEventListenersForEvent::iterator CCScriptEventListenersForEventIterator;

// event -> CCScriptEventListenersForEvent
typedef map<int, CCScriptEventListenersForEvent> CCScriptEventListenersForDispatcher;
typedef CCScriptEventListenersForDispatcher::iterator CCScriptEventListenersForDispatcherIterator;

class CC_DLL CCScriptEventDispatcher : public Ref
{
public:
    CCScriptEventDispatcher();
    virtual ~CCScriptEventDispatcher();
    int addScriptEventListener(int event, int listener, int tag = 0, int priority = 0);
    void removeScriptEventListener(int handle);
    void removeScriptEventListenersByEvent(int event);
    void removeScriptEventListenersByTag(int tag);
    void removeAllScriptEventListeners();

    bool hasScriptEventListener(int event);
    CCScriptEventListenersForEvent &getScriptEventListenersByEvent(int event) const;
    CCScriptEventListenersForDispatcher &getAllScriptEventListeners() const;

private:
    CCScriptEventListenersForDispatcher *m_scriptEventListeners;

    static int s_nextScriptEventHandleIndex;
    static CCScriptEventListenersForEvent s_emptyListenersForEvent;
    static CCScriptEventListenersForDispatcher s_emptyListeners;

    static bool sortListenerCompare(const CCScriptHandlePair &a, const CCScriptHandlePair &b);
    static bool removeListenerByTag(CCScriptHandlePair &p);
    static int s_removeTag;
};

NS_CC_END

#endif // __CCSCRIPT_EVENT_DISPATCHER_H__
