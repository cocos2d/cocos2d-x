/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2022 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "platform/CCPlatformMacros.h"


namespace cocos2d { namespace experimental {

class Value;

using ValueVector = std::vector<Value>;
using ValueMap = std::unordered_map<std::string, Value>;
using ValueMapIntKey = std::unordered_map<int, Value>;

extern const ValueVector VALUE_VECTOR_NULL;
extern const ValueMap VALUE_MAP_NULL;
extern const ValueMapIntKey VALUE_MAP_INT_KEY_NULL;

/*
 * This class is provide as a wrapper of basic types, such as int and bool.
 */
class Value {
public:
    /** A predefined Value that has not value. */
    static const Value VALUE_NULL;

    /** Default constructor. */
    Value();

    /** Create a Value by an unsigned char value. */
    explicit Value(unsigned char v);

    /** Create a Value by an integer value. */
    explicit Value(int v);

    /** Create a Value by an unsigned value. */
    explicit Value(unsigned int v);

    /** Create a Value by a float value. */
    explicit Value(float v);

    /** Create a Value by a double value. */
    explicit Value(double v);

    /** Create a Value by a bool value. */
    explicit Value(bool v);

    /** Create a Value by a char pointer. It will copy the chars internally. */
    explicit Value(const char *v);

    /** Create a Value by a string. */
    explicit Value(const std::string &v);

    /** Create a Value by a ValueVector object. */
    explicit Value(const ValueVector &v);
    /** Create a Value by a ValueVector object. It will use std::move internally. */
    explicit Value(ValueVector &&v);

    /** Create a Value by a ValueMap object. */
    explicit Value(const ValueMap &v);
    /** Create a Value by a ValueMap object. It will use std::move internally. */
    explicit Value(ValueMap &&v);

    /** Create a Value by a ValueMapIntKey object. */
    explicit Value(const ValueMapIntKey &v);
    /** Create a Value by a ValueMapIntKey object. It will use std::move internally. */
    explicit Value(ValueMapIntKey &&v);

    /** Create a Value by another Value object. */
    Value(const Value &other);
    /** Create a Value by a Value object. It will use std::move internally. */
    Value(Value &&other) noexcept;

    /** Destructor. */
    ~Value();

    /** Assignment operator, assign from Value to Value. */
    Value &operator=(const Value &other);
    /** Assignment operator, assign from Value to Value. It will use std::move internally. */
    Value &operator=(Value &&other) noexcept;

    /** Assignment operator, assign from unsigned char to Value. */
    Value &operator=(unsigned char v);
    /** Assignment operator, assign from integer to Value. */
    Value &operator=(int v);
    /** Assignment operator, assign from integer to Value. */
    Value &operator=(unsigned int v);
    /** Assignment operator, assign from float to Value. */
    Value &operator=(float v);
    /** Assignment operator, assign from double to Value. */
    Value &operator=(double v);
    /** Assignment operator, assign from bool to Value. */
    Value &operator=(bool v);
    /** Assignment operator, assign from char* to Value. */
    Value &operator=(const char *v);
    /** Assignment operator, assign from string to Value. */
    Value &operator=(const std::string &v);

    /** Assignment operator, assign from ValueVector to Value. */
    Value &operator=(const ValueVector &v);
    /** Assignment operator, assign from ValueVector to Value. */
    Value &operator=(ValueVector &&v);

    /** Assignment operator, assign from ValueMap to Value. */
    Value &operator=(const ValueMap &v);
    /** Assignment operator, assign from ValueMap to Value. It will use std::move internally. */
    Value &operator=(ValueMap &&v);

    /** Assignment operator, assign from ValueMapIntKey to Value. */
    Value &operator=(const ValueMapIntKey &v);
    /** Assignment operator, assign from ValueMapIntKey to Value. It will use std::move internally. */
    Value &operator=(ValueMapIntKey &&v);

    /** != operator overloading */
    bool operator!=(const Value &v);
    /** != operator overloading */
    bool operator!=(const Value &v) const;
    /** == operator overloading */
    bool operator==(const Value &v);
    /** == operator overloading */
    bool operator==(const Value &v) const;

    /** Gets as a byte value. Will convert to unsigned char if possible, or will trigger assert error. */
    unsigned char asByte() const;
    /** Gets as an integer value. Will convert to integer if possible, or will trigger assert error. */
    int asInt() const;
    /** Gets as an unsigned value. Will convert to unsigned if possible, or will trigger assert error. */
    unsigned int asUnsignedInt() const;
    /** Gets as a float value. Will convert to float if possible, or will trigger assert error. */
    float asFloat() const;
    /** Gets as a double value. Will convert to double if possible, or will trigger assert error. */
    double asDouble() const;
    /** Gets as a bool value. Will convert to bool if possible, or will trigger assert error. */
    bool asBool() const;
    /** Gets as a string value. Will convert to string if possible, or will trigger assert error. */
    std::string asString() const;

    /** Gets as a ValueVector reference. Will convert to ValueVector if possible, or will trigger assert error. */
    ValueVector &asValueVector();
    /** Gets as a const ValueVector reference. Will convert to ValueVector if possible, or will trigger assert error. */
    const ValueVector &asValueVector() const;

    /** Gets as a ValueMap reference. Will convert to ValueMap if possible, or will trigger assert error. */
    ValueMap &asValueMap();
    /** Gets as a const ValueMap reference. Will convert to ValueMap if possible, or will trigger assert error. */
    const ValueMap &asValueMap() const;

    /** Gets as a ValueMapIntKey reference. Will convert to ValueMapIntKey if possible, or will trigger assert error. */
    ValueMapIntKey &asIntKeyMap();
    /** Gets as a const ValueMapIntKey reference. Will convert to ValueMapIntKey if possible, or will trigger assert error. */
    const ValueMapIntKey &asIntKeyMap() const;

    /**
     * Checks if the Value is null.
     * @return True if the Value is null, false if not.
     */
    inline bool isNull() const { return _type == Type::NONE; }

    /** Value type wrapped by Value. */
    enum class Type {
        /// no value is wrapped, an empty Value
        NONE = 0,
        /// wrap byte
        BYTE,
        /// wrap integer
        INTEGER,
        /// wrap unsigned
        UNSIGNED,
        /// wrap float
        FLOAT,
        /// wrap double
        DOUBLE,
        /// wrap bool
        BOOLEAN,
        /// wrap string
        STRING,
        /// wrap vector
        VECTOR,
        /// wrap ValueMap
        MAP,
        /// wrap ValueMapIntKey
        INT_KEY_MAP
    };

    /** Gets the value type. */
    inline Type getType() const { return _type; }

    /** Gets the description of the class. */
    std::string getDescription() const;

private:
    void clear();
    void reset(Type type);

    union {
        unsigned char byteVal;
        int intVal;
        unsigned int unsignedVal;
        float floatVal;
        double doubleVal;
        bool boolVal;

        std::string *strVal;
        ValueVector *vectorVal;
        ValueMap *mapVal;
        ValueMapIntKey *intKeyMapVal;
    } _field;

    Type _type;
};

}}
