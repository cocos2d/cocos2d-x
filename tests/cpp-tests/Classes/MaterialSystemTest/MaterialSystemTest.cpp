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


USING_NS_CC;

// MARK: Helper functions

static void printProperties(Properties* properties, int indent)
{
    // Print the name and ID of the current namespace.
    const char* spacename = properties->getNamespace();
    const char* id = properties->getId();
    char chindent[64];
    int i=0;
    for(i=0; i<indent*2;i++)
        chindent[i] = ' ';
    chindent[i] = '\0';

    CCLOG("%sNamespace: %s  ID: %s\n%s{", chindent, spacename, id, chindent);

    // Print all properties in this namespace.
    const char* name = properties->getNextProperty();
    const char* value = NULL;
    while (name != NULL)
    {
        value = properties->getString(name);
        CCLOG("%s%s = %s", chindent, name, value);
        name = properties->getNextProperty();
    }

    Properties* space = properties->getNextNamespace();
    while (space != NULL)
    {
        printProperties(space, indent+1);
        space = properties->getNextNamespace();
    }

    CCLOG("%s}\n",chindent);
}

// MARK: Tests

MaterialSystemTest::MaterialSystemTest()
{
    ADD_TEST_CASE(Material_2DEffects);
    ADD_TEST_CASE(Material_3DEffects);
    ADD_TEST_CASE(Material_MultipleSprite3D);
    ADD_TEST_CASE(Material_Sprite3DTest);
}

std::string MaterialSystemBaseTest::title() const
{
    return "Material System";
}

// MARK: Tests start here

void Material_Sprite3DTest::onEnter()
{
    MaterialSystemBaseTest::onEnter();

    auto sprite = Sprite3D::create("Sprite3DTest/boss1.obj");
    sprite->setScale(8.f);
    sprite->setTexture("Sprite3DTest/boss.png");
    this->addChild(sprite);
    sprite->setNormalizedPosition(Vec2(0.5,0.5));
}

std::string Material_Sprite3DTest::subtitle() const
{
    return "Material System on Sprite3D";
}

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

//
//
//
void Material_2DEffects::onEnter()
{
    MaterialSystemBaseTest::onEnter();

    auto properties = Properties::create("Materials/2d_effects.material#sample");

    // Print the properties of every namespace within this one.
    printProperties(properties, 0);

    Material *mat1 = Material::createWithProperties(properties);

    auto spriteBlur = Sprite::create("Images/grossini.png");
    spriteBlur->setNormalizedPosition(Vec2(0.2, 0.5));
    this->addChild(spriteBlur);
    spriteBlur->setGLProgramState(mat1->getTechniqueByName("blur")->getPassByIndex(0)->getGLProgramState());

    auto spriteOutline = Sprite::create("Images/grossini.png");
    spriteOutline->setNormalizedPosition(Vec2(0.4, 0.5));
    this->addChild(spriteOutline);
    spriteOutline->setGLProgramState(mat1->getTechniqueByName("outline")->getPassByIndex(0)->getGLProgramState());

    auto spriteNoise = Sprite::create("Images/grossini.png");
    spriteNoise->setNormalizedPosition(Vec2(0.6, 0.5));
    this->addChild(spriteNoise);
    spriteNoise->setGLProgramState(mat1->getTechniqueByName("noise")->getPassByIndex(0)->getGLProgramState());

    auto spriteEdgeDetect = Sprite::create("Images/grossini.png");
    spriteEdgeDetect->setNormalizedPosition(Vec2(0.8, 0.5));
    this->addChild(spriteEdgeDetect);
    spriteEdgeDetect->setGLProgramState(mat1->getTechniqueByName("edge_detect")->getPassByIndex(0)->getGLProgramState());
}

std::string Material_2DEffects::subtitle() const
{
    return "Testing effects on Sprite";
}

//
//
//
void Material_3DEffects::onEnter()
{
    MaterialSystemBaseTest::onEnter();

    auto sprite = Sprite3D::create("Sprite3DTest/boss1.obj");
    sprite->setScale(8.f);
//    sprite->setTexture("Sprite3DTest/boss.png");
    this->addChild(sprite);
    sprite->setNormalizedPosition(Vec2(0.5,0.5));
    _sprite = sprite;

    auto rot = RotateBy::create(5, Vec3(30,60,270));
    auto repeat = RepeatForever::create(rot);
    sprite->runAction(repeat);

    Material *mat = Material::createWithFilename("Materials/3d_effects.material");
    mat->setTechnique("lit");
    sprite->setMaterial(mat);

    // lights
    auto light1 = AmbientLight::create(Color3B::RED);
    addChild(light1);

    auto light2 = DirectionLight::create(Vec3(-1,1,0), Color3B::GREEN);
    addChild(light2);

    this->schedule(CC_CALLBACK_1(Material_3DEffects::changeMaterial, this),  3, "cookie");

    _techniqueState = 0;
}

std::string Material_3DEffects::subtitle() const
{
    return "Testing effects on Sprite3D";
}

void Material_3DEffects::changeMaterial(float dt)
{
    // get it from Mesh 0
    switch (_techniqueState)
    {
        case 0:
            _sprite->getMaterial(0)->setTechnique("lit");
            break;
        case 1:
            _sprite->getMaterial(0)->setTechnique("unlit");
            break;
        default:
            break;
    }

    _techniqueState++;
    if (_techniqueState>1)
        _techniqueState = 0;
}

