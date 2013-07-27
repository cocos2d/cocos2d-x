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
    cocosImage->setAnchorPoint( Point(0,0) );
    

    // Middle layer: a Tile map atlas
    TileMapAtlas *tilemap = TileMapAtlas::create(s_TilesPng, s_LevelMapTga, 16, 16);
    tilemap->releaseMap();
    
    // change the transform anchor to 0,0 (optional)
    tilemap->setAnchorPoint( Point(0, 0) );

    // Anti Aliased images
    tilemap->getTexture()->setAntiAliasTexParameters();
    

    // background layer: another image
    Sprite* background = Sprite::create(s_back);
    // scale the image (optional)
    background->setScale( 1.5f );
    // change the transform anchor point (optional)
    background->setAnchorPoint( Point(0,0) );

    
    // create a void node, a parent node
    ParallaxNode* voidNode = ParallaxNode::create();
    
    // NOW add the 3 layers to the 'void' node

    // background image is moved at a ratio of 0.4x, 0.5y
    voidNode->addChild(background, -1, Point(0.4f,0.5f), Point::ZERO);
    
    // tiles are moved at a ratio of 2.2x, 1.0y
    voidNode->addChild(tilemap, 1, Point(2.2f,1.0f), Point(0,-200) );
    
    // top image is moved at a ratio of 3.0x, 2.5y
    voidNode->addChild(cocosImage, 2, Point(3.0f,2.5f), Point(200,800) );
    
    
    // now create some actions that will move the 'void' node
    // and the children of the 'void' node will move at different
    // speed, thus, simulation the 3D environment
    ActionInterval* goUp = MoveBy::create(4, Point(0,-500) );
    ActionInterval* goDown = goUp->reverse();
    ActionInterval* go = MoveBy::create(8, Point(-1000,0) );
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
    cocosImage->setAnchorPoint( Point(0,0) );
    
    
    // Middle layer: a Tile map atlas
    TileMapAtlas* tilemap = TileMapAtlas::create(s_TilesPng, s_LevelMapTga, 16, 16);
    tilemap->releaseMap();
    
    // change the transform anchor to 0,0 (optional)
    tilemap->setAnchorPoint( Point(0, 0) );
    
    // Anti Aliased images
    tilemap->getTexture()->setAntiAliasTexParameters();
    
    
    // background layer: another image
    Sprite* background = Sprite::create(s_back);
    // scale the image (optional)
    background->setScale( 1.5f );
    // change the transform anchor point (optional)
    background->setAnchorPoint( Point(0,0) );
    
    
    // create a void node, a parent node
    ParallaxNode* voidNode = ParallaxNode::create();
    
    // NOW add the 3 layers to the 'void' node
    
    // background image is moved at a ratio of 0.4x, 0.5y
    voidNode->addChild(background, -1, Point(0.4f,0.5f), Point::ZERO);
    
    // tiles are moved at a ratio of 1.0, 1.0y
    voidNode->addChild(tilemap, 1, Point(1.0f,1.0f), Point(0,-200) );
    
    // top image is moved at a ratio of 3.0x, 2.5y
    voidNode->addChild( cocosImage, 2, Point(3.0f,2.5f), Point(200,1000) );
    addChild(voidNode, 0, kTagNode);
}

void Parallax2::ccTouchesMoved(Set  *touches, Event  *event)
{
    Touch *touch = static_cast<Touch*>(touches->anyObject());
    Point diff = touch->getDelta();
    
    Node* node = getChildByTag(kTagNode);
    Point currentPos = node->getPosition();
    node->setPosition(currentPos + diff);
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

    Layer* layer = createParallaxTestLayer(sceneIdx);
    layer->autorelease();

    return layer;
}

Layer* backParallaxAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    Layer* layer = createParallaxTestLayer(sceneIdx);
    layer->autorelease();

    return layer;
}

Layer* restartParallaxAction()
{
    Layer* layer = createParallaxTestLayer(sceneIdx);
    layer->autorelease();

    return layer;
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

void ParallaxDemo::restartCallback(Object* sender)
{
    Scene* s = new ParallaxTestScene();
    s->addChild(restartParallaxAction()); 

    Director::getInstance()->replaceScene(s);
    s->release();
}

void ParallaxDemo::nextCallback(Object* sender)
{
    Scene* s = new ParallaxTestScene();
    s->addChild( nextParallaxAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void ParallaxDemo::backCallback(Object* sender)
{
    Scene* s = new ParallaxTestScene();
    s->addChild( backParallaxAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
} 

void ParallaxTestScene::runThisTest()
{
    Layer* layer = nextParallaxAction();

    addChild(layer);
    Director::getInstance()->replaceScene(this);
}
