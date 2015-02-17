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


#ifndef __CC_PU_PARTICLE_3D_BOX_COLLIDER_H__
#define __CC_PU_PARTICLE_3D_BOX_COLLIDER_H__

#include "CCPUParticle3DBaseCollider.h"

NS_CC_BEGIN

class  CC_DLL PUParticle3DBoxCollider : public PUParticle3DBaseCollider
{
public:
    static const float DEFAULT_WIDTH;
    static const float DEFAULT_HEIGHT;
    static const float DEFAULT_DEPTH;

    static PUParticle3DBoxCollider* create();

    virtual void preUpdateAffector(float deltaTime) override;
    virtual void updatePUAffector(PUParticle3D *particle, float deltaTime) override;

    /** Returns the width of the box
    */
    const float getWidth() const;

    /** Sets the width of the box
    */
    void setWidth(const float width);

    /** Returns the height of the box
    */
    const float getHeight() const;

    /** Sets the height of the box
    */
    void setHeight(const float height);

    /** Returns the depth of the box
    */
    const float getDepth() const;

    /** Sets the depth of the box
    */
    void setDepth(const float depth);

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
    void calculateDirectionAfterCollision(PUParticle3D* particle);

CC_CONSTRUCTOR_ACCESS:
    PUParticle3DBoxCollider();
    virtual ~PUParticle3DBoxCollider();

protected:
        /** 
    */
    void calculateBounds ();
    /** 
    */
    bool isSmallestValue(float value, const Vec3& particlePosition);

protected:

    float _width;
    float _height;
    float _depth;
    float _xmin;
    float _xmax;
    float _ymin;
    float _ymax;
    float _zmin;
    float _zmax;
    AABB _box;
    Vec3 _predictedPosition;
    bool _innerCollision;
};
NS_CC_END

#endif