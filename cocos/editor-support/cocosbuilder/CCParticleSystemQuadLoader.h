#ifndef _CCB_CCPARTICLESYSTEMQUADLOADER_H_
#define _CCB_CCPARTICLESYSTEMQUADLOADER_H_

#include "base/CCRef.h"
#include "2d/CCParticleSystemQuad.h"

#include "CCNodeLoader.h"

namespace cocosbuilder {

/* Forward declaration. */
class CCBReader;

class ParticleSystemQuadLoader : public NodeLoader {
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ParticleSystemQuadLoader() {};
    /**
     * @js NA
     * @lua NA
     */
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(cocosbuilder::ParticleSystemQuadLoader, loader);

protected:
    /**
     * @js NA
     * @lua NA
     */
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(cocos2d::ParticleSystemQuad);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeIntegerLabeled(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypePoint(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Vector2 pPoint, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeFloat(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, float pFloat, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeInteger(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, int pInteger, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeFloatVar(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, float * pFloatVar, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeColor4FVar(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Color4F * pColor4FVar, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeBlendFunc(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::BlendFunc pBlendFunc, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeTexture(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::Texture2D * pTexture2D, CCBReader * ccbReader);
};

}

#endif
