#include "CCScrollViewLoader.h"

NS_CC_EXT_BEGIN

CCScrollView * CCScrollViewLoader::createCCNode(CCNode * pParent, CCBReader * pCCBReader) {
    return CCScrollView::node();
}

void CCScrollViewLoader::onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCSpriteFrame * pCCSpriteFrame, CCBReader * pCCBReader) {

}

void CCScrollViewLoader::onHandlePropTypeFlip(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, bool * pFlip, CCBReader * pCCBReader) {

}

void CCScrollViewLoader::onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader) {

}

void CCScrollViewLoader::onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, unsigned char pByte, CCBReader * pCCBReader) {

}

void CCScrollViewLoader::onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader) {

}

void CCScrollViewLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, float pFloat, CCBReader * pCCBReader)
{

}

NS_CC_EXT_END
