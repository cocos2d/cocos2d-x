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

#include "CCParticle3DScaleAffector.h"
#include "3dparticle/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float Particle3DScaleAffector::DEFAULT_X_SCALE = 1.0f;
const float Particle3DScaleAffector::DEFAULT_Y_SCALE = 1.0f;
const float Particle3DScaleAffector::DEFAULT_Z_SCALE = 1.0f;
const float Particle3DScaleAffector::DEFAULT_XYZ_SCALE = 1.0f;

//-----------------------------------------------------------------------
Particle3DScaleAffector::Particle3DScaleAffector(void) : 
    PUParticle3DAffector(),
    _dynScaleXSet(false),
    _dynScaleYSet(false),
    _dynScaleZSet(false),
    _dynScaleXYZSet(false),
    _sinceStartSystem(false)
{
    _dynScaleX = new DynamicAttributeFixed();
    _dynScaleY = new DynamicAttributeFixed();
    _dynScaleZ = new DynamicAttributeFixed();
    _dynScaleXYZ = new DynamicAttributeFixed();
    (static_cast<DynamicAttributeFixed*>(_dynScaleX))->setValue(DEFAULT_X_SCALE);
    (static_cast<DynamicAttributeFixed*>(_dynScaleY))->setValue(DEFAULT_Y_SCALE);
    (static_cast<DynamicAttributeFixed*>(_dynScaleZ))->setValue(DEFAULT_Z_SCALE);
    (static_cast<DynamicAttributeFixed*>(_dynScaleXYZ))->setValue(DEFAULT_XYZ_SCALE);
    _latestTimeElapsed = 1.0f;
}
//-----------------------------------------------------------------------
Particle3DScaleAffector::~Particle3DScaleAffector(void)
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
void Particle3DScaleAffector::setDynScaleX(DynamicAttribute* dynScaleX)
{
    if (_dynScaleX)
        CC_SAFE_DELETE(_dynScaleX);

    _dynScaleX = dynScaleX;
    _dynScaleXSet = true;
}
//-----------------------------------------------------------------------
    void Particle3DScaleAffector::resetDynScaleX(bool resetToDefault)
{
    if (resetToDefault)
    {
        CC_SAFE_DELETE(_dynScaleX);
        _dynScaleX = new DynamicAttributeFixed();
        (static_cast<DynamicAttributeFixed*>(_dynScaleX))->setValue(DEFAULT_X_SCALE);
        _dynScaleXSet = false;
    }
    else
    {
        _dynScaleXSet = true;
    }
}
//-----------------------------------------------------------------------
void Particle3DScaleAffector::setDynScaleY(DynamicAttribute* dynScaleY)
{
    if (_dynScaleY)
        CC_SAFE_DELETE(_dynScaleY);

    _dynScaleY = dynScaleY;
    _dynScaleYSet = true;
}
//-----------------------------------------------------------------------
void Particle3DScaleAffector::resetDynScaleY(bool resetToDefault)
{
    if (resetToDefault)
    {

        CC_SAFE_DELETE(_dynScaleY);
        _dynScaleY = new DynamicAttributeFixed();
        (static_cast<DynamicAttributeFixed*>(_dynScaleY))->setValue(DEFAULT_X_SCALE);
        _dynScaleYSet = false;
    }
    else
    {
        _dynScaleYSet = true;
    }
}
//-----------------------------------------------------------------------
void Particle3DScaleAffector::setDynScaleZ(DynamicAttribute* dynScaleZ)
{
    if (_dynScaleZ)
        CC_SAFE_DELETE(_dynScaleZ);

    _dynScaleZ = dynScaleZ;
    _dynScaleZSet = true;
}
//-----------------------------------------------------------------------
void Particle3DScaleAffector::resetDynScaleZ(bool resetToDefault)
{
    if (resetToDefault)
    {
        CC_SAFE_DELETE(_dynScaleZ);
        _dynScaleZ = new DynamicAttributeFixed();
        (static_cast<DynamicAttributeFixed*>(_dynScaleZ))->setValue(DEFAULT_X_SCALE);
        _dynScaleYSet = false;
    }
    else
    {
        _dynScaleYSet = true;
    }
}
//-----------------------------------------------------------------------
void Particle3DScaleAffector::setDynScaleXYZ(DynamicAttribute* dynScaleXYZ)
{
    if (_dynScaleXYZ)
        CC_SAFE_DELETE(_dynScaleXYZ);

    _dynScaleXYZ = dynScaleXYZ;
    _dynScaleXYZSet = true;
}
//-----------------------------------------------------------------------
void Particle3DScaleAffector::resetDynScaleXYZ(bool resetToDefault)
{
    if (resetToDefault)
    {
        CC_SAFE_DELETE(_dynScaleXYZ);
        _dynScaleXYZ = new DynamicAttributeFixed();
        (static_cast<DynamicAttributeFixed*>(_dynScaleXYZ))->setValue(DEFAULT_XYZ_SCALE);
        _dynScaleXYZSet = false;
    }
    else
    {
        _dynScaleXYZSet = true;
    }
}
//-----------------------------------------------------------------------
float Particle3DScaleAffector::calculateScale(DynamicAttribute* dynScale, PUParticle3D* particle)
{
    if (!particle)
        return 0.0f;

    if (_sinceStartSystem)
    {
        // If control points are used (curved type), the first value of each control point is seconds from the start of the system
        return _dynamicAttributeHelper.calculate(dynScale, _particleSystem->getTimeElapsedSinceStart());
    }
    else
    {
        // If control points are used (curved type), the first value of each control point is the fraction of the particle lifetime [0..1]
        return _dynamicAttributeHelper.calculate(dynScale, particle->timeFraction);
    }
}

void Particle3DScaleAffector::updateAffector( PUParticle3D *particle, float deltaTime )
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

NS_CC_END