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

#include "CCParticle3DFlockCenteringAffector.h"
#include "3dparticle/CCParticleSystem3D.h"

NS_CC_BEGIN
//-----------------------------------------------------------------------
Particle3DFlockCenteringAffector::Particle3DFlockCenteringAffector() 
: Particle3DAffector(),
  _sum(Vec3::ZERO),
  _average(Vec3::ZERO),
  _count(0.0f)
{
}

Particle3DFlockCenteringAffector::~Particle3DFlockCenteringAffector()
{
}

void Particle3DFlockCenteringAffector::updateAffector( float deltaTime )
{
    for (auto iter : _particleSystem->getParticles())
    {
        Particle3D *particle = iter;
        _sum += particle->position;
        _count++;
        particle->direction += (_average - particle->position) * deltaTime; // use average of the previous update
    }
}

void Particle3DFlockCenteringAffector::preUpdateAffector( float deltaTime )
{
    if (_count != 0)
    {
        // Calculate the average of the previous update
        _average = _sum / _count;
    }
    else
    {
        _average = getDerivedPosition(); // Set to position of the affector
    }
    _sum = Vec3::ZERO;
    _count = 0;
}

NS_CC_END