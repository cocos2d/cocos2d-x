#ifndef _CCMENUITEMIMAGE_LOADER_H_
#define _CCMENUITEMIMAGE_LOADER_H_

#include "CCMenuItemLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCMenuItemImageLoader : public CCMenuItemLoader {
    protected:
        virtual CCMenuItemImage * createCCNode(CCNode *, CCBReader *);

        virtual void onHandlePropTypeSpriteFrame(CCNode *, CCNode *, std::string, CCSpriteFrame *, CCBReader *);
};

NS_CC_EXT_END

#endif
