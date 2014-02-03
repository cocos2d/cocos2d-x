/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CCINTEGER_H__
#define __CCINTEGER_H__

#include "CCObject.h"
#include "platform/CCCommon.h"

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

class CC_DLL __Integer : public Object, public Clonable
{
public:
    static __Integer* create(int v)
    {
        __Integer* pRet = new __Integer(v);
        pRet->autorelease();
        return pRet;
    }
    /**
     * @js NA
     */
    __Integer(int v)
        : _value(v) {}
    int getValue() const {return _value;}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~__Integer() {
        CCLOGINFO("deallocing ~__Integer: %p", this);
    }

    /* override functions */
    virtual void acceptVisitor(DataVisitor &visitor) { visitor.visit(this); }

    // overrides
    virtual __Integer* clone() const override
    {
        return __Integer::create(_value);
    }
    
private:
    int _value;
};

// end of data_structure group
/// @}

NS_CC_END

#endif /* __CCINTEGER_H__ */
