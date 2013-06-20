#include "CCMenuItemLoader.h"



#define PROPERTY_BLOCK "block"
#define PROPERTY_ISENABLED "isEnabled"

NS_CC_EXT_BEGIN

void MenuItemLoader::onHandlePropTypeBlock(Node * pNode, Node * pParent, const char * pPropertyName, BlockData * pBlockData, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_BLOCK) == 0) {
        if (NULL != pBlockData) // Add this condition to allow MenuItemImage without target/selector predefined 
        {
            ((MenuItem *)pNode)->setCallback( std::bind( pBlockData->mSELMenuHandler, pBlockData->mTarget, std::placeholders::_1) );
//            ((MenuItem *)pNode)->setTarget(pBlockData->mTarget, pBlockData->mSELMenuHandler);
        }
    } else {
        NodeLoader::onHandlePropTypeBlock(pNode, pParent, pPropertyName, pBlockData, pCCBReader);
    }
}

void MenuItemLoader::onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_ISENABLED) == 0) {
        ((MenuItem *)pNode)->setEnabled(pCheck);
    } else {
        NodeLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}

NS_CC_EXT_END