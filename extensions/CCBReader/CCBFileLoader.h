#ifndef _CCB_CCBFILELOADER_H_
#define _CCB_CCBFILELOADER_H_

#include "CCNodeLoader.h"
#include "CCBReader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCBFileLoader : public NodeLoader {
    public:
        virtual ~CCBFileLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCBFileLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCBFile);

        virtual void onHandlePropTypeCCBFile(Node * pNode, Node * pParent, const char * pPropertyName, Node * pCCBFileNode, CCBReader * ccbReader);
};

NS_CC_EXT_END

#endif
