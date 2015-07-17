#ifndef __BUG_PAGEVIEWLAYOUT_H__
#define __BUG_PAGEVIEWLAYOUT_H__

#include "BugsTest.h"

class BugPageViewLayer : public BugsTestBase
{
public:
    CREATE_FUNC(BugPageViewLayer);

    virtual bool init() override;
};

#endif // !__BUG_PAGEVIEWLAYOUT_H__
