#include "CustomGUIScene.h"

#include "CustomTest/CustomImageTest/CustomImageTest.h"
#include "CustomTest/CustomParticleWidgetTest/CustomParticleWidgetTest.h"
#include "CustomTest/CustomWidgetCallbackBindTest/CustomWidgetCallbackBindTest.h"

CustomGUITests::CustomGUITests()
{
    addTestCase("Custom widget call back bind Test", [](){ return CustomWidgetCallbackBindScene::create(); });
    addTestCase("Custom GUI image Test", [](){ return CustomImageScene::create(); });
    addTestCase("Custom GUI particle widget Test", [](){ return CustomParticleWidgetScene::create(); });
}
