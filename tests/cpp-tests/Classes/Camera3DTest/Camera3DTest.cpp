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

#include "Camera3DTest.h"
#include "testResource.h"

USING_NS_CC;

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

Camera3DTests::Camera3DTests()
{
    ADD_TEST_CASE(CameraRotationTest);
    ADD_TEST_CASE(Camera3DTestDemo);
    ADD_TEST_CASE(CameraCullingDemo);
    ADD_TEST_CASE(FogTestDemo);
    ADD_TEST_CASE(CameraArcBallDemo);
    ADD_TEST_CASE(CameraFrameBufferTest);
}

//------------------------------------------------------------------
//
// Camera Rotation Test
//
//------------------------------------------------------------------
CameraRotationTest::CameraRotationTest()
{

    auto s = Director::getInstance()->getWinSize();
    
    _camControlNode = Node::create();
    _camControlNode->setNormalizedPosition(Vec2(.5,.5));
    addChild(_camControlNode);

    _camNode = Node::create();
    _camNode->setPositionZ(Camera::getDefaultCamera()->getPosition3D().z);
    _camControlNode->addChild(_camNode);

    auto sp3d = Sprite3D::create();
    sp3d->setPosition(s.width/2, s.height/2);
    addChild(sp3d);
    
    auto lship = Label::create();
    lship->setString("Ship");
    lship->setPosition(0, 20);
    sp3d->addChild(lship);
    
    //Billboards
    //Yellow is at the back
    bill1 = BillBoard::create("Images/Icon.png");
    bill1->setPosition3D(Vec3(50, 10, -10));
    bill1->setColor(Color3B::YELLOW);
    bill1->setScale(0.6f);
    sp3d->addChild(bill1);
    
    l1 = Label::create();
    l1->setPosition(Vec2(0,-10));
    l1->setString("Billboard1");
    l1->setColor(Color3B::WHITE);
    l1->setScale(3);
    bill1->addChild(l1);

    auto p1 = CCParticleSystemQuad::create("Particles/SmallSun.plist");
    p1->setPosition(30,80);
    bill1->addChild(p1);
    
    bill2 = BillBoard::create("Images/Icon.png");
    bill2->setPosition3D(Vec3(-50, -10, 10));
    bill2->setScale(0.6f);
    sp3d->addChild(bill2);
    
    l2 = Label::create();
    l2->setString("Billboard2");
    l2->setPosition(Vec2(0,-10));
    l2->setColor(Color3B::WHITE);
    l2->setScale(3);
    bill2->addChild(l2);
    
    auto p2 = CCParticleSystemQuad::create("Particles/SmallSun.plist");
    p2->setPosition(30,80);
    bill2->addChild(p2);

    //3D models
    auto model = Sprite3D::create("Sprite3DTest/boss1.obj");
    model->setScale(4);
    model->setTexture("Sprite3DTest/boss.png");
    model->setPosition3D(Vec3(s.width/2, s.height/2, 0));
    addChild(model);

    //Listener
    _lis = EventListenerTouchOneByOne::create();
    _lis->onTouchBegan = [this](Touch* t, Event* e) {
        return true;
    };

    _lis->onTouchMoved = [this](Touch* t, Event* e) {
        float dx = t->getDelta().x;
        Vec3 rot = _camControlNode->getRotation3D();
        rot.y += dx;
        _camControlNode->setRotation3D(rot);

        Vec3 worldPos;
        _camNode->getNodeToWorldTransform().getTranslation(&worldPos);

        Camera::getDefaultCamera()->setPosition3D(worldPos);
        Camera::getDefaultCamera()->lookAt(_camControlNode->getPosition3D());
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_lis, this);
    
    schedule(schedule_selector(CameraRotationTest::update));
}

CameraRotationTest::~CameraRotationTest()
{
    Director::getInstance()->getEventDispatcher()->removeEventListener(_lis);
}

std::string CameraRotationTest::title() const
{
    return "Camera Rotation Test";
}

std::string CameraRotationTest::subtitle() const
{
    return "Slide to rotate";
}

void CameraRotationTest::onEnter()
{
    CameraBaseTest::onEnter();
}

void CameraRotationTest::onExit()
{
    CameraBaseTest::onExit();
}

void CameraRotationTest::update(float dt)
{
}

//------------------------------------------------------------------
//
// Camera3DTestDemo
//
//------------------------------------------------------------------
Camera3DTestDemo::Camera3DTestDemo(void)
: _incRot(nullptr)
, _decRot(nullptr)
, _camera(nullptr)
, _bZoomOut(false)
, _bZoomIn(false)
, _bRotateLeft(false)
, _bRotateRight(false)
{
}
Camera3DTestDemo::~Camera3DTestDemo(void)
{
}
void Camera3DTestDemo::reachEndCallBack()
{
}
std::string Camera3DTestDemo::title() const
{
    return "Testing Camera";
}

void Camera3DTestDemo::scaleCameraCallback(Ref* sender,float value)
{
    if(_camera&& _cameraType!=CameraType::FirstPerson)
    {
        Vec3 cameraPos=  _camera->getPosition3D();
        cameraPos+= cameraPos.getNormalized()*value;
        _camera->setPosition3D(cameraPos);
    }
}
void Camera3DTestDemo::rotateCameraCallback(Ref* sender,float value)
{
    if(_cameraType==CameraType::Free || _cameraType==CameraType::FirstPerson)
    {
        Vec3  rotation3D= _camera->getRotation3D();
        rotation3D.y+= value;
        _camera->setRotation3D(rotation3D);
    }
}
void Camera3DTestDemo::SwitchViewCallback(Ref* sender, CameraType cameraType)
{
    if(_cameraType==cameraType)
    {
        return ;
    }
    _cameraType = cameraType;
    if(_cameraType==CameraType::Free)
    {
        _camera->setPosition3D(Vec3(0, 130, 130) + _sprite3D->getPosition3D());
        _camera->lookAt(_sprite3D->getPosition3D());
        
        _RotateRightlabel->setColor(Color3B::WHITE);
        _RotateLeftlabel->setColor(Color3B::WHITE);
        _ZoomInlabel->setColor(Color3B::WHITE);
        _ZoomOutlabel->setColor(Color3B::WHITE);
    }
    else if(_cameraType==CameraType::FirstPerson)
    {
        Vec3 newFaceDir;
        _sprite3D->getWorldToNodeTransform().getForwardVector(&newFaceDir);
        newFaceDir.normalize();
        _camera->setPosition3D(Vec3(0,35,0) + _sprite3D->getPosition3D());
        _camera->lookAt(_sprite3D->getPosition3D() + newFaceDir*50);
        
        _RotateRightlabel->setColor(Color3B::WHITE);
        _RotateLeftlabel->setColor(Color3B::WHITE);
        _ZoomInlabel->setColor(Color3B::GRAY);
        _ZoomOutlabel->setColor(Color3B::GRAY);
    }
    else if(_cameraType==CameraType::ThirdPerson)
    {
        _camera->setPosition3D(Vec3(0, 130, 130) + _sprite3D->getPosition3D());
        _camera->lookAt(_sprite3D->getPosition3D());
        
        _RotateRightlabel->setColor(Color3B::GRAY);
        _RotateLeftlabel->setColor(Color3B::GRAY);
        _ZoomInlabel->setColor(Color3B::WHITE);
        _ZoomOutlabel->setColor(Color3B::WHITE);
    }
}
void Camera3DTestDemo::onEnter()
{
    CameraBaseTest::onEnter();
    _sprite3D=nullptr;
    auto s = Director::getInstance()->getWinSize();
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(Camera3DTestDemo::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Camera3DTestDemo::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Camera3DTestDemo::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    auto layer3D=Layer::create();
    addChild(layer3D,0);
    _layer3D=layer3D;
    _curState=State_None;
    addNewSpriteWithCoords( Vec3(0,0,0),"Sprite3DTest/girl.c3b",true,0.2f,true);
    TTFConfig ttfConfig("fonts/arial.ttf", 20);
    
    auto containerForLabel1 = Node::create();
    _ZoomOutlabel = Label::createWithTTF(ttfConfig,"zoom out");
    _ZoomOutlabel->setPosition(s.width-50, VisibleRect::top().y-30);
    containerForLabel1->addChild(_ZoomOutlabel);
    addChild(containerForLabel1, 10);
    
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    
    listener1->onTouchBegan = CC_CALLBACK_2(Camera3DTestDemo::onTouchesZoomOut, this);
    listener1->onTouchEnded = CC_CALLBACK_2(Camera3DTestDemo::onTouchesZoomOutEnd, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, _ZoomOutlabel);
    
    auto containerForLabel2 = Node::create();
    _ZoomInlabel = Label::createWithTTF(ttfConfig,"zoom in");
    _ZoomInlabel->setPosition(s.width-50, VisibleRect::top().y-100);
    containerForLabel2->addChild(_ZoomInlabel);
    addChild(containerForLabel2, 10);
    
    auto listener2 = EventListenerTouchOneByOne::create();
    listener2->setSwallowTouches(true);
    
    listener2->onTouchBegan = CC_CALLBACK_2(Camera3DTestDemo::onTouchesZoomIn, this);
    listener2->onTouchEnded = CC_CALLBACK_2(Camera3DTestDemo::onTouchesZoomInEnd, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, _ZoomInlabel);
    
    auto containerForLabel3 = Node::create();
    _RotateLeftlabel = Label::createWithTTF(ttfConfig,"rotate left");
    _RotateLeftlabel->setPosition(s.width-50, VisibleRect::top().y-170);
    containerForLabel3->addChild(_RotateLeftlabel);
    addChild(containerForLabel3, 10);
    
    auto listener3 = EventListenerTouchOneByOne::create();
    listener3->setSwallowTouches(true);
    
    listener3->onTouchBegan = CC_CALLBACK_2(Camera3DTestDemo::onTouchesRotateLeft, this);
    listener3->onTouchEnded = CC_CALLBACK_2(Camera3DTestDemo::onTouchesRotateLeftEnd, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener3, _RotateLeftlabel);
    
    auto containerForLabel4 = Node::create();
    _RotateRightlabel = Label::createWithTTF(ttfConfig,"rotate right");
    _RotateRightlabel->setPosition(s.width-50, VisibleRect::top().y-240);
    containerForLabel4->addChild(_RotateRightlabel);
    addChild(containerForLabel4, 10);
    
    auto listener4 = EventListenerTouchOneByOne::create();
    listener4->setSwallowTouches(true);
    
    listener4->onTouchBegan = CC_CALLBACK_2(Camera3DTestDemo::onTouchesRotateRight, this);
    listener4->onTouchEnded = CC_CALLBACK_2(Camera3DTestDemo::onTouchesRotateRightEnd, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener4, _RotateRightlabel);
    
    auto label1 = Label::createWithTTF(ttfConfig,"free ");
    auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(Camera3DTestDemo::SwitchViewCallback,this,CameraType::Free));
    auto label2 = Label::createWithTTF(ttfConfig,"third person");
    auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(Camera3DTestDemo::SwitchViewCallback,this,CameraType::ThirdPerson));
    auto label3 = Label::createWithTTF(ttfConfig,"first person");
    auto menuItem3 = MenuItemLabel::create(label3, CC_CALLBACK_1(Camera3DTestDemo::SwitchViewCallback,this,CameraType::FirstPerson));
    auto menu = Menu::create(menuItem1, menuItem2, menuItem3, nullptr);
    
    menu->setPosition(Vec2::ZERO);
    
    menuItem1->setPosition(VisibleRect::left().x+100, VisibleRect::top().y-50);
    menuItem2->setPosition(VisibleRect::left().x+100, VisibleRect::top().y -100);
    menuItem3->setPosition(VisibleRect::left().x+100, VisibleRect::top().y -150);
    addChild(menu, 0);
    schedule(CC_SCHEDULE_SELECTOR(Camera3DTestDemo::updateCamera), 0.0f);
    if (_camera == nullptr)
    {
        _camera=Camera::createPerspective(60, (GLfloat)s.width/s.height, 1, 1000);
        _camera->setCameraFlag(CameraFlag::USER1);
        _layer3D->addChild(_camera);
    }
    SwitchViewCallback(this,CameraType::ThirdPerson);
    DrawNode3D* line =DrawNode3D::create();
    //draw x
    for( int j =-20; j<=20 ;j++)
    {
        line->drawLine(Vec3(-100, 0, 5*j),Vec3(100,0,5*j),Color4F(1,0,0,1));
    }
    //draw z
    for( int j =-20; j<=20 ;j++)
    {
        line->drawLine(Vec3(5*j, 0, -100),Vec3(5*j,0,100),Color4F(0,0,1,1));
    }
    //draw y
    line->drawLine(Vec3(0, -50, 0),Vec3(0,0,0),Color4F(0,0.5,0,1));
    line->drawLine(Vec3(0, 0, 0),Vec3(0,50,0),Color4F(0,1,0,1));
    _layer3D->addChild(line);

    _layer3D->setCameraMask(2);
}
void Camera3DTestDemo::onExit()
{
    CameraBaseTest::onExit();
    if (_camera)
    {
        _camera = nullptr;
    }
}

void Camera3DTestDemo::addNewSpriteWithCoords(Vec3 p,std::string fileName,bool playAnimation,float scale,bool bindCamera)
{
    auto sprite = Sprite3D::create(fileName);
    _layer3D->addChild(sprite);
    float globalZOrder=sprite->getGlobalZOrder();
    sprite->setPosition3D( Vec3( p.x, p.y,p.z) );
    sprite->setGlobalZOrder(globalZOrder);
    if(playAnimation)
    {
        auto animation = Animation3D::create(fileName,"Take 001");
        if (animation)
        {
            auto animate = Animate3D::create(animation);
            sprite->runAction(RepeatForever::create(animate));
        }
    }
    if(bindCamera)
    {
        _sprite3D=sprite;
    }
    sprite->setScale(scale);  
}
void Camera3DTestDemo::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    for ( auto &item: touches )
    {
        auto touch = item;
        auto location = touch->getLocation();
    }
}
void Camera3DTestDemo::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    if(touches.size()==1)
    {
        auto touch = touches[0];
        auto location = touch->getLocation();
        Point newPos = touch->getPreviousLocation()-location;
        if(_cameraType==CameraType::Free || _cameraType==CameraType::FirstPerson)
        {
            Vec3 cameraDir;
            Vec3 cameraRightDir;
            _camera->getNodeToWorldTransform().getForwardVector(&cameraDir);
            cameraDir.normalize();
            cameraDir.y=0;
            _camera->getNodeToWorldTransform().getRightVector(&cameraRightDir);
            cameraRightDir.normalize();
            cameraRightDir.y=0;
            Vec3 cameraPos=  _camera->getPosition3D();
            cameraPos+=cameraDir*newPos.y*0.1f;
            cameraPos+=cameraRightDir*newPos.x*0.1f;
            _camera->setPosition3D(cameraPos);
            if(_sprite3D &&  _cameraType==CameraType::FirstPerson)
            {
                _sprite3D->setPosition3D(Vec3(_camera->getPositionX(),0,_camera->getPositionZ()));
                _targetPos=_sprite3D->getPosition3D();
            }
        }
    }
}
void Camera3DTestDemo::move3D(float elapsedTime)
{
    if(_sprite3D)
    {
        Vec3 curPos=  _sprite3D->getPosition3D();
        Vec3 newFaceDir = _targetPos - curPos;
        newFaceDir.y = 0.0f;
        newFaceDir.normalize();
        Vec3 offset = newFaceDir * 25.0f * elapsedTime;
        curPos+=offset;
        _sprite3D->setPosition3D(curPos);
        offset.x=offset.x;
        offset.z=offset.z;
        if(_cameraType==CameraType::ThirdPerson)
        {
            Vec3 cameraPos= _camera->getPosition3D();
            cameraPos.x+=offset.x;
            cameraPos.z+=offset.z;
            _camera->setPosition3D(cameraPos);
        }
    }
}
void Camera3DTestDemo::updateState(float elapsedTime)
{
    if(_sprite3D)
    {
        Vec3 curPos=  _sprite3D->getPosition3D();
        Vec3 curFaceDir;
        _sprite3D->getNodeToWorldTransform().getForwardVector(&curFaceDir);
        curFaceDir=-curFaceDir;
        curFaceDir.normalize();
        Vec3 newFaceDir = _targetPos - curPos;
        newFaceDir.y = 0.0f;
        newFaceDir.normalize();
        float cosAngle = std::fabs(Vec3::dot(curFaceDir,newFaceDir) - 1.0f);
        float dist = curPos.distanceSquared(_targetPos);
        if(dist<=4.0f)
        {
            if(cosAngle<=0.01f)
                _curState = State_Idle;
            else
                _curState = State_Rotate;
        }
        else
        {
            if(cosAngle>0.01f)
                _curState = State_Rotate | State_Move;
            else
                _curState = State_Move;
        }
    }
}
void Camera3DTestDemo::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    for ( auto &item: touches )
    {
        auto touch = item;
        auto location = touch->getLocationInView();
        if(_camera)
        {
            if(_sprite3D && _cameraType==CameraType::ThirdPerson && _bZoomOut == false && _bZoomIn == false && _bRotateLeft == false && _bRotateRight == false)
            {
                Vec3 nearP(location.x, location.y, -1.0f), farP(location.x, location.y, 1.0f);
                
                auto size = Director::getInstance()->getWinSize();
                nearP = _camera->unproject(nearP);
                farP = _camera->unproject(farP);
                Vec3 dir(farP - nearP);
                float dist=0.0f;
                float ndd = Vec3::dot(Vec3(0,1,0),dir);
                if(ndd == 0)
                    dist=0.0f;
                float ndo = Vec3::dot(Vec3(0,1,0),nearP);
                dist= (0 - ndo) / ndd;
                Vec3 p =   nearP + dist *  dir;
                
                if( p.x > 100)
                    p.x = 100;
                if( p.x < -100)
                    p.x = -100;
                if( p.z > 100)
                    p.z = 100;
                if( p.z < -100)
                    p.z = -100;
                
                _targetPos=p;
            }
        }
    }
}
void onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
}
void Camera3DTestDemo::updateCamera(float fDelta)
{
    if(_sprite3D)
    {
        if( _cameraType==CameraType::ThirdPerson)
        {
            updateState(fDelta);
            if(isState(_curState,State_Move))
            {
                move3D(fDelta);
                if(isState(_curState,State_Rotate))
                {
                    Vec3 curPos = _sprite3D->getPosition3D();
                    
                    Vec3 newFaceDir = _targetPos - curPos;
                    newFaceDir.y = 0;
                    newFaceDir.normalize();
                    Vec3 up;
                    _sprite3D->getNodeToWorldTransform().getUpVector(&up);
                    up.normalize();
                    Vec3 right;
                    Vec3::cross(-newFaceDir,up,&right);
                    right.normalize();
                    Vec3 pos = Vec3(0,0,0);
                    Mat4 mat;
                    mat.m[0] = right.x;
                    mat.m[1] = right.y;
                    mat.m[2] = right.z;
                    mat.m[3] = 0.0f;
                    
                    mat.m[4] = up.x;
                    mat.m[5] = up.y;
                    mat.m[6] = up.z;
                    mat.m[7] = 0.0f;
                    
                    mat.m[8]  = newFaceDir.x;
                    mat.m[9]  = newFaceDir.y;
                    mat.m[10] = newFaceDir.z;
                    mat.m[11] = 0.0f;
                    
                    mat.m[12] = pos.x;
                    mat.m[13] = pos.y;
                    mat.m[14] = pos.z;
                    mat.m[15] = 1.0f;
                    _sprite3D->setAdditionalTransform(&mat);
                }
            }
        }
        if(_bZoomOut == true)
        {
            if(_camera)
            {
                if(_cameraType == CameraType::ThirdPerson)
                {
                    Vec3 lookDir = _camera->getPosition3D() - _sprite3D->getPosition3D();
                    Vec3 cameraPos = _camera->getPosition3D();
                    if(lookDir.length() <= 300)
                    {
                        cameraPos += lookDir.getNormalized();
                        _camera->setPosition3D(cameraPos);
                    }
                }
                else if(_cameraType == CameraType::Free)
                {
                    Vec3 cameraPos = _camera->getPosition3D();
                    if(cameraPos.length() <= 300)
                    {
                        cameraPos += cameraPos.getNormalized();
                        _camera->setPosition3D(cameraPos);
                    }
                }
            }
        }
        if(_bZoomIn == true)
        {
            if(_camera)
            {
                if(_cameraType == CameraType::ThirdPerson)
                {
                    Vec3 lookDir = _camera->getPosition3D() - _sprite3D->getPosition3D();
                    Vec3 cameraPos = _camera->getPosition3D();
                    if(lookDir.length() >= 50)
                    {
                        cameraPos -= lookDir.getNormalized();
                        _camera->setPosition3D(cameraPos);
                    }
                }
                else if(_cameraType == CameraType::Free)
                {
                    Vec3 cameraPos = _camera->getPosition3D();
                    if(cameraPos.length() >= 50)
                    {
                        cameraPos -= cameraPos.getNormalized();
                        _camera->setPosition3D(cameraPos);
                    }
                }
            }
        }
        if(_bRotateLeft == true)
        {
            if(_cameraType==CameraType::Free || _cameraType==CameraType::FirstPerson)
            {
                Vec3  rotation3D= _camera->getRotation3D();
                rotation3D.y+= 1;
                _camera->setRotation3D(rotation3D);
            }
        }
        if(_bRotateRight == true)
        {
            if(_cameraType==CameraType::Free || _cameraType==CameraType::FirstPerson)
            {
                Vec3  rotation3D= _camera->getRotation3D();
                rotation3D.y-= 1;
                _camera->setRotation3D(rotation3D);
            }
        }
    }
}
bool Camera3DTestDemo::onTouchesCommon(Touch* touch, Event* event, bool* touchProperty)
{
    auto target = static_cast<Label*>(event->getCurrentTarget());
    
    Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
    Size s = target->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    
    if (rect.containsPoint(locationInNode))
    {
        *touchProperty = true;
        return true;
    }
    return false;
}
bool Camera3DTestDemo::isState(unsigned int state,unsigned int bit) const
{
    return (state & bit) == bit;
}
bool Camera3DTestDemo::onTouchesZoomOut(Touch* touch, Event* event)
{
    return Camera3DTestDemo::onTouchesCommon(touch, event, &_bZoomOut);
}
void Camera3DTestDemo::onTouchesZoomOutEnd(Touch* touch, Event* event)
{
    _bZoomOut = false;
}
bool Camera3DTestDemo::onTouchesZoomIn(Touch* touch, Event* event)
{
    return Camera3DTestDemo::onTouchesCommon(touch, event, &_bZoomIn);
}
void Camera3DTestDemo::onTouchesZoomInEnd(Touch* touch, Event* event)
{
    _bZoomIn = false;
}
bool Camera3DTestDemo::onTouchesRotateLeft(Touch* touch, Event* event)
{
    return Camera3DTestDemo::onTouchesCommon(touch, event, &_bRotateLeft);
}
void Camera3DTestDemo::onTouchesRotateLeftEnd(Touch* touch, Event* event)
{
    _bRotateLeft = false;
}
bool Camera3DTestDemo::onTouchesRotateRight(Touch* touch, Event* event)
{
    return Camera3DTestDemo::onTouchesCommon(touch, event, &_bRotateRight);
}
void Camera3DTestDemo::onTouchesRotateRightEnd(Touch* touch, Event* event)
{
    _bRotateRight = false;
}

////////////////////////////////////////////////////////////
// CameraCullingDemo
CameraCullingDemo::CameraCullingDemo(void)
: _layer3D(nullptr)
, _cameraType(CameraType::FirstPerson)
, _cameraFirst(nullptr)
, _cameraThird(nullptr)
, _moveAction(nullptr)
, _drawAABB(nullptr)
, _drawFrustum(nullptr)
, _row(3)
{
}
CameraCullingDemo::~CameraCullingDemo(void)
{
}

std::string CameraCullingDemo::title() const
{
    return "Camera Frustum Clipping";
}

void CameraCullingDemo::onEnter()
{
    CameraBaseTest::onEnter();

    schedule(schedule_selector(CameraCullingDemo::update), 0.0f);
    
    auto s = Director::getInstance()->getWinSize();
    /*auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(Camera3DTestDemo::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Camera3DTestDemo::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Camera3DTestDemo::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);*/
    auto layer3D=Layer::create();
    addChild(layer3D,0);
    _layer3D=layer3D;
    
    // swich camera
    MenuItemFont::setFontName("fonts/arial.ttf");
    MenuItemFont::setFontSize(20);
    
    auto menuItem1 = MenuItemFont::create("Switch Camera", CC_CALLBACK_1(CameraCullingDemo::switchViewCallback,this));
    menuItem1->setColor(Color3B(0,200,20));
    auto menu = Menu::create(menuItem1,NULL);
    menu->setPosition(Vec2::ZERO);
    menuItem1->setPosition(VisibleRect::left().x + 80, VisibleRect::top().y -70);
    addChild(menu, 1);
    
    // + -
    MenuItemFont::setFontSize(40);
    auto decrease = MenuItemFont::create(" - ", CC_CALLBACK_1(CameraCullingDemo::delSpriteCallback, this));
    decrease->setColor(Color3B(0,200,20));
    auto increase = MenuItemFont::create(" + ", CC_CALLBACK_1(CameraCullingDemo::addSpriteCallback, this));
    increase->setColor(Color3B(0,200,20));
    
    menu = Menu::create(decrease, increase, nullptr);
    menu->alignItemsHorizontally();
    menu->setPosition(Vec2(s.width - 60, VisibleRect::top().y -70));
    addChild(menu, 1);
    
    TTFConfig ttfCount("fonts/Marker Felt.ttf", 30);
    _labelSprite3DCount = Label::createWithTTF(ttfCount,"0 sprits");
    _labelSprite3DCount->setColor(Color3B(0,200,20));
    _labelSprite3DCount->setPosition(Vec2(s.width/2, VisibleRect::top().y -70));
    addChild(_labelSprite3DCount);
    
    // aabb drawNode3D
    _drawAABB = DrawNode3D::create();
    _drawAABB->setCameraMask((unsigned short) CameraFlag::USER1);
    addChild(_drawAABB);
    
    // frustum drawNode3D
    _drawFrustum = DrawNode3D::create();
    _drawFrustum->setCameraMask((unsigned short) CameraFlag::USER1);
    addChild(_drawFrustum);
    
    // set camera
    switchViewCallback(this);
    
    // add sprite
    addSpriteCallback(nullptr);
}

void CameraCullingDemo::onExit()
{
    CameraBaseTest::onExit();
    if (_cameraFirst)
    {
        _cameraFirst = nullptr;
    }
    if (_cameraThird)
    {
        _cameraThird = nullptr;
    }
}

void CameraCullingDemo::update(float dt)
{
    _drawAABB->clear();
    
    if(_cameraType == CameraType::ThirdPerson)
        drawCameraFrustum();
    
    Vector<Node*>& children = _layer3D->getChildren();
    Vec3 corners[8];
    
    for (const auto& iter: children)
    {
        const AABB& aabb = static_cast<Sprite3D*>(iter)->getAABB();
        if (_cameraFirst->isVisibleInFrustum(&aabb))
        {
            aabb.getCorners(corners);
            _drawAABB->drawCube(corners, Color4F(0, 1, 0, 1));
        }
    }
}

void CameraCullingDemo::reachEndCallBack()
{
    _cameraFirst->stopActionByTag(100);
    auto inverse = MoveTo::create(4.f, Vec2(-_cameraFirst->getPositionX(), 0));
    inverse->retain();
    
    _moveAction->release();
    _moveAction = inverse;
    auto rot = RotateBy::create(1.f, Vec3(0.f, 180.f, 0.f));
    auto seq = Sequence::create(rot, _moveAction, CallFunc::create(CC_CALLBACK_0(CameraCullingDemo::reachEndCallBack, this)), nullptr);
    seq->setTag(100);
    _cameraFirst->runAction(seq);
}

void CameraCullingDemo::switchViewCallback(Ref* sender)
{
    auto s = Director::getInstance()->getWinSize();
    
    if (_cameraFirst == nullptr)
    {
        _cameraFirst = Camera::createPerspective(30, (GLfloat)s.width/s.height, 10, 200);
        _cameraFirst->setCameraFlag(CameraFlag::USER8);
        _cameraFirst->setPosition3D(Vec3(-100,0,0));
        _cameraFirst->lookAt(Vec3(1000,0,0));
        _moveAction = MoveTo::create(4.f, Vec2(-_cameraFirst->getPositionX(), 0));
        _moveAction->retain();
        auto seq = Sequence::create(_moveAction, CallFunc::create(CC_CALLBACK_0(CameraCullingDemo::reachEndCallBack, this)), nullptr);
        seq->setTag(100);
        _cameraFirst->runAction(seq);
        addChild(_cameraFirst);
    }
    
    if (_cameraThird == nullptr)
    {
        _cameraThird = Camera::createPerspective(60, (GLfloat)s.width/s.height, 1, 1000);
        _cameraThird->setCameraFlag(CameraFlag::USER8);
        _cameraThird->setPosition3D(Vec3(0, 130, 130));
        _cameraThird->lookAt(Vec3(0,0,0));
        addChild(_cameraThird);
    }
    
    if(_cameraType == CameraType::FirstPerson)
    {
        _cameraType = CameraType::ThirdPerson;
        _cameraThird->setCameraFlag(CameraFlag::USER1);
        _cameraFirst->setCameraFlag(CameraFlag::USER8);
    }
    else if(_cameraType == CameraType::ThirdPerson)
    {
        _cameraType = CameraType::FirstPerson;
        _cameraFirst->setCameraFlag(CameraFlag::USER1);
        _cameraThird->setCameraFlag(CameraFlag::USER8);
        _drawFrustum->clear();
    }
}

void CameraCullingDemo::addSpriteCallback(Ref* sender)
{
    _layer3D->removeAllChildren();
    _objects.clear();
    _drawAABB->clear();
    
    ++_row;
    for (int x = -_row; x < _row; x++)
    {
        for (int z = -_row; z < _row; z++)
        {
            auto sprite = Sprite3D::create("Sprite3DTest/orc.c3b");
            sprite->setPosition3D(Vec3(x * 30, 0, z * 30));
            sprite->setRotation3D(Vec3(0,180,0));
            _objects.push_back(sprite);
            _layer3D->addChild(sprite);
        }
    }
    
    // set layer mask.
    _layer3D->setCameraMask( (unsigned short) CameraFlag::USER1);
    
    // update sprite number
    char szText[16];
    sprintf(szText,"%ld sprits",_layer3D->getChildrenCount());
    _labelSprite3DCount->setString(szText);
}

void CameraCullingDemo::delSpriteCallback(Ref* sender)
{
    if (_row == 0) return;
    
    _layer3D->removeAllChildren();
    _objects.clear();
    
    --_row;
    for (int x = -_row; x < _row; x++)
    {
        for (int z = -_row; z < _row; z++)
        {
            auto sprite = Sprite3D::create("Sprite3DTest/orc.c3b");
            sprite->setPosition3D(Vec3(x * 30, 0, z * 30));
            _objects.push_back(sprite);
            _layer3D->addChild(sprite);
        }
    }
    
    // set layer mask.
    _layer3D->setCameraMask((unsigned short) CameraFlag::USER1);
    
    // update sprite number
    char szText[16];
    sprintf(szText,"%ld sprits",_layer3D->getChildrenCount());
    _labelSprite3DCount->setString(szText);
}

void CameraCullingDemo::drawCameraFrustum()
{
    _drawFrustum->clear();
    auto size = Director::getInstance()->getWinSize();
    
    Color4F color(1.f, 1.f, 0.f, 1);
    
    // top-left
    Vec3 tl_0,tl_1;
    Vec3 src(0,0,0);
    tl_0 = _cameraFirst->unproject(src);
    src = Vec3(0,0,1);
    tl_1 = _cameraFirst->unproject(src);
    
    // top-right
    Vec3 tr_0,tr_1;
    src = Vec3(size.width,0,0);
    tr_0 = _cameraFirst->unproject(src);
    src = Vec3(size.width,0,1);
    tr_1 = _cameraFirst->unproject(src);
    
    // bottom-left
    Vec3 bl_0,bl_1;
    src = Vec3(0,size.height,0);
    bl_0 = _cameraFirst->unproject(src);
    src = Vec3(0,size.height,1);
    bl_1 = _cameraFirst->unproject(src);
    
    // bottom-right
    Vec3 br_0,br_1;
    src = Vec3(size.width,size.height,0);
    br_0 = _cameraFirst->unproject(src);
    src = Vec3(size.width,size.height,1);
    br_1 = _cameraFirst->unproject(src);
    
    _drawFrustum->drawLine(tl_0, tl_1, color);
    _drawFrustum->drawLine(tr_0, tr_1, color);
    _drawFrustum->drawLine(bl_0, bl_1, color);
    _drawFrustum->drawLine(br_0, br_1, color);
    
    _drawFrustum->drawLine(tl_0, tr_0, color);
    _drawFrustum->drawLine(tr_0, br_0, color);
    _drawFrustum->drawLine(br_0, bl_0, color);
    _drawFrustum->drawLine(bl_0, tl_0, color);
    
    _drawFrustum->drawLine(tl_1, tr_1, color);
    _drawFrustum->drawLine(tr_1, br_1, color);
    _drawFrustum->drawLine(br_1, bl_1, color);
    _drawFrustum->drawLine(bl_1, tl_1, color);
}

////////////////////////////////////////////////////////////
// CameraArcBallDemo
CameraArcBallDemo::CameraArcBallDemo(void)
: CameraBaseTest()
, _layer3D(nullptr)
, _cameraType(CameraType::Free)
, _camera(nullptr)
, _drawGrid(nullptr)
, _radius(1.0f)
, _distanceZ(50.0f)
, _operate(OperateCamType::RotateCamera)
, _center(Vec3(0,0,0))
, _target(0)
, _sprite3D1(nullptr)
, _sprite3D2(nullptr)
{
}
CameraArcBallDemo::~CameraArcBallDemo(void)
{
}

std::string CameraArcBallDemo::title() const
{
    return "Camera ArcBall Moving";
}

void CameraArcBallDemo::onEnter()
{
    CameraBaseTest::onEnter();
    _rotationQuat.set(0.0f, 0.0f, 0.0f, 1.0f);
    schedule(schedule_selector(CameraArcBallDemo::update), 0.0f);
    auto s = Director::getInstance()->getWinSize();
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(CameraArcBallDemo::onTouchsMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // swich camera
    MenuItemFont::setFontName("fonts/arial.ttf");
    MenuItemFont::setFontSize(20);
    
    auto menuItem1 = MenuItemFont::create("Switch Operation", CC_CALLBACK_1(CameraArcBallDemo::switchOperateCallback,this));
    menuItem1->setColor(Color3B(0,200,20));
    auto menuItem2 = MenuItemFont::create("Switch Target", CC_CALLBACK_1(CameraArcBallDemo::switchTargetCallback,this));
    menuItem2->setColor(Color3B(0,200,20));
    auto menu = Menu::create(menuItem1,menuItem2,NULL);
    menu->setPosition(Vec2::ZERO);
    menuItem1->setPosition(VisibleRect::left().x + 80, VisibleRect::top().y -70);
    menuItem2->setPosition(VisibleRect::left().x + 80, VisibleRect::top().y -100);
    addChild(menu, 1);

    auto layer3D=Layer::create();
    addChild(layer3D,0);
    _layer3D=layer3D;

    if (_camera == nullptr)
    {
        _camera=Camera::createPerspective(60, (GLfloat)s.width/s.height, 1, 1000);
        _camera->setCameraFlag(CameraFlag::USER1);
        _camera->setPosition3D(Vec3(0, 10, 50));
        _camera->lookAt(Vec3(0, 0, 0), Vec3(0, 1, 0));
        _camera->retain();
        _layer3D->addChild(_camera);
    }

    _sprite3D1 = Sprite3D::create("Sprite3DTest/orc.c3b");
    _sprite3D1->setScale(0.5);
    _sprite3D1->setRotation3D(Vec3(0,180,0));
    _sprite3D1->setPosition3D(Vec3(0,0,0));
    _layer3D->addChild(_sprite3D1);

    _sprite3D2 = Sprite3D::create("Sprite3DTest/boss.c3b");
    _sprite3D2->setScale(0.6f);
    _sprite3D2->setRotation3D(Vec3(-90,0,0));
    _sprite3D2->setPosition3D(Vec3(20,0,0));
    _layer3D->addChild(_sprite3D2);

    _drawGrid =DrawNode3D::create();

    //draw x
    for( int j =-20; j<=20 ;j++)
    {
        _drawGrid->drawLine(Vec3(-100, 0, 5*j),Vec3(100,0,5*j),Color4F(1,0,0,1));
    }
    //draw z
    for( int j =-20; j<=20 ;j++)
    {
        _drawGrid->drawLine(Vec3(5*j, 0, -100),Vec3(5*j,0,100),Color4F(0,0,1,1));
    }
    //draw y
    _drawGrid->drawLine(Vec3(0, 0, 0),Vec3(0,50,0),Color4F(0,1,0,1));
    _layer3D->addChild(_drawGrid);

    _layer3D->setCameraMask(2);

    updateCameraTransform();

}

void CameraArcBallDemo::onExit()
{
    CameraBaseTest::onExit();
    if (_camera)
    {
        _camera = nullptr;
    }
}

void CameraArcBallDemo::onTouchsMoved( const std::vector<Touch*> &touchs, Event *event )
{
    if (!touchs.empty())
    {
        if(_operate == OperateCamType::RotateCamera)           //arc ball rotate
        {
            Size visibleSize = Director::getInstance()->getVisibleSize();
            Vec2 prelocation = touchs[0]->getPreviousLocationInView();
            Vec2 location = touchs[0]->getLocationInView();
            location.x = 2.0 * (location.x) / (visibleSize.width) - 1.0f;
            location.y = 2.0 * (visibleSize.height - location.y) / (visibleSize.height) - 1.0f;
            prelocation.x = 2.0 * (prelocation.x) / (visibleSize.width) - 1.0f;
            prelocation.y = 2.0 * (visibleSize.height - prelocation.y) / (visibleSize.height) - 1.0f;

            Vec3 axes;
            float angle;
            calculateArcBall(axes, angle, prelocation.x, prelocation.y, location.x, location.y);    //calculate  rotation quaternion parameters
            Quaternion quat(axes, angle);                                                           //get rotation quaternion
            _rotationQuat = quat * _rotationQuat;

            updateCameraTransform();                                                                //update camera Transform
        }
        else if(_operate == OperateCamType::MoveCamera)         //camera zoom 
        {
            Point newPos = touchs[0]->getPreviousLocation() - touchs[0]->getLocation();
            _distanceZ -= newPos.y*0.1f;

            updateCameraTransform();
        }
    }
}

void CameraArcBallDemo::calculateArcBall( cocos2d::Vec3 & axis, float & angle, float p1x, float p1y, float p2x, float p2y )
{
    Mat4 rotation_matrix;
    Mat4::createRotation(_rotationQuat, &rotation_matrix);

    Vec3 uv = rotation_matrix * Vec3(0.0f,1.0f,0.0f); //rotation y
    Vec3 sv = rotation_matrix * Vec3(1.0f,0.0f,0.0f); //rotation x
    Vec3 lv = rotation_matrix * Vec3(0.0f,0.0f,-1.0f);//rotation z

    Vec3 p1 = sv * p1x + uv * p1y - lv * projectToSphere(_radius, p1x, p1y); //start point screen transform to 3d
    Vec3 p2 = sv * p2x + uv * p2y - lv * projectToSphere(_radius, p2x, p2y); //end point screen transform to 3d

    Vec3::cross(p2, p1, &axis);  //calculate rotation axis
    axis.normalize();

    float t = (p2 - p1).length() / (2.0 * _radius);
    //clamp -1 to 1
    if (t > 1.0) t = 1.0;
    if (t < -1.0) t = -1.0;
    angle = asin(t);           //rotation angle
}

/* project an x,y pair onto a sphere of radius r or a
hyperbolic sheet if we are away from the center of the sphere. */
float CameraArcBallDemo::projectToSphere( float r, float x, float y )
{
    float d, t, z;
    d = sqrt(x*x + y*y);
    if (d < r * 0.70710678118654752440)//inside sphere
    {
        z = sqrt(r*r - d*d);
    }                         
    else                               //on hyperbola
    {
        t = r / 1.41421356237309504880;
        z = t*t / d;
    }
    return z;
}

void CameraArcBallDemo::updateCameraTransform()
{
    Mat4 trans, rot, center;
    Mat4::createTranslation(Vec3(0.0f, 10.0f, _distanceZ), &trans);
    Mat4::createRotation(_rotationQuat, &rot);
    Mat4::createTranslation(_center, &center);
    Mat4 result = center * rot * trans;
    _camera->setNodeToParentTransform(result);

}

void CameraArcBallDemo::switchOperateCallback(Ref* sender)
{
    if(_operate == OperateCamType::MoveCamera)
    {
        _operate = OperateCamType::RotateCamera;
    }
    else if(_operate == OperateCamType::RotateCamera)
    {
        _operate = OperateCamType::MoveCamera;
    }
}

void CameraArcBallDemo::switchTargetCallback(Ref* sender)
{
    if(_target == 0)
    {
        _target = 1;
        _center = _sprite3D2->getPosition3D();
        updateCameraTransform();
    }
    else if(_target == 1)
    {
        _target = 0;
        _center = _sprite3D1->getPosition3D();
        updateCameraTransform();
    }
}

void CameraArcBallDemo::update(float dt)
{
     //updateCameraTransform();
}

////////////////////////////////////////////////////////////
// FogTestDemo
FogTestDemo::FogTestDemo(void)
: CameraBaseTest()
, _layer3D(nullptr)
, _cameraType(CameraType::Free)
, _camera(nullptr)
, _shader(nullptr)
, _state(nullptr)
{
}
FogTestDemo::~FogTestDemo(void)
{
}

std::string FogTestDemo::title() const
{
    return "Fog Test Demo";
}

void FogTestDemo::onEnter()
{
    CameraBaseTest::onEnter();
    schedule(schedule_selector(FogTestDemo::update), 0.0f);
    Director::getInstance()->setClearColor(Color4F(0.5,0.5,0.5,1));

    auto s = Director::getInstance()->getWinSize();
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(FogTestDemo::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // swich fog type
    TTFConfig ttfConfig("fonts/arial.ttf", 20);
    
    auto label1 = Label::createWithTTF(ttfConfig,"Linear ");
    auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(FogTestDemo::switchTypeCallback,this,0));
    auto label2 = Label::createWithTTF(ttfConfig,"Exp");
    auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(FogTestDemo::switchTypeCallback,this,1));
    auto label3 = Label::createWithTTF(ttfConfig,"Exp2");
    auto menuItem3 = MenuItemLabel::create(label3, CC_CALLBACK_1(FogTestDemo::switchTypeCallback,this,2));
    auto menu = Menu::create(menuItem1, menuItem2, menuItem3, nullptr);
    
    menu->setPosition(Vec2::ZERO);
    
    menuItem1->setPosition(VisibleRect::left().x+60, VisibleRect::top().y-50);
    menuItem2->setPosition(VisibleRect::left().x+60, VisibleRect::top().y -100);
    menuItem3->setPosition(VisibleRect::left().x+60, VisibleRect::top().y -150);
    addChild(menu, 0);


    auto layer3D=Layer::create();
    addChild(layer3D,0);
    _layer3D=layer3D;

    _shader =GLProgram::createWithFilenames("Sprite3DTest/fog.vert","Sprite3DTest/fog.frag");
    _state = GLProgramState::create(_shader);

    _sprite3D1 = Sprite3D::create("Sprite3DTest/teapot.c3b");
    _sprite3D2 = Sprite3D::create("Sprite3DTest/teapot.c3b");

    _sprite3D1->setGLProgramState(_state);
    _sprite3D2->setGLProgramState(_state);
    //pass mesh's attribute to shader
    long offset = 0; 
    auto attributeCount = _sprite3D1->getMesh()->getMeshVertexAttribCount();
    for (auto i = 0; i < attributeCount; i++) {
        auto meshattribute = _sprite3D1->getMesh()->getMeshVertexAttribute(i);
        _state->setVertexAttribPointer(s_attributeNames[meshattribute.vertexAttrib],
            meshattribute.size, 
            meshattribute.type,
            GL_FALSE,
            _sprite3D1->getMesh()->getVertexSizeInBytes(),
            (GLvoid*)offset);
        offset += meshattribute.attribSizeBytes;
    }

    long offset1 = 0; 
    auto attributeCount1 = _sprite3D2->getMesh()->getMeshVertexAttribCount();
    for (auto i = 0; i < attributeCount1; i++) {
        auto meshattribute = _sprite3D2->getMesh()->getMeshVertexAttribute(i);
        _state->setVertexAttribPointer(s_attributeNames[meshattribute.vertexAttrib],
            meshattribute.size, 
            meshattribute.type,
            GL_FALSE,
            _sprite3D2->getMesh()->getVertexSizeInBytes(),
            (GLvoid*)offset1);
        offset1 += meshattribute.attribSizeBytes;
    }

    _state->setUniformVec4("u_fogColor", Vec4(0.5,0.5,0.5,1.0));
    _state->setUniformFloat("u_fogStart",10);
    _state->setUniformFloat("u_fogEnd",60);
    _state->setUniformInt("u_fogEquation" ,0);

    _layer3D->addChild(_sprite3D1);
    _sprite3D1->setPosition3D( Vec3( 0, 0,0 ) );
    _sprite3D1->setScale(2.0f);
    _sprite3D1->setRotation3D(Vec3(-90,180,0));

    _layer3D->addChild(_sprite3D2);
    _sprite3D2->setPosition3D( Vec3( 0, 0,-20 ) );
    _sprite3D2->setScale(2.0f);
    _sprite3D2->setRotation3D(Vec3(-90,180,0));

    if (_camera == nullptr)
    {
        _camera=Camera::createPerspective(60, (GLfloat)s.width/s.height, 1, 1000);
        _camera->setCameraFlag(CameraFlag::USER1);
        _camera->setPosition3D(Vec3(0, 30, 40));
        _camera->lookAt(Vec3(0,0,0), Vec3(0, 1, 0));

        _layer3D->addChild(_camera);
    }
    _layer3D->setCameraMask(2);


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    _backToForegroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
                                                            [this](EventCustom*)
                                                            {
                                                                Director::getInstance()->setClearColor(Color4F(0.5,0.5,0.5,1));
                                                                auto glProgram = _state->getGLProgram();
                                                                glProgram->reset();
                                                                glProgram->initWithFilenames("Sprite3DTest/fog.vert","Sprite3DTest/fog.frag");
                                                                glProgram->link();
                                                                glProgram->updateUniforms();
                                                                
                                                                _state->setUniformVec4("u_fogColor", Vec4(0.5,0.5,0.5,1.0));
                                                                _state->setUniformFloat("u_fogStart",10);
                                                                _state->setUniformFloat("u_fogEnd",60);
                                                                _state->setUniformInt("u_fogEquation" ,0);
                                                            }
                                                            );
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, -1);
#endif

}

void FogTestDemo::switchTypeCallback(Ref* sender,int type)
{
    if(type == 0)
    {
        _state->setUniformVec4("u_fogColor", Vec4(0.5,0.5,0.5,1.0));
        _state->setUniformFloat("u_fogStart",10);
        _state->setUniformFloat("u_fogEnd",60);
        _state->setUniformInt("u_fogEquation" ,0);

        _sprite3D1->setGLProgramState(_state);
        _sprite3D2->setGLProgramState(_state);
    }
    else if(type == 1)
    {
        _state->setUniformVec4("u_fogColor", Vec4(0.5,0.5,0.5,1.0));
        _state->setUniformFloat("u_fogDensity",0.03f);
        _state->setUniformInt("u_fogEquation" ,1);

        _sprite3D1->setGLProgramState(_state);
        _sprite3D2->setGLProgramState(_state);
    }
    else if(type == 2)
    {
        _state->setUniformVec4("u_fogColor", Vec4(0.5,0.5,0.5,1.0));
        _state->setUniformFloat("u_fogDensity",0.03f);
        _state->setUniformInt("u_fogEquation" ,2);

        _sprite3D1->setGLProgramState(_state);
        _sprite3D2->setGLProgramState(_state);
    }
}

void FogTestDemo::onExit()
{
    CameraBaseTest::onExit();
    Director::getInstance()->setClearColor(Color4F(0,0,0,1));
    if (_camera)
    {
        _camera = nullptr;
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif
}

void FogTestDemo::update(float dt)
{
}

void FogTestDemo::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    if(touches.size()==1)
    {
        Vec2 prelocation = touches[0]->getPreviousLocationInView();
        Vec2 location = touches[0]->getLocationInView();
        Vec2 newPos = prelocation - location;
        if(_cameraType==CameraType::Free)
        {
            Vec3 cameraDir;
            Vec3 cameraRightDir;
            _camera->getNodeToWorldTransform().getForwardVector(&cameraDir);
            cameraDir.normalize();
            cameraDir.y=0;
            _camera->getNodeToWorldTransform().getRightVector(&cameraRightDir);
            cameraRightDir.normalize();
            cameraRightDir.y=0;
            Vec3 cameraPos=  _camera->getPosition3D();
            cameraPos-=cameraDir*newPos.y*0.1f;
            cameraPos+=cameraRightDir*newPos.x*0.1f;
            _camera->setPosition3D(cameraPos);
        }
    }
}

CameraFrameBufferTest::CameraFrameBufferTest()
{
    
}

CameraFrameBufferTest::~CameraFrameBufferTest()
{
    
}

std::string CameraFrameBufferTest::title() const
{
    return "Camera FrameBuffer Object Test";
}

void CameraFrameBufferTest::onEnter()
{
    auto sizeInpixels = Director::getInstance()->getWinSizeInPixels();
    auto size = Director::getInstance()->getWinSize();
    auto fboSize = Size(sizeInpixels.width * 1, sizeInpixels.height * 1.5);
    auto fbo = experimental::FrameBuffer::create(1, fboSize.width, fboSize.height);
    
    CameraBaseTest::onEnter();
    //auto sprite = Sprite::createWithTexture(fbo);
    //sprite->setPosition(Vec2(100,100));
    //std::string filename = "Sprite3DTest/girl.c3b";
    //auto sprite = Sprite3D::create(filename);
    //sprite->setScale(1.0);
    //auto animation = Animation3D::create(filename);
    //if (animation)
    //{
    //    auto animate = Animate3D::create(animation);
        
    //    sprite->runAction(RepeatForever::create(animate));
    //}
    //sprite->setPosition(Vec2(100,100));
    auto rt = experimental::RenderTarget::create(fboSize.width, fboSize.height);
    auto rtDS = experimental::RenderTargetDepthStencil::create(fboSize.width, fboSize.height);
    fbo->attachRenderTarget(rt);
    fbo->attachDepthStencilTarget(rtDS);
    auto sprite = Sprite::createWithTexture(fbo->getRenderTarget()->getTexture());
    sprite->setScale(0.3);
    sprite->runAction(RepeatForever::create(RotateBy::create(1, 90)));
    sprite->setPosition(size.width/2, size.height/2);
    addChild(sprite);
    
    auto sprite2 = Sprite::create(s_pathGrossini);
    sprite2->setPosition(Vec2(size.width/5,size.height/5));
    addChild(sprite2);
    sprite2->setCameraMask((unsigned short)CameraFlag::USER1);
    auto move = MoveBy::create(1.0, Vec2(100,100));
    sprite2->runAction(
                       RepeatForever::create(
                                             Sequence::createWithTwoActions(
                                                                            move, move->reverse())
                                             )
                       );
    
    auto camera = Camera::create();
    camera->setCameraFlag(CameraFlag::USER1);
    camera->setDepth(-1);
    camera->setFrameBufferObject(fbo);
    fbo->setClearColor(Color4F(1,1,1,1));
    addChild(camera);
}
