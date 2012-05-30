#ifndef _CCLABELBMFONT_LOADER_H_
#define _CCLABELBMFONT_LOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCLabelBMFontLoader : public CCNodeLoader {
    protected:
        virtual CCLabelBMFont * createCCNode(CCNode *, CCBReader *);

        virtual void onHandlePropTypeColor3(CCNode *, CCNode *, std::string, ccColor3B, CCBReader *);
        virtual void onHandlePropTypeByte(CCNode *, CCNode *, std::string, unsigned char, CCBReader *);
        virtual void onHandlePropTypeBlendFunc(CCNode *, CCNode *, std::string, ccBlendFunc, CCBReader *);
        virtual void onHandlePropTypeFntFile(CCNode *, CCNode *, std::string, std::string, CCBReader *);
        virtual void onHandlePropTypeText(CCNode *, CCNode *, std::string, std::string, CCBReader *);
};

NS_CC_EXT_END

#endif
