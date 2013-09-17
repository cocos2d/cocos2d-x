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

#ifndef __UIDRAGPANEL_H__
#define __UIDRAGPANEL_H__

#include "../../Layouts/Layout.h"
#include "UIScrollInterface.h"

NS_CC_EXT_BEGIN

/**
 *  drag panel move type
 */
enum DRAGPANEL_MOVE_TYPE
{
    DRAGPANEL_MOVE_TYPE_NONE,
    DRAGPANEL_MOVE_TYPE_AUTOMOVE,
    DRAGPANEL_MOVE_TYPE_BOUNCE,
};

/**
 *  dragpanel berth direction 
 */
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

/**
 *  dragpanel bounce direction
 */
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

/**
 *  dragpanel berth event
 */
typedef void (Object::*SEL_DragPanelBerthToLeftBottomEvent)(Object*);
#define coco_DragPane_BerthToLeftBottom_selector(_SELECTOR) (SEL_DragPanelBerthToLeftBottomEvent)(&_SELECTOR)
typedef void (Object::*SEL_DragPanelBerthToLeftTopEvent)(Object*);
#define coco_DragPanel_BerthToLeftTop_selector(_SELECTOR) (SEL_DragPanelBerthToLeftTopEvent)(&_SELECTOR)
typedef void (Object::*SEL_DragPanelBerthToRightBottomEvent)(Object*);
#define coco_DragPanel_BerthToRightBottom_selector(_SELECTOR) (SEL_DragPanelBerthToRightBottomEvent)(&_SELECTOR)
typedef void (Object::*SEL_DragPanelBerthToRightTopEvent)(Object*);
#define coco_DragPanel_BerthToRightTop_selector(_SELECTOR) (SEL_DragPanelBerthToRightTopEvent)(&_SELECTOR)
typedef void (Object::*SEL_DragPanelBerthToLeftEvent)(Object*);
#define coco_DragPanel_BerthToLeft_selector(_SELECTOR) (SEL_DragPanelBerthToLeftEvent)(&_SELECTOR)
typedef void (Object::*SEL_DragPanelBerthToRightEvent)(Object*);
#define coco_DragPanel_BerthToRight_selector(_SELECTOR) (SEL_DragPanelBerthToRightEvent)(&_SELECTOR)
typedef void (Object::*SEL_DragPanelBerthToTopEvent)(Object*);
#define coco_DragPanel_BerthToTop_selector(_SELECTOR) (SEL_DragPanelBerthToTopEvent)(&_SELECTOR)
typedef void (Object::*SEL_DragPanelBerthToBottomEvent)(Object*);
#define coco_DragPanel_BerthToBottom_selector(_SELECTOR) (SEL_DragPanelBerthToBottomEvent)(&_SELECTOR)

/**
 *  dragpanel bounce event
 */
typedef void (Object::*SEL_DragPanelBounceOverEvent)(Object*);
#define coco_DragPanel_BounceOver_selector(_SELECTOR) (SEL_DragPanelBounceOverEvent)(&_SELECTOR)
typedef void (Object::*SEL_DragPanelBounceToLeftBottomEvent)(Object*);
#define coco_DragPanel_BounceToLeftBottom_selector(_SELECTOR) (SEL_DragPanelBounceToLeftBottomEvent)(&_SELECTOR)
typedef void (Object::*SEL_DragPanelBounceToLeftTopEvent)(Object*);
#define coco_DragPanel_BounceToLeftTop_selector(_SELECTOR) (SEL_DragPanelBounceToLeftTopEvent)(&_SELECTOR)
typedef void (Object::*SEL_DragPanelBounceToRightBottomEvent)(Object*);
#define coco_DragPanel_BounceToRightBottom_selector(_SELECTOR) (SEL_DragPanelBounceToRightBottomEvent)(&_SELECTOR)
typedef void (Object::*SEL_DragPanelBounceToRightTopEvent)(Object*);
#define coco_DragPanel_BounceToRightTop_selector(_SELECTOR) (SEL_DragPanelBounceToRightTopEvent)(&_SELECTOR)
typedef void (Object::*SEL_DragPanelBounceToLeftEvent)(Object*);
#define coco_DragPanel_BounceToLeft_selector(_SELECTOR) (SEL_DragPanelBounceToLeftEvent)(&_SELECTOR)
typedef void (Object::*SEL_DragPanelBounceToTopEvent)(Object*);
#define coco_DragPanel_BounceToTop_selector(_SELECTOR) (SEL_DragPanelBounceToTopEvent)(&_SELECTOR)
typedef void (Object::*SEL_DragPanelBounceToRightEvent)(Object*);
#define coco_DragPanel_BounceToRight_selector(_SELECTOR) (SEL_DragPanelBounceToRightEvent)(&_SELECTOR)
typedef void (Object::*SEL_DragPanelBounceToBottomEvent)(Object*);
#define coco_DragPanel_BounceToBottom_selector(_SELECTOR) (SEL_DragPanelBounceToBottomEvent)(&_SELECTOR)

class UIDragPanel : public Layout, public UIScrollInterface
{
public:
    UIDragPanel();
    virtual ~UIDragPanel();
    
    static UIDragPanel* create();        
    
    virtual bool onTouchBegan(const Point &touchPoint);
    virtual void onTouchMoved(const Point &touchPoint);
    virtual void onTouchEnded(const Point &touchPoint);
    virtual void onTouchCancelled(const Point &touchPoint);
    virtual void onTouchLongClicked(const Point &touchPoint);
    
    virtual void update(float dt);
    
    /**
     *  add widget child override
     */
    virtual bool addChild(UIWidget* widget);
    /**
     *  remove widget child override
     */
    virtual bool removeChild(UIWidget* child);
    /**
     *  remove all widget children override
     */
    virtual void removeAllChildren();
    /**
     *  get widget children of inner container
     */
    virtual Array* getChildren();
    /* gui mark */
    /**
     *  get and set inner container size
     */
    const Size& getInnerContainerSize() const;
    void setInnerContainerSize(const Size &size);
    /**
     *  get and set inner container position
     */
    const Point& getInnerContainerPosition() const;    
    void setInnerContainerPosition(const Point& point, bool animated);
    /**
     *  set inner container offset
     */
    void setInnerContainerOffset(const Point& offset, bool animated);
    /**/
    
    // auto move
    /**
     *  set auto move duration
     */
    void setAutoMoveDuration(float duration);
    /**
     *  set auto move ease rate
     */
    void setAutoMoveEaseRate(float rate);        
    
    // berth
    /**
     *  get berth or not
     */
    bool isBerth();
    
    /**
     *  berth event by direction
     */
    void addBerthToLeftBottomEvent(Object* target, SEL_DragPanelBerthToLeftBottomEvent selector);
    void addBerthToLeftTopEvent(Object* target, SEL_DragPanelBerthToLeftTopEvent selector);
    void addBerthToRightBottomEvent(Object* target, SEL_DragPanelBerthToRightBottomEvent selector);
    void addBerthToRightTopEvent(Object* target, SEL_DragPanelBerthToRightTopEvent selector);
    void addBerthToLeftEvent(Object* target, SEL_DragPanelBerthToLeftEvent selector);
    void addBerthToTopEvent(Object* target, SEL_DragPanelBerthToTopEvent selector);
    void addBerthToRightEvent(Object* target, SEL_DragPanelBerthToRightEvent selector);
    void addBerthToBottomEvent(Object* target, SEL_DragPanelBerthToBottomEvent selector);
    
    /**
     *  get and set bounce enable
     */
    bool isBounceEnable();
    void setBounceEnable(bool bounce);
    /**
     *  set bounce duration
     */
    void setBounceDuratoin(float duration);
    /**
     *  set bounce ease rate
     */
    void setBounceEaseRate(float rate);
    /**
     *  bounce event by dircetion
     */
    void addBounceOverEvent(Object* target, SEL_DragPanelBounceOverEvent selector);
    void addBounceToLeftBottomEvent(Object* target, SEL_DragPanelBounceToLeftBottomEvent selector);
    void addBounceToLeftTopEvent(Object* target, SEL_DragPanelBounceToLeftTopEvent selector);
    void addBounceToRightBottomEvent(Object* target, SEL_DragPanelBounceToRightBottomEvent selector);
    void addBounceToRightTopEvent(Object* target, SEL_DragPanelBounceToRightTopEvent selector);
    void addBounceToLeftEvent(Object* target, SEL_DragPanelBounceToLeftEvent selector);
    void addBounceToTopEvent(Object* target, SEL_DragPanelBounceToTopEvent selector);
    void addBounceToRightEvent(Object* target, SEL_DragPanelBounceToRightEvent selector);
    void addBounceToBottomEvent(Object* target, SEL_DragPanelBounceToBottomEvent selector);
    
    /**
     * Gets inner container of dragpanel.
     *
     * Inner container is the container of dragpanel's children.
     *
     * @return inner container.
     */
    Layout* getInnerContainer();
    
protected:
    virtual bool init();
    virtual void initRenderer();
    virtual void releaseResoures();
    
    virtual void handlePressLogic(const Point &touchPoint);
    virtual void handleMoveLogic(const Point &touchPoint);
    virtual void handleReleaseLogic(const Point &touchPoint);
    virtual void interceptTouchEvent(int handleState,UIWidget* sender, const Point &touchPoint);
    /* gui mark */
//    virtual bool isInScrollDegreeRange(UIWidget* widget);
    /**/
    virtual void checkChildInfo(int handleState, UIWidget *sender, const Point &touchPoint);
//    void updateWidthAndHeight();
    void recordSlidTime(float dt);
    
    /* gui mark */
    void setInnerContainerOffset(const Point& offset);
    /**/
    
    // check if dragpanel rect contain inner rect
    bool checkContainInnerRect();
    
    // move
    void moveWithDelta(const Point& delta);
    
    // auto move
    void autoMove();
    void autoMoveOver();    
    void startAutoMove();
    void stopAutoMove();    
    
    // berth
    // check if move to boundary with update
    bool checkToBoundaryWithDeltaPosition(const Point& delta);
    
    // calculate to boundary delta
    Point calculateToBoundaryDeltaPosition(const Point& paramDelta);
    
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
    void moveByWithDuration(float duration, const Point& deltaPosition);
    void moveByInit();
    void moveByUpdate(float t);
    void moveToWithDuration(float duration, const Point& position);
    void moveToInit();
    void moveToUpdate(float t);
    virtual void onSizeChanged();
    /*compatible*/
    /**
     * These methods will be removed
     */
    virtual void setClippingEnable(bool is){setClippingEnabled(is);};
    /************/
    virtual void setClippingEnabled(bool able){Layout::setClippingEnabled(able);};
protected:
    Layout* m_pInnerContainer;
    
    /*
    DRAGPANEL_DIR m_eDirection;
    DRAGPANEL_MOVE_DIR m_eMoveDirection;
     */
    
    bool m_bTouchPressed;
    bool m_bTouchMoved;
    bool m_bTouchReleased;
    bool m_bTouchCanceld; // check touch out of drag panel boundary
    
    Point m_touchStartNodeSpace;
    Point m_touchStartWorldSpace;
    Point m_touchEndWorldSpace;
    
    float m_fSlidTime;
    
    // move type
    DRAGPANEL_MOVE_TYPE m_eMoveType;
    
    // auto move
    float m_fAutoMoveDuration;
    float m_fAutoMoveEaseRate;
    
    // berth
    DRAGPANEL_BERTH_DIR m_eBerthDirection;
    
    // berth event
    Object* m_pBerthToLeftListener;
    SEL_DragPanelBerthToLeftEvent m_pfnBerthToLeftSelector;
    Object* m_pBerthToRightListener;
    SEL_DragPanelBerthToRightEvent m_pfnBerthToRightSelector;
    Object* m_pBerthToTopListener;
    SEL_DragPanelBerthToTopEvent m_pfnBerthToTopSelector;
    Object* m_pBerthToBottomListener;
    SEL_DragPanelBerthToBottomEvent m_pfnBerthToBottomSelector;
    Object* m_pBerthToLeftBottomListener;
    SEL_DragPanelBerthToLeftBottomEvent m_pfnBerthToLeftBottomSelector;
    Object* m_pBerthToLeftTopListener;
    SEL_DragPanelBerthToLeftTopEvent m_pfnBerthToLeftTopSelector;
    Object* m_pBerthToRightBottomListener;
    SEL_DragPanelBerthToRightBottomEvent m_pfnBerthToRightBottomSelector;
    Object* m_pBerthToRightTopListener;
    SEL_DragPanelBerthToRightTopEvent m_pfnBerthToRightTopSelector;
    
    // bounce
    bool m_bBounceEnable;
    DRAGPANEL_BOUNCE_DIR m_eBounceDirection;
    float m_fBounceDuration;
    float m_fBounceEaseRate;
    
    // bounce event
    Object* m_pBounceOverListener;
    SEL_DragPanelBounceOverEvent m_pfnBounceOverSelector;
    Object* m_pBounceToLeftBottomListener;
    SEL_DragPanelBounceToLeftBottomEvent m_pfnBounceToLeftBottomSelector;
    Object* m_pBounceToLeftTopListener;
    SEL_DragPanelBounceToLeftTopEvent m_pfnBounceToLeftTopSelector;
    Object* m_pBounceToRightBottomListener;
    SEL_DragPanelBounceToRightBottomEvent m_pfnBounceToRightBottomSelector;
    Object* m_pBounceToRightTopListener;
    SEL_DragPanelBounceToRightTopEvent m_pfnBounceToRightTopSelector;
    Object* m_pBounceToLeftListener;
    SEL_DragPanelBounceToLeftEvent m_pfnBounceToLeftSelector;
    Object* m_pBounceToTopListener;
    SEL_DragPanelBounceToTopEvent m_pfnBounceToTopSelector;
    Object* m_pBounceToRightListener;
    SEL_DragPanelBounceToRightEvent m_pfnBounceToRightSelector;
    Object* m_pBounceToBottomListener;
    SEL_DragPanelBounceToBottomEvent m_pfnBounceToBottomSelector;        
    
    
    
    float m_bRunningAction;
    int m_nActionType;
    
    UIWidget* m_pActionWidget;
    
    float m_fDuration;
    float m_elapsed;
    bool m_bFirstTick;
    
    Point m_positionDelta;
    Point m_startPosition;
    Point m_previousPosition;
    
    Point m_endPosition;
};

NS_CC_EXT_END

#endif /* defined(__TestCpp__UIDragPanel__) */
