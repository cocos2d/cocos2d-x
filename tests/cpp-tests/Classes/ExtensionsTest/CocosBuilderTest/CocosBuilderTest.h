#ifndef _CCBIREADER_TEST_H_
#define _CCBIREADER_TEST_H_

#include "../../BaseTest.h"

DEFINE_TEST_SUITE(CocosBuilderTests);

class CocosBuilderTestScene : public TestCase {
public:
    CREATE_FUNC(CocosBuilderTestScene);

    virtual bool init() override;
};

#endif
