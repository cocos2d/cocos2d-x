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

#include "UIScrollView.h"

NS_CC_EXT_BEGIN

typedef void (cocos2d::CCObject::*SEL_ListViewInitChildEvent)(cocos2d::CCObject*);
typedef void (cocos2d::CCObject::*SEL_ListViewUpdateChildEvent)(cocos2d::CCObject*);
#define coco_ListView_InitChild_selector(_SELECTOR) (SEL_ListViewInitChildEvent)(&_SELECTOR)
#define coco_ListView_UpdateChild_selector(_SELECTOR) (SEL_ListViewUpdateChildEvent)(&_SELECTOR)

class UIListView : public UIScrollView
{
public:
    UIListView();
    virtual ~UIListView();
    static UIListView* create();
    virtual void releaseResoures();
    virtual bool addChild(UIWidget* widget);
    virtual void removeAllChildrenAndCleanUp(bool cleanup);
    virtual bool removeChild(UIWidget* child, bool cleanup);
    virtual void setSize(const CCSize &size);
    
    void initChildWithDataLength(int length);
    int getDataLength();
    
    UIWidget* getUpdateChild();
    int getUpdateDataIndex();
    bool getUpdateSuccess();
    void setUpdateSuccess(bool sucess);
    
    void addInitChildEvent(cocos2d::CCObject* target, SEL_ListViewInitChildEvent seletor);
    void addUpdateChildEvent(cocos2d::CCObject* target, SEL_ListViewUpdateChildEvent selector);
    
protected:
    virtual bool init();
    virtual void initNodes();
    
    virtual void resetProperty();
    
    virtual void handlePressLogic(const CCPoint &touchPoint);
    virtual void endRecordSlidAction();
    virtual bool scrollChildren(float touchOffset);
    void moveChildren(float offset);
    
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
protected:
    cocos2d::CCObject* m_pInitChildListener;
    SEL_ListViewInitChildEvent m_pfnInitChildSelector;
    cocos2d::CCObject* m_pUpdateChildListener;
    SEL_ListViewUpdateChildEvent m_pfnUpdateChildSelector;
    
    CCArray* m_pChildPool;
    CCArray* m_pUpdatePool;
    
    int m_nDataLength;
    int m_nBegin;
    int m_nEnd;
    UIWidget* m_pUpdateChild;
    int m_nUpdateDataIndex;
    bool m_bUpdateSuccess;
    
    cocos2d::CCArray* m_overTopArray;
    cocos2d::CCArray* m_overBottomArray;
    cocos2d::CCArray* m_overLeftArray;
    cocos2d::CCArray* m_overRightArray;
    
    float m_fDisBoundaryToChild_0;
    float m_fDisBetweenChild;
};

NS_CC_EXT_END


#endif /* defined(__Test__UIListView__) */
