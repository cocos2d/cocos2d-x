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
#include "3dparticle/CCParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float Particle3DScaleAffector::DEFAULT_X_SCALE = 1.0f;
const float Particle3DScaleAffector::DEFAULT_Y_SCALE = 1.0f;
const float Particle3DScaleAffector::DEFAULT_Z_SCALE = 1.0f;
const float Particle3DScaleAffector::DEFAULT_XYZ_SCALE = 1.0f;

//-----------------------------------------------------------------------
Particle3DScaleAffector::Particle3DScaleAffector(void) : 
    Particle3DAffector(),
    _dynScaleXSet(false),
    _dynScaleYSet(false),
    _dynScaleZSet(false),
    _dynScaleXYZSet(false),
    _sinceStartSystem(false)
{
    //_dynScaleX = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
    //_dynScaleY = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
    //_dynScaleZ = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
    //_dynScaleXYZ = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
    //(static_cast<DynamicAttributeFixed*>(_dynScaleX))->setValue(DEFAULT_X_SCALE);
    //(static_cast<DynamicAttributeFixed*>(_dynScaleY))->setValue(DEFAULT_Y_SCALE);
    //(static_cast<DynamicAttributeFixed*>(_dynScaleZ))->setValue(DEFAULT_Z_SCALE);
    //(static_cast<DynamicAttributeFixed*>(_dynScaleXYZ))->setValue(DEFAULT_XYZ_SCALE);
    _latestTimeElapsed = 1.0f;
}
//-----------------------------------------------------------------------
Particle3DScaleAffector::~Particle3DScaleAffector(void)
{
    //if (_dynScaleX)
    //{
    //	PU_DELETE_T(_dynScaleX, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
    //	_dynScaleX = 0;
    //}
    //if (_dynScaleY)
    //{
    //	PU_DELETE_T(_dynScaleY, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
    //	_dynScaleY = 0;
    //}
    //if (_dynScaleZ)
    //{
    //	PU_DELETE_T(_dynScaleZ, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
    //	_dynScaleZ = 0;
    //}
    //if (_dynScaleXYZ)
    //{
    //	PU_DELETE_T(_dynScaleXYZ, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
    //	_dynScaleXYZ = 0;
    //}
}
//-----------------------------------------------------------------------
//void Particle3DScaleAffector::setDynScaleX(DynamicAttribute* dynScaleX)
//{
//	if (_dynScaleX)
//		PU_DELETE_T(_dynScaleX, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
//
//	_dynScaleX = dynScaleX;
//	_dynScaleXSet = true;
//}
//-----------------------------------------------------------------------
//void Particle3DScaleAffector::resetDynScaleX(bool resetToDefault)
//{
//	if (resetToDefault)
//	{
//		PU_DELETE_T(_dynScaleX, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
//		_dynScaleX = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
//		(static_cast<DynamicAttributeFixed*>(_dynScaleX))->setValue(DEFAULT_X_SCALE);
//		_dynScaleXSet = false;
//	}
//	else
//	{
//		_dynScaleXSet = true;
//	}
//}
//-----------------------------------------------------------------------
//void Particle3DScaleAffector::setDynScaleY(DynamicAttribute* dynScaleY)
//{
//	if (_dynScaleY)
//		PU_DELETE_T(_dynScaleY, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
//
//	_dynScaleY = dynScaleY;
//	_dynScaleYSet = true;
//}
//-----------------------------------------------------------------------
//void Particle3DScaleAffector::resetDynScaleY(bool resetToDefault)
//{
//	if (resetToDefault)
//	{
//		PU_DELETE_T(_dynScaleY, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
//		_dynScaleY = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
//		(static_cast<DynamicAttributeFixed*>(_dynScaleY))->setValue(DEFAULT_X_SCALE);
//		_dynScaleYSet = false;
//	}
//	else
//	{
//		_dynScaleYSet = true;
//	}
//}
//-----------------------------------------------------------------------
//void Particle3DScaleAffector::setDynScaleZ(DynamicAttribute* dynScaleZ)
//{
//	if (_dynScaleZ)
//		PU_DELETE_T(_dynScaleZ, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
//
//	_dynScaleZ = dynScaleZ;
//	_dynScaleZSet = true;
//}
//-----------------------------------------------------------------------
//void Particle3DScaleAffector::resetDynScaleZ(bool resetToDefault)
//{
//	if (resetToDefault)
//	{
//		PU_DELETE_T(_dynScaleZ, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
//		_dynScaleZ = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
//		(static_cast<DynamicAttributeFixed*>(_dynScaleZ))->setValue(DEFAULT_X_SCALE);
//		_dynScaleYSet = false;
//	}
//	else
//	{
//		_dynScaleYSet = true;
//	}
//}
//-----------------------------------------------------------------------
//void Particle3DScaleAffector::setDynScaleXYZ(DynamicAttribute* dynScaleXYZ)
//{
//	if (_dynScaleXYZ)
//		PU_DELETE_T(_dynScaleXYZ, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
//
//	_dynScaleXYZ = dynScaleXYZ;
//	_dynScaleXYZSet = true;
//}
//-----------------------------------------------------------------------
//void Particle3DScaleAffector::resetDynScaleXYZ(bool resetToDefault)
//{
//	if (resetToDefault)
//	{
//		//PU_DELETE_T(_dynScaleXYZ, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
//		//_dynScaleXYZ = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
//		//(static_cast<DynamicAttributeFixed*>(_dynScaleXYZ))->setValue(DEFAULT_XYZ_SCALE);
//		_dynScaleXYZSet = false;
//	}
//	else
//	{
//		_dynScaleXYZSet = true;
//	}
//}
//-----------------------------------------------------------------------
//float Particle3DScaleAffector::calculateScale(DynamicAttribute* dynScale, Particle3D* particle)
//{
//	if (!particle)
//		return 0.0f;
//
//	if (_sinceStartSystem)
//	{
//		// If control points are used (curved type), the first value of each control point is seconds from the start of the system
//		return _dynamicAttributeHelper.calculate(dynScale, mParentTechnique->getParentSystem()->getTimeElapsedSinceStart());
//	}
//	else
//	{
//		// If control points are used (curved type), the first value of each control point is the fraction of the particle lifetime [0..1]
//		return _dynamicAttributeHelper.calculate(dynScale, particle->timeFraction);
//	}
//}

void Particle3DScaleAffector::updateAffector( float deltaTime )
{

    //// Only continue if the particle is a visual particle
    //if (particle->particleType != Particle::PT_VISUAL)
    //	return;
    for (auto iter : _particleSystem->getParticles())
    {
        Particle3D *particle = iter;
        float ds = 0;
        float width = 0;
        float height = 0;
        float depth = 0;
        float dimension = 0; // Added in V1.4

        if (_dynScaleXYZSet)
        {
            //ds = calculateScale(_dynScaleXYZ, particle) * deltaTime * calculateAffectSpecialisationFactor(particle);
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
                //ds = calculateScale(_dynScaleX, particle) * deltaTime;
                dimension = particle->width + ds * _affectorScale.x;
                if (dimension > 0)
                {
                    width = dimension;
                }
            }
            if (_dynScaleYSet)
            {
                //ds = calculateScale(_dynScaleY, particle) * deltaTime;
                dimension = particle->height + ds * _affectorScale.y;
                if (dimension > 0)
                {
                    height = dimension;
                }
            }
            if (_dynScaleZSet)
            {
                //ds = calculateScale(_dynScaleZ, particle) * deltaTime;
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