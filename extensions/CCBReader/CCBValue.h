#ifndef __CCB_VALUE_H__
#define __CCB_VALUE_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"

/*
 These classes are wrapper of basic types, such as ccColor3B
 */

NS_CC_EXT_BEGIN
/**
 *  @js NA
 *  @lua NA
 */
class ccColor3BWapper : public CCObject
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
/**
 *  @js NA
 *  @lua NA
 */
class CCBValue : public CCObject
{
private:
    union 
    {
        int nValue;
        float fValue;
    } mValue;
    
    std::string m_strValue;
    CCArray* m_arrValue;
    int mType;
    
public:
    static CCBValue* create(int nValue);
    static CCBValue* create(bool bValue);
    static CCBValue* create(float fValue);
    static CCBValue* create(unsigned char byte);
    static CCBValue* create(const char* pStr);
    static CCBValue* create(CCArray* pArr);

    
    int getIntValue();
    float getFloatValue();
    bool getBoolValue();
    unsigned char getByteValue();
    const char* getStringValue();
    CCArray *getArrayValue();
    
    int getType();
};

NS_CC_EXT_END

#endif // __CCB_VALUE_H__
