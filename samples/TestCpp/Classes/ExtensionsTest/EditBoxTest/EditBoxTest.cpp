//
//  CCEditBoxTest.cpp
//  TestCpp
//
//  Created by James on 8/14/12.
//
//

#include "EditBoxTest.h"
#include "../ExtensionsTest.h"

USING_NS_CC;
USING_NS_CC_EXT;


EditBoxTest::EditBoxTest()
{
    CCPoint visibleOrigin = CCEGLView::sharedOpenGLView().getVisibleOrigin();
    CCSize visibleSize = CCEGLView::sharedOpenGLView().getVisibleSize();
    
    CCSprite* pBg = CCSprite::create("Images/HelloWorld.png");
    pBg->setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/2));
    addChild(pBg);
    
    // Back Menu
    CCMenuItemFont *itemBack = CCMenuItemFont::create("Back", this, menu_selector(EditBoxTest::toExtensionsMainLayer));
    itemBack->setPosition(ccp(visibleOrigin.x+visibleSize.width - 50, visibleOrigin.y+25));
    CCMenu *menuBack = CCMenu::create(itemBack, NULL);
    menuBack->setPosition(CCPointZero);
    addChild(menuBack);
    
    CCSize editBoxSize = CCSizeMake(visibleSize.width/3, visibleSize.height/8);
    CCEditBox* pEdit = NULL;
    // top
    pEdit = CCEditBox::create(editBoxSize);
    pEdit->setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/4));
    addChild(pEdit);
    // middle
    pEdit = CCEditBox::create(editBoxSize);
    pEdit->setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/2));
    addChild(pEdit);
    // bottom
    pEdit = CCEditBox::create(editBoxSize);
    pEdit->setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height*3/4));
    addChild(pEdit);
}

EditBoxTest::~EditBoxTest()
{
    
}

void EditBoxTest::toExtensionsMainLayer(cocos2d::CCObject *sender)
{
    ExtensionsTestScene *pScene = new ExtensionsTestScene();
    pScene->runThisTest();
    pScene->release();
}


void runEditBoxTest()
{
    CCScene *pScene = CCScene::create();
    EditBoxTest *pLayer = new EditBoxTest();
    pScene->addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(pScene);
    pLayer->release();
}