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

#include "Particle3DTest.h"
#include "Particle3D/CCParticleSystem3D.h"
#include "Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

static int sceneIdx = -1;
#define PARTICLE_SYSTEM_TAG 0x0001

static std::function<Layer*()> createFunctions[] =
{
    CL(Particle3DLineStreakDemo),
    CL(Particle3DBlackHoleDemo),
    CL(Particle3DHypnoDemo),
    CL(Particle3DAdvancedLodSystemDemo),
    CL(Particle3DTimeShiftDemo),
    CL(Particle3DUVAnimDemo),
    CL(Particle3DFirePlaceDemo),
    CL(Particle3DElectricBeamSystemDemo),
    CL(Particle3DExplosionBlueDemo),
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

void Particle3DTestScene::runThisTest()
{
    auto layer = nextSpriteTestAction();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
}

void Particle3DTestDemo::restartCallback( Ref* sender )
{
    auto s = new (std::nothrow) Particle3DTestScene();
    s->addChild(restartSpriteTestAction());

    Director::getInstance()->replaceScene(s);
    s->release();
}

void Particle3DTestDemo::nextCallback( Ref* sender )
{
    auto s = new (std::nothrow) Particle3DTestScene();
    s->addChild( nextSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void Particle3DTestDemo::backCallback( Ref* sender )
{
    auto s = new (std::nothrow) Particle3DTestScene();
    s->addChild( backSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

std::string Particle3DTestDemo::title() const 
{
    return "Particle3D Test";
}

std::string Particle3DTestDemo::subtitle() const 
{
    return "";
}

bool Particle3DTestDemo::init()
{
    if (!BaseTest::init()) return false;

    FileUtils::getInstance()->addSearchPath("Particle3D/materials");
    FileUtils::getInstance()->addSearchPath("Particle3D/scripts");
    //FileUtils::getInstance()->addSearchPath("Particle3D/textures");

    Size size = Director::getInstance()->getWinSize();
    _camera = Camera::createPerspective(30.0f, size.width / size.height, 1.0f, 1000.0f);
    _camera->setPosition3D(Vec3(0.0f, 0.0f, 100.0f));
    _camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
    _camera->setCameraFlag(CameraFlag::USER1);
    this->addChild(_camera);

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(Particle3DTestDemo::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(Particle3DTestDemo::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Particle3DTestDemo::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    TTFConfig config("fonts/tahoma.ttf",10);
    _particleLab = Label::createWithTTF(config,"Particle Count: 0",TextHAlignment::LEFT);
    _particleLab->retain();
    _particleLab->setPosition(Vec2(0.0f, size.height / 6.0f));
    _particleLab->setAnchorPoint(Vec2(0.0f, 0.0f));
    this->addChild(_particleLab);
    
    scheduleUpdate();
    return true;
}

void Particle3DTestDemo::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    
}

void Particle3DTestDemo::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    if (touches.size())
    {
        auto touch = touches[0];
        auto delta = touch->getDelta();
        
        _angle -= CC_DEGREES_TO_RADIANS(delta.x);
        _camera->setPosition3D(Vec3(100.0f * sinf(_angle), 0.0f, 100.0f * cosf(_angle)));
        _camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
    }
}

void Particle3DTestDemo::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    
}

Particle3DTestDemo::Particle3DTestDemo( void )
: _angle(0.0f)
{

}

void Particle3DTestDemo::update( float delta )
{
    ParticleSystem3D *ps = static_cast<ParticleSystem3D *>(this->getChildByTag(PARTICLE_SYSTEM_TAG));
    if (ps){
        unsigned int count = 0;
        auto children = ps->getChildren();
        for (auto iter : children){
            ParticleSystem3D *child = dynamic_cast<ParticleSystem3D *>(iter);
            if (child){
                count += child->getParticlePool().getActiveParticleList().size();
            }
        }

        char str[128];
        sprintf(str, "Particle Count: %d", count);
        _particleLab->setString(str);
    }
}

Particle3DTestDemo::~Particle3DTestDemo( void )
{
    _particleLab->release();
}

std::string Particle3DAdvancedLodSystemDemo::subtitle() const 
{
    return "AdvancedSystem";
}

bool Particle3DAdvancedLodSystemDemo::init()
{
    if (!Particle3DTestDemo::init()) 
        return false;

    auto rootps = PUParticleSystem3D::create("advancedLodSystem.pu");
    rootps->setCameraMask((unsigned short)CameraFlag::USER1);

    auto scale = ScaleBy::create(1.0f, 2.0f, 2.0f, 2.0f);
    auto rotate = RotateBy::create(1.0f, Vec3(0.0f, 0.0f, 100.0f));
    rootps->runAction(RepeatForever::create(Sequence::create(rotate, nullptr)));
    rootps->runAction(RepeatForever::create(Sequence::create(scale, scale->reverse(), nullptr)));
    rootps->startParticleSystem();


    this->addChild(rootps, 0, PARTICLE_SYSTEM_TAG);

    return true;
}

std::string Particle3DBlackHoleDemo::subtitle() const 
{
    return "BlackHole";
}

bool Particle3DBlackHoleDemo::init()
{
    if (!Particle3DTestDemo::init()) 
        return false;

    auto rootps = PUParticleSystem3D::create("blackHole.pu", "pu_mediapack_01.material");
    rootps->setCameraMask((unsigned short)CameraFlag::USER1);
    rootps->setPosition(-25.0f, 0.0f);
    auto moveby = MoveBy::create(2.0f, Vec2(50.0f, 0.0f));
    auto moveby1 = MoveBy::create(2.0f, Vec2(-50.0f, 0.0f));
//    auto scale = ScaleBy::create(1.0f, 2.0f, 2.0f, 2.0f);
//    auto rotate = RotateBy::create(1.0f, Vec3(100.0f, 100.0f, 100.0f));
    rootps->runAction(RepeatForever::create(Sequence::create(moveby, moveby1, nullptr)));
    //rootps->runAction(RepeatForever::create(Sequence::create(scale, scale->reverse(), nullptr)));
    //rootps->runAction(RepeatForever::create(Sequence::create(rotate, nullptr)));
    rootps->startParticleSystem();

    this->addChild(rootps, 0, PARTICLE_SYSTEM_TAG);

    return true;
}

std::string Particle3DHypnoDemo::subtitle() const 
{
    return "Hypno";
}

bool Particle3DHypnoDemo::init()
{
    if (!Particle3DTestDemo::init()) 
        return false;

    auto rootps = PUParticleSystem3D::create("hypno.pu", "pu_mediapack_01.material");
    rootps->setCameraMask((unsigned short)CameraFlag::USER1);
//    auto scale = ScaleBy::create(1.0f, 2.0f, 2.0f, 2.0f);
//    auto rotate = RotateBy::create(1.0f, Vec3(0.0, 100.0f, 0.0f));
    //rootps->runAction(RepeatForever::create(Sequence::create(scale, scale->reverse(), nullptr)));
    //rootps->runAction(RepeatForever::create(Sequence::create(rotate, nullptr)));
    rootps->startParticleSystem();

    this->addChild(rootps, 0, PARTICLE_SYSTEM_TAG);

    return true;
}

std::string Particle3DTimeShiftDemo::subtitle() const 
{
    return "TimeShift";
}

bool Particle3DTimeShiftDemo::init()
{
    if (!Particle3DTestDemo::init()) 
        return false;

    auto rootps = PUParticleSystem3D::create("timeShift.pu", "pu_mediapack_01.material");
    rootps->setScale(2.0f);
    rootps->setCameraMask((unsigned short)CameraFlag::USER1);
    rootps->startParticleSystem();

    this->addChild(rootps, 0, PARTICLE_SYSTEM_TAG);

    return true;
}

std::string Particle3DUVAnimDemo::subtitle() const 
{
    return "UVAnim";
}

bool Particle3DUVAnimDemo::init()
{
    if (!Particle3DTestDemo::init()) 
        return false;

    auto rootps = PUParticleSystem3D::create("UVAnimation.pu", "pu_mediapack_01.material");
    rootps->setCameraMask((unsigned short)CameraFlag::USER1);
    rootps->startParticleSystem();

    this->addChild(rootps, 0, PARTICLE_SYSTEM_TAG);

    return true;
}

std::string Particle3DFirePlaceDemo::subtitle() const 
{
    return "Fire";
}

bool Particle3DFirePlaceDemo::init()
{
    if (!Particle3DTestDemo::init()) 
        return false;

    auto rootps = PUParticleSystem3D::create("mp_torch.pu", "pu_mediapack_01.material");
    rootps->setCameraMask((unsigned short)CameraFlag::USER1);
    rootps->setScale(5.0f);
    rootps->startParticleSystem();

    this->addChild(rootps, 0, PARTICLE_SYSTEM_TAG);

    return true;
}

std::string Particle3DLineStreakDemo::subtitle() const 
{
    return "LineStreak";
}

bool Particle3DLineStreakDemo::init()
{
    if (!Particle3DTestDemo::init()) 
        return false;


    auto rootps = PUParticleSystem3D::create("lineStreak.pu", "pu_mediapack_01.material");
    rootps->setCameraMask((unsigned short)CameraFlag::USER1);
    rootps->setScale(5.0f);
    //rootps->runAction(RepeatForever::create(Sequence::create(rotate, nullptr)));
    rootps->startParticleSystem();
    this->addChild(rootps, 0, PARTICLE_SYSTEM_TAG);

    //auto sprite = Sprite::create("pump_streak_04.png");
    //sprite->setCameraMask((unsigned short)CameraFlag::USER1);
    //sprite->setScale(0.5f);
    //this->addChild(sprite);

    return true;
}

std::string Particle3DElectricBeamSystemDemo::subtitle() const 
{
    return "ElectricBeamSystem";
}

bool Particle3DElectricBeamSystemDemo::init()
{
    if (!Particle3DTestDemo::init()) 
        return false;


    auto rootps = PUParticleSystem3D::create("electricBeamSystem.pu");
    rootps->setCameraMask((unsigned short)CameraFlag::USER1);
    rootps->startParticleSystem();
    this->addChild(rootps, 0, PARTICLE_SYSTEM_TAG);

    return true;
}

std::string Particle3DExplosionBlueDemo::subtitle() const 
{
    return "ExplosionBlue";
}

bool Particle3DExplosionBlueDemo::init()
{
    if (!Particle3DTestDemo::init()) 
        return false;


    auto rootps = PUParticleSystem3D::create("mp_explosion_04_blue.pu");
    rootps->setCameraMask((unsigned short)CameraFlag::USER1);
    rootps->setScale(0.25f);
    rootps->startParticleSystem();
    this->addChild(rootps, 0, PARTICLE_SYSTEM_TAG);

    return true;
}
