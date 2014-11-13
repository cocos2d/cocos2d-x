/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PARTICLE_SYSTEM_MANAGER_H__
#define __PU_PARTICLE_SYSTEM_MANAGER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseScriptDeserializer.h"
#include "ParticleUniverseScriptSerializer.h"
#include "ParticleUniverseRendererFactory.h"
#include "ParticleRenderers/ParticleUniverseBoxSet.h"
#include "ParticleRenderers/ParticleUniverseBox.h"
#include "ParticleRenderers/ParticleUniverseSphereSet.h"
#include "ParticleRenderers/ParticleUniverseSphere.h"
#include "ParticleUniverseEmitterFactory.h"
#include "ParticleUniverseAffectorFactory.h"
#include "ParticleUniverseObserverFactory.h"
#include "ParticleUniverseEventHandlerFactory.h"
#include "ParticleUniverseExternFactory.h"
#include "ParticleUniverseBehaviourFactory.h"
#include "ParticleUniverseIAlias.h"
#include "ParticleUniverseCameraDependency.h"
#include "ParticleUniverseSystemTokens.h"
#include "ParticleUniverseTechniqueTokens.h"
#include "ParticleUniverseRendererTokens.h"
#include "ParticleUniverseEmitterTokens.h"
#include "ParticleUniverseAffectorTokens.h"
#include "ParticleUniverseObserverTokens.h"
#include "ParticleUniverseDynamicAttributeTokens.h"
#include "ParticleUniverseSystemManagerTokens.h"
#include "ParticleUniverseCameraDependencyTokens.h"
#include "ParticleUniverseAttachableTokens.h"
#include "OgreRenderTargetListener.h"
#include "ParticleUniverseSingleton.h"

namespace ParticleUniverse
{
	class ParticleSystemFactory;

	/** RenderTargetListener to be used for depth map */
	class _ParticleUniverseExport DepthMapTargetListener : public Ogre::RenderTargetListener, public Ogre::RenderQueue::RenderableListener
	{
		public: 
			DepthMapTargetListener(void) : 
				RenderTargetListener(),
				mSceneManager(0),
				mCamera(0),
				mDepthMap(0){};
			~DepthMapTargetListener(void){};

			virtual void preViewportUpdate(const Ogre::RenderTargetViewportEvent& evt);
			virtual void postViewportUpdate(const Ogre::RenderTargetViewportEvent& evt);
			virtual bool renderableQueued(Ogre::Renderable* rend, 
				uint8 groupID, 
				ushort priority, 
				Ogre::Technique** ppTech, 
				Ogre::RenderQueue* pQueue);
			void registerRenderer(ParticleRenderer* renderer);
			void unregisterRenderer(ParticleRenderer* renderer);
			bool registeredRenderersEmpty(void);
			Ogre::SceneManager* mSceneManager;
			Ogre::Technique* mDepthTechnique;
			Camera* mCamera;
			Ogre::RenderTexture* mDepthMap;
			vector<ParticleRenderer*> mRenderers;
	};

    /** The ParticleSystemManager manages particle systems, particle system scripts (templates), etc. It is also 
		responsible for actually creating techniques, emitters, observers, etc.
	*/
	class _ParticleUniverseExport ParticleSystemManager:
		public Singleton<ParticleSystemManager>, public ScriptWriter
    {
		friend class ParticleSystemFactory;

		protected:
			/** Implementation of creating a particle system used by the MovableObject factory.
			@remarks
				This function must not be used directly.
	        */
			ParticleSystem* _createSystemImpl(const String& name);

			/** Implementation of creating a particle system used by the MovableObject factory.
			@remarks
				This function must not be used directly.
	        */
			ParticleSystem* _createSystemImpl(const String& name, const String& templateName);

			/** Delete a particle system.
			@remarks
				This is a protected function used by the ParticleSystemManager itself.
	        */
			void _destroySystemImpl(ParticleSystem* particleSystem);

			ParticleScriptSerializer* mParticleScriptSerializer;
			ParticleSystemWriter mParticleSystemWriter;
			ParticleTechniqueWriter mParticleTechniqueWriter;
			ParticleRendererWriter mParticleRendererWriter;
			ParticleEmitterWriter mParticleEmitterWriter;
			ParticleAffectorWriter mParticleAffectorWriter;
			ParticleObserverWriter mParticleObserverWriter;
			AttachableWriter mAttachableWriter;
			DynamicAttributeWriter mDynamicAttributeWriter;
			CameraDependencyWriter mCameraDependencyWriter;

			// Emitter Factories
			typedef map<String, ParticleEmitterFactory*> EmitterFactoryMap;
			EmitterFactoryMap mEmitterFactories;

			// Affector Factories
			typedef map<String, ParticleAffectorFactory*> AffectorFactoryMap;
			AffectorFactoryMap mAffectorFactories;

			// Observer Factories
			typedef map<String, ParticleObserverFactory*> ObserverFactoryMap;
			ObserverFactoryMap mObserverFactories;

			// EventHandler Factories
			typedef map<String, ParticleEventHandlerFactory*> EventHandlerFactoryMap;
			EventHandlerFactoryMap mEventHandlerFactories;

			// Renderer Factories
			typedef map<String, ParticleRendererFactory*> RendererFactoryMap;
			RendererFactoryMap mRendererFactories;

			// Extern Factories
			typedef map<String, ExternFactory*> ExternFactoryMap;
			ExternFactoryMap mExternFactories;

			// Behaviour Factories
			typedef map<String, ParticleBehaviourFactory*> BehaviourFactoryMap;
			BehaviourFactoryMap mBehaviourFactories;

			/*	The alias map contains a list with all alias objects that are created during parsing of the 
				scripts. The alias map contains objects that are used in the templated particle systems.
			*/
			typedef map<String, IAlias*> AliasMap;
			AliasMap mAliasMap;

			/*	The template map contains a list with all particle systems that act as a template.
				These templates cannot be used themselves, but form the blueprint for creation of other 
				particle systems.
			*/
			typedef map<String, ParticleSystem*> ParticleSystemTemplateMap;
			ParticleSystemTemplateMap mParticleSystemTemplates;

			/*	The ParticleSystems map contains a list with all particle systems that are created by the manager.
			*/
			typedef map<String, ParticleSystem*> ParticleSystemMap;
			ParticleSystemMap mParticleSystems;

			// Factory used to create ParticleSystems
			ParticleSystemFactory* mParticleSystemFactory;

			// Factory used to create BoxSets
			BoxSetFactory* mBoxSetFactory;

			// Factory used to create SphereSets
			SphereSetFactory* mSphereSetFactory;

			// Parse functions on ParticleSystemManager level
			ParticleSystemManagerWriter mParticleSystemManagerWriter;

			// CameraDependency object is used as a container to store data from a particle script.
			CameraDependency mCameraDependency;

			// Used as a global setting to determine whether materials must be loaded manually or not.
			bool mAutoLoadMaterials;

			// Attributes used for creation of a depth map.
			DepthMapTargetListener mDepthMapTargetListener;
			String mDepthTextureName;
			String mDepthMaterialName;
			String mDepthVertexName;
			String mDepthFragmentName;
			Ogre::RenderTexture* mDepthMap;
			Ogre::Technique* mDepthTechnique;
			Ogre::Pass* mDepthPass;
			bool mDepthMapExtern;
			Ogre::OverlayContainer* mDebugPanel;
			Ogre::Overlay* mDebugOverlay;
			Real mDepthScale;

			// Name of the last created template.
			String mLastCreatedParticleSystemTemplateName;

			// The ScriptTranslatorManager needed to parse the scripts.
			BuiltinScriptTranslatorManager* mBuiltinScriptTranslatorManager;

		public:
			// Constructor
			ParticleSystemManager (void);

			// Destructor
			~ParticleSystemManager (void);

			/** Removes and deletes any SceneNode was created by a Particle System
			@remarks
				SceneNodes are created for certain situations (i.e. EntityRenderer), but just deleting them in the destructor of the 
				Particle System gives unpredictable results.
	        */
			void removeAndDestroyDanglingSceneNodes(Ogre::SceneNode* sceneNode);

			/** Remove all registered templates 
			*/ 
			void destroyAllParticleSystemTemplates(void);

			/** Create a BoxSet. This is similar to a BillboardSet, instead it uses boxes.
			*/
			BoxSet* createBoxSet(const String& name, Ogre::SceneManager* sceneManager, const uint poolSize = 20);
			
			/** Destroy the BoxSet.
			*/
			void destroyBoxSet(BoxSet* boxSet, Ogre::SceneManager* sceneManager);

			/** Create a SphereSet. This is similar to a BillboardSet, instead it uses spheres.
			*/
			SphereSet* createSphereSet(const String& name, Ogre::SceneManager* sceneManager, const uint poolSize = 20);
			
			/** Destroy the SphereSet.
			*/
			void destroySphereSet(SphereSet* sphereSet, Ogre::SceneManager* sceneManager);

			/** Registers a previously created Attachable. This is needed, because the scenemanager has to 
				know.
			*/
			void registerAttachable(Attachable* attachable, Ogre::SceneManager* sceneManager);

			/** Unregisters a created Attachable.
			*/
			void unregisterAttachable(Attachable* attachable, Ogre::SceneManager* sceneManager);

			/** Adds a new 'factory' object for emitters to the list of available emitter types.
			@remarks
				This method allows plugins etc to add new particle emitter types. Particle emitters
				are sources of particles, and generate new particles with their start positions, colours and
				momentums appropriately. 
			@par
				All particle emitter factories have an assigned name which is used to identify the emitter
				type. This must be unique.
			@param
				factory Pointer to a ParticleEmitterFactory subclass created by the plugin or application code.
			*/
			void addEmitterFactory(ParticleEmitterFactory* factory);

			/** Searches a ParticleEmitterFactory.
			*/
			ParticleEmitterFactory* getEmitterFactory(const String& emitterType);

			/** Remove an ParticleEmitterFactory, but doesn't delete it. Search the factory by its type.
			*/
			void removeEmitterFactory(const String& emitterType);

			/** Delete an ParticleEmitterFactory. Search the factory by its type.
			*/
			void destroyEmitterFactory(const String& emitterType);

			/** Method for creating a new emitter from a factory.
			@param
				emitterType String name of the emitter type to be created. A factory of this type must have been registered.
			*/
			ParticleEmitter* createEmitter(const String& emitterType);

			/** Clone a ParticleEmitter.
	        */
			ParticleEmitter* cloneEmitter(ParticleEmitter* emitter);

			/** Delete a ParticleEmitter.
	        */
			void destroyEmitter(ParticleEmitter* emitter);

			/** Add a ParticleAffectorFactory to this ParticleSystemManager.
			@remarks
				ParticleAffectorFactories, ParticleEmitterFactories, ... can be registered by the 
				ParticleSystemManager. This is done by means of their type. If a certain ParticleAffector,
				ParticleEmitter, ... must be created, the appropriate factory is searched (by means of
				its type), which created the object needed.
			@param
				factory Pointer to a ParticleAffectorFactory subclass created by the plugin or application code.
	        */
			void addAffectorFactory(ParticleAffectorFactory* factory);

			/** Searches a ParticleAffectorFactory.
			*/
			ParticleAffectorFactory* getAffectorFactory(const String& affectorType);

			/** Remove an ParticleAffectorFactory, but doesn't delete it. Search the factory by its type.
			*/
			void removeAffectorFactory(const String& affectorType);

			/** Delete a ParticleAffectorFactory. Search by its type.
			*/
			void destroyAffectorFactory(const String& affectorType);

			/** Create a ParticleAffector given a type.
	        */
			ParticleAffector* createAffector(const String& affectorType);

			/** Clone a ParticleAffector.
	        */
			ParticleAffector* cloneAffector(ParticleAffector* affector);

			/** Delete a ParticleAffector.
	        */
			void destroyAffector(ParticleAffector* affector);

			/** Create a ParticleTechnique.
	        */
			ParticleTechnique* createTechnique(void);

			/** Clone a ParticleTechnique.
	        */
			ParticleTechnique* cloneTechnique(ParticleTechnique* technique);

			/** Delete a ParticleTechnique.
	        */
			void destroyTechnique(ParticleTechnique* technique);

			/** Add a ParticleObserverFactory to this ParticleSystemManager.
			@param
				factory Pointer to a ParticleObserverFactory subclass created by the plugin or application code.
	        */
			void addObserverFactory(ParticleObserverFactory* factory);

			/** Searches a ParticleObserverFactory.
			*/
			ParticleObserverFactory* getObserverFactory(const String& observerType);

			/** Remove an ParticleObserverFactory, but doesn't delete it. Search the factory by its type.
			*/
			void removeObserverFactory(const String& affectorType);

			/** Delete a ParticleObserverFactory given its type.
	        */
			void destroyObserverFactory(const String& observerType);

			/** Create a ParticleObserver given a certain type.
	        */
			ParticleObserver* createObserver(const String& observerType);

			/** Clone a ParticleObserver.
	        */
			ParticleObserver* cloneObserver(ParticleObserver* observer);

			/** Destroye a ParticleObserver.
	        */
			void destroyObserver(ParticleObserver* observer);

			/** Add a ParticleEventHandlerFactory to this ParticleSystemManager.
			@param
				factory Pointer to a ParticleEventHandlerFactory subclass created by the plugin or application code.
	        */
			void addEventHandlerFactory(ParticleEventHandlerFactory* factory);

			/** Searches a ParticleEventHandlerFactory.
			*/
			ParticleEventHandlerFactory* getEventHandlerFactory(const String& eventHandlerType);

			/** Remove an ParticleEventHandlerFactory, but doesn't delete it. Search the factory by its type.
			*/
			void removeEventHandlerFactory(const String& affectorType);

			/** Delete a ParticleEventHandlerFactory given a certain type.
	        */
			void destroyEventHandlerFactory(const String& eventHandlerType);

			/** Create a ParticleEventHandler given a certain type.
	        */
			ParticleEventHandler* createEventHandler(const String& eventHandlerType);

			/** Clone a ParticleEventHandler.
	        */
			ParticleEventHandler* cloneEventHandler(ParticleEventHandler* eventHandler);

			/** Delete a ParticleEventHandler.
	        */
			void destroyEventHandler(ParticleEventHandler* eventHandler);

			/** Add a ParticleRendererFactory to this ParticleSystemManager.
	        */
			void addRendererFactory(ParticleRendererFactory* factory);

			/** Searches a ParticleRendererFactory.
			*/
			ParticleRendererFactory* getRendererFactory(const String& rendererType);

			/** Remove an ParticleRendererFactory, but doesn't delete it. Search the factory by its type.
			*/
			void removeRendererFactory(const String& affectorType);

			/** Delete a ParticleRendererFactory given a certain type.
			*/
			void destroyRendererFactory(const String& rendererType);

			/** Create a ParticleRenderer.
	        */
			ParticleRenderer* createRenderer(const String& rendererType);

			/** Clone a ParticleRenderer.
	        */
			ParticleRenderer* cloneRenderer(ParticleRenderer* renderer);

			/** Delete a ParticleRenderer.
	        */
			void destroyRenderer(ParticleRenderer* renderer);

			/** Add a ExternFactory to this ParticleSystemManager.
	        */
			void addExternFactory(ExternFactory* factory);

			/** Searches an ExternFactory.
			*/
			ExternFactory* getExternFactory(const String& externType);

			/** Remove an ParticleExternFactory, but doesn't delete it. Search the factory by its type.
			*/
			void removeExternFactory(const String& affectorType);

			/** Delete a ExternFactory given a certain type.
			*/
			void destroyExternFactory(const String& externType);

			/** Create an Extern object.
	        */
			Extern* createExtern(const String& externType);

			/** Clone an Extern object.
	        */
			Extern* cloneExtern(Extern* externObject);

			/** Delete an Extern object.
	        */
			void destroyExtern(Extern* externObject);

			/** Add a BehaviourFactory to this ParticleSystemManager.
	        */
			void addBehaviourFactory(ParticleBehaviourFactory* factory);

			/** Searches a ParticleBehaviourFactory.
	        */
			ParticleBehaviourFactory* getBehaviourFactory(const String& behaviourType);

			/** Remove an ParticleBehaviourFactory, but doesn't delete it. Search the factory by its type.
			*/
			void removeBehaviourFactory(const String& affectorType);

			/** Delete a BehaviourFactory given a certain type.
			*/
			void destroyBehaviourFactory(const String& behaviourType);

			/** Create a Behaviour object.
	        */
			ParticleBehaviour* createBehaviour(const String& behaviourType);

			/** Clone a Behaviour object.
	        */
			ParticleBehaviour* cloneBehaviour(ParticleBehaviour* behaviour);

			/** Delete a Behaviour object.
	        */
			void destroyBehaviour(ParticleBehaviour* behaviour);

			/** Create a ParticleSystemTemplate.
			@remarks
				ParticleSystemTemplates contain a ParticleSystem and form a blueprint for other ParticleSystems.
				Given the name of the template, a copy is made of the ParticleSystem. This copy can be used
				in your application. The ParticleSystem templates however are restricted to the 
				ParticleSystemManager.
	        */
			ParticleSystem* createParticleSystemTemplate(const String& name, const String& resourceGroupName);

			/** Replace a ParticleSystemTemplate with an existing Particle System.
			@remarks
				The existing Particle System is cloned and still exists after the call.
	        */
			void replaceParticleSystemTemplate(const String& name, ParticleSystem* system);

			/** Returns the name of the last created template. Because the templates are often created by means of a script, it is not
				straightforward to get the template name. It is embedded in the script. Only afterwards it is possible to get the 
				name of the created template, by using this function.
	        */
			const String& getLastCreatedParticleSystemTemplateName(void);

			/** Add a ParticleSystem template to this ParticleSystemManager.
	        */
			void addParticleSystemTemplate(const String& name, ParticleSystem* systemTemplate);

			/** Retrieves a particle system template.
			*/
			ParticleSystem* getParticleSystemTemplate(const String& templateName);

			/** Remove a particle system template and delete it.
			*/
			void destroyParticleSystemTemplate(const String& templateName);

			/** Fill a list of template names in the vector.
			*/
			void particleSystemTemplateNames(vector<String>& v);

			/** Creates a ParticleSystem, using a template as a blueprint.
			@remarks
				This is the function that must be used by the client application that wants to create a
				ParticleSystem.
	        */
			ParticleSystem* createParticleSystem(const String& name, 
				const String& templateName, 
				Ogre::SceneManager* sceneManager);

			/** Creates a default ParticleSystem.
			@remarks
				This is the function that must be used by the client application that wants to create a
				ParticleSystem.
	        */
			ParticleSystem* createParticleSystem(const String& name, 
				Ogre::SceneManager* sceneManager);

			/** Get a ParticleSystem by name.
	        */
			ParticleSystem* getParticleSystem(const String& name);

			/** This is the function that must be used by the client application that wants to delete a ParticleSystem. 
	        */
			void destroyParticleSystem(ParticleSystem* particleSystem, Ogre::SceneManager* sceneManager);

			/** Delete a ParticleSystem.
			@remarks
				This implementation deletes a ParticleSystem identified by its name. The function always
				validates whether the name still exists.
	        */
			void destroyParticleSystem(const String& particleSystemName, Ogre::SceneManager* sceneManager);

			/** Destroy all registered particle systems.
			@remarks
				Particle Systems are NOT automatically destroyed if the ParticleSystemManager is destroyed.
				The reason is, that the ParticleSystemManager is destroyed when the plugin is unloaded, which is too late.
				Before a scene is cleared, all particle systems must be deleted first (manually).
			*/ 
			void destroyAllParticleSystems(Ogre::SceneManager* sceneManager);

			/** Add an alias to this ParticleSystemManager.
			@remarks
				An alias is a ParticleTechnique, ParticleEmitter, ParticleAffector, etc. and forms the
				blueprint to create copies. These copies can be used again in ParticleSystems (templates).
				An alias is similar to a template, but where templates are restricted to ParticleSystems, 
				aliasses can be any type of object that inherits from IAlias.
	        */
			void addAlias (IAlias* alias);

			/** Returns an alias.
	        */
			IAlias* getAlias (const String& aliasName);

			/** Delete an alias from the ParticleSystemManager.
	        */
			void destroyAlias(IAlias* alias);

			/** Delete all aliasses.
	        */
			void destroyAllAliasses(void);

			/** Returns the alias map. Not for general purposes; only use it if you really need it.
	        */
			AliasMap* _getAliasMap(void);

			/** Override standard Singleton retrieval.
	        */
			static ParticleSystemManager& getSingleton (void);
			
			/** Override standard Singleton retrieval.
			*/
			static ParticleSystemManager* getSingletonPtr (void);

			/** Writes a ParticleSystem to a file in the script format.
			*/
			void writeScript(ParticleSystem* particleSystem, const String& fileName);

			/** Writes a ParticleSystem to string in the script format.
			*/
			const String& writeScript(ParticleSystem* particleSystem);

			/** Returns the ParticleScriptSerializer.
			@remarks
				The ParticleScriptSerializer is the main class responsible for serializing a Particle System to a script.
			*/
			ParticleScriptSerializer* getParticleScriptSerializer(void) const;

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element){};

			/** Returns Camera Dependency.
			@remarks
				CameraDependency is used as a container that stores data parsed from a particle script.
			*/
			CameraDependency* createCameraDependency(void);

			/** Create a depth map (texture) of all visible scene objects, except overlays and particle systems that render soft particles.
	        */
			void createDepthMap (Camera* camera, Ogre::SceneManager* sceneManager);

			/** Perform cleanup activities.
	        */
			void destroyDepthMap (void);

			/** Notify the Particle System Manager that is depthmap is needed.
	        */
			bool notifyDepthMapNeeded(Camera* camera, Ogre::SceneManager* sceneManager);

			/** Register the renderer, because it renders soft particles.
			@remarks
				Registration of the renderers is done by the ParticleSystemManager, because the depthmap that is used for soft particles
				is rendered only once under management of the ParticleSystemManager. The reason why the renderers are registered and
				not the complete ParticleSystems is to allow that ParticleSystem can contain a ParticleTechnique with soft particles and
				one without (also in relation to LOD strategies).
	        */
			void registerSoftParticlesRenderer(ParticleRenderer* renderer);

			/** Unregister the renderer, because it will not use soft particles anymore.
	        */
			void unregisterSoftParticlesRenderer(ParticleRenderer* renderer);

			/** Used to scale the values of the generated depth map
	        */
			Real getDepthScale(void) const;
			void setDepthScale(Real depthScale);

			/** Returns the name of the depth texture.
	        */
			const String& getDepthTextureName (void);

			/** Set a depth texture name from a depthmap that is created outside Particle Universe. This means that the external source
				also has to take into account that the Particle Universe particles are excluded from the depth map.
	        */
			void setExternDepthTextureName (const String& depthTextureName);

			/** Reset the external depth texture name, so it is not used anymore.
	        */
			void resetExternDepthTextureName (void);

			/** Create a DynamicAttribute.
			@remarks
				This can be called from outside the plugin, memory is allocated correctly.
	        */
			DynamicAttribute* createDynamicAttribute(DynamicAttribute::DynamicAttributeType type);

			/** Determines whether materials must be loaded dynamically or not. If the function returns 'false', the materials must be loaded 
				manually.
	        */
			bool isAutoLoadMaterials(void) const;

			/** Determines whether materials must be loaded dynamically or not.
			@remarks
				This function gives more control over loading the materials.
	        */
			void setAutoLoadMaterials(bool autoLoadMaterials);
	};

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	/** Factory object for creating ParticleSystem instances */
	class _ParticleUniverseExport ParticleSystemFactory : public Ogre::MovableObjectFactory
	{
		protected:
			Ogre::MovableObject* createInstanceImpl(const String& name, const Ogre::NameValuePairList* params);
		
		public:
			ParticleSystemFactory(void) {};
			~ParticleSystemFactory(void) {};
		
			static String PU_FACTORY_TYPE_NAME;

			const String& getType(void) const;

			void destroyInstance(Ogre::MovableObject* obj);

	};

}
#endif
