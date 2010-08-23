#include "ParticleTest.h"
#include "CCIntervalAction.h"
#include "CCMenu.h"
#include "CCLabel.h"
#include "CCLabelAtlas.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "../testResource.h"
#include "support/CGPointExtension.h"

enum 
{
	kTagLabelAtlas = 1,
};

//------------------------------------------------------------------
//
// DemoFirework
//
//------------------------------------------------------------------
void DemoFirework::onEnter()
{
	__super::onEnter();

	m_emitter = CCParticleFireworks::node();
	m_background->addChild(m_emitter, 10);
	
    m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_stars1) );
	
	setEmitterPosition();
}

std::string DemoFirework::title()
{
	return "ParticleFireworks";
}


//------------------------------------------------------------------
//
// DemoFire
//
//------------------------------------------------------------------
void DemoFire::onEnter()
{
	__super::onEnter();

	m_emitter = CCParticleFire::node();
	m_background->addChild(m_emitter, 10);
	
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_fire) );//.pvr"];
	CGPoint p = m_emitter->getPosition();
	m_emitter->setPosition( CGPointMake(p.x, 100) );
	
	setEmitterPosition();
}

std::string DemoFire::title()
{
	return "ParticleFire";
}

//------------------------------------------------------------------
//
// DemoSun
//
//------------------------------------------------------------------
void DemoSun::onEnter()
{
	__super::onEnter();

	m_emitter = CCParticleSun::node();
	m_background->addChild(m_emitter, 10);

	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_fire) );
	
	setEmitterPosition();
}

std::string DemoSun::title()
{
	return "ParticleSun";
}

//------------------------------------------------------------------
//
// DemoGalaxy
//
//------------------------------------------------------------------
void DemoGalaxy::onEnter()
{
	__super::onEnter();

	m_emitter = CCParticleGalaxy::node();
	m_background->addChild(m_emitter, 10);
	
    m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_fire) );
	
	setEmitterPosition(); 
}

std::string DemoGalaxy::title()
{
	return "ParticleGalaxy";
}

//------------------------------------------------------------------
//
// DemoFlower
//
//------------------------------------------------------------------
void DemoFlower::onEnter()
{
	__super::onEnter();

	m_emitter = CCParticleFlower::node();
	m_background->addChild(m_emitter, 10);
    m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_stars1) );
	
	setEmitterPosition();
}

std::string DemoFlower::title()
{
	return "ParticleFlower";
}

//------------------------------------------------------------------
//
// DemoBigFlower
//
//------------------------------------------------------------------
void DemoBigFlower::onEnter()
{
	__super::onEnter();

	m_emitter = new CCQuadParticleSystem();
	m_emitter->initWithTotalParticles(50);
	//m_emitter->autorelease();

	m_background->addChild(m_emitter, 10);
	m_emitter->release();	// win32 :  use this line or remove this line and use autorelease()
    m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_star1_scale) );

	m_emitter->setDuration(-1);
	
	// gravity
	m_emitter->setGravity(CGPointZero);
	
	// angle
	m_emitter->setAngle(90);
	m_emitter->setAngleVar(360);
	
	// speed of particles
	m_emitter->setSpeed(160);
	m_emitter->setSpeedVar(20);
	
	// radial
	m_emitter->setRadialAccel(-120);
	m_emitter->setRadialAccelVar(0);
	
	// tagential
	m_emitter->setTangentialAccel(30);
	m_emitter->setTangentialAccelVar(0);
	
	// emitter position
	m_emitter->setPosition( CGPointMake(160,240) );
	m_emitter->setPosVar(CGPointZero);
	
	// life of particles
	m_emitter->setLife(4);
	m_emitter->setLifeVar(1);
	
	// spin of particles
	m_emitter->setStartSpin(0);
	m_emitter->setStartSizeVar(0);
	m_emitter->setEndSpin(0);
	m_emitter->setEndSpinVar(0);
	
	// color of particles
	ccColor4F startColor = {0.5f, 0.5f, 0.5f, 1.0f};
	m_emitter->setStartColor(startColor);
	
	ccColor4F startColorVar = {0.5f, 0.5f, 0.5f, 1.0f};
	m_emitter->setStartColorVar(startColorVar);
	
	ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
	m_emitter->setEndColor(endColor);
	
	ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};	
	m_emitter->setEndColorVar(endColorVar);
	
	// size, in pixels
	m_emitter->setStartSize(80.0f);
	m_emitter->setStartSizeVar(40.0f);
	m_emitter->setEndSize(kParticleStartSizeEqualToEndSize);
	
	// emits per second
	m_emitter->setEmissionRate(m_emitter->getTotalParticles()/m_emitter->getLife());
	
	// additive
	m_emitter->setIsBlendAdditive(true);

	setEmitterPosition();
}

std::string DemoBigFlower::title()
{
	return "ParticleBigFlower";
}

//------------------------------------------------------------------
//
// DemoRotFlower
//
//------------------------------------------------------------------
void DemoRotFlower::onEnter()
{
	__super::onEnter();

	m_emitter = new CCQuadParticleSystem();
	m_emitter->initWithTotalParticles(300);
	//m_emitter->autorelease();

	m_background->addChild(m_emitter, 10);
	m_emitter->release();	// win32 : Remove this line
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_star2_scale) );
	
	// duration
	m_emitter->setDuration(-1);
	
	// gravity
	m_emitter->setGravity(CGPointZero);
	
	// angle
	m_emitter->setAngle(90);
	m_emitter->setAngleVar(360);
	
	// speed of particles
	m_emitter->setSpeed(160);
	m_emitter->setSpeedVar(20);
	
	// radial
	m_emitter->setRadialAccel(-120);
	m_emitter->setRadialAccelVar(0);
	
	// tagential
	m_emitter->setTangentialAccel(30);
	m_emitter->setTangentialAccelVar(0);
	
	// emitter position
	m_emitter->setPosition( CGPointMake(160,240) );
	m_emitter->setPosVar(CGPointZero);
	
	// life of particles
	m_emitter->setLife(3);
	m_emitter->setLifeVar(1);

	// spin of particles
	m_emitter->setStartSpin(0);
	m_emitter->setStartSpinVar(0);
	m_emitter->setEndSpin(0);
	m_emitter->setEndSpinVar(2000);
	
	// color of particles
	ccColor4F startColor = {0.5f, 0.5f, 0.5f, 1.0f};
	m_emitter->setStartColor(startColor);
	
	ccColor4F startColorVar = {0.5f, 0.5f, 0.5f, 1.0f};
	m_emitter->setStartColorVar(startColorVar);
	
	ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
	m_emitter->setEndColor(endColor);
	
	ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};	
	m_emitter->setEndColorVar(endColorVar);

	// size, in pixels
	m_emitter->setStartSize(30.0f);
	m_emitter->setStartSizeVar(00.0f);
	m_emitter->setEndSize(kParticleStartSizeEqualToEndSize);
	
	// emits per second
	m_emitter->setEmissionRate(m_emitter->getTotalParticles()/m_emitter->getLife());

	// additive
	m_emitter->setIsBlendAdditive(false);
	
	setEmitterPosition();
}

std::string DemoRotFlower::title()
{
	return "ParticleRotFlower";
}

//------------------------------------------------------------------
//
// DemoMeteor
//
//------------------------------------------------------------------
void DemoMeteor::onEnter()
{
	__super::onEnter();

	m_emitter = CCParticleMeteor::node();
	m_background->addChild(m_emitter, 10);
	
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_fire) );
	
	setEmitterPosition();
}

std::string DemoMeteor::title()
{
	return "ParticleMeteor";
}

//------------------------------------------------------------------
//
// DemoSpiral
//
//------------------------------------------------------------------
void DemoSpiral::onEnter()
{
	__super::onEnter();

	m_emitter = CCParticleSpiral::node();
	m_background->addChild(m_emitter, 10);
	
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_fire) );
	
	setEmitterPosition();
}

std::string DemoSpiral::title()
{
	return "ParticleSpiral";
}

//------------------------------------------------------------------
//
// DemoExplosion
//
//------------------------------------------------------------------
void DemoExplosion::onEnter()
{
	__super::onEnter();

	m_emitter = CCParticleExplosion::node();
	m_background->addChild(m_emitter, 10);
	
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_star1_scale) );
	
	m_emitter->setIsAutoRemoveOnFinish(true);
	
	setEmitterPosition();
}

std::string DemoExplosion::title()
{
	return "ParticleExplosion";
}

//------------------------------------------------------------------
//
// DemoSmoke
//
//------------------------------------------------------------------
void DemoSmoke::onEnter()
{
	__super::onEnter();

	m_emitter = CCParticleSmoke::node();
	m_background->addChild(m_emitter, 10);
	
	CGPoint p = m_emitter->getPosition();
	m_emitter->setPosition( CGPointMake( p.x, 100) );
	
	setEmitterPosition();
}

std::string DemoSmoke::title()
{
	return "ParticleSmoke";
}

//------------------------------------------------------------------
//
// DemoSnow
//
//------------------------------------------------------------------
void DemoSnow::onEnter()
{
	__super::onEnter();

	m_emitter = CCParticleSnow::node();
	m_background->addChild(m_emitter, 10);
	
	CGPoint p = m_emitter->getPosition();
	m_emitter->setPosition( CGPointMake( p.x, p.y-110) );
// 	m_emitter->m_life = 3;
// 	m_emitter->m_lifeVar = 1;
// 	
// 	// gravity
// 	m_emitter->m_gravity = CGPointMake(0,-10);
// 		
// 	// speed of particles
// 	m_emitter->m_speed = 130;
// 	m_emitter->m_speedVar = 30;
// 	
// 	
// 	ccColor4F startColor = m_emitter->m_startColor;
// 	startColor.r = 0.9f;
// 	startColor.g = 0.9f;
// 	startColor.b = 0.9f;
// 	m_emitter->m_startColor = startColor;
// 	
// 	ccColor4F startColorVar = m_emitter->m_startColorVar;
// 	startColorVar.b = 0.1f;
// 	m_emitter->m_startColorVar = startColorVar;
// 	
// 	m_emitter->m_emissionRate = m_emitter->m_totalParticles/m_emitter->m_life;
	
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_snow) );
	
	setEmitterPosition();
}

std::string DemoSnow::title()
{
	return "ParticleSnow";
}

//------------------------------------------------------------------
//
// DemoRain
//
//------------------------------------------------------------------
void DemoRain::onEnter()
{
	__super::onEnter();

	m_emitter = CCParticleRain::node();
	m_background->addChild(m_emitter, 10);
	
	CGPoint p = m_emitter->getPosition();
	m_emitter->setPosition( CGPointMake( p.x, p.y-100) );
	m_emitter->setLife(4);
	
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_fire) );
	
	setEmitterPosition();
}

std::string DemoRain::title()
{
	return "ParticleRain";
}

//------------------------------------------------------------------
//
// DemoModernArt
//
//------------------------------------------------------------------
void DemoModernArt::onEnter()
{
	__super::onEnter();

	m_emitter = new CCPointParticleSystem();
	m_emitter->initWithTotalParticles(1000);
	//m_emitter->autorelease();

	m_background->addChild(m_emitter, 10);
	m_emitter->release();
	
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
// 	
// 	// duration
// 	m_emitter->m_duration = -1;
// 	
// 	// gravity
// 	m_emitter->m_gravity = CGPointMake(0,0);
// 	
// 	// angle
// 	m_emitter->m_angle = 0;
// 	m_emitter->m_angleVar = 360;
// 	
// 	// radial
// 	m_emitter->m_radialAccel = 70;
// 	m_emitter->m_radialAccelVar = 10;
// 	
// 	// tagential
// 	m_emitter->m_tangentialAccel = 80;
// 	m_emitter->m_tangentialAccelVar = 0;
// 	
// 	// speed of particles
// 	m_emitter->m_speed = 50;
// 	m_emitter->m_speedVar = 10;
// 	
// 	// emitter position
// 	m_emitter->setPosition( CGPointMake( s.width/2, s.height/2) );
// 	m_emitter->m_posVar = CGPointZero;
// 	
// 	// life of particles
// 	m_emitter->m_life = 2.0f;
// 	m_emitter->m_lifeVar = 0.3f;
// 	
// 	// emits per frame
// 	m_emitter->m_emissionRate = m_emitter->m_totalParticles/m_emitter->m_life;
// 	
// 	// color of particles
// 	ccColor4F startColor = {0.5f, 0.5f, 0.5f, 1.0f};
// 	m_emitter->m_startColor = startColor;
// 	
// 	ccColor4F startColorVar = {0.5f, 0.5f, 0.5f, 1.0f};
// 	m_emitter->m_startColorVar = startColorVar;
// 	
// 	ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
// 	m_emitter->m_endColor = endColor;
// 	
// 	ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};	
// 	m_emitter->m_endColorVar = endColorVar;
// 	
// 	// size, in pixels
// 	m_emitter->m_startSize = 1.0f;
// 	m_emitter->m_startSizeVar = 1.0f;
// 	m_emitter->m_endSize = 32.0f;
// 	m_emitter->m_endSizeVar = 8.0f;
// 	
	// texture
	//m_emitter.texture = [[TextureMgr sharedTextureMgr] addImage("images/fire.png"];
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_fire_scale) );
	
	// additive
	m_emitter->setIsBlendAdditive(false);
	
	setEmitterPosition();
}

std::string DemoModernArt::title()
{
	return "Varying size";
}

//------------------------------------------------------------------
//
// DemoRing 
//
//------------------------------------------------------------------
void DemoRing::onEnter()
{
	__super::onEnter();

	m_emitter = CCParticleFlower::node();

	m_background->addChild(m_emitter, 10);

	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_star1_scale) );
// 	m_emitter->m_lifeVar = 0;
// 	m_emitter->m_life = 10;
// 	m_emitter->m_speed = 100;
// 	m_emitter->m_speedVar = 0;
// 	m_emitter->m_emissionRate = 10000;
	
	setEmitterPosition();
}

std::string DemoRing::title()
{
	return "Ring Demo";
}

//------------------------------------------------------------------
//
// ParallaxParticle
//
//------------------------------------------------------------------
void ParallaxParticle::onEnter()
{
	__super::onEnter();
// 	
// 	m_background->getParent()->removeChild(m_background, true);
// 
// 	CCParallaxNode* p = CCParallaxNode::node(); 
// 	addChild(p, 5);
// 
// 	CCSprite *p1 = CCSprite::spriteWithFile(s_back3);
// 	CCSprite *p2 = CCSprite::spriteWithFile(s_back3);
// 	
// 	p->addChild( p1, 1, CGPointMake(0.5f,1), CGPointMake(0,250) );
// 	p->addChild(p2, 2, CGPointMake(1.5f,1), CGPointMake(0,50) );
// 
// 	m_emitter = CCParticleFlower::node();
// 
// 	p1->addChild(m_emitter, 10);
// 	m_emitter->setPosition( CGPointMake(250,200) );
// 	
// 	CCParticleSun* par = CCParticleSun::node();
// 	p2->addChild(par, 10);
// 	
// 	CCIntervalAction* move = CCMoveBy::actionWithDuration(4, CGPointMake(300,0));
// 	CCIntervalAction* move_back = move->reverse();
// 	CCIntervalAction* seq = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move, move_back, NULL));
// 	p->runAction( CCRepeatForever::actionWithAction( seq ) );	
}

std::string ParallaxParticle::title()
{
	return "Parallax + Particles";
}

//------------------------------------------------------------------
//
// ParticleDemo
//
//------------------------------------------------------------------

enum
{
	IDC_NEXT = 100,
	IDC_BACK,
	IDC_RESTART,
	IDC_TOGGLE
};

static int sceneIdx = -1; 

#define MAX_LAYER	16

CCLayer* createParticleLayer(int nIndex)
{
	switch(nIndex)
	{
		case 0: return new DemoFlower();
		case 1: return new DemoGalaxy();
		case 2: return new DemoFirework();
		case 3: return new DemoSpiral();
		case 4: return new DemoSun();
		case 5: return new DemoMeteor();
		case 6: return new DemoFire();
		case 7: return new DemoSmoke();
		case 8: return new DemoExplosion();
		case 9: return new DemoSnow();
		case 10: return new DemoRain();
		case 11: return new DemoBigFlower();
		case 12: return new DemoRotFlower();
		case 13: return new DemoModernArt();
		case 14: return new DemoRing();
		case 15: return new ParallaxParticle();
	}

	return NULL;
}


CCLayer* nextParticleAction()
{
	sceneIdx++;
	sceneIdx = sceneIdx % MAX_LAYER;

	CCLayer* pLayer = createParticleLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* backParticleAction()
{
	sceneIdx--;
	int total = MAX_LAYER;
	if( sceneIdx < 0 )
		sceneIdx += total;	
	
	CCLayer* pLayer = createParticleLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* restartParticleAction()
{
	CCLayer* pLayer = createParticleLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
} 


ParticleDemo::ParticleDemo(void)
{
	initWithColor( ccc4(127,127,127,255) );

	m_emitter = NULL;

	setIsTouchEnabled( true );
	
	CGSize s = CCDirector::getSharedDirector()->getWinSize();
	CCLabel* label = CCLabel::labelWithString(title().c_str(), "Arial", 28);
	addChild(label, 100, 1000);
	label->setPosition( CGPointMake(s.width/2, s.height-50) );
	
	CCLabel *tapScreen = CCLabel::labelWithString("(Tap the Screen)", "Arial", 20);
	tapScreen->setPosition( CGPointMake(s.width/2, s.height-80) );
	addChild(tapScreen, 100);
	
	CCMenuItemImage* item1 = CCMenuItemImage::itemFromNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(ParticleDemo::backCallback) );
	CCMenuItemImage* item2 = CCMenuItemImage::itemFromNormalImage(s_pPathR1, s_pPathR2, this, menu_selector(ParticleDemo::restartCallback) );
	CCMenuItemImage* item3 = CCMenuItemImage::itemFromNormalImage(s_pPathF1, s_pPathF2,  this, menu_selector(ParticleDemo::nextCallback) );
	
	CCMenuItemToggle* item4 = CCMenuItemToggle::itemWithTarget(	this, 
																menu_selector(ParticleDemo::toggleCallback), 
																CCMenuItemFont::itemFromString( "Free Movement" ),
																CCMenuItemFont::itemFromString( "Grouped Movement" ),
																NULL );
	
	CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, item4, NULL);
		
	menu->setPosition( CGPointZero );
	item1->setPosition( CGPointMake( s.width/2 - 100,30) );
	item2->setPosition( CGPointMake( s.width/2, 30) );
	item3->setPosition( CGPointMake( s.width/2 + 100,30) );
	item4->setPosition( CGPointMake( 0, 100) );
	item4->setAnchorPoint( CGPointMake(0,0) );

	addChild( menu, 100 );	
	
	CCLabel* labelAtlas = CCLabel::labelWithString("0000", "fonts", 16);
	addChild(labelAtlas, 100, kTagLabelAtlas);
	labelAtlas->setPosition( CGPointMake(254,50) );
	
	// moving background
	m_background = CCSprite::spriteWithFile(s_back3);
	addChild(m_background, 5);
	m_background->setPosition( CGPointMake(s.width/2, s.height-180) );

	CCIntervalAction* move = CCMoveBy::actionWithDuration(4, CGPointMake(300,0) );
	CCIntervalAction* move_back = move->reverse();
	CCIntervalAction* seq = dynamic_cast<CCIntervalAction*>(CCSequence::actions( move, move_back, NULL ));
	m_background->runAction( CCRepeatForever::actionWithAction(seq) );
	
	
	schedule( schedule_selector(ParticleDemo::step) );
}

ParticleDemo::~ParticleDemo(void)
{
	//m_emitter->release(); 
}

void ParticleDemo::onEnter(void)
{
	__super::onEnter();

	CCLabel* pLabel = dynamic_cast<CCLabel*>(this->getChildByTag(1000));
	pLabel->setString(title().c_str());
}

std::string ParticleDemo::title()
{
	return "No title";
}

void ParticleDemo::registerWithTouchDispatcher()
{
    CCTouchDispatcher::getSharedDispatcher()->addTargetedDelegate(this, 0, false);
}

bool ParticleDemo::ccTouchBegan(CCTouch* touch, UIEvent* event)
{
	return true;
}

void ParticleDemo::ccTouchMoved(CCTouch* touch, UIEvent* event)
{
	return ccTouchEnded(touch, event);
}

void ParticleDemo::ccTouchEnded(CCTouch* touch, UIEvent* event)
{
	CGPoint location = touch->locationInView( touch->view() );
	CGPoint convertedLocation = CCDirector::getSharedDirector()->convertToGL(location);
	
	CGPoint	pos = m_background->convertToWorldSpace(CGPointZero);
	m_emitter->setPosition( ccpSub(convertedLocation, pos) );	
}

void ParticleDemo::step(ccTime dt)
{
// 	CCLabel* atlas = (CCLabel*)getChildByTag(kTagLabelAtlas);
// 
//     char str[5] = {0};
// 	//std::string str;
//     sprintf(str, "%4d", m_emitter->getParticleCount());
// 	//str.format("%4d", m_emitter->getParticleCount());
// 	atlas->setString(str);
}

void ParticleDemo::toggleCallback(NSObject* pSender)
{
	if( m_emitter->getPositionType() == kCCPositionTypeGrouped )
		m_emitter->setPositionType( kCCPositionTypeFree );
	else
		m_emitter->setPositionType( kCCPositionTypeGrouped );
}

void ParticleDemo::restartCallback(NSObject* pSender)
{
	m_emitter->resetSystem(); 
}

void ParticleDemo::nextCallback(NSObject* pSender)
{
	CCScene* s = CCScene::node();
	s->addChild( nextParticleAction() );
	CCDirector::getSharedDirector()->replaceScene(s);
}

void ParticleDemo::backCallback(NSObject* pSender)
{
	CCScene* s = CCScene::node();
	s->addChild( backParticleAction() );
	CCDirector::getSharedDirector()->replaceScene(s);
} 

void ParticleDemo::setEmitterPosition()
{
	m_emitter->setPosition( CGPointMake(200, 70) );
}

void ParticleTestScene::runThisTest()
{
    addChild(nextParticleAction());

    CCDirector::getSharedDirector()->replaceScene(this);
}
