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

#include "MaterialSystemTest.h"
#include "../testResource.h"
#include "cocos2d.h"

#include "renderer/CCMaterial.h"


USING_NS_CC;

MaterialSystemTest::MaterialSystemTest()
{
    ADD_TEST_CASE(Material_MultipleSprite3D);
    ADD_TEST_CASE(Material_Sprite3DTest);

//    ADD_TEST_CASE(Material_SpriteTest);

}

// MARK:

std::string MaterialSystemBaseTest::title() const
{
    return "Material System";
}

// MARK: Tests start here

void Material_SpriteTest::onEnter()
{
    // Material remove from Sprite since it is hacking.
    // Sprite (or Node) should have "Effect" instead of "Material"
    
    MaterialSystemBaseTest::onEnter();
    auto layer = LayerColor::create(Color4B::BLUE);
    this->addChild(layer);


    auto sprite = Sprite::create("Images/grossini.png");
    sprite->setNormalizedPosition(Vec2(0.5, 0.5));
    this->addChild(sprite);

//    auto material = Material::createWithFilename("Materials/effects.material");
//    sprite->setMaterial(material);

//    material->setTechnique("blur");
//    material->setTechnique("outline");
//    material->setTechnique("noise");
//    material->setTechnique("edge detect");
//    material->setTechnique("gray+blur");
}

std::string Material_SpriteTest::subtitle() const
{
    return "Material System on Sprite";
}


void Material_Sprite3DTest::onEnter()
{
    MaterialSystemBaseTest::onEnter();

    auto sprite = Sprite3D::create("Sprite3DTest/boss1.obj");
    sprite->setScale(8.f);
    sprite->setTexture("Sprite3DTest/boss.png");
    this->addChild(sprite);
    sprite->setNormalizedPosition(Vec2(0.5,0.5));

//    auto material = Material::createWithFilename("Materials/spaceship.material");
//    sprite->setMaterial(material);
}

std::string Material_Sprite3DTest::subtitle() const
{
    return "Material System on Sprite3D";
}


//
//
//
void Material_MultipleSprite3D::onEnter()
{
    MaterialSystemBaseTest::onEnter();

    const char* names[] = {
        "Sprite3DTest/ReskinGirl.c3b",
        "Sprite3DTest/ReskinGirl.c3b",
        "Sprite3DTest/ReskinGirl.c3b",
        "Sprite3DTest/ReskinGirl.c3b",
        "Sprite3DTest/ReskinGirl.c3b",
        "Sprite3DTest/ReskinGirl.c3b",
        "Sprite3DTest/ReskinGirl.c3b",
        "Sprite3DTest/ReskinGirl.c3b",
    };

    const int totalNames = sizeof(names) / sizeof(names[0]);

    auto size = Director::getInstance()->getWinSize();

    for(int i=0;i<totalNames;i++)
    {
        auto sprite = Sprite3D::create(names[i]);
        this->addChild(sprite);
        sprite->setPosition(Vec2((size.width/(totalNames+1))*(i+1), size.height/4));
        sprite->setScale(3);
    }
}

std::string Material_MultipleSprite3D::subtitle() const
{
    return "Sprites with multiple meshes";
}

