#include "CCLayerLoader.h"




#define PROPERTY_TOUCH_ENABLED "isTouchEnabled"
#define PROPERTY_ACCELEROMETER_ENABLED "isAccelerometerEnabled"
#define PROPERTY_MOUSE_ENABLED "isMouseEnabled"
#define PROPERTY_KEYBOARD_ENABLED "isKeyboardEnabled"

NS_CC_EXT_BEGIN

void CCLayerLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, bool pCheck, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_TOUCH_ENABLED) == 0) {
        ((CCLayer *)pNode)->setTouchEnabled(pCheck);
    } else if(pPropertyName->compare(PROPERTY_ACCELEROMETER_ENABLED) == 0) {
        ((CCLayer *)pNode)->setAccelerometerEnabled(pCheck);
    } else if(pPropertyName->compare(PROPERTY_MOUSE_ENABLED) == 0) {
        // TODO XXX
        CCLOG("The property '%s' is not supported!", PROPERTY_MOUSE_ENABLED);
    } else if(pPropertyName->compare(PROPERTY_KEYBOARD_ENABLED) == 0) {
        // TODO XXX
        CCLOG("The property '%s' is not supported!", PROPERTY_KEYBOARD_ENABLED);
        // This comes closest: ((CCLayer *)pNode)->setKeypadEnabled(pCheck);
    } else {
        CCNodeLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}

NS_CC_EXT_END
