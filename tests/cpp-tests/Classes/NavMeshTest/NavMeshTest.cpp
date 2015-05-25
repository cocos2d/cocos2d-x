/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2015 Chukong Technologies Inc.
 
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

#include "NavMeshTest.h"
#include "physics3d/CCPhysics3DWorld.h"
#include "physics3d/CCPhysics3D.h"
#include "3d/CCBundle3D.h"
#include "2d/CCLight.h"

USING_NS_CC_EXT;
USING_NS_CC;

struct AgentUserData
{
    float time;
};

NavMeshTests::NavMeshTests()
{
#if CC_USE_NAVMESH == 0
    ADD_TEST_CASE(NavMeshDisabled);
#else
    ADD_TEST_CASE(NavMeshTestDemo);
#endif
};

#if CC_USE_NAVMESH == 0
void NavMeshDisabled::onEnter()
{
    TTFConfig ttfConfig("fonts/arial.ttf", 16);
    auto label = Label::createWithTTF(ttfConfig, "Should define CC_USE_NAVMESH\n to run this test case");
    
    auto size = Director::getInstance()->getWinSize();
    label->setPosition(Vec2(size.width / 2, size.height / 2));

    addChild(label);

    TestCase::onEnter();
}
#else
std::string NavMeshTestDemo::title() const
{
    return "Navigation Mesh Test";
}

std::string NavMeshTestDemo::subtitle() const
{
    return "";
}

bool NavMeshTestDemo::init()
{
    if (!TestCase::init()) return false;

    if (initWithPhysics()){

        _angle = 0.0f;

        Size size = Director::getInstance()->getWinSize();
        _camera = Camera::createPerspective(30.0f, size.width / size.height, 1.0f, 1000.0f);
        _camera->setPosition3D(Vec3(0.0f, 50.0f, 100.0f));
        _camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
        _camera->setCameraFlag(CameraFlag::USER1);
        this->addChild(_camera);

        auto listener = EventListenerTouchAllAtOnce::create();
        listener->onTouchesBegan = CC_CALLBACK_2(NavMeshTestDemo::onTouchesBegan, this);
        listener->onTouchesMoved = CC_CALLBACK_2(NavMeshTestDemo::onTouchesMoved, this);
        listener->onTouchesEnded = CC_CALLBACK_2(NavMeshTestDemo::onTouchesEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

        TTFConfig ttfConfig("fonts/arial.ttf", 15);
        _stateLabel = Label::createWithTTF(ttfConfig, "Create Obstacle");
        _stateLabel->retain();
        _debugLabel = Label::createWithTTF(ttfConfig, "Debug Draw ON");
        _debugLabel->retain();
        auto menuItem0 = MenuItemLabel::create(_stateLabel, CC_CALLBACK_0(NavMeshTestDemo::switchState, this));
        menuItem0->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
        menuItem0->setPosition(Vec2(VisibleRect::left().x, VisibleRect::top().y - 50));
        auto menuItem1 = MenuItemLabel::create(_debugLabel, [=](Ref*){
            bool enabledDebug = !getNavMesh()->isDebugDrawEnabled();
            getNavMesh()->setDebugDrawEnable(enabledDebug);
            if (enabledDebug){
                _debugLabel->setString("Debug Draw ON");
            }
            else{
                _debugLabel->setString("Debug Draw OFF");
            }
        });
        menuItem1->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
        menuItem1->setPosition(Vec2(VisibleRect::left().x, VisibleRect::top().y - 100));
        auto menu = Menu::create(menuItem0, menuItem1, nullptr);
        menu->setPosition(Vec2::ZERO);
        addChild(menu);

        initScene();

        scheduleUpdate();
    }
    
    
    return true;
}

void NavMeshTestDemo::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    if (!touches.empty()){
        auto touch = touches[0];
        auto location = touch->getLocationInView();
        Vec3 nearP(location.x, location.y, 0.0f), farP(location.x, location.y, 1.0f);

        auto size = Director::getInstance()->getWinSize();
        _camera->unproject(size, &nearP, &nearP);
        _camera->unproject(size, &farP, &farP);

        Physics3DWorld::HitResult result;
        bool ret = getPhysics3DWorld()->rayCast(nearP, farP, &result);
        if (ret)
        {
            if (_stateLabel->getString() == "Create Obstacle"){
                createObstacle(result.hitPosition);
            }
            
            if (_stateLabel->getString() == "Create Agent"){
                createAgent(result.hitPosition);
            }
            
            if (_stateLabel->getString() == "Move Agent"){
                moveAgents(result.hitPosition);
            }
        }
    }
}

void NavMeshTestDemo::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    if (touches.size() && _camera)
    {
        auto touch = touches[0];
        auto delta = touch->getDelta();

        _angle -= CC_DEGREES_TO_RADIANS(delta.x);
        _camera->setPosition3D(Vec3(100.0f * sinf(_angle), 50.0f, 100.0f * cosf(_angle)));
        _camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
    }
}

void NavMeshTestDemo::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
}

void NavMeshTestDemo::initScene()
{
    getPhysics3DWorld()->setDebugDrawEnable(false);
    //create mesh
    std::vector<Vec3> trianglesList = Bundle3D::getTrianglesList("NavMesh/scene.obj");

    Physics3DRigidBodyDes rbDes;
    rbDes.mass = 0.0f;
    rbDes.shape = Physics3DShape::createMesh(&trianglesList[0], (int)trianglesList.size() / 3);
    auto rigidBody = Physics3DRigidBody::create(&rbDes);
    auto component = Physics3DComponent::create(rigidBody);
    auto sprite = Sprite3D::create("NavMesh/scene.obj");
    sprite->addComponent(component);
    sprite->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(sprite);
    setPhysics3DDebugCamera(_camera);

    auto navMesh = NavMesh::create("NavMesh/all_tiles_tilecache.bin", "NavMesh/geomset.txt");
    navMesh->setDebugDrawEnable(true);
    setNavMesh(navMesh);
    setNavMeshDebugCamera(_camera);


    auto ambientLight = AmbientLight::create(Color3B(64, 64, 64));
    ambientLight->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(ambientLight);

    auto dirLight = DirectionLight::create(Vec3(0.0f, -1.0f, 0.0f), Color3B(150, 150, 150));
    dirLight->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(dirLight);
}

void NavMeshTestDemo::createAgent(const Vec3 &pos)
{
    std::string filePath = "Sprite3DTest/girl.c3b";
    NavMeshAgentParam param;
    param.radius = 2.0f;
    param.height = 8.0f;
    auto agent = NavMeshAgent::create(param);
    auto agentNode = Sprite3D::create(filePath);
    agent->setOrientationRefAxes(Vec3(-1.0f, 0.0f, 1.0f));
    AgentUserData *data = new AgentUserData{ 0.0f };
    agent->setUserData(data);
    agentNode->setScale(0.05f);
    agentNode->addComponent(agent);

    auto node = Node::create();
    node->addChild(agentNode);
    node->setPosition3D(pos);
    node->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(node);


    auto animation = Animation3D::create(filePath);
    auto animate = Animate3D::create(animation);
    if (animate){
        agentNode->runAction(RepeatForever::create(animate));
        animate->setSpeed(0);
    }

    _agents.push_back(std::make_pair(agent, animate));
}

void NavMeshTestDemo::createObstacle(const Vec3 &pos)
{
    auto obstacle = NavMeshObstacle::create(2.0f, 8.0f);
    auto obstacleNode = Sprite3D::create("Sprite3DTest/cylinder.c3b");
    obstacleNode->setPosition3D(pos + Vec3(0.0f, -0.5f, 0.0f));
    obstacleNode->setRotation3D(Vec3(-90.0f, 0.0f, 0.0f));
    obstacleNode->setScale(0.3f);
    obstacleNode->addComponent(obstacle);
    obstacleNode->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(obstacleNode);
}

Vec3 jump(const Vec3* pV1, const Vec3* pV2, float height, float t)
{
    Vec3 pOut;
    pOut.x = pV1->x + t * (pV2->x - pV1->x);
    pOut.y = pV1->y + t * (pV2->y - pV1->y);
    pOut.z = pV1->z + t * (pV2->z - pV1->z);
    pOut.y += height * sinf(M_PI * t);
    return pOut;
}

void NavMeshTestDemo::moveAgents(const cocos2d::Vec3 &des)
{
    for (auto iter : _agents){
        NavMeshAgent::MoveCallback callback = [](NavMeshAgent *agent, float totalTimeAfterMove){
            AgentUserData *data = static_cast<AgentUserData *>(agent->getUserData());
            if (agent->isOnOffMeshLink()){
                agent->setAutoTraverseOffMeshLink(false);
                agent->setAutoOrientation(false);
                OffMeshLinkData linkdata = agent->getCurrentOffMeshLinkData();

                agent->getOwner()->setPosition3D(jump(&linkdata.startPosition, &linkdata.endPosition, 10.0f, data->time));
                Vec3 dir = linkdata.endPosition - linkdata.startPosition;
                dir.y = 0.0f;
                dir.normalize();
                Vec3 axes;
                Vec3 refAxes = Vec3(-1.0f, 0.0f, 1.0f);
                refAxes.normalize();
                Vec3::cross(refAxes, dir, &axes);
                float angle = Vec3::dot(refAxes, dir);
                agent->getOwner()->setRotationQuat(Quaternion(axes, acosf(angle)));
                data->time += 0.01f;
                if (1.0f < data->time){
                    agent->completeOffMeshLink();
                    agent->setAutoOrientation(true);
                    data->time = 0.0f;
                }
            }
        };
        iter.first->move(des, callback);
    }
}

void NavMeshTestDemo::switchState()
{
    if (_stateLabel->getString() == "Create Agent"){
        _stateLabel->setString("Move Agent");
    }else
    if (_stateLabel->getString() == "Move Agent"){
        _stateLabel->setString("Create Obstacle");
    }else
    if (_stateLabel->getString() == "Create Obstacle"){
        _stateLabel->setString("Create Agent");
    }
}

NavMeshTestDemo::NavMeshTestDemo(void)
: _camera(nullptr)
{

}

void NavMeshTestDemo::update( float delta )
{
    for (auto iter : _agents){
        float speed = iter.first->getCurrentVelocity().length() * 0.2;
        iter.second->setSpeed(0.0f < speed ? speed : 0.0f);
    }
}

NavMeshTestDemo::~NavMeshTestDemo( void )
{
    for (auto iter : _agents){
        AgentUserData *data = static_cast<AgentUserData *>(iter.first->getUserData());
        delete data;
    }
}

#endif
