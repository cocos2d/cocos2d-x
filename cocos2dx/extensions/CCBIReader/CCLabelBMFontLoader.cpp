#import "CCLabelBMFontLoader.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"
#define PROPERTY_FNTFILE "fntFile"
#define PROPERTY_STRING "string"

CCLabelBMFont * CCLabelBMFontLoader::createCCNode(CCNode * pParent, CCBReader * pCCBReader) {
    return CCLabelBMFont::node();
}

void CCLabelBMFontLoader::onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, std::string pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_COLOR) == 0) {
        ((CCLabelBMFont *)pNode)->setColor(pCCColor3B);
    } else {
        CCNodeLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
    }
}

void CCLabelBMFontLoader::onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, std::string pPropertyName, unsigned char pByte, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_OPACITY) == 0) {
        ((CCLabelBMFont *)pNode)->setOpacity(pByte);
    } else {
        CCNodeLoader::onHandlePropTypeByte(pNode, pParent, pPropertyName, pByte, pCCBReader);
    }
}

void CCLabelBMFontLoader::onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, std::string pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_BLENDFUNC) == 0) {
        ((CCLabelBMFont *)pNode)->setBlendFunc(pCCBlendFunc);
    } else {
        CCNodeLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
    }
}

void CCLabelBMFontLoader::onHandlePropTypeFntFile(CCNode * pNode, CCNode * pParent, std::string pPropertyName, std::string pFntFile, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_FNTFILE) == 0) {
        ((CCLabelBMFont *)pNode)->setFntFile(pFntFile.c_str());
    } else {
        CCNodeLoader::onHandlePropTypeFntFile(pNode, pParent, pPropertyName, pFntFile, pCCBReader);
    }
}

void CCLabelBMFontLoader::onHandlePropTypeText(CCNode * pNode, CCNode * pParent, std::string pPropertyName, std::string pText, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_STRING) == 0) {
        ((CCLabelBMFont *)pNode)->setString(pText.c_str());
    } else {
        CCNodeLoader::onHandlePropTypeText(pNode, pParent, pPropertyName, pText, pCCBReader);
    }
}