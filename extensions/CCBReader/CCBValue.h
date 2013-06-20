#ifndef __CCB_VALUE_H__
#define __CCB_VALUE_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"

/*
 These classes are wrapper of basic types, such as ccColor3B
 */

NS_CC_EXT_BEGIN

class ccColor3BWapper : public Object
{
private:
    ccColor3B color;
    
public:
    static ccColor3BWapper* create(const ccColor3B& color);
    
    const ccColor3B& getColor() const;
};

enum
{
    kIntValue,
    kFloatValue,
    kBoolValue,
    kUnsignedCharValue,
    kStringValue,
    kArrayValue
};

class CCBValue : public Object
{
private:
    union 
    {
        int nValue;
        float fValue;
    } mValue;
    
    std::string _value;
    Array* _arrValue;
    int mType;
    
public:
    static CCBValue* create(int nValue);
    static CCBValue* create(bool bValue);
    static CCBValue* create(float fValue);
    static CCBValue* create(unsigned char byte);
    static CCBValue* create(const char* pStr);
    static CCBValue* create(Array* pArr);

    
    int getIntValue();
    float getFloatValue();
    bool getBoolValue();
    unsigned char getByteValue();
    const char* getStringValue();
    Array *getArrayValue();
    
    int getType();
};

NS_CC_EXT_END

#endif // __CCB_VALUE_H__
