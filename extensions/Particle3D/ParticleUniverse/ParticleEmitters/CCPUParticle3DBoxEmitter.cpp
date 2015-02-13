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

#include "CCPUParticle3DBoxEmitter.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float PUParticle3DBoxEmitter::DEFAULT_WIDTH = 100.0f;
const float PUParticle3DBoxEmitter::DEFAULT_HEIGHT = 100.0f;
const float PUParticle3DBoxEmitter::DEFAULT_DEPTH = 100.0f;

//-----------------------------------------------------------------------
PUParticle3DBoxEmitter::PUParticle3DBoxEmitter(void) : 
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
const float PUParticle3DBoxEmitter::getHeight(void) const
{
    return _height;
}
//-----------------------------------------------------------------------
void PUParticle3DBoxEmitter::setHeight(const float height)
{
    _height = height;
    _yRange = 0.5f * height;
}
//-----------------------------------------------------------------------
const float PUParticle3DBoxEmitter::getWidth(void) const
{
    return _width;
}
//-----------------------------------------------------------------------
void PUParticle3DBoxEmitter::setWidth(const float width)
{
    _width = width;
    _xRange = 0.5f * width;
}
//-----------------------------------------------------------------------
const float PUParticle3DBoxEmitter::getDepth(void) const
{
    return _depth;
}
//-----------------------------------------------------------------------
void PUParticle3DBoxEmitter::setDepth(const float depth)
{
    _depth = depth;
    _zRange = 0.5f * depth;
}
//-----------------------------------------------------------------------
void PUParticle3DBoxEmitter::initParticlePosition(PUParticle3D* particle)
{
    //ParticleSystem* sys = mParentTechnique->getParentSystem();

    //if (sys)
    {
        Mat4 rotMat;
        Mat4::createRotation(static_cast<PUParticleSystem3D *>(_particleSystem)->getDerivedOrientation(), &rotMat);
        particle->position = getDerivedPosition() + 
            rotMat *
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

PUParticle3DBoxEmitter* PUParticle3DBoxEmitter::create()
{
    auto pe = new (std::nothrow) PUParticle3DBoxEmitter();
    pe->autorelease();
    return pe;
}

NS_CC_END