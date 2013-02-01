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
    value.m_type = CCLuaValueTypeInt;
    value.m_field.intValue = intValue;
    return value;
}

const CCLuaValue CCLuaValue::floatValue(const float floatValue)
{
    CCLuaValue value;
    value.m_type = CCLuaValueTypeFloat;
    value.m_field.floatValue = floatValue;
    return value;
}

const CCLuaValue CCLuaValue::booleanValue(const bool booleanValue)
{
    CCLuaValue value;
    value.m_type = CCLuaValueTypeBoolean;
    value.m_field.booleanValue = booleanValue;
    return value;
}

const CCLuaValue CCLuaValue::stringValue(const char* stringValue)
{
    CCLuaValue value;
    value.m_type = CCLuaValueTypeString;
    value.m_field.stringValue = new std::string(stringValue ? stringValue : "");
    return value;
}

const CCLuaValue CCLuaValue::stringValue(const std::string& stringValue)
{
    CCLuaValue value;
    value.m_type = CCLuaValueTypeString;
    value.m_field.stringValue = new std::string(stringValue);
    return value;
}

const CCLuaValue CCLuaValue::dictValue(const CCLuaValueDict& dictValue)
{
    CCLuaValue value;
    value.m_type = CCLuaValueTypeDict;
    value.m_field.dictValue = new CCLuaValueDict(dictValue);
    return value;
}

const CCLuaValue CCLuaValue::arrayValue(const CCLuaValueArray& arrayValue)
{
    CCLuaValue value;
    value.m_type = CCLuaValueTypeArray;
    value.m_field.arrayValue = new CCLuaValueArray(arrayValue);
    return value;
}

const CCLuaValue CCLuaValue::ccobjectValue(CCObject* ccobjectValue, const char* objectTypename)
{
    CCLuaValue value;
    value.m_type = CCLuaValueTypeCCObject;
    value.m_field.ccobjectValue = ccobjectValue;
    ccobjectValue->retain();
    value.m_ccobjectType = new std::string(objectTypename);
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
    if (m_type == CCLuaValueTypeString)
    {
        delete m_field.stringValue;
    }
    else if (m_type == CCLuaValueTypeDict)
    {
        delete m_field.dictValue;
    }
    else if (m_type == CCLuaValueTypeArray)
    {
        delete m_field.arrayValue;
    }
    else if (m_type == CCLuaValueTypeCCObject)
    {
        m_field.ccobjectValue->release();
        delete m_ccobjectType;
    }
}

void CCLuaValue::copy(const CCLuaValue& rhs)
{
    memcpy(&m_field, &rhs.m_field, sizeof(m_field));
    m_type = rhs.m_type;
    if (m_type == CCLuaValueTypeString)
    {
        m_field.stringValue = new std::string(*rhs.m_field.stringValue);
    }
    else if (m_type == CCLuaValueTypeDict)
    {
        m_field.dictValue = new CCLuaValueDict(*rhs.m_field.dictValue);
    }
    else if (m_type == CCLuaValueTypeArray)
    {
        m_field.arrayValue = new CCLuaValueArray(*rhs.m_field.arrayValue);
    }
    else if (m_type == CCLuaValueTypeCCObject)
    {
        m_field.ccobjectValue = rhs.m_field.ccobjectValue;
        m_field.ccobjectValue->retain();
        m_ccobjectType = new std::string(*rhs.m_ccobjectType);
    }
}

NS_CC_END
