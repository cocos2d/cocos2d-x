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

#include "CCParticle3DForceFieldAffector.h"
#include "3dparticle/CCParticleSystem3D.h"

NS_CC_BEGIN
//-----------------------------------------------------------------------
// Constants
const ForceField::ForceFieldType Particle3DForceFieldAffector::DEFAULT_FORCEFIELD_TYPE = ForceField::FF_REALTIME_CALC;
const float Particle3DForceFieldAffector::DEFAULT_DELTA = 1.0f;
const float Particle3DForceFieldAffector::DEFAULT_FORCE = 400.0f;
const unsigned short Particle3DForceFieldAffector::DEFAULT_OCTAVES = 2;
const double Particle3DForceFieldAffector::DEFAULT_FREQUENCY = 1.0f;
const double Particle3DForceFieldAffector::DEFAULT_AMPLITUDE = 1.0f;
const double Particle3DForceFieldAffector::DEFAULT_PERSISTENCE = 3.0f;
const unsigned int Particle3DForceFieldAffector::DEFAULT_FORCEFIELDSIZE = 64;
const Vec3 Particle3DForceFieldAffector::DEFAULT_WORLDSIZE = Vec3(500.0f, 500.0f, 500.0f);
const Vec3 Particle3DForceFieldAffector::DEFAULT_MOVEMENT = Vec3(500.0f, 0.0f, 0.0f);
const float Particle3DForceFieldAffector::DEFAULT_MOVEMENT_FREQUENCY = 5.0f;

//-----------------------------------------------------------------------
Particle3DForceFieldAffector::Particle3DForceFieldAffector() :
    _forceFieldType(ForceField::FF_REALTIME_CALC),
    _delta(DEFAULT_DELTA),
    _force(Vec3::ZERO),
    _scaleForce(DEFAULT_FORCE),
    _octaves(DEFAULT_OCTAVES),
    _frequency(DEFAULT_FREQUENCY),
    _amplitude(DEFAULT_AMPLITUDE),
    _persistence(DEFAULT_PERSISTENCE),
    _forceFieldSize(DEFAULT_FORCEFIELDSIZE),
    _worldSize(DEFAULT_WORLDSIZE),
    _prepared(true),
    _ignoreNegativeX(false),
    _ignoreNegativeY(false),
    _ignoreNegativeZ(false),
    _movement(DEFAULT_MOVEMENT),
    _movementSet(false),
    _movementFrequency(DEFAULT_MOVEMENT_FREQUENCY),
    _movementFrequencyCount(0.0f),
    _displacement(Vec3::ZERO),
    _basePosition(Vec3::ZERO),
    _suppressGeneration(false)
{
};
//-----------------------------------------------------------------------
Particle3DForceFieldAffector::~Particle3DForceFieldAffector()
{
};
//-----------------------------------------------------------------------
const ForceField::ForceFieldType Particle3DForceFieldAffector::getForceFieldType(void) const
{
    return _forceFieldType;
}
//-----------------------------------------------------------------------
void Particle3DForceFieldAffector::setForceFieldType(const ForceField::ForceFieldType forceFieldType)
{
    _forceFieldType = forceFieldType;
    if (_suppressGeneration)
        return;

    _forceField.setForceFieldType(forceFieldType);
}
//-----------------------------------------------------------------------
float Particle3DForceFieldAffector::getDelta(void) const
{
    return _delta;
}
//-----------------------------------------------------------------------
void Particle3DForceFieldAffector::setDelta(float delta)
{
    _delta = delta;
}
//-----------------------------------------------------------------------
float Particle3DForceFieldAffector::getScaleForce(void) const
{
    return _scaleForce;
}
//-----------------------------------------------------------------------
void Particle3DForceFieldAffector::setScaleForce(float scaleForce)
{
    _scaleForce = scaleForce;
}
//-----------------------------------------------------------------------
unsigned short Particle3DForceFieldAffector::getOctaves(void) const
{
    return _octaves;
}
//-----------------------------------------------------------------------
void Particle3DForceFieldAffector::setOctaves(unsigned short octaves)
{
    _octaves = octaves;
    if (_suppressGeneration)
        return;

    _forceField.setOctaves(octaves);
}
//-----------------------------------------------------------------------
double Particle3DForceFieldAffector::getFrequency(void) const
{
    return _frequency;
}
//-----------------------------------------------------------------------
void Particle3DForceFieldAffector::setFrequency(double frequency)
{
    _frequency = frequency;
    if (_suppressGeneration)
        return;

    _forceField.setFrequency(frequency);
}
//-----------------------------------------------------------------------
double Particle3DForceFieldAffector::getAmplitude(void) const
{
    return _amplitude;
}
//-----------------------------------------------------------------------
void Particle3DForceFieldAffector::setAmplitude(double amplitude)
{
    _amplitude = amplitude;
    if (_suppressGeneration)
        return;

    _forceField.setAmplitude(amplitude);
}
//-----------------------------------------------------------------------
double Particle3DForceFieldAffector::getPersistence(void) const
{
    return _persistence;
}
//-----------------------------------------------------------------------
void Particle3DForceFieldAffector::setPersistence(double persistence)
{
    _persistence = persistence;
    if (_suppressGeneration)
        return;

    _forceField.setPersistence(persistence);
}
//-----------------------------------------------------------------------
unsigned int Particle3DForceFieldAffector::getForceFieldSize(void) const
{
    return _forceFieldSize;
}
//-----------------------------------------------------------------------
void Particle3DForceFieldAffector::setForceFieldSize(unsigned int forceFieldSize)
{
    _forceFieldSize = forceFieldSize;
    if (_suppressGeneration)
        return;

    _forceField.setForceFieldSize(forceFieldSize);
}
//-----------------------------------------------------------------------
Vec3 Particle3DForceFieldAffector::getWorldSize(void) const
{
    return _worldSize;
}
//-----------------------------------------------------------------------
void Particle3DForceFieldAffector::setWorldSize(const Vec3& worldSize)
{
    _worldSize = worldSize;
    if (_suppressGeneration)
        return;

    _forceField.setWorldSize(worldSize);
}
//-----------------------------------------------------------------------
bool Particle3DForceFieldAffector::getIgnoreNegativeX(void) const
{
    return _ignoreNegativeX;
}
//-----------------------------------------------------------------------
void Particle3DForceFieldAffector::setIgnoreNegativeX(bool ignoreNegativeX)
{
    _ignoreNegativeX = ignoreNegativeX;
}
//-----------------------------------------------------------------------
bool Particle3DForceFieldAffector::getIgnoreNegativeY(void) const
{
    return _ignoreNegativeY;
}
//-----------------------------------------------------------------------
void Particle3DForceFieldAffector::setIgnoreNegativeY(bool ignoreNegativeY)
{
    _ignoreNegativeY = ignoreNegativeY;
}
//-----------------------------------------------------------------------
bool Particle3DForceFieldAffector::getIgnoreNegativeZ(void) const
{
    return _ignoreNegativeZ;
}
//-----------------------------------------------------------------------
void Particle3DForceFieldAffector::setIgnoreNegativeZ(bool ignoreNegativeZ)
{
    _ignoreNegativeZ = ignoreNegativeZ;
}
//-----------------------------------------------------------------------
float Particle3DForceFieldAffector::getMovementFrequency(void) const
{
    return _movementFrequency;
}
//-----------------------------------------------------------------------
void Particle3DForceFieldAffector::setMovementFrequency(float movementFrequency)
{
    _movementFrequency = movementFrequency;
    _movementSet = (movementFrequency > 0.0f);
}
//-----------------------------------------------------------------------
const Vec3& Particle3DForceFieldAffector::getMovement(void) const
{
    return _movement;
}
//-----------------------------------------------------------------------
void Particle3DForceFieldAffector::setMovement(const Vec3& movement)
{
    _movement = movement;
    _movementSet = (movement != Vec3::ZERO);
}
//-----------------------------------------------------------------------
void Particle3DForceFieldAffector::suppressGeneration(bool suppress)
{
    _suppressGeneration = suppress;
}

void Particle3DForceFieldAffector::updateAffector( float deltaTime )
{
    for (auto iter : _particleSystem->getParticles())
    {
        Particle3D *particle = iter;
        _forceField.determineForce(particle->position, _force, _delta);
        // If negative values are ignored, set the force to 0.
        if (_ignoreNegativeX)
        {
            _force.x = 0.0f;
        }
        if (_ignoreNegativeY)
        {
            _force.y = 0.0f;
        }
        if (_ignoreNegativeZ)
        {
            _force.z = 0.0f;
        }
        particle->direction += deltaTime * _scaleForce * _force;
    }
}

void Particle3DForceFieldAffector::notifyStart()
{
    _movementFrequencyCount = 0.0f;
}

void Particle3DForceFieldAffector::preUpdateAffector( float deltaTime )
{
    if (_movementSet)
    {
        if (deltaTime > _movementFrequency)
        {
            // Ignore too large times, because it just blows things up
            return;
        }

        _movementFrequencyCount += deltaTime;
        if (_movementFrequencyCount > _movementFrequency)
        {
            _movementFrequencyCount -= _movementFrequency;
        }

        _displacement = sin(2.0f * M_PI * _movementFrequencyCount/_movementFrequency) * _movement;
        _forceField.setForceFieldPositionBase(_basePosition + _displacement);
    }
}

void Particle3DForceFieldAffector::prepare()
{
    //if (particleTechnique->getParentSystem())
    {
        // Forcefield position is same position as particle system position
        _forceField.initialise(_forceFieldType,
            //FIXME need use  _particleSystem->getDerivedPosition()
            getDerivedPosition(),
            //end FIXME
            _forceFieldSize,
            _octaves,
            _frequency,
            _amplitude,
            _persistence,
            _worldSize);
    
        _basePosition = _forceField.getForceFieldPositionBase();
        _prepared = true;
    }
}

NS_CC_END