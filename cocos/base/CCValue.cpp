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

#include "CCValue.h"
#include <sstream>
#include <iomanip>

NS_CC_BEGIN

const Value Value::Null;

Value::Value()
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(nullptr)
, _type(Type::NONE)
{
    
}

Value::Value(unsigned char v)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(nullptr)
, _type(Type::BYTE)
{
    _baseData.byteVal = v;
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

Value::Value(const ValueMapIntKey& v)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(new ValueMapIntKey())
, _type(Type::INT_KEY_MAP)
{
    *_intKeyMapData = v;
}

Value::Value(ValueMapIntKey&& v)
: _vectorData(nullptr)
, _mapData(nullptr)
, _intKeyMapData(new ValueMapIntKey())
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
    clear();
}

Value& Value::operator= (const Value& other)
{
    if (this != &other) {
        switch (other._type) {
            case Type::BYTE:
                _baseData.byteVal = other._baseData.byteVal;
                break;
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
                    _intKeyMapData = new ValueMapIntKey();
                *_intKeyMapData = *other._intKeyMapData;
                break;
            default:
                break;
        }
        _type = other._type;
    }
    return *this;
}

Value& Value::operator= (Value&& other)
{
    if (this != &other) {
        switch (other._type) {
            case Type::BYTE:
                _baseData.byteVal = other._baseData.byteVal;
                break;
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
    }
    
    return *this;
}

Value& Value::operator= (unsigned char v)
{
    clear();
    _type = Type::BYTE;
    _baseData.byteVal = v;
    return *this;
}

Value& Value::operator= (int v)
{
    clear();
    _type = Type::INTEGER;
    _baseData.intVal = v;
    return *this;
}

Value& Value::operator= (float v)
{
    clear();
    _type = Type::FLOAT;
    _baseData.floatVal = v;
    return *this;
}

Value& Value::operator= (double v)
{
    clear();
    _type = Type::DOUBLE;
    _baseData.doubleVal = v;
    return *this;
}

Value& Value::operator= (bool v)
{
    clear();
    _type = Type::BOOLEAN;
    _baseData.boolVal = v;
    return *this;
}

Value& Value::operator= (const char* v)
{
    clear();
    _type = Type::STRING;
    _strData = v ? v : "";
    return *this;
}

Value& Value::operator= (const std::string& v)
{
    clear();
    _type = Type::STRING;
    _strData = v;
    return *this;
}

Value& Value::operator= (const ValueVector& v)
{
    clear();
    _type = Type::VECTOR;
    _vectorData = new ValueVector();
    *_vectorData = v;
    return *this;
}

Value& Value::operator= (ValueVector&& v)
{
    clear();
    _type = Type::VECTOR;
    _vectorData = new ValueVector();
    *_vectorData = std::move(v);
    return *this;
}

Value& Value::operator= (const ValueMap& v)
{
    clear();
    _type = Type::MAP;
    _mapData = new ValueMap();
    *_mapData = v;
    return *this;
}

Value& Value::operator= (ValueMap&& v)
{
    clear();
    _type = Type::MAP;
    _mapData = new ValueMap();
    *_mapData = std::move(v);
    return *this;
}

Value& Value::operator= (const ValueMapIntKey& v)
{
    clear();
    _type = Type::INT_KEY_MAP;
    _intKeyMapData = new ValueMapIntKey();
    *_intKeyMapData = v;
    return *this;
}

Value& Value::operator= (ValueMapIntKey&& v)
{
    clear();
    _type = Type::INT_KEY_MAP;
    _intKeyMapData = new ValueMapIntKey();
    *_intKeyMapData = std::move(v);
    return *this;
}

///
unsigned char Value::asByte() const
{
    CCASSERT(_type != Type::VECTOR && _type != Type::MAP, "");
    
    if (_type == Type::BYTE)
    {
        return _baseData.byteVal;
    }
    
    if (_type == Type::INTEGER)
    {
        return static_cast<unsigned char>(_baseData.intVal);
    }
    
    if (_type == Type::STRING)
    {
        return static_cast<unsigned char>(atoi(_strData.c_str()));
    }
    
    if (_type == Type::FLOAT)
    {
        return static_cast<unsigned char>(_baseData.floatVal);
    }
    
    if (_type == Type::DOUBLE)
    {
        return static_cast<unsigned char>(_baseData.doubleVal);
    }
    
    if (_type == Type::BOOLEAN)
    {
        return _baseData.boolVal ? 1 : 0;
    }
    
    return 0;
}

int Value::asInt() const
{
    CCASSERT(_type != Type::VECTOR && _type != Type::MAP, "");
    if (_type == Type::INTEGER)
    {
        return _baseData.intVal;
    }
    
    if (_type == Type::BYTE)
    {
        return _baseData.byteVal;
    }
    
    if (_type == Type::STRING)
    {
        return atoi(_strData.c_str());
    }
    
    if (_type == Type::FLOAT)
    {
        return static_cast<int>(_baseData.floatVal);
    }
    
    if (_type == Type::DOUBLE)
    {
        return static_cast<int>(_baseData.doubleVal);
    }
    
    if (_type == Type::BOOLEAN)
    {
        return _baseData.boolVal ? 1 : 0;
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
    
    if (_type == Type::BYTE)
    {
        return static_cast<float>(_baseData.byteVal);
    }
    
    if (_type == Type::STRING)
    {
        return atof(_strData.c_str());
    }
    
    if (_type == Type::INTEGER)
    {
        return static_cast<float>(_baseData.intVal);
    }
    
    if (_type == Type::DOUBLE)
    {
        return static_cast<float>(_baseData.doubleVal);
    }
    
    if (_type == Type::BOOLEAN)
    {
        return _baseData.boolVal ? 1.0f : 0.0f;
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
    
    if (_type == Type::BYTE)
    {
        return static_cast<double>(_baseData.byteVal);
    }
    
    if (_type == Type::STRING)
    {
        return static_cast<double>(atof(_strData.c_str()));
    }
    
    if (_type == Type::INTEGER)
    {
        return static_cast<double>(_baseData.intVal);
    }
    
    if (_type == Type::FLOAT)
    {
        return static_cast<double>(_baseData.floatVal);
    }
    
    if (_type == Type::BOOLEAN)
    {
        return _baseData.boolVal ? 1.0 : 0.0;
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
    
    if (_type == Type::BYTE)
    {
        return _baseData.byteVal == 0 ? false : true;
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
        case Type::BYTE:
            ret << _baseData.byteVal;
            break;
        case Type::INTEGER:
            ret << _baseData.intVal;
            break;
        case Type::FLOAT:
            ret << std::fixed << std::setprecision( 7 )<< _baseData.floatVal;
            break;
        case Type::DOUBLE:
            ret << std::fixed << std::setprecision( 16 ) << _baseData.doubleVal;
            break;
        case Type::BOOLEAN:
            ret << (_baseData.boolVal ? "true" : "false");
            break;
        default:
            break;
    }
    return ret.str();
}

ValueVector& Value::asValueVector()
{
	if (nullptr == _vectorData)
		_vectorData = new ValueVector();
	return *_vectorData;
}

const ValueVector& Value::asValueVector() const
{
	static const ValueVector EMPTY_VALUEVECTOR;
	if (nullptr == _vectorData)
		return EMPTY_VALUEVECTOR;
	return *_vectorData; 
}

ValueMap& Value::asValueMap()
{
	if (nullptr == _mapData)
		_mapData = new ValueMap();
	return *_mapData;
}

const ValueMap& Value::asValueMap() const
{
	static const ValueMap EMPTY_VALUEMAP;
	if (nullptr == _mapData)
		return EMPTY_VALUEMAP;
	return *_mapData;
}

ValueMapIntKey& Value::asIntKeyMap()
{
	if (nullptr == _intKeyMapData)
		_intKeyMapData = new ValueMapIntKey();
	return *_intKeyMapData;
}

const ValueMapIntKey& Value::asIntKeyMap() const
{
	static const ValueMapIntKey EMPTY_VALUEMAP_INT_KEY;
	if (nullptr == _intKeyMapData)
		return EMPTY_VALUEMAP_INT_KEY;
	return *_intKeyMapData;
}

static std::string getTabs(int depth)
{
    std::string tabWidth;
    
    for (int i = 0; i < depth; ++i)
    {
        tabWidth += "\t";
    }
    
    return tabWidth;
}

static std::string visit(const Value& v, int depth);

static std::string visitVector(const ValueVector& v, int depth)
{
    std::stringstream ret;
    
    if (depth > 0)
        ret << "\n";
    
    ret << getTabs(depth) << "[\n";
    
    int i = 0;
    for (const auto& child : v)
    {
        ret << getTabs(depth+1) << i << ": " << visit(child, depth + 1);
        ++i;
    }
    
    ret << getTabs(depth) << "]\n";
    
    return ret.str();
}

template <class T>
static std::string visitMap(const T& v, int depth)
{
    std::stringstream ret;
    
    if (depth > 0)
        ret << "\n";
    
    ret << getTabs(depth) << "{\n";
    
    for (auto iter = v.begin(); iter != v.end(); ++iter)
    {
        ret << getTabs(depth + 1) << iter->first << ": ";
        ret << visit(iter->second, depth + 1);
    }
    
    ret << getTabs(depth) << "}\n";
    
    return ret.str();
}

static std::string visit(const Value& v, int depth)
{
    std::stringstream ret;

    switch (v.getType())
    {
        case Value::Type::NONE:
        case Value::Type::BYTE:
        case Value::Type::INTEGER:
        case Value::Type::FLOAT:
        case Value::Type::DOUBLE:
        case Value::Type::BOOLEAN:
        case Value::Type::STRING:
            ret << v.asString() << "\n";
            break;
        case Value::Type::VECTOR:
            ret << visitVector(v.asValueVector(), depth);
            break;
        case Value::Type::MAP:
            ret << visitMap(v.asValueMap(), depth);
            break;
        case Value::Type::INT_KEY_MAP:
            ret << visitMap(v.asIntKeyMap(), depth);
            break;
        default:
            CCASSERT(false, "Invalid type!");
            break;
    }
    
    return ret.str();
}

std::string Value::getDescription()
{
    std::string ret("\n");
    ret += visit(*this, 0);
    return ret;
}

void Value::clear()
{
    _type = Type::NONE;
    _baseData.doubleVal = 0.0;
    _strData.clear();
    CC_SAFE_DELETE(_vectorData);
    CC_SAFE_DELETE(_mapData);
    CC_SAFE_DELETE(_intKeyMapData);
}

NS_CC_END
