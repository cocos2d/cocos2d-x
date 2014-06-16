

#ifndef __TestCpp__UISliderTest_Editor__
#define __TestCpp__UISliderTest_Editor__

#include "../UIScene_Editor.h"

class UISliderTest_Editor : public UIScene_Editor
{
public:
    UISliderTest_Editor();
    ~UISliderTest_Editor();
    bool init();
    void sliderEvent(CCObject* pSender, SliderEventType type);
    void configureGUIScene();
    virtual void switchLoadMethod(CCObject* pSender);
protected:
    UI_SCENE_EDITOR_CREATE_FUNC(UISliderTest_Editor)
    ui::Label* _displayValueLabel;
};

#endif /* defined(__TestCpp__UISliderTest_Editor__) */
