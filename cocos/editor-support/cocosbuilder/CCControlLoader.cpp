#include "CCControlLoader.h"

using namespace cocos2d;
using namespace cocos2d::extension;

namespace cocosbuilder {

#define PROPERTY_ENABLED "enabled"
#define PROPERTY_SELECTED "selected"
#define PROPERTY_CCCONTROL "ccControl"

void ControlLoader::onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_ENABLED) == 0) {
        ((Control *)pNode)->setEnabled(pCheck);
    } else if(strcmp(pPropertyName, PROPERTY_SELECTED) == 0) {
        ((Control *)pNode)->setSelected(pCheck);
    } else {
        NodeLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, ccbReader);
    }
}

void ControlLoader::onHandlePropTypeBlockControl(Node * pNode, Node * pParent, const char * pPropertyName, BlockControlData * pBlockControlData, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_CCCONTROL) == 0) {
        ((Control *)pNode)->addTargetWithActionForControlEvents(pBlockControlData->_target, pBlockControlData->mSELControlHandler, pBlockControlData->mControlEvents);
    } else {
        NodeLoader::onHandlePropTypeBlockControl(pNode, pParent, pPropertyName, pBlockControlData, ccbReader);
    }
}

}