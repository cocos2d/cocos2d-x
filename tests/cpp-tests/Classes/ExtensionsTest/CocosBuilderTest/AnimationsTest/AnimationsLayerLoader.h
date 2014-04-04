#ifndef _ANIMATIONSTESTLAYERLOADER_H_
#define _ANIMATIONSTESTLAYERLOADER_H_

#include "AnimationsTestLayer.h"

/* Forward declaration. */
class CCBReader;

class AnimationsTestLayerLoader : public cocosbuilder::LayerLoader {
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AnimationsTestLayerLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AnimationsTestLayer);
};

#endif
