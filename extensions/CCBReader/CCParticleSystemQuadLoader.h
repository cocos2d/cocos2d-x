#ifndef _CCB_CCPARTICLESYSTEMQUADLOADER_H_
#define _CCB_CCPARTICLESYSTEMQUADLOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCParticleSystemQuadLoader : public CCNodeLoader {
    public:
        virtual ~CCParticleSystemQuadLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCParticleSystemQuadLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCParticleSystemQuad);

        virtual void onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader);
        virtual void onHandlePropTypePoint(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCPoint pPoint, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char * pPropertyName, float pFloat, CCBReader * pCCBReader);
        virtual void onHandlePropTypeInteger(CCNode * pNode, CCNode * pParent, const char * pPropertyName, int pInteger, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFloatVar(CCNode * pNode, CCNode * pParent, const char * pPropertyName, float * pFloatVar, CCBReader * pCCBReader);
        virtual void onHandlePropTypeColor4FVar(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor4F * pCCColor4FVar, CCBReader * pCCBReader);
        virtual void onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader);
        virtual void onHandlePropTypeTexture(CCNode * pNode, CCNode * pParent, const char * pPropertyName, CCTexture2D * pCCTexture2D, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
