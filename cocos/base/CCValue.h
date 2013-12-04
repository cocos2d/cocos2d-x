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

#ifndef __cocos2d_libs__CCValue__
#define __cocos2d_libs__CCValue__

#include "CCPlatformMacros.h"
#include "ccMacros.h"
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

NS_CC_BEGIN

class Value;
typedef std::vector<Value> ValueArray;
typedef std::unordered_map<std::string, Value> ValueDict;
typedef std::unordered_map<int, Value> IntValueDict;

class Value
{
public:
    Value()
    : _arrData(nullptr)
    , _dictData(nullptr)
    , _intKeyDictData(nullptr)
    , _type(Type::NONE)
    {
        
    }
    explicit Value(int v)
    : _arrData(nullptr)
    , _dictData(nullptr)
    , _intKeyDictData(nullptr)
    , _type(Type::INTEGER)
    {
        _baseData.intVal = v;
    }
    explicit Value(float v)
    : _arrData(nullptr)
    , _dictData(nullptr)
    , _intKeyDictData(nullptr)
    , _type(Type::FLOAT)
    {
        _baseData.floatVal = v;
    }
    explicit Value(double v)
    : _arrData(nullptr)
    , _dictData(nullptr)
    , _intKeyDictData(nullptr)
    , _type(Type::DOUBLE)
    {
        _baseData.doubleVal = v;
    }
    explicit Value(bool v)
    : _arrData(nullptr)
    , _dictData(nullptr)
    , _intKeyDictData(nullptr)
    , _type(Type::BOOLEAN)
    {
        _baseData.boolVal = v;
    }
    
    explicit Value(const char* v)
    : _arrData(nullptr)
    , _dictData(nullptr)
    , _intKeyDictData(nullptr)
    , _type(Type::STRING)
    {
        _strData = v;
    }
    
    explicit Value(const std::string& v)
    : _arrData(nullptr)
    , _dictData(nullptr)
    , _intKeyDictData(nullptr)
    , _type(Type::STRING)
    {
        _strData = v;
    }
    explicit Value(const ValueArray& v)
    : _arrData(new ValueArray())
    , _dictData(nullptr)
    , _intKeyDictData(nullptr)
    , _type(Type::ARRAY)
    {
        *_arrData = v;
    }
    explicit Value(const ValueDict& v)
    : _arrData(nullptr)
    , _dictData(new ValueDict())
    , _intKeyDictData(nullptr)
    , _type(Type::DICTIONARY)
    {
        *_dictData = v;
    }

	explicit Value(ValueDict&& v)
    : _arrData(nullptr)
    , _dictData(new ValueDict())
    , _intKeyDictData(nullptr)
    , _type(Type::DICTIONARY)
    {
        *_dictData = std::move(v);
    }
    
    explicit Value(const IntValueDict& v)
    : _arrData(nullptr)
    , _dictData(nullptr)
    , _intKeyDictData(new IntValueDict())
    , _type(Type::INT_KEY_DICT)
    {
        *_intKeyDictData = v;
    }

    Value(const Value& other)
    : _arrData(nullptr)
    , _dictData(nullptr)
    , _intKeyDictData(nullptr)
    {
        *this = other;
    }
    Value(Value&& other)
    : _arrData(nullptr)
    , _dictData(nullptr)
    , _intKeyDictData(nullptr)
    {
        *this = std::move(other);
    }
    
    ~Value()
    {
        CC_SAFE_DELETE(_arrData);
        CC_SAFE_DELETE(_dictData);
        CC_SAFE_DELETE(_intKeyDictData);
    }
    
    Value& operator= (const Value& other)
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
            case Type::ARRAY:
                *_arrData = *other._arrData;
                break;
            case Type::DICTIONARY:
                *_dictData = *other._dictData;
                break;
            case Type::INT_KEY_DICT:
                *_intKeyDictData = *other._intKeyDictData;
                break;
            default:
                break;
        }
        _type = other._type;
        return *this;
    }
    
    Value& operator= (Value&& other)
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
            case Type::ARRAY:
                CC_SAFE_DELETE(_arrData);
                _arrData = other._arrData;
                break;
            case Type::DICTIONARY:
                CC_SAFE_DELETE(_dictData);
                _dictData = other._dictData;
                break;
            case Type::INT_KEY_DICT:
                CC_SAFE_DELETE(_intKeyDictData);
                _intKeyDictData = other._intKeyDictData;
                break;
            default:
                break;
        }
        _type = other._type;

        other._arrData = nullptr;
        other._dictData = nullptr;
        other._intKeyDictData = nullptr;
		other._type = Type::NONE;
        
        return *this;
    }
    
    int asInt() const
    {
        CCASSERT(_type != Type::ARRAY && _type != Type::DICTIONARY, "");
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
    
    float asFloat() const
    {
        CCASSERT(_type != Type::ARRAY && _type != Type::DICTIONARY, "");
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
    double asDouble() const
    {
        CCASSERT(_type != Type::ARRAY && _type != Type::DICTIONARY, "");
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
    bool asBool() const
    {
        CCASSERT(_type != Type::ARRAY && _type != Type::DICTIONARY, "");
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
    
    std::string asString() const
    {
        CCASSERT(_type != Type::ARRAY && _type != Type::DICTIONARY, "");
        
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
    
    ValueArray& asArray()
    {
        return *_arrData;
    }
    
    const ValueArray& asArray() const
    {
        return *_arrData;
    }
    
    ValueDict& asDict()
    {
        return *_dictData;
    }
    
    const ValueDict& asDict() const
    {
        return *_dictData;
    }
    
    IntValueDict& asIntKeyDict()
    {
        return *_intKeyDictData;
    }
    
    bool isNull() const { return _type == Type::NONE; }
    
    enum class Type
    {
        NONE,
        INTEGER,
        FLOAT,
        DOUBLE,
        BOOLEAN,
        STRING,
        ARRAY,
        DICTIONARY,
        INT_KEY_DICT
    };

    inline Type getType() const { return _type; };
    
private:
    union
    {
        int intVal;
        float floatVal;
        double doubleVal;
        bool boolVal;
    }_baseData;
    
    std::string _strData;
    ValueArray* _arrData;
    ValueDict* _dictData;
    IntValueDict* _intKeyDictData;

    Type _type;
};

NS_CC_END


#endif /* defined(__cocos2d_libs__CCValue__) */
