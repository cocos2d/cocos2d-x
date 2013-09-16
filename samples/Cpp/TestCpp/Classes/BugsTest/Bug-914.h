#ifndef __BUG_914_H__
#define __BUG_914_H__

#include "BugsTest.h"

class Bug914Layer : public BugsTestBaseLayer
{
public:
    static Scene* scene();
    virtual bool init();

    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event * event) override;
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event * event) override;
    void restart(Object* sender);

    CREATE_FUNC(Bug914Layer);
};

#endif // __BUG_914_H__
