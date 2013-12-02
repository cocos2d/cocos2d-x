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
#include <vector>
#include <unordered_map>

NS_CC_BEGIN

class Value;

typedef std::vector<Value> ValueArray;
typedef std::unordered_map<std::string, Value> ValueDict;

class Value
{
public:
    Value()
    : _type(Type::NONE)
    {
        
    }
    explicit Value(int v)
    {
        _baseData.intVal = v;
        _type = Type::INTEGER;
    }
    explicit Value(float v)
    {
        _baseData.floatVal = v;
        _type = Type::FLOAT;
    }
    explicit Value(double v)
    {
        _baseData.doubleVal = v;
        _type = Type::DOUBLE;
    }
    explicit Value(bool v)
    {
        _baseData.boolVal = v;
        _type = Type::BOOLEAN;
    }
    explicit Value(const std::string& v)
    {
        _strData = v;
        _type = Type::STRING;
    }
    explicit Value(const ValueArray& v)
    {
        _arrData = v;
        _type = Type::ARRAY;
    }
    explicit Value(const ValueDict& v)
    {
        _dictData = v;
        _type = Type::DICTIONARY;
    }

    Value(const Value& other)
    {
        *this = other;
    }
    Value(Value&& other)
    {
        *this = other;
    }
    
    ~Value()
    {
        
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
                _arrData = other._arrData;
                break;
            case Type::DICTIONARY:
                _dictData = other._dictData;
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
                _arrData = other._arrData;
                break;
            case Type::DICTIONARY:
                _dictData = other._dictData;
                break;
            default:
                break;
        }
        _type = other._type;
        return *this;
    }
    
    int asInt()
    {
        CCASSERT(_type == Type::INTEGER, "");
        return _baseData.intVal;
    }
    
    float asFloat()
    {
        CCASSERT(_type == Type::FLOAT, "");
        return _baseData.floatVal;
    }
    double asDouble()
    {
        CCASSERT(_type == Type::DOUBLE, "");
        return _baseData.doubleVal;
    }
    bool asBool()
    {
        CCASSERT(_type == Type::BOOLEAN, "");
        return _baseData.boolVal;
    }
    std::string asString()
    {
        CCASSERT(_type == Type::STRING, "");
        return _strData;
    }
    ValueArray asArray()
    {
        CCASSERT(_type == Type::ARRAY, "");
        return _arrData;
    }
    ValueDict asDict()
    {
        CCASSERT(_type == Type::DICTIONARY, "");
        return _dictData;
    }
    
    enum class Type
    {
        NONE,
        INTEGER,
        FLOAT,
        DOUBLE,
        BOOLEAN,
        STRING,
        ARRAY,
        DICTIONARY
    };

    inline Type getType() { return _type; };
    
private:
    union
    {
        int intVal;
        float floatVal;
        double doubleVal;
        bool boolVal;
    }_baseData;
    
    std::string _strData;
    ValueArray _arrData;
    ValueDict _dictData;
    

    Type _type;
};


NS_CC_END

#endif /* defined(__cocos2d_libs__CCValue__) */
