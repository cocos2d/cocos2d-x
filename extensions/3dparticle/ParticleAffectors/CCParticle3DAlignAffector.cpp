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

#include "CCParticle3DAlignAffector.h"
#include "3dparticle/CCParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const bool Particle3DAlignAffector::DEFAULT_RESIZE = false;
    
//-----------------------------------------------------------------------
Particle3DAlignAffector::Particle3DAlignAffector() 
    : Particle3DAffector()
    , _resize(DEFAULT_RESIZE)
{
}

Particle3DAlignAffector::~Particle3DAlignAffector()
{
}

bool Particle3DAlignAffector::isResize() const
{
    return _resize;
}

void Particle3DAlignAffector::setResize(bool resize)
{
    _resize = resize;
}

void Particle3DAlignAffector::updateAffector( float deltaTime )
{
    auto particles = _particleSystem->getParticles();
    if (!particles.empty())
    {
        Particle3D *preParticle = particles[0];
        for (unsigned int i = 1; i < particles.size(); ++i)
        {
            Particle3D *particle = particles[i];
            Vec3 diff = preParticle->position - particle->position;
            if (_resize)
            {
                particle->setOwnDimensions(particle->width, diff.length(), particle->depth);
            }
            diff.normalize();
            particle->orientation.x = diff.x;
            particle->orientation.y = diff.y;
            particle->orientation.z = diff.z;
            preParticle = particle;
        }
    }
}

NS_CC_END