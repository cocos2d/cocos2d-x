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

    virtual void onEnter();
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

    static Scene* scene();

private:
    void createParticle();
    void addNewSprites();
    void removeSprites();

    void addParticles();
    void removeParticles();

private:
    MenuItemToggle* _itemToggle;
    Vector<Sprite*> _spriteArray;
    LabelTTF* _spriteLabel;
    LabelTTF* _particleLabel;
    int _particleNumber;
};

void runScenarioTest();

#endif
