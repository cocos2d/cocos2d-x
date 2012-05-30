#ifndef _CCLAYERGRADIENT_LOADER_H_
#define _CCLAYERGRADIENT_LOADER_H_

#include "CCLayerLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCLayerGradientLoader : public CCLayerLoader {
    protected:
        virtual CCLayerGradient * createCCNode(CCNode *, CCBReader *);

        virtual void onHandlePropTypeColor3(CCNode *, CCNode *, std::string, ccColor3B, CCBReader *);
        virtual void onHandlePropTypeByte(CCNode *, CCNode *, std::string, unsigned char, CCBReader *);
        virtual void onHandlePropTypePoint(CCNode *, CCNode *, std::string, CCPoint, CCBReader *);
        virtual void onHandlePropTypeBlendFunc(CCNode *, CCNode *, std::string, ccBlendFunc, CCBReader *);
};

NS_CC_EXT_END

#endif
