#include "CCMenuItemLoader.h"

using namespace cocos2d;

#define PROPERTY_BLOCK "block"
#define PROPERTY_ISENABLED "isEnabled"

namespace cocosbuilder {

void MenuItemLoader::onHandlePropTypeBlock(Node * pNode, Node * pParent, const char * pPropertyName, BlockData * pBlockData, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_BLOCK) == 0) {
        if (NULL != pBlockData) // Add this condition to allow MenuItemImage without target/selector predefined 
        {
            ((MenuItem *)pNode)->setCallback( std::bind( pBlockData->mSELMenuHandler, pBlockData->_target, std::placeholders::_1) );
//            ((MenuItem *)pNode)->setTarget(pBlockData->_target, pBlockData->mSELMenuHandler);
        }
    } else {
        NodeLoader::onHandlePropTypeBlock(pNode, pParent, pPropertyName, pBlockData, ccbReader);
    }
}

void MenuItemLoader::onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_ISENABLED) == 0) {
        ((MenuItem *)pNode)->setEnabled(pCheck);
    } else {
        NodeLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, ccbReader);
    }
}

}
