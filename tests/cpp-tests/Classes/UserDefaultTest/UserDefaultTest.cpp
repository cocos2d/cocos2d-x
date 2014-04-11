#include "UserDefaultTest.h"
#include "stdio.h"
#include "stdlib.h"

// enable log
#define COCOS2D_DEBUG 1

UserDefaultTest::UserDefaultTest()
{
    auto s = Director::getInstance()->getWinSize();
    auto label = Label::createWithTTF("CCUserDefault test see log", "fonts/arial.ttf", 28);
    addChild(label, 0);
    label->setPosition( Point(s.width/2, s.height-50) );

    doTest();
}

void UserDefaultTest::doTest()
{
    CCLOG("********************** init value ***********************");

    // set default value

    UserDefault::getInstance()->setStringForKey("string", "value1");
    UserDefault::getInstance()->setIntegerForKey("integer", 10);
    UserDefault::getInstance()->setFloatForKey("float", 2.3f);
    UserDefault::getInstance()->setDoubleForKey("double", 2.4);
    UserDefault::getInstance()->setBoolForKey("bool", true);

    // print value

    std::string ret = UserDefault::getInstance()->getStringForKey("string");
    CCLOG("string is %s", ret.c_str());

    double d = UserDefault::getInstance()->getDoubleForKey("double");
    CCLOG("double is %f", d);

    int i = UserDefault::getInstance()->getIntegerForKey("integer");
    CCLOG("integer is %d", i);

    float f = UserDefault::getInstance()->getFloatForKey("float");
    CCLOG("float is %f", f);

    bool b = UserDefault::getInstance()->getBoolForKey("bool");
    if (b)
    {
        CCLOG("bool is true");
    }
    else
    {
        CCLOG("bool is false");
    }
    
    //CCUserDefault::getInstance()->flush();

    CCLOG("********************** after change value ***********************");

    // change the value

    UserDefault::getInstance()->setStringForKey("string", "value2");
    UserDefault::getInstance()->setIntegerForKey("integer", 11);
    UserDefault::getInstance()->setFloatForKey("float", 2.5f);
    UserDefault::getInstance()->setDoubleForKey("double", 2.6);
    UserDefault::getInstance()->setBoolForKey("bool", false);

    UserDefault::getInstance()->flush();

    // print value

    ret = UserDefault::getInstance()->getStringForKey("string");
    CCLOG("string is %s", ret.c_str());

    d = UserDefault::getInstance()->getDoubleForKey("double");
    CCLOG("double is %f", d);

    i = UserDefault::getInstance()->getIntegerForKey("integer");
    CCLOG("integer is %d", i);

    f = UserDefault::getInstance()->getFloatForKey("float");
    CCLOG("float is %f", f);

    b = UserDefault::getInstance()->getBoolForKey("bool");
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
    auto layer = new UserDefaultTest();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
    layer->release();
}
