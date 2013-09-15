#ifndef __CCB_VALUE_H__
#define __CCB_VALUE_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"

/*
 These classes are wrapper of basic types, such as Color3B
 */

NS_CC_EXT_BEGIN

class Color3BWapper : public Object
{
public:
    static Color3BWapper* create(const Color3B& color);
    
    const Color3B& getColor() const;
    
private:
    Color3B color;
};



class CCBValue : public Object
{
public:
    
    enum class Type
    {
        INT,
        FLOAT,
        BOOL,
        UNSIGNED_CHAR,
        STRING,
        ARRAY
    };
    
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
    
    Type getType();
    
private:
    union
    {
        int intValue;
        float floatValue;
    } _value;
    
    std::string _strValue;
    Array* _arrValue;
    Type _type;
};

NS_CC_EXT_END

#endif // __CCB_VALUE_H__
