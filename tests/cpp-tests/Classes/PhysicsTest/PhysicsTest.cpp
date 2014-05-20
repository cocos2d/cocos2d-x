#include "PhysicsTest.h"
#include <cmath>
#include "../testResource.h"
USING_NS_CC;

namespace
{
    static std::function<Layer*()> createFunctions[] = {
#if CC_USE_PHYSICS
        CL(PhysicsDemoLogoSmash),
        CL(PhysicsDemoPyramidStack),
        CL(PhysicsDemoClickAdd),
        CL(PhysicsDemoRayCast),
        CL(PhysicsDemoJoints),
        CL(PhysicsDemoActions),
        CL(PhysicsDemoPump),
        CL(PhysicsDemoOneWayPlatform),
        CL(PhysicsDemoSlice),
        CL(PhysicsDemoBug3988),
        CL(PhysicsContactTest),
        CL(PhysicsPositionRotationTest),
        CL(PhysicsSetGravityEnableTest),
#else
        CL(PhysicsDemoDisabled),
#endif
    };
    
    static int sceneIdx=-1;
#define MAX_LAYER (sizeof(createFunctions) / sizeof(createFunctions[0]))
    
    static Layer* next()
    {
        sceneIdx++;
        sceneIdx = sceneIdx % MAX_LAYER;
        
        auto layer = (createFunctions[sceneIdx])();
        return layer;
    }
    
    static Layer* back()
    {
        sceneIdx--;
        int total = MAX_LAYER;
        if( sceneIdx < 0 )
            sceneIdx += total;
        
        auto layer = (createFunctions[sceneIdx])();
        return layer;
    }
    
    static Layer* restart()
    {
        auto layer = (createFunctions[sceneIdx])();
        return layer;
    }
    
    static const Color4F STATIC_COLOR(1.0f, 0.0f, 0.0f, 1.0f);
    static const int DRAG_BODYS_TAG = 0x80;
}

PhysicsTestScene::PhysicsTestScene()
#if CC_USE_PHYSICS
: TestScene(false, true)
#else
: TestScene()
#endif
, _debugDraw(false)
{}

void PhysicsTestScene::runThisTest()
{
    sceneIdx = -1;
    addChild(next());
    
    Director::getInstance()->replaceScene(this);
}

void PhysicsTestScene::toggleDebug()
{
#if CC_USE_PHYSICS
    _debugDraw = !_debugDraw;
    getPhysicsWorld()->setDebugDrawMask(_debugDraw ? PhysicsWorld::DEBUGDRAW_ALL : PhysicsWorld::DEBUGDRAW_NONE);
#endif
}

#if CC_USE_PHYSICS == 0
void PhysicsDemoDisabled::onEnter()
{
    auto label = Label::createWithTTF("Should define CC_USE_PHYSICS\n to run this test case",
                                  "fonts/arial.ttf",
                                  18);
    auto size = Director::getInstance()->getWinSize();
    label->setPosition(Vec2(size.width/2, size.height/2));
    
    addChild(label);
}
#else

PhysicsDemo::PhysicsDemo()
: _scene(nullptr)
, _spriteTexture(nullptr)
, _ball(nullptr)
{
}

PhysicsDemo::~PhysicsDemo()
{
    
}

std::string PhysicsDemo::title() const
{
    return "PhysicsTest";
}

std::string PhysicsDemo::subtitle() const
{
    return "";
}

void PhysicsDemo::restartCallback(Ref* sender)
{
    auto s = new PhysicsTestScene();
    s->addChild( restart() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void PhysicsDemo::nextCallback(Ref* sender)
{
    auto s = new PhysicsTestScene();
    s->addChild( next() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void PhysicsDemo::backCallback(Ref* sender)
{
    auto s = new PhysicsTestScene();
    s->addChild( back() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void PhysicsDemo::onEnter()
{
    BaseTest::onEnter();
    
    _scene = dynamic_cast<PhysicsTestScene*>(this->getParent());
    
    _spriteTexture = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 100)->getTexture();
    
    // menu for debug layer
    MenuItemFont::setFontSize(18);
    auto item = MenuItemFont::create("Toggle debug", CC_CALLBACK_1(PhysicsDemo::toggleDebugCallback, this));
    
    auto menu = Menu::create(item, NULL);
    this->addChild(menu);
    menu->setPosition(Vec2(VisibleRect::right().x-50, VisibleRect::top().y-10));
}

Sprite* PhysicsDemo::addGrossiniAtPosition(Vec2 p, float scale/* = 1.0*/)
{
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
}


void PhysicsDemo::toggleDebugCallback(Ref* sender)
{
    if (_scene != nullptr)
    {
        _scene->toggleDebug();
    }
}

PhysicsDemoClickAdd::~PhysicsDemoClickAdd()
{
    Device::setAccelerometerEnabled(false);
}

void PhysicsDemoClickAdd::onEnter()
{
    PhysicsDemo::onEnter();
    
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesEnded = CC_CALLBACK_2(PhysicsDemoClickAdd::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    Device::setAccelerometerEnabled(true);
    auto accListener = EventListenerAcceleration::create(CC_CALLBACK_2(PhysicsDemoClickAdd::onAcceleration, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(accListener, this);
    
    auto node = Node::create();
    node->setPhysicsBody(PhysicsBody::createEdgeBox(VisibleRect::getVisibleRect().size));
    node->setPosition(VisibleRect::center());
    this->addChild(node);
    
    addGrossiniAtPosition(VisibleRect::center());
}

std::string PhysicsDemoClickAdd::subtitle() const
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
    static float prevX=0, prevY=0;
    
#define kFilterFactor 0.05f
    
    float accelX = (float) acc->x * kFilterFactor + (1- kFilterFactor)*prevX;
    float accelY = (float) acc->y * kFilterFactor + (1- kFilterFactor)*prevY;
    
    prevX = accelX;
    prevY = accelY;
    
    auto v = Vec2( accelX, accelY);
    v = v * 200;
    
    if(_scene != nullptr)
    {
        _scene->getPhysicsWorld()->setGravity(v);
    }
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

Sprite* PhysicsDemo::makeBall(Vec2 point, float radius, PhysicsMaterial material)
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
    ball->setPosition(Vec2(point.x, point.y));
    
    return ball;
}

Sprite* PhysicsDemo::makeBox(Vec2 point, Size size, int color, PhysicsMaterial material)
{
    bool yellow = false;
    if (color == 0)
    {
        yellow = CCRANDOM_0_1() > 0.5f;
    }else
    {
        yellow = color == 1;
    }
    
    auto box = yellow ? Sprite::create("Images/YellowSquare.png") : Sprite::create("Images/CyanSquare.png");
    
    box->setScaleX(size.width/100.0f);
    box->setScaleY(size.height/100.0f);
    
    auto body = PhysicsBody::createBox(size, material);
    box->setPhysicsBody(body);
    box->setPosition(Vec2(point.x, point.y));
    
    return box;
}

Sprite* PhysicsDemo::makeTriangle(Vec2 point, Size size, int color, PhysicsMaterial material)
{
    bool yellow = false;
    if (color == 0)
    {
        yellow = CCRANDOM_0_1() > 0.5f;
    }else
    {
        yellow = color == 1;
    }
    
    auto triangle = yellow ? Sprite::create("Images/YellowTriangle.png") : Sprite::create("Images/CyanTriangle.png");
    
    if(size.height == 0)
    {
        triangle->setScale(size.width/100.0f);
    }else
    {
        triangle->setScaleX(size.width/50.0f);
        triangle->setScaleY(size.height/43.5f);
    }
    
    Vec2 vers[] = { Vec2(0, size.height/2), Vec2(size.width/2, -size.height/2), Vec2(-size.width/2, -size.height/2)};
    
    auto body = PhysicsBody::createPolygon(vers, 3, material);
    triangle->setPhysicsBody(body);
    triangle->setPosition(Vec2(point.x, point.y));
    
    return triangle;
}

bool PhysicsDemo::onTouchBegan(Touch* touch, Event* event)
{
    auto location = touch->getLocation();
    auto arr = _scene->getPhysicsWorld()->getShapes(location);
    
    PhysicsBody* body = nullptr;
    for (auto& obj : arr)
    {
        if ((obj->getBody()->getTag() & DRAG_BODYS_TAG) != 0)
        {
            body = obj->getBody();
            break;
        }
    }
    
    if (body != nullptr)
    {
        Node* mouse = Node::create();
        mouse->setPhysicsBody(PhysicsBody::create(PHYSICS_INFINITY, PHYSICS_INFINITY));
        mouse->getPhysicsBody()->setDynamic(false);
        mouse->setPosition(location);
        this->addChild(mouse);
        PhysicsJointPin* joint = PhysicsJointPin::construct(mouse->getPhysicsBody(), body, location);
        joint->setMaxForce(5000.0f * body->getMass());
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
    
    _scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    _scene->getPhysicsWorld()->setUpdateRate(5.0f);
    
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
                
                Node* ball = makeBall(Vec2(2*(x - logo_width/2 + x_jitter) + VisibleRect::getVisibleRect().size.width/2,
                                            2*(logo_height-y + y_jitter) + VisibleRect::getVisibleRect().size.height/2 - logo_height/2),
                                      0.95f, PhysicsMaterial(0.01f, 0.0f, 0.0f));
                
                ball->getPhysicsBody()->setMass(1.0);
                ball->getPhysicsBody()->setMoment(PHYSICS_INFINITY);
                
                _ball->addChild(ball);
                
            }
        }
    }
    
    
    auto bullet = makeBall(Vec2(400, 0), 10, PhysicsMaterial(PHYSICS_INFINITY, 0, 0));
    bullet->getPhysicsBody()->setVelocity(Vec2(200, 0));
    
    bullet->setPosition(Vec2(-500, VisibleRect::getVisibleRect().size.height/2));
    
    _ball->addChild(bullet);
}

std::string PhysicsDemoLogoSmash::title() const
{
    return "Logo Smash";
}

void PhysicsDemoPyramidStack::updateOnce(float delta)
{
    auto ball = getChildByTag(100);
    
    ball->setScale(ball->getScale() * 3);
    ball->setPhysicsBody(PhysicsBody::createCircle(30));
    ball->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
}

void PhysicsDemoPyramidStack::onEnter()
{
    PhysicsDemo::onEnter();
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PhysicsDemoPyramidStack::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(PhysicsDemoPyramidStack::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(PhysicsDemoPyramidStack::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto node = Node::create();
    node->setPhysicsBody(PhysicsBody::createEdgeSegment(VisibleRect::leftBottom() + Vec2(0, 50), VisibleRect::rightBottom() + Vec2(0, 50)));
    this->addChild(node);
    
    auto ball = Sprite::create("Images/ball.png");
    ball->setScale(1);
    ball->setTag(100);
    ball->setPhysicsBody(PhysicsBody::createCircle(10));
    ball->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
    ball->setPosition(VisibleRect::bottom() + Vec2(0, 60));
    this->addChild(ball);
    
    scheduleOnce(schedule_selector(PhysicsDemoPyramidStack::updateOnce), 3.0);

    for(int i=0; i<14; i++)
    {
        for(int j=0; j<=i; j++)
        {
            auto sp = addGrossiniAtPosition(VisibleRect::bottom() + Vec2((i/2 - j) * 11, (14 - i) * 23 + 100), 0.2f);
            sp->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
        }
    }
}
std::string PhysicsDemoPyramidStack::title() const
{
    return "Pyramid Stack";
}

PhysicsDemoRayCast::PhysicsDemoRayCast()
: _angle(0.0f)
, _node(nullptr)
, _mode(0)
{}

void PhysicsDemoRayCast::onEnter()
{
    PhysicsDemo::onEnter();
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(PhysicsDemoRayCast::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    _scene->getPhysicsWorld()->setGravity(Point::ZERO);
    
    auto node = DrawNode::create();
    node->setPhysicsBody(PhysicsBody::createEdgeSegment(VisibleRect::leftBottom() + Vec2(0, 50), VisibleRect::rightBottom() + Vec2(0, 50)));
    node->drawSegment(VisibleRect::leftBottom() + Vec2(0, 50), VisibleRect::rightBottom() + Vec2(0, 50), 1, STATIC_COLOR);
    this->addChild(node);
    
    MenuItemFont::setFontSize(18);
    auto item = MenuItemFont::create("Change Mode(any)", CC_CALLBACK_1(PhysicsDemoRayCast::changeModeCallback, this));
    
    auto menu = Menu::create(item, NULL);
    this->addChild(menu);
    menu->setPosition(Vec2(VisibleRect::left().x+100, VisibleRect::top().y-10));
    
    scheduleUpdate();
}

void PhysicsDemoRayCast::changeModeCallback(Ref* sender)
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

bool PhysicsDemoRayCast::anyRay(PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data)
{
    *((Vec2*)data) = info.contact;
    return false;
}

void PhysicsDemoRayCast::update(float delta)
{
    float L = 150.0f;
    Vec2 point1 = VisibleRect::center();
    Vec2 d(L * cosf(_angle), L * sinf(_angle));
    Vec2 point2 = point1 + d;
    
    removeChild(_node);
    _node = DrawNode::create();
    switch (_mode)
    {
        case 0:
        {
            Vec2 point3 = point2;
            auto func = CC_CALLBACK_3(PhysicsDemoRayCast::anyRay, this);
            
            _scene->getPhysicsWorld()->rayCast(func, point1, point2, &point3);
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
            Vec2 point3 = point2;
            float friction = 1.0f;
            PhysicsRayCastCallbackFunc func = [&point3, &friction](PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data)->bool
            {
                if (friction > info.fraction)
                {
                    point3 = info.contact;
                    friction = info.fraction;
                }
                
                return true;
            };
            
            _scene->getPhysicsWorld()->rayCast(func, point1, point2, nullptr);
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
#define MAX_MULTI_RAYCAST_NUM 5
            Vec2 points[MAX_MULTI_RAYCAST_NUM];
            int num = 0;
            
            PhysicsRayCastCallbackFunc func = [&points, &num](PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data)->bool
            {
                if (num < MAX_MULTI_RAYCAST_NUM)
                {
                    points[num++] = info.contact;
                }
                
                return true;
            };
            
            _scene->getPhysicsWorld()->rayCast(func, point1, point2, nullptr);
            
            _node->drawSegment(point1, point2, 1, STATIC_COLOR);
            
            for (int i = 0; i < num; ++i)
            {
                _node->drawDot(points[i], 2, Color4F(1.0f, 1.0f, 1.0f, 1.0f));
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
            addChild(makeBall(location, 5 + CCRANDOM_0_1()*10));
        }else if(r < 2.0f/3.0f)
        {
            addChild(makeBox(location, Size(10 + CCRANDOM_0_1()*15, 10 + CCRANDOM_0_1()*15)));
        }else
        {
            addChild(makeTriangle(location, Size(10 + CCRANDOM_0_1()*20, 10 + CCRANDOM_0_1()*20)));
        }
    }
}

std::string PhysicsDemoRayCast::title() const
{
    return "Ray Cast";
}

void PhysicsDemoJoints::onEnter()
{
    PhysicsDemo::onEnter();
    _scene->toggleDebug();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(PhysicsDemoJoints::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(PhysicsDemoJoints::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(PhysicsDemoJoints::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    //_scene->getPhysicsWorld()->setGravity(Point::ZERO);
    
    float width = (VisibleRect::getVisibleRect().size.width - 10) / 4;
    float height = (VisibleRect::getVisibleRect().size.height - 50) / 4;
    
    Node* node = Node::create();
    PhysicsBody* box = PhysicsBody::create();
    node->setPhysicsBody(box);
    box->setDynamic(false);
    node->setPosition(Point::ZERO);
    this->addChild(node);
    
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            Vec2 offset(VisibleRect::leftBottom().x + 5 + j * width + width/2, VisibleRect::leftBottom().y + 50 + i * height + height/2);
            box->addShape(PhysicsShapeEdgeBox::create(Size(width, height), PHYSICSSHAPE_MATERIAL_DEFAULT, 1, offset));
            
            switch (i*4 + j)
            {
                case 0:
                {
                    auto sp1 = makeBall(offset - Vec2(30, 0), 10);
                    sp1->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    auto sp2 = makeBall(offset + Vec2(30, 0), 10);
                    sp2->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    
                    PhysicsJointPin* joint = PhysicsJointPin::construct(sp1->getPhysicsBody(), sp2->getPhysicsBody(), offset);
                    _scene->getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                case 1:
                {
                    
                    auto sp1 = makeBall(offset - Vec2(30, 0), 10);
                    sp1->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    auto sp2 = makeBox(offset + Vec2(30, 0), Size(30, 10));
                    sp2->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    
                    PhysicsJointFixed* joint = PhysicsJointFixed::construct(sp1->getPhysicsBody(), sp2->getPhysicsBody(), offset);
                    _scene->getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                case 2:
                {
                    
                    auto sp1 = makeBall(offset - Vec2(30, 0), 10);
                    sp1->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    auto sp2 = makeBox(offset + Vec2(30, 0), Size(30, 10));
                    sp2->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    
                    PhysicsJointDistance* joint = PhysicsJointDistance::construct(sp1->getPhysicsBody(), sp2->getPhysicsBody(), Point::ZERO, Point::ZERO);
                    _scene->getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                case 3:
                {
                    auto sp1 = makeBall(offset - Vec2(30, 0), 10);
                    sp1->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    auto sp2 = makeBox(offset + Vec2(30, 0), Size(30, 10));
                    sp2->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    
                    PhysicsJointLimit* joint = PhysicsJointLimit::construct(sp1->getPhysicsBody(), sp2->getPhysicsBody(), Point::ZERO, Point::ZERO, 30.0f, 60.0f);
                    _scene->getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                case 4:
                {
                    auto sp1 = makeBall(offset - Vec2(30, 0), 10);
                    sp1->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    auto sp2 = makeBox(offset + Vec2(30, 0), Size(30, 10));
                    sp2->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    
                    PhysicsJointSpring* joint = PhysicsJointSpring::construct(sp1->getPhysicsBody(), sp2->getPhysicsBody(), Point::ZERO, Point::ZERO, 500.0f, 0.3f);
                    _scene->getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                case 5:
                {
                    auto sp1 = makeBall(offset - Vec2(30, 0), 10);
                    sp1->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    auto sp2 = makeBox(offset + Vec2(30, 0), Size(30, 10));
                    sp2->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    
                    PhysicsJointGroove* joint = PhysicsJointGroove::construct(sp1->getPhysicsBody(), sp2->getPhysicsBody(), Vec2(30, 15), Vec2(30, -15), Vec2(-30, 0));
                    _scene->getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                case 6:
                {
                    auto sp1 = makeBox(offset - Vec2(30, 0), Size(30, 10));
                    sp1->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    auto sp2 = makeBox(offset + Vec2(30, 0), Size(30, 10));
                    sp2->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    
                    _scene->getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp1->getPhysicsBody(), box, sp1->getPosition()));
                    _scene->getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp2->getPhysicsBody(), box, sp2->getPosition()));
                    PhysicsJointRotarySpring* joint = PhysicsJointRotarySpring::construct(sp1->getPhysicsBody(), sp2->getPhysicsBody(), 3000.0f, 60.0f);
                    _scene->getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                case 7:
                {
                    auto sp1 = makeBox(offset - Vec2(30, 0), Size(30, 10));
                    sp1->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    auto sp2 = makeBox(offset + Vec2(30, 0), Size(30, 10));
                    sp2->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    
                    _scene->getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp1->getPhysicsBody(), box, sp1->getPosition()));
                    _scene->getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp2->getPhysicsBody(), box, sp2->getPosition()));
                    PhysicsJointRotaryLimit* joint = PhysicsJointRotaryLimit::construct(sp1->getPhysicsBody(), sp2->getPhysicsBody(), 0.0f,(float) M_PI_2);
                    _scene->getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                case 8:
                {
                    auto sp1 = makeBox(offset - Vec2(30, 0), Size(30, 10));
                    sp1->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    auto sp2 = makeBox(offset + Vec2(30, 0), Size(30, 10));
                    sp2->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    
                    _scene->getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp1->getPhysicsBody(), box, sp1->getPosition()));
                    _scene->getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp2->getPhysicsBody(), box, sp2->getPosition()));
                    PhysicsJointRatchet* joint = PhysicsJointRatchet::construct(sp1->getPhysicsBody(), sp2->getPhysicsBody(), 0.0f, (float)M_PI_2);
                    _scene->getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                case 9:
                {
                    auto sp1 = makeBox(offset - Vec2(30, 0), Size(30, 10));
                    sp1->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    auto sp2 = makeBox(offset + Vec2(30, 0), Size(30, 10));
                    sp2->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    
                    _scene->getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp1->getPhysicsBody(), box, sp1->getPosition()));
                    _scene->getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp2->getPhysicsBody(), box, sp2->getPosition()));
                    PhysicsJointGear* joint = PhysicsJointGear::construct(sp1->getPhysicsBody(), sp2->getPhysicsBody(), 0.0f, 2.0f);
                    _scene->getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                case 10:
                {
                    auto sp1 = makeBox(offset - Vec2(30, 0), Size(30, 10));
                    sp1->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    auto sp2 = makeBox(offset + Vec2(30, 0), Size(30, 10));
                    sp2->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
                    
                    _scene->getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp1->getPhysicsBody(), box, sp1->getPosition()));
                    _scene->getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp2->getPhysicsBody(), box, sp2->getPosition()));
                    PhysicsJointMotor* joint = PhysicsJointMotor::construct(sp1->getPhysicsBody(), sp2->getPhysicsBody(), (float)M_PI_2);
                    _scene->getPhysicsWorld()->addJoint(joint);
                    
                    this->addChild(sp1);
                    this->addChild(sp2);
                    break;
                }
                default:
                    break;
            }
        }
    }
}

std::string PhysicsDemoJoints::title() const
{
    return "Joints";
}

void PhysicsDemoActions::onEnter()
{
    PhysicsDemo::onEnter();
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PhysicsDemoActions::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(PhysicsDemoActions::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(PhysicsDemoActions::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto node = Node::create();
    node->setPhysicsBody(PhysicsBody::createEdgeBox(VisibleRect::getVisibleRect().size));
    node->setPosition(VisibleRect::center());
    this->addChild(node);
    
    Sprite* sp1 = addGrossiniAtPosition(VisibleRect::center());
    Sprite* sp2 = addGrossiniAtPosition(VisibleRect::left() + Vec2(50, 0));
    Sprite* sp3 = addGrossiniAtPosition(VisibleRect::right() - Vec2(20, 0));
    Sprite* sp4 = addGrossiniAtPosition(VisibleRect::leftTop() + Vec2(50, -50));
    sp4->getPhysicsBody()->setGravityEnable(false);
    
    
    auto actionTo = JumpTo::create(2, Vec2(100,100), 50, 4);
    auto actionBy = JumpBy::create(2, Vec2(300,0), 50, 4);
    auto actionUp = JumpBy::create(2, Vec2(0,50), 80, 4);
    auto actionByBack = actionBy->reverse();
    
    sp1->runAction(RepeatForever::create(actionUp));
    sp2->runAction(RepeatForever::create(Sequence::create(actionBy, actionByBack, NULL)));
    sp3->runAction(actionTo);
    sp4->runAction(RepeatForever::create(Sequence::create(actionBy->clone(), actionByBack->clone(), NULL)));
}

std::string PhysicsDemoActions::title() const
{
    return "Actions";
}

void PhysicsDemoPump::onEnter()
{
    PhysicsDemo::onEnter();
    _scene->toggleDebug();
    
    _distance = 0.0f;
    _rotationV = 0.0f;
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PhysicsDemoPump::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(PhysicsDemoPump::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(PhysicsDemoPump::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    scheduleUpdate();
    
    auto node = Node::create();
    auto body = PhysicsBody::create();
    body->setDynamic(false);
    
    PhysicsMaterial staticMaterial(PHYSICS_INFINITY, 0, 0.5f);
    body->addShape(PhysicsShapeEdgeSegment::create(VisibleRect::leftTop() + Vec2(50, 0), VisibleRect::leftTop() + Vec2(50, -130), staticMaterial, 2.0f));
    body->addShape(PhysicsShapeEdgeSegment::create(VisibleRect::leftTop() + Vec2(190, 0), VisibleRect::leftTop() + Vec2(100, -50), staticMaterial, 2.0f));
    body->addShape(PhysicsShapeEdgeSegment::create(VisibleRect::leftTop() + Vec2(100, -50), VisibleRect::leftTop() + Vec2(100, -90), staticMaterial, 2.0f));
    body->addShape(PhysicsShapeEdgeSegment::create(VisibleRect::leftTop() + Vec2(50, -130), VisibleRect::leftTop() + Vec2(100, -145), staticMaterial, 2.0f));
    body->addShape(PhysicsShapeEdgeSegment::create(VisibleRect::leftTop() + Vec2(100, -145), VisibleRect::leftBottom() + Vec2(100, 80), staticMaterial, 2.0f));
    body->addShape(PhysicsShapeEdgeSegment::create(VisibleRect::leftTop() + Vec2(150, -80), VisibleRect::leftBottom() + Vec2(150, 80), staticMaterial, 2.0f));
    body->addShape(PhysicsShapeEdgeSegment::create(VisibleRect::leftTop() + Vec2(150, -80), VisibleRect::rightTop() + Vec2(-100, -150), staticMaterial, 2.0f));
    
    body->setCategoryBitmask(0x01);
    
    // balls
    for (int i = 0; i < 6; ++i)
    {
        auto ball = makeBall(VisibleRect::leftTop() + Vec2(75 + CCRANDOM_0_1() * 90, 0), 22, PhysicsMaterial(0.05f, 0.0f, 0.1f));
        ball->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
        addChild(ball);
    }
    
    node->setPhysicsBody(body);
    this->addChild(node);
    
    Vec2 vec[4] =
    {
        VisibleRect::leftTop() + Vec2(102, -148),
        VisibleRect::leftTop() + Vec2(148, -161),
        VisibleRect::leftBottom() + Vec2(148, 20),
        VisibleRect::leftBottom() + Vec2(102, 20)
    };
    
    auto _world = _scene->getPhysicsWorld();
    
    // small gear
    auto sgear = Node::create();
    auto sgearB = PhysicsBody::createCircle(44);
    sgear->setPhysicsBody(sgearB);
    sgear->setPosition(VisibleRect::leftBottom() + Vec2(125, 0));
    this->addChild(sgear);
    sgearB->setCategoryBitmask(0x04);
    sgearB->setCollisionBitmask(0x04);
    sgearB->setTag(1);
    _world->addJoint(PhysicsJointPin::construct(body, sgearB, sgearB->getPosition()));
    
    
    // big gear
    auto bgear = Node::create();
    auto bgearB = PhysicsBody::createCircle(100);
    bgear->setPhysicsBody(bgearB);
    bgear->setPosition(VisibleRect::leftBottom() + Vec2(275, 0));
    this->addChild(bgear);
    bgearB->setCategoryBitmask(0x04);
    _world->addJoint(PhysicsJointPin::construct(body, bgearB, bgearB->getPosition()));
    
    
    // pump
    auto pump = Node::create();
    auto center = PhysicsShape::getPolyonCenter(vec, 4);
    pump->setPosition(center);
    auto pumpB = PhysicsBody::createPolygon(vec, 4, PHYSICSBODY_MATERIAL_DEFAULT, -center);
    pump->setPhysicsBody(pumpB);
    this->addChild(pump);
    pumpB->setCategoryBitmask(0x02);
    pumpB->setGravityEnable(false);
    _world->addJoint(PhysicsJointDistance::construct(pumpB, sgearB, Vec2(0, 0), Vec2(0, -44)));
    
    // plugger
    Vec2 seg[] = {VisibleRect::leftTop() + Vec2(75, -120), VisibleRect::leftBottom() + Vec2(75, -100)};
    Vec2 segCenter = (seg[1] + seg[0])/2;
    seg[1] -= segCenter;
    seg[0] -= segCenter;
    auto plugger = Node::create();
    auto pluggerB = PhysicsBody::createEdgeSegment(seg[0], seg[1], PhysicsMaterial(0.01f, 0.0f, 0.5f), 20);
    pluggerB->setDynamic(true);
    pluggerB->setMass(30);
    pluggerB->setMoment(100000);
    plugger->setPhysicsBody(pluggerB);
    plugger->setPosition(segCenter);
    this->addChild(plugger);
    pluggerB->setCategoryBitmask(0x02);
    sgearB->setCollisionBitmask(0x04 | 0x01);
    _world->addJoint(PhysicsJointPin::construct(body, pluggerB, VisibleRect::leftBottom() + Vec2(75, -90)));
    _world->addJoint(PhysicsJointDistance::construct(pluggerB, sgearB, pluggerB->world2Local(VisibleRect::leftBottom() + Vec2(75, 0)), Vec2(44, 0)));
}

void PhysicsDemoPump::update(float delta)
{
    for (const auto& body : _scene->getPhysicsWorld()->getAllBodies())
    {
        if (body->getTag() == DRAG_BODYS_TAG && body->getPosition().y < 0.0f)
        {
            body->getNode()->setPosition(VisibleRect::leftTop() + Vec2(75 + CCRANDOM_0_1() * 90, 0));
            body->setVelocity(Vec2(0, 0));
        }
    }
    
    PhysicsBody* gear = _scene->getPhysicsWorld()->getBody(1);
    
    if (gear != nullptr)
    {
        if (_distance != 0.0f)
        {
            _rotationV += _distance/2500.0f;
            
            if (_rotationV > 30) _rotationV = 30.0f;
            if (_rotationV < -30) _rotationV = -30.0f;
        }
        
        gear->setAngularVelocity(_rotationV);
        _rotationV *= 0.995f;
    }
}

bool PhysicsDemoPump::onTouchBegan(Touch* touch, Event* event)
{
    PhysicsDemo::onTouchBegan(touch, event);
    
    _distance = touch->getLocation().x - VisibleRect::center().x;
    
    return true;
}

void PhysicsDemoPump::onTouchMoved(Touch* touch, Event* event)
{
    PhysicsDemo::onTouchMoved(touch, event);
    
    _distance = touch->getLocation().x - VisibleRect::center().x;
}

void PhysicsDemoPump::onTouchEnded(Touch* touch, Event* event)
{
    PhysicsDemo::onTouchEnded(touch, event);
    
    _distance = 0;
}

std::string PhysicsDemoPump::title() const
{
    return "Pump";
}

std::string PhysicsDemoPump::subtitle() const
{
    return "touch screen on left or right";
}

void PhysicsDemoOneWayPlatform::onEnter()
{
    PhysicsDemo::onEnter();
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PhysicsDemoOneWayPlatform::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(PhysicsDemoOneWayPlatform::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(PhysicsDemoOneWayPlatform::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto ground = Node::create();
    ground->setPhysicsBody(PhysicsBody::createEdgeSegment(VisibleRect::leftBottom() + Vec2(0, 50), VisibleRect::rightBottom() + Vec2(0, 50)));
    this->addChild(ground);
    
    auto platform = makeBox(VisibleRect::center(), Size(200, 50));
    platform->getPhysicsBody()->setDynamic(false);
    platform->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
    this->addChild(platform);
    
    auto ball = makeBall(VisibleRect::center() - Vec2(0, 50), 20);
    ball->getPhysicsBody()->setVelocity(Vec2(0, 150));
    ball->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
    ball->getPhysicsBody()->setMass(1.0f);
    ball->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
    this->addChild(ball);
    
    auto contactListener = EventListenerPhysicsContactWithBodies::create(platform->getPhysicsBody(), ball->getPhysicsBody());
    contactListener->onContactBegin = CC_CALLBACK_1(PhysicsDemoOneWayPlatform::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool PhysicsDemoOneWayPlatform::onContactBegin(PhysicsContact& contact)
{
    return contact.getContactData()->normal.y < 0;
}

std::string PhysicsDemoOneWayPlatform::title() const
{
    return "One Way Platform";
}

void PhysicsDemoSlice::onEnter()
{
    PhysicsDemo::onEnter();
    _scene->toggleDebug();
    
    _sliceTag = 1;
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [](Touch* touch, Event* event)->bool{ return true; };
    touchListener->onTouchEnded = CC_CALLBACK_2(PhysicsDemoSlice::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto ground = Node::create();
    ground->setPhysicsBody(PhysicsBody::createEdgeSegment(VisibleRect::leftBottom() + Vec2(0, 50), VisibleRect::rightBottom() + Vec2(0, 50)));
    this->addChild(ground);
    
    auto box = Node::create();
    Vec2 points[4] = {Vec2(-100, -100), Vec2(-100, 100), Vec2(100, 100), Vec2(100, -100)};
    box->setPhysicsBody(PhysicsBody::createPolygon(points, 4));
    box->setPosition(VisibleRect::center());
    box->getPhysicsBody()->setTag(_sliceTag);
    addChild(box);
}

bool PhysicsDemoSlice::slice(PhysicsWorld &world, const PhysicsRayCastInfo& info, void *data)
{
    if (info.shape->getBody()->getTag() != _sliceTag)
    {
        return true;
    }
    
    if (!info.shape->containsPoint(info.start) && !info.shape->containsPoint(info.end))
    {
        Vec2 normal = info.end - info.start;
        normal = normal.getPerp().getNormalized();
        float dist = info.start.dot(normal);
        
        clipPoly(dynamic_cast<PhysicsShapePolygon*>(info.shape), normal, dist);
        clipPoly(dynamic_cast<PhysicsShapePolygon*>(info.shape), -normal, -dist);
        
        info.shape->getBody()->removeFromWorld();
    }
    
    return true;
}

void PhysicsDemoSlice::clipPoly(PhysicsShapePolygon* shape, Vec2 normal, float distance)
{
    PhysicsBody* body = shape->getBody();
    int count = shape->getPointsCount();
    int pointsCount = 0;
    Vec2* points = new Vec2[count + 1];
    
    for (int i=0, j=count-1; i<count; j=i, ++i)
    {
        Vec2 a = body->local2World(shape->getPoint(j));
        float aDist = a.dot(normal) - distance;
        
        if (aDist < 0.0f)
        {
            points[pointsCount] = a;
            ++pointsCount;
        }
        
        Vec2 b = body->local2World(shape->getPoint(i));
        float bDist = b.dot(normal) - distance;
        
        if (aDist*bDist < 0.0f)
        {
            float t = std::fabs(aDist)/(std::fabs(aDist) + std::fabs(bDist));
            points[pointsCount] = a.lerp(b, t);
            ++pointsCount;
        }
    }
    
    Vec2 center = PhysicsShape::getPolyonCenter(points, pointsCount);
    Node* node = Node::create();
    PhysicsBody* polyon = PhysicsBody::createPolygon(points, pointsCount, PHYSICSBODY_MATERIAL_DEFAULT, -center);
    node->setPosition(center);
    node->setPhysicsBody(polyon);
    polyon->setVelocity(body->getVelocityAtWorldPoint(center));
    polyon->setAngularVelocity(body->getAngularVelocity());
    polyon->setTag(_sliceTag);
    addChild(node);
    
    delete[] points;
}

void PhysicsDemoSlice::onTouchEnded(Touch *touch, Event *event)
{
    auto func = CC_CALLBACK_3(PhysicsDemoSlice::slice, this);
    _scene->getPhysicsWorld()->rayCast(func, touch->getStartLocation(), touch->getLocation(), nullptr);
}

std::string PhysicsDemoSlice::title() const
{
    return "Slice";
}

std::string PhysicsDemoSlice::subtitle() const
{
    return "click and drag to slice up the block";
}


void PhysicsDemoBug3988::onEnter()
{
    PhysicsDemo::onEnter();
    _scene->toggleDebug();
	_scene->getPhysicsWorld()->setGravity(Vect::ZERO);

	auto ball  = Sprite::create("Images/YellowSquare.png");
	ball->setPosition(VisibleRect::center() - Vec2(100, 0));
	ball->setRotation(30.0f);
	this->addChild(ball);

	auto physicsBall = makeBox(VisibleRect::center() + Vec2(100, 0), Size(100, 100));
	physicsBall->setRotation(30.0f);
	this->addChild(physicsBall);
}

std::string PhysicsDemoBug3988::title() const
{
    return "Bug3988";
}

std::string PhysicsDemoBug3988::subtitle() const
{
    return "All the Rectangles should have same rotation angle";
}

void PhysicsContactTest::onEnter()
{
    PhysicsDemo::onEnter();
	_scene->getPhysicsWorld()->setGravity(Vect::ZERO);
    auto s = VisibleRect::getVisibleRect().size;
    
    _yellowBoxNum = 50;
    _blueBoxNum = 50;
    _yellowTriangleNum = 50;
    _blueTriangleNum = 50;
    
    
    MenuItemFont::setFontSize(65);
    auto decrease1 = MenuItemFont::create(" - ", CC_CALLBACK_1(PhysicsContactTest::onDecrease, this));
    decrease1->setColor(Color3B(0,200,20));
    auto increase1 = MenuItemFont::create(" + ", CC_CALLBACK_1(PhysicsContactTest::onIncrease, this));
    increase1->setColor(Color3B(0,200,20));
    decrease1->setTag(1);
    increase1->setTag(1);
    
    auto menu1 = Menu::create(decrease1, increase1, NULL);
    menu1->alignItemsHorizontally();
    menu1->setPosition(Vec2(s.width/2, s.height-50));
    addChild(menu1, 1);
    
    auto label = Label::createWithTTF("yellow box", "fonts/arial.ttf", 32);
    addChild(label, 1);
    label->setPosition(Vec2(s.width/2 - 150, s.height-50));
    
    auto decrease2 = MenuItemFont::create(" - ", CC_CALLBACK_1(PhysicsContactTest::onDecrease, this));
    decrease2->setColor(Color3B(0,200,20));
    auto increase2 = MenuItemFont::create(" + ", CC_CALLBACK_1(PhysicsContactTest::onIncrease, this));
    increase2->setColor(Color3B(0,200,20));
    decrease2->setTag(2);
    increase2->setTag(2);
    
    auto menu2 = Menu::create(decrease2, increase2, NULL);
    menu2->alignItemsHorizontally();
    menu2->setPosition(Vec2(s.width/2, s.height-90));
    addChild(menu2, 1);
    
    label = Label::createWithTTF("blue box", "fonts/arial.ttf", 32);
    addChild(label, 1);
    label->setPosition(Vec2(s.width/2 - 150, s.height-90));
    
    auto decrease3 = MenuItemFont::create(" - ", CC_CALLBACK_1(PhysicsContactTest::onDecrease, this));
    decrease3->setColor(Color3B(0,200,20));
    auto increase3 = MenuItemFont::create(" + ", CC_CALLBACK_1(PhysicsContactTest::onIncrease, this));
    increase3->setColor(Color3B(0,200,20));
    decrease3->setTag(3);
    increase3->setTag(3);
    
    auto menu3 = Menu::create(decrease3, increase3, NULL);
    menu3->alignItemsHorizontally();
    menu3->setPosition(Vec2(s.width/2, s.height-130));
    addChild(menu3, 1);
    
    label = Label::createWithTTF("yellow triangle", "fonts/arial.ttf", 32);
    addChild(label, 1);
    label->setPosition(Vec2(s.width/2 - 150, s.height-130));
    
    auto decrease4 = MenuItemFont::create(" - ", CC_CALLBACK_1(PhysicsContactTest::onDecrease, this));
    decrease4->setColor(Color3B(0,200,20));
    auto increase4 = MenuItemFont::create(" + ", CC_CALLBACK_1(PhysicsContactTest::onIncrease, this));
    increase4->setColor(Color3B(0,200,20));
    decrease4->setTag(4);
    increase4->setTag(4);
    
    auto menu4 = Menu::create(decrease4, increase4, NULL);
    menu4->alignItemsHorizontally();
    menu4->setPosition(Vec2(s.width/2, s.height-170));
    addChild(menu4, 1);
    
    label = Label::createWithTTF("blue triangle", "fonts/arial.ttf", 32);
    addChild(label, 1);
    label->setPosition(Vec2(s.width/2 - 150, s.height-170));
	
    resetTest();
}

void PhysicsContactTest::onDecrease(Ref* sender)
{
    switch (dynamic_cast<Node*>(sender)->getTag())
    {
        case 1:
            if(_yellowBoxNum > 0) _yellowBoxNum -= 50;
            break;
        case 2:
            if(_blueBoxNum > 0) _blueBoxNum -= 50;
            break;
        case 3:
            if(_yellowTriangleNum > 0) _yellowTriangleNum -= 50;
            break;
        case 4:
            if(_blueTriangleNum > 0) _blueTriangleNum -= 50;
            break;
            
        default:
            break;
    }
    
    resetTest();
}

void PhysicsContactTest::onIncrease(Ref* sender)
{
    switch (dynamic_cast<Node*>(sender)->getTag())
    {
        case 1:
            _yellowBoxNum += 50;
            break;
        case 2:
            _blueBoxNum += 50;
            break;
        case 3:
            _yellowTriangleNum += 50;
            break;
        case 4:
            _blueTriangleNum += 50;
            break;
            
        default:
            break;
    }
    
    resetTest();
}

void PhysicsContactTest::resetTest()
{
    removeChildByTag(10);
    auto root = Node::create();
    root->setTag(10);
    this->addChild(root);
    
    auto s = VisibleRect::getVisibleRect().size;
    std::string strNum;
    char buffer[10];
    
    sprintf(buffer, "%d", _yellowBoxNum);
    auto label = Label::createWithTTF(buffer, "fonts/arial.ttf", 32);
    root->addChild(label, 1);
    label->setPosition(Vec2(s.width/2, s.height-50));
    
    sprintf(buffer, "%d", _blueBoxNum);
    label = Label::createWithTTF(buffer, "fonts/arial.ttf", 32);
    root->addChild(label, 1);
    label->setPosition(Vec2(s.width/2, s.height-90));
    
    sprintf(buffer, "%d", _yellowTriangleNum);
    label = Label::createWithTTF(buffer, "fonts/arial.ttf", 32);
    root->addChild(label, 1);
    label->setPosition(Vec2(s.width/2, s.height-130));
    
    sprintf(buffer, "%d", _blueTriangleNum);
    label = Label::createWithTTF(buffer, "fonts/arial.ttf", 32);
    root->addChild(label, 1);
    label->setPosition(Vec2(s.width/2, s.height-170));
    
    auto wall = Node::create();
    wall->setPhysicsBody(PhysicsBody::createEdgeBox(VisibleRect::getVisibleRect().size, PhysicsMaterial(0.1f, 1, 0.0f)));
    wall->setPosition(VisibleRect::center());
    root->addChild(wall);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(PhysicsContactTest::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    // yellow box, will collide with itself and blue box.
    for (int i = 0; i < _yellowBoxNum; ++i)
    {
        Size size(10 + CCRANDOM_0_1()*10, 10 + CCRANDOM_0_1()*10);
        Size winSize = VisibleRect::getVisibleRect().size;
        Vec2 position = Vec2(winSize.width, winSize.height) - Vec2(size.width, size.height);
        position.x = position.x * CCRANDOM_0_1();
        position.y = position.y * CCRANDOM_0_1();
        position = VisibleRect::leftBottom() + position + Vec2(size.width/2, size.height/2);
        Vect velocity((CCRANDOM_0_1() - 0.5)*200, (CCRANDOM_0_1() - 0.5)*200);
        auto box = makeBox(position, size, 1, PhysicsMaterial(0.1f, 1, 0.0f));
        box->getPhysicsBody()->setVelocity(velocity);
        box->getPhysicsBody()->setCategoryBitmask(0x01);    // 0001
        box->getPhysicsBody()->setContactTestBitmask(0x04); // 0100
        box->getPhysicsBody()->setCollisionBitmask(0x03);   // 0011
        root->addChild(box);
    }
    
    // blue box, will collide with blue box.
    for (int i = 0; i < _blueBoxNum; ++i)
    {
        Size size(10 + CCRANDOM_0_1()*10, 10 + CCRANDOM_0_1()*10);
        Size winSize = VisibleRect::getVisibleRect().size;
        Vec2 position = Vec2(winSize.width, winSize.height) - Vec2(size.width, size.height);
        position.x = position.x * CCRANDOM_0_1();
        position.y = position.y * CCRANDOM_0_1();
        position = VisibleRect::leftBottom() + position + Vec2(size.width/2, size.height/2);
        Vect velocity((CCRANDOM_0_1() - 0.5)*200, (CCRANDOM_0_1() - 0.5)*200);
        auto box = makeBox(position, size, 2, PhysicsMaterial(0.1f, 1, 0.0f));
        box->getPhysicsBody()->setVelocity(velocity);
        box->getPhysicsBody()->setCategoryBitmask(0x02);    // 0010
        box->getPhysicsBody()->setContactTestBitmask(0x08); // 1000
        box->getPhysicsBody()->setCollisionBitmask(0x01);   // 0001
        root->addChild(box);
    }
    
    // yellow triangle, will collide with itself and blue box.
    for (int i = 0; i < _yellowTriangleNum; ++i)
    {
        Size size(10 + CCRANDOM_0_1()*10, 10 + CCRANDOM_0_1()*10);
        Size winSize = VisibleRect::getVisibleRect().size;
        Vec2 position = Vec2(winSize.width, winSize.height) - Vec2(size.width, size.height);
        position.x = position.x * CCRANDOM_0_1();
        position.y = position.y * CCRANDOM_0_1();
        position = VisibleRect::leftBottom() + position + Vec2(size.width/2, size.height/2);
        Vect velocity((CCRANDOM_0_1() - 0.5)*300, (CCRANDOM_0_1() - 0.5)*300);
        auto triangle = makeTriangle(position, size, 1, PhysicsMaterial(0.1f, 1, 0.0f));
        triangle->getPhysicsBody()->setVelocity(velocity);
        triangle->getPhysicsBody()->setCategoryBitmask(0x04);    // 0100
        triangle->getPhysicsBody()->setContactTestBitmask(0x01); // 0001
        triangle->getPhysicsBody()->setCollisionBitmask(0x06);   // 0110
        root->addChild(triangle);
    }
    
    // blue triangle, will collide with yellow box.
    for (int i = 0; i < _blueTriangleNum; ++i)
    {
        Size size(10 + CCRANDOM_0_1()*10, 10 + CCRANDOM_0_1()*10);
        Size winSize = VisibleRect::getVisibleRect().size;
        Vec2 position = Vec2(winSize.width, winSize.height) - Vec2(size.width, size.height);
        position.x = position.x * CCRANDOM_0_1();
        position.y = position.y * CCRANDOM_0_1();
        position = VisibleRect::leftBottom() + position + Vec2(size.width/2, size.height/2);
        Vect velocity((CCRANDOM_0_1() - 0.5)*300, (CCRANDOM_0_1() - 0.5)*300);
        auto triangle = makeTriangle(position, size, 2, PhysicsMaterial(0.1f, 1, 0.0f));
        triangle->getPhysicsBody()->setVelocity(velocity);
        triangle->getPhysicsBody()->setCategoryBitmask(0x08);    // 1000
        triangle->getPhysicsBody()->setContactTestBitmask(0x02); // 0010
        triangle->getPhysicsBody()->setCollisionBitmask(0x01);   // 0001
        root->addChild(triangle);
    }
}

bool PhysicsContactTest::onContactBegin(PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    PhysicsBody* body = (a->getCategoryBitmask() == 0x04 || a->getCategoryBitmask() == 0x08) ? a : b;
    CC_UNUSED_PARAM(body);
    CC_ASSERT(body->getCategoryBitmask() == 0x04 || body->getCategoryBitmask() == 0x08);
    
    return true;
}

std::string PhysicsContactTest::title() const
{
    return "Contact Test";
}

std::string PhysicsContactTest::subtitle() const
{
    return "should not crash";
}

void PhysicsPositionRotationTest::onEnter()
{
    PhysicsDemo::onEnter();
    _scene->toggleDebug();
    _scene->getPhysicsWorld()->setGravity(Point::ZERO);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PhysicsDemo::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(PhysicsDemo::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(PhysicsDemo::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto wall = Node::create();
    wall->setPhysicsBody(PhysicsBody::createEdgeBox(VisibleRect::getVisibleRect().size));
    wall->setPosition(VisibleRect::center());
    addChild(wall);
    
    // anchor test
    auto anchorNode = Sprite::create("Images/YellowSquare.png");
    anchorNode->setAnchorPoint(Vec2(0.1f, 0.9f));
    anchorNode->setPosition(100, 100);
    anchorNode->setScale(0.25);
    anchorNode->setPhysicsBody(PhysicsBody::createBox(anchorNode->getContentSize()*anchorNode->getScale()));
    anchorNode->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
    addChild(anchorNode);
    
    //parent test
    auto parent = Sprite::create("Images/YellowSquare.png");
    parent->setPosition(200, 100);
    parent->setScale(0.25);
    parent->setPhysicsBody(PhysicsBody::createBox(parent->getContentSize()*anchorNode->getScale()));
    parent->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
    addChild(parent);
    
    auto leftBall = Sprite::create("Images/ball.png");
    leftBall->setPosition(-30, 0);
    leftBall->cocos2d::Node::setScale(2);
    leftBall->setPhysicsBody(PhysicsBody::createCircle(leftBall->getContentSize().width/4));
    leftBall->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
    parent->addChild(leftBall);
    
    // offset position rotation test
    auto offsetPosNode = Sprite::create("Images/YellowSquare.png");
    offsetPosNode->setPosition(100, 200);
    offsetPosNode->setPhysicsBody(PhysicsBody::createBox(offsetPosNode->getContentSize()/2));
    offsetPosNode->getPhysicsBody()->setPositionOffset(-Vec2(offsetPosNode->getContentSize()/2));
    offsetPosNode->getPhysicsBody()->setRotationOffset(45);
    offsetPosNode->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
    addChild(offsetPosNode);
    
    return;
}

std::string PhysicsPositionRotationTest::title() const
{
    return "Position/Rotation Test";
}


void PhysicsSetGravityEnableTest::onEnter()
{
    PhysicsDemo::onEnter();
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PhysicsDemo::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(PhysicsDemo::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(PhysicsDemo::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    // wall
    auto wall = Node::create();
    wall->setPhysicsBody(PhysicsBody::createEdgeBox(VisibleRect::getVisibleRect().size, PhysicsMaterial(0.1f, 1.0f, 0.0f)));
    wall->setPosition(VisibleRect::center());
    addChild(wall);
    
    // common box
    auto commonBox = makeBox(Vec2(100, 100), Size(50, 50), 1);
    commonBox->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
    addChild(commonBox);
    
    auto box = makeBox(Vec2(200, 100), Size(50, 50), 2);
    box->getPhysicsBody()->setMass(20);
    box->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
    box->getPhysicsBody()->setGravityEnable(false);
    addChild(box);
    
    auto ball = makeBall(Vec2(200, 200), 50);
    ball->setTag(2);
    ball->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
    ball->getPhysicsBody()->setGravityEnable(false);
    addChild(ball);
    ball->getPhysicsBody()->setMass(50);
    scheduleOnce(schedule_selector(PhysicsSetGravityEnableTest::onScheduleOnce), 1.0);
}

void PhysicsSetGravityEnableTest::onScheduleOnce(float delta)
{
    auto ball = getChildByTag(2);
    ball->getPhysicsBody()->setMass(200);
    
    _scene->getPhysicsWorld()->setGravity(Vect(0, 98));
}

std::string PhysicsSetGravityEnableTest::title() const
{
    return "Set Gravity Enable Test";
}

std::string PhysicsSetGravityEnableTest::subtitle() const
{
    return "only yellow box drop down";
}

#endif // ifndef CC_USE_PHYSICS
