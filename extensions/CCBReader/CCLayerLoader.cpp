#include "CCLayerLoader.h"




#define PROPERTY_TOUCH_ENABLED "isTouchEnabled"
#define PROPERTY_ACCELEROMETER_ENABLED "isAccelerometerEnabled"
#define PROPERTY_MOUSE_ENABLED "isMouseEnabled"
#define PROPERTY_KEYBOARD_ENABLED "isKeyboardEnabled"

NS_CC_EXT_BEGIN

void LayerLoader::onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_TOUCH_ENABLED) == 0) {
        ((Layer *)pNode)->setTouchEnabled(pCheck);
    } else if(strcmp(pPropertyName, PROPERTY_ACCELEROMETER_ENABLED) == 0) {
        ((Layer *)pNode)->setAccelerometerEnabled(pCheck);
    } else if(strcmp(pPropertyName, PROPERTY_MOUSE_ENABLED) == 0) {
        // TODO XXX
        CCLOG("The property '%s' is not supported!", PROPERTY_MOUSE_ENABLED);
    } else if(strcmp(pPropertyName, PROPERTY_KEYBOARD_ENABLED) == 0) {
        // TODO XXX
        CCLOG("The property '%s' is not supported!", PROPERTY_KEYBOARD_ENABLED);
        // This comes closest: ((Layer *)pNode)->setKeypadEnabled(pCheck);
    } else {
        NodeLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, ccbReader);
    }
}

NS_CC_EXT_END
