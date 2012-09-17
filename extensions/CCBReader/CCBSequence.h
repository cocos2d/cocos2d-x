#ifndef __CCB_CCSEQUENCE_H__
#define __CCB_CCSEQUENCE_H__

#include "cocos-ext.h"
#include <string>

NS_CC_EXT_BEGIN

class CCBSequence : public cocos2d::CCObject
{
private:
    float mDuration;
    std::string mName;
    int mSequenceId;
    int mChainedSequenceId;
    
public:
    CCBSequence();
    
    float getDuration();
    void setDuration(float fDuration);
    
    const char* getName();
    void setName(const char *pName);
    
    int getSequenceId();
    void setSequenceId(int nSequenceId);
    
    int getChainedSequenceId();
    void setChainedSequenceId(int nChainedSequenceId);
};


NS_CC_EXT_END


#endif // __CCB_CCSEQUENCE_H__
