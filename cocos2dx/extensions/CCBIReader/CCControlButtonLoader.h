#ifndef _CCCONTROLBUTTON_LOADER_H_
#define _CCCONTROLBUTTON_LOADER_H_

#include "CCControlLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCControlButtonLoader : public CCControlLoader {
    protected:
        virtual CCControl * createCCNode(CCNode *, CCBReader *);

        virtual void onHandlePropTypeCheck(CCNode *, CCNode *, std::string, bool, CCBReader *);
        virtual void onHandlePropTypeString(CCNode *, CCNode *, std::string, std::string, CCBReader *);
        virtual void onHandlePropTypeFontTTF(CCNode *, CCNode *, std::string, std::string, CCBReader *);
        virtual void onHandlePropTypeFloatScale(CCNode *, CCNode *, std::string, float, CCBReader *);
        virtual void onHandlePropTypePoint(CCNode *, CCNode *, std::string, CCPoint, CCBReader *);
        virtual void onHandlePropTypeSize(CCNode *, CCNode *, std::string, CCSize, CCBReader *);
        virtual void onHandlePropTypeSpriteFrame(CCNode *, CCNode *, std::string, CCSpriteFrame *, CCBReader *);
        virtual void onHandlePropTypeColor3(CCNode *, CCNode *, std::string, ccColor3B, CCBReader *);
};

NS_CC_EXT_END

#endif
