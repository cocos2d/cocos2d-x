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

#include "CCPUParticle3DParticleFollower.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float PUParticle3DParticleFollower::DEFAULT_MAX_DISTANCE = 3.40282e+038f;
const float PUParticle3DParticleFollower::DEFAULT_MIN_DISTANCE = 10.0f;

//-----------------------------------------------------------------------
PUParticle3DParticleFollower::PUParticle3DParticleFollower(void) : 
    PUParticle3DAffector(),
    _minDistance(DEFAULT_MIN_DISTANCE),
    _maxDistance(DEFAULT_MAX_DISTANCE),
    _positionPreviousParticle(Vec3::ZERO),
    _first(false)
{
}

PUParticle3DParticleFollower::~PUParticle3DParticleFollower( void )
{

}
//-----------------------------------------------------------------------
float PUParticle3DParticleFollower::getMaxDistance(void) const
{
    return _maxDistance;
}
//-----------------------------------------------------------------------
void PUParticle3DParticleFollower::setMaxDistance(float maxDistance)
{
    _maxDistance = maxDistance;
}
//-----------------------------------------------------------------------
float PUParticle3DParticleFollower::getMinDistance(void) const
{
    return _minDistance;
}
//-----------------------------------------------------------------------
void PUParticle3DParticleFollower::setMinDistance(float minDistance)
{
    _minDistance = minDistance;
}

void PUParticle3DParticleFollower::updatePUAffector( PUParticle3D *particle, float deltaTime )
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

void PUParticle3DParticleFollower::firstParticleUpdate( PUParticle3D *particle, float deltaTime )
{
    _first = true;
}

PUParticle3DParticleFollower* PUParticle3DParticleFollower::create()
{
    auto ppf = new (std::nothrow) PUParticle3DParticleFollower();
    ppf->autorelease();
    return ppf;
}

NS_CC_END