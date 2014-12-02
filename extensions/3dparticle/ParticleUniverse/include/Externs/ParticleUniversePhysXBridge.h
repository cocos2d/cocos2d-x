/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PHYSX_LOADER_H__
#define __PU_PHYSX_LOADER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseController.h"

#ifdef PU_PHYSICS_PHYSX
	#include "NxPhysics.h"

	namespace ParticleUniverse
	{
		// Predeclared classes
		class PhysXExtern;

		// Constants
		static const Real SIMULATION_INTERVAL = 0.02f;

		/** The PhysXContactReport is needed to detect collision of particles.
		*/
		class _ParticleUniverseExport PhysXContactReport : public NxUserContactReport
		{        
			void onContactNotify(NxContactPair& pair, NxU32 events);
		};
		/////////////////////////////////////////////////////////////////////////////

		/** The PhysXBridge is the class with which all PhysXExterns communicate. The PhysXBridge is also used in the client application. The
			client application is the application that uses the Particle Universe plugin and is usually the application that initialises the 
			PhysX engine. The PhysXBridge can also be used as a test class that initialises the PhysX engine itself.
		*/
		class _ParticleUniverseExport PhysXBridge : public Singleton<PhysXBridge>
		{
			public:
				PhysXBridge(void);
				virtual ~PhysXBridge(void);

				/** Initialise the PhysX engine. This is needed for test purposes, because it is usually done outside of the Particle
					Universe plugin.
				*/
				bool initNx(Real gravityY = -100);

				/** Update the bridge class, so it is capable to simulate the scene. Only for test purposes.
				*/
				void _update(Real timeElapsed);

				/** Shutdown the PhysX engine. Only for test purposes.
				*/
				bool exitNx(void);

				/** Assume that simulation is done outside the Particle Universe plugin. Every time a new simulation step has been done,
					the synchronize() function is called, which performs a callback on all registered PhysXExterns, indicating that the 
					particle attributes and actor attributes have to be synchronized.
				*/
				void synchronize(Real timeElapsed);

				/** Return the PhysX scene.
				*/
				NxScene* getScene(void) const;

				/** Although it is possible to create a PhysX scene with the PhysXLoad class, it is usually done in the client application that
					uses Particle Universe. The created scene can be set using this function.
				*/
				void setScene(NxScene* scene);

				/** Create a plane that is used for testing purposes.
				*/
				void createPlane(const Vector3& normal = Vector3::ZERO, Real d = -200);

				/** Return the gravity of the PhysX scene.
				*/
				void getGravity(Vector3& gravity);

				/** Set the gravity of the PhysX scene.
				*/
				void setGravity(const Vector3& gravity);

				/** This function must be called from the PhysXContactReport if the PhysXContactReport::onContactNotify() function is 
					executed. The PhysXBridge will determine whether the collision groups of the actor pair are related to Particle Universe
					particles.
				*/
				bool onContactNotify(NxContactPair& pair, NxU32 events, NxVec3 contactPoint);

				/** PhysXExterns have to register themselves to the PhysXBridge.
				*/
				void registerPhysXExtern(PhysXExtern* physXExtern);

				/** PhysXExtern also have to be unregistered again.
				*/
				void unRegisterPhysXExtern(PhysXExtern* physXExtern);

				/** In case of a collision callback, only actors that are related to a particle are taken into account. 
					This is determined by means of the group.
				*/
				bool isRegisteredCollisionGroup(uint16 collisionGroup);

				/** Override standard Singleton retrieval.
				*/
				static PhysXBridge& getSingleton (void);
				
				/** Override standard Singleton retrieval.
				*/
				static PhysXBridge* getSingletonPtr (void);

			protected:
				static NxPhysicsSDK* mPhysicsSDK;
				static NxScene* mScene;
				vector<PhysXExtern*> mExternList;
				Controller<Real>* mTimeController; // Controller for simulation
				Real mTimeSinceLastSimulation;
				PhysXContactReport mPhysXContactReport;
				NxActor* mPlaneActor;

		};
	}
#endif //PU_PHYSICS_PHYSX
#endif