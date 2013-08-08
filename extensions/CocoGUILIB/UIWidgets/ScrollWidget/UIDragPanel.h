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

#ifndef __TestCpp__UIDragPanel__
#define __TestCpp__UIDragPanel__

#include "../UIPanel.h"
#include "UIScrollDelegate.h"

NS_CC_EXT_BEGIN

class UIWrapPanel;

/*
enum DRAGPANEL_DIR
{
    DRAGPANEL_DIR_NONE,
    DRAGPANEL_DIR_BOTH,
    DRAGPANEL_DIR_VERTICAL,
    DRAGPANEL_DIR_HORIZONTAL,
};

enum DRAGPANEL_MOVE_DIR
{
    DRAGPANEL_MOVE_DIR_NONE,
    DRAGPANEL_MOVE_DIR_ANY,
    DRAGPANEL_MOVE_DIR_UP,
    DRAGPANEL_MOVE_DIR_DOWN,
    DRAGPANEL_MOVE_DIR_LEFT,
    DRAGPANEL_MOVE_DIR_RIGHT,
};
 */

enum DRAGPANEL_MOVE_TYPE
{
    DRAGPANEL_MOVE_TYPE_NONE,
    DRAGPANEL_MOVE_TYPE_AUTOMOVE,
    DRAGPANEL_MOVE_TYPE_BOUNCE,
};

enum DRAGPANEL_BERTH_DIR
{
    DRAGPANEL_BERTH_DIR_NONE,
    DRAGPANEL_BERTH_DIR_LEFTBOTTOM,
    DRAGPANEL_BERTH_DIR_LFETTOP,
    DRAGPANEL_BERTH_DIR_RIGHTBOTTOM,
    DRAGPANEL_BERTH_DIR_RIGHTTOP,
    DRAGPANEL_BERTH_DIR_LEFT,
    DRAGPANEL_BERTH_DIR_TOP,
    DRAGPANEL_BERTH_DIR_RIGHT,
    DRAGPANEL_BERTH_DIR_BOTTOM,
};

enum DRAGPANEL_BOUNCE_DIR
{
    DRAGPANEL_BOUNCE_DIR_NONE,
    DRAGPANEL_BOUNCE_DIR_LEFTBOTTOM,
    DRAGPANEL_BOUNCE_DIR_LEFTTOP,
    DRAGPANEL_BOUNCE_DIR_RIGHTBOTTOM,
    DRAGPANEL_BOUNCE_DIR_RIGHTTOP,
    DRAGPANEL_BOUNCE_DIR_LEFT,
    DRAGPANEL_BOUNCE_DIR_TOP,
    DRAGPANEL_BOUNCE_DIR_RIGHT,
    DRAGPANEL_BOUNCE_DIR_BOTTOM,
};

typedef void (CCObject::*SEL_DragPanelBerthToLeftBottomEvent)(CCObject*);
#define coco_DragPane_BerthToLeftBottom_selector(_SELECTOR) (SEL_DragPanelBerthToLeftBottomEvent)(&_SELECTOR)
typedef void (CCObject::*SEL_DragPanelBerthToLeftTopEvent)(CCObject*);
#define coco_DragPanel_BerthToLeftTop_selector(_SELECTOR) (SEL_DragPanelBerthToLeftTopEvent)(&_SELECTOR)
typedef void (CCObject::*SEL_DragPanelBerthToRightBottomEvent)(CCObject*);
#define coco_DragPanel_BerthToRightBottom_selector(_SELECTOR) (SEL_DragPanelBerthToRightBottomEvent)(&_SELECTOR)
typedef void (CCObject::*SEL_DragPanelBerthToRightTopEvent)(CCObject*);
#define coco_DragPanel_BerthToRightTop_selector(_SELECTOR) (SEL_DragPanelBerthToRightTopEvent)(&_SELECTOR)
typedef void (CCObject::*SEL_DragPanelBerthToLeftEvent)(CCObject*);
#define coco_DragPanel_BerthToLeft_selector(_SELECTOR) (SEL_DragPanelBerthToLeftEvent)(&_SELECTOR)
typedef void (CCObject::*SEL_DragPanelBerthToRightEvent)(CCObject*);
#define coco_DragPanel_BerthToRight_selector(_SELECTOR) (SEL_DragPanelBerthToRightEvent)(&_SELECTOR)
typedef void (CCObject::*SEL_DragPanelBerthToTopEvent)(CCObject*);
#define coco_DragPanel_BerthToTop_selector(_SELECTOR) (SEL_DragPanelBerthToTopEvent)(&_SELECTOR)
typedef void (CCObject::*SEL_DragPanelBerthToBottomEvent)(CCObject*);
#define coco_DragPanel_BerthToBottom_selector(_SELECTOR) (SEL_DragPanelBerthToBottomEvent)(&_SELECTOR)

typedef void (CCObject::*SEL_DragPanelBounceOverEvent)(CCObject*);
#define coco_DragPanel_BounceOver_selector(_SELECTOR) (SEL_DragPanelBounceOverEvent)(&_SELECTOR)
typedef void (CCObject::*SEL_DragPanelBounceToLeftBottomEvent)(CCObject*);
#define coco_DragPanel_BounceToLeftBottom_selector(_SELECTOR) (SEL_DragPanelBounceToLeftBottomEvent)(&_SELECTOR)
typedef void (CCObject::*SEL_DragPanelBounceToLeftTopEvent)(CCObject*);
#define coco_DragPanel_BounceToLeftTop_selector(_SELECTOR) (SEL_DragPanelBounceToLeftTopEvent)(&_SELECTOR)
typedef void (CCObject::*SEL_DragPanelBounceToRightBottomEvent)(CCObject*);
#define coco_DragPanel_BounceToRightBottom_selector(_SELECTOR) (SEL_DragPanelBounceToRightBottomEvent)(&_SELECTOR)
typedef void (CCObject::*SEL_DragPanelBounceToRightTopEvent)(CCObject*);
#define coco_DragPanel_BounceToRightTop_selector(_SELECTOR) (SEL_DragPanelBounceToRightTopEvent)(&_SELECTOR)
typedef void (CCObject::*SEL_DragPanelBounceToLeftEvent)(CCObject*);
#define coco_DragPanel_BounceToLeft_selector(_SELECTOR) (SEL_DragPanelBounceToLeftEvent)(&_SELECTOR)
typedef void (CCObject::*SEL_DragPanelBounceToTopEvent)(CCObject*);
#define coco_DragPanel_BounceToTop_selector(_SELECTOR) (SEL_DragPanelBounceToTopEvent)(&_SELECTOR)
typedef void (CCObject::*SEL_DragPanelBounceToRightEvent)(CCObject*);
#define coco_DragPanel_BounceToRight_selector(_SELECTOR) (SEL_DragPanelBounceToRightEvent)(&_SELECTOR)
typedef void (CCObject::*SEL_DragPanelBounceToBottomEvent)(CCObject*);
#define coco_DragPanel_BounceToBottom_selector(_SELECTOR) (SEL_DragPanelBounceToBottomEvent)(&_SELECTOR)

class UIDragPanel : public UIPanel// , public UIScrollDelegate
{
public:
    UIDragPanel();
    virtual ~UIDragPanel();
    
    static UIDragPanel* create();
    
    virtual bool init();
    virtual void initNodes();
    
    virtual void releaseResoures();
    
    virtual void onTouchBegan(const CCPoint &touchPoint);
    virtual void onTouchMoved(const CCPoint &touchPoint);
    virtual void onTouchEnded(const CCPoint &touchPoint);
    virtual void onTouchCancelled(const CCPoint &touchPoint);
    virtual void onTouchLongClicked(const CCPoint &touchPoint);
    
    virtual void update(float dt);
    
    virtual bool addChild(UIWidget* widget);
    virtual bool removeChild(UIWidget* child,bool cleanup);
    virtual void removeAllChildrenAndCleanUp(bool cleanup);
    
    /*
    void setDirection(DRAGPANEL_DIR dir);
    DRAGPANEL_DIR getDirection();
    void setMoveDirection(DRAGPANEL_MOVE_DIR moveDir);
    DRAGPANEL_MOVE_DIR getMoveDirection();
     */
    
    // auto move
    void setAutoMoveDuration(float duration);
    void setAutoMoveEaseRate(float rate);        
    
    // berth
    bool isBerth();
    
    // berth event
    void addBerthToLeftBottomEvent(CCObject* target, SEL_DragPanelBerthToLeftBottomEvent selector);
    void addBerthToLeftTopEvent(CCObject* target, SEL_DragPanelBerthToLeftTopEvent selector);
    void addBerthToRightBottomEvent(CCObject* target, SEL_DragPanelBerthToRightBottomEvent selector);
    void addBerthToRightTopEvent(CCObject* target, SEL_DragPanelBerthToRightTopEvent selector);
    void addBerthToLeftEvent(CCObject* target, SEL_DragPanelBerthToLeftEvent selector);
    void addBerthToTopEvent(CCObject* target, SEL_DragPanelBerthToTopEvent selector);
    void addBerthToRightEvent(CCObject* target, SEL_DragPanelBerthToRightEvent selector);
    void addBerthToBottomEvent(CCObject* target, SEL_DragPanelBerthToBottomEvent selector);
    
    // bounce
    bool isBounceEnable();
    void setBounceEnable(bool bounce);
    void setBounceDuratoin(float duration);
    void setBounceEaseRate(float rate);
    // bounce event
    void addBounceOverEvent(CCObject* target, SEL_DragPanelBounceOverEvent selector);
    void addBounceToLeftBottomEvent(CCObject* target, SEL_DragPanelBounceToLeftBottomEvent selector);
    void addBounceToLeftTopEvent(CCObject* target, SEL_DragPanelBounceToLeftTopEvent selector);
    void addBounceToRightBottomEvent(CCObject* target, SEL_DragPanelBounceToRightBottomEvent selector);
    void addBounceToRightTopEvent(CCObject* target, SEL_DragPanelBounceToRightTopEvent selector);
    void addBounceToLeftEvent(CCObject* target, SEL_DragPanelBounceToLeftEvent selector);
    void addBounceToTopEvent(CCObject* target, SEL_DragPanelBounceToTopEvent selector);
    void addBounceToRightEvent(CCObject* target, SEL_DragPanelBounceToRightEvent selector);
    void addBounceToBottomEvent(CCObject* target, SEL_DragPanelBounceToBottomEvent selector);    
    
protected:
    virtual void handlePressLogic(const CCPoint &touchPoint);
    virtual void handleMoveLogic(const CCPoint &touchPoint);
    virtual void handleReleaseLogic(const CCPoint &touchPoint);
    virtual void interceptTouchEvent(int handleState,UIWidget* sender, const CCPoint &touchPoint);
    virtual void checkChildInfo(int handleState, UIWidget *sender, const CCPoint &touchPoint);
    void updateWidthAndHeight();
    void recordSlidTime(float dt);
    
    // check if dragpanel rect contain inner rect
    bool checkContainInnerRect();
    
    // move
    void moveWithDelta(const CCPoint& delta);
    
    // auto move
    void autoMove();
    void autoMoveOver();    
    void startAutoMove();
    void stopAutoMove();    
    
    // berth
    // check if move to boundary with update
    bool checkToBoundaryWithDeltaPosition(const CCPoint& delta);
    
    // calculate to boundary delta
    CCPoint calculateToBoundaryDeltaPosition(CCPoint& delta);
    
    // check berth
    bool checkBerth();
    
    // berth event
    void berthEvent();
    void berthToLeftEvent();
    void berthToRightEvent();
    void berthToTopEvent();
    void berthToBottomEvent();
    void berthToLeftBottomEvent();
    void berthToLeftTopEvent();
    void berthToRightBottomEvent();
    void berthToRightTopEvent();
    
    // bounce
    bool checkNeedBounce();
    void startBounce();
    void stopBounce();
    void bounceToCorner();
    void bounceOver();
    // bounce event
    void bounceOverEvent();
    void bounceToLeftBottomEvent();
    void bounceToRightBottomEvent();
    void bounceToLeftTopEvent();
    void bounceToRightTopEvent();
    void bounceToLeftEvent();
    void bounceToTopEvent();
    void bounceToRightEvent();
    void bounceToBottomEvent();    
        
    void actionWithDuration(float duration);
    bool actionIsDone();
    void actionStartWithWidget(UIWidget* widget);
    void actionStep(float dt);
    void actionUpdate(float dt);
    void actionStop();
    void actionDone();
    void moveByWithDuration(float duration, const CCPoint& deltaPosition);
    void moveByInit();
    void moveByUpdate(float t);
    void moveToWithDuration(float duration, const CCPoint& position);
    void moveToInit();
    void moveToUpdate(float t);
    
protected:
    UIPanel* m_pInnerPanel;
    
    /*
    DRAGPANEL_DIR m_eDirection;
    DRAGPANEL_MOVE_DIR m_eMoveDirection;
     */
    
    bool m_bTouchPressed;
    bool m_bTouchMoved;
    bool m_bTouchReleased;
    bool m_bTouchCanceld; // check touch out of drag panel boundary
    
    CCPoint m_touchStartNodeSpace;
    CCPoint m_touchStartWorldSpace;
    CCPoint m_touchEndWorldSpace;
    
    float m_fSlidTime;
    
    // move type
    DRAGPANEL_MOVE_TYPE m_eMoveType;
    
    // auto move
    float m_fAutoMoveDuration;
    float m_fAutoMoveEaseRate;
    
    // berth
    DRAGPANEL_BERTH_DIR m_eBerthDirection;
    
    // berth event
    CCObject* m_pBerthToLeftListener;
    SEL_DragPanelBerthToLeftEvent m_pfnBerthToLeftSelector;
    CCObject* m_pBerthToRightListener;
    SEL_DragPanelBerthToRightEvent m_pfnBerthToRightSelector;
    CCObject* m_pBerthToTopListener;
    SEL_DragPanelBerthToTopEvent m_pfnBerthToTopSelector;
    CCObject* m_pBerthToBottomListener;
    SEL_DragPanelBerthToBottomEvent m_pfnBerthToBottomSelector;
    CCObject* m_pBerthToLeftBottomListener;
    SEL_DragPanelBerthToLeftBottomEvent m_pfnBerthToLeftBottomSelector;
    CCObject* m_pBerthToLeftTopListener;
    SEL_DragPanelBerthToLeftTopEvent m_pfnBerthToLeftTopSelector;
    CCObject* m_pBerthToRightBottomListener;
    SEL_DragPanelBerthToRightBottomEvent m_pfnBerthToRightBottomSelector;
    CCObject* m_pBerthToRightTopListener;
    SEL_DragPanelBerthToRightTopEvent m_pfnBerthToRightTopSelector;
    
    // bounce
    bool m_bBounceEnable;
    DRAGPANEL_BOUNCE_DIR m_eBounceDirection;
    float m_fBounceDuration;
    float m_fBounceEaseRate;
    
    // bounce event
    CCObject* m_pBounceOverListener;
    SEL_DragPanelBounceOverEvent m_pfnBounceOverSelector;
    CCObject* m_pBounceToLeftBottomListener;
    SEL_DragPanelBounceToLeftBottomEvent m_pfnBounceToLeftBottomSelector;
    CCObject* m_pBounceToLeftTopListener;
    SEL_DragPanelBounceToLeftTopEvent m_pfnBounceToLeftTopSelector;
    CCObject* m_pBounceToRightBottomListener;
    SEL_DragPanelBounceToRightBottomEvent m_pfnBounceToRightBottomSelector;
    CCObject* m_pBounceToRightTopListener;
    SEL_DragPanelBounceToRightTopEvent m_pfnBounceToRightTopSelector;
    CCObject* m_pBounceToLeftListener;
    SEL_DragPanelBounceToLeftEvent m_pfnBounceToLeftSelector;
    CCObject* m_pBounceToTopListener;
    SEL_DragPanelBounceToTopEvent m_pfnBounceToTopSelector;
    CCObject* m_pBounceToRightListener;
    SEL_DragPanelBounceToRightEvent m_pfnBounceToRightSelector;
    CCObject* m_pBounceToBottomListener;
    SEL_DragPanelBounceToBottomEvent m_pfnBounceToBottomSelector;        
    
    
    
    float m_bRunningAction;
    int m_nActionType;
    
    UIWidget* m_pActionWidget;
    
    float m_fDuration;
    float m_elapsed;
    bool m_bFirstTick;
    
    CCPoint m_positionDelta;
    CCPoint m_startPosition;
    CCPoint m_previousPosition;
    
    CCPoint m_endPosition;
};

NS_CC_EXT_END

#endif /* defined(__TestCpp__UIDragPanel__) */
