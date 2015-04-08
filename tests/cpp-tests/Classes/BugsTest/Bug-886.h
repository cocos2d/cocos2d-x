#ifndef __BUG_886_H__
#define __BUG_886_H__

#include "BugsTest.h"

class Bug886Layer : public BugsTestBase
{
public:
    CREATE_FUNC(Bug886Layer);

    virtual bool init() override;
};

#endif // __BUG_886_H__
