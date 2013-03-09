#ifndef _BUTTONTESTLAYERLOADER_H_
#define _BUTTONTESTLAYERLOADER_H_

#include "ButtonTestLayer.h"

/* Forward declaration. */
class CCBReader;

class ButtonTestLayerLoader : public cocos2d::extension::CCLayerLoader {
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ButtonTestLayerLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ButtonTestLayer);
};

#endif
