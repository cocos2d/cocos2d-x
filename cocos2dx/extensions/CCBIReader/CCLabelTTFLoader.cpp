#import "CCLabelTTFLoader.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"
#define PROPERTY_FONTNAME "fontName"
#define PROPERTY_FONTSIZE "fontSize"
#define PROPERTY_HORIZONTALALIGNMENT "horizontalAlignment"
#define PROPERTY_VERTICALALIGNMENT "verticalAlignment"
#define PROPERTY_STRING "string"
#define PROPERTY_DIMENSIONS "dimensions"

CCLabelTTF * CCLabelTTFLoader::createCCNode(CCNode * pParent, CCBReader * pCCBReader) {
    return CCLabelTTF::node();
}

void CCLabelTTFLoader::onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, std::string pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_COLOR) == 0) {
        ((CCLabelTTF *)pNode)->setColor(pCCColor3B);
    } else {
        CCNodeLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
    }
}

void CCLabelTTFLoader::onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, std::string pPropertyName, unsigned char pByte, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_OPACITY) == 0) {
        ((CCLabelTTF *)pNode)->setOpacity(pByte);
    } else {
        CCNodeLoader::onHandlePropTypeByte(pNode, pParent, pPropertyName, pByte, pCCBReader);
    }
}

void CCLabelTTFLoader::onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, std::string pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_BLENDFUNC) == 0) {
        ((CCLabelTTF *)pNode)->setBlendFunc(pCCBlendFunc);
    } else {
        CCNodeLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
    }
}

void CCLabelTTFLoader::onHandlePropTypeFontTTF(CCNode * pNode, CCNode * pParent, std::string pPropertyName, std::string pFontTTF, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_FONTNAME) == 0) {
        ((CCLabelTTF *)pNode)->setFontName(pFontTTF.c_str());
    } else {
        CCNodeLoader::onHandlePropTypeFontTTF(pNode, pParent, pPropertyName, pFontTTF, pCCBReader);
    }
}

void CCLabelTTFLoader::onHandlePropTypeText(CCNode * pNode, CCNode * pParent, std::string pPropertyName, std::string pText, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_STRING) == 0) {
        ((CCLabelTTF *)pNode)->setString(pText.c_str());
    } else {
        CCNodeLoader::onHandlePropTypeText(pNode, pParent, pPropertyName, pText, pCCBReader);
    }
}

void CCLabelTTFLoader::onHandlePropTypeFloatScale(CCNode * pNode, CCNode * pParent, std::string pPropertyName, float pFloatScale, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_FONTSIZE) == 0) {
        ((CCLabelTTF *)pNode)->setFontSize(pFloatScale);
    } else {
        CCNodeLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pFloatScale, pCCBReader);
    }
}

void CCLabelTTFLoader::onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, std::string pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_HORIZONTALALIGNMENT) == 0) {
        ((CCLabelTTF *)pNode)->setHorizontalAlignment(CCTextAlignment(pIntegerLabeled));
    } else if(pPropertyName.compare(PROPERTY_VERTICALALIGNMENT) == 0) {
        // TODO Add support when CCLabelTTF supports it. ( See: 63d9724ac4d81a05c6ec7feea0c01bcd27c8fc6b )
        // ((CCLabelTTF *)pNode)->setVerticalAlignment(pIntegerLabeled);
    } else {
        CCNodeLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pIntegerLabeled, pCCBReader);
    }
}

void CCLabelTTFLoader::onHandlePropTypeSize(CCNode * pNode, CCNode * pParent, std::string pPropertyName, CCSize pSize, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_DIMENSIONS) == 0) {
        ((CCLabelTTF *)pNode)->setDimensions(pSize);
    } else {
        CCNodeLoader::onHandlePropTypeSize(pNode, pParent, pPropertyName, pSize, pCCBReader);
    }
}