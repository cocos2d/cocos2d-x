/****************************************************************************
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

#ifndef _SHADER_TEST2_H_
#define _SHADER_TEST2_H_

#include "extensions/cocos-ext.h"
#include "../BaseTest.h"


DEFINE_TEST_SUITE(Shader2Tests);

class ShaderTestDemo2 : public TestCase
{
public:
    virtual std::string title() const override { return "Effects on Sprites";}
};

//
// Effect
//
class EffectSprite;

class Effect : public cocos2d::Ref
{
public:
    cocos2d::backend::ProgramState* getProgramState() const { return _programState; }
    virtual void setTarget(EffectSprite *sprite){}

protected:
    bool initProgramState(const std::string &fragmentFilename);
    Effect();
    virtual ~Effect();
    cocos2d::backend::ProgramState* _programState = nullptr;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string _fragSource;
    cocos2d::EventListenerCustom* _backgroundListener;
#endif
};

class EffectSpriteTest : public ShaderTestDemo2
{
public:
    CREATE_FUNC(EffectSpriteTest);
    EffectSpriteTest();
    virtual bool init();
    virtual std::string subtitle() const {return "Different effects on Sprite";}

protected:
    ssize_t _vectorIndex;
    cocos2d::Vector<Effect*> _effects;
    EffectSprite *_sprite;
};

class EffectSpriteLamp : public ShaderTestDemo2
{
public:
    CREATE_FUNC(EffectSpriteLamp);
    EffectSpriteLamp();
    virtual bool init();
    virtual std::string subtitle() const {return "Sprite Lamp effects";}
    //callback
public:
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* unused_event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* unused_event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* unused_event);
protected:
    EffectSprite *_sprite;
    Effect* _effect;
    cocos2d::Sprite* _lightSprite;
};

#endif
