#include "ButtonTestLayerLoader.h"

USING_NS_CC;
USING_NS_CC_EXT;

ButtonTestLayer * ButtonTestLayerLoader::createCCNode(CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) {
    return ButtonTestLayer::node();
}