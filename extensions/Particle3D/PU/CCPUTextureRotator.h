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


#ifndef __CC_PU_PARTICLE_3D_TEXTURE_ROTATOR_H__
#define __CC_PU_PARTICLE_3D_TEXTURE_ROTATOR_H__

#include "extensions/Particle3D/PU/CCPUAffector.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttribute.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

class  CC_DLL PUTextureRotator : public PUAffector
{
public:
    // Constants
    static const bool DEFAULT_USE_OWN_SPEED;
    static const float DEFAULT_ROTATION_SPEED;
    static const float DEFAULT_ROTATION;

    static PUTextureRotator* create();

    virtual void updatePUAffector(PUParticle3D *particle, float deltaTime) override;

    /** Returns an indication whether the 2D rotation speed is the same for all particles in this 
        particle technique, or whether the 2D rotation speed of the particle itself is used.
    */
    bool useOwnRotationSpeed (void) const;

    /** Set the indication whether the 2D rotation speed of the particle itself is used.
    */
    void setUseOwnRotationSpeed (bool useOwnRotationSpeed);

    /** Returns the rotation speed. This is the speed controlled by the affector.
    */
    PUDynamicAttribute* getRotationSpeed(void) const;

    /** 
    */
    void setRotationSpeed(PUDynamicAttribute* dynRotationSpeed);

    /** Returns the rotation defined in the affector.
    */
    PUDynamicAttribute* getRotation(void) const;

    /** 
    */
    void setRotation(PUDynamicAttribute* dynRotation);

    /** Returns a rotation set in the affector, depending on the type of dynamic attribute.
    */
    float calculateRotation (void);

    /** Returns a rotation speed value, depending on the type of dynamic attribute.
    */
    float calculateRotationSpeed (PUParticle3D* particle);

    /** @copydoc ParticleAffector::_initParticleForEmission */
    virtual void initParticleForEmission(PUParticle3D* particle) override;

    virtual void copyAttributesTo (PUAffector* affector) override;

CC_CONSTRUCTOR_ACCESS:	
    PUTextureRotator(void);
    virtual ~PUTextureRotator(void);

protected:
    bool _useOwnRotationSpeed;
    float _scaledRotationSpeed;
    float _twoPiRad;
    PUDynamicAttribute* _dynRotation;
    PUDynamicAttribute* _dynRotationSpeed;

    /** Helper factory
    */
    PUDynamicAttributeHelper _dynamicAttributeHelper;
};
NS_CC_END

#endif