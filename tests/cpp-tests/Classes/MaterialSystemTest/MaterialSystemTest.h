/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.

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

#pragma once

#include "../BaseTest.h"

DEFINE_TEST_SUITE(MaterialSystemTest);

class MaterialSystemBaseTest : public TestCase
{
public:
    virtual std::string title() const override;
};

class Material_Sprite3DTest : public MaterialSystemBaseTest
{
public:
    CREATE_FUNC(Material_Sprite3DTest);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class Material_MultipleSprite3D : public MaterialSystemBaseTest
{
public:
    CREATE_FUNC(Material_MultipleSprite3D);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class Material_2DEffects : public MaterialSystemBaseTest
{
public:
    CREATE_FUNC(Material_2DEffects);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class EffectAutoBindingResolver;
class Material_AutoBindings : public MaterialSystemBaseTest
{
public:
    CREATE_FUNC(Material_AutoBindings);

    Material_AutoBindings();
    virtual ~Material_AutoBindings();

    virtual void onEnter() override;
    virtual std::string subtitle() const override;

private:
    EffectAutoBindingResolver *_resolver;
};

class Material_setTechnique : public MaterialSystemBaseTest
{
public:
    CREATE_FUNC(Material_setTechnique);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;

private:
    void changeMaterial(float dt);

    cocos2d::Sprite3D* _sprite;
    int _techniqueState;
};

class Material_clone : public MaterialSystemBaseTest
{
public:
    CREATE_FUNC(Material_clone);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
};

class Material_parsePerformance : public MaterialSystemBaseTest
{
public:
    CREATE_FUNC(Material_parsePerformance);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;
    void parsingTesting(unsigned int count);
protected:
    unsigned int _maxParsingCoumt;
};

class Material_invalidate : public MaterialSystemBaseTest
{
public:
    CREATE_FUNC(Material_invalidate);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;

    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

    cocos2d::CustomCommand _customCommand;
};

class Material_renderState : public MaterialSystemBaseTest
{
public:
    CREATE_FUNC(Material_renderState);

    virtual void onEnter() override;
    virtual std::string subtitle() const override;

    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

    cocos2d::RenderState::StateBlock _stateBlock;
    cocos2d::CustomCommand _customCommand;
};


