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
