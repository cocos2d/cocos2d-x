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


#ifndef __CC_PARTICLE_3D_GEOMETRY_ROTATOR_H__
#define __CC_PARTICLE_3D_GEOMETRY_ROTATOR_H__

#include "3dparticle/CCParticle3DAffector.h"
#include "3dparticle/ParticleUniverse/CCParticle3DDynamicAttribute.h"

NS_CC_BEGIN
struct Particle3D;
class  Particle3DGeometryRotator : public Particle3DAffector
{
public:
    // Constants
    static const bool DEFAULT_USE_OWN;
    static const float DEFAULT_ROTATION_SPEED;
    static const Vec3 DEFAULT_ROTATION_AXIS;

    Particle3DGeometryRotator();
    virtual ~Particle3DGeometryRotator();

    virtual void updateAffector(Particle3D *particle, float deltaTime) override;
    /** @copydoc ParticleAffector::_initParticleForEmission */
    virtual void initParticleForEmission(Particle3D* particle) override;

    /** Returns the rotation speed. This is the speed controlled by the affector. Besides
        the default rotation speed, it is also possible to use the particles own rotation speed.
    */
    DynamicAttribute* getRotationSpeed(void) const;

    /** 
    */
    void setRotationSpeed(DynamicAttribute* dynRotationSpeed);

    /** Returns an indication whether the rotation speed is the same for all particles in this 
        particle technique, or whether the rotation speed of the particle itself is used.
    */
    bool useOwnRotationSpeed (void) const;

    /** Set the indication whether rotation speed of the particle itself is used.
    */
    void setUseOwnRotationSpeed (bool _useOwnRotationSpeed);

    /** 
    */
    const Vec3& getRotationAxis(void) const;

    /** 
    */
    void setRotationAxis(const Vec3& rotationAxis);

    /** 
    */
    void resetRotationAxis(void);

protected:

    /** Returns a rotation speed value, depending on the type of dynamic attribute.
    */
    float calculateRotationSpeed (Particle3D* particle);

protected:

    float _scaledRotationSpeed;
    bool _useOwnRotationSpeed;
    DynamicAttribute* _dynRotationSpeed;
    Quaternion _q;
    Vec3 _rotationAxis;
    bool _rotationAxisSet;

    /** Helper factory
    */
    DynamicAttributeHelper _dynamicAttributeHelper;
};
NS_CC_END

#endif