

#ifndef __TestCpp__CocoStudioGUITest__
#define __TestCpp__CocoStudioGUITest__

#include "../../testBasic.h"

class CocoStudioGUIMainLayer : public Layer
{
public:
    virtual void onEnter();
    void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
//    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);
    
private:
    Vector2 _beginPos;
    Menu* _itemMenu;
};

class CocoStudioGUITestScene : public TestScene
{
public:
    virtual void onEnter();
    virtual void runThisTest();
    void BackCallback(Ref* pSender);
};

#endif /* defined(__TestCpp__CocoStudioGUITest__) */
