/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#include "ParticleUniversePCH.h"

#ifndef PARTICLE_UNIVERSE_EXPORTS
#define PARTICLE_UNIVERSE_EXPORTS
#endif

#include "ParticleAffectors/ParticleUniverseBoxCollider.h"

namespace ParticleUniverse
{
	// Constants
	const Real BoxCollider::DEFAULT_WIDTH = 100.0f;
	const Real BoxCollider::DEFAULT_HEIGHT = 100.0f;
	const Real BoxCollider::DEFAULT_DEPTH = 100.0f;

	//-----------------------------------------------------------------------
	BoxCollider::BoxCollider(void) : 
		BaseCollider(),
		mWidth(DEFAULT_WIDTH),
		mHeight(DEFAULT_HEIGHT),
		mDepth(DEFAULT_DEPTH),
		mXmin(0.0f),
		mXmax(0.0f),
		mYmin(0.0f),
		mYmax(0.0f),
		mZmin(0.0f),
		mZmax(0.0f),
		mPredictedPosition(Vector3::ZERO),
		mInnerCollision(false)
	{
	}
	//-----------------------------------------------------------------------
	const Real BoxCollider::getWidth(void) const
	{
		return mWidth;
	}
	//-----------------------------------------------------------------------
	void BoxCollider::setWidth(const Real width)
	{
		mWidth = width;
	}
	//-----------------------------------------------------------------------
	const Real BoxCollider::getHeight(void) const
	{
		return mHeight;
	}
	//-----------------------------------------------------------------------
	void BoxCollider::setHeight(const Real height)
	{
		mHeight = height;
	}
	//-----------------------------------------------------------------------
	const Real BoxCollider::getDepth(void) const
	{
		return mDepth;
	}
	//-----------------------------------------------------------------------
	void BoxCollider::setDepth(const Real depth)
	{
		mDepth = depth;
	}
	//-----------------------------------------------------------------------
	bool BoxCollider::isInnerCollision(void) const
	{
		return mInnerCollision;
	}
	//-----------------------------------------------------------------------
	void BoxCollider::setInnerCollision(bool innerCollision)
	{
		mInnerCollision = innerCollision;
	}
	//-----------------------------------------------------------------------
	void BoxCollider::_preProcessParticles(ParticleTechnique* particleTechnique, Real timeElapsed)
	{
		// Call parent
		BaseCollider::_preProcessParticles(particleTechnique, timeElapsed);

		// Calculate the affectors' center position in worldspace, set the box and calculate the bounds
		// Applied scaling in V 1.3.1.
		populateAlignedBox(mBox, getDerivedPosition(), _mAffectorScale.x * mWidth, _mAffectorScale.y * mHeight, _mAffectorScale.z * mDepth);
		_calculateBounds();
	}
	//-----------------------------------------------------------------------
	void BoxCollider::_affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed)
	{
		mPredictedPosition = particle->position + mVelocityScale * particle->direction;
		bool collision = false;

		/** Collision detection is a two-step. First, we determine whether the particle is now colliding.
			If it is, the particle is re-positioned. However, a timeElapsed value is used, which is not the same
			as the one that was used at the moment before the particle was colliding. Therefore, we rather 
			want to predict particle collision in front. This probably isn't the fastest solution.
			The same approach was used for the other colliders.
		*/
		switch(mIntersectionType)
		{
			case BaseCollider::IT_POINT:
			{
				// Validate for a point-box intersection
				if (mInnerCollision != mBox.intersects(particle->position))
				{
					// Collision detected (re-position the particle)
					particle->position -= mVelocityScale * particle->direction;
					collision = true;
				}
				else if (mInnerCollision != mBox.intersects(mPredictedPosition))
				{
					// Collision detected
					collision = true;
				}
			}
			break;

			case BaseCollider::IT_BOX:
			{
				// Validate for a box-box intersection
				if (particle->particleType != Particle::PT_VISUAL)
					break;

				VisualParticle* visualParticle = static_cast<VisualParticle*>(particle);
				AxisAlignedBox box;
				populateAlignedBox(box,
					visualParticle->position, 
					visualParticle->width, 
					visualParticle->height,
					visualParticle->depth);

				if (mInnerCollision != box.intersects(mBox))
				{
					// Collision detected (re-position the particle)
					particle->position -= mVelocityScale * particle->direction;
					collision = true;
				}
				else
				{
					AxisAlignedBox box;
					populateAlignedBox(box,
						mPredictedPosition, 
						visualParticle->width, 
						visualParticle->height,
						visualParticle->depth);
					if (mInnerCollision != box.intersects(mBox))
					{
						// Collision detected
						collision = true;
					}
				}
			}
			break;
		}

		if (collision)
		{
			calculateDirectionAfterCollision(particle);
			calculateRotationSpeedAfterCollision(particle);
			particle->addEventFlags(Particle::PEF_COLLIDED);
		}
	}
	//-----------------------------------------------------------------------
	void BoxCollider::calculateDirectionAfterCollision(Particle* particle)
	{
		switch (mCollisionType)
		{
			case BaseCollider::CT_BOUNCE:
			{
				// Determine the nearest side and reverse the direction
				if (_isSmallestValue (particle->position.x - mXmin, particle->position))
				{		
					particle->direction.x *= -1;
				}
				else if (_isSmallestValue (mXmax - particle->position.x, particle->position))
				{
					particle->direction.x *= -1;
				}
				else if (_isSmallestValue (particle->position.y - mYmin, particle->position))
				{
					particle->direction.y *= -1;
				}
				else if (_isSmallestValue (mYmax - particle->position.y, particle->position))
				{
					particle->direction.y *= -1;
				}
				else if (_isSmallestValue (particle->position.z - mZmin, particle->position))
				{
					particle->direction.z *= -1;
				}
				else if (_isSmallestValue (mZmax - particle->position.z, particle->position))
				{
					particle->direction.z *= -1;
				}
				particle->direction *= mBouncyness;
			}
			break;
			case BaseCollider::CT_FLOW:
			{
				if (_isSmallestValue (particle->position.x - mXmin, particle->position))
				{		
					particle->direction.x = 0;
				}
				else if (_isSmallestValue (mXmax - particle->position.x, particle->position))
				{
					particle->direction.x = 0;
				}
				else if (_isSmallestValue (particle->position.y - mYmin, particle->position))
				{
					particle->direction.y = 0;
				}
				else if (_isSmallestValue (mYmax - particle->position.y, particle->position))
				{
					particle->direction.y = 0;
				}
				else if (_isSmallestValue (particle->position.z - mZmin, particle->position))
				{
					particle->direction.z = 0;
				}
				else if (_isSmallestValue (mZmax - particle->position.z, particle->position))
				{
					particle->direction.z = 0;
				}
				particle->direction *= -mFriction;
			}
			break;
		}
	}
	//-----------------------------------------------------------------------
	void BoxCollider::_calculateBounds (void)
	{
		Real scaledWidth = _mAffectorScale.x * mWidth;
		Real scaledHeight = _mAffectorScale.y * mHeight;
		Real scaledDepth = _mAffectorScale.z * mDepth;

		mXmin = mDerivedPosition.x - 0.5f * scaledWidth;
		mXmax = mDerivedPosition.x + 0.5f * scaledWidth;
		mYmin = mDerivedPosition.y - 0.5f * scaledHeight;
		mYmax = mDerivedPosition.y + 0.5f * scaledHeight;
		mZmin = mDerivedPosition.z - 0.5f * scaledDepth;
		mZmax = mDerivedPosition.z + 0.5f * scaledDepth;
	}
    //-----------------------------------------------------------------------
	bool BoxCollider::_isSmallestValue(Real value, const Vector3& particlePosition)
    {
		Real value1 = particlePosition.x - mXmin;
		Real value2 = mXmax - particlePosition.x;
		Real value3 = particlePosition.y - mYmin;
		Real value4 = mYmax - particlePosition.y;
		Real value5 = particlePosition.z - mZmin;
		Real value6 = mZmax - particlePosition.z;

		return (
			value <= value1 && 
			value <= value2 &&
			value <= value3 && 
			value <= value4 &&
			value <= value5 &&
			value <= value6);
    }
	//-----------------------------------------------------------------------
	void BoxCollider::copyAttributesTo (ParticleAffector* affector)
	{
		BaseCollider::copyAttributesTo(affector);

		BoxCollider* boxCollider = static_cast<BoxCollider*>(affector);
		boxCollider->mWidth = mWidth;
		boxCollider->mHeight = mHeight;
		boxCollider->mDepth = mDepth;
		boxCollider->mInnerCollision = mInnerCollision;
	}
}
