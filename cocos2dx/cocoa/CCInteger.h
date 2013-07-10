#ifndef __CCINTEGER_H__
#define __CCINTEGER_H__

#include "CCObject.h"

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

class CC_DLL Integer : public Object, public Clonable
{
public:
    Integer(int v)
        : _value(v) {}
    int getValue() const {return _value;}

    static Integer* create(int v)
    {
        Integer* pRet = new Integer(v);
        pRet->autorelease();
        return pRet;
    }

    /* override functions */
    virtual void acceptVisitor(DataVisitor &visitor) { visitor.visit(this); }

    Integer* clone() const
    {
        return Integer::create(_value);
    }
    
private:
    int _value;
};

// end of data_structure group
/// @}

NS_CC_END

#endif /* __CCINTEGER_H__ */
