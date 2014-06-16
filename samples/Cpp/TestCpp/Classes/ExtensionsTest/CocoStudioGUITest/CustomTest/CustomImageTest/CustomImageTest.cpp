

#include "CustomImageTest.h"
#include "../../CustomGUIScene.h"
#include "../../CustomWidget/CustomImageView.h"
#include "../../CustomWidget/CustomImageViewReader.h"
#include "../../CustomWidget/CustomReader.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#pragma mark -
#pragma mark CustomImageLayer
#pragma mark -
#endif

void CustomImageLayer::onEnter()
{
    CCLayer::onEnter();
    
    GUIReader* guiReader = GUIReader::shareReader();
    guiReader->registerTypeAndCallBack("CustomImageView",
                                       &CustomImageView::createInstance,
                                       CustomImageViewReader::getInstance(),
                                       parseselector(CustomImageViewReader::setProperties));        
    
    Layout* layout = static_cast<Layout*>(GUIReader::shareReader()->
                                          widgetFromBinaryFile
                                          ("cocosui/CustomImageViewTest/NewProject_2_1.csb"));
    addChild(layout);
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#pragma mark -
#pragma mark CustomImageScene
#pragma mark -
#endif

void CustomImageScene::onEnter()
{
    CCScene::onEnter();
    
    CCLabelTTF* label = CCLabelTTF::create("Back", "Arial", 20);
    //#endif
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(CustomImageScene::BackCallback));
    
    CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);
    
    pMenu->setPosition( CCPointZero );
    pMenuItem->setPosition( ccp( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );
    
    addChild(pMenu, 1);
}

void CustomImageScene::runThisTest()
{
    CCLayer* pLayer = new CustomImageLayer();
    addChild(pLayer);
    pLayer->release();
    
    CCDirector::sharedDirector()->replaceScene(this);
}

void CustomImageScene::BackCallback(CCObject* pSender)
{
    CustomGUITestScene* pScene = new CustomGUITestScene();
    pScene->runThisTest();
    pScene->release();
}
