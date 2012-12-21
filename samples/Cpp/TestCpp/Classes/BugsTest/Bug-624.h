#ifndef __BUG_624_H__
#define __BUG_624_H__

#include "BugsTest.h"

class Bug624Layer : public BugsTestBaseLayer
{
public:
    virtual bool init();
    void switchLayer(float dt);
    virtual void didAccelerate(CCAcceleration* pAccelerationValue);

    CREATE_FUNC(Bug624Layer);
};

class Bug624Layer2 : public BugsTestBaseLayer
{
public:
    virtual bool init();
    void switchLayer(float dt);
    virtual void didAccelerate(CCAcceleration* pAccelerationValue);

    CREATE_FUNC(Bug624Layer2);
};

#endif // __BUG_624_H__
