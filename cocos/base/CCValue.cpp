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

#include "CCValue.h"
#include <sstream>

NS_CC_BEGIN

Value::Value()
: _vectorData(new ValueVector())
, _mapData(new ValueMap())
, _intKeyMapData(new IntValueMap())
, _type(Type::NONE)
{
    
}

Value::Value(int v)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(nullptr)
, _type(Type::INTEGER)
{
    _baseData.intVal = v;
}

Value::Value(float v)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(nullptr)
, _type(Type::FLOAT)
{
    _baseData.floatVal = v;
}

Value::Value(double v)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(nullptr)
, _type(Type::DOUBLE)
{
    _baseData.doubleVal = v;
}

Value::Value(bool v)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(nullptr)
, _type(Type::BOOLEAN)
{
    _baseData.boolVal = v;
}

Value::Value(const char* v)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(nullptr)
, _type(Type::STRING)
{
    _strData = v;
}

Value::Value(const std::string& v)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(nullptr)
, _type(Type::STRING)
{
    _strData = v;
}

Value::Value(const ValueVector& v)
: _vectorData(new ValueVector())
, _mapData(nullptr)
, _intKeyMapData(nullptr)
, _type(Type::VECTOR)
{
    *_vectorData = v;
}

Value::Value(ValueVector&& v)
: _vectorData(new ValueVector())
, _mapData(nullptr)
, _intKeyMapData(nullptr)
, _type(Type::VECTOR)
{
    *_vectorData = std::move(v);
}

Value::Value(const ValueMap& v)
: _vectorData(nullptr)
, _mapData(new ValueMap())
, _intKeyMapData(nullptr)
, _type(Type::MAP)
{
    *_mapData = v;
}

Value::Value(ValueMap&& v)
: _vectorData(nullptr)
, _mapData(new ValueMap())
, _intKeyMapData(nullptr)
, _type(Type::MAP)
{
    *_mapData = std::move(v);
}

Value::Value(const IntValueMap& v)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(new IntValueMap())
, _type(Type::INT_KEY_MAP)
{
    *_intKeyMapData = v;
}

Value::Value(IntValueMap&& v)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(new IntValueMap())
, _type(Type::INT_KEY_MAP)
{
    *_intKeyMapData = std::move(v);
}

Value::Value(const Value& other)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(nullptr)
{
    *this = other;
}

Value::Value(Value&& other)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(nullptr)
{
    *this = std::move(other);
}

Value::~Value()
{
    CC_SAFE_DELETE(_vectorData);
    CC_SAFE_DELETE(_mapData);
    CC_SAFE_DELETE(_intKeyMapData);
}

Value& Value::operator= (const Value& other)
{
    switch (other._type) {
        case Type::INTEGER:
            _baseData.intVal = other._baseData.intVal;
            break;
        case Type::FLOAT:
            _baseData.floatVal = other._baseData.floatVal;
            break;
        case Type::DOUBLE:
            _baseData.doubleVal = other._baseData.doubleVal;
            break;
        case Type::BOOLEAN:
            _baseData.boolVal = other._baseData.boolVal;
            break;
        case Type::STRING:
            _strData = other._strData;
            break;
        case Type::VECTOR:
            if (_vectorData == nullptr)
                _vectorData = new ValueVector();
            *_vectorData = *other._vectorData;
            break;
        case Type::MAP:
            if (_mapData == nullptr)
                _mapData = new ValueMap();
            *_mapData = *other._mapData;
            break;
        case Type::INT_KEY_MAP:
            if (_intKeyMapData == nullptr)
                _intKeyMapData = new IntValueMap();
            *_intKeyMapData = *other._intKeyMapData;
            break;
        default:
            break;
    }
    _type = other._type;
    return *this;
}

Value& Value::operator= (Value&& other)
{
    switch (other._type) {
        case Type::INTEGER:
            _baseData.intVal = other._baseData.intVal;
            break;
        case Type::FLOAT:
            _baseData.floatVal = other._baseData.floatVal;
            break;
        case Type::DOUBLE:
            _baseData.doubleVal = other._baseData.doubleVal;
            break;
        case Type::BOOLEAN:
            _baseData.boolVal = other._baseData.boolVal;
            break;
        case Type::STRING:
            _strData = other._strData;
            break;
        case Type::VECTOR:
            CC_SAFE_DELETE(_vectorData);
            _vectorData = other._vectorData;
            break;
        case Type::MAP:
            CC_SAFE_DELETE(_mapData);
            _mapData = other._mapData;
            break;
        case Type::INT_KEY_MAP:
            CC_SAFE_DELETE(_intKeyMapData);
            _intKeyMapData = other._intKeyMapData;
            break;
        default:
            break;
    }
    _type = other._type;
    
    other._vectorData = nullptr;
    other._mapData = nullptr;
    other._intKeyMapData = nullptr;
    other._type = Type::NONE;
    
    return *this;
}

int Value::asInt() const
{
    CCASSERT(_type != Type::VECTOR && _type != Type::MAP, "");
    if (_type == Type::INTEGER)
    {
        return _baseData.intVal;
    }
    
    if (_type == Type::STRING)
    {
        return atoi(_strData.c_str());
    }
    
    if (_type == Type::FLOAT)
    {
        return _baseData.floatVal;
    }
    
    if (_type == Type::DOUBLE)
    {
        return _baseData.doubleVal;
    }
    
    if (_type == Type::BOOLEAN)
    {
        return _baseData.boolVal;
    }
    
    return 0;
}

float Value::asFloat() const
{
    CCASSERT(_type != Type::VECTOR && _type != Type::MAP, "");
    if (_type == Type::FLOAT)
    {
        return _baseData.floatVal;
    }
    
    if (_type == Type::STRING)
    {
        return atof(_strData.c_str());
    }
    
    if (_type == Type::INTEGER)
    {
        return _baseData.intVal;
    }
    
    if (_type == Type::DOUBLE)
    {
        return _baseData.doubleVal;
    }
    
    if (_type == Type::BOOLEAN)
    {
        return _baseData.boolVal;
    }
    
    return 0.0f;
}

double Value::asDouble() const
{
    CCASSERT(_type != Type::VECTOR && _type != Type::MAP, "");
    if (_type == Type::DOUBLE)
    {
        return _baseData.doubleVal;
    }
    
    if (_type == Type::STRING)
    {
        return (float)atof(_strData.c_str());
    }
    
    if (_type == Type::INTEGER)
    {
        return _baseData.intVal;
    }
    
    if (_type == Type::FLOAT)
    {
        return _baseData.floatVal;
    }
    
    if (_type == Type::BOOLEAN)
    {
        return _baseData.boolVal;
    }
    
    return 0.0;
}

bool Value::asBool() const
{
    CCASSERT(_type != Type::VECTOR && _type != Type::MAP, "");
    if (_type == Type::BOOLEAN)
    {
        return _baseData.boolVal;
    }
    
    if (_type == Type::STRING)
    {
        return (_strData == "0" || _strData == "false") ? false : true;
    }
    
    if (_type == Type::INTEGER)
    {
        return _baseData.intVal == 0 ? false : true;
    }
    
    if (_type == Type::FLOAT)
    {
        return _baseData.floatVal == 0.0f ? false : true;
    }
    
    if (_type == Type::DOUBLE)
    {
        return _baseData.doubleVal == 0.0 ? false : true;
    }
    
    return true;
}

std::string Value::asString() const
{
    CCASSERT(_type != Type::VECTOR && _type != Type::MAP, "");
    
    if (_type == Type::STRING)
    {
        return _strData;
    }
    
    std::stringstream ret;
    
    switch (_type) {
        case Type::INTEGER:
            ret << _baseData.intVal;
            break;
        case Type::FLOAT:
            ret << _baseData.floatVal;
            break;
        case Type::DOUBLE:
            ret << _baseData.doubleVal;
            break;
        case Type::BOOLEAN:
            ret << _baseData.boolVal;
            break;
        default:
            break;
    }
    return ret.str();
}

NS_CC_END
