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

#include "CCPUForceField.h"

NS_CC_BEGIN

const Vec3 PUForceFieldCalculationFactory::DEFAULT_WORLDSIZE = Vec3(500.0f, 500.0f, 500.0f);

//-----------------------------------------------------------------------
unsigned short PUForceFieldCalculationFactory::getOctaves(void) const
{
    return _octaves;
}
//-----------------------------------------------------------------------
void PUForceFieldCalculationFactory::setOctaves(unsigned short octaves)
{
    _octaves = octaves;
    generate(getForceFieldSize(), _octaves, _frequency, _amplitude, _persistence, _worldSize);
}
//-----------------------------------------------------------------------
double PUForceFieldCalculationFactory::getFrequency(void) const
{
    return _frequency;
}
//-----------------------------------------------------------------------
void PUForceFieldCalculationFactory::setFrequency(double frequency)
{
    _frequency = frequency;
    generate(getForceFieldSize(), _octaves, _frequency, _amplitude, _persistence, _worldSize);
}
//-----------------------------------------------------------------------
double PUForceFieldCalculationFactory::getAmplitude(void) const
{
    return _amplitude;
}
//-----------------------------------------------------------------------
void PUForceFieldCalculationFactory::setAmplitude(double amplitude)
{
    _amplitude = amplitude;
    generate(getForceFieldSize(), _octaves, _frequency, _amplitude, _persistence, _worldSize);
}
//-----------------------------------------------------------------------
double PUForceFieldCalculationFactory::getPersistence(void) const
{
    return _persistence;
}
//-----------------------------------------------------------------------
void PUForceFieldCalculationFactory::setPersistence(double persistence)
{
    _persistence = persistence;
    generate(getForceFieldSize(), _octaves, _frequency, _amplitude, _persistence, _worldSize);
}
//-----------------------------------------------------------------------
unsigned int PUForceFieldCalculationFactory::getForceFieldSize(void) const
{
    return 1; // Return default cubic size
}
//-----------------------------------------------------------------------
void PUForceFieldCalculationFactory::setForceFieldSize(unsigned int forceFieldSize)
{
    // The forcefield cannot be zero
    if (forceFieldSize == 0)
        return;

    generate(forceFieldSize, _octaves, _frequency, _amplitude, _persistence, _worldSize);
}
//-----------------------------------------------------------------------
Vec3 PUForceFieldCalculationFactory::getWorldSize(void) const
{
    return _worldSize;
}
//-----------------------------------------------------------------------
void PUForceFieldCalculationFactory::setWorldSize(const Vec3& worldSize)
{
    // The worldsize cannot be zero
    if (worldSize == Vec3::ZERO)
        return;

    _worldSize = worldSize;
    generate(getForceFieldSize(), _octaves, _frequency, _amplitude, _persistence, _worldSize);
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
void PURealTimeForceFieldCalculationFactory::generate(unsigned int forceFieldSize, 
                                                    unsigned short octaves, 
                                                    double frequency, 
                                                    double amplitude, 
                                                    double persistence, 
                                                    const Vec3& worldSize)
{
    _octaves = octaves;
    _frequency = frequency;
    _amplitude = amplitude;
    _persistence = persistence;
    _worldSize = worldSize;
    _noise3D.initialise(octaves, frequency, amplitude, persistence);

    if (worldSize != Vec3::ZERO)
    {
        _mapScale.x = 1.0f / worldSize.x; // Remark: forceFieldSize is not used, because it is a unit cube
        _mapScale.y = 1.0f / worldSize.y;
        _mapScale.z = 1.0f / worldSize.z;
    }
}
//-----------------------------------------------------------------------
void PURealTimeForceFieldCalculationFactory::determineForce(const Vec3& position, Vec3& force, float delta)
{
    _mappedPosition.x = _mapScale.x * position.x;
    _mappedPosition.y = _mapScale.y * position.y;
    _mappedPosition.z = _mapScale.z * position.z;

    if (_mappedPosition.x < 0.0f || _mappedPosition.x > 1.0f ||
        _mappedPosition.y < 0.0f || _mappedPosition.y > 1.0f ||
        _mappedPosition.z < 0.0f || _mappedPosition.z > 1.0f)
    {
        // Position is outside the forcefield (outside the unit cube)
        return;
    }

    force.x = (float)(_noise3D.noise(_mappedPosition.x + delta, _mappedPosition.y, _mappedPosition.z) - 
        _noise3D.noise(_mappedPosition.x - delta, _mappedPosition.y, _mappedPosition.z));
    force.y = (float)(_noise3D.noise(_mappedPosition.x, _mappedPosition.y + delta, _mappedPosition.z) - 
        _noise3D.noise(_mappedPosition.x, _mappedPosition.y - delta, _mappedPosition.z));
    force.z = (float)(_noise3D.noise(_mappedPosition.x, _mappedPosition.y, _mappedPosition.z + delta) - 
        _noise3D.noise(_mappedPosition.x, _mappedPosition.y, _mappedPosition.z - delta));
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
PUForceField::PUForceField(void) :
    _octaves(2),
    _frequency(1.0f),
    _amplitude(1.0f),
    _persistence(1.0f),
    _worldSize(PUForceFieldCalculationFactory::DEFAULT_WORLDSIZE),
    _forceFieldSize(64),
    _forceFieldCalculationFactory(0),
    _forceFieldPositionBase(Vec3::ZERO),
    _forceFieldType(FF_REALTIME_CALC)
{
}
//-----------------------------------------------------------------------
PUForceField::~PUForceField(void)
{
    if (_forceFieldCalculationFactory)
    {
        delete _forceFieldCalculationFactory;
    }
}
//-----------------------------------------------------------------------
void PUForceField::initialise(ForceFieldType type,
                            const Vec3& position,
                            unsigned int forceFieldSize, 
                            unsigned short octaves, 
                            double frequency, 
                            double amplitude, 
                            double persistence, 
                            const Vec3& worldSize)

{
    // Initialise first
    initialise(type, forceFieldSize, octaves, frequency, amplitude, persistence, worldSize);

    // Store the base and max position of the forcefield.
    _forceFieldPositionBase = position;
    _forceFieldPositionBase.x -= 0.5f * worldSize.x;
    _forceFieldPositionBase.y -= 0.5f * worldSize.y;
    _forceFieldPositionBase.z -= 0.5f * worldSize.z;
}
//-----------------------------------------------------------------------
void PUForceField::initialise(ForceFieldType type,
                            unsigned int forceFieldSize, 
                            unsigned short octaves, 
                            double frequency, 
                            double amplitude, 
                            double persistence, 
                            const Vec3& worldSize)
{
    // Create a factory
    _forceFieldCalculationFactory = createForceFieldCalculationFactory(type);

    // Create all necessary data for the force field
    _forceFieldCalculationFactory->generate(forceFieldSize, octaves, frequency, amplitude, persistence, worldSize);
}
//-----------------------------------------------------------------------
const Vec3& PUForceField::getForceFieldPositionBase(void) const
{
    return _forceFieldPositionBase;
}
//-----------------------------------------------------------------------
void PUForceField::setForceFieldPositionBase(const Vec3& position)
{
    _forceFieldPositionBase = position;
}
//-----------------------------------------------------------------------
void PUForceField::determineForce(const Vec3& position, Vec3& force, float delta)
{
    force.x = 0.0f;
    force.y = 0.0f;
    force.z = 0.0f;

    if (_forceFieldCalculationFactory)
    {
        _forceFieldCalculationFactory->determineForce(position - _forceFieldPositionBase, force, delta);
    }
}
//-----------------------------------------------------------------------
PUForceFieldCalculationFactory* PUForceField::getForceFieldCalculationFactory() const
{
    return _forceFieldCalculationFactory;
}
//-----------------------------------------------------------------------
void PUForceField::setForceFieldCalculationFactory(PUForceFieldCalculationFactory* forceFieldCalculationFactory)
{
    if (_forceFieldCalculationFactory)
    {
        delete _forceFieldCalculationFactory;
    }
    _forceFieldCalculationFactory = forceFieldCalculationFactory;
}
//-----------------------------------------------------------------------
PUForceFieldCalculationFactory* PUForceField::createForceFieldCalculationFactory(ForceFieldType type)
{
    _forceFieldType = type;
    if (type == FF_MATRIX_CALC)
    {
        // Use precreated matrix
        //setForceFieldCalculationFactory(new MatrixForceFieldCalculationFactory());
        return getForceFieldCalculationFactory();
    }
    else
    {
        // Use realtime calculation
        setForceFieldCalculationFactory(new (std::nothrow) PURealTimeForceFieldCalculationFactory());
        return getForceFieldCalculationFactory();
    }
}
//-----------------------------------------------------------------------
const PUForceField::ForceFieldType PUForceField::getForceFieldType(void) const
{
    return _forceFieldType;
}
//-----------------------------------------------------------------------
void PUForceField::setForceFieldType(const PUForceField::ForceFieldType forceFieldType)
{
    _forceFieldType = forceFieldType;
    if (_forceFieldCalculationFactory)
    {
        initialise(_forceFieldType, _forceFieldSize, _octaves, _frequency, _amplitude, _persistence, _worldSize);
    }
}
//-----------------------------------------------------------------------
unsigned short PUForceField::getOctaves(void) const
{
    return _octaves;
}
//-----------------------------------------------------------------------
void PUForceField::setOctaves(unsigned short octaves)
{
    _octaves = octaves;
    if (_forceFieldCalculationFactory)
    {
        _forceFieldCalculationFactory->setOctaves(octaves);
    }
}
//-----------------------------------------------------------------------
double PUForceField::getFrequency(void) const
{
    return _frequency;
}
//-----------------------------------------------------------------------
void PUForceField::setFrequency(double frequency)
{
    _frequency = frequency;
    if (_forceFieldCalculationFactory)
    {
        _forceFieldCalculationFactory->setFrequency(frequency);
    }
}
//-----------------------------------------------------------------------
double PUForceField::getAmplitude(void) const
{
    return _amplitude;
}
//-----------------------------------------------------------------------
void PUForceField::setAmplitude(double amplitude)
{
    _amplitude = amplitude;
    if (_forceFieldCalculationFactory)
    {
        _forceFieldCalculationFactory->setAmplitude(amplitude);
    }
}
//-----------------------------------------------------------------------
double PUForceField::getPersistence(void) const
{
    return _persistence;
}
//-----------------------------------------------------------------------
void PUForceField::setPersistence(double persistence)
{
    _persistence = persistence;
    if (_forceFieldCalculationFactory)
    {
        _forceFieldCalculationFactory->setPersistence(persistence);
    }
}
//-----------------------------------------------------------------------
unsigned int PUForceField::getForceFieldSize(void) const
{
    return _forceFieldSize;
}
//-----------------------------------------------------------------------
void PUForceField::setForceFieldSize(unsigned int forceFieldSize)
{
    _forceFieldSize = forceFieldSize;
    if (_forceFieldCalculationFactory)
    {
        _forceFieldCalculationFactory->setForceFieldSize(forceFieldSize);
    }
}
//-----------------------------------------------------------------------
Vec3 PUForceField::getWorldSize(void) const
{
    return _worldSize;
}
//-----------------------------------------------------------------------
void PUForceField::setWorldSize(const Vec3& worldSize)
{
    _worldSize = worldSize;
    if (_forceFieldCalculationFactory)
    {
        _forceFieldCalculationFactory->setWorldSize(worldSize);
    }
}

NS_CC_END
