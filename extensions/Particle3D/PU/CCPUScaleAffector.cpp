/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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

#include "CCPUScaleAffector.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float PUScaleAffector::DEFAULT_X_SCALE = 1.0f;
const float PUScaleAffector::DEFAULT_Y_SCALE = 1.0f;
const float PUScaleAffector::DEFAULT_Z_SCALE = 1.0f;
const float PUScaleAffector::DEFAULT_XYZ_SCALE = 1.0f;

//-----------------------------------------------------------------------
PUScaleAffector::PUScaleAffector(void) : 
    PUAffector(),
    _dynScaleXSet(false),
    _dynScaleYSet(false),
    _dynScaleZSet(false),
    _dynScaleXYZSet(false),
    _sinceStartSystem(false)
{
    _dynScaleX = new (std::nothrow) PUDynamicAttributeFixed();
    _dynScaleY = new (std::nothrow) PUDynamicAttributeFixed();
    _dynScaleZ = new (std::nothrow) PUDynamicAttributeFixed();
    _dynScaleXYZ = new (std::nothrow) PUDynamicAttributeFixed();
    (static_cast<PUDynamicAttributeFixed*>(_dynScaleX))->setValue(DEFAULT_X_SCALE);
    (static_cast<PUDynamicAttributeFixed*>(_dynScaleY))->setValue(DEFAULT_Y_SCALE);
    (static_cast<PUDynamicAttributeFixed*>(_dynScaleZ))->setValue(DEFAULT_Z_SCALE);
    (static_cast<PUDynamicAttributeFixed*>(_dynScaleXYZ))->setValue(DEFAULT_XYZ_SCALE);
    _latestTimeElapsed = 1.0f;
}
//-----------------------------------------------------------------------
PUScaleAffector::~PUScaleAffector(void)
{
    if (_dynScaleX)
    {
        CC_SAFE_DELETE(_dynScaleX);
    }
    if (_dynScaleY)
    {
        CC_SAFE_DELETE(_dynScaleY);
    }
    if (_dynScaleZ)
    {
        CC_SAFE_DELETE(_dynScaleZ);
    }
    if (_dynScaleXYZ)
    {
        CC_SAFE_DELETE(_dynScaleXYZ);
    }
}
//-----------------------------------------------------------------------
void PUScaleAffector::setDynScaleX(PUDynamicAttribute* dynScaleX)
{
    if (_dynScaleX)
        CC_SAFE_DELETE(_dynScaleX);

    _dynScaleX = dynScaleX;
    _dynScaleXSet = true;
}
//-----------------------------------------------------------------------
    void PUScaleAffector::resetDynScaleX(bool resetToDefault)
{
    if (resetToDefault)
    {
        CC_SAFE_DELETE(_dynScaleX);
        _dynScaleX = new (std::nothrow) PUDynamicAttributeFixed();
        (static_cast<PUDynamicAttributeFixed*>(_dynScaleX))->setValue(DEFAULT_X_SCALE);
        _dynScaleXSet = false;
    }
    else
    {
        _dynScaleXSet = true;
    }
}
//-----------------------------------------------------------------------
void PUScaleAffector::setDynScaleY(PUDynamicAttribute* dynScaleY)
{
    if (_dynScaleY)
        CC_SAFE_DELETE(_dynScaleY);

    _dynScaleY = dynScaleY;
    _dynScaleYSet = true;
}
//-----------------------------------------------------------------------
void PUScaleAffector::resetDynScaleY(bool resetToDefault)
{
    if (resetToDefault)
    {

        CC_SAFE_DELETE(_dynScaleY);
        _dynScaleY = new (std::nothrow) PUDynamicAttributeFixed();
        (static_cast<PUDynamicAttributeFixed*>(_dynScaleY))->setValue(DEFAULT_X_SCALE);
        _dynScaleYSet = false;
    }
    else
    {
        _dynScaleYSet = true;
    }
}
//-----------------------------------------------------------------------
void PUScaleAffector::setDynScaleZ(PUDynamicAttribute* dynScaleZ)
{
    if (_dynScaleZ)
        CC_SAFE_DELETE(_dynScaleZ);

    _dynScaleZ = dynScaleZ;
    _dynScaleZSet = true;
}
//-----------------------------------------------------------------------
void PUScaleAffector::resetDynScaleZ(bool resetToDefault)
{
    if (resetToDefault)
    {
        CC_SAFE_DELETE(_dynScaleZ);
        _dynScaleZ = new (std::nothrow) PUDynamicAttributeFixed();
        (static_cast<PUDynamicAttributeFixed*>(_dynScaleZ))->setValue(DEFAULT_X_SCALE);
        _dynScaleYSet = false;
    }
    else
    {
        _dynScaleYSet = true;
    }
}
//-----------------------------------------------------------------------
void PUScaleAffector::setDynScaleXYZ(PUDynamicAttribute* dynScaleXYZ)
{
    if (_dynScaleXYZ)
        CC_SAFE_DELETE(_dynScaleXYZ);

    _dynScaleXYZ = dynScaleXYZ;
    _dynScaleXYZSet = true;
}
//-----------------------------------------------------------------------
void PUScaleAffector::resetDynScaleXYZ(bool resetToDefault)
{
    if (resetToDefault)
    {
        CC_SAFE_DELETE(_dynScaleXYZ);
        _dynScaleXYZ = new (std::nothrow) PUDynamicAttributeFixed();
        (static_cast<PUDynamicAttributeFixed*>(_dynScaleXYZ))->setValue(DEFAULT_XYZ_SCALE);
        _dynScaleXYZSet = false;
    }
    else
    {
        _dynScaleXYZSet = true;
    }
}
//-----------------------------------------------------------------------
float PUScaleAffector::calculateScale(PUDynamicAttribute* dynScale, PUParticle3D* particle)
{
    if (!particle)
        return 0.0f;

    if (_sinceStartSystem)
    {
        // If control points are used (curved type), the first value of each control point is seconds from the start of the system
        return _dynamicAttributeHelper.calculate(dynScale, (static_cast<PUParticleSystem3D *>(_particleSystem))->getTimeElapsedSinceStart());
    }
    else
    {
        // If control points are used (curved type), the first value of each control point is the fraction of the particle lifetime [0..1]
        return _dynamicAttributeHelper.calculate(dynScale, particle->timeFraction);
    }
}

void PUScaleAffector::updatePUAffector( PUParticle3D *particle, float deltaTime )
{

    //// Only continue if the particle is a visual particle
    //if (particle->particleType != Particle::PT_VISUAL)
    //	return;
    //for (auto iter : _particleSystem->getParticles())
    {
        //PUParticle3D *particle = iter;
        float ds = 0;
        float width = 0;
        float height = 0;
        float depth = 0;
        float dimension = 0; // Added in V1.4

        if (_dynScaleXYZSet)
        {
            ds = calculateScale(_dynScaleXYZ, particle) * deltaTime * calculateAffectSpecialisationFactor(particle);
            dimension = particle->width + ds * _affectorScale.x;
            if (dimension > 0)
            {
                width = dimension;
            }
            dimension = particle->height + ds * _affectorScale.y;
            if (dimension > 0)
            {
                height = dimension;
            }
            dimension = particle->depth + ds * _affectorScale.z;
            if (dimension > 0)
            {
                depth = dimension;
            }
            particle->setOwnDimensions(width, height, depth);
        }
        else
        {
            if (_dynScaleXSet)
            {
                ds = calculateScale(_dynScaleX, particle) * deltaTime;
                dimension = particle->width + ds * _affectorScale.x;
                if (dimension > 0)
                {
                    width = dimension;
                }
            }
            if (_dynScaleYSet)
            {
                ds = calculateScale(_dynScaleY, particle) * deltaTime;
                dimension = particle->height + ds * _affectorScale.y;
                if (dimension > 0)
                {
                    height = dimension;
                }
            }
            if (_dynScaleZSet)
            {
                ds = calculateScale(_dynScaleZ, particle) * deltaTime;
                dimension = particle->depth + ds * _affectorScale.z;
                if (dimension > 0)
                {
                    depth = dimension;
                }
            }
            particle->setOwnDimensions(width, height, depth);
        }
    }

}

PUScaleAffector* PUScaleAffector::create()
{
    auto psa = new (std::nothrow) PUScaleAffector();
    psa->autorelease();
    return psa;
}

void PUScaleAffector::copyAttributesTo( PUAffector* affector )
{
    PUAffector::copyAttributesTo(affector);

    PUScaleAffector* scaleAffector = static_cast<PUScaleAffector*>(affector);
    scaleAffector->setDynScaleX(getDynScaleX()->clone());
    scaleAffector->setDynScaleY(getDynScaleY()->clone());
    scaleAffector->setDynScaleZ(getDynScaleZ()->clone());
    scaleAffector->setDynScaleXYZ(getDynScaleXYZ()->clone());
    scaleAffector->_dynScaleXSet = _dynScaleXSet;
    scaleAffector->_dynScaleYSet = _dynScaleYSet;
    scaleAffector->_dynScaleZSet = _dynScaleZSet;
    scaleAffector->_dynScaleXYZSet = _dynScaleXYZSet;
    scaleAffector->_sinceStartSystem = _sinceStartSystem;
}

NS_CC_END
