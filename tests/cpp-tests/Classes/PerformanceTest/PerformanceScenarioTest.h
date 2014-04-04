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

    virtual void showCurrentTest();

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
    virtual void performTests();

    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);

    static Scene* scene();

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

    TMXTiledMap* _map1;
    TMXTiledMap* _map2;

    MenuItemToggle* _itemToggle;
    Vector<Sprite*> _spriteArray;
    Vector<ParticleSystemQuad*> _parsysArray;
    Label* _spriteLabel;
    Label* _particleLabel;
    Label* _parsysLabel;
    int _particleNumber;
};

void runScenarioTest();

#endif
