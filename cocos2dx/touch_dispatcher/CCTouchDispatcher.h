/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2009      Valentin Milea

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

#ifndef __TOUCH_DISPATCHER_CCTOUCH_DISPATCHER_H__
#define __TOUCH_DISPATCHER_CCTOUCH_DISPATCHER_H__

#include "CCTouchDelegateProtocol.h"
#include "cocoa/CCObject.h"
#include "cocoa/CCArray.h"

NS_CC_BEGIN

/**
 * @addtogroup input
 * @{
 */


enum {
    CCTOUCHBEGAN,
    CCTOUCHMOVED,
    CCTOUCHENDED,
    CCTOUCHCANCELLED,
    
    ccTouchMax,
};

class Set;
class Event;

struct ccTouchHandlerHelperData {
    // we only use the type
//    void (StandardTouchDelegate::*touchesSel)(Set*, Event*);
//    void (TargetedTouchDelegate::*touchSel)(NSTouch*, Event*);
    int  _type;
};


class CC_DLL EGLTouchDelegate
{
public:
    virtual void touchesBegan(Set* touches, Event* pEvent) = 0;
    virtual void touchesMoved(Set* touches, Event* pEvent) = 0;
    virtual void touchesEnded(Set* touches, Event* pEvent) = 0;
    virtual void touchesCancelled(Set* touches, Event* pEvent) = 0;

    virtual ~EGLTouchDelegate() {}
};

class TouchHandler;
struct _ccCArray;
/** @brief TouchDispatcher.
 Singleton that handles all the touch events.
 The dispatcher dispatches events to the registered TouchHandlers.
 There are 2 different type of touch handlers:
   - Standard Touch Handlers
   - Targeted Touch Handlers
 
 The Standard Touch Handlers work like the CocoaTouch touch handler: a set of touches is passed to the delegate.
 On the other hand, the Targeted Touch Handlers only receive 1 touch at the time, and they can "swallow" touches (avoid the propagation of the event).
 
 Firstly, the dispatcher sends the received touches to the targeted touches.
 These touches can be swallowed by the Targeted Touch Handlers. If there are still remaining touches, then the remaining touches will be sent
 to the Standard Touch Handlers.

 @since v0.8.0
 */
class CC_DLL TouchDispatcher : public Object, public EGLTouchDelegate
{
public:
    ~TouchDispatcher();
    bool init(void);
    TouchDispatcher() 
        : _targetedHandlers(NULL)
        , _standardHandlers(NULL)
        , _handlersToAdd(NULL)
        , _handlersToRemove(NULL)
        
    {}

public:
    /** Whether or not the events are going to be dispatched. Default: true */
    bool isDispatchEvents(void);
    void setDispatchEvents(bool bDispatchEvents);

    /** Adds a standard touch delegate to the dispatcher's list.
     See StandardTouchDelegate description.
     IMPORTANT: The delegate will be retained.
     */
    void addStandardDelegate(TouchDelegate *pDelegate, int nPriority);

    /** Adds a targeted touch delegate to the dispatcher's list.
     See TargetedTouchDelegate description.
     IMPORTANT: The delegate will be retained.
     */
    void addTargetedDelegate(TouchDelegate *pDelegate, int nPriority, bool bSwallowsTouches);

    /** Removes a touch delegate.
     The delegate will be released
     */
    void removeDelegate(TouchDelegate *pDelegate);

    /** Removes all touch delegates, releasing all the delegates */
    void removeAllDelegates(void);

    /** Changes the priority of a previously added delegate. The lower the number,
    the higher the priority */
    void setPriority(int nPriority, TouchDelegate *pDelegate);

    void touches(Set *pTouches, Event *pEvent, unsigned int uIndex);

    virtual void touchesBegan(Set* touches, Event* pEvent);
    virtual void touchesMoved(Set* touches, Event* pEvent);
    virtual void touchesEnded(Set* touches, Event* pEvent);
    virtual void touchesCancelled(Set* touches, Event* pEvent);

public:
    TouchHandler* findHandler(TouchDelegate *pDelegate);
protected:
    void forceRemoveDelegate(TouchDelegate *pDelegate);
    void forceAddHandler(TouchHandler *pHandler, Array* pArray);
    void forceRemoveAllDelegates(void);
    void rearrangeHandlers(Array* pArray);
    TouchHandler* findHandler(Array* pArray, TouchDelegate *pDelegate);

protected:
     Array* _targetedHandlers;
     Array* _standardHandlers;

    bool _locked;
    bool _toAdd;
    bool _toRemove;
     Array* _handlersToAdd;
    struct _ccCArray *_handlersToRemove;
    bool _toQuit;
    bool _dispatchEvents;

    // 4, 1 for each type of event
    struct ccTouchHandlerHelperData _handlerHelperData[ccTouchMax];
};

// end of input group
/// @}

NS_CC_END

#endif // __TOUCH_DISPATCHER_CCTOUCH_DISPATCHER_H__
