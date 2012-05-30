#import "CCLabelBMFontLoader.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"

CCLabelBMFont * CCLabelBMFontLoader::createCCNode(CCNode * pParent, CCBReader * pCCBReader) {
    if(pRet && pRet->initWithString(str, fntFile)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return new CCLabelBMFont(); // TODO Is this problematic?
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