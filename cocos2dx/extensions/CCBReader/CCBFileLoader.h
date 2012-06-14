#ifndef _CCB_CCBFILELOADER_H_
#define _CCB_CCBFILELOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCBFileLoader : public CCNodeLoader {
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCBFileLoader, loader);

    protected:
        virtual CCNode * createCCNode(CCNode *, CCBReader *);

        virtual void onHandlePropTypeCCBFile(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCNode *, CCBReader *);
};

NS_CC_EXT_END

#endif
