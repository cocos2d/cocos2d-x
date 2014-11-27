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


#ifndef __CC_PARTICLE_3D_SCALE_AFFECTOR_H__
#define __CC_PARTICLE_3D_SCALE_AFFECTOR_H__

#include "3dparticle/CCParticle3DAffector.h"
#include "3dparticle/ParticleUniverse/CCParticle3DDynamicAttribute.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

class  Particle3DScaleAffector : public Particle3DAffector
{
public:
    // Constants
    static const float DEFAULT_X_SCALE;
    static const float DEFAULT_Y_SCALE;
    static const float DEFAULT_Z_SCALE;
    static const float DEFAULT_XYZ_SCALE;

    Particle3DScaleAffector(void);
    virtual ~Particle3DScaleAffector(void);

    virtual void updateAffector(Particle3D *particle, float deltaTime) override;

    /** 
    */
    DynamicAttribute* getDynScaleX(void) const {return _dynScaleX;};
    void setDynScaleX(DynamicAttribute* dynScaleX);
    void resetDynScaleX(bool resetToDefault = true);

    /** 
    */
    DynamicAttribute* getDynScaleY(void) const {return _dynScaleY;};
    void setDynScaleY(DynamicAttribute* dynScaleY);
    void resetDynScaleY(bool resetToDefault = true);

    /** 
    */
    DynamicAttribute* getDynScaleZ(void) const {return _dynScaleZ;};
    void setDynScaleZ(DynamicAttribute* dynScaleZ);
    void resetDynScaleZ(bool resetToDefault = true);

    /** 
    */
    DynamicAttribute* getDynScaleXYZ(void) const {return _dynScaleXYZ;};
    void setDynScaleXYZ(DynamicAttribute* dynScaleXYZ);
    void resetDynScaleXYZ(bool resetToDefault = true);

    /** 
    */
    bool isSinceStartSystem(void) const {return _sinceStartSystem;};
    void setSinceStartSystem(bool sinceStartSystem){_sinceStartSystem = sinceStartSystem;};

protected:

    /** Returns the scale value for the dynamic Scale.
    */
    float calculateScale(DynamicAttribute* dynScale, Particle3D* particle);

protected:

    DynamicAttribute* _dynScaleX;
    DynamicAttribute* _dynScaleY;
    DynamicAttribute* _dynScaleZ;
    DynamicAttribute* _dynScaleXYZ;
    bool _dynScaleXSet;
    bool _dynScaleYSet;
    bool _dynScaleZSet;
    bool _dynScaleXYZSet;
    DynamicAttributeHelper _dynamicAttributeHelper;
    bool _sinceStartSystem;

    float _latestTimeElapsed;
};
NS_CC_END

#endif