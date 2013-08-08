

#ifndef __TestCpp__UINodeContainerTest__
#define __TestCpp__UINodeContainerTest__

#include "../UIScene.h"

class UINodeContainerTest : public UIScene
{
public:
    UINodeContainerTest();
    ~UINodeContainerTest();
    bool init();
    
protected:
    UI_SCENE_CREATE_FUNC(UINodeContainerTest)
//    CC_SYNTHESIZE_RETAIN(CCLabelTTF *, m_pDisplayValueLabel, DisplayValueLabel)
    UILabel* m_pDisplayValueLabel;
};

#endif /* defined(__TestCpp__UINodeContainerTest__) */
