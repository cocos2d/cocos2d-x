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

#include "CCParticle3DGeometryRotator.h"
#include "3dparticle/CCParticleSystem3D.h"

NS_CC_BEGIN
//-----------------------------------------------------------------------
// Constants
const bool Particle3DGeometryRotator::DEFAULT_USE_OWN = false;
const float Particle3DGeometryRotator::DEFAULT_ROTATION_SPEED = 10.0f;
const Vec3 Particle3DGeometryRotator::DEFAULT_ROTATION_AXIS(0, 0, 0);

//-----------------------------------------------------------------------
Particle3DGeometryRotator::Particle3DGeometryRotator() : 
	Particle3DAffector(),
	_scaledRotationSpeed(0.0f),
	_useOwnRotationSpeed(DEFAULT_USE_OWN),
	//mQ(Quaternion::IDENTITY),
	_rotationAxis(DEFAULT_ROTATION_AXIS),
	_rotationAxisSet(false)
{
	//_dynRotationSpeed = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
	//(static_cast<DynamicAttributeFixed*>(_dynRotationSpeed))->setValue(DEFAULT_ROTATION_SPEED);
};
//-----------------------------------------------------------------------
Particle3DGeometryRotator::~Particle3DGeometryRotator()
{
	//if (_dynRotationSpeed)
	//	PU_DELETE_T(_dynRotationSpeed, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
}
//-----------------------------------------------------------------------
const Vec3& Particle3DGeometryRotator::getRotationAxis() const
{
	return _rotationAxis;
}
//-----------------------------------------------------------------------
void Particle3DGeometryRotator::setRotationAxis(const Vec3& rotationAxis)
{
	_rotationAxis = rotationAxis;
	_rotationAxisSet = true;
}
//-----------------------------------------------------------------------
void Particle3DGeometryRotator::resetRotationAxis(void)
{
	//_dynRotationSpeed = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
	//(static_cast<DynamicAttributeFixed*>(_dynRotationSpeed))->setValue(DEFAULT_ROTATION_SPEED);
	//_rotationAxisSet = false;
}
//-----------------------------------------------------------------------
//DynamicAttribute* Particle3DGeometryRotator::getRotationSpeed(void) const
//{
//	return _dynRotationSpeed;
//}
////-----------------------------------------------------------------------
//void Particle3DGeometryRotator::setRotationSpeed(DynamicAttribute* dynRotationSpeed)
//{
//	if (_dynRotationSpeed)
//		PU_DELETE_T(_dynRotationSpeed, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
//
//	_dynRotationSpeed = dynRotationSpeed;
//}
//-----------------------------------------------------------------------
bool Particle3DGeometryRotator::useOwnRotationSpeed (void) const
{
	return _useOwnRotationSpeed;
}
//-----------------------------------------------------------------------
void Particle3DGeometryRotator::setUseOwnRotationSpeed (bool useOwnRotationSpeed)
{
	_useOwnRotationSpeed = useOwnRotationSpeed;
}
//-----------------------------------------------------------------------
float Particle3DGeometryRotator::calculateRotationSpeed(Particle3D* particle)
{
	//return _dynamicAttributeHelper.calculate(_dynRotationSpeed, particle->timeFraction);
	//FIXME
	return particle->timeFraction;
}
//-----------------------------------------------------------------------
void Particle3DGeometryRotator::initParticleForEmission(Particle3D* particle)
{
	//// Only continue if the particle is a visual particle
	//if (particle->particleType != Particle::PT_VISUAL)
	//	return;
	for (auto iter : _particleSystem->getParticles())
	{
		Particle3D *particle = iter;
		if (!_rotationAxisSet)
		{
			// Set initial random rotation axis and orientation(PU 1.4)
			particle->orientation.x = CCRANDOM_MINUS1_1();
			particle->orientation.y = CCRANDOM_MINUS1_1();
			particle->orientation.z = CCRANDOM_MINUS1_1();
			particle->orientation.w = CCRANDOM_MINUS1_1();
			particle->orientation.normalize();
			particle->rotationAxis.x = CCRANDOM_0_1();
			particle->rotationAxis.y = CCRANDOM_0_1();
			particle->rotationAxis.z = CCRANDOM_0_1();
			particle->rotationAxis.normalize();
		}

		if (_useOwnRotationSpeed)
		{
			// Use the rotation speed of the particle itself
			particle->rotationSpeed = calculateRotationSpeed(particle);
		}
	}
}
//-----------------------------------------------------------------------

void Particle3DGeometryRotator::updateAffector( float deltaTime )
{
	for (auto iter : _particleSystem->getParticles())
	{
		Particle3D *particle = iter;
		// Rotate the geometry

		if (_useOwnRotationSpeed)
		{
			// Use scaled rotationspeed and adjust the speed according to the velocity
			_scaledRotationSpeed = particle->rotationSpeed * deltaTime;
		}
		else
		{
			// Scale speed (beware that dynamic values don't result in a rotation; use a fixed value instead)
			_scaledRotationSpeed = calculateRotationSpeed(particle) * deltaTime;
		}

		_q.set(0.0f, 0.0f, 0.0f, 1.0f);
		//_q = Quaternion::IDENTITY;
		if (_rotationAxisSet)
		{
			_q.set(_rotationAxis, _scaledRotationSpeed);
			//_q.FromAngleAxis(Radian(_scaledRotationSpeed), _rotationAxis);
		}
		else
		{
			_q.set(particle->rotationAxis, _scaledRotationSpeed);
			//_q.FromAngleAxis(Radian(_scaledRotationSpeed), visualParticle->rotationAxis);
		}

		particle->orientation = _q * particle->orientation;
	}
}

//-----------------------------------------------------------------------

NS_CC_END