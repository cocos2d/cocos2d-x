#ifndef _CURL_TEST_H_
#define _CURL_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"

class CurlTest : public Layer
{
public:
    CurlTest();
    ~CurlTest();

    virtual void ccTouchesEnded(cc::Set *pTouches, cc::Event *pEvent);

private:
    cc::LabelTTF*         _label;
};

class CurlTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif // _CURL_TEST_H_
