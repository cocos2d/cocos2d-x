#ifndef _PARTICLESYSTEMTESTLOADER_H_
#define _PARTICLESYSTEMTESTLOADER_H_

#include "ParticleSystemTestLayer.h"

/* Forward declaration. */
class CCBReader;

class ParticleSystemTestLayerLoader : public cocosbuilder::LayerLoader {
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ParticleSystemTestLayerLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ParticleSystemTestLayer);
};

#endif
