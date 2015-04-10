#ifndef _EFFECTS_TEST_H_
#define _EFFECTS_TEST_H_

#include "../testBasic.h"
#include "../BaseTest.h"

class EffectTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class TextLayer : public BaseTest
{
protected:
    //UxString    _title;
    NodeGrid* _gridNodeTarget;
public:
    TextLayer(void);
    ~TextLayer(void);

    void checkAnim(float dt);

    virtual void onEnter() override;

    void restartCallback(Ref* sender) override;
    void nextCallback(Ref* sender) override;
    void backCallback(Ref* sender) override;

    void newScene();

    static TextLayer* create();
};

#endif
