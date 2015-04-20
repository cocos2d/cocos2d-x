#ifndef __BUG_422_H__
#define __BUG_422_H__

#include "BugsTest.h"

class Bug422Layer : public BugsTestBase
{
public:
    CREATE_FUNC(Bug422Layer);

    virtual bool init() override;

    void reset();
    void check(Node* target);
    void menuCallback(cocos2d::Ref* sender);
};

#endif // __BUG_422_H__
