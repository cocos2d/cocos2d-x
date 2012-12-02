#include "CCMenuItemLoader.h"



#define PROPERTY_BLOCK "block"
#define PROPERTY_ISENABLED "isEnabled"

NS_CC_EXT_BEGIN

void CCMenuItemLoader::onHandlePropTypeBlock(CCNode * pNode, CCNode * pParent, const char * pPropertyName, BlockData * pBlockData, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_BLOCK) == 0) {
        if (NULL != pBlockData) // Add this condition to allow CCMenuItemImage without target/selector predefined 
        {
            ((CCMenuItem *)pNode)->setTarget(pBlockData->mTarget, pBlockData->mSELMenuHandler);
        }
    } else {
        CCNodeLoader::onHandlePropTypeBlock(pNode, pParent, pPropertyName, pBlockData, pCCBReader);
    }
}

void CCMenuItemLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool pCheck, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_ISENABLED) == 0) {
        ((CCMenuItem *)pNode)->setEnabled(pCheck);
    } else {
        CCNodeLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}

NS_CC_EXT_END