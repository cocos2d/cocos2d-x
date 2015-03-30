#ifndef __BUG_914_H__
#define __BUG_914_H__

#include "BugsTest.h"

class Bug914Layer : public BugsTestBaseLayer
{
public:
    static Scene* scene();
    virtual bool init() override;

    void onTouchesMoved(const std::vector<Touch*>& touches, Event * event) override;
    void onTouchesBegan(const std::vector<Touch*>& touches, Event * event) override;
    void restart(Ref* sender);

    CREATE_FUNC(Bug914Layer);
};

#endif // __BUG_914_H__
