#ifndef _CURL_TEST_H_
#define _CURL_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"

class CurlTest : public CCLayer
{
public:
    CurlTest();
    ~CurlTest();

    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

private:
    cocos2d::CCLabelTTF*         m_pLabel;
};

class CurlTestScene : public TestScene
{
public:
#if CC_TARGET_PLATFORM == CC_PLATFORM_WINRT && !defined(WINRT_8_1)
    virtual void runThisTest() { return; }
#else
    virtual void runThisTest();
#endif
};

#endif // _CURL_TEST_H_
