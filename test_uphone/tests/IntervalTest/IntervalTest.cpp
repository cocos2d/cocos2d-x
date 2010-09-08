#include "IntervalTest.h"
#include "../testResource.h"

#define SID_STEP1	100
#define SID_STEP2	101
#define SID_STEP3	102

#define IDC_PAUSE	200



IntervalLayer::IntervalLayer()
{
	m_time1 = m_time2 = m_time3 = 0.0f;

	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	// sun
	CCParticleSystem* sun = CCParticleSun::node();
	sun->setPosition( CGPointMake(s.width-32,s.height-32) );

	sun->setTotalParticles(130);
	sun->setLife(0.6f);
	this->addChild(sun);

	// timers
	m_label1 = CCBitmapFontAtlas::bitmapFontAtlasWithString("0", "fonts/bitmapFontTest4.fnt");
	m_label2 = CCBitmapFontAtlas::bitmapFontAtlasWithString("0", "fonts/bitmapFontTest4.fnt");
	m_label3 = CCBitmapFontAtlas::bitmapFontAtlasWithString("0", "fonts/bitmapFontTest4.fnt");
	
	schedule(schedule_selector(IntervalLayer::step1), 0.5f);
	schedule(schedule_selector(IntervalLayer::step2), 1.0f);
	schedule(schedule_selector(IntervalLayer::step3), 1.5f);
	
	m_label1->setPosition( CGPointMake(80,s.width/2) );
	m_label2->setPosition( CGPointMake(240,s.width/2) );
	m_label3->setPosition( CGPointMake(400,s.width/2) );
	
	addChild(m_label1);
	addChild(m_label2);
	addChild(m_label3);
	
	// Sprite
	CCSprite* sprite = CCSprite::spriteWithFile(s_pPathGrossini);
	sprite->setPosition( CGPointMake(40,50) );
	
	CCJumpBy* jump = CCJumpBy::actionWithDuration(3, CGPointMake(400,0), 50, 4);
	
	addChild(sprite);
	sprite->runAction( CCRepeatForever::actionWithAction(
															(CCIntervalAction*)(CCSequence::actions(jump, jump->reverse(), NULL ))
														)
					 );
	// pause button
	CCMenuItem* item1 = CCMenuItemFont::itemFromString("Pause", this, menu_selector(IntervalLayer::onPause) );
	CCMenu* menu = CCMenu::menuWithItems(item1, NULL);
	menu->setPosition( CGPointMake(s.height-50, 270) );

	addChild( menu );
}

void IntervalLayer::onPause(NSObject* pSender)
{
	if(CCDirector::getSharedDirector()->isPaused())
		CCDirector::getSharedDirector()->resume(); 
	else
		CCDirector::getSharedDirector()->pause(); 

}

void IntervalLayer::step1(ccTime dt)
{
	m_time1 +=1;

    char str[5] = {0};
    sprintf(str, "%2.1f", m_time1);
	m_label1->setString( str );
}

void IntervalLayer::step2(ccTime dt)
{
	m_time2 +=1;

    char str[5] = {0};
    sprintf(str, "%2.1f", m_time2);
    m_label2->setString( str ); 
}

void IntervalLayer::step3(ccTime dt)
{
	m_time3 +=1;

    char str[5] = {0};
    sprintf(str, "%2.1f", m_time3);
    m_label3->setString( str ); 
}

void IntervalTestScene::runThisTest()
{
    CCLayer* pLayer = new IntervalLayer();
    addChild(pLayer);

    CCDirector::getSharedDirector()->replaceScene(this);
}
