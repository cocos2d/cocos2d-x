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

#include "../../Layouts/Layout.h"
#include "UIScrollInterface.h"

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


class UIScrollView : public Layout , public UIScrollInterface
{
public:
    /**
     * Default constructor
     */
    UIScrollView();
    
    /**
     * Default destructor
     */
    virtual ~UIScrollView();
    
    /**
     * Allocates and initializes.
     */
    static UIScrollView* create();
    
    /**
     * Changes scroll direction of scrollview.
     *
     * @see SCROLLVIEW_DIR      SCROLLVIEW_DIR_VERTICAL means vertical scroll, SCROLLVIEW_DIR_HORIZONTAL means horizontal scroll
     *
     * @param SCROLLVIEW_DIR
     */
    void setDirection(SCROLLVIEW_DIR dir);
    
    /**
     * Gets scroll direction of scrollview.
     *
     * @see SCROLLVIEW_DIR      SCROLLVIEW_DIR_VERTICAL means vertical scroll, SCROLLVIEW_DIR_HORIZONTAL means horizontal scroll
     *
     * @return SCROLLVIEW_DIR
     */
    SCROLLVIEW_DIR getDirection();
    
    /**
     * Gets inner container of scrollview.
     *
     * Inner container is the container of scrollview's children.
     *
     * @return inner container.
     */
    Layout* getInnerContainer();
    
    /**
     * Scroll inner container to bottom boundary of scrollview.
     */
    void scrollToBottom();
    
    /**
     * Scroll inner container to top boundary of scrollview.
     */
    void scrollToTop();
    
    /**
     * Changes inner container size of scrollview.
     *
     * Inner container size must be larger than or equal scrollview's size.
     *
     * @param inner container size.
     */
    void setInnerContainerSize(const CCSize &size);
    
    /**
     * Gets inner container size of scrollview.
     *
     * Inner container size must be larger than or equal scrollview's size.
     *
     * @return inner container size.
     */
	const CCSize& getInnerContainerSize() const;
    
    /**
     * Add call back function called when scrollview scrolled to top.
     */
    void addScrollToTopEvent(CCObject* target, SEL_ScrollToTopEvent selector);
    
    /**
     * Add call back function called when scrollview scrolled to bottom.
     */
    void addScrollToBottomEvent(CCObject* target, SEL_ScrollToBottomEvent selector);
    
    /**
     * Add call back function called when scrollview scrolled to left.
     */
    void addScrollToLeftEvent(CCObject* target, SEL_ScrollToLeftEvent selector);
    
    /**
     * Add call back function called when scrollview scrolled to right.
     */
    void addScrollToRightEvent(CCObject* target, SEL_ScrollToRightEvent selector);
    
    //override "setLayoutExecutant" method of widget.
    virtual void setLayoutExecutant(LayoutExecutant* exe);
    
    //override "getLayoutExecutant" method of widget.
    virtual LayoutExecutant* getLayoutExecutant() const;

    //override "releaseResoures" method of widget.
    virtual void releaseResoures();
    
    //override "addChild" method of widget.
    virtual bool addChild(UIWidget* widget);
    
    //override "removeAllChildrenAndCleanUp" method of widget.
    virtual void removeAllChildrenAndCleanUp(bool cleanup);
    
    //override "removeChild" method of widget.
	virtual bool removeChild(UIWidget* child,bool cleanup);
    
    //override "getChildren" method of widget.
    virtual CCArray* getChildren();
    
    //override "onTouchBegan" method of widget.
    virtual bool onTouchBegan(const CCPoint &touchPoint);
    
    //override "onTouchMoved" method of widget.
    virtual void onTouchMoved(const CCPoint &touchPoint);
    
    //override "onTouchEnded" method of widget.
    virtual void onTouchEnded(const CCPoint &touchPoint);
    
    //override "onTouchCancelled" method of widget.
    virtual void onTouchCancelled(const CCPoint &touchPoint);
    
    //override "onTouchLongClicked" method of widget.
    virtual void onTouchLongClicked(const CCPoint &touchPoint);
//    float getScrollDegreeRange() const;
//    void setScrollDegreeRange(float range);
protected:
    virtual bool init();
    virtual void initRenderer();
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
    virtual void onSizeChanged();
//    virtual bool isInScrollDegreeRange(UIWidget* widget);
    /*compatible*/
    CC_DEPRECATED_ATTRIBUTE virtual void setClippingEnable(bool is){setClippingEnabled(is);};
    /************/
    virtual void setClippingEnabled(bool able){Layout::setClippingEnabled(able);};
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
    
    Layout* m_pInnerContainer;
    float m_fScrollDegreeRange;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UIScrollView__) */
