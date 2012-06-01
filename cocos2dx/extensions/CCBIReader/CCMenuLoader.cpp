#import "CCMenuLoader.h"

using namespace cocos2d;
using namespace cocos2d::extension;


CCMenu * CCMenuLoader::createCCNode(CCNode * pParent, CCBReader * pCCBReader) {
    return CCMenu::node();
}