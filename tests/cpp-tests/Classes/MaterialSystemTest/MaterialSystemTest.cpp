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
    ADD_TEST_CASE(Material_SpriteSinglePassTest);
    ADD_TEST_CASE(Material_SpriteMultiplePassTest);
}

// MARK:

std::string MaterialSystemBaseTest::title() const
{
    return "Material System";
}

// MARK: Tests start here

void Material_SpriteSinglePassTest::onEnter()
{
    MaterialSystemBaseTest::onEnter();

    auto sprite = Sprite::create("Images/grossini.png");
    sprite->setNormalizedPosition(Vec2(0.5, 0.5));
    this->addChild(sprite);

    auto material = Material::createWithFilename("Materials/basic.material");
    (void)material;
    sprite->setMaterial(material);
}

std::string Material_SpriteSinglePassTest::subtitle() const
{
    return "Sprites with single Pass";
}


void Material_SpriteMultiplePassTest::onEnter()
{
    MaterialSystemBaseTest::onEnter();

    auto sprite = Sprite::create("Images/grossini.png");
    sprite->setNormalizedPosition(Vec2(0.5, 0.5));
    this->addChild(sprite);
}

std::string Material_SpriteMultiplePassTest::subtitle() const
{
    return "Sprites with single Pass";
}
