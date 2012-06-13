#include "TestHeaderLayerLoader.h"

USING_NS_CC;
USING_NS_CC_EXT;

TestHeaderLayer * TestHeaderLayerLoader::createCCNode(CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) {
    return TestHeaderLayer::node();
}