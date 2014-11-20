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

#include "CCParticle3DRandomiser.h"
#include "3dparticle/CCParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const Vec3 Particle3DRandomiser::DEFAULT_MAX_DEVIATION(0, 0, 0);
const float Particle3DRandomiser::DEFAULT_TIME_STEP = 0.0f;
const bool Particle3DRandomiser::DEFAULT_RANDOM_DIRECTION = true;

//-----------------------------------------------------------------------
Particle3DRandomiser::Particle3DRandomiser(void) : 
    Particle3DAffector(),
    _maxDeviationX(DEFAULT_MAX_DEVIATION.x),
    _maxDeviationY(DEFAULT_MAX_DEVIATION.y),
    _maxDeviationZ(DEFAULT_MAX_DEVIATION.z),
    _timeSinceLastUpdate(0.0f),
    _timeStep(DEFAULT_TIME_STEP),
    _update(true),
    _randomDirection(DEFAULT_RANDOM_DIRECTION)
{
}
Particle3DRandomiser::~Particle3DRandomiser( void )
{

}
//-----------------------------------------------------------------------
float Particle3DRandomiser::getMaxDeviationX(void) const
{
    return _maxDeviationX;
}
//-----------------------------------------------------------------------
void Particle3DRandomiser::setMaxDeviationX(float maxDeviationX)
{
    _maxDeviationX = maxDeviationX;
}
//-----------------------------------------------------------------------
float Particle3DRandomiser::getMaxDeviationY(void) const
{
    return _maxDeviationY;
}
//-----------------------------------------------------------------------
void Particle3DRandomiser::setMaxDeviationY(float maxDeviationY)
{
    _maxDeviationY = maxDeviationY;
}
//-----------------------------------------------------------------------
float Particle3DRandomiser::getMaxDeviationZ(void) const
{
    return _maxDeviationZ;
}
//-----------------------------------------------------------------------
void Particle3DRandomiser::setMaxDeviationZ(float maxDeviationZ)
{
    _maxDeviationZ = maxDeviationZ;
}
//-----------------------------------------------------------------------
float Particle3DRandomiser::getTimeStep(void) const
{
    return _timeStep;
}
//-----------------------------------------------------------------------
void Particle3DRandomiser::setTimeStep(float timeStep)
{
    _timeStep = timeStep;
    _timeSinceLastUpdate = timeStep;
}
//-----------------------------------------------------------------------
bool Particle3DRandomiser::isRandomDirection(void) const
{
    return _randomDirection;
}
//-----------------------------------------------------------------------
void Particle3DRandomiser::setRandomDirection(bool randomDirection)
{
    _randomDirection = randomDirection;
}
//-----------------------------------------------------------------------
void Particle3DRandomiser::preUpdateAffector(float deltaTime)
{
    if (/*technique->getNumberOfEmittedParticles()*/_particleSystem->getParticles().size() > 0)
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
void Particle3DRandomiser::updateAffector( float deltaTime )
{
    for (auto iter : _particleSystem->getParticles())
    {
        Particle3D *particle = iter;
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
void Particle3DRandomiser::postUpdateAffector(float deltaTime)
{
    _update = false;
}
NS_CC_END