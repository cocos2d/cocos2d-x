#ifndef _CCB_CCMENUITEMIMAGELOADER_H_
#define _CCB_CCMENUITEMIMAGELOADER_H_

#include "CCMenuItemLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCMenuItemImageLoader : public CCMenuItemLoader {
    public:
        STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCMenuItemImageLoader, loader);

    protected:
        virtual CCMenuItemImage * createCCNode(CCNode *, CCBReader *);

        virtual void onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSpriteFrame *, CCBReader *);
};

NS_CC_EXT_END

#endif
