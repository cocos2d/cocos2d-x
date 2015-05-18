#include "TerrainTest.h"

USING_NS_CC;

TerrainTests::TerrainTests()
{
    ADD_TEST_CASE(TerrainSimple);
    ADD_TEST_CASE(TerrainWalkThru);
}

Vec3 camera_offset(0, 45, 60);
#define PLAYER_HEIGHT 0

TerrainSimple::TerrainSimple()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    //use custom camera
    _camera = Camera::createPerspective(60,visibleSize.width/visibleSize.height,0.1,800);
    _camera->setCameraFlag(CameraFlag::USER1);
    _camera->setPosition3D(Vec3(-1,1.6,4));
    addChild(_camera);

    Terrain::DetailMap r("TerrainTest/dirt.jpg"),g("TerrainTest/Grass2.jpg"),b("TerrainTest/road.jpg"),a("TerrainTest/GreenSkin.jpg");

    Terrain::TerrainData data("TerrainTest/heightmap16.jpg","TerrainTest/alphamap.png",r,g,b,a);

    _terrain = Terrain::create(data,Terrain::CrackFixedType::SKIRT);
    _terrain->setLODDistance(3.2,6.4,9.6);
    _terrain->setMaxDetailMapAmount(4);
    addChild(_terrain);
    _terrain->setCameraMask(2);
    _terrain->setDrawWire(false);
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(TerrainSimple::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

std::string TerrainSimple::title() const 
{
    return "Terrain with skirt";
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


std::string TerrainWalkThru::title() const 
{
    return "Player walk around in terrain";
}

std::string TerrainWalkThru::subtitle() const 
{
    return "touch to move";
}

TerrainWalkThru::TerrainWalkThru()
{
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(TerrainWalkThru::onTouchesBegan, this);
    listener->onTouchesEnded = CC_CALLBACK_2(TerrainWalkThru::onTouchesEnd, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    Size visibleSize = Director::getInstance()->getVisibleSize();

    //use custom camera
    _camera = Camera::createPerspective(60,visibleSize.width/visibleSize.height,0.1,200);
    _camera->setCameraFlag(CameraFlag::USER1);
    addChild(_camera);

    Terrain::DetailMap r("TerrainTest/dirt.jpg"),g("TerrainTest/Grass2.jpg",10),b("TerrainTest/road.jpg"),a("TerrainTest/GreenSkin.jpg",20);

    Terrain::TerrainData data("TerrainTest/heightmap16.jpg","TerrainTest/alphamap.png",r,g,b,a,Size(32,32),40.0f,2);
    _terrain = Terrain::create(data,Terrain::CrackFixedType::SKIRT);
    _terrain->setMaxDetailMapAmount(4);
    _terrain->setCameraMask(2);
    _terrain->setDrawWire(false);

    _terrain->setSkirtHeightRatio(3);
    _terrain->setLODDistance(64,128,192);
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

    addChild(_player);
    addChild(_terrain);
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
