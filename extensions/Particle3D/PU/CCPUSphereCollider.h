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


#ifndef __CC_PU_PARTICLE_3D_SPHERE_COLLIDER_H__
#define __CC_PU_PARTICLE_3D_SPHERE_COLLIDER_H__

#include "CCPUBaseCollider.h"
#include "extensions/Particle3D/PU/CCPUSphere.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

class  CC_DLL PUSphereCollider : public PUBaseCollider
{
public:
    // Constants
    static const float DEFAULT_RADIUS;

    static PUSphereCollider* create();

    virtual void preUpdateAffector(float deltaTime) override;
    virtual void updatePUAffector(PUParticle3D *particle, float deltaTime) override;

    /** Returns the radius of the sphere
    */
    float getRadius() const;

    /** Sets the radius of the sphere
    */
    void setRadius(const float radius);

    /** Returns indication whether the collision is inside or outside of the box
    @remarks
        If value is true, the collision is inside of the box.
    */
    bool isInnerCollision() const;

    /** Set indication whether the collision is inside or outside of the box
    @remarks
        If value is set to true, the collision is inside of the box.
    */
    void setInnerCollision(bool innerCollision);

    /** 
    */
    void calculateDirectionAfterCollision(PUParticle3D* particle, Vec3 distance, float distanceLength);

    virtual void copyAttributesTo (PUAffector* affector) override;

CC_CONSTRUCTOR_ACCESS:	
    PUSphereCollider();
    virtual ~PUSphereCollider();

protected:
    float _radius;
    PUSphere _sphere;
    Vec3 _predictedPosition;
    bool _innerCollision;
};
NS_CC_END

#endif