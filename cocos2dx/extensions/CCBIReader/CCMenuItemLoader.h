#ifndef _CCMENUITEM_LOADER_H_
#define _CCMENUITEM_LOADER_H_

#include "CCLayerLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCMenuItemLoader : public CCNodeLoader {
    protected:
        virtual CCMenuItem * createCCNode(CCNode *, CCBReader *) = 0;

        virtual void onHandlePropTypeBlock(CCNode *, CCNode *, std::string, void *, CCBReader *);
        virtual void onHandlePropTypeCheck(CCNode *, CCNode *, std::string, bool, CCBReader *);
};

NS_CC_EXT_END

#endif
