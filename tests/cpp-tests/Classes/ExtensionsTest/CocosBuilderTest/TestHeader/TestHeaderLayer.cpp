#include "TestHeaderLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

SEL_MenuHandler TestHeaderLayer::onResolveCCBCCMenuItemSelector(Ref * pTarget, const char * pSelectorName) {
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBackClicked", TestHeaderLayer::onBackClicked);

    return NULL;    
}

Control::Handler TestHeaderLayer::onResolveCCBCCControlSelector(Ref * pTarget, const char * pSelectorName) {

    return NULL;
}

void TestHeaderLayer::onNodeLoaded(cocos2d::Node * node, cocosbuilder::NodeLoader * nodeLoader)
{
    CCLOG("TestHeaderLayer::onNodeLoaded");
}

void TestHeaderLayer::onBackClicked(cocos2d::Ref *pSender) {
    Director::getInstance()->popScene();
}
