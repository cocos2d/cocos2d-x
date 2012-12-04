#include "CCMenuItemImageLoader.h"



#define PROPERTY_NORMALDISPLAYFRAME "normalSpriteFrame"
#define PROPERTY_SELECTEDDISPLAYFRAME "selectedSpriteFrame"
#define PROPERTY_DISABLEDDISPLAYFRAME "disabledSpriteFrame"

NS_CC_EXT_BEGIN

void CCMenuItemImageLoader::onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSpriteFrame * pCCSpriteFrame, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_NORMALDISPLAYFRAME) == 0) {
        if(pCCSpriteFrame != NULL) {
            ((CCMenuItemImage *)pNode)->setNormalSpriteFrame(pCCSpriteFrame);
        }
    } else if(strcmp(pPropertyName, PROPERTY_SELECTEDDISPLAYFRAME) == 0) {
        if(pCCSpriteFrame != NULL) {
            ((CCMenuItemImage *)pNode)->setSelectedSpriteFrame(pCCSpriteFrame);
        }
    } else if(strcmp(pPropertyName, PROPERTY_DISABLEDDISPLAYFRAME) == 0) {
        if(pCCSpriteFrame != NULL) {
            ((CCMenuItemImage *)pNode)->setDisabledSpriteFrame(pCCSpriteFrame);
        }
    } else {
        CCMenuItemLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pCCSpriteFrame, pCCBReader);
    }
}

NS_CC_EXT_END
