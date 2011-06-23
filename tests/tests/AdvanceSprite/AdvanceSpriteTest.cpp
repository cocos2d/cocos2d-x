//
//  AdvanceSpriteTest.cpp
//  test
//
//  Created by varadharaj on 16/06/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "AdvanceSpriteTest.h"

void AdvanceSpriteScene::runThisTest()
{
    CCLayer* pLayer = new AdvanceSpriteTest();
    addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();
}

AdvanceSpriteTest::AdvanceSpriteTest()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 28);
	addChild(label, 0);
	label->setPosition( ccp(s.width/2, s.height-50) );
   
    m_pAdvanceSprite = new AdvanceSprite();
    m_pAdvanceSprite->setPosition(ccp(s.width/2,s.height/2));
    
    addChild(m_pAdvanceSprite);
    m_pAdvanceSprite->addFrames("animations/grossini-aliases.plist", "animations/grossini-aliases.png");
    m_pAdvanceSprite->startAnimation(1, 14, -1, 0, this, 5, false, false);
}

void AdvanceSpriteTest::onEnter()
{
    
}

std::string AdvanceSpriteTest::title()
{
    return "AdvanceSprite Test";
}

AdvanceSpriteTest::~AdvanceSpriteTest()
{
    
}