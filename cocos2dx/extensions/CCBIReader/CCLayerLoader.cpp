#include "CCLayerLoader.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define PROPERTY_TOUCH_ENABLED "isTouchEnabled"
#define PROPERTY_ACCELEROMETER_ENABLED "isAccelerometerEnabled"
#define PROPERTY_MOUSE_ENABLED "isMouseEnabled"
#define PROPERTY_KEYBOARD_ENABLED "isKeyboardEnabled"

CCLayer * CCLayerLoader::createCCNode(CCNode * pParent, CCBReader * pCCBReader) {
    return CCLayer::node();
}

void CCLayerLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool pCheck, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_TOUCH_ENABLED) == 0) {
        ((CCLayer *)pNode)->setIsTouchEnabled(pCheck);
    } else if(strcmp(pPropertyName, PROPERTY_ACCELEROMETER_ENABLED) == 0) {
        ((CCLayer *)pNode)->setIsAccelerometerEnabled(pCheck);
    } else if(strcmp(pPropertyName, PROPERTY_MOUSE_ENABLED) == 0) {
        // TODO XXX
        CCLOG("The property '%s' is not supported!", PROPERTY_MOUSE_ENABLED);
    } else if(strcmp(pPropertyName, PROPERTY_KEYBOARD_ENABLED) == 0) {
        // TODO XXX
        CCLOG("The property '%s' is not supported!", PROPERTY_KEYBOARD_ENABLED);
        // This comes closest: ((CCLayer *)pNode)->setIsKeypadEnabled(pCheck);
    } else {
        CCNodeLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}
