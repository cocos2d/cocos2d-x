#ifndef __BUG_899_H__
#define __BUG_899_H__

#include "BugsTest.h"

class Bug899Layer : public BugsTestBase
{
public:
    CREATE_FUNC(Bug899Layer);

    virtual bool init() override;
};

#endif // __BUG_899_H__
