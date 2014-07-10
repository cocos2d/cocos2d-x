

#include "CustomImageTest.h"
#include "../../CustomGUIScene.h"
#include "../../CustomWidget/CustomImageView.h"
#include "../../CustomWidget/CustomImageViewReader.h"
#include "../../CustomWidget/CustomReader.h"
#include "cocostudio/CCSGUIReader.h"

USING_NS_CC;
USING_NS_CC_EXT;


// CustomImageLayer


void CustomImageLayer::onEnter()
{
    Layer::onEnter();
    
    GUIReader* guiReader = GUIReader::getInstance();
    guiReader->registerTypeAndCallBack("CustomImageView",
                                       &CustomImageView::createInstance,
                                       CustomImageViewReader::getInstance(),
                                       parseselector(CustomImageViewReader::setProperties));
    
    Layout* layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("cocosui/CustomImageViewTest/NewProject_2_1.ExportJson"));
    addChild(layout);        
}


// CustomImageScene


void CustomImageScene::onEnter()
{
    CCScene::onEnter();
    
    auto label = Label::createWithTTF("Back", "fonts/arial.ttf", 20);
    //#endif
    MenuItemLabel* pMenuItem = MenuItemLabel::create(label, CC_CALLBACK_1(CustomImageScene::BackCallback, this));
    
    Menu* pMenu = Menu::create(pMenuItem, nullptr);
    
    pMenu->setPosition( Vec2::ZERO );
    pMenuItem->setPosition( Vec2( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );
    
    addChild(pMenu, 1);
}

void CustomImageScene::runThisTest()
{
    Layer* pLayer = new CustomImageLayer();
    addChild(pLayer);
    pLayer->release();
    
    CCDirector::getInstance()->replaceScene(this);
}

void CustomImageScene::BackCallback(Ref* pSender)
{
    CustomGUITestScene* pScene = new CustomGUITestScene();
    pScene->runThisTest();
    pScene->release();
}
