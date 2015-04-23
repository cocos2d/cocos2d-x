/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


#ifndef __CC_PU_PARTICLE_3D_TEXTURE_ANIMATOR_H__
#define __CC_PU_PARTICLE_3D_TEXTURE_ANIMATOR_H__

#include "extensions/Particle3D/PU/CCPUAffector.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

class  CC_DLL PUTextureAnimator : public PUAffector
{
public:
    enum TextureAnimationType
    {
        TAT_LOOP,
        TAT_UP_DOWN,
        TAT_RANDOM
    };

    // Constants
    static const float DEFAULT_TIME_STEP;
    static const unsigned short DEFAULT_TEXCOORDS_START;
    static const unsigned short DEFAULT_TEXCOORDS_END;
    static const TextureAnimationType DEFAULT_ANIMATION_TYPE;
    static const bool DEFAULT_START_RANDOM;

    static PUTextureAnimator* create();

    virtual void preUpdateAffector(float deltaTime) override;
    virtual void initParticleForEmission(PUParticle3D* particle) override;
    virtual void updatePUAffector(PUParticle3D *particle, float deltaTime) override;

    /** Returns the AnimationTimeStep. The AnimationTimeStep defines the time between each animation frame. */
    float getAnimationTimeStep(void) const;

    /** Set the  AnimationTimeStep */
    void setAnimationTimeStep(float animationTimeStep);

    /** Returns the type of texture animation. */
    TextureAnimationType getTextureAnimationType(void) const;

    /** Set the type of texture animation. */
    void setTextureAnimationType(TextureAnimationType textureAnimationType);

    /** Todo */
    unsigned short getTextureCoordsStart(void) const;

    /** Todo */
    void setTextureCoordsStart(unsigned short textureCoordsStart);

    /** Todo */
    unsigned short getTextureCoordsEnd(void) const;

    /** Todo */
    void setTextureCoordsEnd(unsigned short textureCoordsEnd);

    /** Todo */
    bool isStartRandom(void) const;

    /** Todo */
    void setStartRandom(bool startRandom);

    virtual void copyAttributesTo (PUAffector* affector) override;

CC_CONSTRUCTOR_ACCESS:	
    PUTextureAnimator(void);
    virtual ~PUTextureAnimator(void);

protected:

    /** Todo.
    */
    void determineNextTextureCoords(PUParticle3D* visualParticle);

protected:
    float _animationTimeStep;
    float _animationTimeStepCount;
    bool _startRandom;
    bool _animationTimeStepSet;
    bool _nextIndex;
    TextureAnimationType _textureAnimationType;
    unsigned short _textureCoordsStart;
    unsigned short _textureCoordsEnd;

};
NS_CC_END

#endif