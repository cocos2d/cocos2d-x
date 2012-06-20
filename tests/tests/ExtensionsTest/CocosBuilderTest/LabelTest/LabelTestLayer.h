#ifndef _LABELTESTLAYER_H_
#define _LABELTESTLAYER_H_

#include "cocos2d.h"
#include "extensions/CCBReader/CCBReader.h"

class LabelTestLayer : public cocos2d::CCLayer {
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LabelTestLayer, create);
};

#endif