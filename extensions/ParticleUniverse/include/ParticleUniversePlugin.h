/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PARTICLE_UNIVERSE_PLUGIN_H__
#define __PARTICLE_UNIVERSE_PLUGIN_H__

#include "OgrePlugin.h"
#include "ParticleUniverseSystemManager.h"
#include "ParticleUniverseRendererFactory.h"
#include "ParticleUniverseEmitterFactory.h"
#include "ParticleUniverseAffectorFactory.h"
#include "ParticleUniverseObserverFactory.h"
#include "ParticleUniverseEventHandlerFactory.h"
#include "ParticleUniverseExternFactory.h"
#include "ParticleUniverseBehaviourFactory.h"
#include "ParticleUniverseScriptDeserializer.h"

#include "Externs/ParticleUniverseGravityExternFactory.h"
#include "Externs/ParticleUniverseSphereColliderExternFactory.h"
#include "Externs/ParticleUniverseBoxColliderExternFactory.h"
#include "Externs/ParticleUniverseVortexExternFactory.h"
#include "Externs/ParticleUniverseSceneDecoratorExternFactory.h"

#ifdef PU_PHYSICS_PHYSX
		#include "Externs/ParticleUniversePhysXBridge.h"
		#include "Externs/ParticleUniversePhysXActorExternFactory.h"
		#include "Externs/ParticleUniversePhysXFluidExternFactory.h"
#endif // PU_PHYSICS_PHYSX

#include "ParticleRenderers/ParticleUniverseBeamRendererFactory.h"
#include "ParticleRenderers/ParticleUniverseBillboardRendererFactory.h"
#include "ParticleRenderers/ParticleUniverseBoxRendererFactory.h"
#include "ParticleRenderers/ParticleUniverseSphereRendererFactory.h"
#include "ParticleRenderers/ParticleUniverseEntityRendererFactory.h"
#include "ParticleRenderers/ParticleUniverseRibbonTrailRendererFactory.h"
#include "ParticleRenderers/ParticleUniverseLightRendererFactory.h"

#include "ParticleEmitters/ParticleUniversePointEmitterFactory.h"
#include "ParticleEmitters/ParticleUniverseLineEmitterFactory.h"
#include "ParticleEmitters/ParticleUniverseBoxEmitterFactory.h"
#include "ParticleEmitters/ParticleUniverseCircleEmitterFactory.h"
#include "ParticleEmitters/ParticleUniverseSphereSurfaceEmitterFactory.h"
#include "ParticleEmitters/ParticleUniverseVertexEmitterFactory.h"
#include "ParticleEmitters/ParticleUniverseMeshSurfaceEmitterFactory.h"
#include "ParticleEmitters/ParticleUniversePositionEmitterFactory.h"
#include "ParticleEmitters/ParticleUniverseSlaveEmitterFactory.h"

#include "ParticleAffectors/ParticleUniverseBaseForceAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseLinearForceAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseVortexAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseGravityAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseParticleFollowerFactory.h"
#include "ParticleAffectors/ParticleUniverseRandomiserFactory.h"
#include "ParticleAffectors/ParticleUniverseLineAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseScaleAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseScaleVelocityAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseGeometryRotatorFactory.h"
#include "ParticleAffectors/ParticleUniverseTextureRotatorFactory.h"
#include "ParticleAffectors/ParticleUniverseTextureAnimatorFactory.h"
#include "ParticleAffectors/ParticleUniverseJetAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseAlignAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseFlockCenteringAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseCollisionAvoidanceAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseVelocityMatchingAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseColourAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseSineForceAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseSphereColliderFactory.h"
#include "ParticleAffectors/ParticleUniversePlaneColliderFactory.h"
#include "ParticleAffectors/ParticleUniverseBoxColliderFactory.h"
#include "ParticleAffectors/ParticleUniverseInterParticleColliderFactory.h"
#include "ParticleAffectors/ParticleUniversePathFollowerFactory.h"
#include "ParticleAffectors/ParticleUniverseForceFieldAffectorFactory.h"
#include "ParticleAffectors/ParticleUniverseBaseColliderFactory.h"

#include "ParticleObservers/ParticleUniverseOnExpireObserverFactory.h"
#include "ParticleObservers/ParticleUniverseOnEmissionObserverFactory.h"
#include "ParticleObservers/ParticleUniverseOnCountObserverFactory.h"
#include "ParticleObservers/ParticleUniverseOnEventFlagObserverFactory.h"
#include "ParticleObservers/ParticleUniverseOnCollisionObserverFactory.h"
#include "ParticleObservers/ParticleUniverseOnVelocityObserverFactory.h"
#include "ParticleObservers/ParticleUniverseOnTimeObserverFactory.h"
#include "ParticleObservers/ParticleUniverseOnPositionObserverFactory.h"
#include "ParticleObservers/ParticleUniverseOnClearObserverFactory.h"
#include "ParticleObservers/ParticleUniverseOnQuotaObserverFactory.h"
#include "ParticleObservers/ParticleUniverseOnRandomObserverFactory.h"

#include "ParticleEventHandlers/ParticleUniverseDoExpireEventHandlerFactory.h"
#include "ParticleEventHandlers/ParticleUniverseDoFreezeEventHandlerFactory.h"
#include "ParticleEventHandlers/ParticleUniverseDoPlacementParticleEventHandlerFactory.h"
#include "ParticleEventHandlers/ParticleUniverseDoStopSystemEventHandlerFactory.h"
#include "ParticleEventHandlers/ParticleUniverseDoEnableComponentEventHandlerFactory.h"
#include "ParticleEventHandlers/ParticleUniverseDoAffectorEventHandlerFactory.h"
#include "ParticleEventHandlers/ParticleUniverseDoScaleEventHandlerFactory.h"

#include "ParticleBehaviours/ParticleUniverseSlaveBehaviourFactory.h"

namespace ParticleUniverse
{
	/** Plugin instance for Particle Universe */
	class ParticleUniversePlugin : public Ogre::Plugin
	{
	public:
		ParticleUniversePlugin(void);

		/// @copydoc Plugin::getName
		const String& getName(void) const;

		/// @copydoc Plugin::install
		void install(void);

		/// @copydoc Plugin::initialise
		void initialise(void);

		/// @copydoc Plugin::shutdown
		void shutdown(void);

		/// @copydoc Plugin::uninstall
		void uninstall(void);

	protected:
		ParticleSystemManager* mParticleSystemManager;
#ifdef PU_PHYSICS_PHYSX
		PhysXBridge* mPhysXBridge;
#endif // PU_PHYSICS_PHYSX

		vector<ParticleRendererFactory*> mRendererFactories;
		vector<ParticleEmitterFactory*> mEmitterFactories;
		vector<ParticleAffectorFactory*> mAffectorFactories;
		vector<ParticleObserverFactory*> mObserverFactories;
		vector<ParticleEventHandlerFactory*> mEventHandlerFactories;
		vector<ExternFactory*> mExternFactories;
		vector<ParticleBehaviourFactory*> mBehaviourFactories;
	};
}

#endif
