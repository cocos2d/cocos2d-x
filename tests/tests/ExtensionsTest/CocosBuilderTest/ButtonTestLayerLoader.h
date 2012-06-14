#ifndef _BUTTONTESTLAYERLOADER_H_
#define _BUTTONTESTLAYERLOADER_H_

#include "extensions/CCBReader/CCLayerLoader.h"
#include "ButtonTestLayer.h"

/* Forward declaration. */
class CCBReader;

class ButtonTestLayerLoader : public cocos2d::extension::CCLayerLoader {
    public:
        STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ButtonTestLayerLoader, loader);

    protected:
        virtual ButtonTestLayer * createCCNode(cocos2d::CCNode *, cocos2d::extension::CCBReader *);
};

#endif
