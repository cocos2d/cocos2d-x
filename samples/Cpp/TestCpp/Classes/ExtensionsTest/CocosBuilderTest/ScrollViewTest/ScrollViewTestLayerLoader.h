#ifndef _SCROLLVIEWTESTLAYERLOADER_H_
#define _SCROLLVIEWTESTLAYERLOADER_H_

#include "ScrollViewTestLayer.h"

/* Forward declaration. */
class CCBReader;

class ScrollViewTestLayerLoader : public cocos2d::extension::CCLayerLoader {
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ScrollViewTestLayerLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ScrollViewTestLayer);
};

#endif
