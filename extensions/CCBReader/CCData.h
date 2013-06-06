
#ifndef __CCB_CCDATA_H__
#define __CCB_CCDATA_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN

class CCData : public CCObject
{
public:
    CCData(unsigned char *pBytes, const unsigned long nSize);
    CCData(CCData *pData);
    ~CCData();
    
    unsigned char* getBytes();
    unsigned long getSize();
    
private:
    unsigned char* m_pBytes;
    unsigned long m_nSize;
};

NS_CC_EXT_END

#endif // __CCB_CCDATA_H__
