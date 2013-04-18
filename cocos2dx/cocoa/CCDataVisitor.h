/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#ifndef __CCDATAVISITOR_H__
#define __CCDATAVISITOR_H__

#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

class CCObject;
class CCBool;
class CCInteger;
class CCFloat;
class CCDouble;
class CCString;
class CCArray;
class CCDictionary;
class CCSet;

/**
 * @addtogroup data_structures
 * @{
 */

/**
 * Visitor that helps to perform action that depends on polymorphic object type
 *
 * Use cases:
 *  - data serialization,
 *  - pretty printing of \a CCObject *
 *  - safe value reading from \a CCArray, \a CCDictionary, \a CCSet
 *
 * Usage:
 *  1. subclass CCDataVisitor
 *  2. overload visit() methods for object that you need to handle
 *  3. handle other objects in \a visitObject()
 *  4. pass your visitor to \a CCObject::acceptVisitor()
 */
class CCDataVisitor
{
public:
    virtual ~CCDataVisitor() {}

    /** default method, called from non-overloaded methods and for unrecognized objects */
    virtual void visitObject(const CCObject *) = 0;

    virtual void visit(const CCBool *);
    virtual void visit(const CCInteger *);
    virtual void visit(const CCFloat *);
    virtual void visit(const CCDouble *);
    virtual void visit(const CCString *);
    virtual void visit(const CCArray *);
    virtual void visit(const CCDictionary *);
    virtual void visit(const CCSet *);
};

// end of data_structure group
/// @}

NS_CC_END

#endif // __CCDATAVISITOR_H__
