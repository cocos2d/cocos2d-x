#ifndef __BUG_1159_H__
#define __BUG_1159_H__

#include "BugsTest.h"

class Bug1159Layer : public BugsTestBaseLayer
{
public:
    virtual bool init();
    static CCScene* scene();
    void callBack(CCObject* pSender);

    LAYER_NODE_FUNC(Bug1159Layer);
};

#endif // __BUG_1159_H__
