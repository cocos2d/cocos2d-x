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

#include "base/CCRef.h"
#include "deprecated/CCArray.h"
#include "CCTouchDelegateProtocol.h"

NS_CC_BEGIN

/**
 * @addtogroup input
 * @{
 */

typedef enum
{
    ccTouchSelectorBeganBit = 1 << 0,
    ccTouchSelectorMovedBit = 1 << 1,
    ccTouchSelectorEndedBit = 1 << 2,
    ccTouchSelectorCancelledBit = 1 << 3,
    ccTouchSelectorAllBits = ( ccTouchSelectorBeganBit | ccTouchSelectorMovedBit | ccTouchSelectorEndedBit | ccTouchSelectorCancelledBit),
} ccTouchSelectorFlag;



#define CCTOUCHBEGAN        0
#define CCTOUCHMOVED        1
#define CCTOUCHENDED        2
#define CCTOUCHCANCELLED    3
#define CCTOUCHADDED        4
#define CCTOUCHREMOVED      5
#define ccTouchMax          6

class __Set;
class Event;

struct ccTouchHandlerHelperData {
    // we only use the type
//    void (StandardTouchDelegate::*touchesSel)(__Set*, Event*);
//    void (TargetedTouchDelegate::*touchSel)(NSTouch*, Event*);
    int  m_type;
};

/**
 * @js NA
 */
class CC_DLL EGLTouchDelegate
{
public:
    /**
     * @lua NA
     */
    virtual void touchesBegan(__Set* touches, Event* pEvent) = 0;
    /**
     * @lua NA
     */
    virtual void touchesMoved(__Set* touches, Event* pEvent) = 0;
    /**
     * @lua NA
     */
    virtual void touchesEnded(__Set* touches, Event* pEvent) = 0;
    /**
     * @lua NA
     */
    virtual void touchesCancelled(__Set* touches, Event* pEvent) = 0;
    /**
     * @lua NA
     */
    virtual ~EGLTouchDelegate() {}
};

class CCTouchHandler;
struct _ccCArray;
/** @brief CCTouchDispatcher.
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
 @js NA
 */
class CC_DLL CCTouchDispatcher : public Ref, public EGLTouchDelegate
{
public:
    /**
     * @lua NA
     */
    ~CCTouchDispatcher();
    /**
     * @lua NA
     */
    bool init(void);
    /**
     * @lua NA
     */
    CCTouchDispatcher()
        : m_pTargetedHandlers(NULL)
        , m_pStandardHandlers(NULL)
        , m_pHandlersToAdd(NULL)
        , m_pHandlersToRemove(NULL)
        
    {}

public:
    /** Whether or not the events are going to be dispatched. Default: true */
    bool isDispatchEvents(void);
    void setDispatchEvents(bool bDispatchEvents);

    /** Adds a standard touch delegate to the dispatcher's list.
     * See StandardTouchDelegate description.
     * IMPORTANT: The delegate will be retained.
     * @lua NA
     */
    void addStandardDelegate(CCTouchDelegate *pDelegate, int nPriority);

    /** Adds a targeted touch delegate to the dispatcher's list.
     * See TargetedTouchDelegate description.
     * IMPORTANT: The delegate will be retained.
     * @lua NA
     */
    void addTargetedDelegate(CCTouchDelegate *pDelegate, int nPriority, bool bSwallowsTouches);

    /** Removes a touch delegate.
     * The delegate will be released
     * @lua NA
     */
    void removeDelegate(CCTouchDelegate *pDelegate);

    /** Removes all touch delegates, releasing all the delegates 
     * @lua NA
     */
    void removeAllDelegates(void);

    /** Changes the priority of a previously added delegate. The lower the number,
     * the higher the priority 
     * @lua NA
     */
    void setPriority(int nPriority, CCTouchDelegate *pDelegate);
    /**
     * @lua NA
     */
    void touches(__Set *pTouches, Event *pEvent, unsigned int uIndex);
    /**
     * @lua NA
     */
    virtual void touchesBegan(__Set* touches, Event* pEvent);
    /**
     * @lua NA
     */
    virtual void touchesMoved(__Set* touches, Event* pEvent);
    /**
     * @lua NA
     */
    virtual void touchesEnded(__Set* touches, Event* pEvent);
    /**
     * @lua NA
     */
    virtual void touchesCancelled(__Set* touches, Event* pEvent);

public:
    /**
     * @lua NA
     */
    CCTouchHandler* findHandler(CCTouchDelegate *pDelegate);
protected:
    void forceRemoveDelegate(CCTouchDelegate *pDelegate);
    void forceAddHandler(CCTouchHandler *pHandler, __Array* pArray);
    void forceRemoveAllDelegates(void);
    void rearrangeHandlers(__Array* pArray);
    CCTouchHandler* findHandler(__Array* pArray, CCTouchDelegate *pDelegate);

protected:
     __Array* m_pTargetedHandlers;
     __Array* m_pStandardHandlers;

    bool m_bLocked;
    bool m_bToAdd;
    bool m_bToRemove;
    __Array* m_pHandlersToAdd;
    struct _ccCArray *m_pHandlersToRemove;
    bool m_bToQuit;
    bool m_bDispatchEvents;

    // 4, 1 for each type of event
    struct ccTouchHandlerHelperData m_sHandlerHelperData[ccTouchMax];
};

// end of input group
/// @}

NS_CC_END

#endif // __TOUCH_DISPATCHER_CCTOUCH_DISPATCHER_H__
