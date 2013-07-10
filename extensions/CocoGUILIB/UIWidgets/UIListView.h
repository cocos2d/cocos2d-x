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

typedef void (cocos2d::CCObject::*SEL_InitChildEvent)(cocos2d::CCObject*);
typedef void (cocos2d::CCObject::*SEL_UpdateChildEvent)(cocos2d::CCObject*);
#define coco_InitChildSelector(_SELECTOR) (cs::SEL_InitChildEvent)(&_SELECTOR)
#define coco_UpdateChildSelector(_SELECTOR) (cs::SEL_UpdateChildEvent)(&_SELECTOR)

class UIListView : public UIScrollView
{
public:
    UIListView();
    virtual ~UIListView();
    static UIListView* create();
    virtual bool addChild(UIWidget* widget);
    virtual void removeChildMoveToTrash(UIWidget* child);
    virtual void removeChildReferenceOnly(UIWidget* child);
    virtual void removeAllChildrenAndCleanUp(bool cleanup);
    bool scrollChildren(float touchOffset);
    void drag(float offset);        
    UIWidget* getCheckPositionChild();
    void initChildWithDataLength(int length);        
    UIWidget* getChildFromUpdatePool();
    void pushChildToPool();
    void getAndCallback();
    int getDataLength();        
    UIWidget* getUpdateChild();
    void setUpdateChild(UIWidget* child);
    int getUpdateDataIndex();
    void setUpdateDataIndex(int index);
    bool getUpdateSuccess();
    void setUpdateSuccess(bool sucess);
    void collectOverTopChild();
    void collectOverBottomChild();
    void collectOverLeftChild();
    void collectOverRightChild();
    void setLoopPosition();
    void updateChild();
    void initChildEvent();
    void updateChildEvent();
    void addInitChildEvent(cocos2d::CCObject* target, SEL_InitChildEvent seletor);
    void addUpdateChildEvent(cocos2d::CCObject* target, SEL_UpdateChildEvent selector);
    
protected:
    virtual bool init();
protected:
    cocos2d::CCObject* m_pInitChildListener;
    SEL_InitChildEvent m_pfnInitChildSelector;
    cocos2d::CCObject* m_pUpdateChildListener;
    SEL_UpdateChildEvent m_pfnUpdateChildSelector;
    
    CCArray* m_pChildPool;
    CCArray* m_pUpdatePool;
    /*
    UIWidgetPool* m_pChildPool;
    UIWidgetPool* m_pUpdatePool;
     */
    
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
};

NS_CC_EXT_END


#endif /* defined(__Test__UIListView__) */
