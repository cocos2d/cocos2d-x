#include "EaseActionsTest.h"
#include "../testResource.h"

enum {
	kTagAction1 = 1,
	kTagAction2 = 2,
	kTagSlider = 1,
};

//------------------------------------------------------------------
//
// SpriteEase
//
//------------------------------------------------------------------

void SpriteEase::onEnter()
{
	__super::onEnter();
	
	CCIntervalAction* move = CCMoveBy::actionWithDuration(3, CGPointMake(350,0) );
	CCIntervalAction* move_back = move->reverse();
	
	CCIntervalAction* move_ease_in = CCEaseIn::actionWithAction( dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()), 3.0f);
	CCIntervalAction* move_ease_in_back = move_ease_in->reverse();
	
	CCIntervalAction* move_ease_out = CCEaseOut::actionWithAction( dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()), 3.0f);
	CCIntervalAction* move_ease_out_back = move_ease_out->reverse();
	
	
	CCIntervalAction* seq1 = dynamic_cast<CCIntervalAction*>(CCSequence::actions(move, move_back, NULL));
	CCIntervalAction* seq2 = dynamic_cast<CCIntervalAction*>(CCSequence::actions(move_ease_in, move_ease_in_back, NULL));
	CCIntervalAction* seq3 = dynamic_cast<CCIntervalAction*>(CCSequence::actions(move_ease_out, move_ease_out_back, NULL));
	
	
	CCAction *a2 = m_grossini->runAction( CCRepeatForever::actionWithAction(seq1) );
	a2->setTag(1);

	CCAction *a1 = m_tamara->runAction( CCRepeatForever::actionWithAction(seq2) );
	a1->setTag(1);

	CCAction *a = m_kathia->runAction( CCRepeatForever::actionWithAction(seq3) );
	a->setTag(1);

	schedule(schedule_selector(SpriteEase::testStopAction), 6);
}

void SpriteEase::testStopAction(ccTime dt)
{
	unschedule(schedule_selector(SpriteEase::testStopAction));
	m_tamara->stopActionByTag(1);
	m_kathia->stopActionByTag(1);
	m_grossini->stopActionByTag(1);
}

std::string SpriteEase::title()
{
	return "EaseIn - EaseOut - Stop";
}


//------------------------------------------------------------------
//
// SpriteEaseInOut
//
//------------------------------------------------------------------

void SpriteEaseInOut::onEnter()
{
	__super::onEnter();

	CCIntervalAction*  move = CCMoveBy::actionWithDuration(3, CGPointMake(350,0));
//	id move_back = move->reverse();
	
	CCIntervalAction*  move_ease_inout1 = CCEaseInOut::actionWithAction(dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()), 2.0f);
	CCIntervalAction*  move_ease_inout_back1 = move_ease_inout1->reverse();
	
	CCIntervalAction*  move_ease_inout2 = CCEaseInOut::actionWithAction(dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()), 3.0f);
	CCIntervalAction*  move_ease_inout_back2 = move_ease_inout2->reverse();

	CCIntervalAction*  move_ease_inout3 = CCEaseInOut::actionWithAction(dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()), 4.0f);
	CCIntervalAction*  move_ease_inout_back3 = move_ease_inout3->reverse();

	
	CCIntervalAction*  seq1 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move_ease_inout1, move_ease_inout_back1, NULL));
	CCIntervalAction*  seq2 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move_ease_inout2, move_ease_inout_back2, NULL));
	CCIntervalAction*  seq3 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move_ease_inout3, move_ease_inout_back3, NULL));
		
	m_tamara->runAction( CCRepeatForever::actionWithAction(seq1) );
	m_kathia->runAction( CCRepeatForever::actionWithAction(seq2) );
	m_grossini->runAction( CCRepeatForever::actionWithAction(seq3) );
}


std::string SpriteEaseInOut::title()
{
	return "EaseInOut and rates";
}

//------------------------------------------------------------------
//
// SpriteEaseExponential
//
//------------------------------------------------------------------

void SpriteEaseExponential::onEnter()
{
	__super::onEnter();

	CCIntervalAction* move = CCMoveBy::actionWithDuration(3, CGPointMake(350,0));
	CCIntervalAction* move_back = move->reverse();
	
	CCIntervalAction* move_ease_in = CCEaseExponentialIn::actionWithAction( dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()) );
	CCIntervalAction* move_ease_in_back = move_ease_in->reverse();
	
	CCIntervalAction* move_ease_out = CCEaseExponentialOut::actionWithAction( dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()) );
	CCIntervalAction* move_ease_out_back = move_ease_out->reverse();
	
	
	CCIntervalAction* seq1 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move, move_back, NULL));
	CCIntervalAction* seq2 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move_ease_in, move_ease_in_back, NULL));
	CCIntervalAction* seq3 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move_ease_out, move_ease_out_back, NULL));
	

	m_grossini->runAction( CCRepeatForever::actionWithAction(seq1) );
	m_tamara->runAction( CCRepeatForever::actionWithAction(seq2) );
	m_kathia->runAction( CCRepeatForever::actionWithAction(seq3) );
}


std::string SpriteEaseExponential::title()
{
	return "ExpIn - ExpOut actions";
}
//------------------------------------------------------------------
//
// SpriteEaseExponentialInOut
//
//------------------------------------------------------------------

void SpriteEaseExponentialInOut::onEnter()
{
	__super::onEnter();

	CCIntervalAction* move = CCMoveBy::actionWithDuration(3, CGPointMake(350,0));
	CCIntervalAction* move_back = move->reverse();
	
	CCIntervalAction* move_ease = CCEaseExponentialInOut::actionWithAction( dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()) );
	CCIntervalAction* move_ease_back = move_ease->reverse();	//--> reverse()가 존재하지 않는다.
	
	CCIntervalAction* seq1 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move, move_back, NULL));
	CCIntervalAction* seq2 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move_ease, move_ease_back, NULL));
	
	this->positionForTwo();
	
	m_grossini->runAction( CCRepeatForever::actionWithAction(seq1));
	m_tamara->runAction( CCRepeatForever::actionWithAction(seq2));

}


std::string SpriteEaseExponentialInOut::title()
{
	return "EaseExponentialInOut action";
}
//------------------------------------------------------------------
//
// SpriteEaseSine
//
//------------------------------------------------------------------

void SpriteEaseSine::onEnter()
{
	__super::onEnter();

	CCIntervalAction* move = CCMoveBy::actionWithDuration(3, CGPointMake(350,0));
	CCIntervalAction* move_back = move->reverse();
	
	CCIntervalAction* move_ease_in = CCEaseSineIn::actionWithAction( dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()) );
	CCIntervalAction* move_ease_in_back = move_ease_in->reverse();
	
	CCIntervalAction* move_ease_out = CCEaseSineOut::actionWithAction( dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()) );
	CCIntervalAction* move_ease_out_back = move_ease_out->reverse();
	
	
	CCIntervalAction* seq1 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move, move_back, NULL));
	CCIntervalAction* seq2 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move_ease_in, move_ease_in_back, NULL));
	CCIntervalAction* seq3 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move_ease_out, move_ease_out_back, NULL));
	
	
	m_grossini->runAction( CCRepeatForever::actionWithAction(seq1));
	m_tamara->runAction( CCRepeatForever::actionWithAction(seq2));
	m_kathia->runAction( CCRepeatForever::actionWithAction(seq3));	

}


std::string SpriteEaseSine::title()
{
	return "EaseSineIn - EaseSineOut";
}
//------------------------------------------------------------------
//
// SpriteEaseSineInOut
//
//------------------------------------------------------------------

void SpriteEaseSineInOut::onEnter()
{
	__super::onEnter();

	CCIntervalAction* move = CCMoveBy::actionWithDuration(3, CGPointMake(350,0));
	CCIntervalAction* move_back = move->reverse();
	
	CCIntervalAction* move_ease = CCEaseSineInOut::actionWithAction( dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()) );
	CCIntervalAction* move_ease_back = move_ease->reverse();
	
	CCIntervalAction* seq1 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move, move_back, NULL));
	CCIntervalAction* seq2 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move_ease, move_ease_back, NULL));

	this->positionForTwo();

	m_grossini->runAction( CCRepeatForever::actionWithAction(seq1));
	m_tamara->runAction( CCRepeatForever::actionWithAction(seq2));
}


std::string SpriteEaseSineInOut::title()
{
	return "EaseSineInOut action";
}
//------------------------------------------------------------------
//
// SpriteEaseElastic
//
//------------------------------------------------------------------

void SpriteEaseElastic::onEnter()
{
	__super::onEnter();
	CCIntervalAction* move = CCMoveBy::actionWithDuration(3, CGPointMake(350,0));
	CCIntervalAction* move_back = move->reverse();
	
	CCIntervalAction* move_ease_in = CCEaseElasticIn::actionWithAction( dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()) );
	CCIntervalAction* move_ease_in_back = move_ease_in->reverse();
	
	CCIntervalAction* move_ease_out = CCEaseElasticOut::actionWithAction( dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()) );
	CCIntervalAction* move_ease_out_back = move_ease_out->reverse();

	CCIntervalAction* seq1 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move, move_back, NULL));
	CCIntervalAction* seq2 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move_ease_in, move_ease_in_back, NULL));
	CCIntervalAction* seq3 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move_ease_out, move_ease_out_back, NULL));
	
	m_grossini->runAction( CCRepeatForever::actionWithAction(seq1));
	m_tamara->runAction( CCRepeatForever::actionWithAction(seq2));
	m_kathia->runAction( CCRepeatForever::actionWithAction(seq3));	
}


std::string SpriteEaseElastic::title()
{
	return "Elastic In - Out actions";
}

//------------------------------------------------------------------
//
// SpriteEaseElasticInOut
//
//------------------------------------------------------------------

void SpriteEaseElasticInOut::onEnter()
{
	__super::onEnter();
	
	CCIntervalAction* move = CCMoveBy::actionWithDuration(3, CGPointMake(350,0));

	CCIntervalAction* move_ease_inout1 = CCEaseElasticInOut::actionWithAction(dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()), 0.3f);
	CCIntervalAction* move_ease_inout_back1 = move_ease_inout1->reverse();
	
	CCIntervalAction* move_ease_inout2 = CCEaseElasticInOut::actionWithAction(dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()), 0.45f);
	CCIntervalAction* move_ease_inout_back2 = move_ease_inout2->reverse();
	
	CCIntervalAction* move_ease_inout3 = CCEaseElasticInOut::actionWithAction(dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()), 0.6f);
	CCIntervalAction* move_ease_inout_back3 = move_ease_inout3->reverse();
	
	
	CCIntervalAction* seq1 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move_ease_inout1, move_ease_inout_back1, NULL));
	CCIntervalAction* seq2 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move_ease_inout2, move_ease_inout_back2, NULL));
	CCIntervalAction* seq3 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move_ease_inout3, move_ease_inout_back3, NULL));
	
	m_tamara->runAction( CCRepeatForever::actionWithAction(seq1));
	m_kathia->runAction( CCRepeatForever::actionWithAction(seq2));
	m_grossini->runAction( CCRepeatForever::actionWithAction(seq3)); 
}


std::string SpriteEaseElasticInOut::title()
{
	return "EaseElasticInOut action";
}


//------------------------------------------------------------------
//
// SpriteEaseBounce
//
//------------------------------------------------------------------

void SpriteEaseBounce::onEnter()
{
	__super::onEnter();
	CCIntervalAction* move = CCMoveBy::actionWithDuration(3, CGPointMake(350,0));
	CCIntervalAction* move_back = move->reverse();
	
	CCIntervalAction* move_ease_in = CCEaseBounceIn::actionWithAction( dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()) );
	CCIntervalAction* move_ease_in_back = move_ease_in->reverse();
	
	CCIntervalAction* move_ease_out = CCEaseBounceOut::actionWithAction( dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()) );
	CCIntervalAction* move_ease_out_back = move_ease_out->reverse();
	
	CCIntervalAction* seq1 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move, move_back, NULL));
	CCIntervalAction* seq2 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move_ease_in, move_ease_in_back, NULL));
	CCIntervalAction* seq3 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move_ease_out, move_ease_out_back, NULL));
	
	m_grossini->runAction( CCRepeatForever::actionWithAction(seq1));
	m_tamara->runAction( CCRepeatForever::actionWithAction(seq2));
	m_kathia->runAction( CCRepeatForever::actionWithAction(seq3));	
}


std::string SpriteEaseBounce::title()
{
	return "Bounce In - Out actions";
}


//------------------------------------------------------------------
//
// SpriteEaseBounceInOut
//
//------------------------------------------------------------------

void SpriteEaseBounceInOut::onEnter()
{
	__super::onEnter();

		CCIntervalAction* move = CCMoveBy::actionWithDuration(3, CGPointMake(350,0));
	CCIntervalAction* move_back = move->reverse();
	
	CCIntervalAction* move_ease = CCEaseBounceInOut::actionWithAction( dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()) );
	CCIntervalAction* move_ease_back = move_ease->reverse();
	
	CCIntervalAction* seq1 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move, move_back, NULL));
	CCIntervalAction* seq2 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move_ease, move_ease_back, NULL));
	
	this->positionForTwo();
	
	m_grossini->runAction( CCRepeatForever::actionWithAction(seq1));
	m_tamara->runAction( CCRepeatForever::actionWithAction(seq2));
}


std::string SpriteEaseBounceInOut::title()
{
	return "EaseBounceInOut action";
}

//------------------------------------------------------------------
//
// SpriteEaseBack
//
//------------------------------------------------------------------

void SpriteEaseBack::onEnter()
{
	__super::onEnter();
	CCIntervalAction* move = CCMoveBy::actionWithDuration(3, CGPointMake(350,0));
	CCIntervalAction* move_back = move->reverse();
	
	CCIntervalAction* move_ease_in = CCEaseBackIn::actionWithAction( dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()) );
	CCIntervalAction* move_ease_in_back = move_ease_in->reverse();
	
	CCIntervalAction* move_ease_out = CCEaseBackOut::actionWithAction( dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()) );
	CCIntervalAction* move_ease_out_back = move_ease_out->reverse();
	
	CCIntervalAction* seq1 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move, move_back, NULL));
	CCIntervalAction* seq2 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move_ease_in, move_ease_in_back, NULL));
	CCIntervalAction* seq3 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move_ease_out, move_ease_out_back, NULL));
	
	m_grossini->runAction( CCRepeatForever::actionWithAction(seq1));
	m_tamara->runAction( CCRepeatForever::actionWithAction(seq2));
	m_kathia->runAction( CCRepeatForever::actionWithAction(seq3));	
}


std::string SpriteEaseBack::title()
{
	return "Back In - Out actions";
}

//------------------------------------------------------------------
//
// SpriteEaseBackInOut
//
//------------------------------------------------------------------

void SpriteEaseBackInOut::onEnter()
{
	__super::onEnter();
	CCIntervalAction* move = CCMoveBy::actionWithDuration(3, CGPointMake(350,0));
	CCIntervalAction* move_back = move->reverse();
	
	CCIntervalAction* move_ease = CCEaseBackInOut::actionWithAction( dynamic_cast<CCIntervalAction*>(move->copy()->autorelease()) );
	CCIntervalAction* move_ease_back = move_ease->reverse();
	
	CCIntervalAction* seq1 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move, move_back, NULL));
	CCIntervalAction* seq2 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move_ease, move_ease_back, NULL));
	
	this->positionForTwo();
	
	m_grossini->runAction( CCRepeatForever::actionWithAction(seq1));
	m_tamara->runAction( CCRepeatForever::actionWithAction(seq2));	
}


std::string SpriteEaseBackInOut::title()
{
	return "EaseBackInOut action";
}

//------------------------------------------------------------------
//
// SpeedTest
//
//------------------------------------------------------------------

void SpeedTest::onEnter()
{
	__super::onEnter();

	// rotate and jump
	CCIntervalAction *jump1 = CCJumpBy::actionWithDuration(4, CGPointMake(-400,0), 100, 4);
	CCIntervalAction *jump2 = jump1->reverse();
	CCIntervalAction *rot1 = CCRotateBy::actionWithDuration(4, 360*2);
	CCIntervalAction *rot2 = rot1->reverse();
	
	CCIntervalAction* seq3_1 = dynamic_cast<CCIntervalAction*>(CCSequence::actions(jump2, jump1, NULL));
	CCIntervalAction* seq3_2 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( rot1, rot2, NULL));
	CCIntervalAction* spawn = dynamic_cast<CCIntervalAction*>(CCSpawn::actions(seq3_1, seq3_2, NULL));
	CCSpeed* action = CCSpeed::actionWithAction( CCRepeatForever::actionWithAction(spawn), 1.0f);
	action->setTag(kTagAction1);
	
	CCAction* action2 = dynamic_cast<CCAction*>(action->copy()->autorelease());
	CCAction* action3 = dynamic_cast<CCAction*>(action->copy()->autorelease());

	action2->setTag(kTagAction1);
	action3->setTag(kTagAction1);
	
	m_grossini->runAction( action2 );
	m_tamara->runAction( action3 );
	m_kathia->runAction( action );
	
	this->schedule(schedule_selector(SpeedTest::altertime), 1.0f);//:@selector(altertime:) interval:1.0f];
}

void SpeedTest::altertime(ccTime dt)
{	
	CCSpeed* action1 = dynamic_cast<CCSpeed*>(m_grossini->getActionByTag(kTagAction1));
	CCSpeed* action2 = dynamic_cast<CCSpeed*>(m_tamara->getActionByTag(kTagAction1));
	CCSpeed* action3 = dynamic_cast<CCSpeed*>(m_kathia->getActionByTag(kTagAction1));
	
	action1->setSpeed( CCRANDOM_0_1() * 2 );
	action2->setSpeed( CCRANDOM_0_1() * 2 );
	action3->setSpeed( CCRANDOM_0_1() * 2 );
}

std::string SpeedTest::title()
{
	return "Speed action";
}

//------------------------------------------------------------------
//
// SchedulerTest
//
//------------------------------------------------------------------
void SchedulerTest::onEnter()
{
	__super::onEnter();
	
	// rotate and jump
	CCIntervalAction* jump1 = CCJumpBy::actionWithDuration(4, CGPointMake(-400,0), 100, 4);
	CCIntervalAction* jump2 = jump1->reverse();
	CCIntervalAction* rot1 = CCRotateBy::actionWithDuration(4, 360*2);
	CCIntervalAction* rot2 = rot1->reverse();
	
	CCIntervalAction* seq3_1 = dynamic_cast<CCIntervalAction*>(CCSequence::actions(jump2, jump1, NULL));
	CCIntervalAction* seq3_2 = dynamic_cast<CCIntervalAction*>(CCSequence::actions( rot1, rot2, NULL));
	CCIntervalAction* spawn = dynamic_cast<CCIntervalAction*>(CCSpawn::actions(seq3_1, seq3_2, NULL));
	CCRepeatForever* action = CCRepeatForever::actionWithAction(spawn);
	
	CCRepeatForever* action2 = dynamic_cast<CCRepeatForever*>(action->copy()->autorelease());
	CCRepeatForever* action3 = dynamic_cast<CCRepeatForever*>(action->copy()->autorelease());
	
	
	m_grossini->runAction( CCSpeed::actionWithAction( action, 0.5f) );
	m_tamara->runAction( CCSpeed::actionWithAction( action2, 1.5f) );
	m_kathia->runAction( CCSpeed::actionWithAction( action3, 1.0f) );
	
	CCParticleSystem* emitter = CCParticleFireworks::node();
	addChild(emitter);
	
	//sliderCtl = [self sliderCtl];
	//[[[[Director sharedDirector] openGLView] window] addSubview: sliderCtl]; 
}


std::string SchedulerTest::title()
{
	return "Scheduler scaleTime Test";
}

//------------------------------------------------------------------
//
// EaseSpriteDemo
//
//------------------------------------------------------------------

enum
{
	IDC_NEXT = 100,
	IDC_BACK,
	IDC_RESTART
};

static int sceneIdx = -1; 

#define MAX_LAYER	14

CCLayer* createEaseLayer(int nIndex)
{
	switch(nIndex)
	{
		case 0: return new SpriteEase();
		case 1: return new SpriteEaseInOut();
		case 2: return new SpriteEaseExponential();
		case 3: return new SpriteEaseExponentialInOut();
		case 4: return new SpriteEaseSine();
		case 5: return new SpriteEaseSineInOut();
		case 6: return new SpriteEaseElastic();
		case 7: return new SpriteEaseElasticInOut();
		case 8: return new SpriteEaseBounce();
		case 9: return new SpriteEaseBounceInOut();
		case 10: return new SpriteEaseBack();
		case 11: return new SpriteEaseBackInOut();
		case 12: return new SpeedTest();
		case 13: return new SchedulerTest();
	}


	return NULL;
}

CCLayer* nextEaseAction()
{
	sceneIdx++;
	sceneIdx = sceneIdx % MAX_LAYER;

	CCLayer* pLayer = createEaseLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* backEaseAction()
{
	sceneIdx--;
	int total = MAX_LAYER;
	if( sceneIdx < 0 )
		sceneIdx += total;	
	
	CCLayer* pLayer = createEaseLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* restartEaseAction()
{
	CCLayer* pLayer = createEaseLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
} 


EaseSpriteDemo::EaseSpriteDemo(void)
{
}

EaseSpriteDemo::~EaseSpriteDemo(void)
{
	m_grossini->release();
	m_tamara->release();
	m_kathia->release();
}

void EaseSpriteDemo::positionForTwo()
{	
	m_grossini->setPosition( CGPointMake( 60, 120 ) );
	m_tamara->setPosition( CGPointMake( 60, 220) );
	m_kathia->setIsVisible(false);
}


std::string EaseSpriteDemo::title()
{
	return "No title";
}

void EaseSpriteDemo::onEnter()
{
	__super::onEnter();

	// Example:
	// You can create a sprite using a Texture2D
	CCTexture2D* tex = new CCTexture2D();
	UIImage* pImage = new UIImage();
	
	if(pImage->initWithContentsOfFile(CCFileUtils::fullPathFromRelativePath(s_pPathGrossini)))
	{
		tex->initWithImage(pImage);
		m_grossini = CCSprite::spriteWithTexture(tex); 
		m_grossini->retain();

	}

	tex->release();
	delete pImage;
	
	// Example:
	// Or you can create an sprite using a filename. PNG and BMP files are supported. Probably TIFF too
	m_tamara = CCSprite::spriteWithFile(s_pPathSister1); m_tamara->retain();
	m_kathia = CCSprite::spriteWithFile(s_pPathSister2); m_kathia->retain();
	
	addChild( m_grossini, 3);
	addChild( m_kathia, 2);
	addChild( m_tamara, 1);

	CGSize s = CCDirector::getSharedDirector()->getWinSize();

	m_grossini->setPosition( CGPointMake(60, 50) );
	m_kathia->setPosition( CGPointMake(60, 150) );
	m_tamara->setPosition( CGPointMake(60, 250) );

	CCLabel* label = CCLabel::labelWithString(title().c_str(), "Arial", 32);
	addChild(label);
	label->setPosition( CGPointMake(s.width/2, s.height-50) );

	CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(EaseSpriteDemo::backCallback) );
	CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage(s_pPathR1, s_pPathR2, this, menu_selector(EaseSpriteDemo::restartCallback) );
	CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage(s_pPathF1, s_pPathF2, this, menu_selector(EaseSpriteDemo::nextCallback) );

	CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);

	menu->setPosition( CGPointZero );
	item1->setPosition( CGPointMake( s.width/2 - 100,30) );
	item2->setPosition( CGPointMake( s.width/2, 30) );
	item3->setPosition( CGPointMake( s.width/2 + 100,30) );
	
	addChild(menu, 1);	
}

void EaseSpriteDemo::restartCallback(NSObject* pSender)
{
	CCScene* s = new EaseActionsTestScene();//CCScene::node();
	s->addChild(restartEaseAction()); 

	CCDirector::getSharedDirector()->replaceScene(s);
}

void EaseSpriteDemo::nextCallback(NSObject* pSender)
{
	CCScene* s = new EaseActionsTestScene();//CCScene::node();
	s->addChild( nextEaseAction() );
	CCDirector::getSharedDirector()->replaceScene(s);
}

void EaseSpriteDemo::backCallback(NSObject* pSender)
{
	CCScene* s = new EaseActionsTestScene();//CCScene::node();
	s->addChild( backEaseAction() );
	CCDirector::getSharedDirector()->replaceScene(s);
}

void EaseActionsTestScene::runThisTest()
{
    CCLayer* pLayer = nextEaseAction();
    addChild(pLayer);

    CCDirector::getSharedDirector()->replaceScene(this);
}
