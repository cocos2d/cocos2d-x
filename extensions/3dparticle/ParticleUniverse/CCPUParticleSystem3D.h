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

#ifndef __CC_PU_PARTICLE_SYSTEM_3D_H__
#define __CC_PU_PARTICLE_SYSTEM_3D_H__

#include "2d/CCNode.h"
#include "base/CCProtocols.h"
#include "math/CCMath.h"
#include "3dparticle/CCParticleSystem3D.h"
#include <vector>
#include <map>

NS_CC_BEGIN

/**
 * 3d particle system
 */
class PUParticle3DEmitter;
class PUParticle3DAffector;
class Particle3DRender;

struct PUParticle3D : public Particle3D
{
	static float DEFAULT_TTL;
	static float DEFAULT_MASS;

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
    /** zRotation is used to rotate the particle in 2D (around the Z-axis)
    @remarks
        There is no relation between zRotation and orientation.
        rotationSpeed in combination with orientation are used for 3D rotation of the particle, while
        zRotation means the rotation around the Z-axis. This type of rotation is typically used for 
        rotating textures. This also means that both types of rotation can be used together.
    */
    float zRotation; //radian

    /** The zRotationSpeed is used in combination with zRotation and defines tha actual rotationspeed
        in 2D. */
    float zRotationSpeed; //radian

    /*  Orientation of the particle.
    @remarks
        The orientation of the particle is only visible if the Particle Renderer - such as the Box renderer - 
        supports orientation.
    */
    Quaternion orientation;
    Quaternion originalOrientation;

    /** The rotation is used in combination with orientation. Because the rotation speed is part
        of the particle itself, it can be changed independently. */
    float rotationSpeed;
        /** Own width
    */
    float width;
        
    /** Own height
    */
    float height;

    /** Own depth
    */
    float depth;

    /** Radius of the particle, to be used for inter-particle collision and such.
    */
    float radius;

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
};

class PUParticleSystem3D : public ParticleSystem3D
{
public:

	static const float DEFAULT_WIDTH;
	static const float DEFAULT_HEIGHT;
	static const float DEFAULT_DEPTH;

    PUParticleSystem3D();
    virtual ~PUParticleSystem3D();
    
    virtual void update(float delta) override;
    
    /**
     * particle system play control
     */
    virtual void start() override;
    
    /**
     * stop particle
     */
    virtual void stop() override;
    
    /**
     * pause particle
     */
    virtual void pause() override;
    
    /**
     * resume particle
     */
    virtual void resume() override;

    /** Returns the velocity scale, defined in the particle system, but passed to the technique for convenience.
    */
    float getParticleSystemScaleVelocity() const;

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

protected:

	void prepared();
	void unPrepared();
	void preUpdator(float elapsedTime);
	void updator(float elapsedTime);
	void postUpdator(float elapsedTime);
	void emitParticles(float elapsedTime);
    
	inline bool isExpired(PUParticle3D* particle, float timeElapsed);

protected:
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
    
};

NS_CC_END

#endif
