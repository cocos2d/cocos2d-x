#ifndef _CCB_CCMENUITEMIMAGELOADER_H_
#define _CCB_CCMENUITEMIMAGELOADER_H_

#include "CCMenuItemLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class MenuItemImageLoader : public MenuItemLoader {
    public:
        virtual ~MenuItemImageLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MenuItemImageLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MenuItemImage);

        virtual void onHandlePropTypeSpriteFrame(Node * pNode, Node * pParent, const char * pPropertyName, SpriteFrame * pSpriteFrame, CCBReader * ccbReader);
};

NS_CC_EXT_END

#endif
