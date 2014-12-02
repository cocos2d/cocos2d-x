/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SLAVE_EMITTER_H__
#define __PU_SLAVE_EMITTER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEmitter.h"
#include "ParticleUniverseTechniqueListener.h"

namespace ParticleUniverse
{
	/** The SlaveEmitter makes the particle act as a slave, so it follows another particle to which it is related. This only applies
		at the creation (initialisation) of the particle. For further slave behaviour during the lifespan of the particle, the 
		SlaveBehaviour must be used also.
    */
	class _ParticleUniverseExport SlaveEmitter : public ParticleEmitter, public TechniqueListener
	{
		protected:
			Particle* mMasterParticle;
			String mMasterTechniqueName;
			String mMasterEmitterName;
			Vector3 mMasterPosition;
			Vector3 mMasterDirection;
			bool mMasterEmitterNameSet;

		public:
			SlaveEmitter(void);
	        virtual ~SlaveEmitter(void){};

			/** 
	        */
			const String& getMasterTechniqueName(void) const;

			/** 
	        */
			void setMasterTechniqueName(const String& masterTechniqueName);

			/** 
	        */
			const String& getMasterEmitterName(void) const;

			/** See ParticleEmitter.
	        */
			virtual void _initParticlePosition(Particle* particle);

			/** See ParticleEmitter.
	        */
			virtual void _initParticleDirection(Particle* particle);

			/** See ParticleEmitter.
	        */
			virtual void _prepare(ParticleTechnique* particleTechnique);

			/** See ParticleEmitter.
	        */
			virtual void _unprepare(ParticleTechnique* particleTechnique);

			/** See ParticleEmitter.
			*/
			virtual void _notifyStart (void);

			/** Initialise the emitted particle. This means that its position is set.
	        */
			virtual void particleEmitted(ParticleTechnique* particleTechnique, Particle* particle);

			/** No implementation.
	        */
			virtual void particleExpired(ParticleTechnique* particleTechnique, Particle* particle){};

			/** 
	        */
			void setMasterEmitterName(const String& masterEmitterName);

			/** 
	        */
			virtual void copyAttributesTo (ParticleEmitter* emitter);
	};

}
#endif
