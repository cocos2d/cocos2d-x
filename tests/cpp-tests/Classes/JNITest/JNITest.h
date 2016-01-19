#ifndef _JNI_TEST_H_
#define _JNI_TEST_H_

#include "cocos2d.h"
#include "../BaseTest.h"

DEFINE_TEST_SUITE(JNITests);

class JNITest : public TestCase
{
public:
    CREATE_FUNC(JNITest);

    JNITest();
};

#endif // _JNI_TEST_H_
