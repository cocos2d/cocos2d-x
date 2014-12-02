/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#include "ParticleUniversePCH.h"

#ifdef PU_PHYSICS_PHYSX

	#ifndef PARTICLE_UNIVERSE_EXPORTS
	#define PARTICLE_UNIVERSE_EXPORTS
	#endif

	#include "ParticleUniversePrerequisites.h"
	#include "Externs/ParticleUniversePhysXExtern.h"
	#include "Externs/ParticleUniversePhysXActorExtern.h"
	#include "Externs/ParticleUniversePhysXBridge.h"
	#include "Externs/ParticleUniversePhysXMath.h"

	namespace ParticleUniverse
	{
		//-----------------------------------------------------------------------
		PhysXActorExtern::PhysXActorExtern(void) : 
			PhysXExtern(), 
			mScene(0),
			mSynchronize(false),
			mTimeElapsedSynchronize(0.0f),
			mPhysicsShapeDesc(0),
			mPhysXParticles(0),
			mMaxParticles(0),
			mPhysXParticlesPointer(0),
			mStart(0)
		{
			// Set default physics shape
			mPhysicsShapeDesc = PU_NEW_T(PhysicsBoxDesc, MEMCATEGORY_SCENE_OBJECTS)();
		}
		//-----------------------------------------------------------------------
		PhysXActorExtern::~PhysXActorExtern(void)
		{
			// Force both the PhysX engine and the parent technique to expire all particles; this destroys all remaining actors.
			if(mParentTechnique)
			{
				mParentTechnique->_initAllParticlesForExpiration();
			}

			// Ignores unregistering if the PhysXActorExtern wasn´t registered in the first place.
			PhysXBridge::getSingletonPtr()->unRegisterPhysXExtern(this);

			if (mPhysicsShapeDesc)
			{
				PU_DELETE_T(mPhysicsShapeDesc, PhysicsShapeDesc, MEMCATEGORY_SCENE_OBJECTS);
			}
		}
		//-----------------------------------------------------------------------
		void PhysXActorExtern::setPhysicsShape(PhysicsShapeDesc* physicsShapeDesc)
		{
			if (mPhysicsShapeDesc)
			{
				PU_DELETE_T(mPhysicsShapeDesc, PhysicsShapeDesc, MEMCATEGORY_SCENE_OBJECTS);
			}

			switch (physicsShapeDesc->mPhysicsShapeType)
			{
				case ST_BOX:
				{
					PhysicsBoxDesc* physicsBoxDesc = static_cast<PhysicsBoxDesc*>(physicsShapeDesc);
					mPhysicsShapeDesc = PU_NEW_T(PhysicsBoxDesc, MEMCATEGORY_SCENE_OBJECTS)(*physicsBoxDesc);
				}
				break;

				case ST_SPHERE:
				{
					PhysicsSphereDesc* physicsSphereDesc = static_cast<PhysicsSphereDesc*>(physicsShapeDesc);
					mPhysicsShapeDesc = PU_NEW_T(PhysicsSphereDesc, MEMCATEGORY_SCENE_OBJECTS)(*physicsSphereDesc);
				}
				break;

				case ST_CAPSULE:
				{
					PhysicsCapsuleDesc* physicsCapsuleDesc = static_cast<PhysicsCapsuleDesc*>(physicsShapeDesc);
					mPhysicsShapeDesc = PU_NEW_T(PhysicsCapsuleDesc, MEMCATEGORY_SCENE_OBJECTS)(*physicsCapsuleDesc);
				}
				break;
			}
		}
		//-----------------------------------------------------------------------
		void PhysXActorExtern::_initParticleForEmission(Particle* particle)
		{
			if (particle->particleType != Particle::PT_VISUAL)
				return;
			
			VisualParticle* visualParticle = static_cast<VisualParticle*>(particle);
			PhysicsActorDesc physicsActorDesc;
			physicsActorDesc.position = particle->position;
			physicsActorDesc.direction = particle->direction;
			physicsActorDesc.mass = particle->mass;
			physicsActorDesc.orientation = visualParticle->orientation;
			physicsActorDesc.collisionGroup = mCollisionGroup;
			NxActorDesc actorDesc;
			
			// Use the particle dimensions. A particle is (for now) either a box or a sphere. Never a plane.
			switch (mPhysicsShapeDesc->mPhysicsShapeType)
			{
				case ST_BOX:
				{
					PhysicsBoxDesc* physicsBoxDesc = static_cast<PhysicsBoxDesc*>(mPhysicsShapeDesc);
					physicsBoxDesc->mDimensions = 0.5 * Vector3(visualParticle->width, visualParticle->height, visualParticle->depth);
				}
				break;

				case ST_SPHERE:
				{
					PhysicsSphereDesc* physicsSphereDesc = static_cast<PhysicsSphereDesc*>(mPhysicsShapeDesc);
					physicsSphereDesc->mRadius = 0.5f * visualParticle->width;
				}
				break;

				case ST_CAPSULE:
				{
					PhysicsCapsuleDesc* physicsCapsuleDesc = static_cast<PhysicsCapsuleDesc*>(mPhysicsShapeDesc);
					physicsCapsuleDesc->mRadius = 0.5f * visualParticle->width;
					physicsCapsuleDesc->mHeight = 0.5f * visualParticle->height;
				}
				break;
			}

			PhysicsActor* actor = createPhysicsActor(&physicsActorDesc, mPhysicsShapeDesc);
			particle->physicsActor = actor;
			(static_cast<PhysXActor*>(actor))->nxActor->userData = particle; // So particles and actors refer to each other
		}
		//-----------------------------------------------------------------------
		void PhysXActorExtern::_initParticleForExpiration(Particle* particle)
		{
			destroyPhysicsActor(particle->physicsActor);
			particle->physicsActor = 0;
		}
		//-----------------------------------------------------------------------
		PhysicsActor* PhysXActorExtern::createPhysicsActor(PhysicsActorDesc* physicsActorDesc, PhysicsShapeDesc* physicsShapeDesc)
		{
			if (!PhysXBridge::getSingletonPtr()->getScene() || !physicsActorDesc || !physicsShapeDesc)
				return 0;

			NxBodyDesc bodyDesc;
			bodyDesc.setToDefault();
			NxReal angularDamping = bodyDesc.angularDamping;
			NxVec3 angularVelocity = bodyDesc.angularVelocity;
			NxVec3 linearVelocity = bodyDesc.linearVelocity;
			bodyDesc.angularDamping = physicsShapeDesc->mAngularDamping;
			bodyDesc.angularVelocity = PhysXMath::convert(physicsShapeDesc->mAngularVelocity);
			bodyDesc.linearVelocity = PhysXMath::convert(physicsActorDesc->direction);

			NxActorDesc actorDesc;
			NxActorDesc defaultActorDesc;
			actorDesc.setToDefault();
			defaultActorDesc.setToDefault();
			switch (physicsShapeDesc->mPhysicsShapeType)
			{
				case ST_BOX:
				{
					PhysicsBoxDesc* physicsBoxDesc = static_cast<PhysicsBoxDesc*>(physicsShapeDesc);
					NxBoxShapeDesc boxDesc;
					boxDesc.setToDefault();
					boxDesc.dimensions = PhysXMath::convert(physicsBoxDesc->mDimensions);
					boxDesc.group = physicsBoxDesc->mCollisionGroup;
					boxDesc.groupsMask = PhysXMath::convert(physicsBoxDesc->mGroupMask);
					boxDesc.materialIndex = physicsBoxDesc->mMaterialIndex;
					actorDesc.density = NxComputeBoxDensity(2 * boxDesc.dimensions, physicsActorDesc->mass);
					actorDesc.shapes.pushBack(&boxDesc);
				}
				break;

				case ST_SPHERE:
				{
					PhysicsSphereDesc* physicsSphereDesc = static_cast<PhysicsSphereDesc*>(physicsShapeDesc);
					NxSphereShapeDesc sphereDec;
					sphereDec.setToDefault();
					sphereDec.radius = physicsSphereDesc->mRadius;
					sphereDec.group = physicsSphereDesc->mCollisionGroup;
					sphereDec.groupsMask = PhysXMath::convert(physicsSphereDesc->mGroupMask);
					sphereDec.materialIndex = physicsSphereDesc->mMaterialIndex;
					actorDesc.density = NxComputeSphereDensity(sphereDec.radius, physicsActorDesc->mass);
					actorDesc.shapes.pushBack(&sphereDec);
				}
				break;

				case ST_CAPSULE:
				{
					PhysicsCapsuleDesc* physicsCapsuleDesc = static_cast<PhysicsCapsuleDesc*>(physicsShapeDesc);
					NxCapsuleShapeDesc capsuleDec;
					capsuleDec.setToDefault();
					capsuleDec.radius = physicsCapsuleDesc->mRadius;
					capsuleDec.height = physicsCapsuleDesc->mHeight;
					capsuleDec.group = physicsCapsuleDesc->mCollisionGroup;
					capsuleDec.groupsMask = PhysXMath::convert(physicsCapsuleDesc->mGroupMask);
					capsuleDec.materialIndex = physicsCapsuleDesc->mMaterialIndex;
					actorDesc.density = NxComputeCylinderDensity(capsuleDec.radius, capsuleDec.height, physicsActorDesc->mass);
					actorDesc.shapes.pushBack(&capsuleDec);
				}
				break;
			}
			actorDesc.globalPose.t = PhysXMath::convert(physicsActorDesc->position);
			actorDesc.body = &bodyDesc;
			actorDesc.group = physicsActorDesc->collisionGroup;
			PhysXActor* physXActor = 0;
			if (!actorDesc.isValid())
			{
				actorDesc = defaultActorDesc;
				LogManager::getSingleton().logMessage("ParticleUniverse PhysXActor: Cannot create actor; use default attributes.");
			}
			NxActor* nxActor = PhysXBridge::getSingletonPtr()->getScene()->createActor(actorDesc);

			if (nxActor)
			{
				physXActor = PU_NEW_T(PhysXActor, MEMCATEGORY_SCENE_OBJECTS)();
				physXActor->position = PhysXMath::convert(nxActor->getGlobalPosition());
				physXActor->direction = PhysXMath::convert(nxActor->getLinearVelocity());
				nxActor->setGlobalOrientationQuat(PhysXMath::convert(physicsActorDesc->orientation));
				physXActor->orientation = physicsActorDesc->orientation;
				physXActor->mass = nxActor->getMass();
				physXActor->collisionGroup = nxActor->getGroup();
				physXActor->nxActor = nxActor;
			}
			return physXActor;
		}
		//-----------------------------------------------------------------------
		void PhysXActorExtern::destroyPhysicsActor(PhysicsActor* physicsActor)
		{
			if (!physicsActor)
				return;

			if (!PhysXBridge::getSingletonPtr()->getScene())
				return;

			NxActor* nxActor = (static_cast<PhysXActor*>(physicsActor))->nxActor;
			PhysXBridge::getSingletonPtr()->getScene()->releaseActor(*nxActor);
			PU_DELETE_T(physicsActor, PhysicsActor, MEMCATEGORY_SCENE_OBJECTS); // Watch the PhysicsActor type instead of PhysXActor!
		}
		//-----------------------------------------------------------------------
		void PhysXActorExtern::_prepare(ParticleTechnique* technique)
		{
			// Register the PhysXActorExtern to the PhysXBridge
			PhysXBridge::getSingletonPtr()->registerPhysXExtern(this);
		}
		//-----------------------------------------------------------------------
		void PhysXActorExtern::_unprepare(ParticleTechnique* technique)
		{
			// Todo
		}
		//-----------------------------------------------------------------------
		void PhysXActorExtern::synchronize(Real timeElapsed)
		{
			// Is set by the PhysXBridge as soon as a new simulation has been done.
			mSynchronize = true;
			mTimeElapsedSynchronize = timeElapsed;
		}
		//-----------------------------------------------------------------------
		void PhysXActorExtern::_processParticle(
			ParticleTechnique* particleTechnique, 
			Particle* particle, 
			Real timeElapsed, 
			bool firstParticle)
		{
			// Only update after a PhysX simulation step
			if (mSynchronize)
			{
				if (particle->particleType != Particle::PT_VISUAL)
					return;

				if (!particle->physicsActor)
					return;

				VisualParticle* visualParticle = static_cast<VisualParticle*>(particle);
				PhysXActor* physXActor = static_cast<PhysXActor*>(particle->physicsActor);
				NxActor* nxActor = physXActor->nxActor;
				if (nxActor)
				{
					// Synchronize both the particle and the pysicsActor with the nxActor
					particle->position = PhysXMath::convert(nxActor->getGlobalPosition());
					particle->direction = PhysXMath::convert(nxActor->getLinearVelocity());
					visualParticle->orientation = PhysXMath::convert(nxActor->getGlobalOrientationQuat());
					physXActor->position = particle->position;
					physXActor->direction = particle->direction;
					physXActor->orientation = visualParticle->orientation;

					if (nxActor->getNbShapes())
					{
						NxShape *shape = nxActor->getShapes()[0]; // Max one.
						switch(shape->getType())
						{
							case NX_SHAPE_BOX:
								(static_cast<NxBoxShape*>(shape))->setDimensions(
									PhysXMath::convert(0.5 * Vector3(
									visualParticle->width, visualParticle->height, visualParticle->depth)));
							break;
							 case NX_SHAPE_SPHERE:
								(static_cast<NxSphereShape*>(shape))->setRadius(0.5f * visualParticle->width);
							break;
							case NX_SHAPE_CAPSULE:
							{
								(static_cast<NxCapsuleShape*>(shape))->setRadius(0.5f * visualParticle->width);
								(static_cast<NxCapsuleShape*>(shape))->setHeight(0.5f * visualParticle->height);
							}
							break;
						}
					}
				}
			}
		}
		//-----------------------------------------------------------------------
		void PhysXActorExtern::_postProcessParticles(ParticleTechnique* technique, Real timeElapsed)
		{
			// Reset synchronization flag.
			mSynchronize = false;
		}
		//-----------------------------------------------------------------------
		void PhysXActorExtern::copyAttributesTo (Extern* externObject)
		{
			Extern::copyAttributesTo(externObject);
			PhysXActorExtern* physXActorExtern = static_cast<PhysXActorExtern*>(externObject);
	
			// Copy attributes
			physXActorExtern->setPhysicsShape(mPhysicsShapeDesc);
			physXActorExtern->setCollisionGroup(mCollisionGroup);
		}
	}

#endif //PU_PHYSICS_PHYSX