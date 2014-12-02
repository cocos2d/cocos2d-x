/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#include "CCParticle3DBoxEmitter.h"
#include "3dparticle/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float Particle3DBoxEmitter::DEFAULT_WIDTH = 100.0f;
const float Particle3DBoxEmitter::DEFAULT_HEIGHT = 100.0f;
const float Particle3DBoxEmitter::DEFAULT_DEPTH = 100.0f;

//-----------------------------------------------------------------------
Particle3DBoxEmitter::Particle3DBoxEmitter(void) : 
    PUParticle3DEmitter(),
    _width(DEFAULT_WIDTH),
    _height(DEFAULT_HEIGHT),
    _depth(DEFAULT_DEPTH),
    _xRange(0.5f * DEFAULT_WIDTH),
    _yRange(0.5f * DEFAULT_HEIGHT),
    _zRange(0.5f * DEFAULT_DEPTH)
{
}
//-----------------------------------------------------------------------
const float Particle3DBoxEmitter::getHeight(void) const
{
    return _height;
}
//-----------------------------------------------------------------------
void Particle3DBoxEmitter::setHeight(const float height)
{
    _height = height;
    _yRange = 0.5f * height;
}
//-----------------------------------------------------------------------
const float Particle3DBoxEmitter::getWidth(void) const
{
    return _width;
}
//-----------------------------------------------------------------------
void Particle3DBoxEmitter::setWidth(const float width)
{
    _width = width;
    _xRange = 0.5f * width;
}
//-----------------------------------------------------------------------
const float Particle3DBoxEmitter::getDepth(void) const
{
    return _depth;
}
//-----------------------------------------------------------------------
void Particle3DBoxEmitter::setDepth(const float depth)
{
    _depth = depth;
    _zRange = 0.5f * depth;
}
//-----------------------------------------------------------------------
void Particle3DBoxEmitter::initParticlePosition(PUParticle3D* particle)
{
    //ParticleSystem* sys = mParentTechnique->getParentSystem();

    //if (sys)
    {
        particle->position = getDerivedPosition() + 
            //FIXME
            //_particleSystem->getDerivedOrientation() *
            (/*_emitterScale **/
            Vec3(CCRANDOM_MINUS1_1() * _xRange * _emitterScale.x,
            CCRANDOM_MINUS1_1() * _yRange * _emitterScale.y,
            CCRANDOM_MINUS1_1() * _zRange * _emitterScale.z));
    }
    //else
    //{
    //	particle->position = getDerivedPosition() + 
    //		_emitterScale *
    //		Vector3(Math::SymmetricRandom() * _xRange,
    //		Math::SymmetricRandom() * _yRange,
    //		Math::SymmetricRandom() * _zRange);
    //}

    particle->originalPosition = particle->position;
}
NS_CC_END