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
    //UxString    m_strTitle;

public:
    TextLayer(void);
    ~TextLayer(void);

    void checkAnim(float dt);

    virtual void onEnter();

    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);

    void newScene();

    static TextLayer* create();
};

#endif
