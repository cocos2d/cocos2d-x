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
    virtual void runThisTest();
};

#endif // _CURL_TEST_H_
