

#ifndef __TestCpp__UILoadingBarTest_Editor__
#define __TestCpp__UILoadingBarTest_Editor__

#include "../UIScene_Editor.h"

class UILoadingBarTest_Editor : public UIScene_Editor
{
public:
    UILoadingBarTest_Editor();
    ~UILoadingBarTest_Editor();
    bool init();
    void update(float delta);
    void toCocosGUITestScene(CCObject* sender, TouchEventType type);
    void configureGUIScene();
    virtual void switchLoadMethod(CCObject* pSender);
protected:
    UI_SCENE_EDITOR_CREATE_FUNC(UILoadingBarTest_Editor)
    int _count;
};

#endif /* defined(__TestCpp__UILoadingBarTest_Editor__) */
