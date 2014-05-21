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

#include "base/CCPlatformMacros.h"
#include <string>

NS_CC_BEGIN

class Ref;
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
 * 访问者(Visitor)模式: 在多型的数据的情形下, 提供一个共同的方法, 使访问数据更加方便.
 *
 * 用例:
 *  - 数据序列化,
 *  - 更好地打印 Ref* 
 *  - 安全的从 Array, __Dictionary, Set 中读数据.
 *
 * 使用方法:
 *  1. 一个继承 DataVisitor 的子类.
 *  2. 重载你需要处理的对象的`visit()` 方法.
 *  3. 在 `visitObject()` 处理其他对象.
 *  4. 把你的访问者(Visitor)传递给 `Object::acceptVisitor()`.
 */
class CC_DLL DataVisitor
{
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~DataVisitor() {}

    /** 默认方法, 由未重载方法和未识别对象调用. */
    virtual void visitObject(const Ref *p) = 0;

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
    
    virtual void visitObject(const Ref *p);
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
