
#ifndef __CCDATA_H__
#define __CCDATA_H__

#include "platform/CCPlatformMacros.h"
#include "CCObject.h"

NS_CC_BEGIN

class CC_DLL Data : public Object
{
public:
    Data(unsigned char *pBytes, const unsigned long nSize);
    Data(Data *pData);
    ~Data();
    
    static Data* create(unsigned char *pBytes, const unsigned long nSize)
    {
        Data* pRet = new Data(pBytes, nSize);
        if (pRet)
        {
            pRet->autorelease();
        }
        return pRet;
    }    
    
    unsigned char* getBytes() const;
    unsigned long getSize() const;
    
    /* override functions */
    virtual void acceptVisitor(DataVisitor &visitor) { visitor.visit(this); }

private:
    unsigned char* _bytes;
    unsigned long _size;
};

NS_CC_END

#endif // __CCDATA_H__
