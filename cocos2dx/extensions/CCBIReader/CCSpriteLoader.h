#ifndef _CCSPRITE_LOADER_H_
#define _CCSPRITE_LOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCSpriteLoader : public CCNodeLoader {
    protected:
        virtual CCSprite * createCCNode(CCNode *, CCBReader *);

        virtual void onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B, CCBReader *);
        virtual void onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char, CCBReader *);
        virtual void onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc, CCBReader *);
        virtual void onHandlePropTypeSpriteFrame(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCSpriteFrame *, CCBReader *);
        virtual void onHandlePropTypeFlip(CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool *, CCBReader *);
};

NS_CC_EXT_END

#endif
