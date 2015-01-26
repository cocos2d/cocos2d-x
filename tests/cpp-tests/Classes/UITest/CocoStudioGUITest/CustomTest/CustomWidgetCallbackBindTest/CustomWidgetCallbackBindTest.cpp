

#include "CustomWidgetCallbackBindTest.h"

#include "../../CustomGUIScene.h"
#include "cocostudio/ActionTimeline/CSLoader.h"

#include "base/ObjectFactory.h"

#include "CustomRootNode.h"
#include "CustomRootNodeReader.h"

USING_NS_CC;
using namespace flatbuffers;

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
    CSLoader* instance = CSLoader::getInstance();
    instance->registReaderObject("CustomRootNodeReader",
                                 (ObjectFactory::Instance)CustomRootNodeReader::getInstance);
    
    auto pLayer = CSLoader::createNode("cocosui/CustomTest/CustomWidgetCallbackBindTest/CustomWidgetCallbackBindTest.csb");
    addChild(pLayer);
    
    
    Director::getInstance()->replaceScene(this);
}

void CustomWidgetCallbackBindScene::BackCallback(Ref* pSender)
{
    CustomGUITestScene* pScene = new (std::nothrow) CustomGUITestScene();
    pScene->runThisTest();
    pScene->release();
}