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

void ControlButtonLoader::onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_ZOOMONTOUCHDOWN) == 0) {
        ((ControlButton *)pNode)->setZoomOnTouchDown(pCheck);
    } else {
        ControlLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}

void ControlButtonLoader::onHandlePropTypeString(Node * pNode, Node * pParent, const char * pPropertyName, const char * pString, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_TITLE_NORMAL) == 0) {
        ((ControlButton *)pNode)->setTitleForState(String::create(pString), ControlStateNormal);
    } else if(strcmp(pPropertyName, PROPERTY_TITLE_HIGHLIGHTED) == 0) {
        ((ControlButton *)pNode)->setTitleForState(String::create(pString), ControlStateHighlighted);
    } else if(strcmp(pPropertyName, PROPERTY_TITLE_DISABLED) == 0) {
        ((ControlButton *)pNode)->setTitleForState(String::create(pString), ControlStateDisabled);
    } else {
        ControlLoader::onHandlePropTypeString(pNode, pParent, pPropertyName, pString, pCCBReader);
    }
}

void ControlButtonLoader::onHandlePropTypeFontTTF(Node * pNode, Node * pParent, const char * pPropertyName, const char * pFontTTF, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_TITLETTF_NORMAL) == 0) {
        ((ControlButton *)pNode)->setTitleTTFForState(pFontTTF, ControlStateNormal);
    } else if(strcmp(pPropertyName, PROPERTY_TITLETTF_HIGHLIGHTED) == 0) {
        ((ControlButton *)pNode)->setTitleTTFForState(pFontTTF, ControlStateHighlighted);
    } else if(strcmp(pPropertyName, PROPERTY_TITLETTF_DISABLED) == 0) {
        ((ControlButton *)pNode)->setTitleTTFForState(pFontTTF, ControlStateDisabled);
    } else {
        ControlLoader::onHandlePropTypeFontTTF(pNode, pParent, pPropertyName, pFontTTF, pCCBReader);
    }
}

void ControlButtonLoader::onHandlePropTypeFloatScale(Node * pNode, Node * pParent, const char * pPropertyName, float pFloatScale, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_TITLETTFSIZE_NORMAL) == 0) {
        ((ControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, ControlStateNormal);
    } else if(strcmp(pPropertyName, PROPERTY_TITLETTFSIZE_HIGHLIGHTED) == 0) {
        ((ControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, ControlStateHighlighted);
    } else if(strcmp(pPropertyName, PROPERTY_TITLETTFSIZE_DISABLED) == 0) {
        ((ControlButton *)pNode)->setTitleTTFSizeForState(pFloatScale, ControlStateDisabled);
    } else {
        ControlLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pFloatScale, pCCBReader);
    }
}

void ControlButtonLoader::onHandlePropTypePoint(Node * pNode, Node * pParent, const char * pPropertyName, Point pPoint, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_LABELANCHORPOINT) == 0) {
        ((ControlButton *)pNode)->setLabelAnchorPoint(pPoint);
    } else {
        ControlLoader::onHandlePropTypePoint(pNode, pParent, pPropertyName, pPoint, pCCBReader);
    }
}

void ControlButtonLoader::onHandlePropTypeSize(Node * pNode, Node * pParent, const char * pPropertyName, Size pSize, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_PREFEREDSIZE) == 0) {
        ((ControlButton *)pNode)->setPreferredSize(pSize);
    } else {
        ControlLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, pSize, pCCBReader);
    }
}

void ControlButtonLoader::onHandlePropTypeSpriteFrame(Node * pNode, Node * pParent, const char * pPropertyName, SpriteFrame * pSpriteFrame, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_NORMAL) == 0) {
        if(pSpriteFrame != NULL) {
            ((ControlButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, ControlStateNormal);
        }
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_HIGHLIGHTED) == 0) {
        if(pSpriteFrame != NULL) {
            ((ControlButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, ControlStateHighlighted);
        }
    } else if(strcmp(pPropertyName, PROPERTY_BACKGROUNDSPRITEFRAME_DISABLED) == 0) {
        if(pSpriteFrame != NULL) {
            ((ControlButton *)pNode)->setBackgroundSpriteFrameForState(pSpriteFrame, ControlStateDisabled);
        }
    } else {
        ControlLoader::onHandlePropTypeSpriteFrame(pNode, pParent, pPropertyName, pSpriteFrame, pCCBReader);
    }
}

void ControlButtonLoader::onHandlePropTypeColor3(Node * pNode, Node * pParent, const char * pPropertyName, ccColor3B pColor3B, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_NORMAL) == 0) {
        ((ControlButton *)pNode)->setTitleColorForState(pColor3B, ControlStateNormal);
    } else if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_HIGHLIGHTED) == 0) {
        ((ControlButton *)pNode)->setTitleColorForState(pColor3B, ControlStateHighlighted);
    } else if(strcmp(pPropertyName, PROPERTY_TITLECOLOR_DISABLED) == 0) {
        ((ControlButton *)pNode)->setTitleColorForState(pColor3B, ControlStateDisabled);
    } else {
        ControlLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pColor3B, pCCBReader);
    }
}

NS_CC_EXT_END;