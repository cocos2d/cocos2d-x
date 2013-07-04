#ifndef _CCB_CCPARTICLESYSTEMQUADLOADER_H_
#define _CCB_CCPARTICLESYSTEMQUADLOADER_H_

#include "CCNodeLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class ParticleSystemQuadLoader : public NodeLoader {
    public:
        virtual ~ParticleSystemQuadLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ParticleSystemQuadLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ParticleSystemQuad);

        virtual void onHandlePropTypeIntegerLabeled(Node * pNode, Node * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader);
        virtual void onHandlePropTypePoint(Node * pNode, Node * pParent, const char * pPropertyName, Point pPoint, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFloat(Node * pNode, Node * pParent, const char * pPropertyName, float pFloat, CCBReader * pCCBReader);
        virtual void onHandlePropTypeInteger(Node * pNode, Node * pParent, const char * pPropertyName, int pInteger, CCBReader * pCCBReader);
        virtual void onHandlePropTypeFloatVar(Node * pNode, Node * pParent, const char * pPropertyName, float * pFloatVar, CCBReader * pCCBReader);
        virtual void onHandlePropTypeColor4FVar(Node * pNode, Node * pParent, const char * pPropertyName, ccColor4F * pColor4FVar, CCBReader * pCCBReader);
        virtual void onHandlePropTypeBlendFunc(Node * pNode, Node * pParent, const char * pPropertyName, ccBlendFunc pBlendFunc, CCBReader * pCCBReader);
        virtual void onHandlePropTypeTexture(Node * pNode, Node * pParent, const char * pPropertyName, Texture2D * pTexture2D, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
