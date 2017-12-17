/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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

#include "CCPUBoxEmitter.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float CCPUBoxEmitter::DEFAULT_WIDTH = 100.0f;
const float CCPUBoxEmitter::DEFAULT_HEIGHT = 100.0f;
const float CCPUBoxEmitter::DEFAULT_DEPTH = 100.0f;

//-----------------------------------------------------------------------
CCPUBoxEmitter::CCPUBoxEmitter(void) : 
    PUEmitter(),
    _height(DEFAULT_HEIGHT),
    _width(DEFAULT_WIDTH),
    _depth(DEFAULT_DEPTH),
    _xRange(0.5f * DEFAULT_WIDTH),
    _yRange(0.5f * DEFAULT_HEIGHT),
    _zRange(0.5f * DEFAULT_DEPTH)
{
}
//-----------------------------------------------------------------------
float CCPUBoxEmitter::getHeight() const
{
    return _height;
}
//-----------------------------------------------------------------------
void CCPUBoxEmitter::setHeight(const float height)
{
    _height = height;
    _yRange = 0.5f * height;
}
//-----------------------------------------------------------------------
float CCPUBoxEmitter::getWidth() const
{
    return _width;
}
//-----------------------------------------------------------------------
void CCPUBoxEmitter::setWidth(const float width)
{
    _width = width;
    _xRange = 0.5f * width;
}
//-----------------------------------------------------------------------
float CCPUBoxEmitter::getDepth() const
{
    return _depth;
}
//-----------------------------------------------------------------------
void CCPUBoxEmitter::setDepth(const float depth)
{
    _depth = depth;
    _zRange = 0.5f * depth;
}
//-----------------------------------------------------------------------
void CCPUBoxEmitter::initParticlePosition(PUParticle3D* particle)
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

CCPUBoxEmitter* CCPUBoxEmitter::create()
{
    auto pe = new (std::nothrow) CCPUBoxEmitter();
    pe->autorelease();
    return pe;
}

void CCPUBoxEmitter::copyAttributesTo( PUEmitter* emitter )
{
    PUEmitter::copyAttributesTo(emitter);

    CCPUBoxEmitter* boxEmitter = static_cast<CCPUBoxEmitter*>(emitter);
    boxEmitter->_height = _height;
    boxEmitter->_width = _width;
    boxEmitter->_depth = _depth;
    boxEmitter->_xRange = _xRange;
    boxEmitter->_yRange = _yRange;
    boxEmitter->_zRange = _zRange;
}

CCPUBoxEmitter* CCPUBoxEmitter::clone()
{
    auto be = CCPUBoxEmitter::create();
    copyAttributesTo(be);
    return be;
}

NS_CC_END