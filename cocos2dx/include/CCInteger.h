#ifndef __CCINTEGER_H__
#define __CCINTEGER_H__

#include "CCObject.h"

NS_CC_BEGIN

class CC_DLL CCInteger : public CCObject
{
public:
    CCInteger(int v)
        : value(v) {}
    int value;
};

NS_CC_END

#endif /* __CCINTEGER_H__ */
