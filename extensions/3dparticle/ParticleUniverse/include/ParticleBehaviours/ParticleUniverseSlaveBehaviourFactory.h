/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SLAVE_BEHAVIOUR_FACTORY_H__
#define __PU_SLAVE_BEHAVIOUR_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseBehaviourFactory.h"
#include "ParticleUniverseSlaveBehaviour.h"
#include "ParticleUniverseSlaveBehaviourTokens.h"

namespace ParticleUniverse
{
	/** This is the factory class that is responsible for creating a SlaveBehaviour.
    */
	class _ParticleUniverseExport SlaveBehaviourFactory : public ParticleBehaviourFactory
	{
		public:
			SlaveBehaviourFactory(void) {};
	        virtual ~SlaveBehaviourFactory(void) {};

			/** See ParticleBehaviourFactory */
			String getBehaviourType(void) const
			{
				return "Slave";
			}

			/** See ParticleBehaviourFactory */
			ParticleBehaviour* createBehaviour(void)
			{
				return _createBehaviour<SlaveBehaviour>();
			}

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate
				mSlaveBehaviourWriter.write(serializer, element);
			}

		protected:
			SlaveBehaviourWriter mSlaveBehaviourWriter;
	};

}
#endif
