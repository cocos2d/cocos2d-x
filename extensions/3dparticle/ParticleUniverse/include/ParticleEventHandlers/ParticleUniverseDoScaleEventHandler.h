/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_DO_SCALE_EVENT_HANDLER_H__
#define __PU_DO_SCALE_EVENT_HANDLER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEventHandler.h"

namespace ParticleUniverse
{
	/** The DoScaleEventHandler scales different particle attributes.
    */
	class _ParticleUniverseExport DoScaleEventHandler : public ParticleEventHandler
	{
		public:
			enum ScaleType
			{
				ST_TIME_TO_LIVE,
				ST_VELOCITY
			};

			// Constants
			static const ScaleType DEFAULT_SCALE_TYPE;
			static const Real DEFAULT_SCALE_FRACTION;

			DoScaleEventHandler(void);
	        virtual ~DoScaleEventHandler(void) {};

			/** Returns the scale type
	        */
			const ScaleType& getScaleType(void) const;

			/** Set the scale type. This scale type identifies to which attribute the scale factor is applied.
	        */
			void setScaleType(const ScaleType& scaleType);

			/** Returns the scale fraction
	        */
			const Real getScaleFraction(void) const;

			/** Set the scale fraction. This scale fraction value is used to scale different attributes if the 
				event handler is called.
	        */
			void setScaleFraction(const Real scaleFraction);

			/** 
	        */
			virtual void _handle (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** Copy attributes to another event handler.
	        */
			virtual void copyAttributesTo (ParticleEventHandler* eventHandler);

		protected:
			Real mScaleFraction;
			ScaleType mScaleType;
	};

}
#endif
