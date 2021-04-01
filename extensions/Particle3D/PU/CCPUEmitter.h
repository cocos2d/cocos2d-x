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

#ifndef __CC_PU_PARTICLE_3D_EMITTER_H__
#define __CC_PU_PARTICLE_3D_EMITTER_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "extensions/Particle3D/CCParticle3DEmitter.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttribute.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include <vector>
#include <string>

NS_CC_BEGIN
struct PUParticle3D;
class PUParticleSystem3D;
/**
 * 3d particle emitter
 */
class CC_DLL PUEmitter : public Particle3DEmitter
{
    friend class PUParticleSystem3D;
public:

    // Default values
    static const bool DEFAULT_ENABLED;
    static const Vec3 DEFAULT_POSITION;
    static const bool DEFAULT_KEEP_LOCAL;
    static const Vec3 DEFAULT_DIRECTION;
    static const Quaternion DEFAULT_ORIENTATION;
    static const Quaternion DEFAULT_ORIENTATION_RANGE_START;
    static const Quaternion DEFAULT_ORIENTATION_RANGE_END;
    //static const Particle::ParticleType DEFAULT_EMITS;
    static const unsigned short DEFAULT_START_TEXTURE_COORDS;
    static const unsigned short DEFAULT_END_TEXTURE_COORDS;
    static const unsigned short DEFAULT_TEXTURE_COORDS;
    static const Vec4 DEFAULT_START_COLOUR_RANGE;
    static const Vec4 DEFAULT_END_COLOUR_RANGE;
    static const Vec4 DEFAULT_COLOUR;
    static const bool DEFAULT_AUTO_DIRECTION;
    static const bool DEFAULT_FORCE_EMISSION;
    static const float DEFAULT_EMISSION_RATE;
    static const float DEFAULT_TIME_TO_LIVE;
    static const float DEFAULT_MASS;
    static const float DEFAULT_VELOCITY;
    static const float DEFAULT_DURATION;
    static const float DEFAULT_REPEAT_DELAY;
    static const float DEFAULT_ANGLE;
    static const float DEFAULT_DIMENSIONS;
    static const float DEFAULT_WIDTH;
    static const float DEFAULT_HEIGHT;
    static const float DEFAULT_DEPTH;

    PUEmitter();
    virtual ~PUEmitter();
    
    virtual void notifyStart();
    virtual void notifyStop();
    virtual void notifyPause();
    virtual void notifyResume();
    virtual void notifyRescaled(const Vec3& scale);
    virtual void prepare();
    virtual void unPrepare();
    virtual void preUpdateEmitter(float deltaTime);
    virtual void updateEmitter(Particle3D *particle, float deltaTime) override;
    virtual void postUpdateEmitter(float deltaTime);
    virtual unsigned short calculateRequestedParticles(float timeElapsed);
    
    virtual void emit(int count) override;

    void setLocalPosition(const Vec3 &pos) { _position = pos; };
    const Vec3 getLocalPosition() const { return _position; };
        /** Calculate the derived position of the affector.
    @remarks
        Note, that in script, the position is set as localspace, while if the affector is
        emitted, its position is automatically transformed. This function always returns 
        the derived position.
    */
    const Vec3& getDerivedPosition();
    
    /** Enables or disables the emitter.
    */
    void setEnabled (bool enabled);

    bool isEnabled() const;

    bool isEmitterDone() const;

        /** Todo
    */
    const std::string& getEmitterType() const { return _emitterType; }
    void setEmitterType(const std::string& emitterType) {_emitterType = emitterType;};

    /** Todo
    */
    const std::string& getName() const { return _name; }
    void setName(const std::string& name) {_name = name;};

    /** Todo
    */
    PUDynamicAttribute* getDynAngle() const { return _dynAngle; }
    void setDynAngle(PUDynamicAttribute* dynAngle);

    /** Todo
    */
    PUDynamicAttribute* getDynEmissionRate() const { return _dynEmissionRate; }
    void setDynEmissionRate(PUDynamicAttribute* dynEmissionRate);

    /** Todo
    */
    PUDynamicAttribute* getDynTotalTimeToLive() const { return _dynTotalTimeToLive; }
    void setDynTotalTimeToLive(PUDynamicAttribute* dynTotalTimeToLive);

    /** Todo
    */
    PUDynamicAttribute* getDynParticleMass() const { return _dynParticleMass; }
    void setDynParticleMass(PUDynamicAttribute* dynParticleMass);

    /** Todo
    */
    PUDynamicAttribute* getDynVelocity() const { return _dynVelocity; }
    void setDynVelocity(PUDynamicAttribute* dynVelocity);

    /** Todo
    */
    PUDynamicAttribute* getDynDuration() const { return _dynDuration; }
    void setDynDuration(PUDynamicAttribute* dynDuration);
    void setDynDurationSet(bool durationSet);

    /** Todo
    */
    PUDynamicAttribute* getDynRepeatDelay() const { return _dynRepeatDelay; }
    void setDynRepeatDelay(PUDynamicAttribute* dynRepeatDelay);
    void setDynRepeatDelaySet(bool repeatDelaySet);

    /** Todo
    */
    PUDynamicAttribute* getDynParticleAllDimensions() const { return _dynParticleAllDimensions; }
    void setDynParticleAllDimensions(PUDynamicAttribute* dynParticleAllDimensions);
    void setDynParticleAllDimensionsSet(bool particleAllDimensionsSet);

    /** Todo
    */
    PUDynamicAttribute* getDynParticleWidth() const { return _dynParticleWidth; }
    void setDynParticleWidth(PUDynamicAttribute* dynParticleWidth);
    void setDynParticleWidthSet(bool particleWidthSet);

    /** Todo
    */
    PUDynamicAttribute* getDynParticleHeight() const { return _dynParticleHeight; }
    void setDynParticleHeight(PUDynamicAttribute* dynParticleHeight);
    void setDynParticleHeightSet(bool particleHeightSet);

    /** Todo
    */
    PUDynamicAttribute* getDynParticleDepth() const { return _dynParticleDepth; }
    void setDynParticleDepth(PUDynamicAttribute* dynParticleDepth);
    void setDynParticleDepthSet(bool particleDepthSet);

    ///** Todo
    //*/
    //ParticleType getEmitsType() const { return mEmitsType; }
    //void setEmitsType(ParticleType emitsType) {mEmitsType = emitsType;};

    /** Todo
    */
    const std::string& getEmitsName() const { return _emitsName; }
    void setEmitsName(const std::string& emitsName);
    PUParticle3D::ParticleType getEmitsType() const { return _emitsType; }
    void setEmitsType(PUParticle3D::ParticleType type) {_emitsType = type;};
    Ref* getEmitsEntityPtr() const;
    bool isMarkedForEmission() const {return _isMarkedForEmission;};
    void setMarkedForEmission(bool isMarked) {_isMarkedForEmission = isMarked;};

        /** Returns the base direction of the particle that is going to be emitted.
    */
    const Vec3& getParticleDirection();

    /** Returns the originally set particle direction. This value is not affected by affectors, angle, etc.
    */
    const Vec3& getOriginalParticleDirection() const;

    /** Returns the base orientation of the particle that is going to be emitted.
    */
    const Quaternion& getParticleOrientation() const;

    /** Set the orientation of the particle.
    */
    void setParticleOrientation(const Quaternion& orientation);

    /** Returns the start orientation of the particle that is going to be emitted.
    @remarks
        The orientation is generated random between mParticleOrientationRangeStart and mParticleOrientationRangeEnd.
    */
    const Quaternion& getParticleOrientationRangeStart() const;

    /** Set start orientation of the particle that is going to be emitted.
    @remarks
        The orientation is generated random between mParticleOrientationRangeStart and mParticleOrientationRangeEnd.
    */
    void setParticleOrientationRangeStart(const Quaternion& orientationRangeStart);

    /** Returns the end orientation of the particle that is going to be emitted.
    @remarks
        The orientation is generated random between mParticleOrientationRangeStart and mParticleOrientationRangeEnd.
    */
    const Quaternion& getParticleOrientationRangeEnd() const;

    /** Set end orientation of the particle that is going to be emitted.
    @remarks
        The orientation is generated random between mParticleOrientationRangeStart and mParticleOrientationRangeEnd.
    */
    void setParticleOrientationRangeEnd(const Quaternion& orientationRangeEnd);
            
    /** Sets the direction of the particle that the emitter is emitting.
    @remarks
        Don't confuse this with the emitters own direction.
    @param direction The base direction of emitted particles.
    */
    void setParticleDirection(const Vec3& direction);

    /** Todo
    */
    bool isAutoDirection() const;

    /** Todo
    */
    void setAutoDirection(bool autoDirection);

    /** Todo
    */
    bool isForceEmission() const;

    /** Todo
    */
    void setForceEmission(bool forceEmission);

        /** Get the colour of a particle that will be emitted.
    */
    const Vec4& getParticleColor() const;

    /** Set the colour of an emitted particle.
    */
    void setParticleColor(const Vec4& particleColour);

    /** Get the colour range start of an emitted particle.
    */
    const Vec4& getParticleColorRangeStart() const;

    /** Set the colour range start of an emitted particle. This is the lower value used to generate a random colour.
    */
    void setParticleColorRangeStart(const Vec4& particleColourRangeStart);

    /** Get the colour range end of an emitted particle.
    */
    const Vec4& getParticleColorRangeEnd() const;

    /** Set the colour range end of an emitted particle. This is the upper value used to generate a random colour.
    */
    void setParticleColorRangeEnd(const Vec4& particleColourRangeEnd);

    /** Get the texture coords of an emitted particle.
    */
    const unsigned short& getParticleTextureCoords() const;

    /** Set the texture coords of an emitted particle.
    */
    void setParticleTextureCoords(const unsigned short& particleTextureCoords);

    /** Get the texture coords range start  of an emitted particle.
    */
    const unsigned short& getParticleTextureCoordsRangeStart() const;

    /** Set the texture coords range start of an emitted particle. This is the lower value used to set a random texture coords.
    */
    void setParticleTextureCoordsRangeStart(const unsigned short& particleTextureCoordsRangeStart);
            
    /** Get the texture coords range end of an emitted particle.
    */
    const unsigned short& getParticleTextureCoordsRangeEnd() const;

    /** Set the texture coords range end of an emitted particle. This is the upper value used to set a random texture coords.
    */
    void setParticleTextureCoordsRangeEnd(const unsigned short& particleTextureCoordsRangeEnd);

    /** Todo
    */
    bool isKeepLocal() const;

    /** If this attribute is set to 'true', the particles are emitted relative to the emitter
    */
    void setKeepLocal(bool keepLocal);

    /** Transforms the particle position in a local position relative to the emitter
    */
    bool makeParticleLocal(PUParticle3D* particle);

    virtual PUEmitter* clone() = 0;
    virtual void copyAttributesTo (PUEmitter* emitter);

protected:

    /** Todo
    */
    virtual void initParticlePosition(PUParticle3D* particle);

    /**  Internal method for generating the particle direction.
    */
    virtual void initParticleDirection(PUParticle3D* particle);

    /**  Internal method for generating the particle orientation.
    */
    virtual void initParticleOrientation(PUParticle3D* particle);

    virtual void initParticleVelocity(PUParticle3D* particle);

    virtual void initParticleMass(PUParticle3D* particle);

    virtual void initParticleColor(PUParticle3D* particle);

    virtual void initParticleTextureCoords(PUParticle3D* particle);

    virtual float initParticleTimeToLive();

    virtual void initParticleDimensions(PUParticle3D* particle);

    virtual void initParticleForEmission(PUParticle3D* particle);

    /** Initialise some attributes that are time-based.
    */
    inline void initTimeBased();

        /**  Internal method for generating the angle.
    */
    void generateAngle(float &angle);
    
protected:

    Vec3 _position;

    Vec3 _latestPosition;
    Vec3 _latestPositionDiff;

    Vec3 _derivedPosition;
    /** Although the scale is on a Particle System level, the emitter can also be scaled.
    */
    Vec3 _emitterScale;

    // Type of the emitter
    std::string _emitterType;

    // Name of the emitter (optional)
    std::string _name;

    /** Direction (and speed) of the emitted particle
    @remarks
        Don't confuse the particle direction with the direction of the emitter itself. 
        The particleDirection is the direction of an emitted particle.
    */
    Vec3 _particleDirection;
            
    /** The original direction of the emitted particle
    @remarks
        Don't confuse this with the particles' originalDirection.
    */
    Vec3 _originalParticleDirection;

    /** Orientation of the particle as soon as it is emitted.
    @remarks
        This is only visible if a renderer is used that renders 3D particles.
    */
    Quaternion _particleOrientation;

    /** If set, the range generates a random orientation between start and end.
    */
    Quaternion _particleOrientationRangeStart;
    Quaternion _particleOrientationRangeEnd;
    bool _particleOrientationRangeSet;

    // Angle around direction which particles may be emitted
    PUDynamicAttribute* _dynAngle;

    // Rate of particle emission.
    PUDynamicAttribute* _dynEmissionRate;

    //// Identifies the type of particle this emitter emits (default is visual particle).
    //ParticleType mEmitsType;

    // Identifies the name of particle this emitter emits (default is visual particle, so there is no name)
    std::string _emitsName;

    /** Dynamic attribute used to generate the total time to live.
    */
    PUDynamicAttribute* _dynTotalTimeToLive;

    /** Dynamic attribute used to generate the mass of a particle.
    */
    PUDynamicAttribute* _dynParticleMass;

    /** Dynamic attribute used to generate the velocity of a particle.
    */
    PUDynamicAttribute* _dynVelocity;

    /** Dynamic attribute used to define the duration of the emitter.
    */
    PUDynamicAttribute* _dynDuration;

    /** Dynamic attribute used to define the repeat/delay of the emitter.
    */
    PUDynamicAttribute* _dynRepeatDelay;

    /** Dynamic attribute used to define the (own) dimensions of a particle.
    @remarks
        In the Particle Technique it is possible to set the default dimensions for all particles, but it
        is also possible to set the dimensions per particle. Note, that this only applies to visual particles,
        of course. This attribute is used to x, y and z dimensions with the value.
    */
    PUDynamicAttribute* _dynParticleAllDimensions;
    bool _dynParticleAllDimensionsSet;

    /** Dynamic attribute used to define the (own) width of a particle.
    @remarks
        In the Particle Technique it is possible to set the default width for all particles, but it
        is also possible to set the width per particle. Note, that this only applies to visual particles,
        of course.
    */
    PUDynamicAttribute* _dynParticleWidth;
    bool _dynParticleWidthSet;

    /** Dynamic attribute used to define the (own) height of a particle.
    @remarks
        In the Particle Technique it is possible to set the default height for all particles, but it
        is also possible to set the height per particle. Note, that this only applies to visual particles,
        of course.
    */
    PUDynamicAttribute* _dynParticleHeight;
    bool _dynParticleHeightSet;

    /** Dynamic attribute used to define the (own) depth of a particle.
    @remarks
        In the Particle Technique it is possible to set the default depth for all particles, but it
        is also possible to set the depth per particle. Note, that this only applies to visual particles,
        of course.
    */
    PUDynamicAttribute* _dynParticleDepth;
    bool _dynParticleDepthSet;

    /** Notional up vector, just used to speed up generation of variant directions.
    */
    Vec3 _upVector;

    /** Particles that are left to be emitted from the previous time.
    */
    float _remainder;

    ///** Helper factory
    //*/
    //DynamicAttributeFactory mDynamicAttributeFactory;

    /** Helper class
    */
    PUDynamicAttributeHelper _dynamicAttributeHelper;

    /** Duration remainder.
    */
    float _durationRemain;

    /** Indication to determine whether duration is set.
    */
    bool _dynDurationSet;

    /** Repeat/delay remainder.
    */
    float _repeatDelayRemain;

    /** Indication to determine whether repeat/delay is set.
    */
    bool _dynRepeatDelaySet;

    /** Auto direction means that the direction of a particle is not determined by the 
        direction vector that has been set, but the direction vector is generated based on
        the shape of the emitter. In most cases this means that the particle direction is
        perpendicular on the shape of the emitter.
    @remarks
        This attribute has only a meaning for certain emitters.
    */
    bool _autoDirection;

    /** In normal cases, emission is regulated by time. This prevents that too much particles are
        emitted at once, which causes a drop in the framerate. In some cases you just want to emit
        all particles immediately without any delay. Setting the 'mForceEmission' to true enables this.
        In that case, the emission rate defines the number of particles that are emitted immediately.
        If the emission rate is 100, the emitter emits 100 particles at once and then disables.
    */
    bool _forceEmission;

    /** Original value, used to set it back.
    */
    bool _originalForceEmission;

    /** If mForceEmission has been set to true and if all particles are emitted, the mForceEmissionExecuted
        is also set to true, preventing any further 'forced emission'.
    */
    bool _forceEmissionExecuted;

    /** Original value, used to set it back.
    */
    bool _originalForceEmissionExecuted;

    /** Colour that is assigned to an emitted particle.
    */
    Vec4 _particleColor;

    /** Used to randomize the colour of an emitted particle.
    */
    Vec4 _particleColorRangeStart;

    /** Used to randomize the colour of an emitted particle.
    */
    Vec4 _particleColorRangeEnd;

    /** Used to determine whether the colour range has been set.
    */
    bool _particleColorRangeSet;

    /** Determines whether particle positions should be kept local in relation to the emitter.
    */
    bool _keepLocal;

    /** Texture coords that is assigned to an emitted particle (only works if the renderer uses it)
    */
    unsigned short _particleTextureCoords;

    /** Used to randomize the texture coords of an emitted particle.
    */
    unsigned short _particleTextureCoordsRangeStart;
                
    /** Used to randomize the texture coords of an emitted particle.
    */
    unsigned short _particleTextureCoordsRangeEnd;

    /** Used to determine whether the texture coords range has been set.
    */
    bool _particleTextureCoordsRangeSet;

    bool _originEnabled;
    bool _originEnabledSet;

    PUParticle3D::ParticleType _emitsType;
    Ref *_emitsEntity;

    bool _isMarkedForEmission;
};

NS_CC_END

#endif
