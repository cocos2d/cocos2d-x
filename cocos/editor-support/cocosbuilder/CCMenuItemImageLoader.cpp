#include "editor-support/cocosbuilder/CCMenuItemImageLoader.h"

using namespace cocos2d;

#define PROPERTY_NORMALDISPLAYFRAME "normalSpriteFrame"
#define PROPERTY_SELECTEDDISPLAYFRAME "selectedSpriteFrame"
#define PROPERTY_DISABLEDDISPLAYFRAME "disabledSpriteFrame"

namespace cocosbuilder {

void MenuItemImageLoader::onHandlePropTypeSpriteFrame(Node * pNode, Node * pParent, const char * pPropertyName, SpriteFrame * pSpriteFrame, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_NORMALDISPLAYFRAME) == 0) {
        if(pSpriteFrame != nullptr) {
            ((MenuItemImage *)pNode)->setNormalSpriteFrame(pSpriteFrame);
        }
    } else if(strcmp(pPropertyName, PROPERTY_SELECTEDDISPLAYFRAME) == 0) {
        if(pSpriteFrame != nullptr) {
            ((MenuItemImage *)pNode)->setSelectedSpriteFrame(pSpriteFrame);
        }
    } else if(strcmp(pPropertyName, PROPERTY_DISABLEDDISPLAYFRAME) == 0) {
        if(pSpriteFrame != nullptr) {
            ((MenuItemImage *)pNode)->setDisabledSpriteFrame(pSpriteFrame);
        }
    } else {
        MenuItemLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pSpriteFrame, ccbReader);
    }
}

}
