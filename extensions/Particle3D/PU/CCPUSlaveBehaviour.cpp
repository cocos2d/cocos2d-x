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

#include "extensions/Particle3D/PU/CCPUSlaveBehaviour.h"
#include "base/ccMacros.h"

NS_CC_BEGIN

PUSlaveBehaviour::PUSlaveBehaviour()
: masterParticle(nullptr)
{

}

PUSlaveBehaviour::~PUSlaveBehaviour()
{

}

void PUSlaveBehaviour::updateBehaviour( PUParticle3D *particle, float /*deltaTime*/ )
{
    if (masterParticle && !masterParticle->hasEventFlags(PUParticle3D::PEF_EXPIRED))
    {
        particle->position = masterParticle->position;
        particle->direction = masterParticle->direction;
    }
}

PUSlaveBehaviour* PUSlaveBehaviour::clone()
{
    auto pb = PUSlaveBehaviour::create();
    copyAttributesTo(pb);
    return pb;
}

PUSlaveBehaviour* PUSlaveBehaviour::create()
{
    auto pb = new (std::nothrow) PUSlaveBehaviour();
    pb->autorelease();
    return pb;
}

void PUSlaveBehaviour::copyAttributesTo( PUBehaviour* behaviour )
{
    PUBehaviour::copyAttributesTo(behaviour);
}

NS_CC_END
