/****************************************************************************
 Copyright (c) 2013-2017 Chukong Technologies

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

#include "base/CCValue.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include "base/ccUtils.h"

NS_CC_BEGIN

const ValueVector ValueVectorNull;
const ValueMap ValueMapNull;
const ValueMapIntKey ValueMapIntKeyNull;

const Value Value::Null;

Value::Value()
: _type(Type::NONE)
{
    memset(&_field, 0, sizeof(_field));
}

Value::Value(unsigned char v)
: _type(Type::BYTE)
{
    _field.byteVal = v;
}

Value::Value(short v)
: _type(Type::SHORT)
{
    _field.shortVal = v;
}

Value::Value(unsigned short v)
: _type(Type::UNSIGNED_SHORT)
{
    _field.unsignedShortVal = v;
}

Value::Value(int v)
: _type(Type::INTEGER)
{
    _field.intVal = v;
}

Value::Value(unsigned int v)
: _type(Type::UNSIGNED)
{
    _field.unsignedVal = v;
}

Value::Value(long v)
: _type(Type::LONG)
{
    _field.longVal = v;
}

Value::Value(unsigned long v)
: _type(Type::UNSIGNED_LONG)
{
    _field.unsignedLongVal = v;
}

Value::Value(long long v)
: _type(Type::LONG_LONG)
{
    _field.longLongVal = v;
}

Value::Value(unsigned long long v)
: _type(Type::UNSIGNED_LONG_LONG)
{
    _field.unsignedLongLongVal = v;
}

Value::Value(float v)
: _type(Type::FLOAT)
{
    _field.floatVal = v;
}

Value::Value(double v)
: _type(Type::DOUBLE)
{
    _field.doubleVal = v;
}

Value::Value(long double v)
: _type(Type::LONG_DOUBLE)
{
    _field.longDoubleVal = v;
}

Value::Value(bool v)
: _type(Type::BOOLEAN)
{
    _field.boolVal = v;
}

Value::Value(const char* v)
: _type(Type::STRING)
{
    _field.strVal = new (std::nothrow) std::string();
    if (v)
    {
        *_field.strVal = v;
    }
}

Value::Value(const std::string& v)
: _type(Type::STRING)
{
    _field.strVal = new (std::nothrow) std::string();
    *_field.strVal = v;
}

Value::Value(const ValueVector& v)
: _type(Type::VECTOR)
{
    _field.vectorVal = new (std::nothrow) ValueVector();
    *_field.vectorVal = v;
}

Value::Value(ValueVector&& v)
: _type(Type::VECTOR)
{
    _field.vectorVal = new (std::nothrow) ValueVector();
    *_field.vectorVal = std::move(v);
}

Value::Value(const ValueMap& v)
: _type(Type::MAP)
{
    _field.mapVal = new (std::nothrow) ValueMap();
    *_field.mapVal = v;
}

Value::Value(ValueMap&& v)
: _type(Type::MAP)
{
    _field.mapVal = new (std::nothrow) ValueMap();
    *_field.mapVal = std::move(v);
}

Value::Value(const ValueMapIntKey& v)
: _type(Type::INT_KEY_MAP)
{
    _field.intKeyMapVal = new (std::nothrow) ValueMapIntKey();
    *_field.intKeyMapVal = v;
}

Value::Value(ValueMapIntKey&& v)
: _type(Type::INT_KEY_MAP)
{
    _field.intKeyMapVal = new (std::nothrow) ValueMapIntKey();
    *_field.intKeyMapVal = std::move(v);
}

Value::Value(const Value& other)
: _type(Type::NONE)
{
    *this = other;
}

Value::Value(Value&& other)
: _type(Type::NONE)
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
        reset(other._type);

        switch (other._type) {
            case Type::BYTE:
                _field.byteVal = other._field.byteVal;
                break;
            case Type::SHORT:
                _field.shortVal = other._field.shortVal;
                break;
            case Type::UNSIGNED_SHORT:
                _field.unsignedShortVal = other._field.unsignedShortVal;
                break;
            case Type::INTEGER:
                _field.intVal = other._field.intVal;
                break;
            case Type::UNSIGNED:
                _field.unsignedVal = other._field.unsignedVal;
                break;
            case Type::LONG:
                _field.longVal = other._field.longVal;
                break;
            case Type::UNSIGNED_LONG:
                _field.unsignedLongVal = other._field.unsignedLongVal;
                break;
            case Type::LONG_LONG:
                _field.longLongVal = other._field.longLongVal;
                break;
            case Type::UNSIGNED_LONG_LONG:
                _field.unsignedLongLongVal = other._field.unsignedLongLongVal;
                break;
            case Type::FLOAT:
                _field.floatVal = other._field.floatVal;
                break;
            case Type::DOUBLE:
                _field.doubleVal = other._field.doubleVal;
                break;
            case Type::LONG_DOUBLE:
                _field.longDoubleVal = other._field.longDoubleVal;
                break;
            case Type::BOOLEAN:
                _field.boolVal = other._field.boolVal;
                break;
            case Type::STRING:
                if (_field.strVal == nullptr)
                {
                    _field.strVal = new std::string();
                }
                *_field.strVal = *other._field.strVal;
                break;
            case Type::VECTOR:
                if (_field.vectorVal == nullptr)
                {
                    _field.vectorVal = new (std::nothrow) ValueVector();
                }
                *_field.vectorVal = *other._field.vectorVal;
                break;
            case Type::MAP:
                if (_field.mapVal == nullptr)
                {
                    _field.mapVal = new (std::nothrow) ValueMap();
                }
                *_field.mapVal = *other._field.mapVal;
                break;
            case Type::INT_KEY_MAP:
                if (_field.intKeyMapVal == nullptr)
                {
                    _field.intKeyMapVal = new (std::nothrow) ValueMapIntKey();
                }
                *_field.intKeyMapVal = *other._field.intKeyMapVal;
                break;
            default:
                break;
        }
    }
    return *this;
}

Value& Value::operator= (Value&& other)
{
    if (this != &other)
    {
        clear();
        switch (other._type)
        {
            case Type::BYTE:
                _field.byteVal = other._field.byteVal;
                break;
            case Type::SHORT:
                _field.shortVal = other._field.shortVal;
                break;
            case Type::UNSIGNED_SHORT:
                _field.unsignedShortVal = other._field.unsignedShortVal;
                break;
            case Type::INTEGER:
                _field.intVal = other._field.intVal;
                break;
            case Type::UNSIGNED:
                _field.unsignedVal = other._field.unsignedVal;
                break;
            case Type::LONG:
                _field.longVal = other._field.longVal;
                break;
            case Type::UNSIGNED_LONG:
                _field.unsignedLongVal = other._field.unsignedLongVal;
                break;
            case Type::LONG_LONG:
                _field.longLongVal = other._field.longLongVal;
                break;
            case Type::UNSIGNED_LONG_LONG:
                _field.unsignedLongLongVal = other._field.unsignedLongLongVal;
                break;
            case Type::FLOAT:
                _field.floatVal = other._field.floatVal;
                break;
            case Type::DOUBLE:
                _field.doubleVal = other._field.doubleVal;
                break;
            case Type::LONG_DOUBLE:
                _field.longDoubleVal = other._field.longDoubleVal;
                break;
            case Type::BOOLEAN:
                _field.boolVal = other._field.boolVal;
                break;
            case Type::STRING:
                _field.strVal = other._field.strVal;
                break;
            case Type::VECTOR:
                _field.vectorVal = other._field.vectorVal;
                break;
            case Type::MAP:
                _field.mapVal = other._field.mapVal;
                break;
            case Type::INT_KEY_MAP:
                _field.intKeyMapVal = other._field.intKeyMapVal;
                break;
            default:
                break;
        }
        _type = other._type;

        memset(&other._field, 0, sizeof(other._field));
        other._type = Type::NONE;
    }

    return *this;
}

Value& Value::operator= (unsigned char v)
{
    reset(Type::BYTE);
    _field.byteVal = v;
    return *this;
}

Value& Value::operator= (short v)
{
    reset(Type::SHORT);
    _field.shortVal = v;
    return *this;
}

Value& Value::operator= (unsigned short v)
{
    reset(Type::UNSIGNED_SHORT);
    _field.unsignedShortVal = v;
    return *this;
}

Value& Value::operator= (int v)
{
    reset(Type::INTEGER);
    _field.intVal = v;
    return *this;
}

Value& Value::operator= (unsigned int v)
{
    reset(Type::UNSIGNED);
    _field.unsignedVal = v;
    return *this;
}

Value& Value::operator= (long v)
{
    reset(Type::LONG);
    _field.longVal = v;
    return *this;
}


Value& Value::operator= (unsigned long v)
{
    reset(Type::UNSIGNED_LONG);
    _field.unsignedLongVal = v;
    return *this;
}

Value& Value::operator= (long long v)
{
    reset(Type::LONG_LONG);
    _field.longLongVal = v;
    return *this;
}


Value& Value::operator= (unsigned long long v)
{
    reset(Type::UNSIGNED_LONG_LONG);
    _field.unsignedLongLongVal = v;
    return *this;
}

Value& Value::operator= (float v)
{
    reset(Type::FLOAT);
    _field.floatVal = v;
    return *this;
}

Value& Value::operator= (double v)
{
    reset(Type::DOUBLE);
    _field.doubleVal = v;
    return *this;
}

Value& Value::operator= (long double v)
{
    reset(Type::LONG_DOUBLE);
    _field.longDoubleVal = v;
    return *this;
}

Value& Value::operator= (bool v)
{
    reset(Type::BOOLEAN);
    _field.boolVal = v;
    return *this;
}

Value& Value::operator= (const char* v)
{
    reset(Type::STRING);
    *_field.strVal = v ? v : "";
    return *this;
}

Value& Value::operator= (const std::string& v)
{
    reset(Type::STRING);
    *_field.strVal = v;
    return *this;
}

Value& Value::operator= (const ValueVector& v)
{
    reset(Type::VECTOR);
    *_field.vectorVal = v;
    return *this;
}

Value& Value::operator= (ValueVector&& v)
{
    reset(Type::VECTOR);
    *_field.vectorVal = std::move(v);
    return *this;
}

Value& Value::operator= (const ValueMap& v)
{
    reset(Type::MAP);
    *_field.mapVal = v;
    return *this;
}

Value& Value::operator= (ValueMap&& v)
{
    reset(Type::MAP);
    *_field.mapVal = std::move(v);
    return *this;
}

Value& Value::operator= (const ValueMapIntKey& v)
{
    reset(Type::INT_KEY_MAP);
    *_field.intKeyMapVal = v;
    return *this;
}

Value& Value::operator= (ValueMapIntKey&& v)
{
    reset(Type::INT_KEY_MAP);
    *_field.intKeyMapVal = std::move(v);
    return *this;
}

bool Value::operator!= (const Value& v)
{
    return !(*this == v);
}
bool Value::operator!= (const Value& v) const
{
    return !(*this == v);
}

bool Value::operator== (const Value& v)
{
    const auto &t = *this;
    return t == v;
}
bool Value::operator== (const Value& v) const
{
    if (this == &v) return true;
    if (v._type != this->_type) return false;
    if (this->isNull()) return true;
    switch (_type)
    {
        case Type::BYTE:                return v._field.byteVal             == this->_field.byteVal;
        case Type::SHORT:               return v._field.shortVal            == this->_field.shortVal;
        case Type::UNSIGNED_SHORT:      return v._field.unsignedShortVal    == this->_field.unsignedShortVal;
        case Type::INTEGER:             return v._field.intVal              == this->_field.intVal;
        case Type::UNSIGNED:            return v._field.unsignedVal         == this->_field.unsignedVal;
        case Type::LONG:                return v._field.longVal             == this->_field.longVal;
        case Type::UNSIGNED_LONG:       return v._field.unsignedLongVal     == this->_field.unsignedLongVal;
        case Type::LONG_LONG:           return v._field.longLongVal         == this->_field.longLongVal;
        case Type::UNSIGNED_LONG_LONG:  return v._field.unsignedLongLongVal == this->_field.unsignedLongLongVal;
        case Type::BOOLEAN:             return v._field.boolVal             == this->_field.boolVal;
        case Type::STRING:              return *v._field.strVal             == *this->_field.strVal;
        case Type::FLOAT:               return std::abs(v._field.floatVal       - this->_field.floatVal)        <= FLT_EPSILON;
        case Type::DOUBLE:              return std::abs(v._field.doubleVal      - this->_field.doubleVal)       <= DBL_EPSILON;
        case Type::LONG_DOUBLE:         return std::abs(v._field.longDoubleVal  - this->_field.longDoubleVal)   <= LDBL_EPSILON;
        case Type::VECTOR:
        {
            const auto &v1 = *(this->_field.vectorVal);
            const auto &v2 = *(v._field.vectorVal);
            const auto size = v1.size();
            if (size == v2.size())
            {
                for (size_t i = 0; i < size; i++)
                {
                    if (v1[i] != v2[i]) return false;
                }
                return true;
            }
            return false;
        }
        case Type::MAP:
        {
            const auto &map1 = *(this->_field.mapVal);
            const auto &map2 = *(v._field.mapVal);
            for (const auto &kvp : map1)
            {
                auto it = map2.find(kvp.first);
                if (it == map2.end() || it->second != kvp.second)
                {
                    return false;
                }
            }
            return true;
        }
        case Type::INT_KEY_MAP:
        {
            const auto &map1 = *(this->_field.intKeyMapVal);
            const auto &map2 = *(v._field.intKeyMapVal);
            for (const auto &kvp : map1)
            {
                auto it = map2.find(kvp.first);
                if (it == map2.end() || it->second != kvp.second)
                {
                    return false;
                }
            }
            return true;
        }
        default:
            break;
    };

    return false;
}

/// Convert value to a specified type
unsigned char Value::asByte() const
{
    CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");

    switch ( _type )
    {
        case Type::BYTE:
            return _field.byteVal;
            break;
            
        case Type::SHORT:
            return static_cast<unsigned char>(_field.shortVal);
            break;
            
        case Type::UNSIGNED_SHORT:
            return static_cast<unsigned char>(_field.unsignedShortVal);
            break;
            
        case Type::INTEGER:
            return static_cast<unsigned char>(_field.intVal);
            break;
            
        case Type::UNSIGNED:
            return static_cast<unsigned char>(_field.unsignedVal);
            break;
            
        case Type::LONG:
            return static_cast<unsigned char>(_field.longVal);
            break;
            
        case Type::UNSIGNED_LONG:
            return static_cast<unsigned char>(_field.unsignedLongVal);
            break;
    
        case Type::LONG_LONG:
            return static_cast<unsigned char>(_field.longLongVal);
            break;
            
        case Type::UNSIGNED_LONG_LONG:
            return static_cast<unsigned char>(_field.unsignedLongLongVal);
            break;
            
        case Type::STRING:
            return static_cast<unsigned char>(atoi(_field.strVal->c_str()));
            break;
            
        case Type::FLOAT:
            return static_cast<unsigned char>(_field.floatVal);
            break;
            
        case Type::DOUBLE:
            return static_cast<unsigned char>(_field.doubleVal);
            break;
            
        case Type::LONG_DOUBLE:
            return static_cast<unsigned char>(_field.longDoubleVal);
            break;
            
        case Type::BOOLEAN:
            return _field.boolVal ? 1 : 0;
            break;
            
        case Type::NONE:
        case Type::VECTOR:
        case Type::MAP:
        case Type::INT_KEY_MAP:
            return 0;
            break;
    }
}

short Value::asShort() const
{
    CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");
    
    switch ( _type )
    {
        case Type::BYTE:
            return static_cast<short>(_field.byteVal);
            break;
            
        case Type::SHORT:
            return _field.shortVal;
            break;
            
        case Type::UNSIGNED_SHORT:
        {
            CCASSERT(_field.unsignedShortVal < SHRT_MAX, "Can only convert values < SHRT_MAX");
            return (short)_field.unsignedShortVal;
            break;
        }
            
        case Type::INTEGER:
        {
            CCASSERT(_field.intVal < SHRT_MAX, "Can only convert values < SHRT_MAX");
            return (short)_field.intVal;
            break;
        }
            
        case Type::UNSIGNED:
        {
            CCASSERT(_field.unsignedVal < SHRT_MAX, "Can only convert values < SHRT_MAX");
            return (short)_field.unsignedVal;
            break;
        }
            
        case Type::LONG:
        {
            CCASSERT(_field.longVal < SHRT_MAX, "Can only convert values < SHRT_MAX");
            return (short)_field.longVal;
            break;
        }
            
        case Type::UNSIGNED_LONG:
        {
            CCASSERT(_field.unsignedLongVal < SHRT_MAX, "Can only convert values < SHRT_MAX");
            return (short)_field.unsignedLongVal;
            break;
        }
            
        case Type::LONG_LONG:
        {
            CCASSERT(_field.longLongVal < SHRT_MAX, "Can only convert values < SHRT_MAX");
            return (short)_field.longLongVal;
            break;
        }
        case Type::UNSIGNED_LONG_LONG:
        {
            CCASSERT(_field.unsignedLongLongVal < SHRT_MAX, "Can only convert values < SHRT_MAX");
            return (short)_field.unsignedLongLongVal;
            break;
        }
            
        case Type::STRING:
            return static_cast<short>(atoi(_field.strVal->c_str()));
            break;
            
        case Type::FLOAT:
            return static_cast<short>(_field.floatVal);
            break;
            
        case Type::DOUBLE:
            return static_cast<short>(_field.doubleVal);
            break;
            
        case Type::LONG_DOUBLE:
            return static_cast<short>(_field.longDoubleVal);
            break;
            
        case Type::BOOLEAN:
            return _field.boolVal ? 1 : 0;
            break;
            
        case Type::NONE:
        case Type::VECTOR:
        case Type::MAP:
        case Type::INT_KEY_MAP:
            return 0;
            break;
    }
}

unsigned short Value::asUnsignedShort() const
{
    CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");
    
    switch ( _type )
    {
        case Type::BYTE:
            return static_cast<unsigned short>(_field.byteVal);
            break;
            
        case Type::SHORT:
        {
            CCASSERT(_field.shortVal >= 0, "Only values >= 0 can be converted to unsigned short");
            return static_cast<unsigned short>(_field.shortVal);
            break;
        }
            
        case Type::UNSIGNED_SHORT:
            return _field.unsignedShortVal;
            break;
            
        case Type::INTEGER:
        {
            CCASSERT(_field.intVal >= 0, "Only values >= 0 can be converted to unsigned short");
            CCASSERT(_field.intVal < USHRT_MAX, "Can only convert values < USHRT_MAX");
            return (unsigned short)_field.intVal;
            break;
        }
            
        case Type::UNSIGNED:
        {
            CCASSERT(_field.unsignedVal < USHRT_MAX, "Can only convert values < USHRT_MAX");
            return (unsigned short)_field.unsignedVal;
            break;
        }
            
        case Type::LONG:
        {
            CCASSERT(_field.longVal >= 0, "Only values >= 0 can be converted to unsigned short");
            CCASSERT(_field.longVal < USHRT_MAX, "Can only convert values < USHRT_MAX");
            return (unsigned short)_field.longVal;
            break;
        }
            
        case Type::UNSIGNED_LONG:
        {
            CCASSERT(_field.unsignedLongVal < USHRT_MAX, "Can only convert values < USHRT_MAX");
            return (unsigned short)_field.unsignedLongVal;
            break;
        }
            
        case Type::LONG_LONG:
        {
            CCASSERT(_field.longLongVal >= 0, "Only values >= 0 can be converted to unsigned short");
            CCASSERT(_field.longLongVal < USHRT_MAX, "Can only convert values < USHRT_MAX");
            return (unsigned short)_field.longLongVal;
            break;
        }
        case Type::UNSIGNED_LONG_LONG:
        {
            CCASSERT(_field.unsignedLongLongVal < USHRT_MAX, "Can only convert values < USHRT_MAX");
            return (unsigned short)_field.unsignedLongLongVal;
            break;
        }
            
        case Type::STRING:
            return static_cast<unsigned short>(atoi(_field.strVal->c_str()));
            break;
            
        case Type::FLOAT:
            return static_cast<unsigned short>(_field.floatVal);
            break;
            
        case Type::DOUBLE:
            return static_cast<unsigned short>(_field.doubleVal);
            break;
            
        case Type::LONG_DOUBLE:
            return static_cast<unsigned short>(_field.longDoubleVal);
            break;
            
        case Type::BOOLEAN:
            return _field.boolVal ? 1u : 0u;
            break;
            
        case Type::NONE:
        case Type::VECTOR:
        case Type::MAP:
        case Type::INT_KEY_MAP:
            return 0u;
            break;
    }
}

int Value::asInt() const
{
    CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");
    
    switch ( _type )
    {
        case Type::BYTE:
            return static_cast<int>(_field.byteVal);
            break;
            
        case Type::SHORT:
            return static_cast<int>(_field.shortVal);
            break;
            
        case Type::UNSIGNED_SHORT:
            return static_cast<int>(_field.unsignedShortVal);
            break;
            
        case Type::INTEGER:
            return _field.intVal;
            break;
            
        case Type::UNSIGNED:
        {
            CCASSERT(_field.unsignedVal < INT_MAX, "Can only convert values < INT_MAX");
            return (int)_field.unsignedVal;
            break;
        }
            
        case Type::LONG:
        {
            CCASSERT(_field.longVal < INT_MAX, "Can only convert values < INT_MAX");
            return (int)_field.longVal;
            break;
        }
            
        case Type::UNSIGNED_LONG:
        {
            CCASSERT(_field.unsignedLongVal < INT_MAX, "Can only convert values < INT_MAX");
            return (int)_field.unsignedLongVal;
            break;
        }
            
        case Type::LONG_LONG:
        {
            CCASSERT(_field.longLongVal < INT_MAX, "Can only convert values < INT_MAX");
            return (int)_field.longLongVal;
            break;
        }
            
        case Type::UNSIGNED_LONG_LONG:
        {
            CCASSERT(_field.unsignedLongLongVal < INT_MAX, "Can only convert values < INT_MAX");
            return (int)_field.unsignedLongLongVal;
            break;
        }
            
        case Type::STRING:
            return atoi(_field.strVal->c_str());
            break;
            
        case Type::FLOAT:
            return static_cast<int>(_field.floatVal);
            break;
            
        case Type::DOUBLE:
            return static_cast<int>(_field.doubleVal);
            break;
            
        case Type::LONG_DOUBLE:
            return static_cast<int>(_field.longDoubleVal);
            break;
            
        case Type::BOOLEAN:
            return _field.boolVal ? 1 : 0;
            break;
            
        case Type::NONE:
        case Type::VECTOR:
        case Type::MAP:
        case Type::INT_KEY_MAP:
            return 0;
            break;
    }
}

unsigned int Value::asUnsignedInt() const
{
    CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");
    
    switch ( _type )
    {
        case Type::BYTE:
            return static_cast<unsigned int>(_field.byteVal);
            break;
            
        case Type::SHORT:
        {
            CCASSERT(_field.shortVal >= 0, "Only values >= 0 can be converted to unsigned");
            return (unsigned int)_field.shortVal;
            break;
        }
            
        case Type::UNSIGNED_SHORT:
            return static_cast<unsigned int>(_field.unsignedShortVal);
            break;
            
        case Type::INTEGER:
        {
            CCASSERT(_field.intVal >= 0, "Only values >= 0 can be converted to unsigned");
            return (unsigned int)_field.intVal;
            break;
        }
            
        case Type::UNSIGNED:
            return _field.unsignedVal;
            break;
            
        case Type::LONG:
        {
            CCASSERT(_field.longVal >= 0, "Only values >= 0 can be converted to unsigned");
            CCASSERT(_field.longVal < UINT_MAX, "Can only convert values < UINT_MAX");
            return (unsigned int)_field.longVal;
            break;
        }
            
        case Type::UNSIGNED_LONG:
        {
            CCASSERT(_field.unsignedLongVal < UINT_MAX, "Can only convert values < UINT_MAX");
            return (unsigned int)_field.unsignedLongVal;
            break;
        }
            
        case Type::LONG_LONG:
        {
            CCASSERT(_field.longLongVal >= 0, "Only values >= 0 can be converted to unsigned");
            CCASSERT(_field.longLongVal < UINT_MAX, "Can only convert values < UINT_MAX");
            return (unsigned int)_field.longLongVal;
            break;
        }
            
        case Type::UNSIGNED_LONG_LONG:
        {
            CCASSERT(_field.unsignedLongLongVal < UINT_MAX, "Can only convert values < UINT_MAX");
            return (unsigned int)_field.unsignedLongLongVal;
            break;
        }
            
        case Type::STRING:
            return static_cast<unsigned int>(strtoul(_field.strVal->c_str(), nullptr, 10));
            break;
            
        case Type::FLOAT:
            return static_cast<unsigned int>(_field.floatVal);
            break;
            
        case Type::DOUBLE:
            return static_cast<unsigned int>(_field.doubleVal);
            break;
            
        case Type::LONG_DOUBLE:
            return static_cast<unsigned int>(_field.longDoubleVal);
            break;
            
        case Type::BOOLEAN:
            return _field.boolVal ? 1u : 0u;
            break;
            
        case Type::NONE:
        case Type::VECTOR:
        case Type::MAP:
        case Type::INT_KEY_MAP:
            return 0u;
            break;
    }
}

long Value::asLong() const
{
    CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");
    
    switch ( _type )
    {
        case Type::BYTE:
            return static_cast<long>(_field.byteVal);
            break;
            
        case Type::SHORT:
            return static_cast<long>(_field.shortVal);
            break;
            
        case Type::UNSIGNED_SHORT:
            return static_cast<long>(_field.unsignedShortVal);
            break;
            
        case Type::INTEGER:
            return static_cast<long>(_field.intVal);
            break;
            
        case Type::UNSIGNED:
            return static_cast<long>(_field.unsignedVal);
            break;
            
        case Type::LONG:
            return _field.longVal;
            break;
            
        case Type::UNSIGNED_LONG:
        {
            CCASSERT(_field.unsignedLongVal < LONG_MAX, "Can only convert values < LONG_MAX");
            return (long)_field.unsignedLongVal;
            break;
        }
            
        case Type::LONG_LONG:
        {
            CCASSERT(_field.longLongVal < LONG_MAX, "Can only convert values < LONG_MAX");
            return (long)_field.longLongVal;
            break;
        }
            
        case Type::UNSIGNED_LONG_LONG:
        {
            CCASSERT(_field.unsignedLongLongVal < LONG_MAX, "Can only convert values < LONG_MAX");
            return (long)_field.unsignedLongLongVal;
            break;
        }
            
        case Type::STRING:
            return strtol(_field.strVal->c_str(), nullptr, 10);
            break;
            
        case Type::FLOAT:
            return static_cast<long>(_field.floatVal);
            break;
            
        case Type::DOUBLE:
            return static_cast<long>(_field.doubleVal);
            break;
            
        case Type::LONG_DOUBLE:
            return static_cast<long>(_field.longDoubleVal);
            break;
            
        case Type::BOOLEAN:
            return _field.boolVal ? 1l : 0l;
            break;
            
        case Type::NONE:
        case Type::VECTOR:
        case Type::MAP:
        case Type::INT_KEY_MAP:
            return 0l;
            break;
    }
}

unsigned long Value::asUnsignedLong() const
{
    CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");
    
    switch ( _type )
    {
        case Type::BYTE:
            return static_cast<unsigned long>(_field.byteVal);
            break;
            
        case Type::SHORT:
        {
            CCASSERT(_field.shortVal >= 0, "Only values >= 0 can be converted to unsigned long");
            return (unsigned long)_field.shortVal;
            break;
        }
            
        case Type::UNSIGNED_SHORT:
            return static_cast<unsigned long>(_field.unsignedShortVal);
            break;
            
        case Type::INTEGER:
        {
            CCASSERT(_field.intVal >= 0, "Only values >= 0 can be converted to unsigned long");
            return (unsigned long)_field.intVal;
            break;
        }
            
        case Type::UNSIGNED:
            return static_cast<unsigned long>(_field.unsignedVal);
            break;
            
        case Type::LONG:
        {
            CCASSERT(_field.longVal >= 0, "Only values >= 0 can be converted to unsigned long");
            return (long)_field.longVal;
            break;
        }
            
        case Type::UNSIGNED_LONG:
            return _field.unsignedLongVal;
            break;
            
        case Type::LONG_LONG:
        {
            CCASSERT(_field.longLongVal >= 0, "Only values >= 0 can be converted to unsigned long");
            CCASSERT(_field.longLongVal < LONG_MAX, "Can only convert values < LONG_MAX");
            return (unsigned long)_field.longLongVal;
            break;
        }
            
        case Type::UNSIGNED_LONG_LONG:
        {
            CCASSERT(_field.unsignedLongLongVal >= 0, "Only values >= 0 can be converted to unsigned long");
            CCASSERT(_field.unsignedLongLongVal < LONG_MAX, "Can only convert values < LONG_MAX");
            return (unsigned long)_field.unsignedLongLongVal;
            break;
        }
            
        case Type::STRING:
            return strtoul(_field.strVal->c_str(), nullptr, 10);
            break;
            
        case Type::FLOAT:
            return static_cast<unsigned long>(_field.floatVal);
            break;
            
        case Type::DOUBLE:
            return static_cast<unsigned long>(_field.doubleVal);
            break;
            
        case Type::LONG_DOUBLE:
            return static_cast<unsigned long>(_field.longDoubleVal);
            break;
            
        case Type::BOOLEAN:
            return _field.boolVal ? 1ul : 0ul;
            break;
            
        case Type::NONE:
        case Type::VECTOR:
        case Type::MAP:
        case Type::INT_KEY_MAP:
            return 0ul;
            break;
    }
}

long long Value::asLongLong() const
{
    CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");
    
    switch ( _type )
    {
        case Type::BYTE:
            return static_cast<long long>(_field.byteVal);
            break;
            
        case Type::SHORT:
            return static_cast<long long>(_field.shortVal);
            break;
            
        case Type::UNSIGNED_SHORT:
            return static_cast<long long>(_field.unsignedShortVal);
            break;
            
        case Type::INTEGER:
            return static_cast<long long>(_field.intVal);
            break;
            
        case Type::UNSIGNED:
            return static_cast<long long>(_field.unsignedVal);
            break;
            
        case Type::LONG:
            return static_cast<long long>(_field.longVal);
            break;
            
        case Type::UNSIGNED_LONG:
            return static_cast<long long>(_field.unsignedLongVal);
            break;
            
        case Type::LONG_LONG:
            return _field.longLongVal;
            break;
            
        case Type::UNSIGNED_LONG_LONG:
        {
            CCASSERT(_field.unsignedLongLongVal < LLONG_MAX, "Can only convert values < LLONG_MAX");
            return (long long)_field.unsignedLongLongVal;
            break;
        }
            
        case Type::STRING:
            return strtoll(_field.strVal->c_str(), nullptr, 10);
            break;
            
        case Type::FLOAT:
            return static_cast<long long>(_field.floatVal);
            break;
            
        case Type::DOUBLE:
            return static_cast<long long>(_field.doubleVal);
            break;
            
        case Type::LONG_DOUBLE:
            return static_cast<long long>(_field.longDoubleVal);
            break;
            
        case Type::BOOLEAN:
            return _field.boolVal ? 1ll : 0ll;
            break;
            
        case Type::NONE:
        case Type::VECTOR:
        case Type::MAP:
        case Type::INT_KEY_MAP:
            return 0ll;
            break;
    }
}

unsigned long long Value::asUnsignedLongLong() const
{
    CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");
    
    switch ( _type )
    {
        case Type::BYTE:
            return static_cast<unsigned long long>(_field.byteVal);
            break;
            
        case Type::SHORT:
        {
            CCASSERT(_field.shortVal >= 0, "Only values >= 0 can be converted to unsigned long long");
            return (unsigned long long)_field.shortVal;
            break;
        }
            
        case Type::UNSIGNED_SHORT:
            return static_cast<unsigned long long>(_field.unsignedShortVal);
            break;
            
        case Type::INTEGER:
        {
            CCASSERT(_field.intVal >= 0, "Only values >= 0 can be converted to unsigned long long");
            return (unsigned long long)_field.intVal;
            break;
        }
            
        case Type::UNSIGNED:
            return static_cast<unsigned long long>(_field.unsignedVal);
            break;
            
        case Type::LONG:
        {
            CCASSERT(_field.longVal >= 0, "Only values >= 0 can be converted to unsigned long long");
            return (long long)_field.longVal;
            break;
        }
            
        case Type::UNSIGNED_LONG:
            return static_cast<unsigned long long>(_field.unsignedLongVal);
            break;
            
        case Type::LONG_LONG:
        {
            CCASSERT(_field.longLongVal >= 0, "Only values >= 0 can be converted to unsigned long long");
            CCASSERT(_field.longLongVal < LLONG_MAX, "Can only convert values < LLONG_MAX");
            return (unsigned long long)_field.longLongVal;
            break;
        }
            
        case Type::UNSIGNED_LONG_LONG:
            return _field.unsignedLongLongVal;
            break;
            
        case Type::STRING:
            return strtoull(_field.strVal->c_str(), nullptr, 10);
            break;
            
        case Type::FLOAT:
            return static_cast<unsigned long long>(_field.floatVal);
            break;
            
        case Type::DOUBLE:
            return static_cast<unsigned long long>(_field.doubleVal);
            break;
            
        case Type::LONG_DOUBLE:
            return static_cast<unsigned long long>(_field.longDoubleVal);
            break;
            
        case Type::BOOLEAN:
            return _field.boolVal ? 1ull : 0ull;
            break;
            
        case Type::NONE:
        case Type::VECTOR:
        case Type::MAP:
        case Type::INT_KEY_MAP:
            return 0ull;
            break;
    }
}

float Value::asFloat() const
{
    CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");
    
    switch ( _type )
    {
        case Type::BYTE:
            return static_cast<float>(_field.byteVal);
            break;
            
        case Type::SHORT:
            return static_cast<float>(_field.shortVal);
            break;
            
        case Type::UNSIGNED_SHORT:
            return static_cast<float>(_field.unsignedShortVal);
            break;
            
        case Type::INTEGER:
            return static_cast<float>(_field.intVal);
            break;
            
        case Type::UNSIGNED:
            return static_cast<float>(_field.unsignedVal);
            break;
            
        case Type::LONG:
            return static_cast<float>(_field.longVal);
            break;
            
        case Type::UNSIGNED_LONG:
            return static_cast<float>(_field.unsignedLongVal);
            break;
            
        case Type::LONG_LONG:
            return static_cast<float>(_field.longLongVal);
            break;
            
        case Type::UNSIGNED_LONG_LONG:
            return static_cast<float>(_field.unsignedLongLongVal);
            break;
            
        case Type::STRING:
            return utils::atof(_field.strVal->c_str());
            break;
            
        case Type::FLOAT:
            return _field.floatVal;
            break;
            
        case Type::DOUBLE:
        {
            CCASSERT(_field.doubleVal < FLT_MAX, "Can only convert values < FLT_MAX");
            return static_cast<float>(_field.doubleVal);
            break;
        }
        
        case Type::LONG_DOUBLE:
        {
            CCASSERT(_field.longDoubleVal < FLT_MAX, "Can only convert values < FLT_MAX");
            return static_cast<float>(_field.longDoubleVal);
            break;
        }
            
        case Type::BOOLEAN:
            return _field.boolVal ? 1.0f : 0.0f;
            break;
            
        case Type::NONE:
        case Type::VECTOR:
        case Type::MAP:
        case Type::INT_KEY_MAP:
            return 0.0f;
            break;
    }
}

double Value::asDouble() const
{
    CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");
    
    switch ( _type )
    {
        case Type::BYTE:
            return static_cast<double>(_field.byteVal);
            break;
            
        case Type::SHORT:
            return static_cast<double>(_field.shortVal);
            break;
            
        case Type::UNSIGNED_SHORT:
            return static_cast<double>(_field.unsignedShortVal);
            break;
            
        case Type::INTEGER:
            return static_cast<double>(_field.intVal);
            break;
            
        case Type::UNSIGNED:
            return static_cast<double>(_field.unsignedVal);
            break;
            
        case Type::LONG:
            return static_cast<double>(_field.longVal);
            break;
            
        case Type::UNSIGNED_LONG:
            return static_cast<double>(_field.unsignedLongVal);
            break;
            
        case Type::LONG_LONG:
            return static_cast<double>(_field.longLongVal);
            break;
            
        case Type::UNSIGNED_LONG_LONG:
            return static_cast<double>(_field.unsignedLongLongVal);
            break;
            
        case Type::STRING:
            return utils::atof(_field.strVal->c_str());
            break;
            
        case Type::FLOAT:
            return static_cast<double>(_field.floatVal);
            break;
            
        case Type::DOUBLE:
            return _field.doubleVal;
            break;
            
        case Type::LONG_DOUBLE:
        {
            CCASSERT(_field.longDoubleVal < DBL_MAX, "Can only convert values < DBL_MAX");
            return static_cast<double>(_field.longDoubleVal);
            break;
        }
        
        case Type::BOOLEAN:
            return _field.boolVal ? 1.0 : 0.0;
            break;
            
        case Type::NONE:
        case Type::VECTOR:
        case Type::MAP:
        case Type::INT_KEY_MAP:
            return 0.0;
            break;
    }
}

long double Value::asLongDouble() const
{
    CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");
    
    switch ( _type )
    {
        case Type::BYTE:
            return static_cast<long double>(_field.byteVal);
            break;
            
        case Type::SHORT:
            return static_cast<long double>(_field.shortVal);
            break;
            
        case Type::UNSIGNED_SHORT:
            return static_cast<long double>(_field.unsignedShortVal);
            break;
            
        case Type::INTEGER:
            return static_cast<long double>(_field.intVal);
            break;
            
        case Type::UNSIGNED:
            return static_cast<long double>(_field.unsignedVal);
            break;
            
        case Type::LONG:
            return static_cast<long double>(_field.longVal);
            break;
            
        case Type::UNSIGNED_LONG:
            return static_cast<long double>(_field.unsignedLongVal);
            break;
            
        case Type::LONG_LONG:
            return static_cast<long double>(_field.longLongVal);
            break;
            
        case Type::UNSIGNED_LONG_LONG:
            return static_cast<long double>(_field.unsignedLongLongVal);
            break;
            
        case Type::STRING:
            return static_cast<long double>(utils::atof(_field.strVal->c_str()));
            break;
            
        case Type::FLOAT:
            return static_cast<long double>(_field.floatVal);
            break;
            
        case Type::DOUBLE:
            return static_cast<long double>(_field.doubleVal);
            break;
            
        case Type::LONG_DOUBLE:
            return _field.longDoubleVal;
            break;
            
        case Type::BOOLEAN:
            return _field.boolVal ? 1.0l : 0.0l;
            break;
            
        case Type::NONE:
        case Type::VECTOR:
        case Type::MAP:
        case Type::INT_KEY_MAP:
            return 0.0l;
            break;
    }
}

bool Value::asBool() const
{
    CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");
    
    switch ( _type )
    {
        case Type::BYTE:
            return _field.byteVal != 0;
            break;
            
        case Type::SHORT:
            return _field.shortVal != 0;
            break;
            
        case Type::UNSIGNED_SHORT:
            return _field.unsignedShortVal != 0;
            break;
            
        case Type::INTEGER:
            return _field.intVal != 0;
            break;
            
        case Type::UNSIGNED:
            return _field.unsignedVal != 0;
            break;
            
        case Type::LONG:
            return _field.longVal != 0;
            break;
            
        case Type::UNSIGNED_LONG:
            return _field.unsignedLongVal != 0;
            break;
            
        case Type::LONG_LONG:
            return _field.longLongVal != 0;
            break;
            
        case Type::UNSIGNED_LONG_LONG:
            return _field.unsignedLongLongVal != 0;
            break;
            
        case Type::STRING:
            return (*_field.strVal == "0" || *_field.strVal == "false") ? false : true;
            break;
            
        case Type::FLOAT:
            return _field.floatVal != 0.0f;
            break;
            
        case Type::DOUBLE:
            return _field.doubleVal != 0.0f;
            break;
            
        case Type::LONG_DOUBLE:
            return _field.longDoubleVal != 0.0f;
            break;
            
        case Type::BOOLEAN:
            return _field.boolVal;
            break;
            
        case Type::NONE:
        case Type::VECTOR:
        case Type::MAP:
        case Type::INT_KEY_MAP:
            return false;
            break;
    }
}

std::string Value::asString() const
{
    CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");

    if (_type == Type::STRING)
    {
        return *_field.strVal;
    }

    std::stringstream ret;

    switch (_type)
    {
        case Type::BYTE:
            ret << _field.byteVal;
            break;
        case Type::SHORT:
            ret << _field.shortVal;
            break;
        case Type::UNSIGNED_SHORT:
            ret << _field.unsignedShortVal;
            break;
        case Type::INTEGER:
            ret << _field.intVal;
            break;
        case Type::UNSIGNED:
            ret << _field.unsignedVal;
            break;
        case Type::LONG:
            ret << _field.longVal;
            break;
        case Type::UNSIGNED_LONG:
            ret << _field.unsignedLongVal;
            break;
        case Type::LONG_LONG:
            ret << _field.longLongVal;
            break;
        case Type::UNSIGNED_LONG_LONG:
            ret << _field.unsignedLongLongVal;
            break;
        case Type::FLOAT:
            ret << std::fixed << std::setprecision( 7 )<< _field.floatVal;
            break;
        case Type::DOUBLE:
            ret << std::fixed << std::setprecision( 16 ) << _field.doubleVal;
            break;
        case Type::LONG_DOUBLE:
            ret << std::fixed << std::setprecision( 32 ) << _field.longDoubleVal;
            break;
        case Type::BOOLEAN:
            ret << (_field.boolVal ? "true" : "false");
            break;
            
        case Type::NONE:
        case Type::VECTOR:
        case Type::MAP:
        case Type::INT_KEY_MAP:
        case Type::STRING:
            break;
    }
    return ret.str();
}

ValueVector& Value::asValueVector()
{
    CCASSERT(_type == Type::VECTOR, "The value type isn't Type::VECTOR");
    return *_field.vectorVal;
}

const ValueVector& Value::asValueVector() const
{
    CCASSERT(_type == Type::VECTOR, "The value type isn't Type::VECTOR");
    return *_field.vectorVal;
}

ValueMap& Value::asValueMap()
{
    CCASSERT(_type == Type::MAP, "The value type isn't Type::MAP");
    return *_field.mapVal;
}

const ValueMap& Value::asValueMap() const
{
    CCASSERT(_type == Type::MAP, "The value type isn't Type::MAP");
    return *_field.mapVal;
}

ValueMapIntKey& Value::asIntKeyMap()
{
    CCASSERT(_type == Type::INT_KEY_MAP, "The value type isn't Type::INT_KEY_MAP");
    return *_field.intKeyMapVal;
}

const ValueMapIntKey& Value::asIntKeyMap() const
{
    CCASSERT(_type == Type::INT_KEY_MAP, "The value type isn't Type::INT_KEY_MAP");
    return *_field.intKeyMapVal;
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

    for (auto& iter : v)
    {
        ret << getTabs(depth + 1) << iter.first << ": ";
        ret << visit(iter.second, depth + 1);
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
        case Value::Type::SHORT:
        case Value::Type::UNSIGNED_SHORT:
        case Value::Type::INTEGER:
        case Value::Type::UNSIGNED:
        case Value::Type::LONG:
        case Value::Type::UNSIGNED_LONG:
        case Value::Type::LONG_LONG:
        case Value::Type::UNSIGNED_LONG_LONG:
        case Value::Type::FLOAT:
        case Value::Type::DOUBLE:
        case Value::Type::LONG_DOUBLE:
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

std::string Value::getDescription() const
{
    std::string ret("\n");
    ret += visit(*this, 0);
    return ret;
}

void Value::clear()
{
    // Free memory the old value allocated
    switch (_type)
    {
        case Type::BYTE:
            _field.byteVal = 0;
            break;
        case Type::SHORT:
            _field.shortVal = 0;
            break;
        case Type::UNSIGNED_SHORT:
            _field.unsignedShortVal = 0u;
            break;
        case Type::INTEGER:
            _field.intVal = 0;
            break;
        case Type::UNSIGNED:
            _field.unsignedVal = 0u;
            break;
        case Type::LONG:
            _field.longVal = 0l;
            break;
        case Type::UNSIGNED_LONG:
            _field.unsignedLongVal = 0ul;
            break;
        case Type::LONG_LONG:
            _field.longLongVal = 0ll;
            break;
        case Type::UNSIGNED_LONG_LONG:
            _field.unsignedLongLongVal = 0ull;
            break;
        case Type::FLOAT:
            _field.floatVal = 0.0f;
            break;
        case Type::DOUBLE:
            _field.doubleVal = 0.0;
            break;
        case Type::LONG_DOUBLE:
            _field.longDoubleVal = 0.0l;
            break;
        case Type::BOOLEAN:
            _field.boolVal = false;
            break;
        case Type::STRING:
            CC_SAFE_DELETE(_field.strVal);
            break;
        case Type::VECTOR:
            CC_SAFE_DELETE(_field.vectorVal);
            break;
        case Type::MAP:
            CC_SAFE_DELETE(_field.mapVal);
            break;
        case Type::INT_KEY_MAP:
            CC_SAFE_DELETE(_field.intKeyMapVal);
            break;
        default:
            break;
    }

    _type = Type::NONE;
}

void Value::reset(Type type)
{
    if (_type == type)
        return;

    clear();

    // Allocate memory for the new value
    switch (type)
    {
        case Type::STRING:
            _field.strVal = new (std::nothrow) std::string();
            break;
        case Type::VECTOR:
            _field.vectorVal = new (std::nothrow) ValueVector();
            break;
        case Type::MAP:
            _field.mapVal = new (std::nothrow) ValueMap();
            break;
        case Type::INT_KEY_MAP:
            _field.intKeyMapVal = new (std::nothrow) ValueMapIntKey();
            break;
        default:
            break;
    }

    _type = type;
}

NS_CC_END
