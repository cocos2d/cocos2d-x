#include "TerrainTest.h"



Vec3 camera_offset(0,45,60);
#define PLAYER_HEIGHT 0
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
    _camera = Camera::createPerspective(60,visibleSize.width/visibleSize.height,0.1,800);
    _camera->setCameraFlag(CameraFlag::USER1);
    addChild(_camera);

    Terrain::DetailMap r("TerrainTest/dirt.dds"),g("TerrainTest/Grass2.dds"),b("TerrainTest/road.dds"),a("TerrainTest/Grass1.dds");

    Terrain::TerrainData data("TerrainTest/heightmap16.jpg","TerrainTest/alphamap.png",r,g,b,a);
    _terrain = Terrain::create(data);
    _terrain->setMaxDetailMapAmount(4);
    addChild(_terrain);
    _terrain->setCameraMask(2);
    _terrain->setDrawWire(true);
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(TerrainSimple::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

std::string TerrainSimple::title() const 
{
    return "Simple Terrain";
}

std::string TerrainSimple::subtitle() const 
{
    return "Drag to walkThru";
}

void TerrainSimple::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
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

    Terrain::DetailMap r("TerrainTest/dirt.dds"),g("TerrainTest/Grass2.dds",10),b("TerrainTest/road.dds"),a("TerrainTest/Grass1.dds",20);

    Terrain::TerrainData data("TerrainTest/heightmap16.jpg","TerrainTest/alphamap.png",r,g,b,a);
    _terrain = Terrain::create(data);
    _terrain->setScale(20);
    _terrain->setMaxDetailMapAmount(4);
    _terrain->setCameraMask(2);
    _terrain->setDrawWire(false);

    _terrain->setLODDistance(150,220,300);
    _player = Player::create("Sprite3DTest/girl.c3b",_camera,_terrain);
    _player->setCameraMask(2);
    _player->setScale(0.08);
    _player->setPositionY(_terrain->getHeight(_player->getPositionX(),_player->getPositionZ())+PLAYER_HEIGHT);

    auto animation = Animation3D::create("Sprite3DTest/girl.c3b","Take 001");
    if (animation)
    {
        auto animate = Animate3D::create(animation);
        _player->runAction(RepeatForever::create(animate));
    }

    _camera->setPosition3D(_player->getPosition3D()+camera_offset);
    _camera->setRotation3D(Vec3(-45,0,0));

    forward = Label::createWithSystemFont("forward","arial",22);
    forward->setPosition(0,200);
    forward->setAnchorPoint(Vec2(0,0));

    backward = Label::createWithSystemFont("backward","arial",22);
    backward->setPosition(0,250);
    backward->setAnchorPoint(Vec2(0,0));

    left = Label::createWithSystemFont("turn Left","arial",22);
    left->setPosition(0,100);
    left->setAnchorPoint(Vec2(0,0));

    right = Label::createWithSystemFont("turn right","arial",22);
    right->setPosition(0,150);
    right->setAnchorPoint(Vec2(0,0));
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
            float height = _terrain->getHeight(rayPos.x,rayPos.z); 

            while (rayPos.y > height)
            {
                lastRayPosition = rayPos; 
                rayPos += rayStep; 
                height = _terrain->getHeight(rayPos.x,rayPos.z); 
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
            dir = collisionPoint - _player->getPosition3D();
            dir.y = 0;
            dir.normalize();
            _player->_headingAngle =  -1*acos(dir.dot(Vec3(0,0,-1)));
            dir.cross(dir,Vec3(0,0,-1),&_player->_headingAxis);
            _player->_targetPos=collisionPoint;
            _player->forward();
        }
    }
}


bool Player::isDone() const
{
    return false;
}


void Player::update(float dt)
{
    auto player = (Sprite3D *)this;
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
        }
        break;
    case PLAYER_STATE_BACKWARD:
        {
            Vec3 forward_vec;
            player->getNodeToWorldTransform().getForwardVector(&forward_vec);
            forward_vec.normalize();
            player->setPosition3D(player->getPosition3D()-forward_vec*15*dt);
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
    Vec3 Normal;
    float player_h = _terrain->getHeight(player->getPositionX(),player->getPositionZ(),&Normal);

    player->setPositionY(player_h+PLAYER_HEIGHT);
    Quaternion q2;
    q2.createFromAxisAngle(Vec3(0,1,0),-M_PI,&q2);
 
    Quaternion headingQ;
    headingQ.createFromAxisAngle(_headingAxis,_headingAngle,&headingQ);
    player->setRotationQuat(headingQ*q2);
    auto vec_offset =Vec4(camera_offset.x,camera_offset.y,camera_offset.z,1);
    vec_offset = player->getNodeToWorldTransform()*vec_offset;
    // _cam->setRotation3D(player->getRotation3D());
     _cam->setPosition3D(player->getPosition3D() + camera_offset);
    updateState();
}

void Player::turnLeft()
{
    _playerState = PLAYER_STATE_LEFT;
}

void Player::turnRight()
{
    _playerState = PLAYER_STATE_RIGHT;
}

void Player::idle()
{
    _playerState = PLAYER_STATE_IDLE;
}


void Player::forward()
{
    _playerState = PLAYER_STATE_FORWARD;
}

void Player::backward()
{
    _playerState = PLAYER_STATE_BACKWARD;
}

void Player::updateState()
{
    auto player = (Sprite3D * )this;
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

Player * Player::create(const char * file,Camera * cam,Terrain * terrain)
{
    //
    auto sprite = new (std::nothrow) Player();
    if (sprite && sprite->initWithFile(file))
    {
        sprite->_headingAngle = 0;
        sprite->_playerState = PLAYER_STATE_IDLE;
        sprite->_cam = cam;
        sprite->_terrain = terrain;
        sprite->autorelease();
        sprite->scheduleUpdate();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}
