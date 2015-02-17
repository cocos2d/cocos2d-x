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

#include "CCPUParticle3DRandomiser.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const Vec3 PUParticle3DRandomiser::DEFAULT_MAX_DEVIATION(0, 0, 0);
const float PUParticle3DRandomiser::DEFAULT_TIME_STEP = 0.0f;
const bool PUParticle3DRandomiser::DEFAULT_RANDOM_DIRECTION = true;

//-----------------------------------------------------------------------
PUParticle3DRandomiser::PUParticle3DRandomiser(void) : 
    PUParticle3DAffector(),
    _maxDeviationX(DEFAULT_MAX_DEVIATION.x),
    _maxDeviationY(DEFAULT_MAX_DEVIATION.y),
    _maxDeviationZ(DEFAULT_MAX_DEVIATION.z),
    _timeSinceLastUpdate(0.0f),
    _timeStep(DEFAULT_TIME_STEP),
    _update(true),
    _randomDirection(DEFAULT_RANDOM_DIRECTION)
{
}
PUParticle3DRandomiser::~PUParticle3DRandomiser( void )
{

}
//-----------------------------------------------------------------------
float PUParticle3DRandomiser::getMaxDeviationX(void) const
{
    return _maxDeviationX;
}
//-----------------------------------------------------------------------
void PUParticle3DRandomiser::setMaxDeviationX(float maxDeviationX)
{
    _maxDeviationX = maxDeviationX;
}
//-----------------------------------------------------------------------
float PUParticle3DRandomiser::getMaxDeviationY(void) const
{
    return _maxDeviationY;
}
//-----------------------------------------------------------------------
void PUParticle3DRandomiser::setMaxDeviationY(float maxDeviationY)
{
    _maxDeviationY = maxDeviationY;
}
//-----------------------------------------------------------------------
float PUParticle3DRandomiser::getMaxDeviationZ(void) const
{
    return _maxDeviationZ;
}
//-----------------------------------------------------------------------
void PUParticle3DRandomiser::setMaxDeviationZ(float maxDeviationZ)
{
    _maxDeviationZ = maxDeviationZ;
}
//-----------------------------------------------------------------------
float PUParticle3DRandomiser::getTimeStep(void) const
{
    return _timeStep;
}
//-----------------------------------------------------------------------
void PUParticle3DRandomiser::setTimeStep(float timeStep)
{
    _timeStep = timeStep;
    _timeSinceLastUpdate = timeStep;
}
//-----------------------------------------------------------------------
bool PUParticle3DRandomiser::isRandomDirection(void) const
{
    return _randomDirection;
}
//-----------------------------------------------------------------------
void PUParticle3DRandomiser::setRandomDirection(bool randomDirection)
{
    _randomDirection = randomDirection;
}
//-----------------------------------------------------------------------
void PUParticle3DRandomiser::preUpdateAffector(float deltaTime)
{
    if (/*technique->getNumberOfEmittedParticles()*/_particleSystem->getParticlePool().getActiveParticleList().size() > 0)
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
void PUParticle3DRandomiser::updatePUAffector( PUParticle3D *particle, float deltaTime )
{
    //for (auto iter : _particleSystem->getParticles())
    {
        //PUParticle3D *particle = iter;
        if (_update)
        {
            if (_randomDirection)
            {
                // Random direction: Change the direction after each update
                particle->direction += Vec3(CCRANDOM_MINUS1_1() * _maxDeviationX,
                    CCRANDOM_MINUS1_1() * _maxDeviationY,
                    CCRANDOM_MINUS1_1() * _maxDeviationZ);
            }
            else
            {
                // Explicitly check on 'freezed', because it passes the techniques' validation.
                if (particle->isFreezed())
                    return;

                // Random position: Add the position deviation after each update
                particle->position += Vec3(CCRANDOM_MINUS1_1() * _maxDeviationX * _affectorScale.x,
                    CCRANDOM_MINUS1_1() * _maxDeviationY * _affectorScale.y,
                    CCRANDOM_MINUS1_1() * _maxDeviationZ * _affectorScale.z);
            }
        }
    }
}

//-----------------------------------------------------------------------
void PUParticle3DRandomiser::postUpdateAffector(float deltaTime)
{
    _update = false;
}

PUParticle3DRandomiser* PUParticle3DRandomiser::create()
{
    auto pr = new (std::nothrow) PUParticle3DRandomiser();
    pr->autorelease();
    return pr;
}

NS_CC_END