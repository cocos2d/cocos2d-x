/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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

#include "CCPUForceFieldAffector.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN
//-----------------------------------------------------------------------
// Constants
const PUForceField::ForceFieldType PUForceFieldAffector::DEFAULT_FORCEFIELD_TYPE = PUForceField::FF_REALTIME_CALC;
const float PUForceFieldAffector::DEFAULT_DELTA = 1.0f;
const float PUForceFieldAffector::DEFAULT_FORCE = 400.0f;
const unsigned short PUForceFieldAffector::DEFAULT_OCTAVES = 2;
const double PUForceFieldAffector::DEFAULT_FREQUENCY = 1.0f;
const double PUForceFieldAffector::DEFAULT_AMPLITUDE = 1.0f;
const double PUForceFieldAffector::DEFAULT_PERSISTENCE = 3.0f;
const unsigned int PUForceFieldAffector::DEFAULT_FORCEFIELDSIZE = 64;
const Vec3 PUForceFieldAffector::DEFAULT_WORLDSIZE(500.0f, 500.0f, 500.0f);
const Vec3 PUForceFieldAffector::DEFAULT_MOVEMENT(500.0f, 0.0f, 0.0f);
const float PUForceFieldAffector::DEFAULT_MOVEMENT_FREQUENCY = 5.0f;

//-----------------------------------------------------------------------
PUForceFieldAffector::PUForceFieldAffector() :
    _forceFieldType(PUForceField::FF_REALTIME_CALC),
    _delta(DEFAULT_DELTA),
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
    _suppressGeneration(false)
{
};
//-----------------------------------------------------------------------
PUForceFieldAffector::~PUForceFieldAffector()
{
};
//-----------------------------------------------------------------------
PUForceField::ForceFieldType PUForceFieldAffector::getForceFieldType() const
{
    return _forceFieldType;
}
//-----------------------------------------------------------------------
void PUForceFieldAffector::setForceFieldType(const PUForceField::ForceFieldType forceFieldType)
{
    _forceFieldType = forceFieldType;
    if (_suppressGeneration)
        return;

    _forceField.setForceFieldType(forceFieldType);
}
//-----------------------------------------------------------------------
float PUForceFieldAffector::getDelta(void) const
{
    return _delta;
}
//-----------------------------------------------------------------------
void PUForceFieldAffector::setDelta(float delta)
{
    _delta = delta;
}
//-----------------------------------------------------------------------
float PUForceFieldAffector::getScaleForce(void) const
{
    return _scaleForce;
}
//-----------------------------------------------------------------------
void PUForceFieldAffector::setScaleForce(float scaleForce)
{
    _scaleForce = scaleForce;
}
//-----------------------------------------------------------------------
unsigned short PUForceFieldAffector::getOctaves(void) const
{
    return _octaves;
}
//-----------------------------------------------------------------------
void PUForceFieldAffector::setOctaves(unsigned short octaves)
{
    _octaves = octaves;
    if (_suppressGeneration)
        return;

    _forceField.setOctaves(octaves);
}
//-----------------------------------------------------------------------
double PUForceFieldAffector::getFrequency(void) const
{
    return _frequency;
}
//-----------------------------------------------------------------------
void PUForceFieldAffector::setFrequency(double frequency)
{
    _frequency = frequency;
    if (_suppressGeneration)
        return;

    _forceField.setFrequency(frequency);
}
//-----------------------------------------------------------------------
double PUForceFieldAffector::getAmplitude(void) const
{
    return _amplitude;
}
//-----------------------------------------------------------------------
void PUForceFieldAffector::setAmplitude(double amplitude)
{
    _amplitude = amplitude;
    if (_suppressGeneration)
        return;

    _forceField.setAmplitude(amplitude);
}
//-----------------------------------------------------------------------
double PUForceFieldAffector::getPersistence(void) const
{
    return _persistence;
}
//-----------------------------------------------------------------------
void PUForceFieldAffector::setPersistence(double persistence)
{
    _persistence = persistence;
    if (_suppressGeneration)
        return;

    _forceField.setPersistence(persistence);
}
//-----------------------------------------------------------------------
unsigned int PUForceFieldAffector::getForceFieldSize(void) const
{
    return _forceFieldSize;
}
//-----------------------------------------------------------------------
void PUForceFieldAffector::setForceFieldSize(unsigned int forceFieldSize)
{
    _forceFieldSize = forceFieldSize;
    if (_suppressGeneration)
        return;

    _forceField.setForceFieldSize(forceFieldSize);
}
//-----------------------------------------------------------------------
Vec3 PUForceFieldAffector::getWorldSize(void) const
{
    return _worldSize;
}
//-----------------------------------------------------------------------
void PUForceFieldAffector::setWorldSize(const Vec3& worldSize)
{
    _worldSize = worldSize;
    if (_suppressGeneration)
        return;

    _forceField.setWorldSize(worldSize);
}
//-----------------------------------------------------------------------
bool PUForceFieldAffector::getIgnoreNegativeX(void) const
{
    return _ignoreNegativeX;
}
//-----------------------------------------------------------------------
void PUForceFieldAffector::setIgnoreNegativeX(bool ignoreNegativeX)
{
    _ignoreNegativeX = ignoreNegativeX;
}
//-----------------------------------------------------------------------
bool PUForceFieldAffector::getIgnoreNegativeY(void) const
{
    return _ignoreNegativeY;
}
//-----------------------------------------------------------------------
void PUForceFieldAffector::setIgnoreNegativeY(bool ignoreNegativeY)
{
    _ignoreNegativeY = ignoreNegativeY;
}
//-----------------------------------------------------------------------
bool PUForceFieldAffector::getIgnoreNegativeZ(void) const
{
    return _ignoreNegativeZ;
}
//-----------------------------------------------------------------------
void PUForceFieldAffector::setIgnoreNegativeZ(bool ignoreNegativeZ)
{
    _ignoreNegativeZ = ignoreNegativeZ;
}
//-----------------------------------------------------------------------
float PUForceFieldAffector::getMovementFrequency(void) const
{
    return _movementFrequency;
}
//-----------------------------------------------------------------------
void PUForceFieldAffector::setMovementFrequency(float movementFrequency)
{
    _movementFrequency = movementFrequency;
    _movementSet = (movementFrequency > 0.0f);
}
//-----------------------------------------------------------------------
const Vec3& PUForceFieldAffector::getMovement(void) const
{
    return _movement;
}
//-----------------------------------------------------------------------
void PUForceFieldAffector::setMovement(const Vec3& movement)
{
    _movement = movement;
    _movementSet = (movement != Vec3::ZERO);
}
//-----------------------------------------------------------------------
void PUForceFieldAffector::suppressGeneration(bool suppress)
{
    _suppressGeneration = suppress;
}

void PUForceFieldAffector::updatePUAffector( PUParticle3D *particle, float deltaTime )
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

void PUForceFieldAffector::notifyStart()
{
    _movementFrequencyCount = 0.0f;
}

void PUForceFieldAffector::preUpdateAffector( float deltaTime )
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

void PUForceFieldAffector::prepare()
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

PUForceFieldAffector* PUForceFieldAffector::create()
{
    auto pffa = new (std::nothrow) PUForceFieldAffector();
    pffa->autorelease();
    return pffa;
}

void PUForceFieldAffector::copyAttributesTo( PUAffector* affector )
{
    PUAffector::copyAttributesTo(affector);

    PUForceFieldAffector* forceFieldAffector = static_cast<PUForceFieldAffector*>(affector);
    forceFieldAffector->_forceFieldType = _forceFieldType;
    forceFieldAffector->_delta = _delta;
    forceFieldAffector->_scaleForce = _scaleForce;
    forceFieldAffector->_octaves = _octaves;
    forceFieldAffector->_frequency = _frequency;
    forceFieldAffector->_amplitude = _amplitude;
    forceFieldAffector->_persistence = _persistence;
    forceFieldAffector->_forceFieldSize = _forceFieldSize;
    forceFieldAffector->_worldSize = _worldSize;
    forceFieldAffector->_ignoreNegativeX = _ignoreNegativeX;
    forceFieldAffector->_ignoreNegativeY = _ignoreNegativeY;
    forceFieldAffector->_ignoreNegativeZ = _ignoreNegativeZ;
    forceFieldAffector->_movementSet = _movementSet;
    forceFieldAffector->_movementFrequency = _movementFrequency;
    forceFieldAffector->_movement = _movement;
}

NS_CC_END
