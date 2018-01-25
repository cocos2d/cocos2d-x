/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "CCPUVelocityMatchingAffector.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN
// Constants
const float PUVelocityMatchingAffector::DEFAULT_RADIUS = 100.0f;

//-----------------------------------------------------------------------
PUVelocityMatchingAffector::PUVelocityMatchingAffector(void) : 
    PUAffector(),
    _radius(DEFAULT_RADIUS)
{
}

PUVelocityMatchingAffector::~PUVelocityMatchingAffector( void )
{

}

//-----------------------------------------------------------------------
float PUVelocityMatchingAffector::getRadius(void) const
{
    return _radius;
}
//-----------------------------------------------------------------------
void PUVelocityMatchingAffector::setRadius(float radius)
{
    _radius = radius;
}
////-----------------------------------------------------------------------
//void Particle3DVelocityMatchingAffector::_prepare(ParticleTechnique* particleTechnique)
//{
//	// Activate spatial hashing
//	particleTechnique->setSpatialHashingUsed(true);
//}
////-----------------------------------------------------------------------
//void Particle3DVelocityMatchingAffector::_unprepare(ParticleTechnique* particleTechnique)
//{
//	// Activate spatial hashing
//	particleTechnique->setSpatialHashingUsed(false);
//}
//-----------------------------------------------------------------------

void PUVelocityMatchingAffector::updatePUAffector( PUParticle3D* /*particle*/, float /*deltaTime*/ )
{
    //for (auto iter : _particleSystem->getParticles())
    //{
    //    PUParticle3D *particle = iter;
    //	// Determine neighbouring particles.
    //	SpatialHashTable<Particle*>* hashtable = particleTechnique->getSpatialHashTable();
    //	if (hashtable)
    //	{
    //		SpatialHashTable<Particle*>::HashTableCell cell = hashtable->getCell(particle->position);
    //		if (cell.empty())
    //			return;

    //		unsigned int size = static_cast<unsigned int>(cell.size());
    //		Vec3 sumDirection;
    //		Vec3 diff;
    //		unsigned int count = 0;
    //		for (unsigned int i = 0; i < size; ++i)
    //		{
    //			Particle* p = cell[i];

    //			// Don't check if it is the same particle
    //			if (particle != p)
    //			{
    //				// Validate whether the neighbouring particle is within range
    //				diff = p->position - particle->position;
    //				if (diff.length() < _radius)
    //				{
    //					sumDirection += p->direction;
    //					count++;
    //				}
    //			}
    //		}

    //		// Adjust direction
    //		if (count > 0)
    //		{
    //			sumDirection = sumDirection / (float)count;
    //			particle->direction += (sumDirection - particle->direction) * deltaTime;
    //		}
    //	}
    //}
}

PUVelocityMatchingAffector* PUVelocityMatchingAffector::create()
{
    auto pvma = new (std::nothrow) PUVelocityMatchingAffector();
    pvma->autorelease();
    return pvma;
}

void PUVelocityMatchingAffector::copyAttributesTo( PUAffector* affector )
{
    PUAffector::copyAttributesTo(affector);
    PUVelocityMatchingAffector* velocityMatchingAffector = static_cast<PUVelocityMatchingAffector*>(affector);
    velocityMatchingAffector->_radius = _radius;
}

NS_CC_END
