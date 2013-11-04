#ifndef __CCB_VALUE_H__
#define __CCB_VALUE_H__

#include "cocos2d.h"

/*
 These classes are wrapper of basic types, such as Color3B
 */

namespace cocosbuilder {

class Color3BWapper : public cocos2d::Object
{
public:
    static Color3BWapper* create(const cocos2d::Color3B& color);
    
    const cocos2d::Color3B& getColor() const;
    
private:
    cocos2d::Color3B color;
};



class CCBValue : public cocos2d::Object
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
    static CCBValue* create(cocos2d::Array* pArr);

    
    int getIntValue();
    float getFloatValue();
    bool getBoolValue();
    unsigned char getByteValue();
    const char* getStringValue();
    cocos2d::Array *getArrayValue();
    
    Type getType();
    
private:
    union
    {
        int intValue;
        float floatValue;
    } _value;
    
    std::string _strValue;
    cocos2d::Array* _arrValue;
    Type _type;
};

}

#endif // __CCB_VALUE_H__
