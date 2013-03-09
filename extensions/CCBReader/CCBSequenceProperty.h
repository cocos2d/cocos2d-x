#ifndef __CCB_SEQUENCE_PROPERTY_H__
#define __CCB_SEQUENCE_PROPERTY_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "CCBKeyframe.h"

NS_CC_EXT_BEGIN

class CCBSequenceProperty : public CCObject
{
private:
    std::string mName;
    int mType;
    CCArray *mKeyframes;
    
public:
    CCBSequenceProperty();
    ~CCBSequenceProperty();
    
    virtual bool init();
    
    const char* getName();
    void setName(const char* pName);
    
    int getType();
    void setType(int nType);
    
    CCArray* getKeyframes();
};

NS_CC_EXT_END

#endif // __CCB_SEQUENCE_PROPERTY_H__
