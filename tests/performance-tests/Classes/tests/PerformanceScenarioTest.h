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

#ifndef __PERFORMANCE_SCENARIO_TEST_H__
#define __PERFORMANCE_SCENARIO_TEST_H__

#include "BaseTest.h"

DEFINE_TEST_SUITE(PerformceScenarioTests);

class ScenarioTest : public TestCase
{
public:
    CREATE_FUNC(ScenarioTest);

    virtual bool init() override;
    virtual std::string title() const override;
    virtual void performTests();

    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) ;

    static cocos2d::Scene* scene();

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void update(float dt) override;
    void beginStat(float dt);
    void endStat(float dt);
    void doAutoTest();
    
private:
    void addNewSprites(int num);
    void removeSprites();

    void addParticles(int num);
    void removeParticles();

    void addParticleSystem(int num);
    void removeParticleSystem();

private:
    static int _initParticleNum;
    static int _parStepNum;
    static int _initSpriteNum;
    static int _spriteStepNum;
    static int _initParsysNum;
    static int _parsysStepNum;

    cocos2d::TMXTiledMap* _map1;
    cocos2d::TMXTiledMap* _map2;

    cocos2d::MenuItemToggle* _itemToggle;
    cocos2d::Vector<cocos2d::Sprite*> _spriteArray;
    cocos2d::Vector<cocos2d::ParticleSystemQuad*> _parsysArray;
    cocos2d::Label* _spriteLabel;
    cocos2d::Label* _particleLabel;
    cocos2d::Label* _parsysLabel;
    int _particleNumber;

    bool       isStating;
    int        autoTestIndex;
    int        statCount;
    float      totalStatTime;
    float      minFrameRate;
    float      maxFrameRate;
};

#endif
