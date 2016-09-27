/****************************************************************************
 Copyright (c) 2016 Chukong Technologies Inc.

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

#include "CreatorTest.h"
#include "../testResource.h"

USING_NS_CC;

static void test()
{
    // New node
    auto scene_0_0 = Scene::create();
    scene_0_0->setAnchorPoint(Vec2(0.0000f, 0.0000f));
    scene_0_0->setColor(Color3B(255, 255, 255));
    scene_0_0->setLocalZOrder(0);
    scene_0_0->setGlobalZOrder(0);
    scene_0_0->setOpacity(255);
    scene_0_0->setOpacityModifyRGB(false);
    scene_0_0->setCascadeOpacityEnabled(true);
    scene_0_0->setTag(-1);
    scene_0_0->setContentSize(Size(0.000000f, 0.000000f));

    // New node
    auto tmxtiledmap_1_1 = TMXTiledMap::create("iso-test.tmx");
    tmxtiledmap_1_1->setAnchorPoint(Vec2(0.5000f, 0.5000f));
    tmxtiledmap_1_1->setScaleY(1);
    tmxtiledmap_1_1->setScaleX(1);
    tmxtiledmap_1_1->setColor(Color3B(255, 255, 255));
    tmxtiledmap_1_1->setName("iso-test");
    tmxtiledmap_1_1->setLocalZOrder(0);
    tmxtiledmap_1_1->setGlobalZOrder(0);
    tmxtiledmap_1_1->setOpacity(255);
    tmxtiledmap_1_1->setOpacityModifyRGB(false);
    tmxtiledmap_1_1->setCascadeOpacityEnabled(true);
    tmxtiledmap_1_1->setSkewX(0);
    tmxtiledmap_1_1->setTag(-1);
    tmxtiledmap_1_1->setContentSize(Size(4096.000000f, 2048.000000f));
    tmxtiledmap_1_1->setSkewY(0);
    tmxtiledmap_1_1->setRotationSkewY(0);
    tmxtiledmap_1_1->setPosition(Vec2(494.0000f, 231.0000f));
    tmxtiledmap_1_1->setRotationSkewX(0);
    scene_0_0->addChild(tmxtiledmap_1_1);

    // New node
    auto particlesystemquad_1_2 = ParticleSystemQuad::create("Galaxy.plist");
    particlesystemquad_1_2->setAnchorPoint(Vec2(0.5000f, 0.5000f));
    particlesystemquad_1_2->setScaleY(1);
    particlesystemquad_1_2->setScaleX(1);
    particlesystemquad_1_2->setColor(Color3B(255, 255, 255));
    particlesystemquad_1_2->setName("Galaxy");
    particlesystemquad_1_2->setLocalZOrder(0);
    particlesystemquad_1_2->setGlobalZOrder(0);
    particlesystemquad_1_2->setOpacity(255);
    particlesystemquad_1_2->setOpacityModifyRGB(false);
    particlesystemquad_1_2->setCascadeOpacityEnabled(true);
    particlesystemquad_1_2->setSkewX(0);
    particlesystemquad_1_2->setTag(-1);
    particlesystemquad_1_2->setContentSize(Size(0.000000f, 0.000000f));
    particlesystemquad_1_2->setSkewY(0);
    particlesystemquad_1_2->setRotationSkewY(0);
    particlesystemquad_1_2->setPosition(Vec2(115.0000f, 251.0000f));
    particlesystemquad_1_2->setRotationSkewX(0);
    scene_0_0->addChild(particlesystemquad_1_2);

    // New node
    auto sprite_1_3 = Sprite::create();
    sprite_1_3->setSpriteFrame("grossini_dance_08");
    sprite_1_3->setAnchorPoint(Vec2(0.5000f, 0.5000f));
    sprite_1_3->setScaleY(1);
    sprite_1_3->setScaleX(1);
    sprite_1_3->setColor(Color3B(255, 255, 255));
    sprite_1_3->setName("New Sprite (Splash)");
    sprite_1_3->setLocalZOrder(0);
    sprite_1_3->setGlobalZOrder(0);
    sprite_1_3->setOpacity(255);
    sprite_1_3->setOpacityModifyRGB(false);
    sprite_1_3->setCascadeOpacityEnabled(true);
    sprite_1_3->setSkewX(0);
    sprite_1_3->setTag(-1);
    sprite_1_3->setContentSize(Size(100.000000f, 100.000000f));
    sprite_1_3->setSkewY(0);
    sprite_1_3->setRotationSkewY(0);
    sprite_1_3->setPosition(Vec2(220.0000f, 422.0000f));
    sprite_1_3->setRotationSkewX(0);
    scene_0_0->addChild(sprite_1_3);

    // New node
    auto sprite_1_4 = Sprite::create();
    sprite_1_4->setSpriteFrame("grossini_dance_08");
    sprite_1_4->setAnchorPoint(Vec2(0.5000f, 0.5000f));
    sprite_1_4->setScaleY(1);
    sprite_1_4->setScaleX(1);
    sprite_1_4->setColor(Color3B(255, 255, 255));
    sprite_1_4->setName("grossini_dance_08");
    sprite_1_4->setLocalZOrder(0);
    sprite_1_4->setGlobalZOrder(0);
    sprite_1_4->setOpacity(255);
    sprite_1_4->setOpacityModifyRGB(false);
    sprite_1_4->setCascadeOpacityEnabled(true);
    sprite_1_4->setSkewX(0);
    sprite_1_4->setTag(-1);
    sprite_1_4->setContentSize(Size(51.000000f, 109.000000f));
    sprite_1_4->setSkewY(0);
    sprite_1_4->setRotationSkewY(0);
    sprite_1_4->setPosition(Vec2(100.0000f, 407.0000f));
    sprite_1_4->setRotationSkewX(0);
    scene_0_0->addChild(sprite_1_4);

    // New node
    auto label_1_5 = Label::create();
    label_1_5->setAnchorPoint(Vec2(0.5000f, 0.5000f));
    label_1_5->setScaleY(1);
    label_1_5->setScaleX(1);
    label_1_5->setColor(Color3B(255, 255, 255));
    label_1_5->setName("Label_1");
    label_1_5->setLocalZOrder(0);
    label_1_5->setGlobalZOrder(0);
    label_1_5->setOpacity(255);
    label_1_5->setOpacityModifyRGB(false);
    label_1_5->setCascadeOpacityEnabled(true);
    label_1_5->setSkewX(0);
    label_1_5->setTag(-1);
    label_1_5->setContentSize(Size(244.550000f, 40.000000f));
    label_1_5->setSkewY(0);
    label_1_5->setRotationSkewY(0);
    label_1_5->setPosition(Vec2(178.0000f, 548.0000f));
    label_1_5->setRotationSkewX(0);
    scene_0_0->addChild(label_1_5);

    // New node
    auto label_1_6 = Label::create();
    label_1_6->setAnchorPoint(Vec2(0.5000f, 0.5000f));
    label_1_6->setScaleY(1);
    label_1_6->setScaleX(1);
    label_1_6->setColor(Color3B(255, 255, 255));
    label_1_6->setName("Label_2");
    label_1_6->setLocalZOrder(0);
    label_1_6->setGlobalZOrder(0);
    label_1_6->setOpacity(255);
    label_1_6->setOpacityModifyRGB(false);
    label_1_6->setCascadeOpacityEnabled(true);
    label_1_6->setSkewX(0);
    label_1_6->setTag(-1);
    label_1_6->setContentSize(Size(357.970000f, 40.000000f));
    label_1_6->setSkewY(0);
    label_1_6->setRotationSkewY(0);
    label_1_6->setPosition(Vec2(545.0000f, 539.0000f));
    label_1_6->setRotationSkewX(0);
    scene_0_0->addChild(label_1_6);
}


