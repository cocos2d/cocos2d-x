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

        virtual void onHandlePropTypeIntegerLabeled(Node * pNode, Node * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * ccbReader);
        virtual void onHandlePropTypePoint(Node * pNode, Node * pParent, const char * pPropertyName, Point pPoint, CCBReader * ccbReader);
        virtual void onHandlePropTypeFloat(Node * pNode, Node * pParent, const char * pPropertyName, float pFloat, CCBReader * ccbReader);
        virtual void onHandlePropTypeInteger(Node * pNode, Node * pParent, const char * pPropertyName, int pInteger, CCBReader * ccbReader);
        virtual void onHandlePropTypeFloatVar(Node * pNode, Node * pParent, const char * pPropertyName, float * pFloatVar, CCBReader * ccbReader);
        virtual void onHandlePropTypeColor4FVar(Node * pNode, Node * pParent, const char * pPropertyName, Color4F * pColor4FVar, CCBReader * ccbReader);
        virtual void onHandlePropTypeBlendFunc(Node * pNode, Node * pParent, const char * pPropertyName, BlendFunc pBlendFunc, CCBReader * ccbReader);
        virtual void onHandlePropTypeTexture(Node * pNode, Node * pParent, const char * pPropertyName, Texture2D * pTexture2D, CCBReader * ccbReader);
};

NS_CC_EXT_END

#endif
