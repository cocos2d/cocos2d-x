#include "PhysicsTest.h"
#include "../testResource.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;

PhysicsTestLayer::PhysicsTestLayer()
: _spriteTexture(NULL)
{
#ifdef CC_USE_PHYSICS
    //Set up sprite
#if 1
    // Use batch node. Faster
    auto parent = SpriteBatchNode::create("Images/blocks.png", 100);
    _spriteTexture = parent->getTexture();
#else
    // doesn't use batch node. Slower
    _spriteTexture = TextureCache::getInstance()->addImage("Images/blocks.png");
    auto parent = Node::create();
#endif
    
#else
    auto label = LabelTTF::create("Should define CC_ENABLE_BOX2D_INTEGRATION=1\n to run this test case",
                                  "Arial",
                                  18);
    auto size = Director::getInstance()->getWinSize();
    label->setPosition(Point(size.width/2, size.height/2));
    
    addChild(label);
#endif
}

PhysicsTestLayer::~PhysicsTestLayer()
{
}

void PhysicsTestLayer::initPhysics()
{
}

void PhysicsTestLayer::createResetButton()
{
    auto reset = MenuItemImage::create("Images/r1.png", "Images/r2.png", [](Object *sender) {
		auto s = new PhysicsTestScene();
		auto child = new PhysicsTestLayer();
		s->addChild(child);
		child->release();
		Director::getInstance()->replaceScene(s);
		s->release();
	});
    
    auto menu = Menu::create(reset, NULL);
    
    menu->setPosition(Point(VisibleRect::bottom().x, VisibleRect::bottom().y + 30));
    this->addChild(menu, -1);
    
}

void PhysicsTestLayer::addNewSpriteAtPosition(Point p)
{
    CCLOG("Add sprite %0.2f x %02.f",p.x,p.y);
    
#if CC_ENABLE_BOX2D_INTEGRATION
    auto parent = this->getChildByTag(kTagParentNode);
    
    //We have a 64x64 sprite sheet with 4 different 32x32 images.  The following code is
    //just randomly picking one of the images
    int idx = (CCRANDOM_0_1() > .5 ? 0:1);
    int idy = (CCRANDOM_0_1() > .5 ? 0:1);
    auto sprite = PhysicsSprite::createWithTexture(_spriteTexture,Rect(32 * idx,32 * idy,32,32));
    parent->addChild(sprite);
    sprite->setB2Body(body);
    sprite->setPTMRatio(PTM_RATIO);
    sprite->setPosition( Point( p.x, p.y) );
#endif
}

void PhysicsTestLayer::ccTouchesEnded(Set* touches, Event* event)
{
    //Add a new body/atlas sprite at the touched location
    SetIterator it;
    Touch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = static_cast<Touch*>(*it);
        
        if(!touch)
            break;
        
        auto location = touch->getLocation();
        
        addNewSpriteAtPosition( location );
    }
}

bool PhysicsTestScene::initTest()
{
    return TestScene::initWithPhysics();
}

void PhysicsTestScene::runThisTest()
{
    auto layer = new PhysicsTestLayer();
    addChild(layer);
    layer->release();
    
    Director::getInstance()->replaceScene(this);
}
