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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "JNITest.h"


#include "platform/android/jni/JniHelper.h"

#include <string>

USING_NS_CC;

JNITests::JNITests()
{
    ADD_TEST_CASE(JNITest);
}

JNITest::JNITest()
{
    auto nameLabel = Label::createWithTTF("JNI Test", "fonts/arial.ttf", 28);
    nameLabel->setPosition(VisibleRect::center().x, VisibleRect::top().y - 50);
    addChild(nameLabel);

    auto checkLabel = Label::createWithTTF("Please check console output", "fonts/arial.ttf", 22);
    checkLabel->setPosition(VisibleRect::center());
    addChild(checkLabel);

    const std::string classPath = "org.cocos2dx.cpp_tests.JNITest";

    JniHelper::callStaticVoidMethod(classPath, "voidMethod1");

    JniHelper::callStaticVoidMethod(classPath, "voidMethod2", "JNI is easy");

    JniHelper::callStaticVoidMethod(classPath, "voidMethod3", int(4), float(2.5), "JNI is really easy");

    bool b1 = JniHelper::callStaticBooleanMethod(classPath, "booleanMethod", int(5));
    CC_ASSERT(b1 == true);
    bool b2 = JniHelper::callStaticBooleanMethod(classPath, "booleanMethod", int(-3));
    CC_ASSERT(b2 == false);

    int i = JniHelper::callStaticIntMethod(classPath, "intMethod", int(10), int(10));
    CC_ASSERT(i == 20);

    float f = JniHelper::callStaticFloatMethod(classPath, "floatMethod", float(2.35), float(7.65));
    CC_ASSERT(f == 10.0);  
      
    double d = JniHelper::callStaticDoubleMethod(classPath, "doubleMethod", double(2.5), int(4));
    CC_ASSERT(d == 10.0); 

    std::string str = "ABCDEF";
    std::string s1 = JniHelper::callStaticStringMethod(classPath, "stringMethod", str, true);
    CC_ASSERT(s1 == "FEDCBA");
    std::string s2 = JniHelper::callStaticStringMethod(classPath, "stringMethod", str, false);
    CC_ASSERT(s2 == "ABCDEF");

    const char* cstr = "XYZ";
    std::string s3 = JniHelper::callStaticStringMethod(classPath, "stringMethod", cstr, true);
    CC_ASSERT(s3 == "ZYX");

    // should not crash
    for (int i = 0; i < 10000; i++) {
        JniHelper::callStaticVoidMethod(classPath, "voidMethod4", "ABCDEF");
    }

    // should not compile
    // JniHelper::callStaticVoidMethod(classPath, "voidMethod4", std::vector<int>());
}

#endif
