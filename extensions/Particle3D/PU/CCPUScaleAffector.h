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


#ifndef __CC_PU_PARTICLE_3D_SCALE_AFFECTOR_H__
#define __CC_PU_PARTICLE_3D_SCALE_AFFECTOR_H__

#include "extensions/Particle3D/PU/CCPUAffector.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttribute.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

class  CC_DLL PUScaleAffector : public PUAffector
{
public:
    // Constants
    static const float DEFAULT_X_SCALE;
    static const float DEFAULT_Y_SCALE;
    static const float DEFAULT_Z_SCALE;
    static const float DEFAULT_XYZ_SCALE;

    static PUScaleAffector* create();

    virtual void updatePUAffector(PUParticle3D *particle, float deltaTime) override;

    /** 
    */
    PUDynamicAttribute* getDynScaleX(void) const {return _dynScaleX;};
    void setDynScaleX(PUDynamicAttribute* dynScaleX);
    void resetDynScaleX(bool resetToDefault = true);

    /** 
    */
    PUDynamicAttribute* getDynScaleY(void) const {return _dynScaleY;};
    void setDynScaleY(PUDynamicAttribute* dynScaleY);
    void resetDynScaleY(bool resetToDefault = true);

    /** 
    */
    PUDynamicAttribute* getDynScaleZ(void) const {return _dynScaleZ;};
    void setDynScaleZ(PUDynamicAttribute* dynScaleZ);
    void resetDynScaleZ(bool resetToDefault = true);

    /** 
    */
    PUDynamicAttribute* getDynScaleXYZ(void) const {return _dynScaleXYZ;};
    void setDynScaleXYZ(PUDynamicAttribute* dynScaleXYZ);
    void resetDynScaleXYZ(bool resetToDefault = true);

    /** 
    */
    bool isSinceStartSystem(void) const {return _sinceStartSystem;};
    void setSinceStartSystem(bool sinceStartSystem){_sinceStartSystem = sinceStartSystem;};

    virtual void copyAttributesTo (PUAffector* affector) override;

CC_CONSTRUCTOR_ACCESS:
    PUScaleAffector(void);
    virtual ~PUScaleAffector(void);

protected:

    /** Returns the scale value for the dynamic Scale.
    */
    float calculateScale(PUDynamicAttribute* dynScale, PUParticle3D* particle);

protected:

    PUDynamicAttribute* _dynScaleX;
    PUDynamicAttribute* _dynScaleY;
    PUDynamicAttribute* _dynScaleZ;
    PUDynamicAttribute* _dynScaleXYZ;
    bool _dynScaleXSet;
    bool _dynScaleYSet;
    bool _dynScaleZSet;
    bool _dynScaleXYZSet;
    PUDynamicAttributeHelper _dynamicAttributeHelper;
    bool _sinceStartSystem;

    float _latestTimeElapsed;
};
NS_CC_END

#endif