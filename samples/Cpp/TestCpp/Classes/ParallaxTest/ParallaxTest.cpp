#include "ParallaxTest.h"
#include "../testResource.h"

enum 
{
    kTagNode,
    kTagGrossini,
};

Layer* nextParallaxAction();
Layer* backParallaxAction();
Layer* restartParallaxAction();

//------------------------------------------------------------------
//
// Parallax1
//
//------------------------------------------------------------------

Parallax1::Parallax1()
{
    // Top Layer, a simple image
    Sprite* cocosImage = Sprite::create(s_Power);
    // scale the image (optional)
    cocosImage->setScale( 2.5f );
    // change the transform anchor point to 0,0 (optional)
    cocosImage->setAnchorPoint( ccp(0,0) );
    

    // Middle layer: a Tile map atlas
    TileMapAtlas *tilemap = TileMapAtlas::create(s_TilesPng, s_LevelMapTga, 16, 16);
    tilemap->releaseMap();
    
    // change the transform anchor to 0,0 (optional)
    tilemap->setAnchorPoint( ccp(0, 0) );

    // Anti Aliased images
    tilemap->getTexture()->setAntiAliasTexParameters();
    

    // background layer: another image
    Sprite* background = Sprite::create(s_back);
    // scale the image (optional)
    background->setScale( 1.5f );
    // change the transform anchor point (optional)
    background->setAnchorPoint( ccp(0,0) );

    
    // create a void node, a parent node
    ParallaxNode* voidNode = ParallaxNode::create();
    
    // NOW add the 3 layers to the 'void' node

    // background image is moved at a ratio of 0.4x, 0.5y
    voidNode->addChild(background, -1, ccp(0.4f,0.5f), PointZero);
    
    // tiles are moved at a ratio of 2.2x, 1.0y
    voidNode->addChild(tilemap, 1, ccp(2.2f,1.0f), ccp(0,-200) );
    
    // top image is moved at a ratio of 3.0x, 2.5y
    voidNode->addChild(cocosImage, 2, ccp(3.0f,2.5f), ccp(200,800) );
    
    
    // now create some actions that will move the 'void' node
    // and the children of the 'void' node will move at different
    // speed, thus, simulation the 3D environment
    ActionInterval* goUp = MoveBy::create(4, ccp(0,-500) );
    ActionInterval* goDown = goUp->reverse();
    ActionInterval* go = MoveBy::create(8, ccp(-1000,0) );
    ActionInterval* goBack = go->reverse();
    Sequence* seq = Sequence::create(goUp, go, goDown, goBack, NULL);
    voidNode->runAction( (RepeatForever::create(seq) ));
    
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
    setTouchEnabled( true );
    
    // Top Layer, a simple image
    Sprite* cocosImage = Sprite::create(s_Power);
    // scale the image (optional)
    cocosImage->setScale( 2.5f );
    // change the transform anchor point to 0,0 (optional)
    cocosImage->setAnchorPoint( ccp(0,0) );
    
    
    // Middle layer: a Tile map atlas
    TileMapAtlas* tilemap = TileMapAtlas::create(s_TilesPng, s_LevelMapTga, 16, 16);
    tilemap->releaseMap();
    
    // change the transform anchor to 0,0 (optional)
    tilemap->setAnchorPoint( ccp(0, 0) );
    
    // Anti Aliased images
    tilemap->getTexture()->setAntiAliasTexParameters();
    
    
    // background layer: another image
    Sprite* background = Sprite::create(s_back);
    // scale the image (optional)
    background->setScale( 1.5f );
    // change the transform anchor point (optional)
    background->setAnchorPoint( ccp(0,0) );
    
    
    // create a void node, a parent node
    ParallaxNode* voidNode = ParallaxNode::create();
    
    // NOW add the 3 layers to the 'void' node
    
    // background image is moved at a ratio of 0.4x, 0.5y
    voidNode->addChild(background, -1, ccp(0.4f,0.5f), PointZero);
    
    // tiles are moved at a ratio of 1.0, 1.0y
    voidNode->addChild(tilemap, 1, ccp(1.0f,1.0f), ccp(0,-200) );
    
    // top image is moved at a ratio of 3.0x, 2.5y
    voidNode->addChild( cocosImage, 2, ccp(3.0f,2.5f), ccp(200,1000) );
    addChild(voidNode, 0, kTagNode);
}

void Parallax2::ccTouchesMoved(Set *pTouches, Event *pEvent)
{
    Touch *touch = (Touch*)pTouches->anyObject();
    Point diff = touch->getDelta();
    
    Node* node = getChildByTag(kTagNode);
    Point currentPos = node->getPosition();
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

#define MAX_LAYER    2

Layer* createParallaxTestLayer(int nIndex)
{
    switch(nIndex)
    {
        case 0: return new Parallax1();
        case 1: return new Parallax2();
    }

    return NULL;
}

Layer* nextParallaxAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    Layer* pLayer = createParallaxTestLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

Layer* backParallaxAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    Layer* pLayer = createParallaxTestLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

Layer* restartParallaxAction()
{
    Layer* pLayer = createParallaxTestLayer(sceneIdx);
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
    BaseTest::onEnter();
}

void ParallaxDemo::restartCallback(Object* pSender)
{
    Scene* s = new ParallaxTestScene();
    s->addChild(restartParallaxAction()); 

    Director::sharedDirector()->replaceScene(s);
    s->release();
}

void ParallaxDemo::nextCallback(Object* pSender)
{
    Scene* s = new ParallaxTestScene();
    s->addChild( nextParallaxAction() );
    Director::sharedDirector()->replaceScene(s);
    s->release();
}

void ParallaxDemo::backCallback(Object* pSender)
{
    Scene* s = new ParallaxTestScene();
    s->addChild( backParallaxAction() );
    Director::sharedDirector()->replaceScene(s);
    s->release();
} 

void ParallaxTestScene::runThisTest()
{
    Layer* pLayer = nextParallaxAction();

    addChild(pLayer);
    Director::sharedDirector()->replaceScene(this);
}
