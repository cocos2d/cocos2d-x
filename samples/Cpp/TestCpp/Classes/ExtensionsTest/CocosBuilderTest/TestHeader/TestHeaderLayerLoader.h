#ifndef _TESTHEADERLAYERLOADER_H_
#define _TESTHEADERLAYERLOADER_H_

#include "TestHeaderLayer.h"

/* Forward declaration. */
class CCBReader;

class TestHeaderLayerLoader : public cocosbuilder::LayerLoader {
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TestHeaderLayerLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(TestHeaderLayer);
};

#endif
