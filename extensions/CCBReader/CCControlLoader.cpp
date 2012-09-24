#include "CCControlLoader.h"


NS_CC_EXT_BEGIN

#define PROPERTY_ENABLED "enabled"
#define PROPERTY_SELECTED "selected"
#define PROPERTY_CCCONTROL "ccControl"

void CCControlLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, bool pCheck, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_ENABLED) == 0) {
        ((CCControl *)pNode)->setEnabled(pCheck);
    } else if(pPropertyName->compare(PROPERTY_SELECTED) == 0) {
        ((CCControl *)pNode)->setSelected(pCheck);
    } else {
        CCNodeLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}

void CCControlLoader::onHandlePropTypeBlockCCControl(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, BlockCCControlData * pBlockCCControlData, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_CCCONTROL) == 0) {
        ((CCControl *)pNode)->addTargetWithActionForControlEvents(pBlockCCControlData->mTarget, pBlockCCControlData->mSELCCControlHandler, pBlockCCControlData->mControlEvents);
    } else {
        CCNodeLoader::onHandlePropTypeBlockCCControl(pNode, pParent, pPropertyName, pBlockCCControlData, pCCBReader);
    }
}

NS_CC_EXT_END