#include "CCMenuItemImageLoader.h"



#define PROPERTY_NORMALDISPLAYFRAME "normalSpriteFrame"
#define PROPERTY_SELECTEDDISPLAYFRAME "selectedSpriteFrame"
#define PROPERTY_DISABLEDDISPLAYFRAME "disabledSpriteFrame"

NS_CC_EXT_BEGIN

void MenuItemImageLoader::onHandlePropTypeSpriteFrame(Node * pNode, Node * pParent, const char * pPropertyName, SpriteFrame * pSpriteFrame, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_NORMALDISPLAYFRAME) == 0) {
        if(pSpriteFrame != NULL) {
            ((MenuItemImage *)pNode)->setNormalSpriteFrame(pSpriteFrame);
        }
    } else if(strcmp(pPropertyName, PROPERTY_SELECTEDDISPLAYFRAME) == 0) {
        if(pSpriteFrame != NULL) {
            ((MenuItemImage *)pNode)->setSelectedSpriteFrame(pSpriteFrame);
        }
    } else if(strcmp(pPropertyName, PROPERTY_DISABLEDDISPLAYFRAME) == 0) {
        if(pSpriteFrame != NULL) {
            ((MenuItemImage *)pNode)->setDisabledSpriteFrame(pSpriteFrame);
        }
    } else {
        MenuItemLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pSpriteFrame, ccbReader);
    }
}

NS_CC_EXT_END
