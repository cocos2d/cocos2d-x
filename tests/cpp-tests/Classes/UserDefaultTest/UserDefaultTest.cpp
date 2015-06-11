#include "UserDefaultTest.h"
#include "stdio.h"
#include "stdlib.h"
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

USING_NS_CC;

// enable log
#define COCOS2D_DEBUG 1


UserDefaultTests::UserDefaultTests()
{
    ADD_TEST_CASE(UserDefaultTest);
}

UserDefaultTest::UserDefaultTest()
{
    auto s = Director::getInstance()->getWinSize();
    auto label = Label::createWithTTF("CCUserDefault test see log", "fonts/arial.ttf", 28);
    addChild(label, 0);
    label->setPosition( Vec2(s.width/2, s.height-50) );

    doTest();
}

template<typename T>
void logData(const char* key)
{
    Data data = UserDefault::getInstance()->getDataForKey(key);
    T* buffer = (T*) data.getBytes();
    ssize_t length = data.getSize() / sizeof(T);

    std::ostringstream ss;
    ss << setprecision(2) << std::fixed;
    for (int i = 0; i < length; i++)
    {
        ss << buffer[i] << " ";
    }

    CCLOG("%s is %s", key, ss.str().c_str());
}

template<typename T>
void setData(const char* key)
{
    Data data;
    vector<T> v;

    for (int i = 0; i <= 5; i++)
    {
        v.push_back(static_cast<T>(i));
    }
    data.copy((unsigned char*) v.data(), v.size() * sizeof(T));
    UserDefault::getInstance()->setDataForKey(key, data);
}

template<typename T>
void setData2(const char* key)
{
    Data data;
    vector<T> v;

    for (int i = 5; i >= 0; i--)
    {
        v.push_back(static_cast<T>(i));
    }
    data.copy((unsigned char*) v.data(), v.size() * sizeof(T));
    UserDefault::getInstance()->setDataForKey(key, data);
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

    // test saving of Data buffers
    setData<int>("int_data");
    setData<float>("float_data");
    setData<double>("double_data");

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

    logData<int>("int_data");
    logData<float>("float_data");
    logData<double>("double_data");

    //CCUserDefault::getInstance()->flush();

    CCLOG("********************** after change value ***********************");

    // change the value

    UserDefault::getInstance()->setStringForKey("string", "value2");
    UserDefault::getInstance()->setIntegerForKey("integer", 11);
    UserDefault::getInstance()->setFloatForKey("float", 2.5f);
    UserDefault::getInstance()->setDoubleForKey("double", 2.6);
    UserDefault::getInstance()->setBoolForKey("bool", false);

    setData2<int>("int_data");
    setData2<float>("float_data");
    setData2<double>("double_data");

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

    logData<int>("int_data");
    logData<float>("float_data");
    logData<double>("double_data");
}


UserDefaultTest::~UserDefaultTest()
{
}
