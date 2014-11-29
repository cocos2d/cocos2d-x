#include "CCTextFieldLoader.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;

#define PROPERTY_PREFERREDSIZE "preferredSize"
#define PROPERTY_SPRITEFRAME "backgroundSpriteFrame"
#define PROPERTY_PADDING "padding"
#define PROPERTY_BLOCK "block"

namespace spritebuilder {
    
void EditBoxLoader::onHandlePropTypeSize(Node * pNode, Node * pParent, const char* pPropertyName, Size pSize, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_PREFERREDSIZE) == 0) {
        ((ExtTextField*)pNode)->setPreferredSize(pSize);
        ((ExtTextField*)pNode)->setFontSize(pSize.height*2/3);
    } else {
        NodeLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, pSize, ccbReader);
    }
}
    
void EditBoxLoader::onHandlePropTypeSpriteFrame(Node * pNode, Node * pParent, const char * pPropertyName, SpriteFrame * pSpriteFrame, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_SPRITEFRAME) == 0) {
        ((ExtTextField*)pNode)->setBackgroundSpriteFrame(pSpriteFrame);
    } else {
        NodeLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pSpriteFrame, ccbReader);
    }
}
    
void EditBoxLoader::onHandlePropTypeFloatScale(Node * pNode, Node * pParent, const char* pPropertyName, float pFloatScale, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_PADDING) == 0) {
    } else {
        NodeLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pFloatScale, ccbReader);
    }
}
void EditBoxLoader::onHandlePropTypeBlockControl(Node * pNode, Node * pParent, const char * pPropertyName, BlockControlData * pBlockControlData, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_BLOCK) == 0) {
            ((ExtTextField*)pNode)->setTargetSelector(pBlockControlData->_target, pBlockControlData->mSELControlHandler);
    } else {
            NodeLoader::onHandlePropTypeBlockControl(pNode, pParent, pPropertyName, pBlockControlData, ccbReader);
    }
}

}
