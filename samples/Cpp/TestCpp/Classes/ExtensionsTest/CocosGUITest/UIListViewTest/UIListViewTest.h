

#ifndef __TestCpp__UIListViewTest__
#define __TestCpp__UIListViewTest__

#include "../UIScene.h"

class UIListViewTest_Vertical : public UIScene
{
public:
    UIListViewTest_Vertical();
    ~UIListViewTest_Vertical();
    bool init();    
    void initChildEvent(CCObject* pSender);
    void updateChildEvent(CCObject* pSender);
    
protected:
    UI_SCENE_CREATE_FUNC(UIListViewTest_Vertical)
    UILabel* m_pDisplayValueLabel;
    
    int m_nCount;
    CCArray* m_array;
};

class UIListViewTest_Horizontal : public UIScene
{
public:
    UIListViewTest_Horizontal();
    ~UIListViewTest_Horizontal();
    bool init();
    void initChildEvent(CCObject* pSender);
    void updateChildEvent(CCObject* pSender);
    
protected:
    UI_SCENE_CREATE_FUNC(UIListViewTest_Horizontal)
    UILabel* m_pDisplayValueLabel;
    
    int m_nCount;
    CCArray* m_array;
};

#endif /* defined(__TestCpp__UIListViewTest__) */
