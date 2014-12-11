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

#include "BillBoardTest.h"
#include "3d/CCBillBoard.h"

#include <algorithm>
#include "../testResource.h"

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

static int sceneIdx = -1;


static std::function<Layer*()> createFunctions[] =
{
    CL(BillBoardTest)
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

BillBoardTest::BillBoardTest()
:  _camera(nullptr)
{
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(BillBoardTest::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    auto layer3D=Layer::create();
    addChild(layer3D,0);
    _layerBillBorad=layer3D;
    auto s = Director::getInstance()->getWinSize();
    if (_camera == nullptr)
    {
        _camera=Camera::createPerspective(60, (GLfloat)s.width/s.height, 1, 500);
        _camera->setCameraFlag(CameraFlag::USER1);
        _layerBillBorad->addChild(_camera);
    }

    std::string imgs[3] = {"Images/Icon.png", "Images/r2.png"};
    for (unsigned int i = 0; i < 4; ++i)
    {
        Layer *layer = Layer::create();
        auto billboard = BillBoard::create(imgs[(unsigned int)(CCRANDOM_0_1() * 1 + 0.5)]);
        billboard->setScale(0.5f);
        billboard->setPosition3D(Vec3(0.0f, 0.0f,  CCRANDOM_MINUS1_1() * 150.0f));
        billboard->setBlendFunc(cocos2d::BlendFunc::ALPHA_NON_PREMULTIPLIED);
        billboard->setOpacity(CCRANDOM_0_1() * 128 + 128);
        _billboards.push_back(billboard);
        layer->addChild(billboard);
        _layerBillBorad->addChild(layer);
        layer->runAction( RepeatForever::create( RotateBy::create( CCRANDOM_0_1(), Vec3(0.0f, 45.0f, 0.0f) ) ) );
    }

    {
        auto billboard = BillBoard::create("Images/Icon.png");
        billboard->setScale(0.2f);
        billboard->setPosition3D(Vec3(0.0f, 30.0f, 0.0f));

        auto billboard2 = BillBoard::create("Images/r2.png");
        billboard2->setPosition3D(Vec3(0.0f, 0.0f, 100.0f));
        billboard->addChild(billboard2);
        _billboards.push_back(billboard);
        _billboards.push_back(billboard2);

        auto sprite3d = Sprite3D::create("Sprite3DTest/orc.c3t");
        sprite3d->setScale(2.0f);
        sprite3d->addChild(billboard);
        sprite3d->runAction( RepeatForever::create( RotateBy::create( 10.0f, Vec3(0.0f, 360.0f, 0.0f) ) ) );
        _layerBillBorad->addChild(sprite3d);
    }

    addNewBillBoradWithCoords(Vec3(20,5,0));
    addNewBillBoradWithCoords(Vec3(60,5,0));
    addNewBillBoradWithCoords(Vec3(100,5,0));
    addNewBillBoradWithCoords(Vec3(140,5,0));
    addNewBillBoradWithCoords(Vec3(180,5,0));
    addNewAniBillBoradWithCoords(Vec3(-20,0,0));
    addNewAniBillBoradWithCoords(Vec3(-60,0,0));
    addNewAniBillBoradWithCoords(Vec3(-100,0,0));
    addNewAniBillBoradWithCoords(Vec3(-140,0,0));
    addNewAniBillBoradWithCoords(Vec3(-180,0,0));
    _camera->setPosition3D(Vec3(0, 100, 230));
    _camera->lookAt(Vec3(0,0,0), Vec3(0,1,0));

    TTFConfig ttfConfig("fonts/arial.ttf", 16);
    auto label1 = Label::createWithTTF(ttfConfig,"rotate+");
    auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(BillBoardTest::rotateCameraCallback,this,10));
    auto label2 = Label::createWithTTF(ttfConfig,"rotate-");
    auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(BillBoardTest::rotateCameraCallback,this,-10));
    auto menu = Menu::create(menuItem1, menuItem2, nullptr);
    menu->setPosition(Vec2::ZERO);
    menuItem1->setPosition( Vec2( s.width-80, VisibleRect::top().y-160) );
    menuItem2->setPosition( Vec2( s.width-80, VisibleRect::top().y-190) );
    addChild(menu, 0);
    _layerBillBorad->setCameraMask(2);
    
    label1 = Label::createWithTTF(ttfConfig,"Point Oriented");
    menuItem1 = MenuItemLabel::create(label1,CC_CALLBACK_1(BillBoardTest::menuCallback_orientedPoint,this) );
    label2 = Label::createWithTTF(ttfConfig,"Plane Oriented");
    menuItem2 = MenuItemLabel::create(label2,CC_CALLBACK_1(BillBoardTest::menuCallback_orientedPlane,this) );
    menuItem1->setPosition( Vec2( s.width-80, VisibleRect::top().y-100) );
    menuItem2->setPosition( Vec2( s.width-80, VisibleRect::top().y-130) );
    
    menu = Menu::create(menuItem1, menuItem2, nullptr);
    menu->setPosition(Vec2(0,0));
    this->addChild(menu, 10);
    menuCallback_orientedPoint(nullptr);
}

void BillBoardTest::menuCallback_orientedPoint(Ref* sender)
{
    for (auto& billboard : _billboards) {
        billboard->setMode(BillBoard::Mode::VIEW_POINT_ORIENTED);
    }
}

void BillBoardTest::menuCallback_orientedPlane(Ref* sender)
{
    for (auto& billboard : _billboards) {
        billboard->setMode(BillBoard::Mode::VIEW_PLANE_ORIENTED);
    }
}

BillBoardTest::~BillBoardTest()
{
    if (_camera)
    {
        _camera = nullptr;
    }
}
std::string BillBoardTest::title() const
{
    return "Testing BillBoard";
}
std::string BillBoardTest::subtitle() const
{
    return "";
}
void BillBoardTest::addNewBillBoradWithCoords(Vec3 p)
{
    std::string imgs[3] = {"Images/Icon.png", "Images/r2.png"};
    for (unsigned int i = 0; i < 10; ++i)
    {
        auto billborad = BillBoard::create(imgs[(unsigned int)(CCRANDOM_0_1() * 1 + 0.5)]);
        billborad->setScale(0.5f);
        billborad->setPosition3D(Vec3(p.x, p.y,  -150.0f + 30 * i));
        billborad->setBlendFunc(cocos2d::BlendFunc::ALPHA_NON_PREMULTIPLIED);
        billborad->setOpacity(CCRANDOM_0_1() * 128 + 128);
        _layerBillBorad->addChild(billborad);
        _billboards.push_back(billborad);
    }
}
void BillBoardTest::addNewAniBillBoradWithCoords(Vec3 p)
{
    for (unsigned int i = 0; i < 10; ++i)
    {
        auto billboradAni = BillBoard::create("Images/grossini.png");
        billboradAni->setScale(0.5f);
        billboradAni->setPosition3D(Vec3(p.x, p.y,  -150.0f + 30 * i));
        _layerBillBorad->addChild(billboradAni);

        auto animation = Animation::create();
        for( int i=1;i<15;i++)
        {
            char szName1[100] = {0};
            sprintf(szName1, "Images/grossini_dance_%02d.png", i);
            animation->addSpriteFrameWithFile(szName1);
        }
        // should last 2.8 seconds. And there are 14 frames.
        animation->setDelayPerUnit(2.8f / 14.0f);
        animation->setRestoreOriginalFrame(true);

        auto action = Animate::create(animation);
        billboradAni->runAction(RepeatForever::create(action));
        billboradAni->setBlendFunc(cocos2d::BlendFunc::ALPHA_NON_PREMULTIPLIED);
        billboradAni->setOpacity(CCRANDOM_0_1() * 128 + 128);
        _billboards.push_back(billboradAni);
    }
}
void BillBoardTest::update(float dt)
{

}
void BillBoardTest::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
    if(touches.size()==1)
    {
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
        cameraPos+=cameraDir*newPos.y*0.5;
        cameraPos+=cameraRightDir*newPos.x*0.5;
        _camera->setPosition3D(cameraPos);      
    }
}
void BillBoardTest::rotateCameraCallback(Ref* sender,float value)
{
    Vec3  rotation3D= _camera->getRotation3D();
    rotation3D.y+= value;
    _camera->setRotation3D(rotation3D);
}

void BillBoardTestScene::runThisTest()
{
    auto layer = nextSpriteTestAction();
    addChild(layer);
    Director::getInstance()->replaceScene(this);
}
