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

public:
    TextLayer(void);
    ~TextLayer(void);

    void checkAnim(float dt);

    virtual void onEnter();

    void restartCallback(Object* pSender);
    void nextCallback(Object* pSender);
    void backCallback(Object* pSender);

    void newScene();

    static TextLayer* create();
};

#endif
