#ifndef _SPRITETESTLAYER_H_
#define _SPRITETESTLAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

class SpriteTestLayer : public cocos2d::CCLayer {
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SpriteTestLayer, create);
};

#endif