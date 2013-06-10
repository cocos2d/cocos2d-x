
#ifndef __CCDATA_H__
#define __CCDATA_H__

#include "platform/CCPlatformMacros.h"
#include "CCObject.h"

NS_CC_BEGIN

class CC_DLL CCData : public CCObject
{
public:
    CCData(unsigned char *pBytes, const unsigned long nSize);
    CCData(CCData *pData);
    ~CCData();
    
    static CCData* create(unsigned char *pBytes, const unsigned long nSize)
    {
        CCData* pRet = new CCData(pBytes, nSize);
        if (pRet)
        {
            pRet->autorelease();
        }
        return pRet;
    }    
    
    unsigned char* getBytes() const;
    unsigned long getSize() const;
    
    /* override functions */
    virtual void acceptVisitor(CCDataVisitor &visitor) { visitor.visit(this); }

private:
    unsigned char* m_pBytes;
    unsigned long m_nSize;
};

NS_CC_END

#endif // __CCDATA_H__
