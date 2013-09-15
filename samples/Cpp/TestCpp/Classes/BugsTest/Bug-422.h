#ifndef __BUG_422_H__
#define __BUG_422_H__

#include "BugsTest.h"

class Bug422Layer : public BugsTestBaseLayer
{
public:
    virtual bool init();

    void reset();
    void check(Node* target);
    void menuCallback(Object* sender);
};

#endif // __BUG_422_H__
