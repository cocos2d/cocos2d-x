/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "TerrainTest.h"

USING_NS_CC;

TerrainTests::TerrainTests()
{
    ADD_TEST_CASE(TerrainSimple);
    ADD_TEST_CASE(TerrainWalkThru);
    ADD_TEST_CASE(TerrainWithLightMap);
}

Vec3 camera_offset(0, 45, 60);
#define PLAYER_HEIGHT 0

TerrainSimple::TerrainSimple()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    //use custom camera
    _camera = Camera::createPerspective(60,visibleSize.width/visibleSize.height,0.1f,800);
    _camera->setCameraFlag(CameraFlag::USER1);
    _camera->setPosition3D(Vec3(-1,1.6f,4));
    addChild(_camera);

    Terrain::DetailMap r("TerrainTest/dirt.jpg"),g("TerrainTest/Grass2.jpg"),b("TerrainTest/road.jpg"),a("TerrainTest/GreenSkin.jpg");

    Terrain::TerrainData data("TerrainTest/heightmap16.jpg","TerrainTest/alphamap.png",r,g,b,a);

    _terrain = Terrain::create(data,Terrain::CrackFixedType::SKIRT);
    _terrain->setLODDistance(3.2f,6.4f,9.6f);
    _terrain->setMaxDetailMapAmount(4);
    addChild(_terrain);
    _terrain->setCameraMask(2);
    _terrain->setDrawWire(false);
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(TerrainSimple::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
//     add Particle3D for test blend
    auto rootps = PUParticleSystem3D::create("Particle3D/scripts/mp_torch.pu");
    rootps->setCameraMask((unsigned short)CameraFlag::USER1);
    rootps->startParticleSystem();
    
    this->addChild(rootps, 0, 0);
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
    _camera = Camera::createPerspective(60,visibleSize.width/visibleSize.height,0.1f,200);
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
    _player->setScale(0.08f);
    _player->setPositionY(_terrain->getHeight(_player->getPositionX(),_player->getPositionZ())+PLAYER_HEIGHT);

    // add Particle3D for test blend
    auto rootps = PUParticleSystem3D::create("Particle3D/scripts/mp_torch.pu");
    rootps->setCameraMask((unsigned short)CameraFlag::USER1);
    rootps->setScale(30.0f);
    rootps->startParticleSystem();
    _player->addChild(rootps);
    
    // add BillBoard for test blend
    auto billboard = BillBoard::create("Images/btn-play-normal.png");
    billboard->setPosition3D(Vec3(0,180,0));
    billboard->setCameraMask((unsigned short)CameraFlag::USER1);
    _player->addChild(billboard);

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
            Vec3 collisionPoint(-999,-999,-999);
            bool isInTerrain = _terrain->getIntersectionPoint(Ray(nearP, dir), collisionPoint);
            if (!isInTerrain) 
            {
            _player->idle();
            return;
            }
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
    // transform player position to world coord
    auto playerPos = player->getPosition3D();
    auto playerModelMat = player->getParent()->getNodeToWorldTransform();
    playerModelMat.transformPoint(&playerPos);
    Vec3 Normal;
    float player_h = _terrain->getHeight(playerPos.x, playerPos.z,&Normal);
    if (Normal.isZero())//check the player whether is out of the terrain
    {
        player_h = playerPos.y;
    }
    else
    {
        player_h += PLAYER_HEIGHT;
    }
    player->setPositionY(player_h);
    Quaternion q2;
    q2.createFromAxisAngle(Vec3(0,1,0),(float)-M_PI,&q2);
 
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

TerrainWithLightMap::TerrainWithLightMap()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //use custom camera
    _camera = Camera::createPerspective(60,visibleSize.width/visibleSize.height,0.1f,800);
    _camera->setCameraFlag(CameraFlag::USER1);
    _camera->setPosition3D(Vec3(-1,1.6f,4));
    addChild(_camera);
    
    Terrain::DetailMap r("TerrainTest/dirt.jpg"),g("TerrainTest/Grass2.jpg"),b("TerrainTest/road.jpg"),a("TerrainTest/GreenSkin.jpg");
    
    Terrain::TerrainData data("TerrainTest/heightmap16.jpg","TerrainTest/alphamap.png",r,g,b,a);
    
    _terrain = Terrain::create(data,Terrain::CrackFixedType::SKIRT);
    _terrain->setLODDistance(3.2f,6.4f,9.6f);
    _terrain->setMaxDetailMapAmount(4);
    addChild(_terrain);
    _terrain->setCameraMask(2);
    _terrain->setDrawWire(false);
    _terrain->setLightMap("TerrainTest/Lightmap.png");
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(TerrainWithLightMap::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
}
std::string TerrainWithLightMap::title() const
{
    return "Terrain using light map";
}
std::string TerrainWithLightMap::subtitle() const
{
    return "Drag to walkThru";
}
void TerrainWithLightMap::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
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
