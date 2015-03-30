

#ifndef __TestCpp__CocoStudioGUITest__
#define __TestCpp__CocoStudioGUITest__

#include "../../testBasic.h"

class CocoStudioGUIMainLayer : public Layer
{
public:
    virtual void onEnter() override;
    void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event) override;
//    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event) override;
    
private:
    Vec2 _beginPos;
    Menu* _itemMenu;
};

class CocoStudioGUITestScene : public TestScene
{
public:
    virtual void onEnter() override;
    virtual void runThisTest();
    void BackCallback(Ref* pSender);
};

#endif /* defined(__TestCpp__CocoStudioGUITest__) */
