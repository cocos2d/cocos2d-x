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

#ifndef __CC_PARTICLE_3D_EMITTER_H__
#define __CC_PARTICLE_3D_EMITTER_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "3dparticle/ParticleUniverse/CCParticle3DDynamicAttribute.h"
#include <vector>

NS_CC_BEGIN
struct Particle3D;
class ParticleSystem3D;
/**
 * 3d particle emitter
 */
class Particle3DEmitter : public Ref
{
    friend class ParticleSystem3D;
public:
    Particle3DEmitter();
    virtual ~Particle3DEmitter();
    
    virtual void notifyStart();
    virtual void notifyStop();
    virtual void notifyPause();
    virtual void notifyResume();
    virtual void notifyRescaled(const Vec3& scale);
    virtual void prepare();
    virtual void unPrepare();
    virtual void preUpdateAffector(float deltaTime);
    virtual void updateEmitter(float deltaTime);
    virtual void postUpdateAffector(float deltaTime);
    virtual unsigned short calculateRequestedParticles(float timeElapsed);
    
    virtual void emit(int count);

        /** Calculate the derived position of the affector.
    @remarks
        Note, that in script, the position is set as localspace, while if the affector is
        emitted, its position is automatically transformed. This function always returns 
        the derived position.
    */
    const Vec3& getDerivedPosition();
    
    /** Enables or disables the emitter.
    */
    virtual void setEnabled (bool enabled);

protected:

    /** Todo
    */
    virtual void initParticlePosition(Particle3D* particle);

    /**  Internal method for generating the particle direction.
    */
    virtual void initParticleDirection(Particle3D* particle);

    /**  Internal method for generating the particle orientation.
    */
    virtual void initParticleOrientation(Particle3D* particle);

        /**  Internal method for generating the angle.
    */
    void generateAngle(float angle);

    
protected:
    ParticleSystem3D* _particleSystem;
    int _emitRate;
    /** Because the public attribute ´position?is sometimes used for both localspace and worldspace
        position, the mDerivedPosition attribute is introduced.
    */
    Vec3 _derivedPosition;
        /** Although the scale is on a Particle System level, the emitter can also be scaled.
    */
    Vec3 _emitterScale;

    Quaternion _particleOrientationRangeStart;
    Quaternion _particleOrientationRangeEnd;
    bool _ParticleOrientationRangeSet;

        /** Auto direction means that the direction of a particle is not determined by the 
        direction vector that has been set, but the direction vector is generated based on
        the shape of the emitter. In most cases this means that the particle direction is
        perpendicular on the shape of the emitter.
    @remarks
        This attribute has only a meaning for certain emitters.
    */
    bool _autoDirection;
    
        /** Direction (and speed) of the emitted particle
    @remarks
        Don't confuse the particle direction with the direction of the emitter itself. 
        The particleDirection is the direction of an emitted particle.
    */
    Vec3 _particleDirection;

        /** Notional up vector, just used to speed up generation of variant directions.
    */
    Vec3 _upVector;

    /** Orientation of the particle as soon as it is emitted.
    @remarks
        This is only visible if a renderer is used that renders 3D particles.
    */
    Quaternion _particleOrientation;

    DynamicAttribute* _dynAngle;

    /** Helper class
    */
    DynamicAttributeHelper _dynamicAttributeHelper;

    bool _isEnabled;

};

NS_CC_END

#endif
