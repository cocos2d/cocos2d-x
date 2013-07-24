#include "TestHeaderLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

SEL_MenuHandler TestHeaderLayer::onResolveCCBMenuItemSelector(Object * pTarget, const char * pSelectorName) {
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBackClicked", TestHeaderLayer::onBackClicked);

    return NULL;    
}

SEL_CCControlHandler TestHeaderLayer::onResolveCCBControlSelector(Object * pTarget, const char * pSelectorName) {

    return NULL;
}

void TestHeaderLayer::onNodeLoaded(cc::Node * node, cc::extension::NodeLoader * nodeLoader)
{
    CCLOG("TestHeaderLayer::onNodeLoaded");
}

void TestHeaderLayer::onBackClicked(cc::Object *pSender) {
    Director::getInstance()->popScene();
}