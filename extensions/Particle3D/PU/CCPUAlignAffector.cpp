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

#include "CCPUAlignAffector.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const bool PUAlignAffector::DEFAULT_RESIZE = false;
    
//-----------------------------------------------------------------------
PUAlignAffector::PUAlignAffector() 
    : PUAffector()
    , _resize(DEFAULT_RESIZE)
{
}

PUAlignAffector::~PUAlignAffector()
{
}

bool PUAlignAffector::isResize() const
{
    return _resize;
}

void PUAlignAffector::setResize(bool resize)
{
    _resize = resize;
}

void PUAlignAffector::updatePUAffector( PUParticle3D *particle, float /*deltaTime*/ )
{
    //auto particles = _particleSystem->getParticles();
    //if (!particles.empty())
    {
        //PUParticle3D *preParticle = particles[0];
        //for (unsigned int i = 1; i < particles.size(); ++i)
        {
            //PUParticle3D *particle = particles[i];
            Vec3 diff = _previousParticle->position - particle->position;
            if (_resize)
            {
                particle->setOwnDimensions(particle->width, diff.length(), particle->depth);
            }
            diff.normalize();
            particle->orientation.x = diff.x;
            particle->orientation.y = diff.y;
            particle->orientation.z = diff.z;
            _previousParticle = particle;
        }
    }
}

void PUAlignAffector::firstParticleUpdate( PUParticle3D *particle, float /*deltaTime*/ )
{
    _previousParticle = particle;
}

PUAlignAffector* PUAlignAffector::create()
{
    auto paa = new (std::nothrow) PUAlignAffector();
    paa->autorelease();
    return paa;
}

void PUAlignAffector::copyAttributesTo( PUAffector* affector )
{
    PUAffector::copyAttributesTo(affector);

    PUAlignAffector* alignAffector = static_cast<PUAlignAffector*>(affector);
    alignAffector->_resize = _resize;
}

NS_CC_END
