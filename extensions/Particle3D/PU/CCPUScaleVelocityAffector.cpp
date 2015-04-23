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

#include "CCPUScaleVelocityAffector.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN
// Constants
const float PUScaleVelocityAffector::DEFAULT_VELOCITY_SCALE = 1.0f;

//-----------------------------------------------------------------------
PUScaleVelocityAffector::PUScaleVelocityAffector(void) : 
    PUAffector(),
    _sinceStartSystem(false),
    _stopAtFlip(false)
{
    _dynScaleVelocity = new (std::nothrow) PUDynamicAttributeFixed();
    (static_cast<PUDynamicAttributeFixed*>(_dynScaleVelocity))->setValue(DEFAULT_VELOCITY_SCALE);
}
//-----------------------------------------------------------------------
PUScaleVelocityAffector::~PUScaleVelocityAffector(void)
{
    if (_dynScaleVelocity)
    {
        CC_SAFE_DELETE(_dynScaleVelocity);
    }
}
//-----------------------------------------------------------------------
void PUScaleVelocityAffector::updatePUAffector( PUParticle3D *particle, float deltaTime )
{
    //for (auto iter : _particleSystem->getParticles())
    {
       // PUParticle3D *particle = iter;
        float ds = 0;
        if (_sinceStartSystem)
        {
            // If control points are used (curved type), the first value of each control point is seconds from the start of the system
            ds = deltaTime * _dynamicAttributeHelper.calculate(_dynScaleVelocity, (static_cast<PUParticleSystem3D *>(_particleSystem))->getTimeElapsedSinceStart());
        }
        else
        {
            // If control points are used (curved type), the first value of each control point is the fraction of the particle lifetime [0..1]
            ds = deltaTime * _dynamicAttributeHelper.calculate(_dynScaleVelocity, particle->timeFraction);
        }
        float length = particle->direction.length(); // Use length for a better delta direction value
        Vec3 calculated = particle->direction;
        calculated.x += ds * (particle->direction.x / length);
        calculated.y += ds * (particle->direction.y / length);
        calculated.z += ds * (particle->direction.z / length);

        if (_stopAtFlip)
        {
            if ((calculated.x > 0.0f && particle->direction.x < 0.0f) ||
                (calculated.y > 0.0f && particle->direction.y < 0.0f) ||
                (calculated.z > 0.0f && particle->direction.z < 0.0f) ||
                (calculated.x < 0.0f && particle->direction.x > 0.0f) ||
                (calculated.y < 0.0f && particle->direction.y > 0.0f) ||
                (calculated.z < 0.0f && particle->direction.z > 0.0f))
                return;
        }

        particle->direction = calculated;
    }
}

//-----------------------------------------------------------------------
void PUScaleVelocityAffector::setDynScaleVelocity(PUDynamicAttribute* dynScaleVelocity)
{
    if (_dynScaleVelocity)
        CC_SAFE_DELETE(_dynScaleVelocity);

    _dynScaleVelocity = dynScaleVelocity;
}
//-----------------------------------------------------------------------
void PUScaleVelocityAffector::resetDynScaleVelocity(bool resetToDefault)
{
    if (resetToDefault)
    {
        CC_SAFE_DELETE(_dynScaleVelocity);
        _dynScaleVelocity = new (std::nothrow) PUDynamicAttributeFixed();
        (static_cast<PUDynamicAttributeFixed*>(_dynScaleVelocity))->setValue(DEFAULT_VELOCITY_SCALE);
    }
}

PUScaleVelocityAffector* PUScaleVelocityAffector::create()
{
    auto psva = new (std::nothrow) PUScaleVelocityAffector();
    psva->autorelease();
    return psva;
}

void PUScaleVelocityAffector::copyAttributesTo( PUAffector* affector )
{
    PUAffector::copyAttributesTo(affector);

    PUScaleVelocityAffector* scaleVelocityAffector = static_cast<PUScaleVelocityAffector*>(affector);
    scaleVelocityAffector->setDynScaleVelocity(getDynScaleVelocity()->clone());
    scaleVelocityAffector->_sinceStartSystem = _sinceStartSystem;
    scaleVelocityAffector->_stopAtFlip = _stopAtFlip;
}

NS_CC_END
