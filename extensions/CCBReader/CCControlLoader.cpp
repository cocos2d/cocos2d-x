#include "CCControlLoader.h"


NS_CC_EXT_BEGIN

#define PROPERTY_ENABLED "enabled"
#define PROPERTY_SELECTED "selected"
#define PROPERTY_CCCONTROL "ccControl"

void ControlLoader::onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_ENABLED) == 0) {
        ((Control *)pNode)->setEnabled(pCheck);
    } else if(strcmp(pPropertyName, PROPERTY_SELECTED) == 0) {
        ((Control *)pNode)->setSelected(pCheck);
    } else {
        NodeLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}

void ControlLoader::onHandlePropTypeBlockControl(Node * pNode, Node * pParent, const char * pPropertyName, BlockControlData * pBlockControlData, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_CCCONTROL) == 0) {
        ((Control *)pNode)->addTargetWithActionForControlEvents(pBlockControlData->mTarget, pBlockControlData->mSELControlHandler, pBlockControlData->mControlEvents);
    } else {
        NodeLoader::onHandlePropTypeBlockControl(pNode, pParent, pPropertyName, pBlockControlData, pCCBReader);
    }
}

NS_CC_EXT_END