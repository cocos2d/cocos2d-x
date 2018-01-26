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


#ifndef __CC_PU_PARTICLE_3D_INNER_PARTICLE_COLLIDER_H__
#define __CC_PU_PARTICLE_3D_INNER_PARTICLE_COLLIDER_H__

#include "CCPUBaseCollider.h"
#include "base/ccTypes.h"

NS_CC_BEGIN
struct PUParticle3D;
class  CC_DLL PUParticle3DInterParticleCollider : public PUBaseCollider
{
public:

    enum InterParticleCollisionResponse
    {
        IPCR_AVERAGE_VELOCITY,
        IPCR_ANGLE_BASED_VELOCITY
    };

    static PUParticle3DInterParticleCollider* create();

    // Constants
    static const float DEFAULT_ADJUSTMENT;
    static const InterParticleCollisionResponse DEFAULT_COLLISION_RESPONSE;

    virtual void prepare() override;
    virtual void unPrepare() override;
    virtual void updatePUAffector(PUParticle3D *particle, float deltaTime) override;

    /** Todo
    */
    float getAdjustment(void) const;

    /** Todo
    */
    void setAdjustment(float adjustment);

    /** Todo
    */
    InterParticleCollisionResponse getInterParticleCollisionResponse(void) const;

    /** Todo
    */
    void setInterParticleCollisionResponse(InterParticleCollisionResponse interParticleCollisionResponse);

    virtual void copyAttributesTo (PUAffector* affector) override;

CC_CONSTRUCTOR_ACCESS:
    PUParticle3DInterParticleCollider(void);
    virtual ~PUParticle3DInterParticleCollider(void);

protected:

    /** Todo
    */
    bool validateAndExecuteSphereCollision (PUParticle3D* particle1, PUParticle3D* particle2, float timeElapsed);
        
protected:

    float _adjustment;
    InterParticleCollisionResponse _interParticleCollisionResponse;

};
NS_CC_END

#endif