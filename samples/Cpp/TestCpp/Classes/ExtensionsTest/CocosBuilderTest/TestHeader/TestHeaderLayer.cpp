#include "TestHeaderLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

SEL_MenuHandler TestHeaderLayer::onResolveCCBCCMenuItemSelector(Object * pTarget, const char * pSelectorName) {
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBackClicked", TestHeaderLayer::onBackClicked);

    return NULL;    
}

Control::Handler TestHeaderLayer::onResolveCCBCCControlSelector(Object * pTarget, const char * pSelectorName) {

    return NULL;
}

void TestHeaderLayer::onNodeLoaded(cocos2d::Node * node, cocosbuilder::NodeLoader * nodeLoader)
{
    CCLOG("TestHeaderLayer::onNodeLoaded");
}

void TestHeaderLayer::onBackClicked(cocos2d::Object *pSender) {
    Director::getInstance()->popScene();
}