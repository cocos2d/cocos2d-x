/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include "renderer/backend/Types.h"
#include "renderer/backend/ProgramState.h"

#include <vector>

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
    void updateCCTimeUniforms(float);
    
private:
    struct Locations {
        Locations(cocos2d::backend::ProgramState *ps, cocos2d::backend::UniformLocation loc)
            : programState(ps), location(loc) {}
           
        cocos2d::backend::ProgramState *programState = nullptr;
        cocos2d::backend::UniformLocation location;
    };
    std::vector<Locations> timeUniforms;
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

    void updateUniformTime(float);

private:
    cocos2d::backend::UniformLocation _locationTime;
    EffectAutoBindingResolver       *_resolver          = nullptr;
    cocos2d::backend::ProgramState  *_noiseProgramState = nullptr;
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



