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
#include "renderer/CCProperties.h"


USING_NS_CC;

MaterialSystemTest::MaterialSystemTest()
{
    ADD_TEST_CASE(Material_NewMaterialFormat);
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

//
//
//
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

void Material_NewMaterialFormat::onEnter()
{
    MaterialSystemBaseTest::onEnter();

//    auto properties = Properties::create("Materials/light.material");
//    auto properties = Properties::create("Materials/sample.material");
//    auto properties = Properties::create("Materials/shapes.material#box");
    auto properties = Properties::create("Materials/effects2.material#sample");

    // Print the properties of every namespace within this one.
    printProperties(properties, 0);

    Material *mat1 = Material::createWithProperties(properties);
    (void)mat1;

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

std::string Material_NewMaterialFormat::subtitle() const
{
    return "Testing new material file format";
}



