#ifndef _PARTICLESYSTEMTESTLAYER_H_
#define _PARTICLESYSTEMTESTLAYER_H_

#include "cocos2d.h"
#include "extensions/CCBReader/CCBReader.h"

class ParticleSystemTestLayer : public cocos2d::CCLayer {
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ParticleSystemTestLayer, create);
};

#endif