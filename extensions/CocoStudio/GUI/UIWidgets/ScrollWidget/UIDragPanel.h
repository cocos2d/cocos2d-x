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

typedef enum
{
    DRAGPANEL_EVENT_BERTH_LEFTBOTTOM,
    DRAGPANEL_EVENT_BERTH_LFETTOP,
    DRAGPANEL_EVENT_BERTH_RIGHTBOTTOM,
    DRAGPANEL_EVENT_BERTH_RIGHTTOP,
    DRAGPANEL_EVENT_BERTH_LEFT,
    DRAGPANEL_EVENT_BERTH_TOP,
    DRAGPANEL_EVENT_BERTH_RIGHT,
    DRAGPANEL_EVENT_BERTH_BOTTOM,
    DRAGPANEL_EVENT_BOUNCE_LEFTBOTTOM,
    DRAGPANEL_EVENT_BOUNCE_LEFTTOP,
    DRAGPANEL_EVENT_BOUNCE_RIGHTBOTTOM,
    DRAGPANEL_EVENT_BOUNCE_RIGHTTOP,
    DRAGPANEL_EVENT_BOUNCE_LEFT,
    DRAGPANEL_EVENT_BOUNCE_TOP,
    DRAGPANEL_EVENT_BOUNCE_RIGHT,
    DRAGPANEL_EVENT_BOUNCE_BOTTOM,
}DragPanelEventType;

/**
 *  dragpanel event
 */
typedef void (Object::*SEL_DragPanelEvent)(Object*, DragPanelEventType);
#define dragpaneleventselector(_SELECTOR)(SEL_DragPanelEvent)(&_SELECTOR)

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
     *  event
     */
    void addEventListener(Object* target, SEL_DragPanelEvent selector);
        
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
     * Gets inner container of dragpanel.
     *
     * Inner container is the container of dragpanel's children.
     *
     * @return inner container.
     */
    Layout* getInnerContainer();
    
    /**
     * Returns the "class name" of widget.
     */
    virtual const char* getDescription() const;
    
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
    Layout* _innerContainer;
    
    /*
    DRAGPANEL_DIR m_eDirection;
    DRAGPANEL_MOVE_DIR m_eMoveDirection;
     */
    
    bool _touchPressed;
    bool _touchMoved;
    bool _touchReleased;
    bool _touchCanceld; // check touch out of drag panel boundary
    
    Point _touchStartNodeSpace;
    Point _touchStartWorldSpace;
    Point _touchEndWorldSpace;
    
    float _slidTime;
    
    // move type
    DRAGPANEL_MOVE_TYPE _moveType;
    
    // auto move
    float _autoMoveDuration;
    float _autoMoveEaseRate;
    
    // event
    Object* _eventLister;
    SEL_DragPanelEvent _eventSelector;
    
    // berth
    DRAGPANEL_BERTH_DIR _berthDirection;
        
    // bounce
    bool _bounceEnable;
    DRAGPANEL_BOUNCE_DIR _bounceDirection;
    float _bounceDuration;
    float _bounceEaseRate;
    
    
    float _runningAction;
    int _actionType;
    
    UIWidget* _actionWidget;
    
    float _duration;
    float _elapsed;
    bool _firstTick;
    
    Point _positionDelta;
    Point _startPosition;
    Point _previousPosition;
    
    Point _endPosition;
};

NS_CC_EXT_END

#endif /* defined(__TestCpp__UIDragPanel__) */
