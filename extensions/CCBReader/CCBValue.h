#ifndef __CCB_VALUE_H__
#define __CCB_VALUE_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"

/*
 These classes are wrapper of basic types, such as ccColor3B
 */

NS_CC_EXT_BEGIN

class ccColor3BWapper : public CCObject
{
private:
    ccColor3B color;
    
public:
    static ccColor3BWapper* create(const ccColor3B& color);
    
    ccColor3B getColor();
};

enum
{
    kIntValue,
    kFloatValue,
    kPointerValue,
    kBoolValue,
    kUnsignedCharValue,
};

class CCBValue : public CCObject
{
private:
    union 
    {
        int nValue;
        float fValue;
        const void *pointer;
    } mValue;
    
    int mType;
    
public:
    static CCBValue* create(int nValue);
    static CCBValue* create(bool bValue);
    static CCBValue* create(float fValue);
    static CCBValue* create(unsigned char byte);
    static CCBValue* create(const void *pPointer);
    
    int getIntValue();
    float getFloatValue();
    bool getBoolValue();
    unsigned char getByteValue();
    const void* getPointer();
};

NS_CC_EXT_END

#endif // __CCB_VALUE_H__
