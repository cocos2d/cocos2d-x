#ifndef _CCB_CCMENUITEMLOADER_H_
#define _CCB_CCMENUITEMLOADER_H_

#include "CCLayerLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CC_DLL CCMenuItemLoader : public CCNodeLoader {
    public:
        virtual ~CCMenuItemLoader() {};

    protected:
        CCB_PURE_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCMenuItem);

        virtual void onHandlePropTypeBlock(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, BlockData *, CCBReader *);
        virtual void onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, bool, CCBReader *);
};

NS_CC_EXT_END

#endif
