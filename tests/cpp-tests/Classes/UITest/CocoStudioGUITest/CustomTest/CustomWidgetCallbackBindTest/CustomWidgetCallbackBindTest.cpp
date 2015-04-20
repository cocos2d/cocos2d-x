#include "CustomWidgetCallbackBindTest.h"

#include "../../CustomGUIScene.h"
#include "cocostudio/ActionTimeline/CSLoader.h"
#include "cocostudio/CocoStudio.h"
#include "base/ObjectFactory.h"
#include "CustomRootNode.h"
#include "CustomRootNodeReader.h"

USING_NS_CC;
using namespace flatbuffers;

// CustomWidgetCallbackBindScene

bool CustomWidgetCallbackBindScene::init()
{
    if (TestCase::init())
    {
        CSLoader* instance = CSLoader::getInstance();
        instance->registReaderObject("CustomRootNodeReader",
            (ObjectFactory::Instance)CustomRootNodeReader::getInstance);

        auto layer = CSLoader::createNode("cocosui/CustomTest/CustomWidgetCallbackBindTest/CustomWidgetCallbackBindTest.csb");
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
