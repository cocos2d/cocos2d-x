

#ifndef __TestCpp__CutomGUIScene__
#define __TestCpp__CutomGUIScene__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "../../testBasic.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

class CustomGUITestMainLayer : public Layer
{
public:
    virtual void onEnter();
    void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
//    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);    
    
    void touchEvent(Ref* pSender, Widget::TouchEventType type);
    
private:
    Vec2 _beginPos;
    Menu* _itemMenu;
};

class CustomGUITestScene : public TestScene
{
public:
    virtual void onEnter();
    virtual void runThisTest();
    void BackCallback(Ref* pSender);
};

#endif /* defined(__TestCpp__CutomGUIScene__) */
