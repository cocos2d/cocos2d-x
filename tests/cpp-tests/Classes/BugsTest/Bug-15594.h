// https://github.com/cocos2d/cocos2d-x/pull/15594
#ifndef __cocos2d_tests__Bug_15594__
#define __cocos2d_tests__Bug_15594__

#include "BugsTest.h"

class Bug15594Layer : public BugsTestBase
{
public:
    CREATE_FUNC(Bug15594Layer);

    virtual bool init() override;
};

#endif /* defined(__cocos2d_tests__Bug_15594__) */
