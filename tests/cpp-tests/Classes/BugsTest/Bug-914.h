#ifndef __BUG_914_H__
#define __BUG_914_H__

#include "BugsTest.h"

class Bug914Layer : public BugsTestBase
{
public:
    virtual bool init() override;

    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void restart(cocos2d::Ref* sender);

    CREATE_FUNC(Bug914Layer);
};

#endif // __BUG_914_H__
