#import "CCMenuItemImageLoader.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define PROPERTY_NORMALDISPLAYFRAME "normalSpriteFrame"
#define PROPERTY_SELECTEDDISPLAYFRAME "selectedSpriteFrame"
#define PROPERTY_DISABLEDDISPLAYFRAME "disabledSpriteFrame"

CCMenuItemImage * CCMenuItemImageLoader::createCCNode(CCNode * pParent, CCBReader * pCCBReader) {
    return CCMenuItemImage::node();
}

void CCMenuItemImageLoader::onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, std::string pPropertyName, CCSpriteFrame * pCCSpriteFrame, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_NORMALDISPLAYFRAME) == 0) {
        ((CCMenuItemImage *)pNode)->setNormalSpriteFrame(pCCSpriteFrame);
    } else if(pPropertyName.compare(PROPERTY_SELECTEDDISPLAYFRAME) == 0) {
        ((CCMenuItemImage *)pNode)->setSelectedSpriteFrame(pCCSpriteFrame);
    } else if(pPropertyName.compare(PROPERTY_DISABLEDDISPLAYFRAME) == 0) {
        ((CCMenuItemImage *)pNode)->setDisabledSpriteFrame(pCCSpriteFrame);
    } else {
        CCMenuItemLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pCCSpriteFrame, pCCBReader);
    }
}