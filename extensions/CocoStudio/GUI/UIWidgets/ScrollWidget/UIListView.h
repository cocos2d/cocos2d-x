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

#ifndef __UILISTVIEW_H__
#define __UILISTVIEW_H__

/* gui mark */
#include "../../Layouts/Layout.h"
/**/

NS_CC_EXT_BEGIN

/**
 *  list view direction
 */
typedef enum LISTVIEW_DIR
{
    LISTVIEW_DIR_NONE,
    LISTVIEW_DIR_VERTICAL,
    LISTVIEW_DIR_HORIZONTAL
}ListViewDirection;

/**
 *  list view scroll direction
 */
typedef enum LISTVIEW_MOVE_DIR
{
    LISTVIEW_MOVE_DIR_NONE,
    LISTVIEW_MOVE_DIR_UP,
    LISTVIEW_MOVE_DIR_DOWN,
    LISTVIEW_MOVE_DIR_LEFT,
    LISTVIEW_MOVE_DIR_RIGHT,
}ListViewMoveDirection;

typedef enum
{
    LISTVIEW_EVENT_INIT_CHILD,
    LISTVIEW_EVENT_UPDATE_CHILD,
}ListViewEventType;

/**
 *  list view event
 */
typedef void (Object::*SEL_ListViewEvent)(Object*, ListViewEventType);
#define listvieweventselector(_SELECTOR)(SEL_ListViewEvent)(&_SELECTOR)

class UIListView : public Layout
{
public:
    UIListView();
    virtual ~UIListView();
    static UIListView* create();
    
    /**
     *  add widget child override
     */
    virtual bool addChild(UIWidget* widget);
    /**
     *  remove all widget children override
     */
    virtual void removeAllChildren();
    /**
     *  remove widget child override
     */
    virtual bool removeChild(UIWidget* child);
    
    virtual bool onTouchBegan(const Point &touchPoint);
    virtual void onTouchMoved(const Point &touchPoint);
    virtual void onTouchEnded(const Point &touchPoint);
    virtual void onTouchCancelled(const Point &touchPoint);
    virtual void onTouchLongClicked(const Point &touchPoint);
    
    /**
     *  set and get direction
     */
    void setDirection(ListViewDirection dir);
    ListViewDirection getDirection();
    
    /**
     *  initialze data length
     *  and create children with parameter length
     */
    void initChildWithDataLength(int length);
    /**
     *  get data length
     */
    int getDataLength();
    
    /**
     *  update child function whetn trigger update child event
     */
    /**
     *  get update widget child
     */
    UIWidget* getUpdateChild();
    /**
     *  get update data index
     */
    int getUpdateDataIndex();
    /**
     *  get and set update success or not
     */
    bool getUpdateSuccess();
    void setUpdateSuccess(bool sucess);
    
    /**
     *  add event call-back function
     */
    /**
     *  add event
     */
    void addEventListenter(cocos2d::Object* target, SEL_ListViewEvent selector);
    
    /* gui mark */
    /**
     *  get and set degree range for checking move or not with scrolling
     */
    /**/
    virtual void update(float dt);
    
    /**
     * Returns the "class name" of widget.
     */
    virtual const char* getDescription() const;
protected:
    virtual bool init();
    
    virtual void onSizeChanged();
    
    void setMoveDirection(ListViewMoveDirection dir);
    ListViewMoveDirection getMoveDirection();
    
    virtual void resetProperty();
    
    virtual void handlePressLogic(const Point &touchPoint);
    virtual void handleMoveLogic(const Point &touchPoint);
    virtual void handleReleaseLogic(const Point &touchPoint);
    virtual void interceptTouchEvent(int handleState,UIWidget* sender,const Point &touchPoint);
    /* gui mark */
//    virtual bool isInScrollDegreeRange(UIWidget* widget);
    /**/
    virtual void checkChildInfo(int handleState,UIWidget* sender,const Point &touchPoint);
    
    void moveChildren(float offset);
    virtual bool scrollChildren(float touchOffset);
    void autoScrollChildren(float dt);
    float getCurAutoScrollDistance(float time);
    void startAutoScrollChildren(float v);
    void stopAutoScrollChildren();
    void recordSlidTime(float dt);
    void startRecordSlidAction();
    virtual void endRecordSlidAction();
    
    UIWidget* getCheckPositionChild();
    UIWidget* getChildFromUpdatePool();
    void pushChildToPool();
    void getAndCallback();
    
    void setUpdateChild(UIWidget* child);
    void setUpdateDataIndex(int index);
    void clearCollectOverArray();
    void collectOverTopChild();
    void collectOverBottomChild();
    void collectOverLeftChild();
    void collectOverRightChild();
    void setLoopPosition();
    void updateChild();
    
    void initChildEvent();
    void updateChildEvent();        
    
    virtual void setClippingEnabled(bool able){Layout::setClippingEnabled(able);};
protected:
    ListViewDirection _direction;
    ListViewMoveDirection _moveDirection;
    
    float _touchStartLocation;
    float _touchEndLocation;
    float _touchMoveStartLocation;
    float _topBoundary;//test
    float _bottomBoundary;//test
    float _leftBoundary;
    float _rightBoundary;
    
    bool _autoScroll;
    
    float _autoScrollOriginalSpeed;
    float _autoScrollAcceleration;
    
    bool _bePressed;
    float _slidTime;
    Point _moveChildPoint;
    float _childFocusCancelOffset;
    
    Object* _eventListener;
    SEL_ListViewEvent _eventSelector;
    
    Array* _childPool;
    Array* _updatePool;
    
    int _dataLength;
    int _begin;
    int _end;
    UIWidget* _updateChild;
    int _updateDataIndex;
    bool _updateSuccess;
    
    Array* _overTopArray;
    Array* _overBottomArray;
    Array* _overLeftArray;
    Array* _overRightArray;
    
    float _disBoundaryToChild_0;
    float _disBetweenChild;
    
    /* gui mark */
    float _scrollDegreeRange;
    /**/
};

NS_CC_EXT_END


#endif /* defined(__Test__UIListView__) */
