/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_BASE_ATTRACTOR_H__
#define __PU_BASE_ATTRACTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	/** This is a baseclass for other Force Affector classes.
    */
	class _ParticleUniverseExport BaseForceAffector : public ParticleAffector
	{
		public:
			enum ForceApplication
			{
				FA_AVERAGE,
				FA_ADD
			};

			// Constants
			static const Vector3 DEFAULT_FORCE_VECTOR;
			static const ForceApplication DEFAULT_FORCE_APPL;

			BaseForceAffector(void);
	        virtual ~BaseForceAffector(void) {};

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

			/** 
	        */
			const Vector3& getForceVector(void) const;
			void setForceVector(const Vector3& forceVector);

			/** 
	        */
			ForceApplication getForceApplication(void) const;
			void setForceApplication(ForceApplication forceApplication);

		protected:
			Vector3 mForceVector;
			Vector3 mScaledVector;
			ForceApplication mForceApplication;
	};

}
#endif
