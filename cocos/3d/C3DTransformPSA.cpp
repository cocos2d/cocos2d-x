#include "Base.h"
#include "C3DTransformPSA.h"

#include "C3DParticleSystem.h"
#include <vector>
#include "cocos2d.h"
#include "C3DParticleRender.h"

namespace cocos3d
{

C3DTransformPSA::C3DTransformPSA(C3DParticleSystem* system) :   
     C3DBaseParticleAction(system),
	 _rotation(C3DMatrix::identity())
     
{
   
}

C3DTransformPSA::~C3DTransformPSA()
{   
   
}


void C3DTransformPSA::load(C3DElementNode* properties)
{
	C3DBaseParticleAction::load(properties);

	_endSize = properties->getElement("endSize",&_endSize);
	_sizeRate = properties->getElement("sizeRate",&_sizeRate);
    
}

void C3DTransformPSA::save(C3DElementNode* properties)
{
	properties->empty();

	C3DBaseParticleAction::save(properties);

	properties->setElement("endSize",&_endSize);
	properties->setElement("sizeRate",&_sizeRate);
}

void C3DTransformPSA::action(long elapsedTime)
{    
	// Calculate the time passed since last update.
    float elapsedSecs = (float)elapsedTime * 0.001f;
	C3DParticle**& _particles = _system->_particles;
	int& _validParticleCount = _system->_validParticleCount;

	for (int i = 0; i < _validParticleCount; ++i)
    {
		C3DParticle*& p = _particles[i];

        p->_age -= elapsedTime;   


        if (p->_age > 0L)
        {
            if (p->_rotationSpeed != 0.0f && !p->_rotationAxis.isZero())
            {
                C3DMatrix::createRotation(p->_rotationAxis, p->_rotationSpeed * elapsedSecs, &_rotation);

                _rotation.transformPoint(p->_velocity, &p->_velocity);
                _rotation.transformPoint(p->_acceleration, &p->_acceleration);
            }

            p->_position.x += p->_velocity.x * elapsedSecs;
            p->_position.y += p->_velocity.y * elapsedSecs;
            p->_position.z += p->_velocity.z * elapsedSecs;

            p->_angle += p->_rotationPerParticleSpeed * elapsedSecs;

			if (_system->_numTintAction == 0)
				p->_color = C3DVector4(1.0f, 1.0f, 1.0f, 1.0f);
			else
				p->_color = C3DVector4(0.0f, 0.0f, 0.0f, 0.0f);


			if ( p->_size > _endSize )
			{
				p->_size -= _sizeRate * elapsedSecs;
				if ( p->_size < _endSize )
				{
					p->_size = _endSize;
				}
			}
			else if ( p->_size < _endSize )
			{
				p->_size += _sizeRate * elapsedSecs;
				if ( p->_size > _endSize )
				{
					p->_size = _endSize;
				}
			}

			
			if (_system->getParticleRender()->isSpriteAnimated())
			{
				if (!_system->getParticleRender()->isSpriteLoop())
				{
					// The last frame should finish exactly when the particle dies.
					float percent = 1 - (float)p->_age / (float)p->_ageStart; 
					int frameCount = _system->getParticleRender()->getFrameCount();
					p->_frame = (int)(percent * frameCount) + p->_frameStart;

					if (p->_frame >= frameCount)
						p->_frame %= frameCount;
				}
				else
				{
					// _spriteFrameDurationSecs is an absolute time measured in seconds,
					// and the animation repeats indefinitely.
					long duration = _system->getParticleRender()->getSpriteFrameDurationSecs() * 1000;
					int frameCount = _system->getParticleRender()->getFrameCount();
					if (duration == 0)
						p->_frame = p->_frameStart;
					else
						p->_frame = (p->_ageStart - p->_age) / duration + p->_frameStart;

					if (p->_frame >= frameCount)
						p->_frame %= frameCount;
				}
			}
        }
		else
		{
			 // Particle is dead.  Move the particle furthest from the start of the array
            // down to take its place, and re-use the slot at the end of the list of living particles.
            if (i != _validParticleCount - 1)
            {			
				C3DParticle* temp = _particles[i];
                _particles[i] = _particles[_validParticleCount - 1];
				_particles[_validParticleCount - 1] = temp;
				i--;
            }
            --_validParticleCount;
		}
    }

    
}
    
C3DBaseParticleAction* C3DTransformPSA::clone(C3DParticleSystem* system) const
{
    C3DTransformPSA* psa = new C3DTransformPSA(system);
    
    psa->copyFrom(this);
    
    psa->_endSize = _endSize;
    psa->_sizeRate = _sizeRate;
    
    return psa;
}

}
