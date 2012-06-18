#ifndef _CCB_CCBFILELOADER_H_
#define _CCB_CCBFILELOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CC_DLL CCBFileLoader : public CCNodeLoader {
    public:
        virtual ~CCBFileLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCBFileLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCNode);

        virtual void onHandlePropTypeCCBFile(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCNode * pCCBFileNode, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
