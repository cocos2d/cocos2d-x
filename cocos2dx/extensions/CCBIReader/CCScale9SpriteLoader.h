#ifndef _CCSCALE9SPRITE_LOADER_H_
#define _CCSCALE9SPRITE_LOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCScale9SpriteLoader : public CCNodeLoader {
    protected:
        virtual CCScale9Sprite * createCCNode(CCNode *, CCBReader *);

        virtual void onHandlePropTypeColor3(CCNode *, CCNode *, std::string, ccColor3B, CCBReader *);
        virtual void onHandlePropTypeByte(CCNode *, CCNode *, std::string, unsigned char, CCBReader *);
        virtual void onHandlePropTypeBlendFunc(CCNode *, CCNode *, std::string, ccBlendFunc, CCBReader *);
        virtual void onHandlePropTypeSpriteFrame(CCNode *, CCNode *, std::string, CCSpriteFrame *, CCBReader *);
        virtual void onHandlePropTypeSize(CCNode *, CCNode *, std::string, CCSize, CCBReader *);
        virtual void onHandlePropTypeFloat(CCNode *, CCNode *, std::string, float, CCBReader *);
};

NS_CC_EXT_END

#endif
