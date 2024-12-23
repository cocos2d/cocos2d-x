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

#include "../Value.h"

#include <memory.h>
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <sstream>

#include "../utils/Utils.h"

namespace cocos2d { namespace experimental {

const ValueVector VALUE_VECTOR_NULL;
const ValueMap VALUE_MAP_NULL = {};
const ValueMapIntKey VALUE_MAP_INT_KEY_NULL = {};

const Value Value::VALUE_NULL;

Value::Value()
: _type(Type::NONE) {
    memset(&_field, 0, sizeof(_field));
}

Value::Value(unsigned char v)
: _type(Type::BYTE) {
    _field.byteVal = v;
}

Value::Value(int v)
: _type(Type::INTEGER) {
    _field.intVal = v;
}

Value::Value(unsigned int v)
: _type(Type::UNSIGNED) {
    _field.unsignedVal = v;
}

Value::Value(float v)
: _type(Type::FLOAT) {
    _field.floatVal = v;
}

Value::Value(double v)
: _type(Type::DOUBLE) {
    _field.doubleVal = v;
}

Value::Value(bool v)
: _type(Type::BOOLEAN) {
    _field.boolVal = v;
}

Value::Value(const char *v)
: _type(Type::STRING) {
    _field.strVal = new std::string();
    if (v) {
        *_field.strVal = v;
    }
}

Value::Value(const std::string &v)
: _type(Type::STRING) {
    _field.strVal = new std::string();
    *_field.strVal = v;
}

Value::Value(const ValueVector &v)
: _type(Type::VECTOR) {
    _field.vectorVal = new ValueVector();
    *_field.vectorVal = v;
}

Value::Value(ValueVector &&v)
: _type(Type::VECTOR) {
    _field.vectorVal = new ValueVector();
    *_field.vectorVal = std::move(v);
}

Value::Value(const ValueMap &v)
: _type(Type::MAP) {
    _field.mapVal = new ValueMap();
    *_field.mapVal = v;
}

Value::Value(ValueMap &&v)
: _type(Type::MAP) {
    _field.mapVal = new ValueMap();
    *_field.mapVal = std::move(v);
}

Value::Value(const ValueMapIntKey &v)
: _type(Type::INT_KEY_MAP) {
    _field.intKeyMapVal = new ValueMapIntKey();
    *_field.intKeyMapVal = v;
}

Value::Value(ValueMapIntKey &&v)
: _type(Type::INT_KEY_MAP) {
    _field.intKeyMapVal = new ValueMapIntKey();
    *_field.intKeyMapVal = std::move(v);
}

Value::Value(const Value &other) //NOLINT(misc-no-recursion)
: _type(Type::NONE) {
    *this = other;
}

Value::Value(Value &&other) noexcept
: _type(Type::NONE) {
    *this = std::move(other);
}

Value::~Value() {
    clear();
}

Value &Value::operator=(const Value &other) { //NOLINT(misc-no-recursion)
    if (this != &other) {
        reset(other._type);

        switch (other._type) {
            case Type::BYTE:
                _field.byteVal = other._field.byteVal;
                break;
            case Type::INTEGER:
                _field.intVal = other._field.intVal;
                break;
            case Type::UNSIGNED:
                _field.unsignedVal = other._field.unsignedVal;
                break;
            case Type::FLOAT:
                _field.floatVal = other._field.floatVal;
                break;
            case Type::DOUBLE:
                _field.doubleVal = other._field.doubleVal;
                break;
            case Type::BOOLEAN:
                _field.boolVal = other._field.boolVal;
                break;
            case Type::STRING:
                if (_field.strVal == nullptr) {
                    _field.strVal = new std::string();
                }
                *_field.strVal = *other._field.strVal;
                break;
            case Type::VECTOR:
                if (_field.vectorVal == nullptr) {
                    _field.vectorVal = new ValueVector();
                }
                *_field.vectorVal = *other._field.vectorVal;
                break;
            case Type::MAP:
                if (_field.mapVal == nullptr) {
                    _field.mapVal = new ValueMap();
                }
                *_field.mapVal = *other._field.mapVal;
                break;
            case Type::INT_KEY_MAP:
                if (_field.intKeyMapVal == nullptr) {
                    _field.intKeyMapVal = new ValueMapIntKey();
                }
                *_field.intKeyMapVal = *other._field.intKeyMapVal;
                break;
            default:
                break;
        }
    }
    return *this;
}

Value &Value::operator=(Value &&other) noexcept {
    if (this != &other) {
        clear();
        switch (other._type) {
            case Type::BYTE:
                _field.byteVal = other._field.byteVal;
                break;
            case Type::INTEGER:
                _field.intVal = other._field.intVal;
                break;
            case Type::UNSIGNED:
                _field.unsignedVal = other._field.unsignedVal;
                break;
            case Type::FLOAT:
                _field.floatVal = other._field.floatVal;
                break;
            case Type::DOUBLE:
                _field.doubleVal = other._field.doubleVal;
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

Value &Value::operator=(unsigned char v) {
    reset(Type::BYTE);
    _field.byteVal = v;
    return *this;
}

Value &Value::operator=(int v) {
    reset(Type::INTEGER);
    _field.intVal = v;
    return *this;
}

Value &Value::operator=(unsigned int v) {
    reset(Type::UNSIGNED);
    _field.unsignedVal = v;
    return *this;
}

Value &Value::operator=(float v) {
    reset(Type::FLOAT);
    _field.floatVal = v;
    return *this;
}

Value &Value::operator=(double v) {
    reset(Type::DOUBLE);
    _field.doubleVal = v;
    return *this;
}

Value &Value::operator=(bool v) {
    reset(Type::BOOLEAN);
    _field.boolVal = v;
    return *this;
}

Value &Value::operator=(const char *v) {
    reset(Type::STRING);
    *_field.strVal = v ? v : "";
    return *this;
}

Value &Value::operator=(const std::string &v) {
    reset(Type::STRING);
    *_field.strVal = v;
    return *this;
}

Value &Value::operator=(const ValueVector &v) {
    reset(Type::VECTOR);
    *_field.vectorVal = v;
    return *this;
}

Value &Value::operator=(ValueVector &&v) {
    reset(Type::VECTOR);
    *_field.vectorVal = std::move(v);
    return *this;
}

Value &Value::operator=(const ValueMap &v) {
    reset(Type::MAP);
    *_field.mapVal = v;
    return *this;
}

Value &Value::operator=(ValueMap &&v) {
    reset(Type::MAP);
    *_field.mapVal = std::move(v);
    return *this;
}

Value &Value::operator=(const ValueMapIntKey &v) {
    reset(Type::INT_KEY_MAP);
    *_field.intKeyMapVal = v;
    return *this;
}

Value &Value::operator=(ValueMapIntKey &&v) {
    reset(Type::INT_KEY_MAP);
    *_field.intKeyMapVal = std::move(v);
    return *this;
}

bool Value::operator!=(const Value &v) {
    return !(*this == v);
}
bool Value::operator!=(const Value &v) const { //NOLINT(misc-no-recursion)
    return !(*this == v);
}

bool Value::operator==(const Value &v) {
    const auto &t = *this;
    return t == v;
}
bool Value::operator==(const Value &v) const { //NOLINT(misc-no-recursion)
    if (this == &v) {
        return true;
    }

    if (v._type != this->_type) {
        return false;
    }

    if (this->isNull()) {
        return true;
    }

    switch (_type) {
        case Type::BYTE: return v._field.byteVal == this->_field.byteVal;
        case Type::INTEGER: return v._field.intVal == this->_field.intVal;
        case Type::UNSIGNED: return v._field.unsignedVal == this->_field.unsignedVal;
        case Type::BOOLEAN: return v._field.boolVal == this->_field.boolVal;
        case Type::STRING: return *v._field.strVal == *this->_field.strVal;
        case Type::FLOAT: return std::abs(v._field.floatVal - this->_field.floatVal) <= FLT_EPSILON;
        case Type::DOUBLE: return std::abs(v._field.doubleVal - this->_field.doubleVal) <= DBL_EPSILON;
        case Type::VECTOR: {
            const auto &v1 = *(this->_field.vectorVal);
            const auto &v2 = *(v._field.vectorVal);
            const auto size = v1.size();
            if (size == v2.size()) {
                for (size_t i = 0; i < size; i++) {
                    if (v1[i] != v2[i]) {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
        case Type::MAP: {
            const auto &map1 = *(this->_field.mapVal);
            const auto &map2 = *(v._field.mapVal);
            for (const auto &kvp : map1) { //NOLINT
                auto it = map2.find(kvp.first);
                if (it == map2.end() || it->second != kvp.second) {
                    return false;
                }
            }
            return true;
        }
        case Type::INT_KEY_MAP: {
            const auto &map1 = *(this->_field.intKeyMapVal);
            const auto &map2 = *(v._field.intKeyMapVal);
            for (const auto &kvp : map1) { //NOLINT
                auto it = map2.find(kvp.first);
                if (it == map2.end() || it->second != kvp.second) {
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
unsigned char Value::asByte() const {
    CC_ASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP);

    if (_type == Type::BYTE) {
        return _field.byteVal;
    }

    if (_type == Type::INTEGER) {
        return static_cast<unsigned char>(_field.intVal);
    }

    if (_type == Type::UNSIGNED) {
        return static_cast<unsigned char>(_field.unsignedVal);
    }

    if (_type == Type::STRING) {
        return static_cast<unsigned char>(atoi(_field.strVal->c_str()));
    }

    if (_type == Type::FLOAT) {
        return static_cast<unsigned char>(_field.floatVal);
    }

    if (_type == Type::DOUBLE) {
        return static_cast<unsigned char>(_field.doubleVal);
    }

    if (_type == Type::BOOLEAN) {
        return _field.boolVal ? 1 : 0;
    }

    return 0;
}

int Value::asInt() const {
    CC_ASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP);
    if (_type == Type::INTEGER) {
        return _field.intVal;
    }

    if (_type == Type::UNSIGNED) {
        CC_ASSERT(_field.unsignedVal < INT_MAX);
        return static_cast<int>(_field.unsignedVal);
    }

    if (_type == Type::BYTE) {
        return _field.byteVal;
    }

    if (_type == Type::STRING) {
        return atoi(_field.strVal->c_str());
    }

    if (_type == Type::FLOAT) {
        return static_cast<int>(_field.floatVal);
    }

    if (_type == Type::DOUBLE) {
        return static_cast<int>(_field.doubleVal);
    }

    if (_type == Type::BOOLEAN) {
        return _field.boolVal ? 1 : 0;
    }

    return 0;
}

unsigned int Value::asUnsignedInt() const {
    CC_ASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP);
    if (_type == Type::UNSIGNED) {
        return _field.unsignedVal;
    }

    if (_type == Type::INTEGER) {
        CC_ASSERT(_field.intVal >= 0);
        return static_cast<unsigned int>(_field.intVal);
    }

    if (_type == Type::BYTE) {
        return static_cast<unsigned int>(_field.byteVal);
    }

    if (_type == Type::STRING) {
        // NOTE: strtoul is required (need to augment on unsupported platforms)
        return static_cast<unsigned int>(strtoul(_field.strVal->c_str(), nullptr, 10));
    }

    if (_type == Type::FLOAT) {
        return static_cast<unsigned int>(_field.floatVal);
    }

    if (_type == Type::DOUBLE) {
        return static_cast<unsigned int>(_field.doubleVal);
    }

    if (_type == Type::BOOLEAN) {
        return _field.boolVal ? 1U : 0U;
    }

    return 0U;
}

#define MAX_ITOA_BUFFER_SIZE 256
double audioAtof(const char *str) {
    if (str == nullptr) {
        return 0.0;
    }

    char buf[MAX_ITOA_BUFFER_SIZE];
    strncpy(buf, str, MAX_ITOA_BUFFER_SIZE);

    // strip string, only remain 7 numbers after '.'
    char *dot = strchr(buf, '.');
    if (dot != nullptr && dot - buf + 8 < MAX_ITOA_BUFFER_SIZE) {
        dot[8] = '\0';
    }

    return ::atof(buf);
}

float Value::asFloat() const {
    CC_ASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP);
    if (_type == Type::FLOAT) {
        return _field.floatVal;
    }

    if (_type == Type::BYTE) {
        return static_cast<float>(_field.byteVal);
    }

    if (_type == Type::STRING) {
        return static_cast<float>(audioAtof(_field.strVal->c_str()));
    }

    if (_type == Type::INTEGER) {
        return static_cast<float>(_field.intVal);
    }

    if (_type == Type::UNSIGNED) {
        return static_cast<float>(_field.unsignedVal);
    }

    if (_type == Type::DOUBLE) {
        return static_cast<float>(_field.doubleVal);
    }

    if (_type == Type::BOOLEAN) {
        return _field.boolVal ? 1.0F : 0.0F;
    }

    return 0.0F;
}

double Value::asDouble() const {
    CC_ASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP);
    if (_type == Type::DOUBLE) {
        return _field.doubleVal;
    }

    if (_type == Type::BYTE) {
        return static_cast<double>(_field.byteVal);
    }

    if (_type == Type::STRING) {
        return static_cast<double>(audioAtof(_field.strVal->c_str()));
    }

    if (_type == Type::INTEGER) {
        return static_cast<double>(_field.intVal);
    }

    if (_type == Type::UNSIGNED) {
        return static_cast<double>(_field.unsignedVal);
    }

    if (_type == Type::FLOAT) {
        return static_cast<double>(_field.floatVal);
    }

    if (_type == Type::BOOLEAN) {
        return _field.boolVal ? 1.0 : 0.0;
    }

    return 0.0;
}

bool Value::asBool() const {
    CC_ASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP);
    if (_type == Type::BOOLEAN) {
        return _field.boolVal;
    }

    if (_type == Type::BYTE) {
        return _field.byteVal != 0;
    }

    if (_type == Type::STRING) {
        return *_field.strVal != "0" || *_field.strVal != "false";
    }

    if (_type == Type::INTEGER) {
        return _field.intVal != 0;
    }

    if (_type == Type::UNSIGNED) {
        return _field.unsignedVal != 0;
    }

    if (_type == Type::FLOAT) {
        return _field.floatVal != 0.0F;
    }

    if (_type == Type::DOUBLE) {
        return _field.doubleVal != 0.0;
    }

    return false;
}

std::string Value::asString() const {
    CC_ASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP);

    if (_type == Type::STRING) {
        return *_field.strVal;
    }

    std::stringstream ret;

    switch (_type) {
        case Type::BYTE:
            ret << _field.byteVal;
            break;
        case Type::INTEGER:
            ret << _field.intVal;
            break;
        case Type::UNSIGNED:
            ret << _field.unsignedVal;
            break;
        case Type::FLOAT:
            ret << std::fixed << std::setprecision(7) << _field.floatVal;
            break;
        case Type::DOUBLE:
            ret << std::fixed << std::setprecision(16) << _field.doubleVal;
            break;
        case Type::BOOLEAN:
            ret << (_field.boolVal ? "true" : "false");
            break;
        default:
            break;
    }
    return ret.str();
}

ValueVector &Value::asValueVector() {
    CC_ASSERT(_type == Type::VECTOR);
    return *_field.vectorVal;
}

const ValueVector &Value::asValueVector() const {
    CC_ASSERT(_type == Type::VECTOR);
    return *_field.vectorVal;
}

ValueMap &Value::asValueMap() {
    CC_ASSERT(_type == Type::MAP);
    return *_field.mapVal;
}

const ValueMap &Value::asValueMap() const {
    CC_ASSERT(_type == Type::MAP);
    return *_field.mapVal;
}

ValueMapIntKey &Value::asIntKeyMap() {
    CC_ASSERT(_type == Type::INT_KEY_MAP);
    return *_field.intKeyMapVal;
}

const ValueMapIntKey &Value::asIntKeyMap() const {
    CC_ASSERT(_type == Type::INT_KEY_MAP);
    return *_field.intKeyMapVal;
}

static std::string getTabs(int depth) {
    std::string tabWidth;

    for (int i = 0; i < depth; ++i) {
        tabWidth += "\t";
    }

    return tabWidth;
}

static std::string visit(const Value &v, int depth);

static std::string visitVector(const ValueVector &v, int depth) { //NOLINT[misc-no-recursion]
    std::stringstream ret;

    if (depth > 0) {
        ret << "\n";
    }

    ret << getTabs(depth) << "[\n";

    int i = 0;
    for (const auto &child : v) {
        ret << getTabs(depth + 1) << i << ": " << visit(child, depth + 1);
        ++i;
    }

    ret << getTabs(depth) << "]\n";

    return ret.str();
}

template <class T>
static std::string visitMap(const T &v, int depth) { //NOLINT[misc-no-recursion]
    std::stringstream ret;

    if (depth > 0) {
        ret << "\n";
    }

    ret << getTabs(depth) << "{\n";

    for (auto iter = v.begin(); iter != v.end(); ++iter) {
        ret << getTabs(depth + 1) << iter->first << ": ";
        ret << visit(iter->second, depth + 1);
    }

    ret << getTabs(depth) << "}\n";

    return ret.str();
}

static std::string visit(const Value &v, int depth) { //NOLINT[misc-no-recursion]
    std::stringstream ret;

    switch (v.getType()) {
        case Value::Type::NONE:
        case Value::Type::BYTE:
        case Value::Type::INTEGER:
        case Value::Type::UNSIGNED:
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
            CC_ASSERT(false);
            break;
    }

    return ret.str();
}

std::string Value::getDescription() const {
    std::string ret("\n");
    ret += visit(*this, 0);
    return ret;
}

void Value::clear() {
    // Free memory the old value allocated
    switch (_type) {
        case Type::BYTE:
            _field.byteVal = 0;
            break;
        case Type::INTEGER:
            _field.intVal = 0;
            break;
        case Type::UNSIGNED:
            _field.unsignedVal = 0U;
            break;
        case Type::FLOAT:
            _field.floatVal = 0.0F;
            break;
        case Type::DOUBLE:
            _field.doubleVal = 0.0;
            break;
        case Type::BOOLEAN:
            _field.boolVal = false;
            break;
        case Type::STRING:
            CC_AUDIO_SAFE_DELETE(_field.strVal);
            break;
        case Type::VECTOR:
            CC_AUDIO_SAFE_DELETE(_field.vectorVal);
            break;
        case Type::MAP:
            CC_AUDIO_SAFE_DELETE(_field.mapVal);
            break;
        case Type::INT_KEY_MAP:
            CC_AUDIO_SAFE_DELETE(_field.intKeyMapVal);
            break;
        default:
            break;
    }

    _type = Type::NONE;
}

void Value::reset(Type type) {
    if (_type == type) {
        return;
    }

    clear();

    // Allocate memory for the new value
    switch (type) {
        case Type::STRING:
            _field.strVal = new std::string();
            break;
        case Type::VECTOR:
            _field.vectorVal = new ValueVector();
            break;
        case Type::MAP:
            _field.mapVal = new ValueMap();
            break;
        case Type::INT_KEY_MAP:
            _field.intKeyMapVal = new ValueMapIntKey();
            break;
        default:
            break;
    }

    _type = type;
}

}} // namespace CocosDenshion
