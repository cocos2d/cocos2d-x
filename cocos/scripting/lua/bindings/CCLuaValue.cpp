/****************************************************************************
 Copyright (c) 2011-2012 cocos2d-x.org
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

#include "CCLuaValue.h"


NS_CC_BEGIN

const LuaValue LuaValue::intValue(const int intValue)
{
    LuaValue value;
    value._type = LuaValueTypeInt;
    value._field.intValue = intValue;
    return value;
}

const LuaValue LuaValue::floatValue(const float floatValue)
{
    LuaValue value;
    value._type = LuaValueTypeFloat;
    value._field.floatValue = floatValue;
    return value;
}

const LuaValue LuaValue::booleanValue(const bool booleanValue)
{
    LuaValue value;
    value._type = LuaValueTypeBoolean;
    value._field.booleanValue = booleanValue;
    return value;
}

const LuaValue LuaValue::stringValue(const char* stringValue)
{
    LuaValue value;
    value._type = LuaValueTypeString;
    value._field.stringValue = new std::string(stringValue ? stringValue : "");
    return value;
}

const LuaValue LuaValue::stringValue(const std::string& stringValue)
{
    LuaValue value;
    value._type = LuaValueTypeString;
    value._field.stringValue = new std::string(stringValue);
    return value;
}

const LuaValue LuaValue::dictValue(const LuaValueDict& dictValue)
{
    LuaValue value;
    value._type = LuaValueTypeDict;
    value._field.dictValue = new LuaValueDict(dictValue);
    return value;
}

const LuaValue LuaValue::arrayValue(const LuaValueArray& arrayValue)
{
    LuaValue value;
    value._type = LuaValueTypeArray;
    value._field.arrayValue = new LuaValueArray(arrayValue);
    return value;
}

const LuaValue LuaValue::ccobjectValue(Ref* ccobjectValue, const char* objectTypename)
{
    LuaValue value;
    value._type = LuaValueTypeObject;
    value._field.ccobjectValue = ccobjectValue;
    ccobjectValue->retain();
    value._ccobjectType = new std::string(objectTypename);
    return value;
}

const LuaValue LuaValue::ccobjectValue(Ref* ccobjectValue, const std::string& objectTypename)
{
    return LuaValue::ccobjectValue(ccobjectValue, objectTypename.c_str());
}

LuaValue::LuaValue(const LuaValue& rhs)
{
    copy(rhs);
}

LuaValue& LuaValue::operator=(const LuaValue& rhs)
{
    if (this != &rhs) copy(rhs);
    return *this;
}

LuaValue::~LuaValue(void)
{
    if (_type == LuaValueTypeString)
    {
        delete _field.stringValue;
    }
    else if (_type == LuaValueTypeDict)
    {
        delete _field.dictValue;
    }
    else if (_type == LuaValueTypeArray)
    {
        delete _field.arrayValue;
    }
    else if (_type == LuaValueTypeObject)
    {
        _field.ccobjectValue->release();
        delete _ccobjectType;
    }
}

void LuaValue::copy(const LuaValue& rhs)
{
    memcpy(&_field, &rhs._field, sizeof(_field));
    _type = rhs._type;
    if (_type == LuaValueTypeString)
    {
        _field.stringValue = new std::string(*rhs._field.stringValue);
    }
    else if (_type == LuaValueTypeDict)
    {
        _field.dictValue = new LuaValueDict(*rhs._field.dictValue);
    }
    else if (_type == LuaValueTypeArray)
    {
        _field.arrayValue = new LuaValueArray(*rhs._field.arrayValue);
    }
    else if (_type == LuaValueTypeObject)
    {
        _field.ccobjectValue = rhs._field.ccobjectValue;
        _field.ccobjectValue->retain();
        _ccobjectType = new std::string(*rhs._ccobjectType);
    }
}

NS_CC_END
