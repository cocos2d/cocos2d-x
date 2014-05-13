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

#ifndef __cocos2d_libs__CCValue__
#define __cocos2d_libs__CCValue__

#include "base/CCPlatformMacros.h"
#include "base/ccMacros.h"
#include <string>
#include <vector>
#include <unordered_map>

NS_CC_BEGIN

class Value;

typedef std::vector<Value> ValueVector;
typedef std::unordered_map<std::string, Value> ValueMap;
typedef std::unordered_map<int, Value> ValueMapIntKey;

extern const ValueVector ValueVectorNull;
extern const ValueMap ValueMapNull;
extern const ValueMapIntKey ValueMapIntKeyNull;

class Value
{
public:
    static const Value Null;

    Value();
    explicit Value(unsigned char v);
    explicit Value(int v);
    explicit Value(float v);
    explicit Value(double v);
    explicit Value(bool v);
    explicit Value(const char* v);
    explicit Value(const std::string& v);

    explicit Value(const ValueVector& v);
    explicit Value(ValueVector&& v);

    explicit Value(const ValueMap& v);
        explicit Value(ValueMap&& v);

    explicit Value(const ValueMapIntKey& v);
    explicit Value(ValueMapIntKey&& v);

    Value(const Value& other);
    Value(Value&& other);
    ~Value();

    // assignment operator
    Value& operator= (const Value& other);
    Value& operator= (Value&& other);

    Value& operator= (unsigned char v);
    Value& operator= (int v);
    Value& operator= (float v);
    Value& operator= (double v);
    Value& operator= (bool v);
    Value& operator= (const char* v);
    Value& operator= (const std::string& v);

    Value& operator= (const ValueVector& v);
    Value& operator= (ValueVector&& v);

    Value& operator= (const ValueMap& v);
        Value& operator= (ValueMap&& v);

    Value& operator= (const ValueMapIntKey& v);
    Value& operator= (ValueMapIntKey&& v);

    unsigned char asByte() const;
    int asInt() const;
    float asFloat() const;
    double asDouble() const;
    bool asBool() const;
    std::string asString() const;

    ValueVector& asValueVector();
    const ValueVector& asValueVector() const;

    ValueMap& asValueMap();
    const ValueMap& asValueMap() const;

    ValueMapIntKey& asIntKeyMap();
    const ValueMapIntKey& asIntKeyMap() const;

    inline bool isNull() const { return _type == Type::NONE; }

    enum class Type
    {
        NONE = 0,
        BYTE,
        INTEGER,
        FLOAT,
        DOUBLE,
        BOOLEAN,
        STRING,
        VECTOR,
        MAP,
        INT_KEY_MAP
    };

    inline Type getType() const { return _type; };

    std::string getDescription();

private:
    void clear();
    void reset(Type type);

    union
    {
        unsigned char byteVal;
        int intVal;
        float floatVal;
        double doubleVal;
        bool boolVal;

        std::string* strVal;
        ValueVector* vectorVal;
        ValueMap* mapVal;
        ValueMapIntKey* intKeyMapVal;
    }_field;

    Type _type;
};

NS_CC_END


#endif /* defined(__cocos2d_libs__CCValue__) */
