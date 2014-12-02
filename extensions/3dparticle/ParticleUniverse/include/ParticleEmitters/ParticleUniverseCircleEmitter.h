/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_CIRCLE_EMITTER_H__
#define __PU_CIRCLE_EMITTER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseSystem.h"
#include "ParticleUniverseEmitter.h"

namespace ParticleUniverse
{
	/** The CircleEmitter is a ParticleEmitter that emits particles on a circle shape. Particle can be emitted
		random on the circle, but it can also follow the circles' contours.
    */
	class _ParticleUniverseExport CircleEmitter : public ParticleEmitter
	{
		protected:
			Real mRadius;
			Real mCircleAngle;
			Real mOriginalCircleAngle;
			Real mStep;
			Real mX;
			Real mZ;
			bool mRandom;
			Quaternion mOrientation;
			Vector3 mNormal;

		public:
			// Constants
			static const Real DEFAULT_RADIUS;
			static const Real DEFAULT_STEP;
			static const Real DEFAULT_ANGLE;
			static const bool DEFAULT_RANDOM;
			static const Vector3 DEFAULT_NORMAL;

			CircleEmitter(void);
	        virtual ~CircleEmitter(void) {};

			/** 
	        */
			const Real getRadius(void) const;
			void setRadius(const Real radius);

			/** 
	        */
			const Real getCircleAngle(void) const;
			void setCircleAngle(const Real circleAngle);

			/** 
	        */
			const Real getStep(void) const;
			void setStep(const Real step);

			/** 
	        */
			const bool isRandom(void) const;
			void setRandom(const bool random);

			/* 
			*/ 
			const Quaternion& getOrientation(void) const;
			const Vector3& getNormal(void) const;
			void setNormal(const Vector3 &normal); 

			/** See ParticleEmiter
	        */
			void _notifyStart(void);

			/** Determine a particle position on the circle.
	        */
			virtual void _initParticlePosition(Particle* particle);

			/** Determine the particle direction.
	        */
			virtual void _initParticleDirection(Particle* particle);

			/** 
	        */
			virtual void copyAttributesTo (ParticleEmitter* emitter);
	};

}
#endif
