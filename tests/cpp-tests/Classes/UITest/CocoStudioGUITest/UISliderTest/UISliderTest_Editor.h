

#ifndef __TestCpp__UISliderTest_Editor__
#define __TestCpp__UISliderTest_Editor__

#include "../UIScene_Editor.h"

DEFINE_TEST_SUITE(UISliderEditorTests);

class UISliderTest_Editor : public UIScene_Editor
{
public:
    CREATE_FUNC(UISliderTest_Editor);

    UISliderTest_Editor();
    ~UISliderTest_Editor();

    virtual bool init() override;
    void sliderEvent(Ref* pSender, Slider::EventType type);
    virtual void configureGUIScene() override;

protected:
    Text* _displayValueLabel;
};

#endif /* defined(__TestCpp__UISliderTest_Editor__) */
