#ifndef __BUG_350_H__
#define __BUG_350_H__

#include "BugsTest.h"

class Bug350Layer : public BugsTestBase
{
public:
    CREATE_FUNC(Bug350Layer);

    virtual bool init() override;
};

#endif // __BUG_350_H__
