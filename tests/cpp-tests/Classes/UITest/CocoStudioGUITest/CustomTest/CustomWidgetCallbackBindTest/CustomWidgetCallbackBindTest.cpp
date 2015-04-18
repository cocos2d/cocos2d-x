#include "CustomWidgetCallbackBindTest.h"

#include "../../CustomGUIScene.h"
#include "cocostudio/ActionTimeline/CSLoader.h"
#include "cocostudio/CocoStudio.h"
#include "base/ObjectFactory.h"
#include "CustomRootNode.h"

USING_NS_CC;
using namespace flatbuffers;

// CustomWidgetCallbackBindScene

bool CustomWidgetCallbackBindScene::init()
{
    if (TestCase::init())
    {
	    CustomRootNode* node = CustomRootNode::create();

        auto layer = CSLoader::createNodeWithRoot(node, "cocosui/CustomTest/CustomWidgetCallbackBindTest/CustomWidgetCallbackBindTest.csb");
        addChild(layer);

        return true;
    }
    
    return false;
}

void CustomWidgetCallbackBindScene::onExit()
{
    cocostudio::destroyCocosStudio();

    TestCase::onExit();
}
