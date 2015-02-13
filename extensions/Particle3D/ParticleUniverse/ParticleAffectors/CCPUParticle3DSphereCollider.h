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


#ifndef __CC_PU_PARTICLE_3D_SPHERE_COLLIDER_H__
#define __CC_PU_PARTICLE_3D_SPHERE_COLLIDER_H__

#include "CCPUParticle3DBaseCollider.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticle3DSphere.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

class  CC_DLL PUParticle3DSphereCollider : public PUParticle3DBaseCollider
{
public:
    // Constants
    static const float DEFAULT_RADIUS;

    static PUParticle3DSphereCollider* create();

    virtual void preUpdateAffector(float deltaTime) override;
    virtual void updatePUAffector(PUParticle3D *particle, float deltaTime) override;

    /** Returns the radius of the sphere
    */
    const float getRadius(void) const;

    /** Sets the radius of the sphere
    */
    void setRadius(const float radius);

    /** Returns indication whether the collision is inside or outside of the box
    @remarks
        If value is true, the collision is inside of the box.
    */
    bool isInnerCollision(void) const;

    /** Set indication whether the collision is inside or outside of the box
    @remarks
        If value is set to true, the collision is inside of the box.
    */
    void setInnerCollision(bool innerCollision);

    /** 
    */
    void calculateDirectionAfterCollision(PUParticle3D* particle, Vec3 distance, float distanceLength);

CC_CONSTRUCTOR_ACCESS:	
    PUParticle3DSphereCollider(void);
    virtual ~PUParticle3DSphereCollider(void);

protected:
    float _radius;
    PUSphere _sphere;
    Vec3 _predictedPosition;
    bool _innerCollision;
};
NS_CC_END

#endif