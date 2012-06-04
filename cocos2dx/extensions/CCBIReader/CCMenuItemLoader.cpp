#import "CCMenuItemLoader.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define PROPERTY_BLOCK "block"
#define PROPERTY_ISENABLED "isEnabled"

void CCMenuItemLoader::onHandlePropTypeBlock(CCNode * pNode, CCNode * pParent, std::string pPropertyName, BlockData * pBlockData, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_BLOCK) == 0) {
        ((CCMenuItem *)pNode)->setTarget(pBlockData->mTarget, pBlockData->mSELMenuHandler);
    } else {
        CCNodeLoader::onHandlePropTypeBlock(pNode, pParent, pPropertyName, pBlockData, pCCBReader);
    }
}

void CCMenuItemLoader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, std::string pPropertyName, bool pCheck, CCBReader * pCCBReader) {
    if(pPropertyName.compare(PROPERTY_ISENABLED) == 0) {
        ((CCMenuItem *)pNode)->setIsEnabled(pCheck);
    } else {
        CCNodeLoader::onHandlePropTypeCheck(pNode, pParent, pPropertyName, pCheck, pCCBReader);
    }
}