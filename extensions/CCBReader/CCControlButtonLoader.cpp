#include "CCControlButtonLoader.h"


NS_CC_EXT_BEGIN;

#define PROPERTY_ZOOMONTOUCHDOWN "zoomOnTouchDown"
#define PROPERTY_TITLE_NORMAL "title|1"
#define PROPERTY_TITLE_HIGHLIGHTED "title|2"
#define PROPERTY_TITLE_DISABLED "title|3"
#define PROPERTY_TITLECOLOR_NORMAL "titleColor|1"
#define PROPERTY_TITLECOLOR_HIGHLIGHTED "titleColor|2"
#define PROPERTY_TITLECOLOR_DISABLED "titleColor|3"
#define PROPERTY_TITLETTF_NORMAL "titleTTF|1"
#define PROPERTY_TITLETTF_HIGHLIGHTED "titleTTF|2"
#define PROPERTY_TITLETTF_DISABLED "titleTTF|3"
#define PROPERTY_TITLETTFSIZE_NORMAL "titleTTFSize|1"
#define PROPERTY_TITLETTFSIZE_HIGHLIGHTED "titleTTFSize|2"
#define PROPERTY_TITLETTFSIZE_DISABLED "titleTTFSize|3"
#define PROPERTY_LABELANCHORPOINT "labelAnchorPoint"
#define PROPERTY_PREFEREDSIZE "preferedSize" // TODO Should be "preferredSize". This is a typo in cocos2d-iphone, cocos2d-x and CocosBuilder!
#define PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL "backgroundSpriteFrame|1"
#define PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED "backgroundSpriteFrame|2"
#define PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED "backgroundSpriteFrame|3"

void CCControlButtonLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, bool pCheck, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_ZOOMONTOUCHDOWN) == 0) {
        ((CCControlButton *)pNode)->setZoomOnTouchDown(pCheck);
    } else {
        CCControlLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}

void CCControlButtonLoader::onHandlePropTypeString(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCString * pString, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_TITLE_NORMAL) == 0) {
        ((CCControlButton *)pNode)->setTitleForState(pString, CCControlStateNormal);
    } else if(pPropertyName->compare(PROPERTY_TITLE_HIGHLIGHTED) == 0) {
        ((CCControlButton *)pNode)->setTitleForState(pString, CCControlStateHighlighted);
    } else if(pPropertyName->compare(PROPERTY_TITLE_DISABLED) == 0) {
        ((CCControlButton *)pNode)->setTitleForState(pString, CCControlStateDisabled);
    } else {
        CCControlLoader::onHandlePropTypeString(pNode, pParent, pPropertyName, pString, pCCBReader);
    }
}

void CCControlButtonLoader::onHandlePropTypeFontTTF(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCString * pFontTTF, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_TITLETTF_NORMAL) == 0) {
        ((CCControlButton *)pNode)->setTitleTTFForState(pFontTTF->getCString(), CCControlStateNormal);
    } else if(pPropertyName->compare(PROPERTY_TITLETTF_HIGHLIGHTED) == 0) {
        ((CCControlButton *)pNode)->setTitleTTFForState(pFontTTF->getCString(), CCControlStateHighlighted);
    } else if(pPropertyName->compare(PROPERTY_TITLETTF_DISABLED) == 0) {
        ((CCControlButton *)pNode)->setTitleTTFForState(pFontTTF->getCString(), CCControlStateDisabled);
    } else {
        CCControlLoader::onHandlePropTypeFontTTF(pNode, pParent, pPropertyName, pFontTTF, pCCBReader);
    }
}

void CCControlButtonLoader::onHandlePropTypeFloatScale(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, float pFloatScale, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_TITLETTFSIZE_NORMAL) == 0) {
        ((CCControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, CCControlStateNormal);
    } else if(pPropertyName->compare(PROPERTY_TITLETTFSIZE_HIGHLIGHTED) == 0) {
        ((CCControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, CCControlStateHighlighted);
    } else if(pPropertyName->compare(PROPERTY_TITLETTFSIZE_DISABLED) == 0) {
        ((CCControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, CCControlStateDisabled);
    } else {
        CCControlLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pFloatScale, pCCBReader);
    }
}

void CCControlButtonLoader::onHandlePropTypePoint(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCPoint pPoint, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_LABELANCHORPOINT) == 0) {
        ((CCControlButton *)pNode)->setLabelAnchorPoint(pPoint);
    } else {
        CCControlLoader::onHandlePropTypePoint(pNode, pParent, pPropertyName, pPoint, pCCBReader);
    }
}

void CCControlButtonLoader::onHandlePropTypeSize(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCSize pSize, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_PREFEREDSIZE) == 0) {
        ((CCControlButton *)pNode)->setPreferredSize(pSize);
    } else {
        CCControlLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, pSize, pCCBReader);
    }
}

void CCControlButtonLoader::onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCSpriteFrame * pCCSpriteFrame, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL) == 0) {
        if(pCCSpriteFrame != NULL) {
            ((CCControlButton *)pNode)->setBackgroundSpriteFrameForState(pCCSpriteFrame, CCControlStateNormal);
        }
    } else if(pPropertyName->compare(PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED) == 0) {
        if(pCCSpriteFrame != NULL) {
            ((CCControlButton *)pNode)->setBackgroundSpriteFrameForState(pCCSpriteFrame, CCControlStateHighlighted);
        }
    } else if(pPropertyName->compare(PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED) == 0) {
        if(pCCSpriteFrame != NULL) {
            ((CCControlButton *)pNode)->setBackgroundSpriteFrameForState(pCCSpriteFrame, CCControlStateDisabled);
        }
    } else {
        CCControlLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pCCSpriteFrame, pCCBReader);
    }
}

void CCControlButtonLoader::onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_TITLECOLOR_NORMAL) == 0) {
        ((CCControlButton *)pNode)->setTitleColorForState(pCCColor3B, CCControlStateNormal);
    } else if(pPropertyName->compare(PROPERTY_TITLECOLOR_HIGHLIGHTED) == 0) {
        ((CCControlButton *)pNode)->setTitleColorForState(pCCColor3B, CCControlStateHighlighted);
    } else if(pPropertyName->compare(PROPERTY_TITLECOLOR_DISABLED) == 0) {
        ((CCControlButton *)pNode)->setTitleColorForState(pCCColor3B, CCControlStateDisabled);
    } else {
        CCControlLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
    }
}

NS_CC_EXT_END;