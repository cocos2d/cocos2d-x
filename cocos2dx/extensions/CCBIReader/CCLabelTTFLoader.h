#ifndef _CCLABELTTF_LOADER_H_
#define _CCLABELTTF_LOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCLabelTTFLoader : public CCNodeLoader {
    protected:
        virtual cocos2d::CCLabelTTF * createCCNode(cocos2d::CCNode *, CCBReader *);

        virtual void onHandlePropTypeColor3(cocos2d::CCNode *, cocos2d::CCNode *, std::string, cocos2d::ccColor3B, CCBReader *);
        virtual void onHandlePropTypeByte(CCNode *, CCNode *, std::string, unsigned char, CCBReader *);
        virtual void onHandlePropTypeBlendFunc(CCNode *, CCNode *, std::string, ccBlendFunc, CCBReader *);
        virtual void onHandlePropTypeFontTTF(CCNode *, CCNode *, std::string, std::string, CCBReader *);
        virtual void onHandlePropTypeText(CCNode *, CCNode *, std::string, std::string, CCBReader *);
        virtual void onHandlePropTypeFloatScale(CCNode *, CCNode *, std::string, float, CCBReader *);
        virtual void onHandlePropTypeIntegerLabeled(CCNode *, CCNode *, std::string, int, CCBReader *);
};

NS_CC_EXT_END

#endif
