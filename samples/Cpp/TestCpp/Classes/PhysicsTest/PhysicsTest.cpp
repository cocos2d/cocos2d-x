#include "PhysicsTest.h"
#include "../testResource.h"
USING_NS_CC;

PhysicsTestLayer::PhysicsTestLayer()
: _spriteTexture(NULL)
{
#ifdef CC_USE_PHYSICS
    setTouchEnabled(true);
    setAccelerometerEnabled(true);
    
    // title
    auto label = LabelTTF::create("Multi touch the screen", "Marker Felt", 36);
    label->setPosition(Point( VisibleRect::center().x, VisibleRect::top().y - 30));
    this->addChild(label, -1);
    
    // menu for debug layer
    MenuItemFont::setFontSize(18);
    auto item = MenuItemFont::create("Toggle debug", CC_CALLBACK_1(PhysicsTestLayer::toggleDebugCallback, this));
    
    auto menu = Menu::create(item, NULL);
    this->addChild(menu);
    menu->setPosition(Point(VisibleRect::right().x-100, VisibleRect::top().y-60));
    
    auto sp = Sprite::create();
    auto body = PhysicsBody::createEdgeBox(VisibleRect::getVisibleRect().size);
    sp->setPhysicsBody(body);
    this->addChild(sp);
    sp->setPosition(VisibleRect::center());
    
    auto parent = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 100);
    _spriteTexture = parent->getTexture();
    
    addNewSpriteAtPosition(VisibleRect::center());
    
    createResetButton();
    
#else
    auto label = LabelTTF::create("Should define CC_USE_BOX2D or CC_USE_CHIPMUNK\n to run this test case",
                                  "Arial",
                                  18);
    auto size = Director::getInstance()->getWinSize();
    label->setPosition(Point(size.width/2, size.height/2));
    
    addChild(label);
#endif
}

void PhysicsTestLayer::toggleDebugCallback(Object* sender)
{
#ifdef CC_USE_PHYSICS
    if (dynamic_cast<Scene*>(this->getParent()) != nullptr)
    {
        PhysicsWorld* world = dynamic_cast<Scene*>(this->getParent())->getPhysicsWorld();
        world->setDebugDraw(!world->getDebugDraw());
    }
#endif
}

PhysicsTestLayer::~PhysicsTestLayer()
{
}

void PhysicsTestLayer::createResetButton()
{
    auto reset = MenuItemImage::create("Images/r1.png", "Images/r2.png", [](Object *sender) {
		auto s = new PhysicsTestScene();
        s->initTest();
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

void PhysicsTestLayer::ccTouchesEnded(Set* touches, Event* event)
{
    //Add a new body/atlas sprite at the touched location
    
    for( auto &item: *touches)
    {
        auto touch = static_cast<Touch*>(item);
        
        auto location = touch->getLocation();
        
        addNewSpriteAtPosition( location );
    }
}

void PhysicsTestLayer::addNewSpriteAtPosition(Point p)
{
#ifdef CC_USE_PHYSICS
    CCLOG("Add sprite %0.2f x %02.f",p.x,p.y);
    
    int posx, posy;
    
    posx = CCRANDOM_0_1() * 200.0f;
    posy = CCRANDOM_0_1() * 200.0f;
    
    posx = (posx % 4) * 85;
    posy = (posy % 3) * 121;
    
    auto sp = Sprite::createWithTexture(_spriteTexture, Rect(posx, posy, 85, 121));
    auto body = PhysicsBody::createBox(Size(48, 108));
    sp->setPhysicsBody(body);
    sp->setPosition(p);
    this->addChild(sp);
#endif
}

bool PhysicsTestScene::initTest()
{
#ifdef CC_USE_PHYSICS
    if (TestScene::initWithPhysics())
    {
        this->getPhysicsWorld()->setDebugDraw(true);
        return true;
    }
#else
    return TestScene::init();
#endif
    
    return false;
}

void PhysicsTestScene::runThisTest()
{
    auto layer = new PhysicsTestLayer();
    addChild(layer);
    layer->release();
    
    Director::getInstance()->replaceScene(this);
}
