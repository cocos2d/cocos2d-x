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
#include "../../CustomWidget/CustomImageViewReader.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

#pragma mark -
#pragma mark CustomParticleWidgetLayer
#pragma mark -

void CustomParticleWidgetLayer::onEnter()
{
    CCLayer::onEnter();
    
    GUIReader* guiReader = GUIReader::shareReader();
    guiReader->registerTypeAndCallBack("CustomParticleWidget",
                                       &CustomParticleWidget::createInstance,
                                       CustomImageViewReader::getInstance(),
                                       parseselector(CustomImageViewReader::setProperties));
    
    TouchGroup* touchGroup = TouchGroup::create();
    addChild(touchGroup);
    
    CustomParticleWidget* custom = CustomParticleWidget::create();
    custom->setParticlePlist("Particles/BoilingFoam.plist");
    touchGroup->addWidget(custom);
}

#pragma mark -
#pragma mark CustomImageScene
#pragma mark -

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
