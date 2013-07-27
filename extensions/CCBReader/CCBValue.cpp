#include "CCBValue.h"

using namespace cocos2d;

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
        ret->mValue.nValue = nValue;
        ret->mType = TYPE_INT;
        ret->autorelease();
    }
    
    return ret;
}

CCBValue* CCBValue::create(float fValue)
{
    CCBValue *ret = new CCBValue();
    if (ret)
    {
        ret->mValue.fValue = fValue;
        ret->mType = TYPE_FLOAT;
        ret->autorelease();
    }
    
    return ret;
}

CCBValue* CCBValue::create(bool vValue)
{
    CCBValue *ret = new CCBValue();
    if (ret)
    {
        ret->mValue.nValue = vValue ? 1 : 0;
        ret->mType = TYPE_BOOL;
        ret->autorelease();
    }
    
    return ret;
}

CCBValue* CCBValue::create(unsigned char byte)
{
    CCBValue *ret = new CCBValue();
    if (ret)
    {
        ret->mValue.nValue = byte;
        ret->mType = TYPE_UNSIGNED_CHAR;
        ret->autorelease();
    }
    
    return ret;
}

CCBValue* CCBValue::create(const char *pStringValue)
{
    CCBValue *ret = new CCBValue();
    if (ret)
    {
        ret->_value = pStringValue;
        ret->mType = TYPE_STRING;
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
        ret->mType = TYPE_ARRAY;
        ret->autorelease();
    }
    
    return ret;
}


int CCBValue::getIntValue()
{
    CCASSERT(mType == TYPE_INT, "The type of CCBValue isn't integer.");
    
    return mValue.nValue;
}

float CCBValue::getFloatValue()
{
    CCASSERT(mType == TYPE_FLOAT, "The type of CCBValue isn't float.");
    
    return mValue.fValue;
}

bool CCBValue::getBoolValue()
{
    CCASSERT(mType == TYPE_BOOL, "The type of CCBValue isn't boolean.");
    
    return mValue.nValue == 1 ? true : false;
}

unsigned char CCBValue::getByteValue()
{
    CCASSERT(mType == TYPE_UNSIGNED_CHAR, "The type of CCBValue isn't unsigned char.");
    
    return (unsigned char)(mValue.nValue);
}

Array* CCBValue::getArrayValue()
{
    CCASSERT(mType == TYPE_ARRAY, "The type of CCBValue isn't array.");
    
    return _arrValue;
}


const char* CCBValue::getStringValue()
{
    CCASSERT(mType == TYPE_STRING, "The type of CCBValue isn't string.");
    
    return _value.c_str();
}

CCBValue::Type CCBValue::getType()
{
    return mType;
}

NS_CC_EXT_END
