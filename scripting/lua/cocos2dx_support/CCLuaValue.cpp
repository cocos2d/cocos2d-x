/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org
 
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

#include "CCLuaValue.h"


NS_CC_BEGIN

const CCLuaValue CCLuaValue::intValue(const int intValue)
{
    CCLuaValue value;
    value._type = CCLuaValueTypeInt;
    value._field.intValue = intValue;
    return value;
}

const CCLuaValue CCLuaValue::floatValue(const float floatValue)
{
    CCLuaValue value;
    value._type = CCLuaValueTypeFloat;
    value._field.floatValue = floatValue;
    return value;
}

const CCLuaValue CCLuaValue::booleanValue(const bool booleanValue)
{
    CCLuaValue value;
    value._type = CCLuaValueTypeBoolean;
    value._field.booleanValue = booleanValue;
    return value;
}

const CCLuaValue CCLuaValue::stringValue(const char* stringValue)
{
    CCLuaValue value;
    value._type = CCLuaValueTypeString;
    value._field.stringValue = new std::string(stringValue ? stringValue : "");
    return value;
}

const CCLuaValue CCLuaValue::stringValue(const std::string& stringValue)
{
    CCLuaValue value;
    value._type = CCLuaValueTypeString;
    value._field.stringValue = new std::string(stringValue);
    return value;
}

const CCLuaValue CCLuaValue::dictValue(const CCLuaValueDict& dictValue)
{
    CCLuaValue value;
    value._type = CCLuaValueTypeDict;
    value._field.dictValue = new CCLuaValueDict(dictValue);
    return value;
}

const CCLuaValue CCLuaValue::arrayValue(const CCLuaValueArray& arrayValue)
{
    CCLuaValue value;
    value._type = CCLuaValueTypeArray;
    value._field.arrayValue = new CCLuaValueArray(arrayValue);
    return value;
}

const CCLuaValue CCLuaValue::ccobjectValue(CCObject* ccobjectValue, const char* objectTypename)
{
    CCLuaValue value;
    value._type = CCLuaValueTypeCCObject;
    value._field.ccobjectValue = ccobjectValue;
    ccobjectValue->retain();
    value._ccobjectType = new std::string(objectTypename);
    return value;
}

const CCLuaValue CCLuaValue::ccobjectValue(CCObject* ccobjectValue, const std::string& objectTypename)
{
    return CCLuaValue::ccobjectValue(ccobjectValue, objectTypename.c_str());
}

CCLuaValue::CCLuaValue(const CCLuaValue& rhs)
{
    copy(rhs);
}

CCLuaValue& CCLuaValue::operator=(const CCLuaValue& rhs)
{
    if (this != &rhs) copy(rhs);
    return *this;
}

CCLuaValue::~CCLuaValue(void)
{
    if (_type == CCLuaValueTypeString)
    {
        delete _field.stringValue;
    }
    else if (_type == CCLuaValueTypeDict)
    {
        delete _field.dictValue;
    }
    else if (_type == CCLuaValueTypeArray)
    {
        delete _field.arrayValue;
    }
    else if (_type == CCLuaValueTypeCCObject)
    {
        _field.ccobjectValue->release();
        delete _ccobjectType;
    }
}

void CCLuaValue::copy(const CCLuaValue& rhs)
{
    memcpy(&_field, &rhs._field, sizeof(_field));
    _type = rhs._type;
    if (_type == CCLuaValueTypeString)
    {
        _field.stringValue = new std::string(*rhs._field.stringValue);
    }
    else if (_type == CCLuaValueTypeDict)
    {
        _field.dictValue = new CCLuaValueDict(*rhs._field.dictValue);
    }
    else if (_type == CCLuaValueTypeArray)
    {
        _field.arrayValue = new CCLuaValueArray(*rhs._field.arrayValue);
    }
    else if (_type == CCLuaValueTypeCCObject)
    {
        _field.ccobjectValue = rhs._field.ccobjectValue;
        _field.ccobjectValue->retain();
        _ccobjectType = new std::string(*rhs._ccobjectType);
    }
}

NS_CC_END
