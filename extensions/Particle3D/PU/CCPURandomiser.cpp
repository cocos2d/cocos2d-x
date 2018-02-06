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

#include "CCPURandomiser.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const Vec3 PURandomiser::DEFAULT_MAX_DEVIATION(0, 0, 0);
const float PURandomiser::DEFAULT_TIME_STEP = 0.0f;
const bool PURandomiser::DEFAULT_RANDOM_DIRECTION = true;

//-----------------------------------------------------------------------
PURandomiser::PURandomiser(void) : 
    PUAffector(),
    _maxDeviationX(DEFAULT_MAX_DEVIATION.x),
    _maxDeviationY(DEFAULT_MAX_DEVIATION.y),
    _maxDeviationZ(DEFAULT_MAX_DEVIATION.z),
    _timeSinceLastUpdate(0.0f),
    _timeStep(DEFAULT_TIME_STEP),
    _randomDirection(DEFAULT_RANDOM_DIRECTION),
    _update(true)
{
}
PURandomiser::~PURandomiser( void )
{

}
//-----------------------------------------------------------------------
float PURandomiser::getMaxDeviationX(void) const
{
    return _maxDeviationX;
}
//-----------------------------------------------------------------------
void PURandomiser::setMaxDeviationX(float maxDeviationX)
{
    _maxDeviationX = maxDeviationX;
}
//-----------------------------------------------------------------------
float PURandomiser::getMaxDeviationY(void) const
{
    return _maxDeviationY;
}
//-----------------------------------------------------------------------
void PURandomiser::setMaxDeviationY(float maxDeviationY)
{
    _maxDeviationY = maxDeviationY;
}
//-----------------------------------------------------------------------
float PURandomiser::getMaxDeviationZ(void) const
{
    return _maxDeviationZ;
}
//-----------------------------------------------------------------------
void PURandomiser::setMaxDeviationZ(float maxDeviationZ)
{
    _maxDeviationZ = maxDeviationZ;
}
//-----------------------------------------------------------------------
float PURandomiser::getTimeStep(void) const
{
    return _timeStep;
}
//-----------------------------------------------------------------------
void PURandomiser::setTimeStep(float timeStep)
{
    _timeStep = timeStep;
    _timeSinceLastUpdate = timeStep;
}
//-----------------------------------------------------------------------
bool PURandomiser::isRandomDirection(void) const
{
    return _randomDirection;
}
//-----------------------------------------------------------------------
void PURandomiser::setRandomDirection(bool randomDirection)
{
    _randomDirection = randomDirection;
}
//-----------------------------------------------------------------------
void PURandomiser::preUpdateAffector(float deltaTime)
{
    if (/*technique->getNumberOfEmittedParticles()*/static_cast<PUParticleSystem3D *>(_particleSystem)->getAliveParticleCount() > 0)
    {
        _timeSinceLastUpdate += deltaTime;
        if (_timeSinceLastUpdate > _timeStep)
        {
            _timeSinceLastUpdate -= _timeStep;
            _update = true;
        }
    }
}
//-----------------------------------------------------------------------
void PURandomiser::updatePUAffector( PUParticle3D *particle, float /*deltaTime*/ )
{
    //for (auto iter : _particleSystem->getParticles())
    {
        //PUParticle3D *particle = iter;
        if (_update)
        {
            if (_randomDirection)
            {
                // Random direction: Change the direction after each update
                particle->direction.add(CCRANDOM_MINUS1_1() * _maxDeviationX,
                    CCRANDOM_MINUS1_1() * _maxDeviationY,
                    CCRANDOM_MINUS1_1() * _maxDeviationZ);
            }
            else
            {
                // Explicitly check on 'freezed', because it passes the techniques' validation.
                if (particle->isFreezed())
                    return;

                // Random position: Add the position deviation after each update
                particle->position.add(CCRANDOM_MINUS1_1() * _maxDeviationX * _affectorScale.x,
                    CCRANDOM_MINUS1_1() * _maxDeviationY * _affectorScale.y,
                    CCRANDOM_MINUS1_1() * _maxDeviationZ * _affectorScale.z);
            }
        }
    }
}

//-----------------------------------------------------------------------
void PURandomiser::postUpdateAffector(float /*deltaTime*/)
{
    _update = false;
}

PURandomiser* PURandomiser::create()
{
    auto pr = new (std::nothrow) PURandomiser();
    pr->autorelease();
    return pr;
}

void PURandomiser::copyAttributesTo( PUAffector* affector )
{
    PUAffector::copyAttributesTo(affector);

    PURandomiser* randomiser = static_cast<PURandomiser*>(affector);
    randomiser->_maxDeviationX = _maxDeviationX;
    randomiser->_maxDeviationY = _maxDeviationY;
    randomiser->_maxDeviationZ = _maxDeviationZ;
    randomiser->setTimeStep(_timeStep); // Also sets time since last update to appropriate value
    randomiser->_randomDirection = _randomDirection;
}

NS_CC_END
