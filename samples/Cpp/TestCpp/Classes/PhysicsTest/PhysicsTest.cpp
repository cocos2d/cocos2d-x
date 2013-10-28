#include "PhysicsTest.h"
#include "../testResource.h"
USING_NS_CC;

namespace
{
    static std::function<Layer*()> createFunctions[] = {
        CL(PhysicsDemoLogoSmash),
        CL(PhysicsDemoPyramidStack),
        CL(PhysicsDemoPlink),
        CL(PhysicsDemoClickAdd),
        CL(PhysicsDemoRayCast),
    };
    
    static int sceneIdx=-1;
#define MAX_LAYER (sizeof(createFunctions) / sizeof(createFunctions[0]))
    
    static Layer* next()
    {
        sceneIdx++;
        sceneIdx = sceneIdx % MAX_LAYER;
        
        auto layer = (createFunctions[sceneIdx])();
        layer->init();
        layer->autorelease();
        
        return layer;
    }
    
    static Layer* back()
    {
        sceneIdx--;
        int total = MAX_LAYER;
        if( sceneIdx < 0 )
            sceneIdx += total;
        
        auto layer = (createFunctions[sceneIdx])();
        layer->init();
        layer->autorelease();
        
        return layer;
    }
    
    static Layer* restart()
    {
        auto layer = (createFunctions[sceneIdx])();
        layer->init();
        layer->autorelease();
        
        return layer;
    }
    
    static const Color4F STATIC_COLOR(1.0f, 0.0f, 0.0f, 1.0f);
}


bool PhysicsTestScene::_debugDraw = false;

bool PhysicsTestScene::initTest()
{
#ifdef CC_USE_PHYSICS
    if(TestScene::initWithPhysics())
    {
        this->getPhysicsWorld()->setDebugDraw(_debugDraw);
        return true;
    }
#else
    return TestScene::init();
#endif
    
    return false;
}

void PhysicsTestScene::runThisTest()
{
#ifdef CC_USE_PHYSICS
    sceneIdx = -1;
    addChild(next());
    
    Director::getInstance()->replaceScene(this);
#else
#endif
}

void PhysicsTestScene::toggleDebug()
{
    _debugDraw = !_debugDraw;
    getPhysicsWorld()->setDebugDraw(_debugDraw);
}

PhysicsDemo::PhysicsDemo()
: _scene(nullptr)
, _ball(nullptr)
, _spriteTexture(nullptr)
{
    
}

PhysicsDemo::~PhysicsDemo()
{
    
}

std::string PhysicsDemo::title()
{
    return "PhysicsTest";
}

std::string PhysicsDemo::subtitle()
{
    return "";
}

void PhysicsDemo::restartCallback(Object* sender)
{
    auto s = new PhysicsTestScene();
    s->initTest();
    s->addChild( restart() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void PhysicsDemo::nextCallback(Object* sender)
{
    auto s = new PhysicsTestScene();
    s->initTest();
    s->addChild( next() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void PhysicsDemo::backCallback(Object* sender)
{
    auto s = new PhysicsTestScene();
    s->initTest();
    s->addChild( back() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void PhysicsDemo::onEnter()
{
    BaseTest::onEnter();
    
    _scene = dynamic_cast<PhysicsTestScene*>(this->getParent());
    
    _spriteTexture = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 100)->getTexture();
    
#ifdef CC_USE_PHYSICS
    
    // menu for debug layer
    MenuItemFont::setFontSize(18);
    auto item = MenuItemFont::create("Toggle debug", CC_CALLBACK_1(PhysicsDemo::toggleDebugCallback, this));
    
    auto menu = Menu::create(item, NULL);
    this->addChild(menu);
    menu->setPosition(Point(VisibleRect::right().x-50, VisibleRect::top().y-10));
#else
#endif
}

Sprite* PhysicsDemo::addGrossiniAtPosition(Point p, float scale/* = 1.0*/)
{
#ifdef CC_USE_PHYSICS
    CCLOG("Add sprite %0.2f x %02.f",p.x,p.y);
    
    int posx, posy;
    
    posx = CCRANDOM_0_1() * 200.0f;
    posy = CCRANDOM_0_1() * 200.0f;
    
    posx = (posx % 4) * 85;
    posy = (posy % 3) * 121;
    
    auto sp = Sprite::createWithTexture(_spriteTexture, Rect(posx, posy, 85, 121));
    sp->setScale(scale);
    sp->setPhysicsBody(PhysicsBody::createBox(Size(48.0f * scale, 108.0f * scale)));
    this->addChild(sp);
    sp->setPosition(p);
    
    return sp;
#endif
}


void PhysicsDemo::toggleDebugCallback(Object* sender)
{
#ifdef CC_USE_PHYSICS
    if (_scene != nullptr)
    {
        _scene->toggleDebug();
    }
#endif
}

void PhysicsDemoClickAdd::onEnter()
{
    PhysicsDemo::onEnter();
    
#ifdef CC_USE_PHYSICS
    setTouchEnabled(true);
    setAccelerometerEnabled(true);
    
    auto node = Node::create();
    node->setPhysicsBody(PhysicsBody::createEdgeBox(VisibleRect::getVisibleRect().size));
    node->setPosition(VisibleRect::center());
    this->addChild(node);
    
    addGrossiniAtPosition(VisibleRect::center());
    
#else
    auto label = LabelTTF::create("Should define CC_USE_BOX2D or CC_USE_CHIPMUNK\n to run this test case",
                                  "Arial",
                                  18);
    auto size = Director::getInstance()->getWinSize();
    label->setPosition(Point(size.width/2, size.height/2));
    
    addChild(label);
#endif
}

std::string PhysicsDemoClickAdd::subtitle()
{
    return "multi touch to add grossini";
}

void PhysicsDemoClickAdd::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    //Add a new body/atlas sprite at the touched location
    
    for( auto &touch: touches)
    {
        auto location = touch->getLocation();
        
        addGrossiniAtPosition( location );
    }
}

void PhysicsDemoClickAdd::onAcceleration(Acceleration* acc, Event* event)
{
#ifdef CC_USE_PHYSICS
    static float prevX=0, prevY=0;
    
#define kFilterFactor 0.05f
    
    float accelX = (float) acc->x * kFilterFactor + (1- kFilterFactor)*prevX;
    float accelY = (float) acc->y * kFilterFactor + (1- kFilterFactor)*prevY;
    
    prevX = accelX;
    prevY = accelY;
    
    auto v = Point( accelX, accelY);
    v = v * 200;
    
    if(_scene != nullptr)
    {
        _scene->getPhysicsWorld()->setGravity(v);
    }
#endif
}

namespace
{
    static const int logo_width = 188;
    static const int logo_height = 35;
    static const int logo_row_length = 24;
    static const char logo_image[] =
    {
        15,-16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,-64,15,63,-32,-2,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,31,-64,15,127,-125,-1,-128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,127,-64,15,127,15,-1,-64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,-1,-64,15,-2,
        31,-1,-64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,-1,-64,0,-4,63,-1,-32,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,1,-1,-64,15,-8,127,-1,-32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,-1,-64,0,-8,-15,-1,-32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,-31,-1,-64,15,-8,-32,
        -1,-32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,-15,-1,-64,9,-15,-32,-1,-32,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,31,-15,-1,-64,0,-15,-32,-1,-32,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,63,-7,-1,-64,9,-29,-32,127,-61,-16,63,15,-61,-1,-8,31,-16,15,-8,126,7,-31,
        -8,31,-65,-7,-1,-64,9,-29,-32,0,7,-8,127,-97,-25,-1,-2,63,-8,31,-4,-1,15,-13,
        -4,63,-1,-3,-1,-64,9,-29,-32,0,7,-8,127,-97,-25,-1,-2,63,-8,31,-4,-1,15,-13,
        -2,63,-1,-3,-1,-64,9,-29,-32,0,7,-8,127,-97,-25,-1,-1,63,-4,63,-4,-1,15,-13,
        -2,63,-33,-1,-1,-32,9,-25,-32,0,7,-8,127,-97,-25,-1,-1,63,-4,63,-4,-1,15,-13,
        -1,63,-33,-1,-1,-16,9,-25,-32,0,7,-8,127,-97,-25,-1,-1,63,-4,63,-4,-1,15,-13,
        -1,63,-49,-1,-1,-8,9,-57,-32,0,7,-8,127,-97,-25,-8,-1,63,-2,127,-4,-1,15,-13,
        -1,-65,-49,-1,-1,-4,9,-57,-32,0,7,-8,127,-97,-25,-8,-1,63,-2,127,-4,-1,15,-13,
        -1,-65,-57,-1,-1,-2,9,-57,-32,0,7,-8,127,-97,-25,-8,-1,63,-2,127,-4,-1,15,-13,
        -1,-1,-57,-1,-1,-1,9,-57,-32,0,7,-1,-1,-97,-25,-8,-1,63,-1,-1,-4,-1,15,-13,-1,
        -1,-61,-1,-1,-1,-119,-57,-32,0,7,-1,-1,-97,-25,-8,-1,63,-1,-1,-4,-1,15,-13,-1,
        -1,-61,-1,-1,-1,-55,-49,-32,0,7,-1,-1,-97,-25,-8,-1,63,-1,-1,-4,-1,15,-13,-1,
        -1,-63,-1,-1,-1,-23,-49,-32,127,-57,-1,-1,-97,-25,-1,-1,63,-1,-1,-4,-1,15,-13,
        -1,-1,-63,-1,-1,-1,-16,-49,-32,-1,-25,-1,-1,-97,-25,-1,-1,63,-33,-5,-4,-1,15,
        -13,-1,-1,-64,-1,-9,-1,-7,-49,-32,-1,-25,-8,127,-97,-25,-1,-1,63,-33,-5,-4,-1,
        15,-13,-1,-1,-64,-1,-13,-1,-32,-49,-32,-1,-25,-8,127,-97,-25,-1,-2,63,-49,-13,
        -4,-1,15,-13,-1,-1,-64,127,-7,-1,-119,-17,-15,-1,-25,-8,127,-97,-25,-1,-2,63,
        -49,-13,-4,-1,15,-13,-3,-1,-64,127,-8,-2,15,-17,-1,-1,-25,-8,127,-97,-25,-1,
        -8,63,-49,-13,-4,-1,15,-13,-3,-1,-64,63,-4,120,0,-17,-1,-1,-25,-8,127,-97,-25,
        -8,0,63,-57,-29,-4,-1,15,-13,-4,-1,-64,63,-4,0,15,-17,-1,-1,-25,-8,127,-97,
        -25,-8,0,63,-57,-29,-4,-1,-1,-13,-4,-1,-64,31,-2,0,0,103,-1,-1,-57,-8,127,-97,
        -25,-8,0,63,-57,-29,-4,-1,-1,-13,-4,127,-64,31,-2,0,15,103,-1,-1,-57,-8,127,
        -97,-25,-8,0,63,-61,-61,-4,127,-1,-29,-4,127,-64,15,-8,0,0,55,-1,-1,-121,-8,
        127,-97,-25,-8,0,63,-61,-61,-4,127,-1,-29,-4,63,-64,15,-32,0,0,23,-1,-2,3,-16,
        63,15,-61,-16,0,31,-127,-127,-8,31,-1,-127,-8,31,-128,7,-128,0,0
    };
    
    static inline int get_pixel(int x, int y)
    {
        return (logo_image[(x>>3) + y*logo_row_length]>>(~x&0x7)) & 1;
    }
    
    static inline float frand(void)
    {
        return rand()/RAND_MAX;
    }
}

Sprite* PhysicsDemo::makeBall(float x, float y, float radius, PhysicsMaterial material)
{
    Sprite* ball = nullptr;
    if (_ball != nullptr)
    {
        ball = Sprite::createWithTexture(_ball->getTexture());
    }else
    {
        ball = Sprite::create("Images/ball.png");
    }
    
    ball->setScale(0.13f * radius);
    
    auto body = PhysicsBody::createCircle(radius, material);
    ball->setPhysicsBody(body);
    ball->setPosition(Point(x, y));
    
    return ball;
}

Sprite* PhysicsDemo::makeBox(float x, float y, Size size, PhysicsMaterial material)
{
    auto box = CCRANDOM_0_1() > 0.5f ? Sprite::create("Images/YellowSquare.png") : Sprite::create("Images/CyanSquare.png");
    
    box->setScaleX(size.width/100.0f);
    box->setScaleY(size.height/100.0f);
    
    auto body = PhysicsBody::createBox(size);
    box->setPhysicsBody(body);
    box->setPosition(Point(x, y));
    
    return box;
}

Sprite* PhysicsDemo::makeTriangle(float x, float y, Size size, PhysicsMaterial material)
{
    auto triangle = CCRANDOM_0_1() > 0.5f ? Sprite::create("Images/YellowTriangle.png") : Sprite::create("Images/CyanTriangle.png");
    
    if(size.height == 0)
    {
        triangle->setScale(size.width/100.0f);
    }else
    {
        triangle->setScaleX(size.width/50.0f);
        triangle->setScaleY(size.height/43.5f);
    }
    
    Point vers[] = { Point(0, size.height/2), Point(size.width/2, -size.height/2), Point(-size.width/2, -size.height/2)};
    
    auto body = PhysicsBody::createPolygon(vers, 3);
    triangle->setPhysicsBody(body);
    triangle->setPosition(Point(x, y));
    
    return triangle;
}

bool PhysicsDemo::onTouchBegan(Touch* touch, Event* event)
{
    auto location = touch->getLocation();
    Array* arr = _scene->getPhysicsWorld()->getShapesAtPoint(location);
    
    PhysicsShape* shape = nullptr;
    for (Object* obj : *arr)
    {
        shape = dynamic_cast<PhysicsShape*>(obj);
        
        if (shape->getTag() == 1)
        {
            break;
        }
    }
    
    if (shape != nullptr)
    {
        
        Node* mouse = Node::create();
        mouse->setPhysicsBody(PhysicsBody::create(PHYSICS_INFINITY, PHYSICS_INFINITY));
        mouse->getPhysicsBody()->setDynamic(false);
        mouse->setPosition(location);
        this->addChild(mouse);
        PhysicsJoint* joint = PhysicsJointPin::create(mouse->getPhysicsBody(), shape->getBody(), location);
        _scene->getPhysicsWorld()->addJoint(joint);
        _mouses.insert(std::make_pair(touch->getID(), mouse));
        
        return true;
    }
    
    return false;
}

void PhysicsDemo::onTouchMoved(Touch* touch, Event* event)
{
    auto it = _mouses.find(touch->getID());
    
    if (it != _mouses.end())
    {
        it->second->getPhysicsBody()->setVelocity((touch->getLocation() - it->second->getPosition()) * 60.0f);
        it->second->setPosition(touch->getLocation());
    }
}

void PhysicsDemo::onTouchEnded(Touch* touch, Event* event)
{
    auto it = _mouses.find(touch->getID());
    
    if (it != _mouses.end())
    {
        this->removeChild(it->second);
        _mouses.erase(it);
    }
    
}

void PhysicsDemoLogoSmash::onEnter()
{
    PhysicsDemo::onEnter();
    
    _scene->getPhysicsWorld()->setGravity(Point(0, 0));
    
    _ball = SpriteBatchNode::create("Images/ball.png", sizeof(logo_image)/sizeof(logo_image[0]));
    addChild(_ball);
    for (int y = 0; y < logo_height; ++y)
    {
        for (int x = 0; x < logo_width; ++x)
        {
            if (get_pixel(x, y))
            {
                float x_jitter = 0.05*frand();
                float y_jitter = 0.05*frand();
                
                Node* ball = makeBall(2*(x - logo_width/2 + x_jitter) + VisibleRect::getVisibleRect().size.width/2,
                                      2*(logo_height-y + y_jitter) + VisibleRect::getVisibleRect().size.height/2 - logo_height/2,
                                      0.95f, PhysicsMaterial(1.0f, 0.0f, 0.0f));
                
                ball->getPhysicsBody()->setMass(1.0);
                ball->getPhysicsBody()->setMoment(PHYSICS_INFINITY);
                
                _ball->addChild(ball);
                
            }
        }
    }
    
    
    auto bullet = makeBall(400, 0, 10, PhysicsMaterial(PHYSICS_INFINITY, 0, 0));
    bullet->getPhysicsBody()->setVelocity(Point(400, 0));
    
    bullet->setPosition(Point(-1000, VisibleRect::getVisibleRect().size.height/2));
    
    _ball->addChild(bullet);
}

std::string PhysicsDemoLogoSmash::title()
{
    return "Logo Smash";
}

void PhysicsDemoPyramidStack::onEnter()
{
    PhysicsDemo::onEnter();
    
    setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    
    auto node = Node::create();
    node->setPhysicsBody(PhysicsBody::createEdgeSegment(VisibleRect::leftBottom() + Point(0, 50), VisibleRect::rightBottom() + Point(0, 50)));
    this->addChild(node);
    
    auto ball = Sprite::create("Images/ball.png");
    ball->setScale(1);
    ball->setPhysicsBody(PhysicsBody::createCircle(10));
    ball->setPosition(VisibleRect::bottom() + Point(0, 60));
    this->addChild(ball);
    
	for(int i=0; i<14; i++)
    {
		for(int j=0; j<=i; j++)
        {
			auto sp = addGrossiniAtPosition(VisibleRect::bottom() + Point((i/2 - j) * 11, (14 - i) * 23 + 100), 0.2f);
            
            sp->getPhysicsBody()->setTag(1);
		}
	}
}
std::string PhysicsDemoPyramidStack::title()
{
    return "Pyramid Stack";
}


void PhysicsDemoPlink::onEnter()
{
    PhysicsDemo::onEnter();
    
    auto node = DrawNode::create();
    auto body = PhysicsBody::create();
    body->setDynamic(false);
    node->setPhysicsBody(body);
    
    Point tris[] = { Point(-15, -15), Point(0, 10), Point(15, -15) };
    
    auto rect = VisibleRect::getVisibleRect();
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            Point offset(rect.origin.x + rect.size.width/9*i + (j%2)*40 - 20, rect.origin.y + j*70);
            body->addShape(PhysicsShapePolygon::create(tris, 3, PHYSICSSHAPE_MATERIAL_DEFAULT, offset));
            
            Point drawVec[] = {tris[0] + offset, tris[1] + offset, tris[2] + offset};
            node->drawPolygon(drawVec, 3, STATIC_COLOR, 1, STATIC_COLOR);
        }
    }
    
    addChild(node);
    
}

std::string PhysicsDemoPlink::title()
{
    return "Plink";
}

PhysicsDemoRayCast::PhysicsDemoRayCast()
: _angle(0.0f)
, _node(nullptr)
, _mode(0)
{}

void PhysicsDemoRayCast::onEnter()
{
    PhysicsDemo::onEnter();
    setTouchEnabled(true);
    
    _scene->getPhysicsWorld()->setGravity(Point::ZERO);
    
    auto node = DrawNode::create();
    node->setPhysicsBody(PhysicsBody::createEdgeSegment(VisibleRect::leftBottom() + Point(0, 50), VisibleRect::rightBottom() + Point(0, 50)));
    node->drawSegment(VisibleRect::leftBottom() + Point(0, 50), VisibleRect::rightBottom() + Point(0, 50), 1, STATIC_COLOR);
    this->addChild(node);
    
    MenuItemFont::setFontSize(18);
    auto item = MenuItemFont::create("Change Mode(any)", CC_CALLBACK_1(PhysicsDemoRayCast::changeModeCallback, this));
    
    auto menu = Menu::create(item, NULL);
    this->addChild(menu);
    menu->setPosition(Point(VisibleRect::left().x+100, VisibleRect::top().y-10));
    
    scheduleUpdate();
}

void PhysicsDemoRayCast::changeModeCallback(Object* sender)
{
    _mode = (_mode + 1) % 3;
    
    switch (_mode)
    {
        case 0:
            ((MenuItemFont*)sender)->setString("Change Mode(any)");
            break;
        case 1:
            ((MenuItemFont*)sender)->setString("Change Mode(nearest)");
            break;
        case 2:
            ((MenuItemFont*)sender)->setString("Change Mode(multiple)");
            break;
            
        default:
            break;
    }
}

bool PhysicsDemoRayCast::anyRay(PhysicsWorld& world, PhysicsShape& shape, Point point, Point normal, float fraction, void* data)
{
    *((Point*)data) = point;
    return false;
}

class PhysicsDemoNearestRayCastCallback : public PhysicsRayCastCallback
{
public:
    PhysicsDemoNearestRayCastCallback();

private:
    float _friction;
};

PhysicsDemoNearestRayCastCallback::PhysicsDemoNearestRayCastCallback()
: _friction(1.0f)
{
    report = [this](PhysicsWorld& world, PhysicsShape& shape, Point point, Point normal, float fraction, void* data)->bool
    {
        if (_friction > fraction)
        {
            *((Point*)data) = point;
            _friction = fraction;
        }
        
        return true;
    };
}

namespace
{
    static const int MAX_MULTI_RAYCAST_NUM = 5;
}

class PhysicsDemoMultiRayCastCallback : public PhysicsRayCastCallback
{
public:
    PhysicsDemoMultiRayCastCallback();
    
public:
    Point points[MAX_MULTI_RAYCAST_NUM];
    int num;
};

PhysicsDemoMultiRayCastCallback::PhysicsDemoMultiRayCastCallback()
: num(0)
{
    report = [this](PhysicsWorld& world, PhysicsShape& shape, Point point, Point normal, float fraction, void* data)->bool
    {
        if (num < MAX_MULTI_RAYCAST_NUM)
        {
            points[num++] = point;
        }
        
        return true;
    };
}

void PhysicsDemoRayCast::update(float delta)
{
    float L = 150.0f;
    Point point1 = VisibleRect::center();
    Point d(L * cosf(_angle), L * sinf(_angle));
    Point point2 = point1 + d;
    
    removeChild(_node);
    _node = DrawNode::create();
    switch (_mode)
    {
        case 0:
        {
            PhysicsRayCastCallback callback;
            Point point3 = point2;
            callback.report = anyRay;
            
            _scene->getPhysicsWorld()->rayCast(callback, point1, point2, &point3);
            _node->drawSegment(point1, point3, 1, STATIC_COLOR);
            
            if (point2 != point3)
            {
                _node->drawDot(point3, 2, Color4F(1.0f, 1.0f, 1.0f, 1.0f));
            }
            addChild(_node);
            
            break;
        }
        case 1:
        {
            PhysicsDemoNearestRayCastCallback callback;
            Point point3 = point2;
            
            _scene->getPhysicsWorld()->rayCast(callback, point1, point2, &point3);
            _node->drawSegment(point1, point3, 1, STATIC_COLOR);
            
            if (point2 != point3)
            {
                _node->drawDot(point3, 2, Color4F(1.0f, 1.0f, 1.0f, 1.0f));
            }
            addChild(_node);
            
            break;
        }
        case 2:
        {
            PhysicsDemoMultiRayCastCallback callback;
            
            _scene->getPhysicsWorld()->rayCast(callback, point1, point2, nullptr);
            
            _node->drawSegment(point1, point2, 1, STATIC_COLOR);
            
            for (int i = 0; i < callback.num; ++i)
            {
                _node->drawDot(callback.points[i], 2, Color4F(1.0f, 1.0f, 1.0f, 1.0f));
            }
            
            addChild(_node);
            
            break;
        }
            
        default:
            break;
    }
    
    _angle += 0.25f * (float)M_PI / 180.0f;
}

void PhysicsDemoRayCast::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    //Add a new body/atlas sprite at the touched location
    
    for( auto &touch: touches)
    {
        auto location = touch->getLocation();
        
        float r = CCRANDOM_0_1();
        
        if (r < 1.0f/3.0f)
        {
            addChild(makeBall(location.x, location.y, 5 + CCRANDOM_0_1()*10));
        }else if(r < 2.0f/3.0f)
        {
            addChild(makeBox(location.x, location.y, Size(10 + CCRANDOM_0_1()*15, 10 + CCRANDOM_0_1()*15)));
        }else
        {
            addChild(makeTriangle(location.x, location.y, Size(10 + CCRANDOM_0_1()*20, 10 + CCRANDOM_0_1()*20)));
        }
    }
}

std::string PhysicsDemoRayCast::title()
{
    return "Ray Cast";
}


void PhysicsDemoJoints::onEnter()
{
    PhysicsDemo::onEnter();
    
    setTouchEnabled(true);
    
    _scene->getPhysicsWorld()->setGravity(Point::ZERO);
    
    
}

std::string PhysicsDemoJoints::title()
{
    return "Joints";
}