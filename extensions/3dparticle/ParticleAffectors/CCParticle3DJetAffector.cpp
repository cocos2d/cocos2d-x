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

#include "CCParticle3DJetAffector.h"
#include "3dparticle/CCParticleSystem3D.h"

NS_CC_BEGIN

// Constants
const float Particle3DJetAffector::DEFAULT_ACCELERATION = 1.0f;

//-----------------------------------------------------------------------
Particle3DJetAffector::Particle3DJetAffector (void) : 
    Particle3DAffector(),
    _scaled(0.0f)
{
    //_dynAcceleration = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
    //(static_cast<DynamicAttributeFixed*>(_dynAcceleration))->setValue(DEFAULT_ACCELERATION);
}
//-----------------------------------------------------------------------
Particle3DJetAffector::~Particle3DJetAffector (void)
{
    //if (!_dynAcceleration)
    //	return;

    //PU_DELETE_T(_dynAcceleration, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
    //_dynAcceleration = 0;
}
//-----------------------------------------------------------------------
//void Particle3DJetAffector::setDynAcceleration(DynamicAttribute* dynAcceleration)
//{
//	if (_dynAcceleration)
//		PU_DELETE_T(_dynAcceleration, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
//
//	_dynAcceleration = dynAcceleration;
//}

void Particle3DJetAffector::updateAffector( float deltaTime )
{
    for (auto iter : _particleSystem->getParticles())
    {
        Particle3D *particle = iter;
        //_scaled = deltaTime * (_dynAcceleration->getValue(particle->timeFraction));
        if (particle->direction == Vec3::ZERO)
        {
            // Existing direction is zero, so use original direction
            particle->direction += (particle->originalDirection * _scaled);
        }
        else
        {
            particle->direction += (particle->direction * _scaled);
        }
    }
}

NS_CC_END