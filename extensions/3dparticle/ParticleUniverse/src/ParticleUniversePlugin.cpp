/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#include "ParticleUniversePCH.h"
#include "ParticleUniversePlugin.h"
#include "OgreRoot.h"

namespace ParticleUniverse
{
	const String sPluginName = "ParticleUniverse";
	//---------------------------------------------------------------------
	ParticleUniversePlugin::ParticleUniversePlugin()
	{
	}
	//---------------------------------------------------------------------
	const String& ParticleUniversePlugin::getName() const
	{
		return sPluginName;
	}
	//---------------------------------------------------------------------
	void ParticleUniversePlugin::install()
	{
#ifdef PU_PHYSICS_PHYSX
		// ----------------------- Create the PhysXBridge -----------------------
		mPhysXBridge = PU_NEW_T(PhysXBridge, MEMCATEGORY_SCENE_CONTROL)();
#endif // PU_PHYSICS_PHYSX

		// ----------------------- Create the particle system manager -----------------------
		mParticleSystemManager = PU_NEW_T(ParticleSystemManager, MEMCATEGORY_SCENE_CONTROL)();

		// ----------------------- Create renderer factories -----------------------
		ParticleRendererFactory* particleRendererFactory;

		particleRendererFactory = PU_NEW BeamRendererFactory();
		mParticleSystemManager->addRendererFactory(particleRendererFactory);
		mRendererFactories.push_back(particleRendererFactory);

		particleRendererFactory = PU_NEW BillboardRendererFactory();
		mParticleSystemManager->addRendererFactory(particleRendererFactory);
		mRendererFactories.push_back(particleRendererFactory);

		particleRendererFactory = PU_NEW BoxRendererFactory();
		mParticleSystemManager->addRendererFactory(particleRendererFactory);
		mRendererFactories.push_back(particleRendererFactory);

		particleRendererFactory = PU_NEW SphereRendererFactory();
		mParticleSystemManager->addRendererFactory(particleRendererFactory);
		mRendererFactories.push_back(particleRendererFactory);

		particleRendererFactory = PU_NEW EntityRendererFactory();
		mParticleSystemManager->addRendererFactory(particleRendererFactory);
		mRendererFactories.push_back(particleRendererFactory);

		particleRendererFactory = PU_NEW RibbonTrailRendererFactory();
		mParticleSystemManager->addRendererFactory(particleRendererFactory);
		mRendererFactories.push_back(particleRendererFactory);

		particleRendererFactory = PU_NEW LightRendererFactory();
		mParticleSystemManager->addRendererFactory(particleRendererFactory);
		mRendererFactories.push_back(particleRendererFactory);

		// ----------------------- Create emitter factories -----------------------
		ParticleEmitterFactory* particleEmitterFactory;
		particleEmitterFactory = PU_NEW PointEmitterFactory();
		mParticleSystemManager->addEmitterFactory(particleEmitterFactory);
		mEmitterFactories.push_back(particleEmitterFactory);

		particleEmitterFactory = PU_NEW LineEmitterFactory();
		mParticleSystemManager->addEmitterFactory(particleEmitterFactory);
		mEmitterFactories.push_back(particleEmitterFactory);

		particleEmitterFactory = PU_NEW BoxEmitterFactory();
		mParticleSystemManager->addEmitterFactory(particleEmitterFactory);
		mEmitterFactories.push_back(particleEmitterFactory);

		particleEmitterFactory = PU_NEW CircleEmitterFactory();
		mParticleSystemManager->addEmitterFactory(particleEmitterFactory);
		mEmitterFactories.push_back(particleEmitterFactory);

		particleEmitterFactory = PU_NEW SphereSurfaceEmitterFactory();
		mParticleSystemManager->addEmitterFactory(particleEmitterFactory);
		mEmitterFactories.push_back(particleEmitterFactory);

		particleEmitterFactory = PU_NEW VertexEmitterFactory();
		mParticleSystemManager->addEmitterFactory(particleEmitterFactory);
		mEmitterFactories.push_back(particleEmitterFactory);
		
		particleEmitterFactory = PU_NEW MeshSurfaceEmitterFactory();
		mParticleSystemManager->addEmitterFactory(particleEmitterFactory);
		mEmitterFactories.push_back(particleEmitterFactory);

		particleEmitterFactory = PU_NEW PositionEmitterFactory();
		mParticleSystemManager->addEmitterFactory(particleEmitterFactory);
		mEmitterFactories.push_back(particleEmitterFactory);

		particleEmitterFactory = PU_NEW SlaveEmitterFactory();
		mParticleSystemManager->addEmitterFactory(particleEmitterFactory);
		mEmitterFactories.push_back(particleEmitterFactory);

		// ----------------------- Create affector factories -----------------------
		ParticleAffectorFactory* particleAffectorFactory;
		particleAffectorFactory = PU_NEW BaseForceAffectorFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW LinearForceAffectorFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW GravityAffectorFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW ParticleFollowerFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW VortexAffectorFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW RandomiserFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW LineAffectorFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW ScaleAffectorFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW ScaleVelocityAffectorFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW GeometryRotatorFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW TextureRotatorFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW TextureAnimatorFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW JetAffectorFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW AlignAffectorFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW FlockCenteringAffectorFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW CollisionAvoidanceAffectorFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW VelocityMatchingAffectorFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW ColourAffectorFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW SineForceAffectorFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW BaseColliderFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW SphereColliderFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW PlaneColliderFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW BoxColliderFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW InterParticleColliderFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW PathFollowerFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		particleAffectorFactory = PU_NEW ForceFieldAffectorFactory();
		mParticleSystemManager->addAffectorFactory(particleAffectorFactory);
		mAffectorFactories.push_back(particleAffectorFactory);

		// ----------------------- Create observer factories -----------------------
		ParticleObserverFactory* particleObserverFactory;
		particleObserverFactory = PU_NEW OnExpireObserverFactory();
		mParticleSystemManager->addObserverFactory(particleObserverFactory);
		mObserverFactories.push_back(particleObserverFactory);

		particleObserverFactory = PU_NEW OnEmissionObserverFactory();
		mParticleSystemManager->addObserverFactory(particleObserverFactory);
		mObserverFactories.push_back(particleObserverFactory);

		particleObserverFactory = PU_NEW OnCountObserverFactory();
		mParticleSystemManager->addObserverFactory(particleObserverFactory);
		mObserverFactories.push_back(particleObserverFactory);

		particleObserverFactory = PU_NEW OnEventFlagObserverFactory();
		mParticleSystemManager->addObserverFactory(particleObserverFactory);
		mObserverFactories.push_back(particleObserverFactory);

		particleObserverFactory = PU_NEW OnCollisionObserverFactory();
		mParticleSystemManager->addObserverFactory(particleObserverFactory);
		mObserverFactories.push_back(particleObserverFactory);

		particleObserverFactory = PU_NEW OnVelocityObserverFactory();
		mParticleSystemManager->addObserverFactory(particleObserverFactory);
		mObserverFactories.push_back(particleObserverFactory);

		particleObserverFactory = PU_NEW OnTimeObserverFactory();
		mParticleSystemManager->addObserverFactory(particleObserverFactory);
		mObserverFactories.push_back(particleObserverFactory);

		particleObserverFactory = PU_NEW OnPositionObserverFactory();
		mParticleSystemManager->addObserverFactory(particleObserverFactory);
		mObserverFactories.push_back(particleObserverFactory);

		particleObserverFactory = PU_NEW OnClearObserverFactory();
		mParticleSystemManager->addObserverFactory(particleObserverFactory);
		mObserverFactories.push_back(particleObserverFactory);

		particleObserverFactory = PU_NEW OnQuotaObserverFactory();
		mParticleSystemManager->addObserverFactory(particleObserverFactory);
		mObserverFactories.push_back(particleObserverFactory);

		particleObserverFactory = PU_NEW OnRandomObserverFactory();
		mParticleSystemManager->addObserverFactory(particleObserverFactory);
		mObserverFactories.push_back(particleObserverFactory);

		// ----------------------- Create event handler factories -----------------------
		ParticleEventHandlerFactory* particleEventHandlerFactory;
		particleEventHandlerFactory = PU_NEW DoExpireEventHandlerFactory();
		mParticleSystemManager->addEventHandlerFactory(particleEventHandlerFactory);
		mEventHandlerFactories.push_back(particleEventHandlerFactory);

		particleEventHandlerFactory = PU_NEW DoFreezeEventHandlerFactory();
		mParticleSystemManager->addEventHandlerFactory(particleEventHandlerFactory);
		mEventHandlerFactories.push_back(particleEventHandlerFactory);

		particleEventHandlerFactory = PU_NEW DoPlacementParticleEventHandlerFactory();
		mParticleSystemManager->addEventHandlerFactory(particleEventHandlerFactory);
		mEventHandlerFactories.push_back(particleEventHandlerFactory);

		particleEventHandlerFactory = PU_NEW DoStopSystemEventHandlerFactory();
		mParticleSystemManager->addEventHandlerFactory(particleEventHandlerFactory);
		mEventHandlerFactories.push_back(particleEventHandlerFactory);

		particleEventHandlerFactory = PU_NEW DoEnableComponentEventHandlerFactory();
		mParticleSystemManager->addEventHandlerFactory(particleEventHandlerFactory);
		mEventHandlerFactories.push_back(particleEventHandlerFactory);

		particleEventHandlerFactory = PU_NEW DoAffectorEventHandlerFactory();
		mParticleSystemManager->addEventHandlerFactory(particleEventHandlerFactory);
		mEventHandlerFactories.push_back(particleEventHandlerFactory);

		particleEventHandlerFactory = PU_NEW DoScaleEventHandlerFactory();
		mParticleSystemManager->addEventHandlerFactory(particleEventHandlerFactory);
		mEventHandlerFactories.push_back(particleEventHandlerFactory);

		// ----------------------- Create extern factories -----------------------
		ExternFactory* externFactory;
		externFactory = PU_NEW GravityExternFactory();
		mParticleSystemManager->addExternFactory(externFactory);
		mExternFactories.push_back(externFactory);

		externFactory = PU_NEW SphereColliderExternFactory();
		mParticleSystemManager->addExternFactory(externFactory);
		mExternFactories.push_back(externFactory);

		externFactory = PU_NEW BoxColliderExternFactory();
		mParticleSystemManager->addExternFactory(externFactory);
		mExternFactories.push_back(externFactory);

		externFactory = PU_NEW VortexExternFactory();
		mParticleSystemManager->addExternFactory(externFactory);
		mExternFactories.push_back(externFactory);

		externFactory = PU_NEW SceneDecoratorExternFactory();
		mParticleSystemManager->addExternFactory(externFactory);
		mExternFactories.push_back(externFactory);

#ifdef PU_PHYSICS_PHYSX
		externFactory = PU_NEW PhysXActorExternFactory();
		mParticleSystemManager->addExternFactory(externFactory);
		mExternFactories.push_back(externFactory);

		externFactory = PU_NEW PhysXFluidExternFactory();
		mParticleSystemManager->addExternFactory(externFactory);
		mExternFactories.push_back(externFactory);
#endif //PU_PHYSICS_PHYSX

		// ----------------------- Create behaviour factories -----------------------
		ParticleBehaviourFactory* particleBehaviourFactory;
		particleBehaviourFactory = PU_NEW SlaveBehaviourFactory();
		mParticleSystemManager->addBehaviourFactory(particleBehaviourFactory);
		mBehaviourFactories.push_back(particleBehaviourFactory);
	}
	//---------------------------------------------------------------------
	void ParticleUniversePlugin::initialise()
	{
	}
	//---------------------------------------------------------------------
	void ParticleUniversePlugin::shutdown()
	{
		// Delete the manager.
		// The manager must be deleted before all factories are deleted (also the factories of other plugins)
		PU_DELETE_T(mParticleSystemManager, ParticleSystemManager, MEMCATEGORY_SCENE_CONTROL);
	}
	//---------------------------------------------------------------------
	void ParticleUniversePlugin::uninstall()
	{
		// Delete all factories created in dllStartPlugin (after deleting the ParticleSystemManager)
		vector<ParticleRendererFactory*>::iterator ri;
		for (ri = mRendererFactories.begin(); ri != mRendererFactories.end(); ++ri)
		{
			PU_DELETE *ri;
		}

		vector<ParticleEmitterFactory*>::iterator ei;
		for (ei = mEmitterFactories.begin(); ei != mEmitterFactories.end(); ++ei)
		{
			PU_DELETE *ei;
		}

		vector<ParticleAffectorFactory*>::iterator ai;
		for (ai = mAffectorFactories.begin(); ai != mAffectorFactories.end(); ++ai)
		{
			PU_DELETE *ai;
		}
		
		vector<ParticleObserverFactory*>::iterator oi;
		for (oi = mObserverFactories.begin(); oi != mObserverFactories.end(); ++oi)
		{
			PU_DELETE *oi;
		}
		
		vector<ParticleEventHandlerFactory*>::iterator ehi;
		for (ehi = mEventHandlerFactories.begin(); ehi != mEventHandlerFactories.end(); ++ehi)
		{
			PU_DELETE *ehi;
		}

		vector<ExternFactory*>::iterator exi;
		for (exi = mExternFactories.begin(); exi != mExternFactories.end(); ++exi)
		{
			PU_DELETE *exi;
		}

		vector<ParticleBehaviourFactory*>::iterator bi;
		for (bi = mBehaviourFactories.begin(); bi != mBehaviourFactories.end(); ++bi)
		{
			PU_DELETE *bi;
		}

#ifdef PU_PHYSICS_PHYSX
		// Delete the PhysXBridge
		PU_DELETE_T(mPhysXBridge, PhysXBridge, MEMCATEGORY_SCENE_CONTROL);
#endif // PU_PHYSICS_PHYSX
	}
}
