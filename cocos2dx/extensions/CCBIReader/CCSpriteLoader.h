#ifndef _CCSPRITE_LOADER_H_
#define _CCSPRITE_LOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCSpriteLoader : public CCNodeLoader {
    protected:
        virtual cocos2d::CCSprite * createCCNode(cocos2d::CCNode *, CCBReader *);

        virtual void onHandlePropTypeColor3(cocos2d::CCNode *, cocos2d::CCNode *, std::string, cocos2d::ccColor3B, CCBReader *);
        virtual void onHandlePropTypeByte(CCNode *, CCNode *, std::string, unsigned char, CCBReader *);
        virtual void onHandlePropTypeBlendFunc(CCNode *, CCNode *, std::string, ccBlendFunc, CCBReader *);
        virtual void onHandlePropTypeSpriteFrame(CCNode *, CCNode *, std::string, CCSpriteFrame *, CCBReader *);
        virtual void onHandlePropTypeFlip(CCNode *, CCNode *, std::string, bool *, CCBReader *);
};

NS_CC_EXT_END

#endif
