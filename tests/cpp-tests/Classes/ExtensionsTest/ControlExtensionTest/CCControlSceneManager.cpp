#include "CCControlSceneManager.h"
#include "CCControlScene.h"
#include "CCControlButtonTest/CCControlButtonTest.h"
#include "CCControlColourPicker/CCControlColourPickerTest.h"
#include "CCControlSliderTest/CCControlSliderTest.h"
#include "CCControlSwitchTest/CCControlSwitchTest.h"
#include "CCControlPotentiometerTest/CCControlPotentiometerTest.h"
#include "CCControlStepperTest/CCControlStepperTest.h"

USING_NS_CC;

ControlTests::ControlTests()
{
    addTestCase("CCControlSliderTest", [](){ return ControlSliderTest::create(); });
    addTestCase("ControlColourPickerTest", [](){ return ControlColourPickerTest::create(); });
    addTestCase("ControlSwitchTest", [](){ return ControlSwitchTest::create(); });
    addTestCase("ControlButtonTest_HelloVariableSize", [](){ return ControlButtonTest_HelloVariableSize::create(); });
    addTestCase("ControlButtonTest_Event", [](){ return ControlButtonTest_Event::create(); });
    addTestCase("ControlButtonTest_Styling", [](){ return ControlButtonTest_Styling::create(); });
    addTestCase("ControlPotentiometerTest", [](){ return ControlPotentiometerTest::create(); });
    addTestCase("CCControlStepperTest", [](){ return ControlStepperTest::create(); });
}
