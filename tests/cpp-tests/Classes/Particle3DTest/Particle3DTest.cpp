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


void Particle3DTestScene::runThisTest()
{
    auto layer = Particle3DTestDemo::create();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
}

void Particle3DTestDemo::restartCallback( Ref* sender )
{

}

void Particle3DTestDemo::nextCallback( Ref* sender )
{

}

void Particle3DTestDemo::backCallback( Ref* sender )
{

}

std::string Particle3DTestDemo::title() const 
{
    return "Particle3D Test";
}

std::string Particle3DTestDemo::subtitle() const 
{
    return "";
}

void Particle3DTestDemo::onEnter()
{
    BaseTest::onEnter();
}

bool Particle3DTestDemo::init()
{
    if (!BaseTest::init()) return false;

    Size size = Director::getInstance()->getWinSize();
    _camera = Camera::createPerspective(60.0f, size.width / size.height, 1.0f, 1000.0f);
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


    auto sprite3d = Sprite3D::create("Sprite3DTest/orc.c3b");
    sprite3d->setRotation3D(Vec3(0.0f, 180.0f, 0.0f));
    sprite3d->setScale(1.0f);
    sprite3d->setCameraMask((unsigned short)CameraFlag::USER1);

    auto animation = Animation3D::create("Sprite3DTest/orc.c3b");
    if (animation)
    {
        auto animate = Animate3D::create(animation);
        sprite3d->runAction(RepeatForever::create(animate));
    }

    this->addChild(sprite3d);

    auto ps = createParticleSystem();
    ps->setPosition(-25.0f, -25.0f);
    auto moveby = MoveBy::create(2.0f, Vec2(50.0f, 50.0f));
    auto moveby1 = MoveBy::create(2.0f, Vec2(-50.0f, 0.0f));
    auto moveby2 = MoveBy::create(2.0f, Vec2(50.0f, -50.0f));
    auto moveby3 = MoveBy::create(2.0f, Vec2(-50.0f, 0.0f));
    ps->runAction(RepeatForever::create(Sequence::create(moveby, moveby1, moveby2, moveby3, nullptr)));
    this->addChild(ps);
    //sprite3d->getAttachNode("Bip001 R Hand")->addChild(ps);

    return true;
}

ParticleSystem3D* Particle3DTestDemo::createParticleSystem()
{
    auto ps = PUParticleSystem3D::create();
    ps->setBlendFunc(BlendFunc::ADDITIVE);
    ps->setParticleQuota(2500);
    ps->setKeepLocal(false);
    //emitter
    {
        auto ppe = PUParticle3DSphereSurfaceEmitter::create();
        ppe->setParticleDirection(Vec3(0.0f, 1.0f, 0.0f));
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
        ppe->setParticleColorRangeStart(Vec4(0.0f, 0.0f, 0.0f, 1.0f));
        ppe->setParticleColorRangeEnd(Vec4(1.0f, 1.0f, 1.0f, 1.0f));
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

        auto psa = PUParticle3DScaleAffector::create();
        PUDynamicAttributeFixed *scl = new PUDynamicAttributeFixed();
        scl->setValue(-4.5f);
        psa->setDynScaleXYZ(scl);
        ps->addAffector(psa);

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
        auto pr = Particle3DQuadRender::create("Images/Comet.png");
        ps->setRender(pr);
    }


    //auto pr = Particle3DModelRender::create(Sprite3D::create("Sprite3DTest/axe.c3b"));
    //ps->setRender(pr);

    ps->startParticle();
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
