#ifndef __CCINTEGER_H__
#define __CCINTEGER_H__

#include "CCObject.h"

NS_CC_BEGIN

class CC_DLL CCInteger : public CCObject
{
public:
    CCInteger(int v)
        : m_nValue(v) {}
    int getValue() const {return m_nValue;}

    static CCInteger* integerWithInt(int v)
    {
        CCInteger* pRet = new CCInteger(v);
        pRet->autorelease();
        return pRet;
    }
private:
    int m_nValue;
};

NS_CC_END

#endif /* __CCINTEGER_H__ */
