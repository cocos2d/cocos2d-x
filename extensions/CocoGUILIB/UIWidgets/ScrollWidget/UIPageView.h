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

#ifndef __UIPAGEVIEW_H__
#define __UIPAGEVIEW_H__

#include "../UIPanel.h"
#include "UIScrollDelegate.h"

NS_CC_EXT_BEGIN

typedef enum {
    PAGEVIEW_TOUCHLEFT,
    PAGEVIEW_TOUCHRIGHT
}PVTouchDir;

class UIPageView : public UIPanel// , public UIScrollDelegate
{
    
public:
    UIPageView();
    virtual ~UIPageView();
    static UIPageView* create();
    void addWidgetToPage(UIWidget* widget, int pageIdx, bool forceCreate);
    UIPanel* createPage();
    void addPage(UIContainerWidget* page);
    void insertPage(UIContainerWidget* page, int idx);
    void removePage(UIContainerWidget* page, bool cleanup);
    void removePageAtIndex(int index, bool cleanup);
    virtual void setSize(const CCSize &size);
    void updateChildrenSize();
    void updateChildrenPosition();
    void scrollToPage(int idx);
    virtual bool removeChild(UIWidget* widget, bool cleanup);
    virtual void removeAllChildrenAndCleanUp(bool cleanup);
    virtual void onTouchBegan(const CCPoint &touchPoint);
    virtual void onTouchMoved(const CCPoint &touchPoint);
    virtual void onTouchEnded(const CCPoint &touchPoint);
    virtual void onTouchCancelled(const CCPoint &touchPoint);
    virtual void update(float dt);
protected:
    virtual bool addChild(UIWidget* widget);
    virtual bool init();
    float getPositionXByIndex(int idx);
    void updateBoundaryPages();
    virtual void handlePressLogic(const CCPoint &touchPoint);
    virtual void handleMoveLogic(const CCPoint &touchPoint);
    virtual void handleReleaseLogic(const CCPoint &touchPoint);
    virtual void interceptTouchEvent(int handleState, UIWidget* sender, const CCPoint &touchPoint);
    virtual void checkChildInfo(int handleState, UIWidget* sender, const CCPoint &touchPoint);
    virtual bool scrollPages(float touchOffset);
    void movePages(float offset);
protected:
    int m_nCurPageIdx;
    CCArray* m_pages;
    PVTouchDir m_touchMoveDir;
    float m_fTouchStartLocation;
    float m_fTouchEndLocation;
    float m_fTouchMoveStartLocation;
    CCPoint movePagePoint;
    UIWidget* m_pLeftChild;
    UIWidget* m_pRightChild;
    float m_fLeftBoundary;
    float m_fRightBoundary;
    bool m_bIsAutoScrolling;
    float m_fAutoScrollDistance;
    float m_fAutoScrollSpeed;
    int m_nAutoScrollDir;
    float m_fChildFocusCancelOffset;
};

NS_CC_EXT_END

#endif /* defined(__UIPageView__) */
