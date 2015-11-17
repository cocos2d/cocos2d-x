#ifndef __BUG_624_H__
#define __BUG_624_H__

#include "BugsTest.h"

class Bug624Layer : public BugsTestBase
{
public:
    virtual ~Bug624Layer();
    virtual bool init() override;
    void switchLayer(float dt);
    virtual void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event);

    CREATE_FUNC(Bug624Layer);
};

class Bug624Layer2 : public BugsTestBase
{
public:
    virtual ~Bug624Layer2();
    virtual bool init() override;
    void switchLayer(float dt);
    virtual void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event);

    CREATE_FUNC(Bug624Layer2);
};

#endif // __BUG_624_H__
