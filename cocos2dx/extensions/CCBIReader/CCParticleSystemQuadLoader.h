#ifndef _CCB_CCPARTICLESYSTEMQUADLOADER_H_
#define _CCB_CCPARTICLESYSTEMQUADLOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCParticleSystemQuadLoader : public CCNodeLoader {
    public:
        STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCParticleSystemQuadLoader, loader);

    protected:
        virtual CCParticleSystemQuad * createCCNode(CCNode *, CCBReader *);

        virtual void onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, const char * pPropertyName, int, CCBReader *);
        virtual void onHandlePropTypePoint(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCPoint, CCBReader *);
        virtual void onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char * pPropertyName, float, CCBReader *);
        virtual void onHandlePropTypeInteger(CCNode * pNode, CCNode * pParent, const char * pPropertyName, int, CCBReader *);
        virtual void onHandlePropTypeFloatVar(CCNode * pNode, CCNode * pParent, const char * pPropertyName, float *, CCBReader *);
        virtual void onHandlePropTypeColor4FVar(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor4F *, CCBReader *);
        virtual void onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc, CCBReader *);
        virtual void onHandlePropTypeTexture(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCTexture2D *, CCBReader *);
};

NS_CC_EXT_END

#endif
