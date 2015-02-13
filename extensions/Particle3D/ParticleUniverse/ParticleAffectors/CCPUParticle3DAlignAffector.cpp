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

#include "CCPUParticle3DAlignAffector.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const bool PUParticle3DAlignAffector::DEFAULT_RESIZE = false;
    
//-----------------------------------------------------------------------
PUParticle3DAlignAffector::PUParticle3DAlignAffector() 
    : PUParticle3DAffector()
    , _resize(DEFAULT_RESIZE)
{
}

PUParticle3DAlignAffector::~PUParticle3DAlignAffector()
{
}

bool PUParticle3DAlignAffector::isResize() const
{
    return _resize;
}

void PUParticle3DAlignAffector::setResize(bool resize)
{
    _resize = resize;
}

void PUParticle3DAlignAffector::updatePUAffector( PUParticle3D *particle, float deltaTime )
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

void PUParticle3DAlignAffector::firstParticleUpdate( PUParticle3D *particle, float deltaTime )
{
    _previousParticle = particle;
}

PUParticle3DAlignAffector* PUParticle3DAlignAffector::create()
{
    auto paa = new (std::nothrow) PUParticle3DAlignAffector();
    paa->autorelease();
    return paa;
}

NS_CC_END