#include "CCParticleSystemQuadLoader.h"



#define PROPERTY_EMITERMODE "emitterMode"
#define PROPERTY_POSVAR "posVar"
#define PROPERTY_EMISSIONRATE "emissionRate"
#define PROPERTY_DURATION "duration"
#define PROPERTY_TOTALPARTICLES "totalParticles"
#define PROPERTY_LIFE "life"
#define PROPERTY_STARTSIZE "startSize"
#define PROPERTY_ENDSIZE "endSize"
#define PROPERTY_STARTSPIN "startSpin"
#define PROPERTY_ENDSPIN "endSpin"
#define PROPERTY_ANGLE "angle"
#define PROPERTY_STARTCOLOR "startColor"
#define PROPERTY_ENDCOLOR "endColor"
#define PROPERTY_BLENDFUNC "blendFunc"
#define PROPERTY_GRAVITY "gravity"
#define PROPERTY_SPEED "speed"
#define PROPERTY_TANGENTIALACCEL "tangentialAccel"
#define PROPERTY_RADIALACCEL "radialAccel"
#define PROPERTY_TEXTURE "texture"
#define PROPERTY_STARTRADIUS "startRadius"
#define PROPERTY_ENDRADIUS "endRadius"
#define PROPERTY_ROTATEPERSECOND "rotatePerSecond"

NS_CC_EXT_BEGIN

void CCParticleSystemQuadLoader::onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_EMITERMODE) == 0) {
        ((CCParticleSystemQuad *)pNode)->setEmitterMode(pIntegerLabeled);
    } else {
        CCNodeLoader::onHandlePropTypeIntegerLabeled(pNode, pParent, pPropertyName, pIntegerLabeled, pCCBReader);
    }
}

void CCParticleSystemQuadLoader::onHandlePropTypePoint(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCPoint pPoint, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_POSVAR) == 0) {
        ((CCParticleSystemQuad *)pNode)->setPosVar(pPoint);
    } else if(pPropertyName->compare(PROPERTY_GRAVITY) == 0) {
        ((CCParticleSystemQuad *)pNode)->setGravity(pPoint);
    } else {
        CCNodeLoader::onHandlePropTypePoint(pNode, pParent, pPropertyName, pPoint, pCCBReader);
    }
}

void CCParticleSystemQuadLoader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, float pFloat, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_EMISSIONRATE) == 0) {
        ((CCParticleSystemQuad *)pNode)->setEmissionRate(pFloat);
    } else if(pPropertyName->compare(PROPERTY_DURATION) == 0) {
        ((CCParticleSystemQuad *)pNode)->setDuration(pFloat);
    } else {
        CCNodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, pCCBReader);
    }
}

void CCParticleSystemQuadLoader::onHandlePropTypeInteger(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, int pInteger, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_TOTALPARTICLES) == 0) {
        ((CCParticleSystemQuad *)pNode)->setTotalParticles(pInteger);
    } else {
        CCNodeLoader::onHandlePropTypeInteger(pNode, pParent, pPropertyName, pInteger, pCCBReader);
    }
}

void CCParticleSystemQuadLoader::onHandlePropTypeFloatVar(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, float * pFloatVar, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_LIFE) == 0) {
        ((CCParticleSystemQuad *)pNode)->setLife(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setLifeVar(pFloatVar[1]);
    } else if(pPropertyName->compare(PROPERTY_STARTSIZE) == 0) {
        ((CCParticleSystemQuad *)pNode)->setStartSize(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setStartSizeVar(pFloatVar[1]);
    } else if(pPropertyName->compare(PROPERTY_ENDSIZE) == 0) {
        ((CCParticleSystemQuad *)pNode)->setEndSize(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setEndSizeVar(pFloatVar[1]);
    } else if(pPropertyName->compare(PROPERTY_STARTSPIN) == 0) {
        ((CCParticleSystemQuad *)pNode)->setStartSpin(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setStartSpinVar(pFloatVar[1]);
    } else if(pPropertyName->compare(PROPERTY_ENDSPIN) == 0) {
        ((CCParticleSystemQuad *)pNode)->setEndSpin(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setEndSpinVar(pFloatVar[1]);
    } else if(pPropertyName->compare(PROPERTY_ANGLE) == 0) {
        ((CCParticleSystemQuad *)pNode)->setAngle(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setAngleVar(pFloatVar[1]);
    } else if(pPropertyName->compare(PROPERTY_SPEED) == 0) {
        ((CCParticleSystemQuad *)pNode)->setSpeed(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setSpeedVar(pFloatVar[1]);
    } else if(pPropertyName->compare(PROPERTY_TANGENTIALACCEL) == 0) {
        ((CCParticleSystemQuad *)pNode)->setTangentialAccel(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setTangentialAccelVar(pFloatVar[1]);
    } else if(pPropertyName->compare(PROPERTY_RADIALACCEL) == 0) {
        ((CCParticleSystemQuad *)pNode)->setRadialAccel(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setRadialAccelVar(pFloatVar[1]);
    } else if(pPropertyName->compare(PROPERTY_STARTRADIUS) == 0) {
        ((CCParticleSystemQuad *)pNode)->setStartRadius(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setStartRadiusVar(pFloatVar[1]);
    } else if(pPropertyName->compare(PROPERTY_ENDRADIUS) == 0) {
        ((CCParticleSystemQuad *)pNode)->setEndRadius(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setEndRadiusVar(pFloatVar[1]);
    } else if(pPropertyName->compare(PROPERTY_ROTATEPERSECOND) == 0) {
        ((CCParticleSystemQuad *)pNode)->setRotatePerSecond(pFloatVar[0]);
        ((CCParticleSystemQuad *)pNode)->setRotatePerSecondVar(pFloatVar[1]);
    } else {
        CCNodeLoader::onHandlePropTypeFloatVar(pNode, pParent, pPropertyName, pFloatVar, pCCBReader);
    }
}

void CCParticleSystemQuadLoader::onHandlePropTypeColor4FVar(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, ccColor4F * pCCColor4FVar, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_STARTCOLOR) == 0) {
        ((CCParticleSystemQuad *)pNode)->setStartColor(pCCColor4FVar[0]);
        ((CCParticleSystemQuad *)pNode)->setStartColorVar(pCCColor4FVar[1]);
    } else if(pPropertyName->compare(PROPERTY_ENDCOLOR) == 0) {
        ((CCParticleSystemQuad *)pNode)->setEndColor(pCCColor4FVar[0]);
        ((CCParticleSystemQuad *)pNode)->setEndColorVar(pCCColor4FVar[1]);
    } else {
        CCNodeLoader::onHandlePropTypeColor4FVar(pNode, pParent, pPropertyName, pCCColor4FVar, pCCBReader);
    }
}

void CCParticleSystemQuadLoader::onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_BLENDFUNC) == 0) {
        ((CCParticleSystemQuad *)pNode)->setBlendFunc(pCCBlendFunc);
    } else {
        CCNodeLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
    }
}

void CCParticleSystemQuadLoader::onHandlePropTypeTexture(CCNode * pNode, CCNode * pParent, CCString * pPropertyName, CCTexture2D * pCCTexture2D, CCBReader * pCCBReader) {
    if(pPropertyName->compare(PROPERTY_TEXTURE) == 0) {
        ((CCParticleSystemQuad *)pNode)->setTexture(pCCTexture2D);
    } else {
        CCNodeLoader::onHandlePropTypeTexture(pNode, pParent, pPropertyName, pCCTexture2D, pCCBReader);
    }
}

NS_CC_EXT_END