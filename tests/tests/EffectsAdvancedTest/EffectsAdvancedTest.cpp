#include "EffectsAdvancedTest.h"

enum 
{
	kTagTextLayer = 1,

	kTagSprite1 = 1,
	kTagSprite2 = 2,

	kTagBackground = 1,
	kTagLabel = 2,
};

//------------------------------------------------------------------
//
// Effect1
//
//------------------------------------------------------------------
void Effect1::onEnter()
{
	EffectAdvanceTextLayer::onEnter();

	CCNode* target = getChildByTag(kTagBackground);
	
	// To reuse a grid the grid size and the grid type must be the same.
	// in this case:
	//     Lens3D is Grid3D and it's size is (15,10)
	//     Waves3D is Grid3D and it's size is (15,10)
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCActionInterval* lens = CCLens3D::actionWithPosition(ccp(size.width/2,size.height/2), 240, ccg(15,10), 0.0f);
	CCActionInterval* waves = CCWaves3D::actionWithWaves(18, 15, ccg(15,10), 10);

	CCFiniteTimeAction* reuse = CCReuseGrid::actionWithTimes(1);
	CCActionInterval* delay = CCDelayTime::actionWithDuration(8);

	CCActionInterval* orbit = CCOrbitCamera::actionWithDuration(5, 1, 2, 0, 180, 0, -90);
	CCActionInterval* orbit_back = orbit->reverse();

	target->runAction( CCRepeatForever::actionWithAction( (CCActionInterval *)(CCSequence::actions( orbit, orbit_back, NULL) ) ) );
	target->runAction( CCSequence::actions(lens, delay, reuse, waves, NULL) );
}

std::string Effect1::title()
{
	return "Lens + Waves3d and OrbitCamera";
}

//------------------------------------------------------------------
//
// Effect2
//
//------------------------------------------------------------------
void Effect2::onEnter()
{
	EffectAdvanceTextLayer::onEnter();

	CCNode* target = getChildByTag(kTagBackground);
	
	// To reuse a grid the grid size and the grid type must be the same.
	// in this case:
	//     ShakyTiles is TiledGrid3D and it's size is (15,10)
	//     Shuffletiles is TiledGrid3D and it's size is (15,10)
	//	   TurnOfftiles is TiledGrid3D and it's size is (15,10)
	CCActionInterval* shaky = CCShakyTiles3D::actionWithRange(4, false, ccg(15,10), 5);
	CCActionInterval* shuffle = CCShuffleTiles::actionWithSeed(0, ccg(15,10), 3);
	CCActionInterval* turnoff = CCTurnOffTiles::actionWithSeed(0, ccg(15,10), 3);
	CCActionInterval* turnon = turnoff->reverse();
	
	// reuse 2 times:
	//   1 for shuffle
	//   2 for turn off
	//   turnon tiles will use a new grid
	CCFiniteTimeAction* reuse = CCReuseGrid::actionWithTimes(2);

	CCActionInterval* delay = CCDelayTime::actionWithDuration(1);
	
//	id orbit = [OrbitCamera::actionWithDuration:5 radius:1 deltaRadius:2 angleZ:0 deltaAngleZ:180 angleX:0 deltaAngleX:-90];
//	id orbit_back = [orbit reverse];
//
//	[target runAction: [RepeatForever::actionWithAction: [Sequence actions: orbit, orbit_back, nil]]];
	target->runAction( (CCActionInterval *)(CCSequence::actions( shaky, delay, reuse, shuffle, delay->copy()->autorelease(), turnoff, turnon, NULL) ) );
}

std::string Effect2::title()
{
	return "ShakyTiles + ShuffleTiles + TurnOffTiles";
}


//------------------------------------------------------------------
//
// Effect3
//
//------------------------------------------------------------------
void Effect3::onEnter()
{
	EffectAdvanceTextLayer::onEnter();

	CCNode* bg = getChildByTag(kTagBackground);
	CCNode* target1 = bg->getChildByTag(kTagSprite1);
	CCNode* target2 = bg->getChildByTag(kTagSprite2);	
	
	CCActionInterval* waves = CCWaves::actionWithWaves(5, 20, true, false, ccg(15,10), 5);
	CCActionInterval* shaky = CCShaky3D::actionWithRange(4, false, ccg(15,10), 5);
	
	target1->runAction( CCRepeatForever::actionWithAction( waves ) );
	target2->runAction( CCRepeatForever::actionWithAction( shaky ) );
	
	// moving background. Testing issue #244
	CCActionInterval* move = CCMoveBy::actionWithDuration(3, ccp(200,0) );
	bg->runAction(CCRepeatForever::actionWithAction( (CCActionInterval *)(CCSequence::actions(move, move->reverse(), NULL) ) ) );	
}

std::string Effect3::title()
{
	return "Effects on 2 sprites";
}


//------------------------------------------------------------------
//
// Effect4
//
//------------------------------------------------------------------
void Effect4::onEnter()
{
	EffectAdvanceTextLayer::onEnter();

	CCActionInterval* lens = CCLens3D::actionWithPosition(ccp(100,180), 150, ccg(32,24), 10);
	//id move = [MoveBy::actionWithDuration:5 position:ccp(400,0)];

    /**
    @todo we only support CCNode run actions now.
    */
// 	CCActionInterval* move = CCJumpBy::actionWithDuration(5, ccp(380,0), 100, 4);
// 	CCActionInterval* move_back = move->reverse();
// 	CCActionInterval* seq = (CCActionInterval *)(CCSequence::actions( move, move_back, NULL));
//  CCActionManager::sharedManager()->addAction(seq, lens, false);

	runAction( lens );
}

std::string Effect4::title()
{
	return "Jumpy Lens3D";
}

//------------------------------------------------------------------
//
// Effect5
//
//------------------------------------------------------------------
void Effect5::onEnter()
{
	EffectAdvanceTextLayer::onEnter();

	//CCDirector::sharedDirector()->setProjection(CCDirectorProjection2D);
	
	CCActionInterval* effect = CCLiquid::actionWithWaves(1, 20, ccg(32,24), 2);	

	CCActionInterval* stopEffect = (CCActionInterval *)( CCSequence::actions(
										 effect,
										 CCDelayTime::actionWithDuration(2),
										 CCStopGrid::action(),
					//					 [DelayTime::actionWithDuration:2],
					//					 [[effect copy] autorelease],
										 NULL) );
	
	CCNode* bg = getChildByTag(kTagBackground);
	bg->runAction(stopEffect);
}

std::string Effect5::title()
{
	return "Test Stop-Copy-Restar";
}

void Effect5::onExit()
{
	EffectAdvanceTextLayer::onExit();

	CCDirector::sharedDirector()->setProjection(CCDirectorProjection3D);
}

//------------------------------------------------------------------
//
// Effect5
//
//------------------------------------------------------------------
void Issue631::onEnter()
{
	EffectAdvanceTextLayer::onEnter();
		
	CCActionInterval* effect = (CCActionInterval*)(CCSequence::actions( CCDelayTime::actionWithDuration(2.0f), CCShaky3D::actionWithRange(16, false, ccg(5, 5), 5.0f), NULL));

	// cleanup
	CCNode* bg = getChildByTag(kTagBackground);
	removeChild(bg, true);

	// background
	CCLayerColor* layer = CCLayerColor::layerWithColor( ccc4(255,0,0,255) );
	addChild(layer, -10);
	CCSprite* sprite = CCSprite::spriteWithFile("Images/grossini.png");
	sprite->setPosition( ccp(50,80) );
	layer->addChild(sprite, 10);
	
	// foreground
	CCLayerColor* layer2 = CCLayerColor::layerWithColor(ccc4( 0, 255,0,255 ) );
	CCSprite* fog = CCSprite::spriteWithFile("Images/Fog.png");

    ccBlendFunc bf = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};
	fog->setBlendFunc(bf);
	layer2->addChild(fog, 1);
	addChild(layer2, 1);
	
	layer2->runAction( CCRepeatForever::actionWithAction(effect) );
}

std::string Issue631::title()
{
	return "Testing Opacity";
}

std::string Issue631::subtitle()
{
	return "Effect image should be 100% opaque. Testing issue #631";
}

//------------------------------------------------------------------
//
// EffectAdvanceTextLayer
//
//------------------------------------------------------------------

enum
{
	IDC_NEXT = 100,
	IDC_BACK,
	IDC_RESTART
};

static int sceneIdx = -1; 

#define MAX_LAYER	6

CCLayer* nextEffectAdvanceAction();
CCLayer* backEffectAdvanceAction();
CCLayer* restartEffectAdvanceAction();

CCLayer* createEffectAdvanceLayer(int nIndex)
{
	switch(nIndex)
	{
		case 0: return new Effect3();
		case 1: return new Effect2();
		case 2: return new Effect1();
		case 3: return new Effect4();
		case 4: return new Effect5();
		case 5: return new Issue631();
	}  

	return NULL;
}

CCLayer* nextEffectAdvanceAction()
{
	sceneIdx++;
	sceneIdx = sceneIdx % MAX_LAYER;

	CCLayer* pLayer = createEffectAdvanceLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* backEffectAdvanceAction()
{
	sceneIdx--;
	int total = MAX_LAYER;
	if( sceneIdx < 0 )
		sceneIdx += total;	
	
	CCLayer* pLayer = createEffectAdvanceLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* restartEffectAdvanceAction()
{
	CCLayer* pLayer = createEffectAdvanceLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
} 


void EffectAdvanceTextLayer::onEnter(void)
{
	CCLayer::onEnter();
	float x,y;
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	x = size.width;
	y = size.height;
	
	CCSprite *bg = CCSprite::spriteWithFile("Images/background3.png");
	addChild(bg, 0, kTagBackground);
	bg->setPosition( ccp(x/2,y/2) );
	
	CCSprite* grossini = CCSprite::spriteWithFile("Images/grossinis_sister2.png");
	bg->addChild(grossini, 1, kTagSprite1);
	grossini->setPosition( ccp(x/3.0f,200) );
	CCActionInterval* sc = CCScaleBy::actionWithDuration(2, 5);
	CCActionInterval* sc_back = sc->reverse();
	grossini->runAction( CCRepeatForever::actionWithAction( (CCActionInterval*)(CCSequence::actions(sc, sc_back, NULL)) ) );

	CCSprite* tamara = CCSprite::spriteWithFile("Images/grossinis_sister1.png");
	bg->addChild(tamara, 1, kTagSprite2);
	tamara->setPosition( ccp(2*x/3.0f,200) );
	CCActionInterval* sc2 = CCScaleBy::actionWithDuration(2, 5);
	CCActionInterval* sc2_back = sc2->reverse();
	tamara->runAction( CCRepeatForever::actionWithAction( (CCActionInterval*)(CCSequence::actions(sc2, sc2_back, NULL)) ) );
	
	CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Marker Felt", 28);
	
	label->setPosition( ccp(x/2,y-80) );
	addChild(label);
	label->setTag( kTagLabel );

	std::string strSubtitle = subtitle();
	if( ! strSubtitle.empty() ) 
	{
		CCLabelTTF* l = CCLabelTTF::labelWithString(strSubtitle.c_str(), "Thonburi", 16);
		addChild(l, 101);
		l->setPosition( ccp(size.width/2, size.height-80) );
	}	

	CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage("Images/b1.png", "Images/b2.png", this, menu_selector(EffectAdvanceTextLayer::backCallback) );
	CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage("Images/r1.png","Images/r2.png", this, menu_selector(EffectAdvanceTextLayer::restartCallback) );
	CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage("Images/f1.png", "Images/f2.png", this, menu_selector(EffectAdvanceTextLayer::nextCallback) );

	CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);

	menu->setPosition( CCPointZero );
	item1->setPosition( ccp( size.width/2 - 100,30) );
	item2->setPosition( ccp( size.width/2, 30) );
	item3->setPosition( ccp( size.width/2 + 100,30) );
	
	addChild(menu, 1);	
}

EffectAdvanceTextLayer::~EffectAdvanceTextLayer(void)
{
}

std::string EffectAdvanceTextLayer::title()
{
	return "No title";
}

std::string EffectAdvanceTextLayer::subtitle()
{
	return "";
}

void EffectAdvanceTextLayer::restartCallback(CCObject* pSender)
{
	CCScene* s = new EffectAdvanceScene();
	s->addChild(restartEffectAdvanceAction()); 

	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void EffectAdvanceTextLayer::nextCallback(CCObject* pSender)
{
	CCScene* s = new EffectAdvanceScene();
	s->addChild( nextEffectAdvanceAction() );
	CCDirector::sharedDirector()->replaceScene(s);

    s->release();
}

void EffectAdvanceTextLayer::backCallback(CCObject* pSender)
{
	CCScene* s = new EffectAdvanceScene();
	s->addChild( backEffectAdvanceAction() );
	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
} 

void EffectAdvanceScene::runThisTest()
{
    CCLayer* pLayer = nextEffectAdvanceAction();

    addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(this);
}
