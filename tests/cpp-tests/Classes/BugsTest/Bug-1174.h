#ifndef __BUG_1174_H__
#define __BUG_1174_H__

#include "BugsTest.h"

class Bug1174Layer : public BugsTestBase
{
public:
    CREATE_FUNC(Bug1174Layer);

    virtual bool init() override;
};

#endif // __BUG_1174_H__
