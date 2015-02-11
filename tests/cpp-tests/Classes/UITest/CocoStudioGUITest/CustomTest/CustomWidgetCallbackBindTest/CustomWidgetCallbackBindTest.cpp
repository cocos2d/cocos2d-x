

#include "CustomWidgetCallbackBindTest.h"

#include "../../CustomGUIScene.h"
#include "cocostudio/ActionTimeline/CSLoader.h"

//#include "base/ObjectFactory.h"

//#include "CustomRootNode.h"
//#include "CustomRootNodeReader.h"

USING_NS_CC;
using namespace flatbuffers;
using namespace std;
using namespace cocos2d::ui;

// CustomWidgetCallbackBindScene

void CustomWidgetCallbackBindScene::onEnter()
{
    Scene::onEnter();
    
    auto label = Label::createWithTTF("Back", "fonts/arial.ttf", 20);
    //#endif
    MenuItemLabel* pMenuItem = MenuItemLabel::create(label, CC_CALLBACK_1(CustomWidgetCallbackBindScene::BackCallback, this));
    
    Menu* pMenu = Menu::create(pMenuItem, nullptr);
    
    pMenu->setPosition( Vec2::ZERO );
    pMenuItem->setPosition(VisibleRect::right().x - 50, VisibleRect::bottom().y + 25);
    
    addChild(pMenu, 1);
}

void CustomWidgetCallbackBindScene::runThisTest()
{
//    CSLoader* instance = CSLoader::getInstance();
//    instance->registReaderObject("CustomRootNodeReader",
//                                 (ObjectFactory::Instance)CustomRootNodeReader::getInstance);
    
    auto pLayer = CSLoader::createNode("cocosui/CustomTest/CustomWidgetCallbackBindTest/CustomWidgetCallbackBindTest.csb", this);
    addChild(pLayer);
    
    
    Director::getInstance()->replaceScene(this);
}

void CustomWidgetCallbackBindScene::BackCallback(Ref* pSender)
{
    CustomGUITestScene* pScene = new (std::nothrow) CustomGUITestScene();
    pScene->runThisTest();
    pScene->release();
}

Widget::ccWidgetTouchCallback CustomWidgetCallbackBindScene::onLocateTouchCallback(const string &callBackName)
{
    if (callBackName == "onTouch")
    {
        return CC_CALLBACK_2(CustomWidgetCallbackBindScene::onTouch, this);
    }

    return nullptr;
}

Widget::ccWidgetClickCallback CustomWidgetCallbackBindScene::onLocateClickCallback(const string &callBackName)
{
    if (callBackName == "onClick")
    {
        return CC_CALLBACK_1(CustomWidgetCallbackBindScene::onClick, this);
    }

    return nullptr;
}

Widget::ccWidgetEventCallback CustomWidgetCallbackBindScene::onLocateEventCallback(const string &callBackName)
{
    if (callBackName == "onEvent")
    {
        return CC_CALLBACK_2(CustomWidgetCallbackBindScene::onEvent, this);
    }
    return nullptr;
}

void CustomWidgetCallbackBindScene::onTouch(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("onTouch");
//    Text* info = dynamic_cast<Text*>(getChildByName("Info"));
//    info->setString(_touchTypes.at((int)type));
}

void CustomWidgetCallbackBindScene::onClick(cocos2d::Ref* sender)
{
    CCLOG("onClick");
//    Text* info = dynamic_cast<Text*>(getChildByName("Info"));
//    info->setString(_click);
}

void CustomWidgetCallbackBindScene::onEvent(cocos2d::Ref* sender, int eventType)
{
    CCLOG("onEvent");
//    Text* info = dynamic_cast<Text*>(getChildByName("Info"));
//    info->setString(_eventTypes.at(eventType));
}
