#ifndef _CCSPRITE_LOADER_H_
#define _CCSPRITE_LOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCSpriteLoader : public CCNodeLoader {
    protected:
        virtual CCSprite * createCCNode(CCNode *, CCBReader *);

        virtual void onHandlePropTypeColor3(CCNode *, CCNode *, std::string, ccColor3B, CCBReader *);
        virtual void onHandlePropTypeByte(CCNode *, CCNode *, std::string, unsigned char, CCBReader *);
        virtual void onHandlePropTypeBlendFunc(CCNode *, CCNode *, std::string, ccBlendFunc, CCBReader *);
        virtual void onHandlePropTypeSpriteFrame(CCNode *, CCNode *, std::string, CCSpriteFrame *, CCBReader *);
        virtual void onHandlePropTypeFlip(CCNode *, CCNode *, std::string, bool *, CCBReader *);
};

NS_CC_EXT_END

#endif
