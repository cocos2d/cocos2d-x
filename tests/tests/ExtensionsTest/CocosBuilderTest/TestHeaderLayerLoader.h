#ifndef _TESTHEADERLAYERLOADER_H_
#define _TESTHEADERLAYERLOADER_H_

#include "CCLayerLoader.h"
#include "TestHeaderLayer.h"

/* Forward declaration. */
class CCBReader;

class TestHeaderLayerLoader : public cocos2d::extension::CCLayerLoader {
    public:
        STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TestHeaderLayerLoader, loader);

    protected:
        virtual TestHeaderLayer * createCCNode(cocos2d::CCNode *, cocos2d::extension::CCBReader *);
};

#endif
