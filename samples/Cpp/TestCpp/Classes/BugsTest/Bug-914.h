#ifndef __BUG_914_H__
#define __BUG_914_H__

#include "BugsTest.h"

class Bug914Layer : public BugsTestBaseLayer
{
public:
    static CCScene* scene();
    virtual bool init();

    void ccTouchesMoved(CCSet *touches, CCEvent * event);
    void ccTouchesBegan(CCSet *touches, CCEvent * event);
    void restart(CCObject* sender);

    CREATE_FUNC(Bug914Layer);
};

#endif // __BUG_914_H__
