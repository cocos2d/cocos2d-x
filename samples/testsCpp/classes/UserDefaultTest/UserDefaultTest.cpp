// enable log
#define COCOS2D_DEBUG 1

#include "UserDefaultTest.h"
#include "stdio.h"
#include "stdlib.h"

UserDefaultTest::UserDefaultTest()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF* label = CCLabelTTF::create("CCUserDefault test see log", "Arial", 28);
    addChild(label, 0);
    label->setPosition( ccp(s.width/2, s.height-50) );

    doTest();
}

void UserDefaultTest::doTest()
{
    CCLOG("********************** init value ***********************");

    // set default value

    CCUserDefault::sharedUserDefault()->setStringForKey("string", "value1");
    CCUserDefault::sharedUserDefault()->setIntegerForKey("integer", 10);
    CCUserDefault::sharedUserDefault()->setFloatForKey("float", 2.3f);
    CCUserDefault::sharedUserDefault()->setDoubleForKey("double", 2.4);
    CCUserDefault::sharedUserDefault()->setBoolForKey("bool", true);

    // print value

    string ret = CCUserDefault::sharedUserDefault()->getStringForKey("string");
    CCLOG("string is %s", ret.c_str());

    double d = CCUserDefault::sharedUserDefault()->getDoubleForKey("double");
    CCLOG("double is %f", d);

    int i = CCUserDefault::sharedUserDefault()->getIntegerForKey("integer");
    CCLOG("integer is %d", i);

    float f = CCUserDefault::sharedUserDefault()->getFloatForKey("float");
    CCLOG("float is %f", f);

    bool b = CCUserDefault::sharedUserDefault()->getBoolForKey("bool");
    if (b)
    {
        CCLOG("bool is true");
    }
    else
    {
        CCLOG("bool is false");
    }
    
    //CCUserDefault::sharedUserDefault()->flush();

    CCLOG("********************** after change value ***********************");

    // change the value

    CCUserDefault::sharedUserDefault()->setStringForKey("string", "value2");
    CCUserDefault::sharedUserDefault()->setIntegerForKey("integer", 11);
    CCUserDefault::sharedUserDefault()->setFloatForKey("float", 2.5f);
    CCUserDefault::sharedUserDefault()->setDoubleForKey("double", 2.6);
    CCUserDefault::sharedUserDefault()->setBoolForKey("bool", false);

    CCUserDefault::sharedUserDefault()->flush();

    // print value

    ret = CCUserDefault::sharedUserDefault()->getStringForKey("string");
    CCLOG("string is %s", ret.c_str());

    d = CCUserDefault::sharedUserDefault()->getDoubleForKey("double");
    CCLOG("double is %f", d);

    i = CCUserDefault::sharedUserDefault()->getIntegerForKey("integer");
    CCLOG("integer is %d", i);

    f = CCUserDefault::sharedUserDefault()->getFloatForKey("float");
    CCLOG("float is %f", f);

    b = CCUserDefault::sharedUserDefault()->getBoolForKey("bool");
    if (b)
    {
        CCLOG("bool is true");
    }
    else
    {
        CCLOG("bool is false");
    }
}


UserDefaultTest::~UserDefaultTest()
{
}

void UserDefaultTestScene::runThisTest()
{
    CCLayer* pLayer = new UserDefaultTest();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();
}
