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

#ifndef __UISCROLLVIEW_H__
#define __UISCROLLVIEW_H__

#include "../UIPanel.h"
#include "UIScrollDelegate.h"

NS_CC_EXT_BEGIN

enum SCROLLVIEW_DIR
{
    SCROLLVIEW_DIR_NONE,
    SCROLLVIEW_DIR_VERTICAL,
    SCROLLVIEW_DIR_HORIZONTAL
};

enum SCROLLVIEW_MOVE_DIR
{
    SCROLLVIEW_MOVE_DIR_NONE,
    SCROLLVIEW_MOVE_DIR_UP,
    SCROLLVIEW_MOVE_DIR_DOWN,
    SCROLLVIEW_MOVE_DIR_LEFT,
    SCROLLVIEW_MOVE_DIR_RIGHT,
};

typedef void (CCObject::*SEL_ScrollToTopEvent)(CCObject*);
typedef void (CCObject::*SEL_ScrollToBottomEvent)(CCObject*);
typedef void (CCObject::*SEL_ScrollToLeftEvent)(CCObject*);
typedef void (CCObject::*SEL_ScrollToRightEvent)(CCObject*);
#define coco_ScrollToTopSelector(_SELECTOR) (cocos2d::extension::SEL_ScrollToTopEvent)(&_SELECTOR)
#define coco_ScrollToBottomSelector(_SELECTOR) (cocos2d::extension::SEL_ScrollToBottomEvent)(&_SELECTOR)
#define coco_ScrollToLeftSelector(_SELECTOR) (cocos2d::extension::SEL_ScrollToLeftEvent)(&_SELECTOR)
#define coco_ScrollToRightSelector(_SELECTOR) (cocos2d::extension::SEL_ScrollToRightEvent)(&_SELECTOR)


class UIScrollView : public UIPanel , public UIScrollDelegate
{
public:
    UIScrollView();
    virtual ~UIScrollView();
    virtual void releaseResoures();
    static UIScrollView* create();
    virtual bool addChild(UIWidget* widget);
    virtual void removeAllChildrenAndCleanUp(bool cleanup);
	virtual bool removeChild(UIWidget* child,bool cleanup);
    void scrollToBottom();
    void scrollToTop();
    virtual void setSize(const CCSize &size);
    void setInnerContainerSize(const CCSize &size);
	const CCSize& getInerContainerSize() const;
    
	CCNode* getInnerContainerNode();
    
    void addScrollToTopEvent(CCObject* target, SEL_ScrollToTopEvent selector);
    void addScrollToBottomEvent(CCObject* target, SEL_ScrollToBottomEvent selector);
    void addScrollToLeftEvent(CCObject* target, SEL_ScrollToLeftEvent selector);
    void addScrollToRightEvent(CCObject* target, SEL_ScrollToRightEvent selector);
    
    virtual void onTouchBegan(const CCPoint &touchPoint);
    virtual void onTouchMoved(const CCPoint &touchPoint);
    virtual void onTouchEnded(const CCPoint &touchPoint);
    virtual void onTouchCancelled(const CCPoint &touchPoint);
    virtual void onTouchLongClicked(const CCPoint &touchPoint);
    void setDirection(SCROLLVIEW_DIR dir);
    SCROLLVIEW_DIR getDirection();
    
    virtual void setLayoutType(LayoutType type);
protected:
    virtual bool init();
    virtual void initNodes();
    void moveChildren(float offset);
    void autoScrollChildren(float dt);
    void startAutoScrollChildren(float v);
    void stopAutoScrollChildren();
    float getCurAutoScrollDistance(float time);
    virtual bool scrollChildren(float touchOffset);
    void startRecordSlidAction();
    virtual void endRecordSlidAction();
    virtual void handlePressLogic(const CCPoint &touchPoint);
    virtual void handleMoveLogic(const CCPoint &touchPoint);
    virtual void handleReleaseLogic(const CCPoint &touchPoint);
    virtual void interceptTouchEvent(int handleState,UIWidget* sender,const CCPoint &touchPoint);
    virtual void checkChildInfo(int handleState,UIWidget* sender,const CCPoint &touchPoint);
    virtual void update(float dt);
    void recordSlidTime(float dt);
    
    void scrollToTopEvent();
    void scrollToBottomEvent();
    void scrollToLeftEvent();
    void scrollToRightEvent();
    void setMoveDirection(SCROLLVIEW_MOVE_DIR dir);
    SCROLLVIEW_MOVE_DIR getMoveDirection();
protected:
    SCROLLVIEW_DIR m_eDirection;
    SCROLLVIEW_MOVE_DIR m_eMoveDirection;
    float m_fTouchStartLocation;
    float m_fTouchEndLocation;
    float m_fTouchMoveStartLocation;
    float m_fTopBoundary;//test
    float m_fBottomBoundary;//test
    float m_fLeftBoundary;
    float m_fRightBoundary;
    
    
    int m_nMoveDirection;//0 pull down, 1 push up
    
    bool m_bTopEnd;
    bool m_bBottomEnd;
    bool m_bLeftEnd;
    bool m_bRightEnd;
    
    bool m_bAutoScroll;
    
    float m_fAutoScrollOriginalSpeed;
    float m_fAutoScrollAcceleration;
    
    bool m_bBePressed;
    float m_fSlidTime;
    CCPoint moveChildPoint;
    float m_fChildFocusCancelOffset;
    
    CCObject* m_pScrollToTopListener;
    SEL_ScrollToTopEvent m_pfnScrollToTopSelector;
    CCObject* m_pScrollToBottomListener;
    SEL_ScrollToBottomEvent m_pfnScrollToBottomSelector;
    CCObject* m_pScrollToLeftListener;
    SEL_ScrollToLeftEvent m_pfnScrollToLeftSelector;
    CCObject* m_pScrollToRightListener;
    SEL_ScrollToRightEvent m_pfnScrollToRightSelector;
    
    UIContainerWidget* m_pInnerContainer;
    
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UIScrollView__) */
