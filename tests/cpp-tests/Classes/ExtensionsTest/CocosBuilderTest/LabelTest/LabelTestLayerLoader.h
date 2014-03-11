#ifndef _LABELTESTLAYERLOADER_H_
#define _LABELTESTLAYERLOADER_H_

#include "LabelTestLayer.h"

/* Forward declaration. */
class CCBReader;

class LabelTestLayerLoader : public cocosbuilder::LayerLoader {
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LabelTestLayerLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LabelTestLayer);
};

#endif
