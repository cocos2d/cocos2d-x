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

#include "CCObject.h"
#include "CCBool.h"
#include "CCInteger.h"
#include "CCFloat.h"
#include "CCDouble.h"
#include "CCString.h"
#include "CCArray.h"
#include "CCDictionary.h"
#include "CCSet.h"

NS_CC_BEGIN

void CCDataVisitor::visit(const CCBool *value)
{
    visitObject(value);
}

void CCDataVisitor::visit(const CCInteger *value)
{
    visitObject(value);
}

void CCDataVisitor::visit(const CCFloat *value)
{
    visitObject(value);
}

void CCDataVisitor::visit(const CCDouble *value)
{
    visitObject(value);
}

void CCDataVisitor::visit(const CCString *value)
{
    visitObject(value);
}

void CCDataVisitor::visit(const CCArray *value)
{
    visitObject(value);
}

void CCDataVisitor::visit(const CCDictionary *value)
{
    visitObject(value);
}

void CCDataVisitor::visit(const CCSet *value)
{
    visitObject(value);
}

// CCPrettyPrinter
CCPrettyPrinter::CCPrettyPrinter(int indentLevel/* = 0 */)
{
    setIndentLevel(indentLevel);
}

void CCPrettyPrinter::clear()
{
    _result.clear();
}

std::string CCPrettyPrinter::getResult()
{
    return _result;
}

void CCPrettyPrinter::visitObject(const CCObject *p)
{
    char buf[50] = {0};
    sprintf(buf, "%p", p);
    _result += buf;
}

void CCPrettyPrinter::visit(const CCBool * p)
{
    char buf[50] = {0};
    sprintf(buf, "%s", p->getValue() ? "true" : "false");
   _result += buf;
}

void CCPrettyPrinter::visit(const CCInteger *p)
{
    char buf[50] = {0};
    sprintf(buf, "%d", p->getValue());
    _result += buf;
}

void CCPrettyPrinter::visit(const CCFloat *p)
{
    char buf[50] = {0};
    sprintf(buf, "%f", p->getValue());
    _result += buf;
}

void CCPrettyPrinter::visit(const CCDouble *p)
{
    char buf[50] = {0};
    sprintf(buf, "%lf", p->getValue());
    _result += buf;
}

void CCPrettyPrinter::visit(const CCString *p)
{
    _result += p->getCString();
}

void CCPrettyPrinter::visit(const CCArray *p)
{
    _result += "\n";
    _result += _indentStr;
    _result += "<array>\n";

    setIndentLevel(_indentLevel+1);
    CCObject* obj;
    int i = 0;
    char buf[50] = {0};
    CCARRAY_FOREACH(p, obj)
    {
        if (i > 0) {
            _result += "\n";
        }
        sprintf(buf, "%s%02d: ", _indentStr.c_str(), i);
        _result += buf;
        CCPrettyPrinter v(_indentLevel);
        obj->acceptVisitor(v);
        _result += v.getResult();
        i++;
    }
    setIndentLevel(_indentLevel-1);
    
    _result += "\n";
    _result += _indentStr;
    _result += "</array>";
}

void CCPrettyPrinter::visit(const CCDictionary *p)
{
    _result += "\n";
    _result += _indentStr;
    _result += "<dict>\n";
    
    setIndentLevel(_indentLevel+1);
    CCDictElement* element;
    bool bFirstElement = true;
    char buf[1000] = {0};
    CCDICT_FOREACH(p, element)
    {
        if (!bFirstElement) {
            _result += "\n";
        }
        sprintf(buf, "%s%s: ", _indentStr.c_str(),element->getStrKey());
        _result += buf;
        CCPrettyPrinter v(_indentLevel);
        element->getObject()->acceptVisitor(v);
        _result += v.getResult();
        bFirstElement = false;
    }
    setIndentLevel(_indentLevel-1);
    
    _result += "\n";
    _result += _indentStr;
    _result += "</dict>";
}

void CCPrettyPrinter::visit(const CCSet *p)
{
    _result += "\n";
    _result += _indentStr;
    _result += "<set>\n";
    
    setIndentLevel(_indentLevel+1);

    int i = 0;
    CCSet* tmp = const_cast<CCSet*>(p);
    CCSetIterator it = tmp->begin();

    for (; it != tmp->end(); ++it, ++i) {
        if (i > 0) {
            _result += "\n";
        }
        _result += _indentStr.c_str();
        CCPrettyPrinter v(_indentLevel);
        (*it)->acceptVisitor(v);
        _result += v.getResult();
    }
    setIndentLevel(_indentLevel-1);
    
    _result += "\n";
    _result += _indentStr;
    _result += "</set>\n";
}

void CCPrettyPrinter::setIndentLevel(int indentLevel)
{
    _indentLevel = indentLevel;
    _indentStr.clear();
    for (int i = 0; i < _indentLevel; ++i) {
        _indentStr += "\t";
    }
}

NS_CC_END
