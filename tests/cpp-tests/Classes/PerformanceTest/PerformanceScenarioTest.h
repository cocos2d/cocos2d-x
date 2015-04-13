#ifndef __PERFORMANCE_SCENARIO_TEST_H__
#define __PERFORMANCE_SCENARIO_TEST_H__

#include "PerformanceTest.h"

class ScenarioMenuLayer : public PerformBasicLayer
{
public:
    ScenarioMenuLayer(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0)
        :PerformBasicLayer(bControlMenuVisible, nMaxCases, nCurCase)
    {
    }

    virtual void showCurrentTest() override;

    virtual void onEnter() override;
    virtual std::string title() const;
    virtual std::string subtitle() const;
    virtual void performTests() = 0;
};

class ScenarioTest : public ScenarioMenuLayer
{
public:
    ScenarioTest(bool bControlMenuVisible, int nMaxCases = 0, int nCurCase = 0)
        :ScenarioMenuLayer(bControlMenuVisible, nMaxCases, nCurCase)
    {
    }

    virtual std::string title() const override;
    virtual void performTests() override;

    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) override;

    static cocos2d::Scene* scene();

private:
    void addNewSprites(int num);
    void removeSprites();

    void addParticles();
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
};

void runScenarioTest();

#endif
