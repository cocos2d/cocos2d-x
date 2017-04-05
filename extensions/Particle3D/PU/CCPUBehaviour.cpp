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

#include "extensions/Particle3D/PU/CCPUBehaviour.h"
#include "base/ccMacros.h"

NS_CC_BEGIN

PUBehaviour::PUBehaviour( void ): 
_particleSystem(nullptr),
_behaviourScale(Vec3::ONE)
{}

PUBehaviour::~PUBehaviour( void )
{}

void PUBehaviour::updateBehaviour(PUParticle3D* /*particle*/, float /*deltaTime*/)
{}

void PUBehaviour::initParticleForEmission(PUParticle3D* /*particle*/)
{}

void PUBehaviour::initParticleForExpiration(PUParticle3D* /*particle*/, float /*timeElapsed*/)
{}

PUBehaviour* PUBehaviour::clone()
{
    auto pb = new (std::nothrow) PUBehaviour;
    pb->autorelease();
    copyAttributesTo(pb);
    return pb;
}

void PUBehaviour::copyAttributesTo( PUBehaviour* behaviour )
{
    behaviour->_particleSystem = _particleSystem;
    behaviour->_behaviourType = _behaviourType;
    behaviour->_behaviourScale = _behaviourScale;
}

NS_CC_END
