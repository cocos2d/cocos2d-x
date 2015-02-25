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

#include "CCPUParticle3DForceFieldAffector.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN
//-----------------------------------------------------------------------
// Constants
const PUForceField::ForceFieldType PUParticle3DForceFieldAffector::DEFAULT_FORCEFIELD_TYPE = PUForceField::FF_REALTIME_CALC;
const float PUParticle3DForceFieldAffector::DEFAULT_DELTA = 1.0f;
const float PUParticle3DForceFieldAffector::DEFAULT_FORCE = 400.0f;
const unsigned short PUParticle3DForceFieldAffector::DEFAULT_OCTAVES = 2;
const double PUParticle3DForceFieldAffector::DEFAULT_FREQUENCY = 1.0f;
const double PUParticle3DForceFieldAffector::DEFAULT_AMPLITUDE = 1.0f;
const double PUParticle3DForceFieldAffector::DEFAULT_PERSISTENCE = 3.0f;
const unsigned int PUParticle3DForceFieldAffector::DEFAULT_FORCEFIELDSIZE = 64;
const Vec3 PUParticle3DForceFieldAffector::DEFAULT_WORLDSIZE = Vec3(500.0f, 500.0f, 500.0f);
const Vec3 PUParticle3DForceFieldAffector::DEFAULT_MOVEMENT = Vec3(500.0f, 0.0f, 0.0f);
const float PUParticle3DForceFieldAffector::DEFAULT_MOVEMENT_FREQUENCY = 5.0f;

//-----------------------------------------------------------------------
PUParticle3DForceFieldAffector::PUParticle3DForceFieldAffector() :
    _forceFieldType(PUForceField::FF_REALTIME_CALC),
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
PUParticle3DForceFieldAffector::~PUParticle3DForceFieldAffector()
{
};
//-----------------------------------------------------------------------
const PUForceField::ForceFieldType PUParticle3DForceFieldAffector::getForceFieldType(void) const
{
    return _forceFieldType;
}
//-----------------------------------------------------------------------
void PUParticle3DForceFieldAffector::setForceFieldType(const PUForceField::ForceFieldType forceFieldType)
{
    _forceFieldType = forceFieldType;
    if (_suppressGeneration)
        return;

    _forceField.setForceFieldType(forceFieldType);
}
//-----------------------------------------------------------------------
float PUParticle3DForceFieldAffector::getDelta(void) const
{
    return _delta;
}
//-----------------------------------------------------------------------
void PUParticle3DForceFieldAffector::setDelta(float delta)
{
    _delta = delta;
}
//-----------------------------------------------------------------------
float PUParticle3DForceFieldAffector::getScaleForce(void) const
{
    return _scaleForce;
}
//-----------------------------------------------------------------------
void PUParticle3DForceFieldAffector::setScaleForce(float scaleForce)
{
    _scaleForce = scaleForce;
}
//-----------------------------------------------------------------------
unsigned short PUParticle3DForceFieldAffector::getOctaves(void) const
{
    return _octaves;
}
//-----------------------------------------------------------------------
void PUParticle3DForceFieldAffector::setOctaves(unsigned short octaves)
{
    _octaves = octaves;
    if (_suppressGeneration)
        return;

    _forceField.setOctaves(octaves);
}
//-----------------------------------------------------------------------
double PUParticle3DForceFieldAffector::getFrequency(void) const
{
    return _frequency;
}
//-----------------------------------------------------------------------
void PUParticle3DForceFieldAffector::setFrequency(double frequency)
{
    _frequency = frequency;
    if (_suppressGeneration)
        return;

    _forceField.setFrequency(frequency);
}
//-----------------------------------------------------------------------
double PUParticle3DForceFieldAffector::getAmplitude(void) const
{
    return _amplitude;
}
//-----------------------------------------------------------------------
void PUParticle3DForceFieldAffector::setAmplitude(double amplitude)
{
    _amplitude = amplitude;
    if (_suppressGeneration)
        return;

    _forceField.setAmplitude(amplitude);
}
//-----------------------------------------------------------------------
double PUParticle3DForceFieldAffector::getPersistence(void) const
{
    return _persistence;
}
//-----------------------------------------------------------------------
void PUParticle3DForceFieldAffector::setPersistence(double persistence)
{
    _persistence = persistence;
    if (_suppressGeneration)
        return;

    _forceField.setPersistence(persistence);
}
//-----------------------------------------------------------------------
unsigned int PUParticle3DForceFieldAffector::getForceFieldSize(void) const
{
    return _forceFieldSize;
}
//-----------------------------------------------------------------------
void PUParticle3DForceFieldAffector::setForceFieldSize(unsigned int forceFieldSize)
{
    _forceFieldSize = forceFieldSize;
    if (_suppressGeneration)
        return;

    _forceField.setForceFieldSize(forceFieldSize);
}
//-----------------------------------------------------------------------
Vec3 PUParticle3DForceFieldAffector::getWorldSize(void) const
{
    return _worldSize;
}
//-----------------------------------------------------------------------
void PUParticle3DForceFieldAffector::setWorldSize(const Vec3& worldSize)
{
    _worldSize = worldSize;
    if (_suppressGeneration)
        return;

    _forceField.setWorldSize(worldSize);
}
//-----------------------------------------------------------------------
bool PUParticle3DForceFieldAffector::getIgnoreNegativeX(void) const
{
    return _ignoreNegativeX;
}
//-----------------------------------------------------------------------
void PUParticle3DForceFieldAffector::setIgnoreNegativeX(bool ignoreNegativeX)
{
    _ignoreNegativeX = ignoreNegativeX;
}
//-----------------------------------------------------------------------
bool PUParticle3DForceFieldAffector::getIgnoreNegativeY(void) const
{
    return _ignoreNegativeY;
}
//-----------------------------------------------------------------------
void PUParticle3DForceFieldAffector::setIgnoreNegativeY(bool ignoreNegativeY)
{
    _ignoreNegativeY = ignoreNegativeY;
}
//-----------------------------------------------------------------------
bool PUParticle3DForceFieldAffector::getIgnoreNegativeZ(void) const
{
    return _ignoreNegativeZ;
}
//-----------------------------------------------------------------------
void PUParticle3DForceFieldAffector::setIgnoreNegativeZ(bool ignoreNegativeZ)
{
    _ignoreNegativeZ = ignoreNegativeZ;
}
//-----------------------------------------------------------------------
float PUParticle3DForceFieldAffector::getMovementFrequency(void) const
{
    return _movementFrequency;
}
//-----------------------------------------------------------------------
void PUParticle3DForceFieldAffector::setMovementFrequency(float movementFrequency)
{
    _movementFrequency = movementFrequency;
    _movementSet = (movementFrequency > 0.0f);
}
//-----------------------------------------------------------------------
const Vec3& PUParticle3DForceFieldAffector::getMovement(void) const
{
    return _movement;
}
//-----------------------------------------------------------------------
void PUParticle3DForceFieldAffector::setMovement(const Vec3& movement)
{
    _movement = movement;
    _movementSet = (movement != Vec3::ZERO);
}
//-----------------------------------------------------------------------
void PUParticle3DForceFieldAffector::suppressGeneration(bool suppress)
{
    _suppressGeneration = suppress;
}

void PUParticle3DForceFieldAffector::updatePUAffector( PUParticle3D *particle, float deltaTime )
{
    //for (auto iter : _particleSystem->getParticles())
    {
        //PUParticle3D *particle = iter;
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

void PUParticle3DForceFieldAffector::notifyStart()
{
    _movementFrequencyCount = 0.0f;
}

void PUParticle3DForceFieldAffector::preUpdateAffector( float deltaTime )
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

void PUParticle3DForceFieldAffector::prepare()
{
    //if (particleTechnique->getParentSystem())
    {
        // Forcefield position is same position as particle system position
        _forceField.initialise(_forceFieldType,
            // _particleSystem->getDerivedPosition()
            getDerivedPosition(),
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

PUParticle3DForceFieldAffector* PUParticle3DForceFieldAffector::create()
{
    auto pffa = new (std::nothrow) PUParticle3DForceFieldAffector();
    pffa->autorelease();
    return pffa;
}

NS_CC_END