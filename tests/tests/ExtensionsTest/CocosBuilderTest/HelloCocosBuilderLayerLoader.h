#ifndef _HELLOCOCOSBUILDERLAYERLOADER_H_
#define _HELLOCOCOSBUILDERLAYERLOADER_H_

#include "CCLayerLoader.h"
#include "HelloCocosBuilderLayer.h"

/* Forward declaration. */
class CCBReader;

class HelloCocosBuilderLayerLoader : public cocos2d::extension::CCLayerLoader {
    public:
        STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HelloCocosBuilderLayerLoader, loader);

    protected:
        virtual HelloCocosBuilderLayer * createCCNode(cocos2d::CCNode *, cocos2d::extension::CCBReader *);
};

#endif
