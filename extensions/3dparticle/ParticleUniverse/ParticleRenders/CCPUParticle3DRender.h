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

#ifndef __CC_PU_PARTICLE_3D_RENDER_H__
#define __CC_PU_PARTICLE_3D_RENDER_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "3dparticle/CCParticle3DRender.h"
#include <vector>

NS_CC_BEGIN

// particle render for quad
class CC_DLL PUParticle3DQuadRender : public Particle3DQuadRender
{
public:

    enum Type
    {
        POINT,
        ORIENTED_SELF,
        PERPENDICULAR_COMMON,
    };

    enum Origin
    {
        TOP_LEFT,
        TOP_CENTER,
        TOP_RIGHT,
        CENTER_LEFT,
        CENTER,
        CENTER_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_CENTER,
        BOTTOM_RIGHT
    };

    static PUParticle3DQuadRender* create(const std::string& texFile = "");
    
    void setType(Type type) { _type = type; }
    Type getType() const { return _type; }
    void setOrigin(Origin origin) { _origin = origin; }
    Origin getOrigin() const { return _origin; }
    void setCommonDirection(const Vec3 &dir) { _commonDir = dir; }
    const Vec3& getCommonDirection() const { return _commonDir; }
    void setCommonUp(const Vec3 &up) { _commonUp = up; }
    const Vec3& getCommonUp() const { return _commonUp; }

    virtual void render(Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem) override;
    
CC_CONSTRUCTOR_ACCESS:
    PUParticle3DQuadRender();
    virtual ~PUParticle3DQuadRender();

protected:

    void getOriginOffset(int &offsetX, int &offsetY);

protected:
    Type _type;
    Origin _origin;
    Vec3 _commonDir;
    Vec3 _commonUp;
};

NS_CC_END

#endif
