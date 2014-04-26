#ifndef __CCB_SEQUENCE_PROPERTY_H__
#define __CCB_SEQUENCE_PROPERTY_H__

#include "base/CCRef.h"
#include "base/CCVector.h"
#include "CCBKeyframe.h"

namespace cocosbuilder {

class CCBSequenceProperty : public cocos2d::Ref
{
public:
    /**
     * @js ctor
     */
    CCBSequenceProperty();
    /**
     * @js NA
     * @lua NA
     */
    ~CCBSequenceProperty();
    
    virtual bool init();
    
    const char* getName();
    void setName(const char* pName);
    
    int getType();
    void setType(int type);
    
    cocos2d::Vector<CCBKeyframe*>& getKeyframes();

private:
    std::string _name;
    int _type;
    cocos2d::Vector<CCBKeyframe*> _keyframes;
};

}

#endif // __CCB_SEQUENCE_PROPERTY_H__
