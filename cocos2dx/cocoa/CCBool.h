#ifndef __CCBOOL_H__
#define __CCBOOL_H__

#include "CCObject.h"

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

class CC_DLL CCBool : public CCObject
{
public:
    CCBool(bool v)
        : m_nValue(v) {}
    bool getValue() const {return m_nValue;}

    static CCBool* create(bool v)
    {
        CCBool* pRet = new CCBool(v);
        pRet->autorelease();
        return pRet;
    }
private:
    double m_nValue;
};

// end of data_structure group
/// @}

NS_CC_END

#endif /* __CCBOOL_H__ */
