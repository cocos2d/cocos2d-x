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

#include "CCPUParticleFollower.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float PUParticleFollower::DEFAULT_MAX_DISTANCE = 3.40282e+038f;
const float PUParticleFollower::DEFAULT_MIN_DISTANCE = 10.0f;

//-----------------------------------------------------------------------
PUParticleFollower::PUParticleFollower(void) : 
    PUAffector(),
    _minDistance(DEFAULT_MIN_DISTANCE),
    _maxDistance(DEFAULT_MAX_DISTANCE),
    _positionPreviousParticle(Vec3::ZERO),
    _first(false)
{
}

PUParticleFollower::~PUParticleFollower( void )
{

}
//-----------------------------------------------------------------------
float PUParticleFollower::getMaxDistance(void) const
{
    return _maxDistance;
}
//-----------------------------------------------------------------------
void PUParticleFollower::setMaxDistance(float maxDistance)
{
    _maxDistance = maxDistance;
}
//-----------------------------------------------------------------------
float PUParticleFollower::getMinDistance(void) const
{
    return _minDistance;
}
//-----------------------------------------------------------------------
void PUParticleFollower::setMinDistance(float minDistance)
{
    _minDistance = minDistance;
}

void PUParticleFollower::updatePUAffector( PUParticle3D *particle, float deltaTime )
{
    //_first = true;
    //for (auto iter : _particleSystem->getParticles())
    {
        //PUParticle3D *particle = iter;
        if (!_first)
        {
            // Change in V 1.3.1
            // Only proceed if it isn the first one. Compensate for scaling.
            float distance = (particle->position).distance(_positionPreviousParticle);
            float avgScale = 0.3333f * (_affectorScale.x + _affectorScale.y + _affectorScale.z);
            float scaledMinDistance = avgScale * _minDistance;
            if (distance > scaledMinDistance && distance < avgScale * _maxDistance)
            {
                // This particle drifts too much from the previous one; correct it!
                float f = scaledMinDistance/distance;
                particle->position = _positionPreviousParticle + f * (particle->position - _positionPreviousParticle);
            }
        }
        _positionPreviousParticle = particle->position;
        _first = false;
    }
}

void PUParticleFollower::firstParticleUpdate( PUParticle3D *particle, float deltaTime )
{
    _first = true;
}

PUParticleFollower* PUParticleFollower::create()
{
    auto ppf = new (std::nothrow) PUParticleFollower();
    ppf->autorelease();
    return ppf;
}

void PUParticleFollower::copyAttributesTo( PUAffector* affector )
{
    PUAffector::copyAttributesTo(affector);

    PUParticleFollower* particleFollower = static_cast<PUParticleFollower*>(affector);
    particleFollower->_maxDistance = _maxDistance;
    particleFollower->_minDistance = _minDistance;
}

NS_CC_END
