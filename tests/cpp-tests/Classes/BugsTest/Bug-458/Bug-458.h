#ifndef __BUG_458_H__
#define __BUG_458_H__

#include "../BugsTest.h"

class Bug458Layer : public BugsTestBaseLayer
{
public:
    virtual bool init();
    void selectAnswer(Ref* sender);
};

#endif // __BUG_458_H__
