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
#include <algorithm>
#include "../testResource.h"

#include "3d/CCDrawNode3D.h"
#include "3d/CCAttachNode.h"

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

static int sceneIdx = -1;

static std::function<Layer*()> createFunctions[] =
{
    CL(Camera3DTestDemo),
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

//------------------------------------------------------------------
//
// SpriteTestDemo
//
//------------------------------------------------------------------

Camera3DTestDemo::Camera3DTestDemo(void)
: BaseTest()
, _camera(nullptr)
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

std::string Camera3DTestDemo::subtitle() const
{
    return "";
}
void Camera3DTestDemo::scaleCameraCallback(Ref* sender,float value)
{
    if(_camera&& _cameraType!=CameraType::FirstCamera)
    {
        Vec3 cameraPos=  _camera->getPosition3D();
        cameraPos+= cameraPos.getNormalized()*value;
        _camera->setPosition3D(cameraPos);
    }
}	
void Camera3DTestDemo::rotateCameraCallback(Ref* sender,float value)
{
    if(_cameraType==CameraType::FreeCamera || _cameraType==CameraType::FirstCamera)
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
    if(_cameraType==CameraType::FreeCamera)
    {
         _camera->setPosition3D(Vec3(0, 130, 130) + _sprite3D->getPosition3D());
         _camera->lookAt(_sprite3D->getPosition3D(), Vec3(0,1,0));
    }
    else if(_cameraType==CameraType::FirstCamera)
    {
           Vec3 newFaceDir;
           _sprite3D->getWorldToNodeTransform().getForwardVector(&newFaceDir);
           newFaceDir.normalize();
           _camera->setPosition3D(Vec3(0,35,0) + _sprite3D->getPosition3D());
           _camera->lookAt(_sprite3D->getPosition3D() + newFaceDir*50, Vec3(0, 1, 0));
    }
    else if(_cameraType==CameraType::ThirdCamera)
    {
           _camera->setPosition3D(Vec3(0, 130, 130) + _sprite3D->getPosition3D());
           _camera->lookAt(_sprite3D->getPosition3D(), Vec3(0,1,0));
    }
}
void Camera3DTestDemo::onEnter()
{
    BaseTest::onEnter();
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
    addNewSpriteWithCoords( Vec3(0,0,0),"Sprite3DTest/girl.c3b",true,0.2,true);
    TTFConfig ttfConfig("fonts/arial.ttf", 20);
    auto label1 = Label::createWithTTF(ttfConfig,"zoom out");
    auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(Camera3DTestDemo::scaleCameraCallback,this,1));
    auto label2 = Label::createWithTTF(ttfConfig,"zoom in");
    auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(Camera3DTestDemo::scaleCameraCallback,this,-1));
    auto label3 = Label::createWithTTF(ttfConfig,"rotate+");
    auto menuItem3 = MenuItemLabel::create(label3, CC_CALLBACK_1(Camera3DTestDemo::rotateCameraCallback,this,10));
    auto label4 = Label::createWithTTF(ttfConfig,"rotate-");
    auto menuItem4 = MenuItemLabel::create(label4, CC_CALLBACK_1(Camera3DTestDemo::rotateCameraCallback,this,-10));
    auto label5 = Label::createWithTTF(ttfConfig,"free ");
    auto menuItem5 = MenuItemLabel::create(label5, CC_CALLBACK_1(Camera3DTestDemo::SwitchViewCallback,this,CameraType::FreeCamera));
    auto label6 = Label::createWithTTF(ttfConfig,"third person");
    auto menuItem6 = MenuItemLabel::create(label6, CC_CALLBACK_1(Camera3DTestDemo::SwitchViewCallback,this,CameraType::ThirdCamera));
    auto label7 = Label::createWithTTF(ttfConfig,"first person");
    auto menuItem7 = MenuItemLabel::create(label7, CC_CALLBACK_1(Camera3DTestDemo::SwitchViewCallback,this,CameraType::FirstCamera));
    auto menu = Menu::create(menuItem1,menuItem2,menuItem3,menuItem4,menuItem5,menuItem6,menuItem7,NULL);

    menu->setPosition(Vec2::ZERO);
    menuItem1->setPosition( Vec2( s.width-50, VisibleRect::top().y-50 ) );
    menuItem2->setPosition( Vec2( s.width-50, VisibleRect::top().y-100) );
    menuItem3->setPosition( Vec2( s.width-50, VisibleRect::top().y-150) );
    menuItem4->setPosition( Vec2( s.width-50, VisibleRect::top().y-200) );
    menuItem5->setPosition( Vec2(VisibleRect::left().x+100, VisibleRect::top().y-50) );
    menuItem6->setPosition( Vec2(VisibleRect::left().x+100, VisibleRect::top().y -100));
    menuItem7->setPosition( Vec2(VisibleRect::left().x+100, VisibleRect::top().y -150));
    addChild(menu, 0);
    schedule(schedule_selector(Camera3DTestDemo::updateCamera), 0.0f);
    if (_camera == nullptr)
    {
        _camera=Camera::createPerspective(60, (GLfloat)s.width/s.height, 1, 1000);
        _camera->setCameraFlag(CameraFlag::USER1);
        _layer3D->addChild(_camera);
    }
    SwitchViewCallback(this,CameraType::ThirdCamera);
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
    BaseTest::onExit();
    if (_camera)
    {
        _camera = nullptr;
    }
}

void Camera3DTestDemo::restartCallback(Ref* sender)
{
    auto s = new Camera3DTestScene();
    s->addChild(restartSpriteTestAction());

    Director::getInstance()->replaceScene(s);
    s->release();
}

void Camera3DTestDemo::nextCallback(Ref* sender)
{
    auto s = new Camera3DTestScene();
    s->addChild( nextSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}
void Camera3DTestDemo::backCallback(Ref* sender)
{
    auto s = new Camera3DTestScene();
    s->addChild( backSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}
void Camera3DTestDemo::addNewSpriteWithCoords(Vec3 p,std::string fileName,bool playAnimation,float scale,bool bindCamera)
{

    auto sprite = Sprite3D::create(fileName);
    sprite->setScale(1);
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
            bool inverse = (std::rand() % 3 == 0);

            int rand2 = std::rand();
            float speed = 1.0f;
            if(rand2 % 3 == 1)
            {
                speed = animate->getSpeed() + CCRANDOM_0_1();
            }
            else if(rand2 % 3 == 2)
            {
                speed = animate->getSpeed() - 0.5 * CCRANDOM_0_1();
            }
            animate->setSpeed(inverse ? -speed : speed);
            sprite->runAction(RepeatForever::create(animate));
            //auto sp = Sprite3D::create("Sprite3DTest/axe.c3b");
            // sprite->getAttachNode("Bip001 R Hand")->addChild(sp);
        }
    }
    if(bindCamera)
    {
        _sprite3D=sprite;
       // auto sp = Sprite3D::create("Sprite3DTest/axe.c3b");
      //  sp->setScale(3);
        //sprite->getAttachNode("Bip001 R Hand")->addChild(sp);
        //ParticleSystem3D* particleSystem3D = ParticleSystem3D::create("CameraTest/particle3Dtest1.particle");
        //particleSystem3D->start();
        //sprite->getAttachNode("Bip001 R Hand")->addChild(particleSystem3D);

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
        if(_cameraType==CameraType::FreeCamera || _cameraType==CameraType::FirstCamera)
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
             cameraPos+=cameraDir*newPos.y*0.1;
             cameraPos+=cameraRightDir*newPos.x*0.1;
            _camera->setPosition3D(cameraPos);
             if(_sprite3D &&  _cameraType==CameraType::FirstCamera)
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
        if(_cameraType==CameraType::ThirdCamera)
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
            if(_sprite3D && _cameraType==CameraType::ThirdCamera)
            {
                Vec3 nearP(location.x, location.y, -1.0f), farP(location.x, location.y, 1.0f);
                
                auto size = Director::getInstance()->getWinSize();
                _camera->unproject(size, &nearP, &nearP);
                _camera->unproject(size, &farP, &farP);
                Vec3 dir(farP - nearP);
                float dist=0.0f;
                float ndd = Vec3::dot(Vec3(0,1,0),dir);
                if(ndd == 0)
                    dist=0.0f;
                float ndo = Vec3::dot(Vec3(0,1,0),nearP);
                dist= (0 - ndo) / ndd;
                Vec3 p =   nearP + dist *  dir;
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
        if( _cameraType==CameraType::ThirdCamera)
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
    }
}
bool Camera3DTestDemo::isState(unsigned int state,unsigned int bit) const
{
    return (state & bit) == bit;
}
void Camera3DTestScene::runThisTest()
{
    auto layer = nextSpriteTestAction();
    addChild(layer);
    Director::getInstance()->replaceScene(this);
}
