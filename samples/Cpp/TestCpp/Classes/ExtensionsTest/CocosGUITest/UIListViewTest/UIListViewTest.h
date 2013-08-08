

#ifndef __TestCpp__UIListViewTest__
#define __TestCpp__UIListViewTest__

#include "../UIScene.h"

class UIListViewTest : public UIScene
{
public:
    UIListViewTest();
    ~UIListViewTest();
    bool init();    
    void initChildEvent(CCObject* pSender);
    void updateChildEvent(CCObject* pSender);
    
protected:
    UI_SCENE_CREATE_FUNC(UIListViewTest)
    UILabel* m_pDisplayValueLabel;
    
    int m_nCount;
    CCArray* array;
};

#endif /* defined(__TestCpp__UIListViewTest__) */
