

#ifndef __TestCpp__GUIEditorTest__
#define __TestCpp__GUIEditorTest__

#include "../../testBasic.h"

class GUIEditorMainLayer : public Layer
{
public:
    virtual void onEnter();
    void menuCallback(Ref* pSender);
    void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);
private:
    Vec2 _beginPos;
    Menu* _itemMenu;
    
	int _testcount;
};

class GUIEditorTestScene : public TestScene
{
public:
    virtual void onEnter();
    virtual void runThisTest();
    void BackCallback(Ref* pSender);
};

#endif /* defined(__TestCpp__GUIEditorTest__) */
