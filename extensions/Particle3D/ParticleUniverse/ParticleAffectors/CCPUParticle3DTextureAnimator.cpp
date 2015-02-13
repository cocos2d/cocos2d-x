/****************************************************************************
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

#include "CCPUParticle3DTextureAnimator.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN
// Constants
const float PUParticle3DTextureAnimator::DEFAULT_TIME_STEP = 0.0f;
const unsigned short PUParticle3DTextureAnimator::DEFAULT_TEXCOORDS_START = 0;
const unsigned short PUParticle3DTextureAnimator::DEFAULT_TEXCOORDS_END = 0;
const PUParticle3DTextureAnimator::TextureAnimationType PUParticle3DTextureAnimator::DEFAULT_ANIMATION_TYPE = PUParticle3DTextureAnimator::TAT_LOOP;
const bool PUParticle3DTextureAnimator::DEFAULT_START_RANDOM = true;

//-----------------------------------------------------------------------
PUParticle3DTextureAnimator::PUParticle3DTextureAnimator(void) : 
    PUParticle3DAffector(),
    _animationTimeStep(DEFAULT_TIME_STEP),
    _animationTimeStepSet(false),
    _nextIndex(false),
    _textureAnimationType(DEFAULT_ANIMATION_TYPE),
    _textureCoordsStart(DEFAULT_TEXCOORDS_START),
    _textureCoordsEnd(DEFAULT_TEXCOORDS_END),
    _startRandom(DEFAULT_START_RANDOM),
    _animationTimeStepCount(0.0f)
{
}
//-----------------------------------------------------------------------
PUParticle3DTextureAnimator::~PUParticle3DTextureAnimator(void)
{
}
//-----------------------------------------------------------------------
float PUParticle3DTextureAnimator::getAnimationTimeStep(void) const
{
    return _animationTimeStep;
}
//-----------------------------------------------------------------------
void PUParticle3DTextureAnimator::setAnimationTimeStep(float animationTimeStep)
{
    _animationTimeStep = animationTimeStep;
    _animationTimeStepSet = true;
}
//-----------------------------------------------------------------------
PUParticle3DTextureAnimator::TextureAnimationType PUParticle3DTextureAnimator::getTextureAnimationType(void) const
{
    return _textureAnimationType;
}
//-----------------------------------------------------------------------
void PUParticle3DTextureAnimator::setTextureAnimationType(PUParticle3DTextureAnimator::TextureAnimationType textureAnimationType)
{
    _textureAnimationType = textureAnimationType;
}
//-----------------------------------------------------------------------
unsigned short PUParticle3DTextureAnimator::getTextureCoordsStart(void) const
{
    return _textureCoordsStart;
}
//-----------------------------------------------------------------------
void PUParticle3DTextureAnimator::setTextureCoordsStart(unsigned short textureCoordsStart)
{
    _textureCoordsStart = textureCoordsStart;
}
//-----------------------------------------------------------------------
unsigned short PUParticle3DTextureAnimator::getTextureCoordsEnd(void) const
{
    return _textureCoordsEnd;
}
//-----------------------------------------------------------------------
void PUParticle3DTextureAnimator::setTextureCoordsEnd(unsigned short textureCoordsEnd)
{
    _textureCoordsEnd = textureCoordsEnd;
}
//-----------------------------------------------------------------------
bool PUParticle3DTextureAnimator::isStartRandom(void) const
{
    return _startRandom;
}
//-----------------------------------------------------------------------
void PUParticle3DTextureAnimator::setStartRandom(bool startRandom)
{
    _startRandom = startRandom;
}
//-----------------------------------------------------------------------
void PUParticle3DTextureAnimator::initParticleForEmission(PUParticle3D* particle)
{
    //// Only continue if the particle is a visual particle
    //if (particle->particleType != Particle::PT_VISUAL)
    //	return;

    // Set first image
    if (_startRandom)
    {
        particle->textureCoordsCurrent = (unsigned short)cocos2d::random((float)_textureCoordsStart, (float)_textureCoordsEnd + 0.999f);
    }
    else
    {
        particle->textureCoordsCurrent = _textureCoordsStart;
    }

    // Calculate the animationTimeStep
    if (!_animationTimeStepSet)
    {
        // Set the animation time step for each particle
        switch(_textureAnimationType)
        {
        case TAT_LOOP:
            {
                particle->textureAnimationTimeStep = particle->timeToLive / (_textureCoordsEnd - _textureCoordsStart + 1);
            }
            break;

        case TAT_UP_DOWN:
            {
                particle->textureAnimationTimeStep = particle->timeToLive / (2 * (_textureCoordsEnd - _textureCoordsStart) + 1);
            }
            break;

        case TAT_RANDOM:
            {
                particle->textureAnimationTimeStep = particle->timeToLive;
            }
            break;
        }
    }
}
//-----------------------------------------------------------------------
void PUParticle3DTextureAnimator::preUpdateAffector(float deltaTime)
{
    // Determine the next texture coords index (global)
    if (_animationTimeStepSet)
    {
        _nextIndex = false;
        _animationTimeStepCount += deltaTime;
        if (_animationTimeStepCount > _animationTimeStep)
        {
            _animationTimeStepCount -= _animationTimeStep;
            _nextIndex = true;
        }
    }
}
//-----------------------------------------------------------------------
void PUParticle3DTextureAnimator::determineNextTextureCoords(PUParticle3D* visualParticle)
{
    switch(_textureAnimationType)
    {
    case TAT_LOOP:
        {
            if (visualParticle->textureCoordsCurrent >= _textureCoordsEnd)
            {
                visualParticle->textureCoordsCurrent = _textureCoordsStart;
            }
            else
            {
                (visualParticle->textureCoordsCurrent)++;
            }
        }
        break;

    case TAT_UP_DOWN:
        {
            if (visualParticle->textureAnimationDirectionUp == true)
            {
                // Going up
                if (visualParticle->textureCoordsCurrent >= _textureCoordsEnd)
                {
                    (visualParticle->textureCoordsCurrent)--;
                    visualParticle->textureAnimationDirectionUp = false;
                }
                else
                {
                    (visualParticle->textureCoordsCurrent)++;
                }
            }
            else
            {
                // Going down
                if (visualParticle->textureCoordsCurrent <= _textureCoordsStart)
                {
                    (visualParticle->textureCoordsCurrent)++;
                    visualParticle->textureAnimationDirectionUp = true;
                }
                else
                {
                    (visualParticle->textureCoordsCurrent)--;
                }
            }
        }
        break;

    case TAT_RANDOM:
        {
            // Generate a random texcoord index
            visualParticle->textureCoordsCurrent = (unsigned short)cocos2d::random((float)_textureCoordsStart, (float)_textureCoordsEnd + 0.999f);
        }
        break;
    }
}

void PUParticle3DTextureAnimator::updatePUAffector( PUParticle3D *particle, float deltaTime )
{
    //// Only continue if the particle is a visual particle
    //if (particle->particleType != Particle::PT_VISUAL)
    //	return;

    //for (auto iter : _particleSystem->getParticles())
    {
        //PUParticle3D *particle = iter;
        // Determine the next texture coords index
        if (_animationTimeStepSet)
        {
            if (_nextIndex)
            {
                // Use the global one for all particles
                determineNextTextureCoords(particle);
            }
        }
        else
        {
            particle->textureAnimationTimeStepCount += deltaTime;
            if (particle->textureAnimationTimeStepCount > particle->textureAnimationTimeStep)
            {
                particle->textureAnimationTimeStepCount -= particle->textureAnimationTimeStep;
                determineNextTextureCoords(particle);
            }
        }
    }
}

PUParticle3DTextureAnimator* PUParticle3DTextureAnimator::create()
{
    auto pta = new (std::nothrow) PUParticle3DTextureAnimator();
    pta->autorelease();
    return pta;
}

NS_CC_END