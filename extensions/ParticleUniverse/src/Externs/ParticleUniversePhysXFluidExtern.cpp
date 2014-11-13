/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode
Special thanks to: M. Geissler

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#include "ParticleUniversePCH.h"

#ifdef PU_PHYSICS_PHYSX

	#ifndef PARTICLE_UNIVERSE_EXPORTS
	#define PARTICLE_UNIVERSE_EXPORTS
	#endif

	#include "Externs/ParticleUniversePhysXFluidExtern.h"
	#include "Externs/ParticleUniversePhysXBridge.h"
	#include "Externs/ParticleUniversePhysXMath.h"
	#include "ParticleUniverseTechnique.h"

	namespace ParticleUniverse
	{
		//-----------------------------------------------------------------------
		PhysXFluidExtern::PhysXFluidExtern(void) : 
			PhysXExtern(), 
			mSynchronize(false),
			mFluid(0),
			mPhysXFluidParticles(0),
			mMaxParticles(0),
			mNumAliveParticles(0),
			mPUParticles(0),
			mCreatedParticlesID(0),
			mNumCreatedParticles(0),
			mDeletedParticlesID(0),
			mNumDeletedParticles(0)
		{
			// Set default fluid settings
			mFluidDesc.setToDefault();
		}

		//-----------------------------------------------------------------------
		PhysXFluidExtern::~PhysXFluidExtern(void)
		{
			// Force both the PhysX engine and the parent technique to expire all particles; this destroys all remaining actors.
			if (mParentTechnique)
			{
				mParentTechnique->_initAllParticlesForExpiration();
			}

			// Ignores unregistering if the PhysXExtern wasn´t registered in the first place.
			PhysXBridge::getSingletonPtr()->unRegisterPhysXExtern(this);

			// Destroy fluid
			destroyFluid();
		}

		//-----------------------------------------------------------------------
		void PhysXFluidExtern::_notifyStop (void)
		{
			if (mFluid)
			{
				mFluid->removeAllParticles();
			}

			// PU should handle the deletion of the particle objects.
			// So just set the pointers to NULL
			if (mPUParticles)
			{
				for (NxU32 p=0; p<mMaxParticles; p++)
				{
					mPUParticles[p] = 0;
				}
			}
		}

		//-----------------------------------------------------------------------
		void PhysXFluidExtern::_initParticleForEmission(Particle* particle)
		{
			// Delete the dead particles. Needed to clear the mPUParticles before assigning a new link
			// if we don't do this here (before creating a particle) then this will be done after in the process function.
			// So if a PhysX particle at index 2 died, when you call addParticle it will return index 2 and we will set a pointer there for the link
			// But then in the process function we will read which particles died (from mDeletedParticlesID), we will read 2, and remove this link even though we have a new particle there!
			processPhysXDeletionIDBuffer();

			// Create a PhysX fluid particle and link it to a created PU particle
			createPhysXFluidParticle(particle);
		}

		//-----------------------------------------------------------------------
		void PhysXFluidExtern::_initParticleForExpiration(Particle* particle)
		{
		}

		//-----------------------------------------------------------------------
		void PhysXFluidExtern::processPhysXDeletionIDBuffer()
		{
			for (unsigned int p=0; p<mNumDeletedParticles; p++) 
			{
				// Kill the PU particle (just in case the timers between PhysX particle and PU particle are not 100% syncronized).
				// Also we need to do this in case the PhysX particle died prematurely (by hitting a drain).
				// Also check if this particle has already been unlinked before.
				if (mPUParticles[mDeletedParticlesID[p]]) 
				{
					// Kill the particle
					mPUParticles[mDeletedParticlesID[p]]->addEventFlags(Particle::PEF_EXPIRED);
					//mPUParticles[mDeletedParticlesID[p]]->timeToLive = 0;
				}

				// Reset the link
				mPUParticles[mDeletedParticlesID[p]] = 0;
			}
			// We killed all particles, no more to kill
			mNumDeletedParticles = 0;
		}

		//-----------------------------------------------------------------------
		void PhysXFluidExtern::createFluid(const NxFluidDesc& nxFluidDesc)
		{
			mFluidDesc = nxFluidDesc;
			createFluid();
		}

		//-----------------------------------------------------------------------
		void PhysXFluidExtern::createFluid(void)
		{
			// Destroy the fluid just in case
			destroyFluid();

			// Test if we have hardware support, and if we don't make sure that the hardware flag in the fluid descriptor is set to false
			if (PhysXBridge::getSingletonPtr()->getScene()->getPhysicsSDK().getHWVersion() == NX_HW_VERSION_NONE && (mFluidDesc.flags & NX_FF_HARDWARE))
			{
				mFluidDesc.flags &= ~NX_FF_HARDWARE;
				LogManager::getSingleton().logMessage("ParticleUniverse PhysXFluid: PhysX hardware is not present. Overriding the PhysX Fluid settings to use software mode.");
			}

			// Test the validity of the fluid
			if (!mFluidDesc.isValid()) 
			{
				// Since the fluid is invalid, reset it to the original value
				mFluidDesc.setToDefault();

				// And throw an exception
				EXCEPT(Exception::ERR_INVALIDPARAMS, "Invalid PhysX fluid parameters.", "PhysXFluidExtern::createFluid");
			}

			//////////////////////////////////////////////////////////////////////////
			mMaxParticles = static_cast<NxU32>(mParentTechnique->getVisualParticleQuota());

			mPhysXFluidParticles = PU_NEW_ARRAY_T(ParticleStructure, mMaxParticles, MEMCATEGORY_SCENE_OBJECTS);

			// Initialize the PU particles
			mPUParticles = PU_NEW_ARRAY_T(Particle*, mMaxParticles, MEMCATEGORY_SCENE_OBJECTS);
			for (NxU32 p=0; p<mMaxParticles; p++)
			{
				mPUParticles[p] = 0;
			}

			// Initialize the creation ID write buffer
			mCreatedParticlesID = PU_NEW_ARRAY_T(NxU32, mMaxParticles, MEMCATEGORY_SCENE_OBJECTS); 

			// Initialize the deletion ID write buffer
			mDeletedParticlesID = PU_NEW_ARRAY_T(NxU32, mMaxParticles, MEMCATEGORY_SCENE_OBJECTS); 

			//////////////////////////////////////////////////////////////////////////
			NxParticleData particleWriteData;
			particleWriteData.numParticlesPtr = &mNumAliveParticles;
			particleWriteData.bufferPos = &mPhysXFluidParticles[0].position.x;
			particleWriteData.bufferPosByteStride = sizeof(ParticleStructure);
			particleWriteData.bufferVel = &mPhysXFluidParticles[0].velocity.x;
			particleWriteData.bufferVelByteStride = sizeof(ParticleStructure);
			particleWriteData.bufferLife = &mPhysXFluidParticles[0].lifetime;
			particleWriteData.bufferLifeByteStride = sizeof(ParticleStructure);
			particleWriteData.bufferFlag = &mPhysXFluidParticles[0].bufferFlag;
			particleWriteData.bufferFlagByteStride = sizeof(ParticleStructure);
			particleWriteData.bufferDensity = &mPhysXFluidParticles[0].density;
			particleWriteData.bufferDensityByteStride = sizeof(ParticleStructure);
			particleWriteData.bufferId = &mPhysXFluidParticles[0].id;
			particleWriteData.bufferIdByteStride = sizeof(ParticleStructure);

			//////////////////////////////////////////////////////////////////////////
			mCreationIDWriteData.bufferId = mCreatedParticlesID;
			mCreationIDWriteData.bufferIdByteStride = sizeof(NxU32);
			mCreationIDWriteData.numIdsPtr = &mNumCreatedParticles;
			mFluidDesc.particleCreationIdWriteData = mCreationIDWriteData;

			mDeletionIDWriteData.bufferId = mDeletedParticlesID;
			mDeletionIDWriteData.bufferIdByteStride = sizeof(NxU32);
			mDeletionIDWriteData.numIdsPtr = &mNumDeletedParticles;
			mFluidDesc.particleDeletionIdWriteData = mDeletionIDWriteData;

			//////////////////////////////////////////////////////////////////////////
			mFluidDesc.particlesWriteData = particleWriteData;
			mFluidDesc.maxParticles = mMaxParticles;
			mFluidDesc.collisionGroup = mCollisionGroup;

			//////////////////////////////////////////////////////////////////////////
			// Create the fluid
			mFluid = PhysXBridge::getSingletonPtr()->getScene()->createFluid(mFluidDesc);
			if (!mFluid)
			{
				EXCEPT(Exception::ERR_INTERNAL_ERROR, "PU: Cannot create the PhysX fluid.", "PhysXFluidExtern::createFluid");
			}
		}

		//-----------------------------------------------------------------------
		void PhysXFluidExtern::destroyFluid(void)
		{
			if (mFluid)
			{
				// Delete mFluid: The PhysX scene must still exist
				if (PhysXBridge::getSingletonPtr()->getScene())
				{
					PhysXBridge::getSingletonPtr()->getScene()->releaseFluid(*mFluid);
				}
				mFluid = 0;
			}

			if (mPhysXFluidParticles)
			{
				// Delete mPhysXFluidParticles
				PU_DELETE_ARRAY_T(mPhysXFluidParticles, ParticleStructure, mMaxParticles, MEMCATEGORY_SCENE_OBJECTS);
				mPhysXFluidParticles = 0;
			}

			if (mCreatedParticlesID)
			{
				// Delete mPhysXFluidParticles
				PU_DELETE_ARRAY_T(mCreatedParticlesID, NxU32, mMaxParticles, MEMCATEGORY_SCENE_OBJECTS);
				mCreatedParticlesID = 0;
			}

			if (mDeletedParticlesID)
			{
				// Delete mPhysXFluidParticles
				PU_DELETE_ARRAY_T(mDeletedParticlesID, NxU32, mMaxParticles, MEMCATEGORY_SCENE_OBJECTS);
				mDeletedParticlesID = 0;
			}

			// Delete the PU particles from the array
			if (mPUParticles)
			{
				// PU should be responsible for deleting particle objects,
				// so just delete the particle array itself
				//::Ogre::CategorisedAllocPolicy<MEMCATEGORY_SCENE_OBJECTS>::deallocateBytes((void*)mPUParticles);
				PU_DELETE_ARRAY_BYTES(mPUParticles, MEMCATEGORY_SCENE_OBJECTS);
				mPUParticles = 0;
			}
		}

		//-----------------------------------------------------------------------
		PhysicsActor* PhysXFluidExtern::createPhysXFluidParticle(Particle* particle)
		{
			NxParticleData nxParticleData;

			NxU32 particleNum = 1;
			nxParticleData.numParticlesPtr = &particleNum;
			nxParticleData.bufferPos = (float*)&(particle->position).x;
			nxParticleData.bufferPosByteStride = sizeof(ParticleStructure);
			nxParticleData.bufferVel = (float*)&(particle->direction).x;
			nxParticleData.bufferVelByteStride = sizeof(ParticleStructure);
			nxParticleData.bufferLife = (float*)&particle->timeToLive;
			nxParticleData.bufferLifeByteStride = sizeof(ParticleStructure);
			nxParticleData.bufferFlag = 0;
			nxParticleData.bufferFlagByteStride = sizeof(ParticleStructure);
			if (mFluid)
			{
				NxF32 density = NxComputeSphereDensity(mFluid->getKernelRadiusMultiplier(), particle->mass);
				nxParticleData.bufferDensity = &density;
			}
			nxParticleData.bufferDensityByteStride = sizeof(ParticleStructure);

			particle->physicsActor = 0;

			// Try to create the PhysX fluid particle
			if (mFluid->addParticles(nxParticleData) == 1)
			{	
				// We should only create one particle
				if (mNumCreatedParticles != 1) EXCEPT(Exception::ERR_INVALIDPARAMS, "Particle created, but the number of particles in mCreatedParticlesID is " + mNumCreatedParticles, "PhysXFluidExtern::createPhysicsActor");

				// If the previous particle with the same index didn't die, kill it first.
				// This can happen because the PhysX fluid particle and PU particle have their own timers for timeToLive nad they might not be 100% syncronized
				if (mPUParticles[mCreatedParticlesID[0]] != 0)
				{
					mPUParticles[mCreatedParticlesID[0]]->timeToLive = 0;
				}

				// Set the link to the new particle
				mPUParticles[mCreatedParticlesID[0]] = particle;
			}
			else  // We could not create the PhysX particle. The fluid is full
				// Kill the PU particle
				particle->timeToLive = 0;

			particle->direction = Vector3::ZERO; // Reset, because the direction must be recalculated by the fluid
			return particle->physicsActor;
		}

		//-----------------------------------------------------------------------
		void PhysXFluidExtern::_prepare(ParticleTechnique* technique)
		{
			// Register the PhysXFluidExtern to the PhysXBridge
			PhysXBridge::getSingletonPtr()->registerPhysXExtern(this);

			// Create the fluid
			createFluid();
		}

		//-----------------------------------------------------------------------
		void PhysXFluidExtern::synchronize(Real timeElapsed)
		{
			// Set a flag that we want to update PU particles based on the PhysX particles
			mSynchronize = true;
		}
		//-----------------------------------------------------------------------
		void PhysXFluidExtern::_preProcessParticles(ParticleTechnique* technique, Real timeElapsed)
		{
			if (mSynchronize)
			{
				processPhysXDeletionIDBuffer();
			}
		}

		//-----------------------------------------------------------------------
		void PhysXFluidExtern::_processParticle(ParticleTechnique* particleTechnique,
												Particle* particle,
												Real timeElapsed,
												bool firstParticle)
		{
			// Fluids are updated in the _postProcessParticles() function)
		}

		//-----------------------------------------------------------------------
		void PhysXFluidExtern::_postProcessParticles(ParticleTechnique* technique, Real timeElapsed)
		{
			// Only update after a PhysX simulation step
			if (mSynchronize)
			{
				// Run through particle fluid buffer
				NxU32 index;	// this will store the ID carried by each PhysX particle
				// Run through all non-expired particles. mNumAliveParticles is set by PhysX
				for (NxU32 i = 0; i < mNumAliveParticles; ++i)
				{		
					index = mPhysXFluidParticles[i].id;
					// If there doesn't exists a Particle Universe particle link for this ID, skip this ID
					if (!mPUParticles[index])
					{
						continue;
					}

					// Sync the position and the velocity of the particles
					mPUParticles[index]->position = PhysXMath::convert(mPhysXFluidParticles[i].position);
					mPUParticles[index]->direction = PhysXMath::convert(mPhysXFluidParticles[i].velocity);
				}	// for		
			}

			// Reset synchronization flag.
			mSynchronize = false;
		}

		//-----------------------------------------------------------------------
		void PhysXFluidExtern::copyAttributesTo (Extern* externObject)
		{
			Extern::copyAttributesTo(externObject);
			PhysXFluidExtern* physXFluidExtern = static_cast<PhysXFluidExtern*>(externObject);

			// Copy attributes
			physXFluidExtern->mFluidDesc = mFluidDesc;
		}
	}

#endif //PU_PHYSICS_PHYSX
