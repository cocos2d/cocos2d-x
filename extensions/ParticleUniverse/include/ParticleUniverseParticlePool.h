/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PARTICLE_POOL_H__
#define __PU_PARTICLE_POOL_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniversePool.h"
#include "ParticleUniversePoolMap.h"
#include "ParticleUniverseVisualParticle.h"

namespace ParticleUniverse
{
	/** The ParticlePool is a container class that includes other pools. The ParticlePool acts as one pool
		with different types of particles.
    */
	class _ParticleUniverseExport ParticlePool
	{
		protected:
			ParticleTechnique* mParentTechnique;

			/** The Pools
		    */
			Pool<VisualParticle> mVisualParticlesPool;
			PoolMap<ParticleEmitter> mParticleEmitterPool;
			PoolMap<ParticleAffector> mParticleAffectorPool;
			PoolMap<ParticleSystem> mParticleSystemPool;
			PoolMap<ParticleTechnique> mParticleTechniquePool;

			/** Vectors used for deletion of created objects
		    */
			vector<VisualParticle*> mVisualParticles;
			vector<ParticleEmitter*> mEmitters;
			vector<ParticleAffector*> mAffectors;
			vector<ParticleTechnique*> mTechniques;
			vector<String> mSystems; // Use names instead of pointers to avoid problems during cleanup.

			/** Protected methods to increase the pools
		    */
			void _increaseVisualParticlePool(size_t size, Particle::ParticleBehaviourList& behaviours);
			void _increaseParticleEmitterPool(size_t size, Particle::ParticleBehaviourList& behaviours, ParticleTechnique* technique);
			void _increaseParticleAffectorPool(size_t size, Particle::ParticleBehaviourList& behaviours, ParticleTechnique* technique);
			void _increaseParticleTechniquePool(size_t size, Particle::ParticleBehaviourList& behaviours, ParticleSystem* system);
			void _increaseParticleSystemPool(size_t size, Particle::ParticleBehaviourList& behaviours, ParticleTechnique* technique);

			Particle* mLatestParticle;

		public:

			ParticlePool(void) : mLatestParticle(0){};
			virtual ~ParticlePool (void);

			/** 
			*/
			void setParentTechnique(ParticleTechnique* parentTechnique);

			/** 
			*/
			bool isEmpty(void);

			/** 
			*/
			bool isEmpty(const Particle::ParticleType particleType);

			/** 
			*/
			size_t getSize(void);

			/** 
			*/
			size_t getSize(const Particle::ParticleType particleType);

			/** 
		    */
			void initialisePool(void);

			/** 
		    */
			void increasePool (const Particle::ParticleType particleType, 
				size_t size,
				Particle::ParticleBehaviourList& behaviours,
				ParticleTechnique* technique);

			/** Destroy particles of a certain type
		    */
			void destroyParticles(const Particle::ParticleType particleType);
			void destroyAllVisualParticles(void);
			void destroyAllEmitterParticles(void);
			void destroyAllTechniqueParticles(void);
			void destroyAllAffectorParticles(void);
			void destroyAllSystemParticles(void);

			/** Releases a particle from the pool
		    */
			Particle* releaseParticle (const Particle::ParticleType particleType, const String& name);

			/** Releases all particles from the pool
		    */
			void releaseAllParticles (void);

			/** 
		    */
			void lockLatestParticle (void);

			/** Lock all particles in the pool
		    */
			void lockAllParticles (void);

			/** 
		    */
			void resetIterator(void);

			/** 
		    */
			Particle* getFirst(void);


			/** 
		    */
			Particle* getNext(void);

			/** 
		    */
			Particle* getFirst(const Particle::ParticleType particleType);


			/** 
		    */
			Particle* getNext(const Particle::ParticleType particleType);

			/** 
		    */
			bool end(void);

			/** 
		    */
			bool end(const Particle::ParticleType particleType);

			/** 
		    */
			Pool<VisualParticle>::PoolList& getVisualParticlesList(void)
			{
				return mVisualParticlesPool.getActiveElementsList();
			};
	};

}
#endif
