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

    const std::string classPath = "org/cocos2dx/cpp_tests/JNITest";

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
