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


#ifndef __CC_PARTICLE_3D_SPHERE_SURFACE_EMITTER_H__
#define __CC_PARTICLE_3D_SPHERE_SURFACE_EMITTER_H__

#include "3dparticle/CCParticle3DEmitter.h"

NS_CC_BEGIN

class  CC_DLL Particle3DSphereSurfaceEmitter : public Particle3DEmitter
{
public:
    // Constants
    static const float DEFAULT_RADIUS;

    static Particle3DSphereSurfaceEmitter* create();
    /** 
    */
    const float getRadius(void) const;
    void setRadius(const float radius);

    /** 
    */
    virtual void initParticlePosition(Particle3D* particle);

    /** 
    */
    virtual void initParticleDirection(Particle3D* particle);

CC_CONSTRUCTOR_ACCESS:
    Particle3DSphereSurfaceEmitter(void);
    virtual ~Particle3DSphereSurfaceEmitter(void) {};

protected:
    float _radius;
    Vec3 _randomVector;

};
NS_CC_END

#endif