/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#if (CC_ENABLE_BULLET_INTEGRATION)

#include "Physics3DTest.h"
#include "extensions/Physics3D/CCPhysics3D.h"
USING_NS_CC_EXT;

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

static int sceneIdx = -1;
static Scene* physicsScene = nullptr;

#define START_POS_X -0.5
#define START_POS_Y -2.5
#define START_POS_Z -0.5

#define ARRAY_SIZE_X 5
#define ARRAY_SIZE_Y 5
#define ARRAY_SIZE_Z 5

static std::function<Layer*()> createFunctions[] =
{
    CL(BasicPhysics3DDemo),
    CL(Physics3DConstraintDemo),
    CL(Physics3DKinematicDemo),
    CL(Physics3DTerrainDemo),
};

#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))

static Layer* nextSpriteTestAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

static Layer* backSpriteTestAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;

    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

static Layer* restartSpriteTestAction()
{
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

void Physics3DTestScene::runThisTest()
{
    auto layer = nextSpriteTestAction();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
}

Physics3DTestScene::Physics3DTestScene()
#if CC_USE_3D_PHYSICS
: TestScene(false, true)
#else
: TestScene()
#endif
{
    getPhysics3DWorld()->setDebugDrawEnable(true);

    physicsScene = this;
}

void Physics3DTestDemo::restartCallback( Ref* sender )
{
    auto s = new (std::nothrow) Physics3DTestScene();
    s->addChild(restartSpriteTestAction());

    Director::getInstance()->replaceScene(s);
    s->release();
}

void Physics3DTestDemo::nextCallback( Ref* sender )
{
    auto s = new (std::nothrow) Physics3DTestScene();
    s->addChild( nextSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void Physics3DTestDemo::backCallback( Ref* sender )
{
    auto s = new (std::nothrow) Physics3DTestScene();
    s->addChild( backSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

std::string Physics3DTestDemo::title() const
{
    return "Physics3D Test";
}

std::string Physics3DTestDemo::subtitle() const
{
    return "";
}

bool Physics3DTestDemo::init()
{
    if (!BaseTest::init()) return false;

    Size size = Director::getInstance()->getWinSize();
    _camera = Camera::createPerspective(30.0f, size.width / size.height, 1.0f, 1000.0f);
    _camera->setPosition3D(Vec3(0.0f, 50.0f, 100.0f));
    _camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
    _camera->setCameraFlag(CameraFlag::USER1);
    this->addChild(_camera);

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(Physics3DTestDemo::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Physics3DTestDemo::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Physics3DTestDemo::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    _angle = 0.0f;
    return true;
}

void Physics3DTestDemo::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    _needShootBox = true;
}

void Physics3DTestDemo::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    if (touches.size() && _camera)
    {
        auto touch = touches[0];
        auto delta = touch->getDelta();

        _angle -= CC_DEGREES_TO_RADIANS(delta.x);
        _camera->setPosition3D(Vec3(100.0f * sinf(_angle), 50.0f, 100.0f * cosf(_angle)));
        _camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));

        if (delta.lengthSquared() > 16)
        {
            _needShootBox = false;
        }
    }
}

void Physics3DTestDemo::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    if (!_needShootBox) return;
    if (!touches.empty())
    {
        auto location = touches[0]->getLocationInView();

        Vec3 nearP(location.x, location.y, -1.0f), farP(location.x, location.y, 1.0f);
        nearP = _camera->unproject(nearP);
        farP = _camera->unproject(farP);
        Vec3 dir(farP - nearP);
        shootBox(_camera->getPosition3D() + dir * 10.0f);
    }
}

Physics3DTestDemo::Physics3DTestDemo( void )
: _angle(0.0f)
, _camera(nullptr)
{

}

void Physics3DTestDemo::update( float delta )
{
    
}

Physics3DTestDemo::~Physics3DTestDemo( void )
{
    
}

void Physics3DTestDemo::shootBox( const cocos2d::Vec3 &des )
{
    Physics3DRigidBodyDes rbDes;
    auto sprite = Sprite3D::create("Sprite3DTest/box.c3t");
    sprite->setTexture("Images/Icon.png");

    Vec3 linearVel = des - _camera->getPosition3D();
    linearVel.normalize();
    linearVel *= 100.0f;
    rbDes.originalTransform.translate(_camera->getPosition3D());
    rbDes.mass = 1.f;
    rbDes.shape = Physics3DShape::createBox(Vec3(0.5f, 0.5f, 0.5f));
    auto rigidBody = Physics3DRigidBody::create(&rbDes);
    rigidBody->setLinearFactor(Vec3::ONE);
    rigidBody->setLinearVelocity(linearVel);
    rigidBody->setAngularVelocity(Vec3::ZERO);
    rigidBody->setCcdMotionThreshold(0.5f);
    rigidBody->setCcdSweptSphereRadius(0.4f);

    auto component = Physics3DComponent::create(rigidBody);
    
    sprite->addComponent(component);
    this->addChild(sprite);
    sprite->setPosition3D(_camera->getPosition3D());
    
    sprite->setCameraMask((unsigned short)CameraFlag::USER1);
}

std::string BasicPhysics3DDemo::subtitle() const
{
    return "Basic Physics3D";
}

bool BasicPhysics3DDemo::init()
{
    if (!Physics3DTestDemo::init())
        return false;

    //create floor
    Physics3DRigidBodyDes rbDes;
    rbDes.mass = 0.0f;
    rbDes.shape = Physics3DShape::createBox(Vec3(60.0f, 1.0f, 60.0f));
    
    auto rigidBody = Physics3DRigidBody::create(&rbDes);
    auto component = Physics3DComponent::create(rigidBody);
    auto floor = Sprite3D::create("Sprite3DTest/box.c3t");
    floor->setTexture("Sprite3DTest/plane.png");
    floor->setScaleX(60);
    floor->setScaleZ(60);
    floor->setCameraMask((unsigned short)CameraFlag::USER1);
    
    floor->addComponent(component);
    this->addChild(floor);

    //create several boxes
    rbDes.mass = 1.f;
    rbDes.shape = Physics3DShape::createBox(Vec3(1.0f, 1.0f, 1.0f));
    float start_x = START_POS_X - ARRAY_SIZE_X/2;
    float start_y = START_POS_Y;
    float start_z = START_POS_Z - ARRAY_SIZE_Z/2;

    for (int k=0;k<ARRAY_SIZE_Y;k++)
    {
        for (int i=0;i<ARRAY_SIZE_X;i++)
        {
            for(int j = 0;j<ARRAY_SIZE_Z;j++)
            {
                float x = 1.0*i + start_x;
                float y = 5.0+1.0*k + start_y;
                float z = 1.0*j + start_z;
                
                rigidBody = Physics3DRigidBody::create(&rbDes);
                component = Physics3DComponent::create(rigidBody);
                auto sprite = Sprite3D::create("Sprite3DTest/box.c3t");
                sprite->setTexture("Images/CyanSquare.png");
                sprite->setPosition3D(Vec3(x, y, z));
                sprite->addComponent(component);
                sprite->setCameraMask((unsigned short)CameraFlag::USER1);
                this->addChild(sprite);
            }
        }
    }

    physicsScene->setPhysics3DDebugCamera(_camera);

    return true;
}

std::string Physics3DConstraintDemo::subtitle() const
{
    return "Physics3D Constraint";
}

std::string Physics3DKinematicDemo::subtitle() const 
{
    return "Physics3D Kinematic";
}

bool Physics3DKinematicDemo::init()
{
    if (!Physics3DTestDemo::init())
        return false;

    //create floor
    Physics3DRigidBodyDes rbDes;
    rbDes.mass = 0.0f;
    rbDes.shape = Physics3DShape::createBox(Vec3(60.0f, 2.0f, 60.0f));
    rbDes.originalTransform.translate(0.f, -1.f, 0.f);
    auto rigidBody = Physics3DRigidBody::create(&rbDes);
    auto component = Physics3DComponent::create(rigidBody);
    auto node = Node::create();
    node->addComponent(component);
    this->addChild(node);

    //create Kinematics
    {
        rbDes.mass = 1.f;
        rbDes.shape = Physics3DShape::createBox(Vec3(2.0f, 2.0f, 2.0f));
        auto rigidBody = Physics3DRigidBody::create(&rbDes);
        rigidBody->setKinematic(true);
        auto component = Physics3DComponent::create(rigidBody);
        auto sprite = Sprite3D::create("Sprite3DTest/box.c3t");
        sprite->setTexture("Images/CyanSquare.png");
        sprite->setCameraMask((unsigned short)CameraFlag::USER1);
        sprite->addComponent(component);
        this->addChild(sprite);

        sprite->setScale(2.0f);
    }

    for (unsigned int i = 0; i < 3; ++i)
    {
        rbDes.mass = 1.f;
        rbDes.shape = Physics3DShape::createBox(Vec3(2.0f, 2.0f, 2.0f));
        auto rigidBody = Physics3DRigidBody::create(&rbDes);
        rigidBody->setKinematic(true);
        auto component = Physics3DComponent::create(rigidBody);
        auto sprite = Sprite3D::create("Sprite3DTest/box.c3t");
        sprite->setTexture("Images/CyanSquare.png");
        sprite->setCameraMask((unsigned short)CameraFlag::USER1);
        sprite->addComponent(component);
        this->addChild(sprite);

        sprite->setScale(2.0f);
        sprite->setPosition3D(Vec3(-15.0f, 0.0f, 15.0f - 15.0f * i));
        auto moveby = MoveBy::create(2.0f + i, Vec3(30.0f, 0.0f, 0.0f));
        sprite->runAction(RepeatForever::create(Sequence::create(moveby, moveby->reverse(), nullptr)));
    }

    //create Dynamic
    {
        //create several spheres
        rbDes.mass = 1.f;
        rbDes.shape = Physics3DShape::createSphere(0.5f);
        float start_x = START_POS_X - ARRAY_SIZE_X/2;
        float start_y = START_POS_Y + 5.0f;
        float start_z = START_POS_Z - ARRAY_SIZE_Z/2;

        for (int k=0;k<ARRAY_SIZE_Y;k++)
        {
            for (int i=0;i<ARRAY_SIZE_X;i++)
            {
                for(int j = 0;j<ARRAY_SIZE_Z;j++)
                {
                    float x = 1.0*i + start_x;
                    float y = 5.0+1.0*k + start_y;
                    float z = 1.0*j + start_z;
                    rbDes.originalTransform.setIdentity();
                    rbDes.originalTransform.translate(x, y, z);

                    rigidBody = Physics3DRigidBody::create(&rbDes);
                    component = Physics3DComponent::create(rigidBody);
                    auto sprite = Sprite3D::create("Sprite3DTest/sphere.c3b");
                    sprite->setTexture("Sprite3DTest/plane.png");
                    sprite->addComponent(component);
                    sprite->setCameraMask((unsigned short)CameraFlag::USER1);
                    sprite->setScale(1.0f / sprite->getContentSize().width);
                    this->addChild(sprite);
                }
            }
        }
    }


    physicsScene->setPhysics3DDebugCamera(_camera);
    return true;
}


bool Physics3DConstraintDemo::init()
{
    if (!Physics3DTestDemo::init())
        return false;
    
    Physics3DRigidBodyDes rbDes;
    //create box
    auto sprite = Sprite3D::create("Sprite3DTest/orc.c3b");
    rbDes.mass = 10.f;
    rbDes.shape = Physics3DShape::createBox(Vec3(5.0f, 5.0f, 5.0f));
    auto rigidBody = Physics3DRigidBody::create(&rbDes);
    Quaternion quat;
    Quaternion::createFromAxisAngle(Vec3(0.f, 1.f, 0.f), CC_DEGREES_TO_RADIANS(180), &quat);
    auto component = Physics3DComponent::create(rigidBody, Vec3(0.f, -3.f, 0.f), quat);
    
    sprite->addComponent(component);
    addChild(sprite);
    sprite->setCameraMask((unsigned short)CameraFlag::USER1);
    sprite->setScale(0.4f);
    sprite->setPosition3D(Vec3(0.f, 10.f, 0.f));
    //sync node position to physics
    component->syncToNode();
    //physics controlled, we will not set position for it, so we can skip sync node position to physics
    component->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::PHYSICS_TO_NODE);
    
    physicsScene->setPhysics3DDebugCamera(_camera);
    
    //create constraint
    auto constraint = Physics3DPointToPointConstraint::create(rigidBody, Vec3(2.5f, 2.5f, 2.5f));
    physicsScene->getPhysics3DWorld()->addPhysics3DConstraint(constraint);
    
    return true;
}

bool Physics3DTerrainDemo::init()
{
    if (!Physics3DTestDemo::init())
        return false;

    unsigned int sz = sizeof(unsigned char);
    _data = FileUtils::getInstance()->getDataFromFile("images/heightfield64x64.raw");

    //create terrain
    Physics3DRigidBodyDes rbDes;
    rbDes.mass = 0.0f;
    rbDes.shape = Physics3DShape::createHeightfield(64, 64, _data.getBytes(), 0.01f, -100.0f, 100.0f, false, false, true);
    rbDes.originalTransform.translate(0.f, 0.f, 0.f);
    auto rigidBody = Physics3DRigidBody::create(&rbDes);
    auto component = Physics3DComponent::create(rigidBody);
    auto node = Node::create();
    node->addComponent(component);
    this->addChild(node);


    //create several spheres
    rbDes.mass = 1.f;
    rbDes.shape = Physics3DShape::createSphere(0.5f);
    float start_x = START_POS_X - ARRAY_SIZE_X/2;
    float start_y = START_POS_Y + 5.0f;
    float start_z = START_POS_Z - ARRAY_SIZE_Z/2;

    for (int k=0;k<ARRAY_SIZE_Y;k++)
    {
        for (int i=0;i<ARRAY_SIZE_X;i++)
        {
            for(int j = 0;j<ARRAY_SIZE_Z;j++)
            {
                float x = 1.0*i + start_x;
                float y = 5.0+1.0*k + start_y;
                float z = 1.0*j + start_z;
                rbDes.originalTransform.setIdentity();
                rbDes.originalTransform.translate(x, y, z);

                rigidBody = Physics3DRigidBody::create(&rbDes);
                component = Physics3DComponent::create(rigidBody);
                auto sprite = Sprite3D::create("Sprite3DTest/sphere.c3b");
                sprite->setTexture("Sprite3DTest/plane.png");
                sprite->addComponent(component);
                sprite->setCameraMask((unsigned short)CameraFlag::USER1);
                sprite->setScale(1.0f / sprite->getContentSize().width);
                this->addChild(sprite);
            }
        }
    }

    physicsScene->setPhysics3DDebugCamera(_camera);
    return true;
}

std::string Physics3DTerrainDemo::subtitle() const 
{
    return "Physics3D Terrain";
}

#endif
