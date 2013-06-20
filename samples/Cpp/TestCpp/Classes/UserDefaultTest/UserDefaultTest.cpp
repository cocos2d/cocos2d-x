// enable log
#define COCOS2D_DEBUG 1

#include "UserDefaultTest.h"
#include "stdio.h"
#include "stdlib.h"

UserDefaultTest::UserDefaultTest()
{
    Size s = Director::sharedDirector()->getWinSize();
    LabelTTF* label = LabelTTF::create("CCUserDefault test see log", "Arial", 28);
    addChild(label, 0);
    label->setPosition( ccp(s.width/2, s.height-50) );

    doTest();
}

void UserDefaultTest::doTest()
{
    CCLOG("********************** init value ***********************");

    // set default value

    UserDefault::sharedUserDefault()->setStringForKey("string", "value1");
    UserDefault::sharedUserDefault()->setIntegerForKey("integer", 10);
    UserDefault::sharedUserDefault()->setFloatForKey("float", 2.3f);
    UserDefault::sharedUserDefault()->setDoubleForKey("double", 2.4);
    UserDefault::sharedUserDefault()->setBoolForKey("bool", true);

    // print value

    string ret = UserDefault::sharedUserDefault()->getStringForKey("string");
    CCLOG("string is %s", ret.c_str());

    double d = UserDefault::sharedUserDefault()->getDoubleForKey("double");
    CCLOG("double is %f", d);

    int i = UserDefault::sharedUserDefault()->getIntegerForKey("integer");
    CCLOG("integer is %d", i);

    float f = UserDefault::sharedUserDefault()->getFloatForKey("float");
    CCLOG("float is %f", f);

    bool b = UserDefault::sharedUserDefault()->getBoolForKey("bool");
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

    UserDefault::sharedUserDefault()->setStringForKey("string", "value2");
    UserDefault::sharedUserDefault()->setIntegerForKey("integer", 11);
    UserDefault::sharedUserDefault()->setFloatForKey("float", 2.5f);
    UserDefault::sharedUserDefault()->setDoubleForKey("double", 2.6);
    UserDefault::sharedUserDefault()->setBoolForKey("bool", false);

    UserDefault::sharedUserDefault()->flush();

    // print value

    ret = UserDefault::sharedUserDefault()->getStringForKey("string");
    CCLOG("string is %s", ret.c_str());

    d = UserDefault::sharedUserDefault()->getDoubleForKey("double");
    CCLOG("double is %f", d);

    i = UserDefault::sharedUserDefault()->getIntegerForKey("integer");
    CCLOG("integer is %d", i);

    f = UserDefault::sharedUserDefault()->getFloatForKey("float");
    CCLOG("float is %f", f);

    b = UserDefault::sharedUserDefault()->getBoolForKey("bool");
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
    Layer* pLayer = new UserDefaultTest();
    addChild(pLayer);

    Director::sharedDirector()->replaceScene(this);
    pLayer->release();
}
