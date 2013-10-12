#include "CCBValue.h"

NS_CC_EXT_BEGIN

// Implementation of Color3BWapper

Color3BWapper* Color3BWapper::create(const Color3B& color)
{
    Color3BWapper *ret = new Color3BWapper();
    if (ret)
    {
        ret->color.r = color.r;
        ret->color.g = color.g;
        ret->color.b = color.b;

        ret->autorelease();
    }

    return ret;
}

const Color3B& Color3BWapper::getColor() const
{
    return color;
}

// Implementation of CCBValue

CCBValue* CCBValue::create(int nValue)
{
    CCBValue *ret = new CCBValue();
    if (ret)
    {
        ret->_value.intValue = nValue;
        ret->_type = Type::INT;
        ret->autorelease();
    }

    return ret;
}

CCBValue* CCBValue::create(float fValue)
{
    CCBValue *ret = new CCBValue();
    if (ret)
    {
        ret->_value.floatValue = fValue;
        ret->_type = Type::FLOAT;
        ret->autorelease();
    }

    return ret;
}

CCBValue* CCBValue::create(bool vValue)
{
    CCBValue *ret = new CCBValue();
    if (ret)
    {
        ret->_value.intValue = vValue ? 1 : 0;
        ret->_type = Type::BOOL;
        ret->autorelease();
    }

    return ret;
}

CCBValue* CCBValue::create(unsigned char byte)
{
    CCBValue *ret = new CCBValue();
    if (ret)
    {
        ret->_value.intValue = byte;
        ret->_type = Type::UNSIGNED_CHAR;
        ret->autorelease();
    }

    return ret;
}

CCBValue* CCBValue::create(const char *pStringValue)
{
    CCBValue *ret = new CCBValue();
    if (ret)
    {
        ret->_strValue = pStringValue;
        ret->_type = Type::STRING;
        ret->autorelease();
    }

    return ret;
}


CCBValue* CCBValue::create(Array *pArrValue)
{
    CCBValue *ret = new CCBValue();
    if (ret)
    {
        ret->_arrValue = pArrValue;
        ret->_type = Type::ARRAY;
        ret->autorelease();
    }

    return ret;
}


int CCBValue::getIntValue()
{
    CCASSERT(_type == Type::INT, "The type of CCBValue isn't integer.");

    return _value.intValue;
}

float CCBValue::getFloatValue()
{
    CCASSERT(_type == Type::FLOAT, "The type of CCBValue isn't float.");

    return _value.floatValue;
}

bool CCBValue::getBoolValue()
{
    CCASSERT(_type == Type::BOOL, "The type of CCBValue isn't boolean.");

    return _value.intValue == 1 ? true : false;
}

unsigned char CCBValue::getByteValue()
{
    CCASSERT(_type == Type::UNSIGNED_CHAR, "The type of CCBValue isn't unsigned char.");

    return (unsigned char)(_value.intValue);
}

Array* CCBValue::getArrayValue()
{
    CCASSERT(_type == Type::ARRAY, "The type of CCBValue isn't array.");

    return _arrValue;
}


const char* CCBValue::getStringValue()
{
    CCASSERT(_type == Type::STRING, "The type of CCBValue isn't string.");

    return _strValue.c_str();
}

CCBValue::Type CCBValue::getType()
{
    return _type;
}

NS_CC_EXT_END
