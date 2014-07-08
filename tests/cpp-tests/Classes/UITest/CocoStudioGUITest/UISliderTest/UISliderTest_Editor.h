

#ifndef __TestCpp__UISliderTest_Editor__
#define __TestCpp__UISliderTest_Editor__

#include "../UIScene_Editor.h"

class UISliderTest_Editor : public UIScene_Editor
{
public:
    UISliderTest_Editor();
    ~UISliderTest_Editor();
    bool init();
    void sliderEvent(Ref* pSender, Slider::EventType type);
    virtual void switchLoadMethod(Ref* pSender);
    void configureGUIScene();

protected:
    UI_SCENE_EDITOR_CREATE_FUNC(UISliderTest_Editor)
    Text* _displayValueLabel;
};

#endif /* defined(__TestCpp__UISliderTest_Editor__) */
