/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_POSITION_EMITTER_H__
#define __PU_POSITION_EMITTER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseSystem.h"
#include "ParticleUniverseEmitter.h"

namespace ParticleUniverse
{
	/** The PositionEmitter is an emitter that emits particles from one or more given positions.
		The PositionEmitter enables building up a predefined structure out of particles. Imaging building up a
		wall that is made up from stone blocks. The particles are emitted on the positions that are added to this
		emitter. Adding some physical behaviour to the particles and you have your stone wall that collapses if a 
		force is applied to it.
    */
	class _ParticleUniverseExport PositionEmitter : public ParticleEmitter
	{
		protected:
			vector<Vector3> mPositionList;
			bool mRandomized;
			size_t mIndex;

		public:
			// Constants
			static const bool DEFAULT_RANDOMIZE;

			PositionEmitter(void);
	        virtual ~PositionEmitter(void) {};

			/** 
	        */
			bool isRandomized(void) const;

			/** 
	        */
			void setRandomized(bool randomized);

			/** Returns a list with positions
	        */
			const vector<Vector3>& getPositions(void) const;

			/** Add a new position to this emitter
	        */
			void addPosition(const Vector3& position);

			/** Remove all positions from this emitter
	        */
			void removeAllPositions(void);

			/** See ParticleEmitter
			*/
			void _notifyStart(void);

			/** See ParticleEmitter
			*/
			virtual unsigned short _calculateRequestedParticles(Real timeElapsed);

			/** Generate a particle position based on the added positions.
	        */
			virtual void _initParticlePosition(Particle* particle);

			/** 
	        */
			virtual void copyAttributesTo (ParticleEmitter* emitter);
	};

}
#endif
