#ifndef __CCDOUBLE_H__
#define __CCDOUBLE_H__

#include "CCObject.h"

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

class CC_DLL CCDouble : public CCObject
{
public:
    CCDouble(double v)
        : m_nValue(v) {}
    double getValue() const {return m_nValue;}

    static CCDouble* create(double v)
    {
        CCDouble* pRet = new CCDouble(v);
        pRet->autorelease();
        return pRet;
    }
private:
    double m_nValue;
};

// end of data_structure group
/// @}

NS_CC_END

#endif /* __CCDOUBLE_H__ */
