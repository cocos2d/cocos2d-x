#ifndef __BUG_CCDRAWNODE_H__
#define __BUG_CCDRAWNODE_H__

#include "BugsTest.h"

class BugDrawNodeLayer : public BugsTestBase
{
public:
    CREATE_FUNC(BugDrawNodeLayer);

    virtual bool init() override;
};

#endif