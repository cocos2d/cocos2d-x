#ifndef _CCPARTICLESYSTEMQUAD_LOADER_H_
#define _CCPARTICLESYSTEMQUAD_LOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCParticleSystemQuadLoader : public CCNodeLoader {
    protected:
        virtual CCParticleSystemQuad * createCCNode(CCNode *, CCBReader *);

        virtual void onHandlePropTypeIntegerLabeled(CCNode *, CCNode *, std::string, int, CCBReader *);
        virtual void onHandlePropTypePoint(CCNode *, CCNode *, std::string, CCPoint, CCBReader *);
        virtual void onHandlePropTypeFloat(CCNode *, CCNode *, std::string, float, CCBReader *);
        virtual void onHandlePropTypeInteger(CCNode *, CCNode *, std::string, int, CCBReader *);
        virtual void onHandlePropTypeFloatVar(CCNode *, CCNode *, std::string, float *, CCBReader *);
        virtual void onHandlePropTypeColor4FVar(CCNode *, CCNode *, std::string, ccColor4F *, CCBReader *);
        virtual void onHandlePropTypeBlendFunc(CCNode *, CCNode *, std::string, ccBlendFunc, CCBReader *);
        virtual void onHandlePropTypeTexture(CCNode *, CCNode *, std::string, CCTexture2D *, CCBReader *);
};

NS_CC_EXT_END

#endif
