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


#ifndef __CC_PU_PARTICLE_3D_FORCE_FIELD_AFFECTOR_H__
#define __CC_PU_PARTICLE_3D_FORCE_FIELD_AFFECTOR_H__

#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DAffector.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DForceField.h"

NS_CC_BEGIN

class  CC_DLL PUParticle3DForceFieldAffector : public PUParticle3DAffector
{
public:
    // Constants
    static const PUForceField::ForceFieldType DEFAULT_FORCEFIELD_TYPE;
    static const float DEFAULT_DELTA;
    static const float DEFAULT_FORCE;
    static const unsigned short DEFAULT_OCTAVES;
    static const double DEFAULT_FREQUENCY;
    static const double DEFAULT_AMPLITUDE;
    static const double DEFAULT_PERSISTENCE;
    static const unsigned int DEFAULT_FORCEFIELDSIZE;
    static const Vec3 DEFAULT_WORLDSIZE;
    static const Vec3 DEFAULT_MOVEMENT;
    static const float DEFAULT_MOVEMENT_FREQUENCY;

    static PUParticle3DForceFieldAffector* create();

    virtual void notifyStart() override;
    virtual void preUpdateAffector(float deltaTime) override;
    virtual void updatePUAffector(PUParticle3D *particle, float deltaTime) override;
    virtual void prepare() override;

    /** Get/Set Forcefield type
    */
    const PUForceField::ForceFieldType getForceFieldType(void) const;
    void setForceFieldType(const PUForceField::ForceFieldType forceFieldType);

    /** Get/Set Delta
    */
    float getDelta(void) const;
    void setDelta(float delta);

    /** Get/Set scale Force
    */
    float getScaleForce(void) const;
    void setScaleForce(float scaleForce);

    /** Get/Set scale Octaves
    */
    unsigned short getOctaves(void) const;
    void setOctaves(unsigned short octaves);

    /** Get/Set scale Frequency
    */
    double getFrequency(void) const;
    void setFrequency(double frequency);

    /** Get/Set scale Amplitude
    */
    double getAmplitude(void) const;
    void setAmplitude(double amplitude);

    /** Get/Set scale Persistence
    */
    double getPersistence(void) const;
    void setPersistence(double persistence);

    /** Get/Set scale ForceFieldSize
    */
    unsigned int getForceFieldSize(void) const;
    void setForceFieldSize(unsigned int forceFieldSize);

    /** Get/Set scale worldSize
    */
    Vec3 getWorldSize(void) const;
    void setWorldSize(const Vec3& worldSize);

    /** Get/Set scale flip attributes
    */
    bool getIgnoreNegativeX(void) const;
    void setIgnoreNegativeX(bool ignoreNegativeX);
    bool getIgnoreNegativeY(void) const;
    void setIgnoreNegativeY(bool ignoreNegativeY);
    bool getIgnoreNegativeZ(void) const;
    void setIgnoreNegativeZ(bool ignoreNegativeZ);

    /** Get/Set Movement
    @remarks
        The movement vector determines the position of the movement. This movement is a displacement of the particle position 
        mapped to the forcefield.
    */
    const Vec3& getMovement(void) const;
    void setMovement(const Vec3& movement);

    /** Get/Set Movement frequency
    */
    float getMovementFrequency(void) const;
    void setMovementFrequency(float movementFrequency);

    /** Suppress (re)generation of the forcefield everytime an attribute is changed.
    */
    void suppressGeneration(bool suppress);

CC_CONSTRUCTOR_ACCESS:
    PUParticle3DForceFieldAffector();
    ~PUParticle3DForceFieldAffector();

protected:

    PUForceField _forceField; // Local force field
    PUForceField::ForceFieldType _forceFieldType; // Type of force field
    float _delta; // Radius of particle position
    Vec3 _force; // Force value that is used to calculate the force and reused for all particles
    float _scaleForce; // Scaling factor used in calculation of the direction vector of the particle
    unsigned short _octaves; // Used in noise generation
    double _frequency; // Used in noise generation
    double _amplitude; // Used in noise generation
    double _persistence; // Used in noise generation
    unsigned int _forceFieldSize; // The real size of the force field (is a unit cube in case of a 'realtime' force field type
    Vec3 _worldSize; // Size of the force field in world coordinates (can be non-cubic)
    bool _prepared; // Determines whether the force field is generated
    bool _ignoreNegativeX; // X-force is never negative
    bool _ignoreNegativeY; // Y-force is never negative
    bool _ignoreNegativeZ; // Z-force is never negative
    Vec3 _movement; // The direction to which the forcefield moves
    bool _movementSet; // Is true if the movement is set
    float _movementFrequency; // Speed of movement
    float _movementFrequencyCount;
    Vec3 _displacement;
    Vec3 _basePosition;
    bool _suppressGeneration; // Prevents re-generation of the complete forcefield after a change.
};
NS_CC_END

#endif