/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_TECHNIQUE_H__
#define __PU_TECHNIQUE_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseRenderer.h"
#include "ParticleUniverseParticle.h"
#include "ParticleUniverseEmitter.h"
#include "ParticleUniverseAffector.h"
#include "ParticleUniverseObserver.h"
#include "ParticleUniverseEventHandler.h"
#include "ParticleUniverseBehaviour.h"
#include "ParticleUniverseIAlias.h"
#include "ParticleUniverseParticlePool.h"
#include "ParticleUniverseIElement.h"
#include "ParticleUniverseHook.h"
#include "ParticleUniverseSpatialHashTable.h"
#include "ParticleUniverseCameraDependency.h"
#include "ParticleUniverseCameraDependencyFactory.h"
#include "ParticleUniverseTechniqueListener.h"
#include "ParticleUniverseAxisAlignedBox.h"

namespace ParticleUniverse
{
	static const Vector3 HALFSCALE(0.5f, 0.5f, 0.5f);

	/** In analogy of Ogre's material system, the ParticleTechnique is introduced. It forms an extra layer 
		between particle emitters, affectors, etc. on one side, and the particle system and the other side.
		A ParticleTechnique has a few benefits. For example, with the use of a ParticleTechnique it is possible
		to implement Particle LOD (Level Of Detail). Also combining multiple renderers and material within one 
		ParticleSystem is possible.
    */
	class _ParticleUniverseExport ParticleTechnique : public Particle, public IAlias, public IElement
	{
		public:
			// Default values
			static const bool DEFAULT_ENABLED;
			static const Vector3 DEFAULT_POSITION;
			static const bool DEFAULT_KEEP_LOCAL;
			static const size_t DEFAULT_VISUAL_PARTICLE_QUOTA;
			static const size_t DEFAULT_EMITTED_EMITTER_QUOTA;
			static const size_t DEFAULT_EMITTED_TECHNIQUE_QUOTA;
			static const size_t DEFAULT_EMITTED_AFFECTOR_QUOTA;
			static const size_t DEFAULT_EMITTED_SYSTEM_QUOTA;
			static const unsigned short DEFAULT_LOD_INDEX;
			static const Real DEFAULT_WIDTH;
			static const Real DEFAULT_HEIGHT;
			static const Real DEFAULT_DEPTH;
			static const unsigned short DEFAULT_SPATIAL_HASHING_CELL_DIM;
			static const unsigned short DEFAULT_SPATIAL_HASHING_CELL_OVERLAP;
			static const size_t DEFAULT_SPATIAL_HASHING_TABLE_SIZE;
			static const Real DEFAULT_SPATIAL_HASHING_INTERVAL;
			static const Real DEFAULT_MAX_VELOCITY;

			// Have to use the expanded version because the Hook class can also only use the expanded version
			typedef vector<ParticleEmitter*> ParticleEmitterList;
			typedef ParticleEmitterList::const_iterator ParticleEmitterIterator;

			typedef vector<ParticleAffector*> ParticleAffectorList;
			typedef ParticleAffectorList::const_iterator ParticleAffectorIterator;

			typedef vector<ParticleObserver*> ParticleObserverList;
			typedef ParticleObserverList::const_iterator ParticleObserverIterator;

			typedef vector<Extern*> ExternList;
			typedef ExternList::const_iterator ExternIterator;

			typedef vector<TechniqueListener*> TechniqueListenerList;
			typedef TechniqueListenerList::const_iterator TechniqueListenerIterator;

			ParticleTechnique(void);
	        virtual ~ParticleTechnique(void);

			/** 
	        */
			inline ParticleSystem* getParentSystem(void) const {return mParentSystem;};
			void setParentSystem(ParticleSystem* parentSystem) {mParentSystem = parentSystem;};

			/** 
	        */
			inline const String& getName(void) const {return mName;};
			void setName(const String& name) {mName = name;};

			/** 
	        */
			size_t getVisualParticleQuota(void) const;
			void setVisualParticleQuota(size_t quota);

			/** 
	        */
			size_t getEmittedEmitterQuota(void) const;
			void setEmittedEmitterQuota(size_t quota);

			/** 
	        */
			size_t getEmittedTechniqueQuota(void) const;
			void setEmittedTechniqueQuota(size_t quota);

			/** 
	        */
			size_t getEmittedAffectorQuota(void) const;
			void setEmittedAffectorQuota(size_t quota);

			/** 
	        */
			size_t getEmittedSystemQuota(void) const;
			void setEmittedSystemQuota(size_t quota);

			/** 
	        */
			const Real getDefaultWidth(void) const;
			void setDefaultWidth(const Real width);

			/** 
	        */
			const Real getDefaultHeight(void) const;
			void setDefaultHeight(const Real height);

			/** 
	        */
			const Real getDefaultDepth(void) const;
			void setDefaultDepth(const Real depth);

			/** Returns the derived position of the technique.
			@remarks
				Note, that in script, the position is set into localspace, while if the technique is
				emitted, its position is automatically transformed. This function always returns the 
				derived position.
	        */
			const Vector3& getDerivedPosition(void);

			/** Get/Set the squared distance between camera and ParticleTechnique.
	        */
			inline Real getCameraSquareDistance(void) const {return mCameraSquareDistance;};
			void setCameraSquareDistance(Real cameraSquareDistance){mCameraSquareDistance = cameraSquareDistance;};

			/** Function to suppress notification of an emission change.
			@see
				ParticleTechnique
	        */
			void suppressNotifyEmissionChange(bool suppress);

			/** Set the name of the material used by the renderer.
	        */
			const String& getMaterialName(void) const;

			/** Get the material pointer.
	        */
			const Ogre::MaterialPtr getMaterial(void) const;

			/** Set the name of the material used by the renderer.
	        */
			void setMaterialName(const String& materialName);

			//-------------------------------------- Emitter --------------------------------------
			/** Create a ParticleEmitter and add it to this ParticleTechnique.
	        */
			ParticleEmitter* createEmitter (const String& emitterType);

			/** Add a ParticleEmitter to this ParticleTechnique.
			@remarks
				It must be possible to add a previously created emitter to the list. This is the case with 
				emitters that were created outside the technique. An example is the creation of emitters by means
				of a script. The emitter will be placed under control of the technique. The Emitter Factory
				however, deletes the emitters (since they are also created by the factory).
			@param
				emitter Pointer to a previously created emitter.
	        */
			void addEmitter (ParticleEmitter* emitter);

			/** Remove a ParticleEmitter from the ParticleTechnique, but don´t delete it.
			@param
				Pointer to a ParticleEmitter object.
	        */
			void removeEmitter(ParticleEmitter* emitter);

			/** Get a ParticleEmitter. Search by index.
	        */
			ParticleEmitter* getEmitter (size_t index) const;

			/** Get a ParticleEmitter. Search by name.
	        */
			ParticleEmitter* getEmitter (const String& emitterName) const;

			/** Get the number of ParticleEmitters added to this ParticleTechnique.
	        */
			size_t getNumEmitters (void) const;

			/** Delete a ParticleEmitter that is part of this ParticleTechnique. Search by index.
	        */
			void destroyEmitter (size_t index);

			/** Delete a ParticleEmitter that is part of this ParticleTechnique.
	        */
			void destroyEmitter (ParticleEmitter* emitter);

			/** Delete all ParticleEmitters of this ParticleTechnique.
	        */
			void destroyAllEmitters (void);

			/** Get the number of emitted ParticleEmitters.
			@remarks
				This doesn't return the real number of emitted emitters, but the number of emitters that are
				marked for emission.
	        */
			size_t getNumEmittedEmitters (void) const;

			//-------------------------------------- Affector --------------------------------------
			/** Create a ParticleAffector and add it to this ParticleTechnique.
	        */
			ParticleAffector* createAffector (const String& affectorType);

			/** Add a ParticleAffector to this ParticleTechnique.
			@param
				Pointer to a previously created affector.
	        */
			void addAffector (ParticleAffector* affector);

			/** Remove a ParticleAffector from the ParticleTechnique, but don´t delete it.
			@param
				Pointer to a ParticleAffector object.
	        */
			void removeAffector (ParticleAffector* affector);

			/** Get a ParticleAffector. Search by index.
	        */
			ParticleAffector* getAffector (size_t index) const;

			/** Get a ParticleAffector. Search by name.
	        */
			ParticleAffector* getAffector (const String& affectorName) const;

			/** Get the number of ParticleAffectors added to this ParticleTechnique.
	        */
			size_t getNumAffectors (void) const;

			/** Delete a ParticleAffector that is part of this ParticleTechnique. Search by index.
	        */
			void destroyAffector (size_t index);

			/** Delete a ParticleAffector that is part of this ParticleTechnique.
	        */
			void destroyAffector (ParticleAffector* affector);

			/** Delete all ParticleAffectors of this ParticleTechnique.
	        */
			void destroyAllAffectors (void);

			/** Get the number of emitted ParticleAffectors.
			@remarks
				This doesn't return the real number of emitted affectors, but the number of affectors that are
				marked for emission.
	        */
			size_t getNumEmittedAffectors (void) const;

			//-------------------------------------- Observer --------------------------------------
			/** Create a ParticleObserver and add it to this ParticleTechnique.
	        */
			ParticleObserver* createObserver (const String& observerType);

			/** Add a ParticleObserver to this ParticleTechnique.
			@param
				Pointer to a previously created observer.
	        */
			void addObserver (ParticleObserver* observer);

			/** Remove a ParticleObserver from the ParticleTechnique, but don´t delete it.
			@param
				Pointer to a ParticleObserver object.
	        */
			void removeObserver(ParticleObserver* observer);

			/** Get a ParticleObserver. Search by index.
	        */
			ParticleObserver* getObserver (size_t index) const;

			/** Get a ParticleObserver. Search by name.
	        */
			ParticleObserver* getObserver (const String& observerName) const;

			/** Get the number of ParticleObservers added to this ParticleTechnique.
	        */
			size_t getNumObservers (void) const;

			/** Delete a ParticleObserver that is part of this ParticleTechnique. Search by index.
	        */
			void destroyObserver (size_t index);

			/** Delete a ParticleObserver that is part of this ParticleTechnique.
	        */
			void destroyObserver (ParticleObserver* observer);

			/** Delete all ParticleObservers of this ParticleTechnique.
	        */
			void destroyAllObservers (void);

			//-------------------------------------- Renderer --------------------------------------
			/** Returns the pointer to the renderer.
			*/
			ParticleRenderer* getRenderer(void) const;

			/** Set a renderer by means of the type of renderer.
	        */
			void setRenderer(const String& rendererType);

			/** Remove a renderer; this doesn't detroy it.
	        */
			void removeRenderer(ParticleRenderer* renderer);

			/** Set a renderer.
	        */
			void setRenderer(ParticleRenderer* renderer);

			/** Delete the renderer of this ParticleTechnique.
	        */
			void destroyRenderer(void);

			//-------------------------------------- Behaviour --------------------------------------
			/** Add a ParticleBehaviour template to this ParticleTechnique.
			@remarks
				The ParticleBehaviour only serves as a blueprint for other ParticleBehaviour objects that
				are attached to a Particle, so the method should only be used internally.
			@param
				Pointer to a previously created Behaviour object.
	        */
			void _addBehaviourTemplate (ParticleBehaviour* behaviourTemplate);

			/** Remove a ParticleBehaviour template.
	        */
			void _removeBehaviourTemplate(ParticleBehaviour* behaviourTemplate);

			/** Get a ParticleBehaviour template. Search by index.
	        */
			ParticleBehaviour* _getBehaviourTemplate (size_t index) const;

			/** Get a ParticleBehaviour template. Search by type.
	        */
			ParticleBehaviour* _getBehaviourTemplate (const String& behaviourType) const;

			/** Get the number of ParticleBehaviour templates added to this ParticleTechnique.
	        */
			size_t _getNumBehaviourTemplates (void) const;

			/** Delete a ParticleBehaviour template that is part of this ParticleTechnique.
	        */
			void _destroyBehaviourTemplate (ParticleBehaviour* behaviourTemplate);

			/** Delete all ParticleBehaviour templates of this ParticleTechnique.
	        */
			void _destroyAllBehaviourTemplates (void);

			//-------------------------------------- Extern --------------------------------------
			/** Create an Extern and add it to this ParticleTechnique.
	        */
			Extern* createExtern (const String& externType);

			/** Add an Extern to this ParticleTechnique.
			@param
				Pointer to a previously created Extern object.
	        */
			void addExtern (Extern* externObject);

			/** Remove an Extern from the ParticleTechnique, but don´t delete it.
			@param
				Pointer to an Extern object.
	        */
			void removeExtern (Extern* externObject);

			/** Get an Extern. Search by index.
	        */
			Extern* getExtern (size_t index) const;

			/** Get an Extern. Search by name.
	        */
			Extern* getExtern (const String& externName) const;

			/** Get an Extern. Search by type.
	        */
			Extern* getExternType (const String& externType) const;

			/** Get the number of Externs added to this ParticleTechnique.
	        */
			size_t getNumExterns (void) const;

			/** Delete an Extern that is part of this ParticleTechnique. Search by index.
	        */
			void destroyExtern (size_t index);

			/** Delete an Extern that is part of this ParticleTechnique.
	        */
			void destroyExtern (Extern* externObject);

			/** Delete all Externs of this ParticleTechnique.
	        */
			void destroyAllExterns (void);

			//-------------------------------------- Rest --------------------------------------
			/** Update the renderqueue.
			@remarks
				This function invokes the renderer and updates the renderqueue of that renderer. This is not
				only performed for this ParticleTechnique, but also for the pooled ParticleTechniques if
				available. Updating the renderqueue causes the particles to be actually rendered.
	        */
			void _updateRenderQueue(Ogre::RenderQueue* queue);

			/** Set the renderqueue group in the renderer
			*/
			void setRenderQueueGroup(uint8 queueId);

			/** Perform some initialisation activities.
			@remarks
				To reduce initialisation activities as soon as the particle system is started, these activities 
				can also be performed in front.
	        */
			void _prepare(void);

			/** V1.5: Perform some cleanup activities.
	        */
			void _unprepare(void);

			/** Perform (un)initialisation activities of system elements.
	        */
			void _prepareSystem(void);
			void _unprepareSystem(void);

			/** Perform (un)initialisation activities of the technique itself.
	        */
			void _prepareTechnique(void);
			void _unprepareTechnique(void);

			/** (Un)initialise visual particles if needed.
	        */
			void _prepareVisualParticles(void);
			void _unprepareVisualParticles(void);

			/** Perform (un)initialisation activities of the renderer.
	        */
			void _prepareRenderer(void);
			void _unprepareRenderer(void);

			/** Perform (un)initialisation activities of emitters.
	        */
			void _prepareEmitters(void);
			void _unprepareEmitters(void);

			/** Perform (un)initialisation activities of affectors.
	        */
			void _prepareAffectors(void);
			void _unprepareAffectors(void);

			/** Perform (un)initialisation activities of behaviours.
	        */
			void _prepareBehaviours(void);
			void _unprepareBehaviours(void);

			/** Perform (un)initialisation activities of externs.
	        */
			void _prepareExterns(void);
			void _unprepareExterns(void);

			/** Update this ParticleTechnique.
			@remarks
				Updating the ParticleTechnique actually sets all particles in motion. The ParticleTechnique is
				only updated if the ParticleSystem to which the ParticleTechnique belongs is started.
	        */
			void _update(Real timeElapsed);

			/** Is called as soon as a new emitter is added or deleted, which leads to a re-evaluation of the 
				emitted objects.
			@remarks
				Emitters are able to emit other objects (emitters, techniques, affectors) besides visual 
				particles, and removing or adding an emitter could lead to a broken chain of references. This 
				means that 1). Emitters that were emitted by a deleted emitter, aren't emitted anymore. 2).
				An added emitter could emit another emitter (or affector); the other emitter has to know that 
				it will be emitted. 3). Another emitter could emit the emitter that is added; the added emitter 
				has to know that. 4). If an already existing emitter sets its emitsName the chain is broken.
			@par
				This method runs through the whole chain of emitters each time a new emitter is 
				added or an emitter is deleted. This has a performance penalty, but since the number of emitters
				is usually not very large we can get away with it.
			@par
				If an emitter is deleted and this emitter is also emitted itself, the effect of deletion is not always
				instantly noticable. Emitted emitters are part of the particle pool and are NOT deleted if the base
				emitter (from which the pooled emitters are cloned) is deleted.
			*/
			void _notifyEmissionChange(void);

			/** Implementation of the _notifyAttached, needed for each technique that is part of a 
				particle system.
			@remarks
				Delegates to the renderer.
			*/
			void _notifyAttached(Ogre::Node* parent, bool isTagPoint = false);

			/** Notify the pooled techniques that its parent system has been attached or detached.
			@remarks
				This is done for emitted ParticleTechniques.
	        */
			void _notifyAttachedPooledTechniques(Ogre::Node* parent, bool isTagPoint);

			/** Implementation of the _notifyCurrentCamera, needed for each technique that is part of a 
				particle system.
			@remarks
				Delegates to the renderer.
			*/
			void _notifyCurrentCamera(Camera* camera);

			/** Notify the pooled techniques with the current camera.
			@remarks
				This is done for emitted ParticleTechniques.
	        */
			void _notifyCurrentCameraPooledTechniques(Camera* camera);

			/** Implementation of the _notifyParticleResized, needed for each technique that is part of a 
				particle system.
			@remarks
				Delegates to the renderer.
			*/
			void _notifyParticleResized(void);

			/** Perform activities when a ParticleTechnique is started.
			@remarks
				This is only used to set some attributes to their default value, so a re-start can be performed.
				Note, that one cannot assume that the _prepare() function has been called, so don´t perform 
				initialisation activities on objects that are not created yet (for instance the renderer).
			*/
			void _notifyStart (void);

			/** Perform activities when a ParticleTechnique is stopped.
			*/
			void _notifyStop (void);

			/** if stopFade is set, emitter must not emit new particles anymore
			*/
			bool isStopFade(void);

			/** Perform activities when a ParticleTechnique is paused.
			*/
			void _notifyPause (void);

			/** Perform activities when a ParticleTechnique is resumed.
			*/
			void _notifyResume (void);

			/** Validate whether a particle is expired.
			*/
			inline bool _isExpired(Particle* particle, Real timeElapsed);

			/** Forces emission of particles.
			@remarks
				The number of requested particles are the exact number that are emitted. No down-scalling is applied.
			*/
			void forceEmission(ParticleEmitter* emitter, unsigned requested);

			/** Emits particles of the first emitter it encounters in this technique.
			*/
			void forceEmission(const Particle::ParticleType particleType, unsigned requested);

			/** Copy the attributes of this ParticleTechnique to another ParticleTechnique.
			*/
			virtual void copyAttributesTo (ParticleTechnique* technique);

			/** Get the Lod index.
			@remarks
				The Lod index determines at which distance this ParticleTechnique is active. This has only effect
				if the Lod distances of the ParticleSystem to which this ParticleTechnique belongs have been defined.
			*/
			inline unsigned short getLodIndex(void) const {return mLodIndex;};

			/** Set the Lod index.
			*/
			void setLodIndex(unsigned short lodIndex) {mLodIndex = lodIndex;};

			/** Determine which techniques, affectors, emitters will be emitted.
			@remarks
				All objects that are able to be emitted will get an indication when they are emitted. This function
				runs through all ParticleEmitters and if the ParticleEmitter emits objects other than visual particles,
				these objects are marked.
	        */
			void _markForEmission(void);

			/** Determines which techniques, affectors, emitters will be emitted (or not) by the given emitter.
	        */
			void _markForEmission(ParticleEmitter* emitter, bool mark = true);

			/** Notify updating the axis aligned bounding box.
			@remarks
				The Particle System calls this function to make the ParticleTechnique calculating its mWorldAABB.
	        */
			void _notifyUpdateBounds(void);

			/** Reset the bounds.
	        */
			void _resetBounds(void);

			/** Notify that the Particle System is rescaled.
	        */
			void _notifyRescaled(const Vector3& scale);

			/** Notify that the velocity is rescaled.
	        */
			void _notifyVelocityRescaled(const Real& scaleVelocity);

			/** Returns the world aabb.
			*/
			inline const AxisAlignedBox& getWorldBoundingBox(void) const {return mWorldAABB;}

			/** Sort the visual particles.
			@remarks
				Only the visual particles are sorted, because sorting non-visual particles doesn't make sense.
			*/
			void _sortVisualParticles(Camera* camera);

			/** 
			*/
			void setWidthCameraDependency(CameraDependency* cameraDependency);
			void setWidthCameraDependency(Real squareDistance, bool inc);

			/** 
			*/
			CameraDependency* getWidthCameraDependency(void) const;

			/** 
			*/
			void setHeightCameraDependency(CameraDependency* cameraDependency);
			void setHeightCameraDependency(Real squareDistance, bool inc);

			/** 
			*/
			CameraDependency* getHeightCameraDependency(void) const;

			/** 
			*/
			void setDepthCameraDependency(CameraDependency* cameraDependency);
			void setDepthCameraDependency(Real squareDistance, bool inc);

			/** 
			*/
			CameraDependency* getDepthCameraDependency(void) const;

			/** 
			*/
			size_t getNumberOfEmittedParticles(void);

			/** 
			*/
			size_t getNumberOfEmittedParticles(Particle::ParticleType particleType);

			/** Expire all active (emitted) particles and put them back into the pool.
			*/
			void _initAllParticlesForExpiration(void);

			/** Put all emitted particles back into the pool.
			*/
			void lockAllParticles(void);

			/** Reset the visual data in the pool.
			@remarks
				Visual particles may keep some additional visual data that needs to be reset in some cases.
				This function puts all particles back into the pool.
			*/
			void initVisualDataInPool(void);

			/** Returns a pointer to the particle pool.
			@remarks
				Caution: Only use this function if you know what you are doing.  If this function is called from a function that
				is already iterating over the pool, unexpected behaviour can occur.
			*/
			ParticlePool* _getParticlePool(void);

			/** 
			*/
			bool isKeepLocal(void) const;

			/** If this attribute is set to 'true', the particles are emitted relative to the technique 
			*/
			void setKeepLocal(bool keepLocal);

			/** Transforms the particle position in a local position relative to the technique
			*/
			inline bool makeParticleLocal(Particle* particle);

			/** Returns the Spatial Hashtable.
			*/
			SpatialHashTable<Particle*>* getSpatialHashTable(void) const;

			/** Returns true if spatial hashing is used.
			*/
			bool isSpatialHashingUsed(void) const;

			/** Defines whether spatial hashing is used.
			*/
			void setSpatialHashingUsed(bool spatialHashingUsed);

			/** Returns the celsize used in spatial hashing.
			*/
			unsigned short getSpatialHashingCellDimension(void) const;

			/** Set the celsize used in spatial hashing. A cel represents a small part of the 3d space in which 
				particles may exist. The size of the cel is the same for both x, y and z dimension.
			*/
			void setSpatialHashingCellDimension(unsigned short spatialHashingCellDimension);
			
			/** Return the size of the overlap.
			*/
			unsigned short getSpatialHashingCellOverlap(void) const;

			/** Set the size of the overlap.
			@remarks
				The cell overlap is used to put a particle in multiple cells if needed. This is a better way to 
				determine nearby particles. A particle in one cell is not considered nearby in relation to a 
				particle in another cel, although they can be nearby in terms of their world position. If you want to
				inspect all particles positioned in a radius around a central particle, and that particle is close
				to the border of a cel, you miss a few particles in the neighbouring cell that are nearby. By 
				defining an overlap you duplicate particles in multiple cells, but you are able to determine all 
				nearby particles.
			@par
				Because particle are duplicated in multiple cells, you have to consider that validations between
				2 particles in one cell are also performed in another cell. Set a flag to a particle, indicating that
				it has been validated.
			*/
			void setSpatialHashingCellOverlap(unsigned short spatialHashingCellOverlap);

			/** Returns the size of the hashtable used in spatial hashing.
			*/
			unsigned int getSpatialHashTableSize(void) const;

			/** Sets the size of the hashtable used in spatial hashing.
			*/
			void setSpatialHashTableSize(unsigned int spatialHashTableSize);

			/** Return the interval when the spatial hashtable is updated.
			*/
			Real getSpatialHashingInterval(void) const;

			/** Set the interval when the spatial hashtable is updated.
			*/
			void setSpatialHashingInterval(Real spatialHashingInterval);

			/** Return the indication whether to use only the particle position (false) or take the particle size
				into account (true).
			*/
			bool isSpatialHashingParticleSizeUsed(void) const;

			/** Set the indication whether to use only the particle position (false) or take the particle size
				into account (true).
			*/
			void setSpatialHashingParticleSizeUsed(bool spatialHashingParticleSizeUsed);

			/** Return the maximum velocity a particle can have, even if the velocity of the particle has been set higher (either by 
			    initialisation of the particle or by means of an affector).
			*/
			Real getMaxVelocity(void) const;

			/** Set the maximum velocity a particle can have.
			*/
			void setMaxVelocity(Real maxVelocity);

			/** Add a TechniqueListener, which gets called in case a particle is emitted or expired.
			*/
			void addTechniqueListener (TechniqueListener* techniqueListener);

			/** Removes the TechniqueListener, but it isn't destroyed.
			*/
			void removeTechniqueListener (TechniqueListener* techniqueListener);

			/** Generates debug information, such as max. used particles in a technique.
			*/
			void logDebug(void);

			/** Returns the velocity scale, defined in the particle system, but passed to the technique for convenience.
	        */
			Real getParticleSystemScaleVelocity(void) const;

			/** Forwards an event to the parent particle system.
	        */
			void pushEvent(ParticleUniverseEvent& particleUniverseEvent);

		protected:

			/** Convenient function to push an event.
			*/
			void _pushTechniqueEvent(EventType eventType);

			/** Functor to sort by direction.
			*/
			struct DirectionSorter
			{
				Vector3 sortDirection;

				DirectionSorter(const Vector3& dir);
				float operator()(Particle* p) const;
			};

			/** Functor to sort by distance.
			*/
			struct DistanceSorter
			{
				Vector3 sortPosition;

				DistanceSorter(const Vector3& pos);
				float operator()(Particle* p) const;
			};

			/** Sort the particles.
	        */
			static RadixSort<Pool<VisualParticle>::PoolList, Particle*, float> mRadixSorter;

			/** Initialises a particle by another object (if available).
	        */
			void _initParticleForEmission(Particle* particle);

			/** Initialise the ParticleTechnique before it is emitted itself.
	        */
			virtual void _initForEmission(void);

			/** Initialise the ParticleTechnique before it is expired itself.
	        */
			virtual void _initForExpiration(ParticleTechnique* technique, Real timeElapsed);

			/** Updates the renderqueue of pooled ParticleTechniques.
			@remarks
				It is possible to emit ParticleTechniques, where these ParticleTechniques are created by and stored
				in the particle pool. Since they aren't the responsibility of the ParticleSystem itself, they
				also aren't updated by the ParticleSystem. This means that the ParticleTechnique that emits the
				pooled ParticleTechniques, must update them.
	        */
			void _updateRenderQueuePooledTechniques(Ogre::RenderQueue* queue);

			/** Reset all MarkForEmission values (to false) for all techniques, affectors and emitters.
	        */
			void _resetMarkForEmission(void);

			/** Apply actions on the emitted particles (expire, affect, observe, ...).
			*/
			void _processParticles(Real timeElapsed);

			/** Determine the dependencies and process them.
			*/
			void _processDependencies(void);

			/** Copies the pooled affectors from the pool to a separate list.
			@remarks
				Unfortunately, the particle pool can only be iterated once at a time. This prevents simultanious
				iteration of both particles and affectors, so the pooled affectors are stored in a temporary list.
				The benefit of a separate affector list is that it allows fast traversing once it has been created.
			*/
			void _extractPooledAffectors(void);

			/** If spatial hashing is required, the particle will be put in a hashtable.
			*/
			void _processSpatialHashing(Particle* particle, Real timeElapsed);

			/** Function that affects a particle by the affectors that are part of this particle technique.
			*/
			void _processAffectors(Particle* particle, Real timeElapsed, bool firstParticle);

			/** Perform some activities before all individual particles are processed.
			*/
			void _preProcessParticles(Real timeElapsed);

			/** Perform some activities after all individual particles are processed.
			*/
			void _postProcessParticles(Real timeElapsed);

			/** A Spatial Hash table is used if particles approach each other and the mutual distance is important.
			    This function is called for each particle if the use of a Spatial Hash table is set to true.
			*/
			void _postProcessSpatialHashing(void);

			/** Function that uses an external source - outside the partice technique - to affect the particle.
			*/
			void _processExternals(Particle* particle, Real timeElapsed, bool firstParticle);

			/** Some renderers also perform additional activities on particles (besides renderering).
			*/
			void _processRenderer(Particle* particle, Real timeElapsed, bool firstParticle);

			/** Perform actions on a single particle after each update.
			@remarks
				Besides affecting particles by affectors (which apply a global effect on a particle), particles
				can also affect themselves.
			*/
			inline void _processParticleSelf(Particle* particle, Real timeElapsed, bool firstParticle);

			/** Perform actions if a particle gets expired.
			*/
			void _initParticleForExpiration(Particle* particle, Real timeElapsed);

			/** Observers are classes that ´watch´ at a particle and perform an action as soon as a certain 
				threshold is exceeded. This function calls all observers.
			*/
			void _processObservers(Particle* particle, Real timeElapsed, bool firstParticle);

			/** Call the emitters to emit particles.
			*/
			void _emitParticles(Real timeElapsed);

			/** Actually executes emission of particles.
			*/
			void _executeEmitParticles(ParticleEmitter* emitter, unsigned requested, Real timeElapsed);

			/** Apply motion to a particle.
			*/
			inline void _processMotion(Particle* particle, Real timeElapsed, bool firstParticle);

			/** Parent Particle System of this technique.
	        */
			ParticleSystem* mParentSystem;

			/** Name of the technique (optional).
	        */
			String mName;

			/** Indication whether elements of the the particle pool are initialized.
	        */
			bool mVisualParticlePoolIncreased;
			bool mParticleEmitterPoolIncreased;
			bool mParticleTechniquePoolIncreased;
			bool mParticleAffectorPoolIncreased;
			bool mParticleSystemPoolIncreased;

			/** The maximum number of visual particles that can be emitted.
	        */
			size_t mVisualParticleQuota;
			
			/** The maximum number of emitter particles that can be emitted.
	        */
			size_t mEmittedEmitterQuota;

			/** The maximum number of technique particles that can be emitted.
	        */
			size_t mEmittedTechniqueQuota;

			/** The maximum number of affector particles that can be emitted.
	        */
			size_t mEmittedAffectorQuota;

			/** The maximum number of particle system particles that can be emitted.
	        */
			size_t mEmittedSystemQuota;

			/** List containing registered ParticleEmitters.
	        */
			ParticleEmitterList mEmitters;

			/** List containing registered ParticleAffectors.
	        */
			ParticleAffectorList mAffectors;

			/** List containing registered ParticleObservers.
	        */
			ParticleObserverList mObservers;

			/** List containing registered Behaviour templates.
			@remarks
				Note, that the ParticleBehaviours are only used as a blueprint. The actual ParticleBehaviour
				objects that are used in the ParticleUniverse plugin are attached to a Particle.
	        */
			Particle::ParticleBehaviourList mBehaviourTemplates;

			/** List containing registered Externs.
	        */
			ExternList mExterns;

			/** Particle pool.
			@remarks
				The particle pool contains precreated particles. In most cases these particles are visual particles,
				but the pool can also contain ParticleEmitters, ParticleAffectors and ParticleTechniques that are
				emitted.
	        */
			ParticlePool mPool;

			/** Because the particle pool is not capable to iterate multiple times at once, an extraction of the 
				pooled ParticleAffectors is made.
	        */
			ParticleAffectorList mCopyOfPooledAffectors;

			/** Particle Renderer.
	        */
			ParticleRenderer* mRenderer;

			/** Indication whether _notifyEmissionChange() must be suppressed or not.
			@remarks
				Default is true
	        */
			bool mSuppressNotifyEmissionChange;

			/** Name of the material used in the renderer.
	        */
			String mMaterialName;

			/** Default width of each visual particle.
	        */
			Real mDefaultWidth;

			/** Default height of each visual particle.
	        */
			Real mDefaultHeight;

			/** Default depth of each visual particle.
	        */
			Real mDefaultDepth;

			/** Lod level.
			@remarks
				The mLodIndex corresponds to one of the lod distances set by the ParticleSystem. If the distance
				between the ParticleTechnique and the camera corresponds with the index of the ParticleTechnique,
				the ParticleTechnique will be enabled, otherwise the ParticleTechnique is disabled.
			@par
				Note, that mLodIndex only has a meaning if the lod distances are set by the ParticleSystem, otherwise
				it is ignored (which enables all ParticleTechniques).
	        */
			unsigned short mLodIndex;

			/** Distance between the latest camera that updated the renderqueue and the particle system.
			@remarks
				This is really only usable with a 1 camera set-up, because it always calculates the square
				distance between the technique and the latest camera update and you´ll never know which
				camera it was.
				The reason to have this attribute is to be able to apply LOD to a Particle System and Particle
				System LOD is only effective with 1 camera (otherwise, with more camera´s there is a risk that 
				more than 1 Particle Technique is emitting)
	        */
			Real mCameraSquareDistance;

			/** CameraDependency that causes a decrease (or increase if needed) of the particle width.
			*/
			CameraDependency* mWidthCameraDependency;

			/** CameraDependency that causes a decrease (or increase if needed) of the particle height.
			*/
			CameraDependency* mHeightCameraDependency;

			/** CameraDependency that causes a decrease (or increase if needed) of the particle depth.
			*/
			CameraDependency* mDepthCameraDependency;

			/** Helper Factory to create a CameraDependency.
	        */
			CameraDependencyFactory mCameraDependencyFactory;

			/** Indication used to determine whether the Extern objects must be prepared.
	        */
			bool mPrepareExtern;

			/** Indication used to determine whether the Behaviour objects must be prepared.
	        */
			bool mPrepareBehaviour;

			/** Indication used to determine whether the Affector objects must be prepared.
	        */
			bool mPrepareAffector;

			/** Indication used to determine whether the Emitter objects must be prepared.
	        */
			bool mPrepareEmitter;

			/** World AABB.
			@remarks
				Because all positions are in worldspace, the ParticleTechnique's worldspace bounding box is
				calculated.
	        */
			AxisAlignedBox mWorldAABB;

			/** Determines whether the Particle Technique should update their bounds.
	        */
			bool mUpdateWorldAABB;

			/** Min/max extends of the WorldAABB.
	        */
			Vector3 mMinWorldExtend;
			Vector3 mMaxWorldExtend;
			bool mHasExtents;

			/** Determines whether particle positions should be kept local in relation to the technique.
	        */
			bool mKeepLocal;

			/** Similar as _notifyStart(), but now for the pooled components.
			*/
			void _notifyStartPooledComponents(void);

			/** Similar as _notifyStop(), but now for the pooled components.
			*/
			void _notifyStopPooledComponents(void);

			/** Similar as _notifyPause(), but now for the pooled components.
			*/
			void _notifyPausePooledComponents(void);

			/** Similar as _notifyResume(), but now for the pooled components.
			*/
			void _notifyResumePooledComponents(void);

			/** Although the scale is on a Particle System level, it is stored here also, because this value is often 
				used. It is a derived value, so it has not get a get and set function.
			*/
			Vector3 _mParticleSystemScale;

			/** Although the velocity scale is on a Particle System level, it is stored here also, because this 
				value is often used. It is a derived value, so it has not get a get and set function.
			*/
			Real _mParticleSystemScaleVelocity;

			/** If needed, the particles can be structured in a spatial hashtable. This is a fast way to store 
				particles that are near each other in 3d space. The hashtable can be used for inter-particle
				collision or nearest neighbour search.
			@remarks
				We are using 2 hashtables. One table is filled during frame 1 and used in frame 2, while the other 
				table is used in frame 1 and filled in frame 2. By swapping the tables after each frame we have
				the possibility to compare each particle in the processParticles loop with the particles in the
				currently used hashtable.
			*/
			bool mIsSpatialHashingUsed;
			bool mIsSpatialHashingInitialised;
			unsigned short mSpatialHashingCellDimension; // Cell size
			unsigned short mSpatialHashingCellOverlap; // Amount of overlap between each cell
			unsigned int mSpatialHashTableSize;
			SpatialHashTable<Particle*>* mSpatialHashTableA;
			SpatialHashTable<Particle*>* mSpatialHashTableB;
			SpatialHashTable<Particle*>* mCurrentSpatialHashTable;

			/** Attributes that determine that the spatial hashtable is the updated after every interval.
	        */
			Real mSpatialHashingInterval;
			Real mSpatialHashingIntervalRemainder;
			bool mSpatialHashingIntervalSet; // If true, use the interval
			bool mSpatialHashingIntervalActivate; // If true, the spatial hashtable is updated (only if the interval is used)

			/** Attributes that limit the velocity of the particles in this technique.
	        */
			Real mMaxVelocity;
			bool mMaxVelocitySet;

			/** List of TechniqueListeners
	        */
			TechniqueListenerList mTechniqueListenerList;

			/** Keeps track of maximum number of emitted particles.
	        */
			size_t mMaxNumVisualParticles;
			size_t mMaxNumEmitterParticles;
			size_t mMaxNumTechniqueParticles;
			size_t mMaxNumAffectorParticles;
			size_t mMaxNumSystemParticles;
	};
}
#endif
