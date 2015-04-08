#ifndef __BUG_914_H__
#define __BUG_914_H__

#include "BugsTest.h"

class Bug914Layer : public BugsTestBase
{
public:
    static Scene* scene();
    virtual bool init() override;

    void onTouchesMoved(const std::vector<Touch*>& touches, Event * event);
    void onTouchesBegan(const std::vector<Touch*>& touches, Event * event);
    void restart(Ref* sender);

    CREATE_FUNC(Bug914Layer);
};

#endif // __BUG_914_H__
