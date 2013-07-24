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
#include <string>

NS_CC_BEGIN

class Object;
class Bool;
class Integer;
class Float;
class Double;
class String;
class Array;
class Dictionary;
class Set;
class Data;

/**
 * @addtogroup data_structures
 * @{
 */

/**
 * Visitor that helps to perform action that depends on polymorphic object type
 *
 * Use cases:
 *  - data serialization,
 *  - pretty printing of \a Object *
 *  - safe value reading from \a Array, \a Dictionary, \a Set
 *
 * Usage:
 *  1. subclass DataVisitor
 *  2. overload visit() methods for object that you need to handle
 *  3. handle other objects in \a visitObject()
 *  4. pass your visitor to \a Object::acceptVisitor()
 */
class CC_DLL DataVisitor
{
public:
    virtual ~DataVisitor() {}

    /** default method, called from non-overloaded methods and for unrecognized objects */
    virtual void visitObject(const Object *p) = 0;

    virtual void visit(const Bool *p);
    virtual void visit(const Integer *p);
    virtual void visit(const Float *p);
    virtual void visit(const Double *p);
    virtual void visit(const String *p);
    virtual void visit(const Array *p);
    virtual void visit(const Dictionary *p);
    virtual void visit(const Set *p);
    virtual void visit(const Data *p);
};


class CC_DLL PrettyPrinter : public DataVisitor
{
public:
    PrettyPrinter(int indentLevel = 0);
    
    virtual void clear();
    virtual std::string getResult();
    
    virtual void visitObject(const Object *p);
    virtual void visit(const Bool * p);
    virtual void visit(const Integer *p);
    virtual void visit(const Float *p);
    virtual void visit(const Double *p);
    virtual void visit(const String *p);
    virtual void visit(const Array *p);
    virtual void visit(const Dictionary *p);
    virtual void visit(const Set *p);
    virtual void visit(const Data *p);
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
