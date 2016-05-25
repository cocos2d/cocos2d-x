#ifndef _JNI_TEST_H_
#define _JNI_TEST_H_

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "cocos2d.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(JNITests);

class JNITest : public TestCase
{
public:
    CREATE_FUNC(JNITest);

    JNITest();
};
#endif
#endif // _JNI_TEST_H_
