/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

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
    auto label = Label::createWithTTF("CCUserDefault test Log data see console", "fonts/arial.ttf", 22);
    addChild(label, 0);
    label->setPosition( Vec2(s.width/2, s.height-50) );

    this->_label = Label::createWithTTF("result", "fonts/arial.ttf", 12);
    addChild(this->_label, 0);

    label->setPosition(Vec2(s.width / 2, s.height - 50));
    this->_label->setPosition(Vec2(s.width / 2, s.height / 2));

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
    this->_label->setString(this->_label->getString() + "\n" + "********************** init value ***********************");

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

    printValue();

    logData<int>("int_data");
    logData<float>("float_data");
    logData<double>("double_data");

    //CCUserDefault::getInstance()->flush();

    this->_label->setString(this->_label->getString() + "\n" + "********************** after change value ***********************");

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
    printValue();

    logData<int>("int_data");
    logData<float>("float_data");
    logData<double>("double_data");

    this->_label->setString(this->_label->getString() + "\n" + "********************** after delete value ***********************");

    UserDefault::getInstance()->deleteValueForKey("string");
    UserDefault::getInstance()->deleteValueForKey("integer");
    UserDefault::getInstance()->deleteValueForKey("float");
    UserDefault::getInstance()->deleteValueForKey("double");
    UserDefault::getInstance()->deleteValueForKey("bool");

    // print value
    printValue();
}

void UserDefaultTest::printValue()
{
    char strTemp[256] = "";
    // print value
    std::string ret = UserDefault::getInstance()->getStringForKey("string");
    sprintf(strTemp, "string is %s", ret.c_str());
    this->_label->setString(this->_label->getString() + "\n" + strTemp);

    double d = UserDefault::getInstance()->getDoubleForKey("double");
    sprintf(strTemp, "double is %f", d);
    this->_label->setString(this->_label->getString() + "\n" + strTemp);

    int i = UserDefault::getInstance()->getIntegerForKey("integer");
    sprintf(strTemp, "integer is %d", i);
    this->_label->setString(this->_label->getString() + "\n" + strTemp);

    float f = UserDefault::getInstance()->getFloatForKey("float");
    sprintf(strTemp, "float is %f", f);
    this->_label->setString(this->_label->getString() + "\n" + strTemp);

    bool b = UserDefault::getInstance()->getBoolForKey("bool");
    if (b)
    {
        sprintf(strTemp, "bool is true");
        this->_label->setString(this->_label->getString() + "\n" + strTemp);
    }
    else
    {
        sprintf(strTemp, "bool is false");
        this->_label->setString(this->_label->getString() + "\n" + strTemp);
    }
}

UserDefaultTest::~UserDefaultTest()
{
}


