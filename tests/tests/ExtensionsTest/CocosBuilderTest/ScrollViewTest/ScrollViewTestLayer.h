#ifndef _SCROLLVIEWTESTLAYER_H_
#define _SCROLLVIEWTESTLAYER_H_

#include "cocos2d.h"
#include "extensions/CCBReader/CCBReader.h"

class ScrollViewTestLayer : public cocos2d::CCLayer {
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ScrollViewTestLayer, create);
};

#endif