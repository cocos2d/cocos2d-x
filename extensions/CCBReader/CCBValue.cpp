#include "CCBValue.h"

using namespace cocos2d;

NS_CC_EXT_BEGIN

// Implementation of ccColor3BWapper

ccColor3BWapper* ccColor3BWapper::create(const ccColor3B& color)
{
    ccColor3BWapper *ret = new ccColor3BWapper();
    if (ret)
    {
        ret->color.r = color.r;
        ret->color.g = color.g;
        ret->color.b = color.b;
        
        ret->autorelease();
    }
    
    return ret;
}

const ccColor3B& ccColor3BWapper::getColor() const
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
        ret->mType = kIntValue;
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
        ret->mType = kFloatValue;
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
        ret->mType = kBoolValue;
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
        ret->mType = kUnsignedCharValue;
        ret->autorelease();
    }
    
    return ret;
}

CCBValue* CCBValue::create(const char *pStringValue)
{
    CCBValue *ret = new CCBValue();
    if (ret)
    {
        ret->m_strValue = pStringValue;
        ret->mType = kStringValue;
        ret->autorelease();
    }
    
    return ret;
}

int CCBValue::getIntValue()
{
    assert(mType == kIntValue);
    
    return mValue.nValue;
}

float CCBValue::getFloatValue()
{
    assert(mType == kFloatValue);
    
    return mValue.fValue;
}

bool CCBValue::getBoolValue()
{
    assert(mType == kBoolValue);
    
    return mValue.nValue == 1 ? true : false;
}

unsigned char CCBValue::getByteValue()
{
    assert(mType = kUnsignedCharValue);
    
    return (unsigned char)(mValue.nValue);
}

const char* CCBValue::getStringValue()
{
    assert(mType == kStringValue);
    
    return m_strValue.c_str();
}

int CCBValue::getType()
{
    return mType;
}

NS_CC_EXT_END
