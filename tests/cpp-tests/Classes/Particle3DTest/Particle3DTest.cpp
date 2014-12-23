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
#include "3dparticle/CCParticle3DEmitter.h"
#include "3dparticle/CCParticle3DAffector.h"
#include "3dparticle/CCParticle3DRender.h"
#include "3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DPointEmitter.h"
#include "3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DBoxEmitter.h"
#include "3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DCircleEmitter.h"
#include "3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DLineEmitter.h"
#include "3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DPositionEmitter.h"
#include "3dparticle/ParticleUniverse/ParticleEmitters/CCPUParticle3DSphereSurfaceEmitter.h"
#include "3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DAlignAffector.h"
#include "3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DBoxCollider.h"
#include "3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DColorAffector.h"
#include "3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DGravityAffector.h"
#include "3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DScaleAffector.h"
#include "3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DFlockCenteringAffector.h"
#include "3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DForceFieldAffector.h"
#include "3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DLinearForceAffector.h"
#include "3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DParticleFollower.h"
#include "3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DPathFollower.h"
#include "3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DPlaneCollider.h"
#include "3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DRandomiser.h"
#include "3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DSineForceAffector.h"
#include "3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DTextureRotator.h"
#include "3dparticle/ParticleUniverse/ParticleAffectors/CCPUParticle3DVortexAffector.h"
#include "3dparticle/ParticleUniverse/CCPUParticleSystem3D.h"
#include "3dparticle/ParticleUniverse/CCPUParticle3DScriptCompiler.h"

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

static int sceneIdx = -1;


static std::function<Layer*()> createFunctions[] =
{
    CL(Particle3DAdvancedLodSystemDemo),
    CL(Particle3DBlackHoleDemo),
    CL(Particle3DHypnoDemo),
    CL(Particle3DTimeShiftDemo),
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
    FileUtils::getInstance()->addSearchPath("Particle3D/textures");

    Size size = Director::getInstance()->getWinSize();
    _camera = Camera::createPerspective(30.0f, size.width / size.height, 1.0f, 1000.0f);
    _camera->setPosition3D(Vec3(0.0f, 0.0f, 100.0f));
    _camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
    _camera->setCameraFlag(CameraFlag::USER1);
    this->addChild(_camera);

    auto label1 = Label::createWithTTF("Rotate Left", "fonts/arial.ttf", 20);
    auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(Particle3DTestDemo::rotateCameraLeft, this));
    auto label2 = Label::createWithTTF("Rotate Right", "fonts/arial.ttf", 20);
    auto menuItem2 = MenuItemLabel::create(label2, CC_CALLBACK_1(Particle3DTestDemo::rotateCameraRight, this));
    auto menu = Menu::create(menuItem1, menuItem2, nullptr);
    menu->setPosition(Vec2::ZERO);
    menuItem1->setAnchorPoint(Vec2(0.0f, 0.0f));
    menuItem2->setAnchorPoint(Vec2(0.0f, 0.0f));
    menuItem1->setPosition(0, size.height -50);
    menuItem2->setPosition(0, size.height -100);
    this->addChild(menu);

    return true;
}

ParticleSystem3D* Particle3DTestDemo::createParticleSystem()
{
    auto ps = PUParticleSystem3D::create();
    BlendFunc blend;
    blend.src = GL_ONE;
    blend.dst = GL_ONE;
    ps->setBlendFunc(blend);
    ps->setParticleQuota(2500);
    ps->setKeepLocal(false);
    //emitter
    {
        auto ppe = PUParticle3DSphereSurfaceEmitter::create();
        ppe->setRadius(12.0f);

        //PUDynamicAttributeFixed *angle = new PUDynamicAttributeFixed();
        //angle->setValue(0.0f);
        //ppe->setDynAngle(angle);
        PUDynamicAttributeFixed *velocity = new PUDynamicAttributeFixed();
        velocity->setValue(3.0f);
        ppe->setDynVelocity(velocity);
        PUDynamicAttributeFixed *alive = new PUDynamicAttributeFixed();
        alive->setValue(3.0f);
        ppe->setDynTotalTimeToLive(alive);
        PUDynamicAttributeFixed *dim = new PUDynamicAttributeFixed();
        dim->setValue(12.0f);
        ppe->setDynParticleAllDimensions(dim);
        PUDynamicAttributeFixed *rate = new PUDynamicAttributeFixed();
        rate->setValue(200.0f);
        ppe->setDynEmissionRate(rate);
        //ppe->setParticleColorRangeStart(Vec4(0.0f, 0.0f, 0.0f, 1.0f));
        //ppe->setParticleColorRangeEnd(Vec4(1.0f, 1.0f, 1.0f, 1.0f));
        ps->setEmitter(ppe);
    }

    //affector
    {
        auto pca = PUParticle3DColorAffector::create();
        pca->addColor(0.0f, Vec4(0.0f, 0.0f, 0.2f, 1.0f));
        pca->addColor(0.9f, Vec4(0.8f, 0.8f, 1.0f, 1.0f));
        pca->addColor(1.0f, Vec4(1.0f, 1.0f, 1.0f, 1.0f));
        ps->addAffector(pca);

        auto pga = PUParticle3DGravityAffector::create();
        pga->setGravity(2700);
        ps->addAffector(pga);

//        auto psa = PUParticle3DScaleAffector::create();
        PUDynamicAttributeFixed *scl = new PUDynamicAttributeFixed();
        scl->setValue(-4.5f);
        //psa->setDynScaleXYZ(scl);
        //ps->addAffector(psa);

  //      auto pfca = PUParticle3DFlockCenteringAffector::create();
  //      ps->addAffector(pfca);

        //auto pffa = PUParticle3DForceFieldAffector::create();
        //ps->addAffector(pffa);

        //auto plfa = PUParticle3DLinearForceAffector::create();
        //plfa->setForceVector(Vec3(0.0f, 10.0f, 0.0f));
        //ps->addAffector(plfa);

        //auto ppf = PUParticle3DParticleFollower::create();
        //ps->addAffector(ppf);

        //auto pptf = PUParticle3DPathFollower::create();
        //pptf->addPoint(Vec3(0.0f, 0.0f, 0.0f));
        //pptf->addPoint(Vec3(50.0f, 50.0f, -50.0f));
        //pptf->addPoint(Vec3(0.0f, 50.0f, -50.0f));
        //pptf->addPoint(Vec3(50.0f, 0.0f, 0.0f));
        //pptf->addPoint(Vec3(0.0f, 0.0f, 0.0f));
        //ps->addAffector(pptf);

        //auto ppc = PUParticle3DPlaneCollider::create();
        //ppc->setNormal(Vec3(0.0f, 1.0f, 0.0f));
        //ps->addAffector(ppc);

        //auto pr = PUParticle3DRandomiser::create();
        //ps->addAffector(pr);

        //auto psfa = PUParticle3DSineForceAffector::create();
        //psfa->setForceVector(Vec3(0.0f, 10.0f, 0.0f));
        //psfa->setFrequencyMax(10.0f);
        //ps->addAffector(psfa);

        //auto ptr = PUParticle3DTextureRotator::create();
        //PUDynamicAttributeFixed *rSpeed = new PUDynamicAttributeFixed();
        //rSpeed->setValue(2.0f);
        //ptr->setRotationSpeed(rSpeed);
        //ps->addAffector(ptr);

        //auto pva = PUParticle3DVortexAffector::create();
        //PUDynamicAttributeFixed *rSpeed = new PUDynamicAttributeFixed();
        //rSpeed->setValue(10.0f);
        //pva->setRotationSpeed(rSpeed);
        //pva->setRotationVector(Vec3(0.0f, 1.0f, 0.0f));
        //ps->addAffector(pva);
    }

    //render
    {
        auto pr = Particle3DQuadRender::create("pump_flare_04.png");
        ps->setRender(pr);
    }


    //auto pr = Particle3DModelRender::create(Sprite3D::create("Sprite3DTest/axe.c3b"));
    //ps->setRender(pr);

    //ps->startParticle();
    //this->addChild(ps);

    ps->setCameraMask((unsigned short)CameraFlag::USER1);
    return ps;
}

void Particle3DTestDemo::rotateCameraLeft( cocos2d::Ref *sender )
{
    _angle -= 0.1f;
    _camera->setPosition3D(Vec3(100.0f * sinf(_angle), 0.0f, 100.0f * cosf(_angle)));
    _camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
}

void Particle3DTestDemo::rotateCameraRight( cocos2d::Ref *sender )
{
    _angle += 0.1f;
    _camera->setPosition3D(Vec3(100.0f * sinf(_angle), 0.0f, 100.0f * cosf(_angle)));
    _camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
}

Particle3DTestDemo::Particle3DTestDemo( void )
    : _angle(0.0f)
{

}

std::string Particle3DAdvancedLodSystemDemo::subtitle() const 
{
    return "AdvancedSystem";
}

bool Particle3DAdvancedLodSystemDemo::init()
{
    if (!Particle3DTestDemo::init()) 
        return false;

    auto rootps = PUParticleSystem3D::create("advancedLodSystem.pu", "pu_mediapack_01.material");
    rootps->setCameraMask((unsigned short)CameraFlag::USER1);

    auto scale = ScaleBy::create(1.0f, 2.0f, 2.0f, 2.0f);
    auto rotate = RotateBy::create(1.0f, Vec3(0.0f, 0.0f, 100.0f));
    rootps->runAction(RepeatForever::create(Sequence::create(rotate, nullptr)));
    rootps->runAction(RepeatForever::create(Sequence::create(scale, scale->reverse(), nullptr)));
    rootps->startParticle();


    this->addChild(rootps);

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
    auto scale = ScaleBy::create(1.0f, 2.0f, 2.0f, 2.0f);
    auto rotate = RotateBy::create(1.0f, Vec3(100.0f, 100.0f, 100.0f));
    rootps->runAction(RepeatForever::create(Sequence::create(moveby, moveby1, nullptr)));
    rootps->runAction(RepeatForever::create(Sequence::create(scale, scale->reverse(), nullptr)));
    rootps->runAction(RepeatForever::create(Sequence::create(rotate, nullptr)));
    rootps->startParticle();

    this->addChild(rootps);

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
    auto scale = ScaleBy::create(1.0f, 2.0f, 2.0f, 2.0f);
    auto rotate = RotateBy::create(1.0f, Vec3(0.0, 100.0f, 0.0f));
    rootps->runAction(RepeatForever::create(Sequence::create(scale, scale->reverse(), nullptr)));
    rootps->runAction(RepeatForever::create(Sequence::create(rotate, nullptr)));
    rootps->startParticle();

    this->addChild(rootps);

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
    rootps->setCameraMask((unsigned short)CameraFlag::USER1);
    rootps->startParticle();

    this->addChild(rootps);

    return true;
}