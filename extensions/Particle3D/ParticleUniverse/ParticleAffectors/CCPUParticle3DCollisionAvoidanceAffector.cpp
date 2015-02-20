/****************************************************************************
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

#include "CCPUParticle3DCollisionAvoidanceAffector.h"
#include "extensions/Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"

NS_CC_BEGIN
// Constants
const float PUParticle3DCollisionAvoidanceAffector::DEFAULT_RADIUS = 100.0f;

//-----------------------------------------------------------------------
PUParticle3DCollisionAvoidanceAffector::PUParticle3DCollisionAvoidanceAffector(void) : 
    PUParticle3DAffector(),
    _radius(DEFAULT_RADIUS)
{
}
PUParticle3DCollisionAvoidanceAffector::~PUParticle3DCollisionAvoidanceAffector()
{

}
//-----------------------------------------------------------------------
float PUParticle3DCollisionAvoidanceAffector::getRadius(void) const
{
    return _radius;
}
//-----------------------------------------------------------------------
void PUParticle3DCollisionAvoidanceAffector::setRadius(float radius)
{
    _radius = radius;
}
//-----------------------------------------------------------------------
void PUParticle3DCollisionAvoidanceAffector::updatePUAffector( PUParticle3D *particle, float deltaTime )
{
    CCASSERT(0, "nonsupport yet");
    //for (auto iter : _particleSystem->getParticles())
    //{
    //	PUParticle3D *particle = iter;
    //	// Activate spatial hashing
    //	particleTechnique->setSpatialHashingUsed(true);

    //	// Determine neighbouring particles.
    //	SpatialHashTable<Particle*>* hashtable = particleTechnique->getSpatialHashTable();
    //	if (hashtable)
    //	{
    //		SpatialHashTable<Particle*>::HashTableCell cell = hashtable->getCell(particle->position);
    //		if (cell.empty())
    //			return;

    //		unsigned int size = static_cast<unsigned int>(cell.size());
    //		Vector3 displacement = Vector3::ZERO;
    //		Vector3 diff = Vector3::ZERO;
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
    //					displacement -= diff;
    //				}
    //			}
    //		}
    //		particle->direction += displacement * deltaTime;
    //	}

    //	// Deactivate spatial hashing
    //	particleTechnique->setSpatialHashingUsed(false);
    //}

}

PUParticle3DCollisionAvoidanceAffector* PUParticle3DCollisionAvoidanceAffector::create()
{
    auto pcaa = new (std::nothrow) PUParticle3DCollisionAvoidanceAffector();
    pcaa->autorelease();
    return pcaa;
}

NS_CC_END