#include "CCParticleSystemQuadLoader.h"

using namespace cocos2d;

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

namespace cocosbuilder {

void ParticleSystemQuadLoader::onHandlePropTypeIntegerLabeled(Node * pNode, Node * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_EMITERMODE) == 0) {
        ((ParticleSystemQuad *)pNode)->setEmitterMode((ParticleSystem::Mode)pIntegerLabeled);
    } else {
        NodeLoader::onHandlePropTypeIntegerLabeled(pNode, pParent, pPropertyName, pIntegerLabeled, ccbReader);
    }
}

void ParticleSystemQuadLoader::onHandlePropTypePoint(Node * pNode, Node * pParent, const char * pPropertyName, Vector2 pPoint, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_POSVAR) == 0) {
        ((ParticleSystemQuad *)pNode)->setPosVar(pPoint);
    } else if(strcmp(pPropertyName, PROPERTY_GRAVITY) == 0) {
        ((ParticleSystemQuad *)pNode)->setGravity(pPoint);
    } else {
        NodeLoader::onHandlePropTypePoint(pNode, pParent, pPropertyName, pPoint, ccbReader);
    }
}

void ParticleSystemQuadLoader::onHandlePropTypeFloat(Node * pNode, Node * pParent, const char * pPropertyName, float pFloat, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_EMISSIONRATE) == 0) {
        ((ParticleSystemQuad *)pNode)->setEmissionRate(pFloat);
    } else if(strcmp(pPropertyName, PROPERTY_DURATION) == 0) {
        ((ParticleSystemQuad *)pNode)->setDuration(pFloat);
    } else {
        NodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, ccbReader);
    }
}

void ParticleSystemQuadLoader::onHandlePropTypeInteger(Node * pNode, Node * pParent, const char * pPropertyName, int pInteger, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_TOTALPARTICLES) == 0) {
        ((ParticleSystemQuad *)pNode)->setTotalParticles(pInteger);
    } else {
        NodeLoader::onHandlePropTypeInteger(pNode, pParent, pPropertyName, pInteger, ccbReader);
    }
}

void ParticleSystemQuadLoader::onHandlePropTypeFloatVar(Node * pNode, Node * pParent, const char * pPropertyName, float * pFloatVar, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_LIFE) == 0) {
        ((ParticleSystemQuad *)pNode)->setLife(pFloatVar[0]);
        ((ParticleSystemQuad *)pNode)->setLifeVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_STARTSIZE) == 0) {
        ((ParticleSystemQuad *)pNode)->setStartSize(pFloatVar[0]);
        ((ParticleSystemQuad *)pNode)->setStartSizeVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_ENDSIZE) == 0) {
        ((ParticleSystemQuad *)pNode)->setEndSize(pFloatVar[0]);
        ((ParticleSystemQuad *)pNode)->setEndSizeVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_STARTSPIN) == 0) {
        ((ParticleSystemQuad *)pNode)->setStartSpin(pFloatVar[0]);
        ((ParticleSystemQuad *)pNode)->setStartSpinVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_ENDSPIN) == 0) {
        ((ParticleSystemQuad *)pNode)->setEndSpin(pFloatVar[0]);
        ((ParticleSystemQuad *)pNode)->setEndSpinVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_ANGLE) == 0) {
        ((ParticleSystemQuad *)pNode)->setAngle(pFloatVar[0]);
        ((ParticleSystemQuad *)pNode)->setAngleVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_SPEED) == 0) {
        ((ParticleSystemQuad *)pNode)->setSpeed(pFloatVar[0]);
        ((ParticleSystemQuad *)pNode)->setSpeedVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_TANGENTIALACCEL) == 0) {
        ((ParticleSystemQuad *)pNode)->setTangentialAccel(pFloatVar[0]);
        ((ParticleSystemQuad *)pNode)->setTangentialAccelVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_RADIALACCEL) == 0) {
        ((ParticleSystemQuad *)pNode)->setRadialAccel(pFloatVar[0]);
        ((ParticleSystemQuad *)pNode)->setRadialAccelVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_STARTRADIUS) == 0) {
        ((ParticleSystemQuad *)pNode)->setStartRadius(pFloatVar[0]);
        ((ParticleSystemQuad *)pNode)->setStartRadiusVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_ENDRADIUS) == 0) {
        ((ParticleSystemQuad *)pNode)->setEndRadius(pFloatVar[0]);
        ((ParticleSystemQuad *)pNode)->setEndRadiusVar(pFloatVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_ROTATEPERSECOND) == 0) {
        ((ParticleSystemQuad *)pNode)->setRotatePerSecond(pFloatVar[0]);
        ((ParticleSystemQuad *)pNode)->setRotatePerSecondVar(pFloatVar[1]);
    } else {
        NodeLoader::onHandlePropTypeFloatVar(pNode, pParent, pPropertyName, pFloatVar, ccbReader);
    }
}

void ParticleSystemQuadLoader::onHandlePropTypeColor4FVar(Node * pNode, Node * pParent, const char * pPropertyName, Color4F * pColor4FVar, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_STARTCOLOR) == 0) {
        ((ParticleSystemQuad *)pNode)->setStartColor(pColor4FVar[0]);
        ((ParticleSystemQuad *)pNode)->setStartColorVar(pColor4FVar[1]);
    } else if(strcmp(pPropertyName, PROPERTY_ENDCOLOR) == 0) {
        ((ParticleSystemQuad *)pNode)->setEndColor(pColor4FVar[0]);
        ((ParticleSystemQuad *)pNode)->setEndColorVar(pColor4FVar[1]);
    } else {
        NodeLoader::onHandlePropTypeColor4FVar(pNode, pParent, pPropertyName, pColor4FVar, ccbReader);
    }
}

void ParticleSystemQuadLoader::onHandlePropTypeBlendFunc(Node * pNode, Node * pParent, const char * pPropertyName, BlendFunc pBlendFunc, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
        ((ParticleSystemQuad *)pNode)->setBlendFunc(pBlendFunc);
    } else {
        NodeLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pBlendFunc, ccbReader);
    }
}

void ParticleSystemQuadLoader::onHandlePropTypeTexture(Node * pNode, Node * pParent, const char * pPropertyName, Texture2D * pTexture2D, CCBReader * ccbReader) {
    if(strcmp(pPropertyName, PROPERTY_TEXTURE) == 0) {
        static_cast<ParticleSystemQuad*>(pNode)->setTexture(pTexture2D);
        if(pTexture2D)
        {
            static_cast<ParticleSystemQuad*>(pNode)->setBlendAdditive(true);
        }
    } else {
        NodeLoader::onHandlePropTypeTexture(pNode, pParent, pPropertyName, pTexture2D, ccbReader);
    }
}

}