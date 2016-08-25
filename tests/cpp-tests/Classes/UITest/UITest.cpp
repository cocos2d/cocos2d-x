#include "UITest.h"
#include "CocoStudioGUITest/CocosGUIScene.h"


UITests::UITests()
{
    addTest("GUI Dynamic Create Test", [](){ return new (std::nothrow) GUIDynamicCreateTests; });
}

UITests::~UITests()
{
}
