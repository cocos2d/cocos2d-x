#ifndef _HELLOCOCOSBUILDERLAYERLOADER_H_
#define _HELLOCOCOSBUILDERLAYERLOADER_H_

#include "HelloCocosBuilderLayer.h"

/* Forward declaration. */
class CCBReader;

class HelloCocosBuilderLayerLoader : public cocosbuilder::LayerLoader {
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HelloCocosBuilderLayerLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HelloCocosBuilderLayer);
};

#endif
