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

#ifndef __CCFLOAT_H__
#define __CCFLOAT_H__

#include "CCObject.h"

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

class CC_DLL __Float : public Object, public Clonable
{
public:
    __Float(float v)
        : _value(v) {}
    float getValue() const {return _value;}

    static __Float* create(float v)
    {
        __Float* pRet = new __Float(v);
        if (pRet)
        {
            pRet->autorelease();
        }
        return pRet;
    }

    /* override functions */
    virtual void acceptVisitor(DataVisitor &visitor) { visitor.visit(this); }
    
    __Float* clone() const
    {
        return __Float::create(_value);
    }
    
private:
    float _value;
};

// end of data_structure group
/// @}

NS_CC_END

#endif /* __CCFLOAT_H__ */
