#include "CustomImageTest.h"
#include "../../CustomGUIScene.h"
#include "../../CustomWidget/CustomImageView.h"
#include "../../CustomWidget/CustomImageViewReader.h"
#include "../../CustomWidget/CustomReader.h"
#include "cocostudio/CCSGUIReader.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
using namespace cocostudio;

// CustomImageLayer
bool CustomImageLayer::init()
{
    if (Layer::init())
    {
        GUIReader* guiReader = GUIReader::getInstance();
        guiReader->registerTypeAndCallBack("CustomImageView",
            &CustomImageView::createInstance,
            CustomImageViewReader::getInstance(),
            parseselector(CustomImageViewReader::setProperties));

        Layout* layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/CustomImageViewTest/NewProject_2_1.ExportJson"));
        addChild(layout);

        return true;
    }
    
    return false;
}


// CustomImageScene


bool CustomImageScene::init()
{
    if (TestCase::init())
    {
        addChild(CustomImageLayer::create());

        return true;
    }

    return false;
}

