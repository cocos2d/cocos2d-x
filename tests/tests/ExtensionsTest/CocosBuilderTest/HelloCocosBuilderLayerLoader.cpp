#include "HelloCocosBuilderLayerLoader.h"

USING_NS_CC;
USING_NS_CC_EXT;

HelloCocosBuilderLayer * HelloCocosBuilderLayerLoader::createCCNode(CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) {
    return HelloCocosBuilderLayer::node();
}