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


#ifndef __CC_PU_PARTICLE_3D_CIRCLE_EMITTER_H__
#define __CC_PU_PARTICLE_3D_CIRCLE_EMITTER_H__

#include "extensions/Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DEmitter.h"

NS_CC_BEGIN

class  CC_DLL PUParticle3DCircleEmitter : public PUParticle3DEmitter
{
public:
    // Constants
    static const float DEFAULT_RADIUS;
    static const float DEFAULT_STEP;
    static const float DEFAULT_ANGLE;
    static const bool DEFAULT_RANDOM;
    static const Vec3 DEFAULT_NORMAL;

    static PUParticle3DCircleEmitter* create();

    /** 
    */
    const float getRadius(void) const;
    void setRadius(const float radius);

    /** 
    */
    const float getCircleAngle(void) const;
    void setCircleAngle(const float circleAngle);

    /** 
    */
    const float getStep(void) const;
    void setStep(const float step);

    /** 
    */
    const bool isRandom(void) const;
    void setRandom(const bool random);

    /* 
    */ 
    const Quaternion& getOrientation(void) const;
    const Vec3& getNormal(void) const;
    void setNormal(const Vec3 &normal); 

    /** See ParticleEmiter
    */
    virtual void notifyStart(void) override;

CC_CONSTRUCTOR_ACCESS:
    PUParticle3DCircleEmitter(void);
    virtual ~PUParticle3DCircleEmitter(void) {};

protected:

    /** Determine a particle position on the circle.
    */
    virtual void initParticlePosition(PUParticle3D* particle);

    /** Determine the particle direction.
    */
    virtual void initParticleDirection(PUParticle3D* particle);

    Quaternion getRotationTo(const Vec3 &src, const Vec3& dest,
        const Vec3& fallbackAxis = Vec3::ZERO) const;

protected:
    float _radius;
    float _circleAngle;
    float _originalCircleAngle;
    float _step;
    float _x;
    float _z;
    bool _random;
    Quaternion _orientation;
    Vec3 _normal;


};
NS_CC_END

#endif