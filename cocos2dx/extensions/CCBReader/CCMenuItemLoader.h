#ifndef _CCB_CCMENUITEMLOADER_H_
#define _CCB_CCMENUITEMLOADER_H_

#include "CCLayerLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CC_DLL CCMenuItemLoader : public CCNodeLoader {
    protected:
        virtual CCMenuItem * createCCNode(CCNode *, CCBReader *) = 0;

        virtual void onHandlePropTypeBlock(CCNode * pNode, CCNode * pParent, const char * pPropertyName, BlockData *, CCBReader *);
        virtual void onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool, CCBReader *);
};

NS_CC_EXT_END

#endif
