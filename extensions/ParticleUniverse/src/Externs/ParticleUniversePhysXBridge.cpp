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
	#include "Externs/ParticleUniversePhysXBridge.h"
	#include "Externs/ParticleUniversePhysXLogging.h"
	#include "Externs/ParticleUniversePhysXExtern.h"
    #include "Externs/ParticleUniversePhysXMath.h"
	#include "ParticleUniverseControllerManager.h"
	#include "ParticleUniverseController.h"

	template<> ParticleUniverse::PhysXBridge* ParticleUniverse::Singleton<ParticleUniverse::PhysXBridge>::msSingleton = 0;

	namespace ParticleUniverse
	{
		// Static members
		NxPhysicsSDK* PhysXBridge::mPhysicsSDK = 0;
		NxScene* PhysXBridge::mScene = 0;

		//-----------------------------------------------------------------------
		void PhysXContactReport::onContactNotify(NxContactPair& pair, NxU32 events)
		{
			/** Iterate through the actors.
			*/
			NxContactStreamIterator i(pair.stream);
			while(i.goNextPair())
			{
				while(i.goNextPatch())
				{
					while(i.goNextPoint())
					{
						PhysXBridge::getSingletonPtr()->onContactNotify(pair, events, i.getPoint());
					}
				}
			}
		}
		//-----------------------------------------------------------------------
		//-----------------------------------------------------------------------
		//-----------------------------------------------------------------------
		class PhysXBridgeUpdateValue : public ControllerValue<Real>
		{
			protected:
				PhysXBridge* mTarget;
		
			public:
				PhysXBridgeUpdateValue(PhysXBridge* target) : mTarget(target) {}
				
				Real getValue(void) const {return 0;}
				void setValue(Real value) {mTarget->_update(value);}
		};
		//-----------------------------------------------------------------------
		//-----------------------------------------------------------------------
		//-----------------------------------------------------------------------
		PhysXBridge::PhysXBridge(void) :
			mTimeController(0),
			mTimeSinceLastSimulation(0),
			mPlaneActor(0)
		{
		}
		//-----------------------------------------------------------------------
		PhysXBridge::~PhysXBridge(void)
		{
		}
		//-----------------------------------------------------------------------
		bool PhysXBridge::initNx(Real gravityY)
		{
			if (!mPhysicsSDK)
			{
				// Initialize PhysicsSDK
				NxPhysicsSDKDesc desc;
				NxSDKCreateError errorCode = NXCE_NO_ERROR;
				mPhysicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, 0, new PhysXLogging(), desc, &errorCode);
				if(!mPhysicsSDK) 
				{
					EXCEPT(Exception::ERR_INTERNAL_ERROR, "PU: Cannot initialise the PhysX SDK.", "PhysXBridge::initNx");
				}

				mPhysicsSDK->setParameter(NX_SKIN_WIDTH, 0.05f);
			}

			// Create a scene
			if (!mScene)
			{
				NxSceneDesc sceneDesc;
				sceneDesc.gravity = NxVec3(0.0f, gravityY, 0.0f);
				mScene = mPhysicsSDK->createScene(sceneDesc);
				if(!mScene)
				{
					EXCEPT(Exception::ERR_INTERNAL_ERROR, "PU: Cannot create a PhysX Scene.", "PhysXBridge::initNx");
				}

				// Set the contact report
				mScene->setUserContactReport(&mPhysXContactReport);

				// Set default material
				NxMaterial* defaultMaterial = mScene->getMaterialFromIndex(0);
				defaultMaterial->setRestitution(0.0f);
				defaultMaterial->setStaticFriction(0.5f);
				defaultMaterial->setDynamicFriction(0.5f);

				// Create ground plane
				createPlane();
			}

			// Create a controller
			ControllerManager& controllerManager = ControllerManager::getSingleton(); 
			ControllerValueRealPtr physXBridgeUpdateValue(PU_NEW PhysXBridgeUpdateValue(this));
			mTimeController = controllerManager.createFrameTimePassthroughController(physXBridgeUpdateValue);

			return true;
		}
		//-----------------------------------------------------------------------
		void PhysXBridge::_update(Real timeElapsed)
		{
			if (!mScene)
				return;

			// Simulate the PhysX scene every x seconds
			mTimeSinceLastSimulation += timeElapsed;
			while (mTimeSinceLastSimulation > SIMULATION_INTERVAL)
			{
				// Simulate with SIMULATION_INTERVAL
				mScene->simulate(SIMULATION_INTERVAL);

				// Fetch simulation results
				mScene->flushStream();
				mScene->fetchResults(NX_RIGID_BODY_FINISHED, true);

				// Broadcast to registered PhysXExterns
				synchronize(SIMULATION_INTERVAL);
				mTimeSinceLastSimulation -= SIMULATION_INTERVAL;
			}
		}
		//-----------------------------------------------------------------------
		bool PhysXBridge::exitNx(void)
		{
			if(mPhysicsSDK)
			{
				if(mScene)
				{
					// Delete the scene
					mPhysicsSDK->releaseScene(*mScene);
				}
				mScene = 0;

				// Delete the SDK
				NxReleasePhysicsSDK(mPhysicsSDK);
				mPhysicsSDK = 0;
				
				// Delete the controller
				if (mTimeController)
				{
					ControllerManager::getSingleton().destroyController(mTimeController);
					mTimeController = 0;
				}
				
				return true;
			}
			
			return false;
		}
		//-----------------------------------------------------------------------
		void PhysXBridge::synchronize(Real timeElapsed)
		{
			// Call to the synchronize() function of all registered PhysicsExterns
			vector<PhysXExtern*>::iterator it;
			vector<PhysXExtern*>::iterator itEnd = mExternList.end();
			for (it = mExternList.begin(); it != itEnd; ++it)
			{
				(*it)->synchronize(timeElapsed);
			}
		}
		//-----------------------------------------------------------------------
		NxScene* PhysXBridge::getScene(void) const
		{
			return mScene;
		}
		//-----------------------------------------------------------------------
		void PhysXBridge::setScene(NxScene* scene)
		{
			mScene = scene;
		}
		//-----------------------------------------------------------------------
		void PhysXBridge::createPlane(const Vector3& normal, Real d)
		{
			if (mScene)
			{
				if (mPlaneActor)
				{
					mScene->releaseActor(*mPlaneActor);
				}
				NxPlaneShapeDesc planeDesc;
				planeDesc.d = d;
				planeDesc.normal = PhysXMath::convert(normal);
				NxActorDesc actorDesc;
				actorDesc.shapes.pushBack(&planeDesc);
				mPlaneActor = mScene->createActor(actorDesc);
			}
		}
		//-----------------------------------------------------------------------
		void PhysXBridge::getGravity(Vector3& gravity)
		{
			gravity = Vector3::ZERO;
			if (mScene)
			{
				NxVec3 g = PhysXMath::convert(gravity);
				mScene->getGravity(g);
				gravity = PhysXMath::convert(g);
			}
		}
		//-----------------------------------------------------------------------
		void PhysXBridge::setGravity(const Vector3& gravity)
		{
			if (mScene)
			{
				mScene->setGravity(PhysXMath::convert(gravity));
			}
		}
		//-----------------------------------------------------------------------
		bool PhysXBridge::onContactNotify(NxContactPair& pair, NxU32 events, NxVec3 contactPoint)
		{
			Particle* p0 = 0;
			Particle* p1 = 0;
			bool collision = false;

			/** Only actors with collisiongroups that are associated with particles and have userData attached are taken into account.
			*/

			if (!pair.isDeletedActor[0] && pair.actors[0]->userData)
			{
				if (isRegisteredCollisionGroup(pair.actors[0]->getGroup()))
				{
					// First check whether it is a particle
					p0 = static_cast<Particle*>(pair.actors[0]->userData);
					if (typeid(p0) == typeid(Particle*))
					{
						p0->addEventFlags(Particle::PEF_COLLIDED);
						collision = true;
						if (p0->physicsActor)
						{
							p0->physicsActor->contactPoint = PhysXMath::convert(contactPoint);
							p0->physicsActor->contactNormal = (PhysXMath::convert(contactPoint)- p0->position);
							p0->physicsActor->contactNormal.normalise();
						}
					}
				}
			}
			if (!pair.isDeletedActor[1] && pair.actors[1]->userData)
			{
				if (isRegisteredCollisionGroup(pair.actors[1]->getGroup()))
				{
					// First check whether it is a particle
					p1 = static_cast<Particle*>(pair.actors[1]->userData);
					if (typeid(p1) == typeid(Particle*))
					{
						p1->addEventFlags(Particle::PEF_COLLIDED);
						collision = true;
						if (p1->physicsActor)
						{
							p1->physicsActor->contactPoint = PhysXMath::convert(contactPoint);
							p1->physicsActor->contactNormal = (PhysXMath::convert(contactPoint)- p1->position);
							p1->physicsActor->contactNormal.normalise();
						}
					}
				}
			}
			return collision;
		}
		//-----------------------------------------------------------------------
		void PhysXBridge::registerPhysXExtern(PhysXExtern* physXExtern)
		{
			if (physXExtern)
			{
				mExternList.push_back(physXExtern);
			}
		}
		//-----------------------------------------------------------------------
		void PhysXBridge::unRegisterPhysXExtern(PhysXExtern* physXExtern)
		{
			vector<PhysXExtern*>::iterator it;
			vector<PhysXExtern*>::iterator itEnd = mExternList.end();
			for (it = mExternList.begin(); it != itEnd; ++it)
			{
				if (*it == physXExtern)
				{
					// Remove it
					mExternList.erase(it);
					break;
				}
			}
		}
		//-----------------------------------------------------------------------
		bool PhysXBridge::isRegisteredCollisionGroup(uint16 collisionGroup)
		{
			vector<PhysXExtern*>::iterator it;
			vector<PhysXExtern*>::iterator itEnd = mExternList.end();
			for (it = mExternList.begin(); it != itEnd; ++it)
			{
				if (collisionGroup == (*it)->getCollisionGroup())
				{
					return true;
				}
			}
			return false;
		}
		//-----------------------------------------------------------------------
		PhysXBridge* PhysXBridge::getSingletonPtr(void)
		{
			return msSingleton;
		}
		//-----------------------------------------------------------------------
		PhysXBridge& PhysXBridge::getSingleton(void)
		{
			assert( msSingleton );  return ( *msSingleton );
		}

	}
#endif //PU_PHYSICS_PHYSX