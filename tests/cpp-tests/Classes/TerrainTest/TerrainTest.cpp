#include "TerrainTest.h"



Vec3 camera_offset(0,30,90);

static std::function<Layer*()> createFunctions[] =
{
    CL(TerrainSimple),
    CL(TerrainWalkThru),
};

static int sceneIdx = -1;
#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))

static Layer* nextTerrainTestAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

static Layer* backTerrainTestAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;

    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

static Layer* restartTerrainTestAction()
{
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

TerrainSimple::TerrainSimple()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    //use custom camera
    auto camera = Camera::createPerspective(60,visibleSize.width/visibleSize.height,0.1,200);
    camera->setCameraFlag(CameraFlag::USER1);
    addChild(camera);

    Terrain::TerrainData a("TerrainTest/heightmap16.jpg","TerrainTest/sand.jpg");
    auto terrain = Terrain::create(a);
    addChild(terrain);
    terrain->setCameraMask(2);
}

std::string TerrainSimple::title() const 
{
    return "Simple Terrain";
}

std::string TerrainSimple::subtitle() const 
{
    return "Drag to walkThru";
}



void TerrainTestScene::runThisTest()
{
    auto layer = nextTerrainTestAction();
    addChild(layer);
    Director::getInstance()->replaceScene(this);
}


void TerrainTestDemo::restartCallback(Ref* sender)
{
    auto s = new (std::nothrow) TerrainTestScene();
    s->addChild(restartTerrainTestAction());

    Director::getInstance()->replaceScene(s);
    s->release();
}

void TerrainTestDemo::nextCallback(Ref* sender)
{
    auto s = new (std::nothrow) TerrainTestScene();
    s->addChild( nextTerrainTestAction());
    Director::getInstance()->replaceScene(s);
    s->release();
}

void TerrainTestDemo::backCallback(Ref* sender)
{
    auto s = new (std::nothrow) TerrainTestScene();
    s->addChild( backTerrainTestAction());
    Director::getInstance()->replaceScene(s);
    s->release();
}

std::string TerrainTestDemo::title() const 
{
    return "No title";
}

std::string TerrainTestDemo::subtitle() const 
{
    return "";
}

void TerrainTestDemo::onEnter()
{
    BaseTest::onEnter();
}

TerrainTestDemo::TerrainTestDemo(void)
    :BaseTest()
{

}

TerrainTestDemo::~TerrainTestDemo(void)
{

}

std::string TerrainWalkThru::title() const 
{
    return " ";
}

std::string TerrainWalkThru::subtitle() const 
{
    return " ";
}

TerrainWalkThru::TerrainWalkThru()
{
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(TerrainWalkThru::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(TerrainWalkThru::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(TerrainWalkThru::onTouchesEnd, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    Size visibleSize = Director::getInstance()->getVisibleSize();

    //use custom camera
    _camera = Camera::createPerspective(60,visibleSize.width/visibleSize.height,0.1,200);
    _camera->setCameraFlag(CameraFlag::USER1);
    addChild(_camera);

    Terrain::TerrainData a("TerrainTest/heightmap16.jpg","TerrainTest/sand.jpg");
    _terrain = Terrain::create(a);
    _terrain->setScale(20);

    _terrain->setCameraMask(2);
    _terrain->setDrawWire(false);

    _action = new PlayerAction(_camera,_terrain);
    _action->retain();
    _player =Sprite3D::create("Sprite3DTest/orc.c3b");
    _player->runAction(_action);
    _player->setCameraMask(2);
    //_player->setScale(0.1);
    _player->setPositionY(_terrain->getHeight(_player->getPosition3D()));

    _camera->setPosition3D(_player->getPosition3D()+camera_offset);
    _camera->setRotation3D(Vec3(-15,0,0));

    forward = Label::create("forward","arial",22);
    forward->setPosition(0,200);
    forward->setAnchorPoint(Vec2(0,0));

    backward = Label::create("backward","arial",22);
    backward->setPosition(0,250);
    backward->setAnchorPoint(Vec2(0,0));

    left = Label::create("turn Left","arial",22);
    left->setPosition(0,100);
    left->setAnchorPoint(Vec2(0,0));


    right = Label::create("turn right","arial",22);
    right->setPosition(0,150);
    right->setAnchorPoint(Vec2(0,0));
    addChild(forward);
    addChild(backward);
    addChild(left);
    addChild(right);
    addChild(_player);
    addChild(_terrain);
}

void TerrainWalkThru::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
    float delta = Director::getInstance()->getDeltaTime();
    auto touch = touches[0];
    auto location = touch->getLocation();
    auto PreviousLocation = touch->getPreviousLocation();
    Point newPos = PreviousLocation - location;

    Vec3 cameraDir;
    Vec3 cameraRightDir;
    _camera->getNodeToWorldTransform().getForwardVector(&cameraDir);
    cameraDir.normalize();
    cameraDir.y=0;
    _camera->getNodeToWorldTransform().getRightVector(&cameraRightDir);
    cameraRightDir.normalize();
    cameraRightDir.y=0;
    Vec3 cameraPos=  _camera->getPosition3D();
    cameraPos+=cameraDir*newPos.y*0.5*delta;  
    cameraPos+=cameraRightDir*newPos.x*0.5*delta;
    _camera->setPosition3D(cameraPos);   
}

void TerrainWalkThru::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
    auto touch = touches[0];
    Size s = left->getContentSize();
    Rect rect = Rect(left->getPositionX(), left->getPositionY(), s.width, s.height);
    auto location = touch->getLocation();
    if(rect.containsPoint(location))
    {
        //turn left
        _action->turnLeft();
    }

    s = right->getContentSize();
    rect = Rect(right->getPositionX(), right->getPositionY(), s.width, s.height);
    if(rect.containsPoint(location))
    {
        //turn right
        _action->turnRight();
    }

    s = forward->getContentSize();
    rect = Rect(forward->getPositionX(), forward->getPositionY(), s.width, s.height);
    if(rect.containsPoint(location))
    {
        //forward
        _action->forward();
    }

    s = backward->getContentSize();
    rect = Rect(backward->getPositionX(), backward->getPositionY(), s.width, s.height);
    if(rect.containsPoint(location))
    {
        //backward
        _action->backward();
    }

}

void TerrainWalkThru::onTouchesEnd(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{

    auto touch = touches[0];
    auto location = touch->getLocationInView();
    if(_camera)
    {
        if(_player)
        {
            Vec3 nearP(location.x, location.y, 0.0f), farP(location.x, location.y, 1.0f);

            auto size = Director::getInstance()->getWinSize();
            _camera->unproject(size, &nearP, &nearP);
            _camera->unproject(size, &farP, &farP);
            Vec3 dir = farP - nearP;
            dir.normalize();
            Vec3 rayStep = 15*dir;
            Vec3 rayPos =  nearP;
            Vec3 rayStartPosition = nearP;
            Vec3 lastRayPosition =rayPos;
            rayPos += rayStep; 
            // Linear search - Loop until find a point inside and outside the terrain Vector3 
            float height = _terrain->getHeight(rayPos); 

            while (rayPos.y > height)
            {
                lastRayPosition = rayPos; 
                rayPos += rayStep; 
                height = _terrain->getHeight(rayPos); 
            } 

            Vec3 startPosition = lastRayPosition;
            Vec3 endPosition = rayPos;

            for (int i= 0; i< 32; i++) 
            { 
                // Binary search pass 
                Vec3 middlePoint = (startPosition + endPosition) * 0.5f;
                if (middlePoint.y < height) 
                    endPosition = middlePoint; 
                else 
                    startPosition = middlePoint;
            } 
            Vec3 collisionPoint = (startPosition + endPosition) * 0.5f; 

            _action->_targetPos=collisionPoint;
            _action->forward();
        }
    }
}


bool PlayerAction::isDone() const
{
    return false;
}


void PlayerAction::step(float dt)
{
    auto player = (Sprite3D * )_target;
    switch (_playerState)
    {
    case PLAYER_STATE_IDLE:
        break;
    case PLAYER_STATE_FORWARD:
        {
            Vec3 curPos=  player->getPosition3D();
            Vec3 newFaceDir = _targetPos - curPos;
            newFaceDir.y = 0.0f;
            newFaceDir.normalize();
            Vec3 offset = newFaceDir * 25.0f * dt;
            curPos+=offset;
            player->setPosition3D(curPos);
            player->setPositionY(_terrain->getHeight(player->getPosition3D()));
        }
        break;
    case PLAYER_STATE_BACKWARD:
        {
            Vec3 forward_vec;
            player->getNodeToWorldTransform().getForwardVector(&forward_vec);
            forward_vec.normalize();
            player->setPosition3D(player->getPosition3D()-forward_vec*15*dt);
            player->setPositionY(_terrain->getHeight(player->getPosition3D()));
        }
        break;
    case PLAYER_STATE_LEFT:
        {
            player->setRotation3D(player->getRotation3D()+Vec3(0,25*dt,0));
        }
        break;
    case PLAYER_STATE_RIGHT:
        {
            player->setRotation3D(player->getRotation3D()+Vec3(0,-25*dt,0));
        }
        break;
    default:
        break;
    }
    auto vec_offset =Vec4(camera_offset.x,camera_offset.y,camera_offset.z,1);
    vec_offset = player->getNodeToWorldTransform()*vec_offset;
    _cam->setRotation3D(player->getRotation3D());
    _cam->setPosition3D(Vec3(vec_offset.x,vec_offset.y,vec_offset.z));
    updateState();
}

void PlayerAction::turnLeft()
{
    _playerState = PLAYER_STATE_LEFT;
}

void PlayerAction::turnRight()
{
    _playerState = PLAYER_STATE_RIGHT;
}

void PlayerAction::idle()
{
    _playerState = PLAYER_STATE_IDLE;
}

PlayerAction::PlayerAction(Camera * cam,Terrain * terrain)
{
    _playerState = PLAYER_STATE_IDLE;
    _cam = cam;
    _terrain = terrain;
}

void PlayerAction::forward()
{
    _playerState = PLAYER_STATE_FORWARD;
}

void PlayerAction::backward()
{
    _playerState = PLAYER_STATE_BACKWARD;
}

void PlayerAction::updateState()
{
    auto player = (Sprite3D * )_target;
    switch (_playerState)
    {
    case PLAYER_STATE_FORWARD:
        {
            Vec2 player_pos =Vec2(player->getPositionX(),player->getPositionZ());
            Vec2 targetPos = Vec2(_targetPos.x,_targetPos.z);
            auto dist = player_pos.distance(targetPos);
            if(dist<1)
            {
                _playerState = PLAYER_STATE_IDLE;
            }
        }
        break;
    default:
        break;
    }
}
