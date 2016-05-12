#include "UITest.h"
#include "editor-support/cocostudio/CCArmatureDataManager.h"
#include "CocoStudioGUITest/CocosGUIScene.h"
#include "CocoStudioGUITest/GUIEditorTest.h"
#include "CocoStudioGUITest/CustomGUIScene.h"
#include "CocoStudioGUITest/CocostudioParserTest.h"

UITests::UITests()
{
    addTest("GUI Dynamic Create Test", [](){ return new (std::nothrow) GUIDynamicCreateTests; });
    addTest("GUI Editor Test", [](){ return new (std::nothrow) GUIEditorTests; });
    addTest("Custom GUI Test", [](){ return new (std::nothrow) CustomGUITests; });
    addTest("Cocostudio Parser Test", [](){ return new (std::nothrow) CocostudioParserTests; });
}

UITests::~UITests()
{
    cocostudio::ArmatureDataManager::destroyInstance();
}
