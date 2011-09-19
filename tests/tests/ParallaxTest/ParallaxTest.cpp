#include "ParallaxTest.h"
#include "../testResource.h"

enum 
{
	kTagNode,
	kTagGrossini,
};

CCLayer* nextParallaxAction();
CCLayer* backParallaxAction();
CCLayer* restartParallaxAction();

//------------------------------------------------------------------
//
// Parallax1
//
//------------------------------------------------------------------

Parallax1::Parallax1()
{
	// Top Layer, a simple image
	CCSprite* cocosImage = CCSprite::spriteWithFile(s_Power);
	// scale the image (optional)
	cocosImage->setScale( 2.5f );
	// change the transform anchor point to 0,0 (optional)
	cocosImage->setAnchorPoint( ccp(0,0) );
	

	// Middle layer: a Tile map atlas
	CCTileMapAtlas *tilemap = CCTileMapAtlas::tileMapAtlasWithTileFile(s_TilesPng, s_LevelMapTga, 16, 16);
	tilemap->releaseMap();
	
	// change the transform anchor to 0,0 (optional)
	tilemap->setAnchorPoint( ccp(0, 0) );

	// Anti Aliased images
    tilemap->getTexture()->setAntiAliasTexParameters();
	

	// background layer: another image
	CCSprite* background = CCSprite::spriteWithFile(s_back);
	// scale the image (optional)
	background->setScale( 1.5f );
	// change the transform anchor point (optional)
	background->setAnchorPoint( ccp(0,0) );

	
	// create a void node, a parent node
	CCParallaxNode* voidNode = CCParallaxNode::node();
	
	// NOW add the 3 layers to the 'void' node

	// background image is moved at a ratio of 0.4x, 0.5y
	voidNode->addChild(background, -1, ccp(0.4f,0.5f), CCPointZero);
	
	// tiles are moved at a ratio of 2.2x, 1.0y
	voidNode->addChild(tilemap, 1, ccp(2.2f,1.0f), ccp(0,-200) );
	
	// top image is moved at a ratio of 3.0x, 2.5y
	voidNode->addChild(cocosImage, 2, ccp(3.0f,2.5f), ccp(200,800) );
	
	
	// now create some actions that will move the 'void' node
	// and the children of the 'void' node will move at different
	// speed, thus, simulation the 3D environment
	CCActionInterval* goUp = CCMoveBy::actionWithDuration(4, ccp(0,-500) );
	CCActionInterval* goDown = goUp->reverse();
	CCActionInterval* go = CCMoveBy::actionWithDuration(8, ccp(-1000,0) );
	CCActionInterval* goBack = go->reverse();
	CCFiniteTimeAction* seq = CCSequence::actions(goUp, go, goDown, goBack, NULL);
	voidNode->runAction( (CCRepeatForever::actionWithAction((CCActionInterval*) seq) ));
	
	addChild( voidNode );
}

std::string Parallax1::title()
{
	return "Parallax: parent and 3 children";
}

//------------------------------------------------------------------
//
// Parallax2
//
//------------------------------------------------------------------

Parallax2::Parallax2()
{
	setIsTouchEnabled( true );
	
	// Top Layer, a simple image
	CCSprite* cocosImage = CCSprite::spriteWithFile(s_Power);
	// scale the image (optional)
	cocosImage->setScale( 2.5f );
	// change the transform anchor point to 0,0 (optional)
	cocosImage->setAnchorPoint( ccp(0,0) );
	
	
	// Middle layer: a Tile map atlas
	CCTileMapAtlas* tilemap = CCTileMapAtlas::tileMapAtlasWithTileFile(s_TilesPng, s_LevelMapTga, 16, 16);
	tilemap->releaseMap();
	
	// change the transform anchor to 0,0 (optional)
	tilemap->setAnchorPoint( ccp(0, 0) );
	
    // Anti Aliased images
    tilemap->getTexture()->setAntiAliasTexParameters();
	
	
	// background layer: another image
	CCSprite* background = CCSprite::spriteWithFile(s_back);
	// scale the image (optional)
	background->setScale( 1.5f );
	// change the transform anchor point (optional)
	background->setAnchorPoint( ccp(0,0) );
	
	
	// create a void node, a parent node
	CCParallaxNode* voidNode = CCParallaxNode::node();
	
	// NOW add the 3 layers to the 'void' node
	
	// background image is moved at a ratio of 0.4x, 0.5y
	voidNode->addChild(background, -1, ccp(0.4f,0.5f), CCPointZero);
	
	// tiles are moved at a ratio of 1.0, 1.0y
	voidNode->addChild(tilemap, 1, ccp(1.0f,1.0f), ccp(0,-200) );
	
	// top image is moved at a ratio of 3.0x, 2.5y
	voidNode->addChild( cocosImage, 2, ccp(3.0f,2.5f), ccp(200,1000) );
	addChild(voidNode, 0, kTagNode);
}

void Parallax2::registerWithTouchDispatcher()
{
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
}

bool Parallax2::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	return true;
}

void Parallax2::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
}

void Parallax2::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{
}

void Parallax2::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CCPoint touchLocation = touch->locationInView( touch->view() );	
	CCPoint prevLocation = touch->previousLocationInView( touch->view() );	

	touchLocation = CCDirector::sharedDirector()->convertToGL( touchLocation );
	prevLocation = CCDirector::sharedDirector()->convertToGL( prevLocation );

	CCPoint diff = ccpSub(touchLocation,prevLocation);
	
	CCNode* node = getChildByTag(kTagNode);
	CCPoint currentPos = node->getPosition();
	node->setPosition( ccpAdd(currentPos, diff) );
}

std::string Parallax2::title()
{
	return "Parallax: drag screen";
}

//------------------------------------------------------------------
//
// ParallaxDemo
//
//------------------------------------------------------------------

static int sceneIdx = -1; 

#define MAX_LAYER	2

CCLayer* createParallaxTestLayer(int nIndex)
{
	switch(nIndex)
	{
		case 0: return new Parallax1();
		case 1: return new Parallax2();
	}

	return NULL;
}

CCLayer* nextParallaxAction()
{
	sceneIdx++;
	sceneIdx = sceneIdx % MAX_LAYER;

	CCLayer* pLayer = createParallaxTestLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* backParallaxAction()
{
	sceneIdx--;
	int total = MAX_LAYER;
	if( sceneIdx < 0 )
		sceneIdx += total;	
	
	CCLayer* pLayer = createParallaxTestLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* restartParallaxAction()
{
	CCLayer* pLayer = createParallaxTestLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
} 


ParallaxDemo::ParallaxDemo(void)
{
}

ParallaxDemo::~ParallaxDemo(void)
{
}

std::string ParallaxDemo::title()
{
	return "No title";
}

void ParallaxDemo::onEnter()
{
	CCLayer::onEnter();

	CCSize s = CCDirector::sharedDirector()->getWinSize();

	CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 28);
	addChild(label, 1);
	label->setPosition( ccp(s.width/2, s.height-50) );

	CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(ParallaxDemo::backCallback) );
	CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage(s_pPathR1, s_pPathR2, this, menu_selector(ParallaxDemo::restartCallback) );
	CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage(s_pPathF1, s_pPathF2, this, menu_selector(ParallaxDemo::nextCallback) );

	CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);

	menu->setPosition( CCPointZero );
	item1->setPosition( ccp( s.width/2 - 100,30) );
	item2->setPosition( ccp( s.width/2, 30) );
	item3->setPosition( ccp( s.width/2 + 100,30) );
	
	addChild(menu, 1);	
}

void ParallaxDemo::restartCallback(CCObject* pSender)
{
	CCScene* s = new ParallaxTestScene();
	s->addChild(restartParallaxAction()); 

	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void ParallaxDemo::nextCallback(CCObject* pSender)
{
	CCScene* s = new ParallaxTestScene();
	s->addChild( nextParallaxAction() );
	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void ParallaxDemo::backCallback(CCObject* pSender)
{
	CCScene* s = new ParallaxTestScene();
	s->addChild( backParallaxAction() );
	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
} 

void ParallaxTestScene::runThisTest()
{
    CCLayer* pLayer = nextParallaxAction();

    addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(this);
}
