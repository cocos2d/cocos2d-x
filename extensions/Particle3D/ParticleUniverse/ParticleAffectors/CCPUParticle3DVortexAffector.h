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


#ifndef __CC_PU_PARTICLE_3D_VORTEX_AFFECTOR_H__
#define __CC_PU_PARTICLE_3D_VORTEX_AFFECTOR_H__

#include "extensions/Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DAffector.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DDynamicAttribute.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

class  CC_DLL PUParticle3DVortexAffector : public PUParticle3DAffector
{
public:
    // Constants
    static const Vec3 DEFAULT_ROTATION_VECTOR;
    static const float DEFAULT_ROTATION_SPEED;

    static PUParticle3DVortexAffector* create();

    virtual void preUpdateAffector(float deltaTime) override;
    virtual void updatePUAffector(PUParticle3D *particle, float deltaTime) override;
    /** 
    */
    const Vec3& getRotationVector(void) const;

    /** 
    */
    void setRotationVector(const Vec3& rotationVector);

    /** 
    */
    PUDynamicAttribute* getRotationSpeed(void) const;

    /** 
    */
    void setRotationSpeed(PUDynamicAttribute* dynRotationSpeed);

CC_CONSTRUCTOR_ACCESS:	      
    PUParticle3DVortexAffector(void);
    virtual ~PUParticle3DVortexAffector(void);

protected:

    /** 
    */
    float calculateRotationSpeed(void);

protected:
    Vec3 _rotationVector;
    Quaternion _rotation;
    PUDynamicAttribute* _dynRotationSpeed;
    PUDynamicAttributeHelper _dynamicAttributeHelper;
};
NS_CC_END

#endif