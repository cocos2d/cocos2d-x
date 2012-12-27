#ifndef __CCFLOAT_H__
#define __CCFLOAT_H__

#include "CCObject.h"

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

class CC_DLL CCFloat : public CCObject
{
public:
    CCFloat(float v)
        : m_nValue(v) {}
    float getValue() const {return m_nValue;}

    static CCFloat* create(float v)
    {
        CCFloat* pRet = new CCFloat(v);
        pRet->autorelease();
        return pRet;
    }
private:
    float m_nValue;
};

// end of data_structure group
/// @}

NS_CC_END

#endif /* __CCFLOAT_H__ */
