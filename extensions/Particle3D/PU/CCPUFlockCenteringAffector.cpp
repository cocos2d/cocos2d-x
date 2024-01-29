/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "CCPUFlockCenteringAffector.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN
//-----------------------------------------------------------------------
PUFlockCenteringAffector::PUFlockCenteringAffector() 
: PUAffector(),
  _count(0.0f)
{
}

PUFlockCenteringAffector::~PUFlockCenteringAffector()
{
}

void PUFlockCenteringAffector::updatePUAffector( PUParticle3D *particle, float deltaTime )
{
    //for (auto iter : _particleSystem->getParticles())
    {
        //PUParticle3D *particle = iter;
        _sum += particle->position;
        _count++;
        particle->direction += (_average - particle->position) * deltaTime; // use average of the previous update
    }
}

void PUFlockCenteringAffector::preUpdateAffector( float /*deltaTime*/ )
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
    _sum.setZero();
    _count = 0;
}

PUFlockCenteringAffector* PUFlockCenteringAffector::create()
{
    auto pfca = new (std::nothrow) PUFlockCenteringAffector();
    pfca->autorelease();
    return pfca;
}

void PUFlockCenteringAffector::copyAttributesTo( PUAffector* affector )
{
    PUAffector::copyAttributesTo(affector);
    PUFlockCenteringAffector* flockCenteringAffector = static_cast<PUFlockCenteringAffector*>(affector);
    flockCenteringAffector->_sum = _sum;
    flockCenteringAffector->_average = _average;
    flockCenteringAffector->_count = _count;
}

NS_CC_END
