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

#ifndef __CC_PU_PARTICLE_3D_FORCE_FIELD_H__
#define __CC_PU_PARTICLE_3D_FORCE_FIELD_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "CCPUNoise.h"

NS_CC_BEGIN

/** Pure virtual ForceFieldCalculationFactory
*/
class  PUForceFieldCalculationFactory
{
public:
    // Const
    static const Vec3 DEFAULT_WORLDSIZE;

    PUForceFieldCalculationFactory() : 
        _octaves(2),
        _frequency(1.0f),
        _amplitude(1.0f),
        _persistence(1.0f),
        _worldSize(DEFAULT_WORLDSIZE)
    {
    }
    virtual ~PUForceFieldCalculationFactory(){};

    /** Generates the force field
    @remarks
        This function takes several arguments. 
        - forceFieldSize defines the internal dimensions of the force field. 
        - octaves, frequency, amplitude and persistence define the noise that is being generated.
        - worldSize defines the dimensions in the real world (scene).
    */
    virtual void generate(unsigned int forceFieldSize, 
        unsigned short octaves, 
        double frequency, 
        double amplitude, 
        double persistence, 
        const Vec3& worldSize) = 0;

    /** Determine force, based on the position of a particle.
    #remarks
        The position is the position of a particle. The argument 'delta' defines the radius around the position that contributes to the 
        calculation of the force.
    */
    virtual void determineForce(const Vec3& position, Vec3& force, float delta) = 0;

    /** Default Getters/Setters
    */
    virtual unsigned short getOctaves() const;
    virtual void setOctaves(unsigned short octaves);
    virtual double getFrequency() const;
    virtual void setFrequency(double frequency);
    virtual double getAmplitude() const;
    virtual void setAmplitude(double amplitude);
    virtual double getPersistence() const;
    virtual void setPersistence(double persistence);
    virtual unsigned int getForceFieldSize() const;
    virtual void setForceFieldSize(unsigned int forceFieldSize);
    virtual Vec3 getWorldSize() const;
    virtual void setWorldSize(const Vec3& worldSize);

protected:
    PUNoise3D _noise3D;
    unsigned short _octaves;
    double _frequency;
    double _amplitude;
    double _persistence;
    Vec3 _mapScale;
    Vec3 _worldSize;
    Vec3 _mappedPosition;
};
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

/** Factory class to calculate forces in realtime
*/
class PURealTimeForceFieldCalculationFactory : public PUForceFieldCalculationFactory
{
public:
    PURealTimeForceFieldCalculationFactory() : PUForceFieldCalculationFactory() {};
    virtual ~PURealTimeForceFieldCalculationFactory(){};

    /** Override from ForceFieldCalculationFactory
    */
    virtual void generate(unsigned int forceFieldSize, 
        unsigned short octaves, 
        double frequency, 
        double amplitude, 
        double persistence, 
        const Vec3& worldSize);

    /** Override from ForceFieldCalculationFactory
    */
    virtual void determineForce(const Vec3& position, Vec3& force, float delta);
};
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------


/** Force Field Affector Class:
    This class defines a force field to affect the particle direction. The force field is based on 3D noise. The force can be calculated in
    realtime or based on a precreated 3D force field matrix, which essentially involves one lookup. To speed things up, the 3d matrix can be
    precreated in a separate thread (optionally).
*/
class PUForceField
{
    public:
        enum ForceFieldType
        {
            FF_REALTIME_CALC,
            FF_MATRIX_CALC
        };

        PUForceField();
        virtual ~PUForceField();

        /** Initialises a ForceField */
        virtual void initialise(ForceFieldType type,
            const Vec3& position,
            unsigned int forceFieldSize, 
            unsigned short octaves, 
            double frequency, 
            double amplitude, 
            double persistence, 
            const Vec3& worldSize);

        /** Initialises a ForceField */
        virtual void initialise(ForceFieldType type,
            unsigned int forceFieldSize, 
            unsigned short octaves, 
            double frequency, 
            double amplitude, 
            double persistence, 
            const Vec3& worldSize);

        /** Get/Set the base position of the force field */
        const Vec3& getForceFieldPositionBase() const;
        void setForceFieldPositionBase(const Vec3& position);

        /** Calculate the force, based on a certain position */
        void determineForce(const Vec3& position, Vec3& force, float delta);

        /** Getters/Setters
        */
        virtual unsigned short getOctaves() const;
        virtual void setOctaves(unsigned short octaves);
        virtual double getFrequency() const;
        virtual void setFrequency(double frequency);
        virtual double getAmplitude() const;
        virtual void setAmplitude(double amplitude);
        virtual double getPersistence() const;
        virtual void setPersistence(double persistence);
        virtual unsigned int getForceFieldSize() const;
        virtual void setForceFieldSize(unsigned int forceFieldSize);
        virtual Vec3 getWorldSize() const;
        virtual void setWorldSize(const Vec3& worldSize);
            
        /** Get/Set the Forcefield type
        */
        ForceFieldType getForceFieldType() const;
        void setForceFieldType(const ForceFieldType forceFieldType);

    protected:
        unsigned short _octaves;
        double _frequency;
        double _amplitude;
        double _persistence;
        Vec3 _worldSize;
        unsigned int _forceFieldSize;
        PUForceFieldCalculationFactory* _forceFieldCalculationFactory; // Internal factory that creates a certain force field type
        Vec3 _forceFieldPositionBase; // Position of the force field
        ForceFieldType _forceFieldType;

        /** Get/Set/Create ForceFieldCalculationFactory */
        PUForceFieldCalculationFactory* getForceFieldCalculationFactory() const;
        void setForceFieldCalculationFactory(PUForceFieldCalculationFactory* forceFieldCalculationFactory);
        PUForceFieldCalculationFactory* createForceFieldCalculationFactory(ForceFieldType type);
};
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

NS_CC_END

#endif
