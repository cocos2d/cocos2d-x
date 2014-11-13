/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_COLOUR_AFFECTOR_H__
#define __PU_COLOUR_AFFECTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	/** This affector is typically used to change the colour of a particle during its lifetime.
    */
	class _ParticleUniverseExport ColourAffector : public ParticleAffector
	{
		public:
			typedef map<Real, ColourValue> ColourMap;
			typedef map<Real, ColourValue>::iterator ColourMapIterator;
			enum ColourOperation
			{
				CAO_MULTIPLY,
				CAO_SET
			};

			// Constants
			static const ColourOperation DEFAULT_COLOUR_OPERATION;

			// Constructor
			ColourAffector(void);

			// Destructor
	        virtual ~ColourAffector(void) {};

			/** 
	        */
			void addColour(Real timeFraction, const ColourValue& colour);

			/** 
	        */
			const ColourMap& getTimeAndColour(void) const;

			/** 
	        */
			void clearColourMap (void);
				
			/** 
	        */
			inline ColourMapIterator _findNearestColourMapIterator(Real timeFraction);

			/** 
	        */
			const ColourOperation& getColourOperation (void) const;

			/** 
	        */
			void setColourOperation (const ColourOperation& colourOperation);

			/** 
	        */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

		protected:
			ColourMap mColourMap;
			ColourOperation mColourOperation;
	};

}
#endif
