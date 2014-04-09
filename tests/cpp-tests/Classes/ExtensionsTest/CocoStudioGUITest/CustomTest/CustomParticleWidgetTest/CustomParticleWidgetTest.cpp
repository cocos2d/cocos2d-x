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
#include "cocostudio/CCSGUIReader.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocostudio;


// CustomParticleWidgetLayer


void CustomParticleWidgetLayer::onEnter()
{
    CCLayer::onEnter();
    
    GUIReader* guiReader = GUIReader::getInstance();
    guiReader->registerTypeAndCallBack("CustomParticleWidget",
                                       &CustomParticleWidget::createInstance,
                                       CustomParticleWidgetReader::getInstance(),
                                       parseselector(CustomParticleWidgetReader::setProperties));
    
    CustomParticleWidget* custom = CustomParticleWidget::create();
    custom->setParticlePlist("Particles/BoilingFoam.plist");
    
    addChild(custom, 10, -1);
}


// CustomImageScene


void CustomParticleWidgetScene::onEnter()
{
    CCScene::onEnter();
    
    Layer* pLayer = new CustomParticleWidgetLayer();
    addChild(pLayer);
    pLayer->release();
    
    auto label = Label::createWithTTF("Back", "fonts/arial.ttf", 20);
    //#endif
    MenuItemLabel* pMenuItem = MenuItemLabel::create(label, CC_CALLBACK_1(CustomParticleWidgetScene::BackCallback, this));
    
    Menu* pMenu = Menu::create(pMenuItem, NULL);
    
    pMenu->setPosition( Point::ZERO );
    pMenuItem->setPosition( Point( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );
    
    addChild(pMenu, 1);
}

void CustomParticleWidgetScene::runThisTest()
{
    Layer* pLayer = new CustomParticleWidgetLayer();
    addChild(pLayer);
    pLayer->release();
    
    CCDirector::getInstance()->replaceScene(this);
}

void CustomParticleWidgetScene::BackCallback(Ref* pSender)
{
    CustomGUITestScene* pScene = new CustomGUITestScene();
    pScene->runThisTest();
    pScene->release();
}
