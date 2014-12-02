#include "CCControlLoader.h"

using namespace cocos2d;
using namespace cocos2d::extension;

namespace spritebuilder {

#define PROPERTY_ENABLED "enabled"
#define PROPERTY_SELECTED "selected"
#define PROPERTY_CCCONTROL "ccControl"
#define PROPERTY_BLOCK     "block"

void ControlLoader::onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_ENABLED) == 0) {
        ((Control *)pNode)->setEnabled(pCheck);
    } else if(strcmp(pPropertyName, PROPERTY_SELECTED) == 0) {
        ((Control *)pNode)->setSelected(pCheck);
    } else {
        NodeLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, ccbReader);
    }
}
    
void ControlLoader::onHandlePropTypeBlock(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, BlockData * pBlockData, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_BLOCK) == 0) {
        if (pBlockData)
            ((Control *)pNode)->addTargetWithActionForControlEvents(pBlockData->_target, (Control::Handler)pBlockData->mSELMenuHandler, cocos2d::extension::Control::EventType::TOUCH_DOWN);
    } else {
        NodeLoader::onHandlePropTypeBlock(pNode, pParent, pPropertyName, pBlockData, ccbReader);
    }

}
    
void ControlLoader::onHandlePropTypeBlockControl(Node * pNode, Node * pParent, const char * pPropertyName, BlockControlData * pBlockControlData, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_CCCONTROL) == 0) {
        ((Control *)pNode)->addTargetWithActionForControlEvents(pBlockControlData->_target, pBlockControlData->mSELControlHandler, pBlockControlData->mControlEvents);
    } else if(strcmp(pPropertyName, PROPERTY_BLOCK) == 0) {
        ((Control *)pNode)->addTargetWithActionForControlEvents(pBlockControlData->_target, pBlockControlData->mSELControlHandler, cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
    } else {
        NodeLoader::onHandlePropTypeBlockControl(pNode, pParent, pPropertyName, pBlockControlData, ccbReader);
    }
}

}