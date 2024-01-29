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


#ifndef __CC_PU_PARTICLE_3D_VORTEX_AFFECTOR_H__
#define __CC_PU_PARTICLE_3D_VORTEX_AFFECTOR_H__

#include "extensions/Particle3D/PU/CCPUAffector.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttribute.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

class  CC_DLL PUVortexAffector : public PUAffector
{
public:
    // Constants
    static const Vec3 DEFAULT_ROTATION_VECTOR;
    static const float DEFAULT_ROTATION_SPEED;

    static PUVortexAffector* create();

    virtual void preUpdateAffector(float deltaTime) override;
    virtual void updatePUAffector(PUParticle3D *particle, float deltaTime) override;
    /** 
    */
    const Vec3& getRotationVector() const;

    /** 
    */
    void setRotationVector(const Vec3& rotationVector);

    /** 
    */
    PUDynamicAttribute* getRotationSpeed() const;

    /** 
    */
    void setRotationSpeed(PUDynamicAttribute* dynRotationSpeed);

    virtual void copyAttributesTo (PUAffector* affector) override;

CC_CONSTRUCTOR_ACCESS:	      
    PUVortexAffector();
    virtual ~PUVortexAffector();

protected:

    /** 
    */
    float calculateRotationSpeed();

protected:
    Vec3 _rotationVector;
    Quaternion _rotation;
    PUDynamicAttribute* _dynRotationSpeed;
    PUDynamicAttributeHelper _dynamicAttributeHelper;
};
NS_CC_END

#endif
