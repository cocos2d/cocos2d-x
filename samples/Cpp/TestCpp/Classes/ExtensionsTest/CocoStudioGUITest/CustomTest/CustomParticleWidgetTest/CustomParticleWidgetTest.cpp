//
//  CustomParticleWidgetTest.cpp
//  CustomUI
//
//  Created by cai wenzhi on 14-3-7.
//
//

#include "CustomParticleWidgetTest.h"
#include "../../CustomGUIScene.h"
#include "../../CustomWidget/CustomParticleWidget.h"
#include "../../CustomWidget/CustomParticleWidgetReader.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#pragma mark -
#pragma mark CustomParticleWidgetLayer
#pragma mark -
#endif

void CustomParticleWidgetLayer::onEnter()
{
    CCLayer::onEnter();
    
    GUIReader* guiReader = GUIReader::shareReader();
    guiReader->registerTypeAndCallBack("CustomParticleWidget",
                                       &CustomParticleWidget::createInstance,
                                       CustomParticleWidgetReader::getInstance(),
                                       parseselector(CustomParticleWidgetReader::setProperties));
    
    TouchGroup* touchGroup = TouchGroup::create();
    addChild(touchGroup);
    
    CustomParticleWidget* custom = CustomParticleWidget::create();
    custom->setParticlePlist("Particles/BoilingFoam.plist");
    touchGroup->addWidget(custom);
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#pragma mark -
#pragma mark CustomImageScene
#pragma mark -
#endif

void CustomParticleWidgetScene::onEnter()
{
    CCScene::onEnter();
    
    CCLayer* pLayer = new CustomParticleWidgetLayer();
    addChild(pLayer);
    pLayer->release();
    
    CCLabelTTF* label = CCLabelTTF::create("Exit", "Arial", 20);
    //#endif
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(CustomParticleWidgetScene::BackCallback));
    
    CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);
    
    pMenu->setPosition( CCPointZero );
    pMenuItem->setPosition( ccp( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );
    
    addChild(pMenu, 1);
}

void CustomParticleWidgetScene::runThisTest()
{
    CCLayer* pLayer = new CustomParticleWidgetLayer();
    addChild(pLayer);
    pLayer->release();
    
    CCDirector::sharedDirector()->replaceScene(this);
}

void CustomParticleWidgetScene::BackCallback(CCObject* pSender)
{
    CustomGUITestScene* pScene = new CustomGUITestScene();
    pScene->runThisTest();
    pScene->release();
}
