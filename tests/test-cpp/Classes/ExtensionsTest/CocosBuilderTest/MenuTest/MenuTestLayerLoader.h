#ifndef _MENUTESTLAYERLOADER_H_
#define _MENUTESTLAYERLOADER_H_

#include "MenuTestLayer.h"

/* Forward declaration. */
class CCBReader;

class MenuTestLayerLoader : public cocosbuilder::LayerLoader {
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MenuTestLayerLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MenuTestLayer);
};

#endif
