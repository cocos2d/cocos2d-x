#ifndef _NETWORK_UTILS_TEST_H_
#define _NETWORK_UTILS_TEST_H_

#include "cocos2d.h"
#include "../testBasic.h"

class NetworkUtilsTest : public Layer
{
public:
    NetworkUtilsTest();
    virtual ~NetworkUtilsTest();
    
    void onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event);
private:
    cocos2d::Label* _label;
};

class NetworkUtilsTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif // _NETWORK_UTILS_TEST_H_
