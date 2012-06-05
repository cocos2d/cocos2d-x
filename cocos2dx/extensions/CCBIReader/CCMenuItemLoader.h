#ifndef _CCMENUITEM_LOADER_H_
#define _CCMENUITEM_LOADER_H_

#include "CCLayerLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCMenuItemLoader : public CCNodeLoader {
    protected:
        virtual CCMenuItem * createCCNode(CCNode *, CCBReader *) = 0;

        virtual void onHandlePropTypeBlock(CCNode * pNode, CCNode * pParent, const char * pPropertyName, BlockData *, CCBReader *);
        virtual void onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool, CCBReader *);
};

NS_CC_EXT_END

#endif
