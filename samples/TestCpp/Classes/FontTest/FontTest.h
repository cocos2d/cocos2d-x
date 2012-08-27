#ifndef _FONT_TEST_H_
#define _FONT_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"

class FontTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class FontTest : public cocos2d::CCLayer
{
public:
    FontTest();
    void showFont(const char *pFont);

    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);
    virtual std::string title();

    CREATE_FUNC(FontTest);
};

#endif // _FONT_TEST_H_
