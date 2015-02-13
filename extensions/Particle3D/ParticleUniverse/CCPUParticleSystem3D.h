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

#ifndef __CC_PU_PARTICLE_SYSTEM_3D_H__
#define __CC_PU_PARTICLE_SYSTEM_3D_H__

#include "2d/CCNode.h"
#include "base/CCProtocols.h"
#include "math/CCMath.h"
#include "extensions/Particle3D/CCParticleSystem3D.h"
#include <vector>
#include <map>

NS_CC_BEGIN

/**
 * 3d particle system
 */
class PUParticle3DEmitter;
class PUParticle3DAffector;
class Particle3DRender;

struct CC_DLL PUParticle3D : public Particle3D
{
    static float DEFAULT_TTL;
    static float DEFAULT_MASS;

    PUParticle3D();
        /** Enumeration which lists a number of reserved event flags. Although custom flags can be used to
        indicate that a certain condition occurs, the first number of flags may not be used as custom flags.
    */
    enum ReservedParticleEventFlags
    {
        PEF_EXPIRED = 1<<0,
        PEF_EMITTED = 1<<1,
        PEF_COLLIDED = 1<<2
    };

    PUParticle3DEmitter* parentEmitter;

    // Values that are assigned as soon as the particle is emitted (non-transformed)
    Vec3 positionInWorld;
    Vec3 originalPosition;
    Vec3 latestPosition;
    // Direction (and speed)
    Vec3 direction;
    Vec3 originalDirection;
    float originalDirectionLength; // Length of the direction that has been set
    float originalVelocity;
    float originalScaledDirectionLength; // Length of the direction after multiplication with the velocity

    /** The rotation axis is used in combination with orientation. Because the rotation axis is part
        of the particle itself, it can be changed independently. */
    Vec3 rotationAxis;
    /** Current and original colour */

    Vec4 originalColor;

    /** The zRotationSpeed is used in combination with zRotation and defines tha actual rotationspeed
        in 2D. */
    float zRotationSpeed; //radian

    Quaternion orientationInWorld;
    /*@remarks
        The orientation of the particle is only visible if the Particle Renderer - such as the Box renderer - 
        supports orientation.
    */
    Quaternion originalOrientation;


    /** The rotation is used in combination with orientation. Because the rotation speed is part
        of the particle itself, it can be changed independently. */
    float rotationSpeed;

    /** Radius of the particle, to be used for inter-particle collision and such.
    */
    float radius;

    float calculateVelocity() const;

    /** Set own dimensions
    */
    void setOwnDimensions(float newWidth, float newHeight, float newDepth);
    void calculateBoundingSphereRadius();

    void initForEmission();

    /** Does this particle have it's own dimensions? */
    bool ownDimensions;

        /** Sets the event flags.
    */
    inline void setEventFlags(unsigned int flags) {eventFlags = flags;}

    /** As setEventFlags, except the flags passed as parameters are appended to the
        existing flags on this object.
    */
    inline void addEventFlags(unsigned int flags) {eventFlags |= flags;}
            
    /** The flags passed as parameters are removed from the existing flags.
    */
    inline void removeEventFlags(unsigned int flags) {eventFlags &= ~flags;}
        
    /** Return the event flags.
    */
    inline unsigned int getEventFlags() const {return eventFlags;}

    /** Determines whether it has certain flags set.
    */
    inline bool hasEventFlags(unsigned int flags) const {return (eventFlags & flags) != 0;}

    unsigned int eventFlags;

    bool isFreezed(void) const
    {
        return freezed;
    }
    //-----------------------------------------------------------------------
    void setFreezed(bool fzd)
    {
        freezed = fzd;
    }
    bool freezed;

    // Time to live, number of seconds left of particles natural life
    float timeToLive;

    // Total Time to live, number of seconds of particles natural life
    float totalTimeToLive;

    // The timeFraction is calculated every update. It is used in other observers, affectors, etc. so it is
    // better to calculate it once at the Particle level.
    float timeFraction;

        /*  Mass of a particle.
    @remarks
        In case of simulations where mass of a particle is needed (i.e. exploding particles of different
        mass) this attribute can be used.
    */
    float mass;

    /** Animation attributes
    */
    float textureAnimationTimeStep;
    float textureAnimationTimeStepCount;
    unsigned short textureCoordsCurrent;
    bool textureAnimationDirectionUp;

    float depthInView;//depth in camera view
    float zRotation; //zRotation is used to rotate the particle in 2D (around the Z-axis)   (radian)
    float widthInWorld;
    float heightInWorld;
    float depthInWorld;
};

class CC_DLL PUParticleSystem3D : public ParticleSystem3D
{
public:

    static const float DEFAULT_WIDTH;
    static const float DEFAULT_HEIGHT;
    static const float DEFAULT_DEPTH;
    static const unsigned short DEFAULT_PARTICLE_QUOTA;
    static const float DEFAULT_MAX_VELOCITY;

    static PUParticleSystem3D* create();
    static PUParticleSystem3D* create(const std::string &filePath);
    static PUParticleSystem3D* create(const std::string &filePath, const std::string &materialPath);
    
    virtual void update(float delta) override;
    
    /**
     * particle system play control
     */
    virtual void startParticleSystem() override;
    
    /**
     * stop particle
     */
    virtual void stopParticleSystem() override;
    
    /**
     * pause particle
     */
    virtual void pauseParticleSystem() override;
    
    /**
     * resume particle
     */
    virtual void resumeParticleSystem() override;

    /** Returns the velocity scale, defined in the particle system, but passed to the technique for convenience.
    */
    float getParticleSystemScaleVelocity() const;

    void setParticleSystemScaleVelocity(float scaleVelocity) { _particleSystemScaleVelocity = scaleVelocity; }

    /** If the orientation of the particle system has been changed since the last update, the passed vector
        is rotated accordingly.
    */
    void rotationOffset(Vec3& pos);

    inline float getTimeElapsedSinceStart(void) const {return _timeElapsedSinceStart;};

    /** 
    */
    const float getDefaultWidth(void) const;
    void setDefaultWidth(const float width);

    /** 
    */
    const float getDefaultHeight(void) const;
    void setDefaultHeight(const float height);

    /** 
    */
    const float getDefaultDepth(void) const;
    void setDefaultDepth(const float depth);

    Vec3 getDerivedPosition();
    Quaternion getDerivedOrientation();
    Vec3 getDerivedScale();

    /** Return the maximum velocity a particle can have, even if the velocity of the particle has been set higher (either by 
        initialisation of the particle or by means of an affector).
    */
    float getMaxVelocity() const;

    /** Set the maximum velocity a particle can have.
    */
    void setMaxVelocity(float maxVelocity);

    void setMaterialName(const std::string &name) { _matName = name; };
    const std::string getMaterialName() const { return _matName; };

        /**
     * add particle affector
     */
    void addEmitter(PUParticle3DEmitter* emitter);
    
    virtual int getAliveParticleCount() const override;

CC_CONSTRUCTOR_ACCESS:
    PUParticleSystem3D();
    virtual ~PUParticleSystem3D();

protected:

    void prepared();
    void unPrepared();
    void preUpdator(float elapsedTime);
    void updator(float elapsedTime);
    void postUpdator(float elapsedTime);
    void emitParticles(float elapsedTime);
    
    inline bool isExpired(PUParticle3D* particle, float timeElapsed);

    bool initSystem(const std::string &filePath);
    static void convertToUnixStylePath(std::string &path);

protected:

    std::vector<PUParticle3DEmitter*> _emitters;

    bool _prepared;

    float _particleSystemScaleVelocity;
    float _timeElapsedSinceStart;
    /** Rotation offset between 2 updates.
    */
    Quaternion _rotationOffset;

    /** The rotation centre.
    */
    Vec3 _rotationCentre;
    

    /** Default width of each visual particle.
    */
    float _defaultWidth;

    /** Default height of each visual particle.
    */
    float _defaultHeight;

    /** Default depth of each visual particle.
    */
    float _defaultDepth;
    
        /** Attributes that limit the velocity of the particles in this technique.
    */
    float _maxVelocity;
    bool _maxVelocitySet;

    std::string _matName;
};

NS_CC_END

#endif
