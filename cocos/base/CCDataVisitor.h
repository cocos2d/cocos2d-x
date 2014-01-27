/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "CCPlatformMacros.h"
#include <string>

NS_CC_BEGIN

class Object;
class __Bool;
class __Integer;
class __Float;
class __Double;
class __String;
class __Array;
class __Dictionary;
class __Set;

/**
 * @addtogroup data_structures
 * @{
 */

/**
 * Visitor that helps to perform action that depends on polymorphic object type
 *
 * Use cases:
 *  - data serialization,
 *  - pretty printing of Object *
 *  - safe value reading from Array, __Dictionary, Set
 *
 * Usage:
 *  1. subclass DataVisitor
 *  2. overload visit() methods for object that you need to handle
 *  3. handle other objects in visitObject()
 *  4. pass your visitor to Object::acceptVisitor()
 */
class CC_DLL DataVisitor
{
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~DataVisitor() {}

    /** default method, called from non-overloaded methods and for unrecognized objects */
    virtual void visitObject(const Object *p) = 0;

    virtual void visit(const __Bool *p);
    virtual void visit(const __Integer *p);
    virtual void visit(const __Float *p);
    virtual void visit(const __Double *p);
    virtual void visit(const __String *p);
    virtual void visit(const __Array *p);
    virtual void visit(const __Dictionary *p);
    virtual void visit(const __Set *p);
};


class CC_DLL PrettyPrinter : public DataVisitor
{
public:
    PrettyPrinter(int indentLevel = 0);
    
    virtual void clear();
    virtual std::string getResult();
    
    virtual void visitObject(const Object *p);
    virtual void visit(const __Bool * p);
    virtual void visit(const __Integer *p);
    virtual void visit(const __Float *p);
    virtual void visit(const __Double *p);
    virtual void visit(const __String *p);
    virtual void visit(const __Array *p);
    virtual void visit(const __Dictionary *p);
    virtual void visit(const __Set *p);
private:
    void setIndentLevel(int indentLevel);
    int _indentLevel;
    std::string _indentStr;
    std::string _result;
};

// end of data_structure group
/// @}

NS_CC_END

#endif // __CCDATAVISITOR_H__
