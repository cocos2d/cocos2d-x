/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#include "ParticleUniversePCH.h"

#ifndef PARTICLE_UNIVERSE_EXPORTS
#define PARTICLE_UNIVERSE_EXPORTS
#endif

#include "OgreMaterialManager.h"
#include "ParticleUniverseCamera.h"

namespace ParticleUniverse
{
	RadixSort<Pool<VisualParticle>::PoolList, Particle*, float> ParticleTechnique::mRadixSorter;
	
	// Constants
	const bool ParticleTechnique::DEFAULT_ENABLED = true;
	const Vector3 ParticleTechnique::DEFAULT_POSITION(0, 0, 0);
	const bool ParticleTechnique::DEFAULT_KEEP_LOCAL = false;
	const size_t ParticleTechnique::DEFAULT_VISUAL_PARTICLE_QUOTA = 500;
	const size_t ParticleTechnique::DEFAULT_EMITTED_EMITTER_QUOTA = 50;
	const size_t ParticleTechnique::DEFAULT_EMITTED_TECHNIQUE_QUOTA = 10;
	const size_t ParticleTechnique::DEFAULT_EMITTED_AFFECTOR_QUOTA = 10;
	const size_t ParticleTechnique::DEFAULT_EMITTED_SYSTEM_QUOTA = 10;
	const unsigned short ParticleTechnique::DEFAULT_LOD_INDEX = 0;
	const Real ParticleTechnique::DEFAULT_WIDTH = 50;
	const Real ParticleTechnique::DEFAULT_HEIGHT = 50;
	const Real ParticleTechnique::DEFAULT_DEPTH = 50;
	const unsigned short ParticleTechnique::DEFAULT_SPATIAL_HASHING_CELL_DIM = 15;
	const unsigned short ParticleTechnique::DEFAULT_SPATIAL_HASHING_CELL_OVERLAP = 0;
	const size_t ParticleTechnique::DEFAULT_SPATIAL_HASHING_TABLE_SIZE = 50;
	const Real ParticleTechnique::DEFAULT_SPATIAL_HASHING_INTERVAL = 0.05;
	const Real ParticleTechnique::DEFAULT_MAX_VELOCITY = 9999.0f;

	//-----------------------------------------------------------------------
	ParticleTechnique::ParticleTechnique(void) : 
		Particle(),
		IAlias(),
		IElement(),
		mParentSystem(0),
		mName(StringUtil::BLANK),
		mRenderer(0),
		mVisualParticleQuota(DEFAULT_VISUAL_PARTICLE_QUOTA),
		mEmittedEmitterQuota(DEFAULT_EMITTED_EMITTER_QUOTA),
		mEmittedTechniqueQuota(DEFAULT_EMITTED_TECHNIQUE_QUOTA),
		mEmittedAffectorQuota(DEFAULT_EMITTED_AFFECTOR_QUOTA),
		mEmittedSystemQuota(DEFAULT_EMITTED_SYSTEM_QUOTA),
		mVisualParticlePoolIncreased(false),
		mParticleEmitterPoolIncreased(false),
		mParticleTechniquePoolIncreased(false),
		mParticleAffectorPoolIncreased(false),
		mParticleSystemPoolIncreased(false),
		mSuppressNotifyEmissionChange(true),
		mDefaultWidth(DEFAULT_WIDTH),
		mDefaultHeight(DEFAULT_HEIGHT),
		mDefaultDepth(DEFAULT_DEPTH),
		mMaterialName(StringUtil::BLANK),
		mLodIndex(DEFAULT_LOD_INDEX),
		mCameraSquareDistance(0),
		mPrepareExtern(false),
		mPrepareBehaviour(false),
		mPrepareAffector(false),
		mPrepareEmitter(false),
		mWorldAABB(),
		mUpdateWorldAABB(false),
		mMinWorldExtend(Vector3::ZERO),
		mMaxWorldExtend(Vector3::ZERO),
		mHasExtents(false),
		mWidthCameraDependency(0),
		mHeightCameraDependency(0),
		mDepthCameraDependency(0),
		mKeepLocal(DEFAULT_KEEP_LOCAL),
		_mParticleSystemScale(Vector3::UNIT_SCALE),
		_mParticleSystemScaleVelocity(1.0),
		mSpatialHashTableA(0),
		mSpatialHashTableB(0),
		mCurrentSpatialHashTable(0),
		mIsSpatialHashingUsed(false),
		mIsSpatialHashingInitialised(false),
		mSpatialHashingCellDimension(DEFAULT_SPATIAL_HASHING_CELL_DIM),
		mSpatialHashingCellOverlap(DEFAULT_SPATIAL_HASHING_CELL_OVERLAP),
		mSpatialHashTableSize(DEFAULT_SPATIAL_HASHING_TABLE_SIZE),
		mSpatialHashingInterval(DEFAULT_SPATIAL_HASHING_INTERVAL),
		mSpatialHashingIntervalRemainder(0.0),
		mSpatialHashingIntervalSet(false),
		mSpatialHashingIntervalActivate(false),
		mMaxVelocity(DEFAULT_MAX_VELOCITY),
		mMaxVelocitySet(false),
		mMaxNumVisualParticles(0),
		mMaxNumEmitterParticles(0),
		mMaxNumTechniqueParticles(0),
		mMaxNumAffectorParticles(0),
		mMaxNumSystemParticles(0)
	{
		particleType = PT_TECHNIQUE;
		mAliasType = AT_TECHNIQUE;
		setMaterialName("BaseWhite");
		mPool.setParentTechnique(this);
	}
	//-----------------------------------------------------------------------
	ParticleTechnique::~ParticleTechnique(void)
	{
		// Bugfix V1.5: Cleanup
		_unprepare();

		// Destroy the spatial hashing tables.
		if (mSpatialHashTableA)
		{
			PU_DELETE_T(mSpatialHashTableA, SpatialHashTable<Particle*>, MEMCATEGORY_SCENE_OBJECTS);
		}
		if (mSpatialHashTableB)
		{
			PU_DELETE_T(mSpatialHashTableB, SpatialHashTable<Particle*>, MEMCATEGORY_SCENE_OBJECTS);
		}

		mSuppressNotifyEmissionChange = true;
		destroyAllEmitters();
		destroyAllAffectors();
		destroyAllObservers();
		_destroyAllBehaviourTemplates();
		destroyAllExterns();
		destroyRenderer();

		if (mWidthCameraDependency)
			mCameraDependencyFactory.destroy(mWidthCameraDependency);

		if (mHeightCameraDependency)
			mCameraDependencyFactory.destroy(mHeightCameraDependency);

		if (mDepthCameraDependency)
			mCameraDependencyFactory.destroy(mDepthCameraDependency);
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_initParticleForEmission(Particle* particle)
	{
		if (!mTechniqueListenerList.empty())
		{
			// Run through all listeners, so it can be used or initialised by another object.
			TechniqueListenerIterator it;
			TechniqueListenerIterator itEnd = mTechniqueListenerList.end();
			for (it = mTechniqueListenerList.begin(); it != itEnd; ++it)
			{
				(*it)->particleEmitted(this, particle);
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_initForEmission(void)
	{
		// The technique itself is emitted.
		Particle::_initForEmission();

		// Emitting a technique is similar as starting one.
		_notifyStart();

		/** Reset the particle pool.
			If the technique is reused (in its parents pool), all particles in the pool must locked again.
		*/
		mPool.lockAllParticles();
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_initForExpiration(ParticleTechnique* technique, Real timeElapsed)
	{
		// The technique itself is expired.
		Particle::_initForExpiration(technique, timeElapsed);

		// Expiring a technique is similar as stopping one.
		_notifyStop();
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_markForEmission(void)
	{
		// Set all indications to false.
		_resetMarkForEmission();

		// Run through all emitters and determine which objects each one emits.
		ParticleEmitterList::iterator emitterIt;
		ParticleEmitterList::iterator emitterItEnd = mEmitters.end();

		for (emitterIt = mEmitters.begin(); emitterIt != emitterItEnd; ++emitterIt)
		{
			_markForEmission(*emitterIt);
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_markForEmission(ParticleEmitter* emitter, bool mark)
	{
		// Determine the type of particle the emitter emits
		// Note, that a visual particle is always marked for emission
		if (emitter->getEmitsType() == PT_TECHNIQUE && mParentSystem)
		{
			// Search the technique to be emitted
			ParticleTechnique* searchTechnique = mParentSystem->getTechnique(emitter->getEmitsName());
			if (searchTechnique)
			{
				searchTechnique->_setMarkedForEmission(mark);
			}
		}
		else if (emitter->getEmitsType() == PT_EMITTER && emitter->getEmitsName() != emitter->getName())
		{
			// Search the emitter to be emitted
			ParticleEmitter* searchEmitter = getEmitter(emitter->getEmitsName());
			if (searchEmitter)
			{
				searchEmitter->_setMarkedForEmission(mark);
			}
		}
		else if (emitter->getEmitsType() == PT_AFFECTOR)
		{
			// Search the affector to be emitted
			ParticleAffector* searchAffector = getAffector(emitter->getEmitsName());
			if (searchAffector)
			{
				searchAffector->_setMarkedForEmission(mark);
			}
		}
		else if (emitter->getEmitsType() == PT_SYSTEM)
		{
			// Don't take action.
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_resetMarkForEmission(void)
	{
		// Run through all emitters and set MarkedForEmission to false.
		ParticleEmitterList::iterator emitterIt;
		ParticleEmitterList::iterator emitterItEnd = mEmitters.end();
		for (emitterIt = mEmitters.begin(); emitterIt != emitterItEnd; ++emitterIt)
		{
			(*emitterIt)->_setMarkedForEmission(false);
		}

		// Run through all affectors and set MarkedForEmission to false.
		ParticleAffectorIterator affectorIt;
		ParticleAffectorIterator affectorItEnd = mAffectors.end();
		for (affectorIt = mAffectors.begin(); affectorIt != affectorItEnd; ++affectorIt)
		{
			(*affectorIt)->_setMarkedForEmission(false);
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_notifyUpdateBounds()
	{
		if (mPool.isEmpty())
		{
			// No particles, reset to null
			_resetBounds();
			mUpdateWorldAABB = false;
		}
		else
		{
			mUpdateWorldAABB = true;
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_resetBounds()
	{
		mWorldAABB.setNull();
		Vector3 position = getDerivedPosition();
		mMinWorldExtend = position;
		mMaxWorldExtend = position;
		mHasExtents = false;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_notifyRescaled(const Vector3& scale)
	{
		_mParticleSystemScale = scale;

		// Notify the emitters
		ParticleEmitterList::iterator itEmitter;
		ParticleEmitterList::iterator itEmitterEnd = mEmitters.end();
		for (itEmitter = mEmitters.begin(); itEmitter != itEmitterEnd; ++itEmitter)
		{
			(*itEmitter)->_notifyRescaled(scale);
		}
		
		// Notify the affectors
		ParticleAffectorIterator itAffector;
		ParticleAffectorIterator itAffectorEnd = mAffectors.end();
		for (itAffector = mAffectors.begin(); itAffector != itAffectorEnd; ++itAffector)
		{
			(*itAffector)->_notifyRescaled(scale);
		}

		// Notify the renderer
		if (mRenderer)
		{
			mRenderer->_notifyRescaled(scale);
		}

		// Notify the observers
		ParticleObserverIterator itObserver;
		ParticleObserverIterator itObserverEnd = mObservers.end();
		for (itObserver = mObservers.begin(); itObserver != itObserverEnd; ++itObserver)
		{
			(*itObserver)->_notifyRescaled(scale);
		}

		// Notify the behaviour
		ParticleBehaviourIterator itBehaviour;
		ParticleBehaviourIterator itBehaviourEnd = mBehaviours.end();
		for (itBehaviour = mBehaviours.begin(); itBehaviour != itBehaviourEnd; ++itBehaviour)
		{
			(*itBehaviour)->_notifyRescaled(scale);
		}

		// Notify the extern
		ExternIterator itExtern;
		ExternIterator itExternEnd = mExterns.end();
		for (itExtern = mExterns.begin(); itExtern != itExternEnd; ++itExtern)
		{
			(*itExtern)->_notifyRescaled(scale);
		}

		// Take the emitted techniques into account
		// Addition to V1.3.1
		ParticleTechnique* technique = static_cast<ParticleTechnique*>(mPool.getFirst(Particle::PT_TECHNIQUE));
		while (!mPool.end(Particle::PT_TECHNIQUE))
		{
			if (technique)
			{
				technique->_notifyRescaled(scale);
			}
			
			technique = static_cast<ParticleTechnique*>(mPool.getNext(Particle::PT_TECHNIQUE));
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_notifyVelocityRescaled(const Real& scaleVelocity)
	{
		_mParticleSystemScaleVelocity = scaleVelocity;

		// Take the emitted techniques into account
		// Addition to V1.3.1
		ParticleTechnique* technique = static_cast<ParticleTechnique*>(mPool.getFirst(Particle::PT_TECHNIQUE));
		while (!mPool.end(Particle::PT_TECHNIQUE))
		{
			if (technique)
			{
				technique->_notifyVelocityRescaled(scaleVelocity);
			}
			
			technique = static_cast<ParticleTechnique*>(mPool.getNext(Particle::PT_TECHNIQUE));
		}
	}
	//-----------------------------------------------------------------------
	size_t ParticleTechnique::getVisualParticleQuota(void) const 
	{
		return mVisualParticleQuota;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setVisualParticleQuota(size_t quota) 
	{
		mVisualParticleQuota = quota;
		mVisualParticlePoolIncreased = false; // Triggers function to increase the number of visual particles
	}
	//-----------------------------------------------------------------------
	size_t ParticleTechnique::getEmittedEmitterQuota(void) const
	{
		return mEmittedEmitterQuota;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setEmittedEmitterQuota(size_t quota)
	{
		mEmittedEmitterQuota = quota;
		mParticleEmitterPoolIncreased = false; // Triggers function to increase the number of emitter particles
	}
	//-----------------------------------------------------------------------
	size_t ParticleTechnique::getEmittedTechniqueQuota(void) const
	{
		return mEmittedTechniqueQuota;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setEmittedTechniqueQuota(size_t quota)
	{
		mEmittedTechniqueQuota = quota;
		mParticleTechniquePoolIncreased = false; // Triggers function to increase the number of technique particles
	}
	//-----------------------------------------------------------------------
	size_t ParticleTechnique::getEmittedAffectorQuota(void) const
	{
		return mEmittedAffectorQuota;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setEmittedAffectorQuota(size_t quota)
	{
		mEmittedAffectorQuota = quota;
		mParticleAffectorPoolIncreased = false; // Triggers function to increase the number of affector particles
	}
	//-----------------------------------------------------------------------
	size_t ParticleTechnique::getEmittedSystemQuota(void) const
	{
		return mEmittedSystemQuota;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setEmittedSystemQuota(size_t quota)
	{
		mEmittedSystemQuota = quota;
		mParticleSystemPoolIncreased = false; // Triggers function to increase the number of particle system particles
	}
	//-----------------------------------------------------------------------
	const Real ParticleTechnique::getDefaultWidth(void) const
	{
		return mDefaultWidth;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setDefaultWidth(const Real width)
	{
		mDefaultWidth = width;
		if (mRenderer)
		{
			mRenderer->_notifyDefaultDimensions(_mParticleSystemScale.x * mDefaultWidth, 
				_mParticleSystemScale.y * mDefaultHeight, 
				_mParticleSystemScale.z * mDefaultDepth);
		}
	}
	//-----------------------------------------------------------------------
	const Real ParticleTechnique::getDefaultHeight(void) const
	{
		return mDefaultHeight;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setDefaultHeight(const Real height)
	{
		mDefaultHeight = height;
		if (mRenderer)
		{
			mRenderer->_notifyDefaultDimensions(_mParticleSystemScale.x * mDefaultWidth, 
				_mParticleSystemScale.y * mDefaultHeight, 
				_mParticleSystemScale.z * mDefaultDepth);
		}
	}
	//-----------------------------------------------------------------------
	const Real ParticleTechnique::getDefaultDepth(void) const
	{
		return mDefaultDepth;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setDefaultDepth(const Real depth)
	{
		mDefaultDepth = depth;
		if (mRenderer)
		{
			mRenderer->_notifyDefaultDimensions(_mParticleSystemScale.x * mDefaultWidth, 
				_mParticleSystemScale.y * mDefaultHeight, 
				_mParticleSystemScale.z * mDefaultDepth);
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::suppressNotifyEmissionChange(bool suppress)
	{
		mSuppressNotifyEmissionChange = suppress;
	}
	//-----------------------------------------------------------------------
	const String& ParticleTechnique::getMaterialName(void) const
	{
		return mMaterialName;
	}
	//-----------------------------------------------------------------------
	const Ogre::MaterialPtr ParticleTechnique::getMaterial(void) const
	{
		String resourceGroupName = mParentSystem ? mParentSystem->getResourceGroupName() : Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
		return Ogre::MaterialManager::getSingleton().load(mMaterialName, resourceGroupName);
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setMaterialName(const String& materialName)
	{
        mMaterialName = materialName;
		if (mRenderer)
		{
			if (ParticleSystemManager::getSingletonPtr()->isAutoLoadMaterials())
			{
				String resourceGroupName = mParentSystem ? mParentSystem->getResourceGroupName() : Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
                

				Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().load(mMaterialName, resourceGroupName);
                
                mRenderer->_setMaterialName(mMaterialName);
                
                
			}
		}
	}
	//-----------------------------------------------------------------------
	ParticleEmitter* ParticleTechnique::createEmitter(const String& emitterType)
	{
		assert(emitterType != StringUtil::BLANK && "emitterType is empty!");
		ParticleEmitter* emitter = ParticleSystemManager::getSingletonPtr()->createEmitter(emitterType);
		addEmitter(emitter);
		return emitter;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::addEmitter (ParticleEmitter* emitter)
	{
		assert(emitter && "Emitter is null!");
		mEmitters.push_back(emitter);
		emitter->setParentTechnique(this);
		//emitter->_notifyRescaled(_mParticleSystemScale);
		mPrepareEmitter = true;
		_notifyEmissionChange();
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::removeEmitter(ParticleEmitter* emitter)
	{
		assert(emitter && "Emitter is null!");
		ParticleEmitterList::iterator it;
		ParticleEmitterList::iterator itEnd = mEmitters.end();
		bool notify = false;
		for (it = mEmitters.begin(); it != itEnd; ++it)
		{
			if (*it == emitter)
			{
				// Must be notified in case the emitter emits non-visual particles
				notify = emitter->getEmitsName() != StringUtil::BLANK;

				// Remove it
				mEmitters.erase(it);
				break;
			}
		}

		// It has no parent anymore
		emitter->setParentTechnique(0);

		// Notify, because an emitter that emitted non-visual objects was removed
		if (notify)
			_notifyEmissionChange();
	}
	//-----------------------------------------------------------------------
	ParticleEmitter* ParticleTechnique::getEmitter (size_t index) const
	{
		assert(index < mEmitters.size() && "Emitter index out of bounds!");
		return mEmitters[index];
	}
	//-----------------------------------------------------------------------
	ParticleEmitter* ParticleTechnique::getEmitter (const String& emitterName) const
	{
		if (emitterName == StringUtil::BLANK)
			return 0;

		ParticleEmitterIterator it;
		ParticleEmitterIterator itEnd = mEmitters.end();
		for (it = mEmitters.begin(); it != itEnd; ++it)
		{
			if ((*it)->getName() == emitterName)
			{
				return *it;
			}
		}
		
		return 0;
	}
	//-----------------------------------------------------------------------
	size_t ParticleTechnique::getNumEmitters (void) const
	{
		return mEmitters.size();
	}
	//-----------------------------------------------------------------------
	size_t ParticleTechnique::getNumEmittedEmitters (void) const
	{
		ParticleEmitterIterator it;
		ParticleEmitterIterator itEnd = mEmitters.end();
		size_t count = 0;
		for (it = mEmitters.begin(); it != itEnd; ++it)
		{
			if ((*it)->_isMarkedForEmission())
			{
				count++;
			}
		}

		return count;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::destroyEmitter(ParticleEmitter* emitter)
	{
		assert(emitter && "Emitter is null!");
		ParticleEmitterList::iterator it;
		ParticleEmitterList::iterator itEnd = mEmitters.end();
		bool notify = false;
		for (it = mEmitters.begin(); it != itEnd; ++it)
		{
			if (*it == emitter)
			{
				// Must be notified in case the emitter emits non-visual particles
				notify = emitter->getEmitsName() != StringUtil::BLANK;

				// Detroy it
				ParticleSystemManager::getSingletonPtr()->destroyEmitter(*it);
				mEmitters.erase(it);
				break;
			}
		}

		// Notify, because an emitter that emitted non-visual objects was deleted
		if (notify)
			_notifyEmissionChange();
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::destroyEmitter (size_t index)
	{
		destroyEmitter(getEmitter(index));
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::destroyAllEmitters(void)
	{
		ParticleEmitterList::iterator it;
		ParticleEmitterList::iterator itEnd = mEmitters.end();
		for (it = mEmitters.begin(); it != itEnd; ++it)
		{
			ParticleSystemManager::getSingletonPtr()->destroyEmitter(*it);
		}
		mEmitters.clear();
	}

	//-----------------------------------------------------------------------
	ParticleAffector* ParticleTechnique::createAffector(const String& affectorType)
	{
		assert(affectorType != StringUtil::BLANK && "affectorType is empty!");
		ParticleAffector* affector = ParticleSystemManager::getSingletonPtr()->createAffector(affectorType);
		addAffector(affector);
		return affector;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::addAffector (ParticleAffector* affector)
	{
		assert(affector && "Affector is null!");
		mAffectors.push_back(affector);
		affector->setParentTechnique(this);
		mPrepareAffector = true;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::removeAffector (ParticleAffector* affector)
	{
		assert(affector && "Affector is null!");
		ParticleAffectorList::iterator it;
		ParticleAffectorIterator itEnd = mAffectors.end();
		for (it = mAffectors.begin(); it != itEnd; ++it)
		{
			if (*it == affector)
			{
				// Remove it
				mAffectors.erase(it);
				break;
			}
		}

		// It has no parent anymore
		affector->setParentTechnique(0);
	}
	//-----------------------------------------------------------------------
	ParticleAffector* ParticleTechnique::getAffector (size_t index) const
	{
		assert(index < mAffectors.size() && "Affector index out of bounds!");
		return mAffectors[index];
	}
	//-----------------------------------------------------------------------
	ParticleAffector* ParticleTechnique::getAffector (const String& affectorName) const
	{
		if (affectorName == StringUtil::BLANK)
			return 0;

		ParticleAffectorIterator it;
		ParticleAffectorIterator itEnd = mAffectors.end();
		for (it = mAffectors.begin(); it != itEnd; ++it)
		{
			if ((*it)->getName() == affectorName)
			{
				return *it;
			}
		}
		
		return 0;
	}
	//-----------------------------------------------------------------------
	size_t ParticleTechnique::getNumAffectors (void) const
	{
		return mAffectors.size();
	}
	//-----------------------------------------------------------------------
	size_t ParticleTechnique::getNumEmittedAffectors (void) const
	{
		ParticleAffectorIterator it;
		ParticleAffectorIterator itEnd = mAffectors.end();
		size_t count = 0;
		for (it = mAffectors.begin(); it != itEnd; ++it)
		{
			if ((*it)->_isMarkedForEmission())
			{
				count++;
			}
		}

		return count;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::destroyAffector(ParticleAffector* affector)
	{
		assert(affector && "Affector is null!");
		ParticleAffectorList::iterator it;
		ParticleAffectorIterator itEnd = mAffectors.end();
		for (it = mAffectors.begin(); it != itEnd; ++it)
		{
			if (*it == affector)
			{
				// Destroy it
				ParticleSystemManager::getSingletonPtr()->destroyAffector(*it);
				mAffectors.erase(it);
				break;
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::destroyAffector (size_t index)
	{
		destroyAffector(getAffector(index));
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::destroyAllAffectors(void)
	{
		ParticleAffectorIterator it;
		ParticleAffectorIterator itEnd = mAffectors.end();
		for (it = mAffectors.begin(); it != itEnd; ++it)
		{
			ParticleSystemManager::getSingletonPtr()->destroyAffector(*it);
		}
		mAffectors.clear();
	}

	//-----------------------------------------------------------------------
	ParticleObserver* ParticleTechnique::createObserver(const String& observerType)
	{
		assert(observerType != StringUtil::BLANK && "observerType is empty!");
		ParticleObserver* observer = ParticleSystemManager::getSingletonPtr()->createObserver(observerType);
		addObserver(observer);
		return observer;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::addObserver (ParticleObserver* observer)
	{
		assert(observer && "Observer is null!");
		mObservers.push_back(observer);
		observer->setParentTechnique(this);
		//observer->_notifyRescaled(_mParticleSystemScale);
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::removeObserver(ParticleObserver* observer)
	{
		assert(observer && "Observer is null!");
		ParticleObserverList::iterator it;
		ParticleObserverIterator itEnd = mObservers.end();
		for (it = mObservers.begin(); it != itEnd; ++it)
		{
			if (*it == observer)
			{
				// Remove it
				mObservers.erase(it);
				break;
			}
		}

		// It has no parent anymore
		observer->setParentTechnique(0);
	}
	//-----------------------------------------------------------------------
	ParticleObserver* ParticleTechnique::getObserver (size_t index) const
	{
		assert(index < mObservers.size() && "Observer index out of bounds!");
		return mObservers[index];
	}
	//-----------------------------------------------------------------------
	ParticleObserver* ParticleTechnique::getObserver (const String& observerName) const
	{
		if (observerName == StringUtil::BLANK)
			return 0;

		ParticleObserverIterator it;
		ParticleObserverIterator itEnd = mObservers.end();
		for (it = mObservers.begin(); it != itEnd; ++it)
		{
			if ((*it)->getName() == observerName)
			{
				return *it;
			}
		}
		
		return 0;
	}
	//-----------------------------------------------------------------------
	size_t ParticleTechnique::getNumObservers (void) const
	{
		return mObservers.size();
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::destroyObserver(ParticleObserver* observer)
	{
		assert(observer && "Observer is null!");
		ParticleObserverList::iterator it;
		ParticleObserverIterator itEnd = mObservers.end();
		for (it = mObservers.begin(); it != itEnd; ++it)
		{
			if (*it == observer)
			{
				// Detroy it
				ParticleSystemManager::getSingletonPtr()->destroyObserver(*it);
				mObservers.erase(it);
				break;
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::destroyObserver (size_t index)
	{
		destroyObserver(getObserver(index));
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::destroyAllObservers(void)
	{
		ParticleObserverIterator it;
		ParticleObserverIterator itEnd = mObservers.end();
		for (it = mObservers.begin(); it != itEnd; ++it)
		{
			ParticleSystemManager::getSingletonPtr()->destroyObserver(*it);
		}
		mObservers.clear();
	}
	//-----------------------------------------------------------------------
	ParticleRenderer* ParticleTechnique::getRenderer(void) const
	{
		return mRenderer;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setRenderer(const String& rendererType)
	{
		if (mRenderer)
		{
			destroyRenderer();
		}

		if (rendererType != StringUtil::BLANK)
		{
			mRenderer = ParticleSystemManager::getSingletonPtr()->createRenderer(rendererType);
			mRenderer->setParentTechnique(this);
			mRenderer->setRendererInitialised(false);
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setRenderer(ParticleRenderer* renderer)
	{
		if (!renderer)
			return;

		if (mRenderer)
		{
			destroyRenderer();
		}

		mRenderer = renderer;
		mRenderer->setParentTechnique(this);
		mRenderer->setRendererInitialised(false);
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::removeRenderer(ParticleRenderer* renderer)
	{
		mRenderer = 0;

		// It has no parent anymore
		renderer->setParentTechnique(0);
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::destroyRenderer(void)
	{
		if (mRenderer)
		{
			ParticleSystemManager::getSingletonPtr()->destroyRenderer(mRenderer);
			mRenderer = 0;
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_addBehaviourTemplate(ParticleBehaviour* behaviourTemplate)
	{
		assert(behaviourTemplate && "Behaviour is null!");
		mBehaviourTemplates.push_back(behaviourTemplate);
		behaviourTemplate->setParentTechnique(this);
		//behaviourTemplate->_notifyRescaled(_mParticleSystemScale);
		mPrepareBehaviour = true;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_removeBehaviourTemplate(ParticleBehaviour* behaviourTemplate)
	{
		assert(behaviourTemplate && "Behaviour is null!");
		ParticleBehaviourList::iterator it;
		ParticleBehaviourIterator itEnd = mBehaviourTemplates.end();
		for (it = mBehaviourTemplates.begin(); it != itEnd; ++it)
		{
			if (*it == behaviourTemplate)
			{
				// Remove it
				mBehaviourTemplates.erase(it);
				break;
			}
		}

		// It has no parent anymore
		behaviourTemplate->setParentTechnique(0);
	}
	//-----------------------------------------------------------------------
	ParticleBehaviour* ParticleTechnique::_getBehaviourTemplate (size_t index) const
	{
		assert(index < mBehaviourTemplates.size() && "Behaviour index out of bounds!");
		return mBehaviourTemplates[index];
	}
	//-----------------------------------------------------------------------
	ParticleBehaviour* ParticleTechnique::_getBehaviourTemplate (const String& behaviourType) const
	{
		if (behaviourType == StringUtil::BLANK)
			return 0;

		ParticleBehaviourIterator it;
		ParticleBehaviourIterator itEnd = mBehaviourTemplates.end();
		for (it = mBehaviourTemplates.begin(); it != itEnd; ++it)
		{
			if ((*it)->getBehaviourType() == behaviourType)
			{
				return *it;
			}
		}
		
		return 0;
	}
	//-----------------------------------------------------------------------
	size_t ParticleTechnique::_getNumBehaviourTemplates (void) const
	{
		return mBehaviourTemplates.size();
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_destroyBehaviourTemplate(ParticleBehaviour* behaviourTemplate)
	{
		assert(behaviourTemplate && "Behaviour is null!");
		ParticleBehaviourList::iterator it;
		ParticleBehaviourIterator itEnd = mBehaviourTemplates.end();
		for (it = mBehaviourTemplates.begin(); it != itEnd; ++it)
		{
			if (*it == behaviourTemplate)
			{
				// Detroy it
				ParticleSystemManager::getSingletonPtr()->destroyBehaviour(*it);
				mBehaviourTemplates.erase(it);
				break;
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_destroyAllBehaviourTemplates (void)
	{
		ParticleBehaviourIterator it;
		ParticleBehaviourIterator itEnd = mBehaviourTemplates.end();
		for (it = mBehaviourTemplates.begin(); it != itEnd; ++it)
		{
			ParticleSystemManager::getSingletonPtr()->destroyBehaviour(*it);
		}
		mBehaviourTemplates.clear();
	}
	//-----------------------------------------------------------------------
	Extern* ParticleTechnique::createExtern (const String& externType)
	{
		assert(externType != StringUtil::BLANK && "externType is empty!");
		Extern* externObject = ParticleSystemManager::getSingletonPtr()->createExtern(externType);
		addExtern(externObject);
		return externObject;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::addExtern (Extern* externObject)
	{
		assert(externObject && "Extern is null!");
		mExterns.push_back(externObject);
		externObject->setParentTechnique(this);
		//externObject->_notifyRescaled(_mParticleSystemScale);
		mPrepareExtern = true;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::removeExtern (Extern* externObject)
	{
		assert(externObject && "ExternObject is null!");
		ExternList::iterator it;
		ExternIterator itEnd = mExterns.end();
		for (it = mExterns.begin(); it != itEnd; ++it)
		{
			if (*it == externObject)
			{
				// Remove it
				mExterns.erase(it);
				break;
			}
		}

		// It has no parent anymore
		externObject->setParentTechnique(0);
	}
	//-----------------------------------------------------------------------
	Extern* ParticleTechnique::getExtern (size_t index) const
	{
		assert(index < mExterns.size() && "Extern index out of bounds!");
		return mExterns[index];
	}
	//-----------------------------------------------------------------------
	Extern* ParticleTechnique::getExtern (const String& externName) const
	{
		if (externName == StringUtil::BLANK)
			return 0;

		ExternIterator it;
		ExternIterator itEnd = mExterns.end();
		for (it = mExterns.begin(); it != itEnd; ++it)
		{
			if ((*it)->getName() == externName)
			{
				return *it;
			}
		}
		
		return 0;
	}
	//-----------------------------------------------------------------------
	Extern* ParticleTechnique::getExternType (const String& externType) const
	{
		if (externType == StringUtil::BLANK)
			return 0;

		ExternIterator it;
		ExternIterator itEnd = mExterns.end();
		for (it = mExterns.begin(); it != itEnd; ++it)
		{
			if ((*it)->getExternType() == externType)
			{
				return *it;
			}
		}
		
		return 0;
	}
	//-----------------------------------------------------------------------
	size_t ParticleTechnique::getNumExterns (void) const
	{
		return mExterns.size();
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::destroyExtern (size_t index)
	{
		destroyExtern(getExtern(index));
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::destroyExtern (Extern* externObject)
	{
		assert(externObject && "ExternObject is null!");
		ExternList::iterator it;
		ExternIterator itEnd = mExterns.end();
		for (it = mExterns.begin(); it != itEnd; ++it)
		{
			if (*it == externObject)
			{
				// Detroy it
				ParticleSystemManager::getSingletonPtr()->destroyExtern(*it);
				mExterns.erase(it);
				break;
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::destroyAllExterns (void)
	{
		ExternIterator it;
		ExternIterator itEnd = mExterns.end();
		for (it = mExterns.begin(); it != itEnd; ++it)
		{
			ParticleSystemManager::getSingletonPtr()->destroyExtern(*it);
		}
		mExterns.clear();
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_updateRenderQueue(Ogre::RenderQueue* queue)
	{
		if (mRenderer && mRenderer->isRendererInitialised())
		{
			if (mEnabled || mParentSystem->isSmoothLod())
			{
				// Update the techniques' own renderqueue or proceed if smooth Lod has been set, 
				// to be able to render the existing particles.
				mRenderer->_updateRenderQueue(queue, &mPool);

				/** Update the renderqueue of the pooled techniques (if available)
					Note, that the _updateRenderQueue() of pooled (emitted) particle systems is NOT
					called from the parent technique (a pooled particle system is still a movable 
					object). Same for _notifyCurrentCamera(), ... etc.
				*/
				_updateRenderQueuePooledTechniques(queue);
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_updateRenderQueuePooledTechniques(Ogre::RenderQueue* queue)
	{
		if (mPool.isEmpty(Particle::PT_TECHNIQUE))
			return;

		ParticleTechnique* technique = static_cast<ParticleTechnique*>(mPool.getFirst(Particle::PT_TECHNIQUE));
		while (!mPool.end(Particle::PT_TECHNIQUE))
		{
			if (technique)
			{
				technique->_updateRenderQueue(queue);
			}
			
			technique = static_cast<ParticleTechnique*>(mPool.getNext(Particle::PT_TECHNIQUE));
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setRenderQueueGroup(uint8 queueId)
	{
		if (mRenderer)
		{
			mRenderer->setRenderQueueGroup(queueId);
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_unprepare(void)
	{
		_unprepareVisualParticles();
		_unprepareSystem();
		_unprepareTechnique();
		_unprepareAffectors();
		_unprepareEmitters();
		_unprepareBehaviours();
		_unprepareRenderer();
		_unprepareExterns();
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_prepare(void)
	{
		/** Prepare all externs.
		*/
		_prepareExterns();

		/** Prepare the renderer.
		*/
		_prepareRenderer();

		/** Prepare all behaviour templates.
		*/
		_prepareBehaviours();

		/** Prepare all emitters.
		*/
		_prepareEmitters();

		/** Prepare all affectors.
		*/
		_prepareAffectors();

		/** Prepare the technique itself.
		*/
		_prepareTechnique();

		/** Prepare the system.
		@remarks
			This only means intialisations within this technique that concer the particle system (i.e. emitted system pool). This doesn't mean
			that the particle system itself is initialised.
		*/
		_prepareSystem();

		/** Create new visual particles if needed.
		*/
		_prepareVisualParticles();

		// Notify rescaling here, so emitted techniques are also taken into account
		// Change in V1.3.1
		_notifyRescaled(_mParticleSystemScale);
		_notifyVelocityRescaled(_mParticleSystemScaleVelocity);
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_prepareSystem(void)
	{
		// Create new particle system particles if the quota has been increased
		if (!mParticleSystemPoolIncreased)
		{
			// Increase the pool dynamically with the quota settings (if quota is large enough)
			mPool.increasePool(Particle::PT_SYSTEM, mEmittedSystemQuota, mBehaviourTemplates, this);
			mParticleSystemPoolIncreased = true;
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_unprepareSystem(void)
	{
		// Destroy the emitted systems in the pool
		mPool.destroyParticles(Particle::PT_SYSTEM);
		mParticleSystemPoolIncreased = false;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_prepareTechnique(void)
	{
		// Create new technique particles if the quota has been increased
		if (!mParticleTechniquePoolIncreased)
		{
			// Increase the pool dynamically with the quota settings (if quota is large enough)
			mPool.increasePool(Particle::PT_TECHNIQUE, mEmittedTechniqueQuota, mBehaviourTemplates, this);
			mParticleTechniquePoolIncreased = true;
		}

		// Prepare the Spatial Hashtables
		if (mIsSpatialHashingUsed && !mIsSpatialHashingInitialised)
		{
			if (mSpatialHashTableA)
			{
				PU_DELETE_T(mSpatialHashTableA, SpatialHashTable<Particle*>, MEMCATEGORY_SCENE_OBJECTS);
			}
			mSpatialHashTableA = PU_NEW_T(SpatialHashTable<Particle*>, MEMCATEGORY_SCENE_OBJECTS)(	mSpatialHashTableSize,
																											mSpatialHashingCellDimension, 
																											mSpatialHashingCellOverlap);

			if (mSpatialHashTableB)
			{
				PU_DELETE_T(mSpatialHashTableB, SpatialHashTable<Particle*>, MEMCATEGORY_SCENE_OBJECTS);
			}
			mSpatialHashTableB = PU_NEW_T(SpatialHashTable<Particle*>, MEMCATEGORY_SCENE_OBJECTS)(	mSpatialHashTableSize,
																											mSpatialHashingCellDimension, 
																											mSpatialHashingCellOverlap);

			mCurrentSpatialHashTable = mSpatialHashTableB;
			mIsSpatialHashingInitialised = true;
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_unprepareTechnique(void)
	{
		// Destroy the emitted techniques in the pool
		mPool.destroyParticles(Particle::PT_TECHNIQUE);
		mParticleTechniquePoolIncreased = false;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_prepareVisualParticles(void)
	{
		if (!mVisualParticlePoolIncreased)
		{
			// Increase the pool dynamically with the quota settings (if quota is large enough)
			mPool.increasePool(Particle::PT_VISUAL, mVisualParticleQuota, mBehaviourTemplates, this);
			mVisualParticlePoolIncreased = true;
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_unprepareVisualParticles(void)
	{
		// Destroy the visual particles in the pool
		mPool.destroyParticles(Particle::PT_VISUAL);
		mVisualParticlePoolIncreased = false;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_prepareRenderer(void)
	{
		if (mRenderer && !mRenderer->isRendererInitialised())
		{
			mRenderer->_prepare(this);
			mRenderer->setRendererInitialised(true); // To be sure
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_unprepareRenderer(void)
	{
		if (mRenderer && mRenderer->isRendererInitialised())
		{
			mRenderer->_unprepare(this);
			mRenderer->setRendererInitialised(false);
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_prepareEmitters(void)
	{
		if (mPrepareEmitter && !mEmitters.empty())
		{
			Hook<ParticleEmitter>::_prepare(&mEmitters, this);
			mPrepareEmitter = false;
		}

		// Create new emitter particles if the quota has been increased
		if (!mParticleEmitterPoolIncreased)
		{
			// Increase the pool dynamically with the quota settings (if quota is large enough)
			mPool.increasePool(Particle::PT_EMITTER, mEmittedEmitterQuota, mBehaviourTemplates, this);
			mParticleEmitterPoolIncreased = true;
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_unprepareEmitters(void)
	{
		if (!mEmitters.empty())
		{
			Hook<ParticleEmitter>::_unprepare(&mEmitters, this);
			mPrepareEmitter = true;
		}

		// Destroy the emitted emitters in the pool
		mPool.destroyParticles(Particle::PT_EMITTER);
		mParticleEmitterPoolIncreased = false;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_prepareAffectors(void)
	{
		if (mPrepareAffector && !mAffectors.empty())
		{
			Hook<ParticleAffector>::_prepare(&mAffectors, this);
			mPrepareAffector = false;
		}

		// Create new affector particles if the quota has been increased
		if (!mParticleAffectorPoolIncreased)
		{
			// Increase the pool dynamically with the quota settings (if quota is large enough)
			mPool.increasePool(Particle::PT_AFFECTOR, mEmittedAffectorQuota, mBehaviourTemplates, this);
			mParticleAffectorPoolIncreased = true;
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_unprepareAffectors(void)
	{
		// Unprepare individual affectors
		if (!mAffectors.empty())
		{
			Hook<ParticleAffector>::_unprepare(&mAffectors, this);
			mPrepareAffector = true;
		}

		// Destroy the emitted affectors in the pool
		mPool.destroyParticles(Particle::PT_AFFECTOR);
		mParticleAffectorPoolIncreased = false;
		mCopyOfPooledAffectors.clear(); // Don't forget to cleanup this one.
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_prepareBehaviours(void)
	{
		/*
		@remarks
			Note, that the ParticleBehaviour template list stored in this ParticleTechnique is ¥prepared¥ 
			and not the ParticleBehaviour objects of each Particle. The ParticleBehaviour templates in 
			this ParticleTechnique can be initialised quickly with certain data, while this data 
			is automatically used in the cloned ParticleBehaviour objects stored in each Particle.
			This prevents that all ParticleBehaviour objects for each Particle in the pool must be
			initialised separately.
		@par
			Preparing the behaviour templates is only done once, so adding new ParticleBehaviour 
			objects doesn't have any effect and will also not be added to the Particles in the pool.
			If ParticleBehaviour objects are added by means of code and not by means of a script,
			make sure that they are added between creation of the ParticleSystem and start/prepare 
			the ParticleSystem.
		*/
		if (mPrepareBehaviour && !mBehaviourTemplates.empty())
		{
			Hook<ParticleBehaviour>::_prepare(&mBehaviourTemplates, this);
			mPrepareBehaviour = false;
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_unprepareBehaviours(void)
	{
		if (!mBehaviourTemplates.empty())
		{
			Hook<ParticleBehaviour>::_unprepare(&mBehaviourTemplates, this);
			mPrepareBehaviour = true;
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_prepareExterns(void)
	{
		// Prepare the Extern objects
		if (mPrepareExtern && !mExterns.empty())
		{
			/* Prepare all extern components
			@remarks
				If a new Extern is added, this code is called again, so take precautions if an 
				extern object isn't allowed to be 'prepared' multiple times.
			*/
			Hook<Extern>::_prepare(&mExterns, this);
			mPrepareExtern = false;
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_unprepareExterns(void)
	{
		if (mPrepareExtern && !mExterns.empty())
		{
			Hook<Extern>::_unprepare(&mExterns, this);
			mPrepareExtern = false;
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_update(Real timeElapsed)
	{
		if (!mEnabled)
		{
			// It is not enabled, but if smoothLod has been set, the already emitted particles are allowed to be processed.
			if (!mParentSystem->isSmoothLod())
			{
				// Technique is disabled and smoothLod isn't set, so don't continue.
				return;
			}
			else if (mPool.isEmpty())
			{
				// Technique is disabled and smoothLod is set, but there are no particles yet/anymore.
				return;
			}
		}

		/*  Perform some initialisation type of activities (if needed). This must be done within the update-loop,
			because settings could be changed (i.e. changing quota), which must trigger a re-initialisation.
		*/
		_prepare();

		if (mParentSystem && mParentSystem->hasTightBoundingBox())
		{
			// Rebuild the bounding box every update
			_resetBounds();
		}

		// Process the emitters
		_emitParticles(timeElapsed);

		// Perform some actions before processing each individual particle
		_preProcessParticles(timeElapsed);

		// Process all particles
		_processParticles(timeElapsed);

		// Perform some actions after processing each individual particle
		_postProcessParticles(timeElapsed);

		latestPosition = getDerivedPosition();
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_notifyEmissionChange(void)
	{
		if (mSuppressNotifyEmissionChange)
			return;

		if (getParentSystem())
		{
			// Notify the parent system.
			getParentSystem()->_notifyEmissionChange();
		}
		else
		{
			// Mark the emitters and affectors (but not the techniques).
			_markForEmission();
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_notifyAttached(Ogre::Node* parent, bool isTagPoint)
	{
		if (mRenderer && mRenderer->isRendererInitialised())
		{
			mRenderer->_notifyAttached(parent, isTagPoint);
		}

		/** Do the same for the the pooled techniques. Pooled Particle Systems are not taken into account, because they are attached
			to their own SceneNode (you really should emit Particle Systems and detach / attach all the time).
		*/
		_notifyAttachedPooledTechniques(parent, isTagPoint);
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_notifyAttachedPooledTechniques(Ogre::Node* parent, bool isTagPoint)
	{
		if (!mPool.isEmpty(Particle::PT_TECHNIQUE))
		{
			ParticleTechnique* technique = static_cast<ParticleTechnique*>(mPool.getFirst(Particle::PT_TECHNIQUE));
			while (!mPool.end(Particle::PT_TECHNIQUE))
			{
				if (technique)
				{
					technique->_notifyAttached(parent, isTagPoint);
				}
			
				technique = static_cast<ParticleTechnique*>(mPool.getNext(Particle::PT_TECHNIQUE));
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_notifyCurrentCamera(Camera* camera)
	{
		if (mRenderer && mRenderer->isRendererInitialised())
		{
			if (mRenderer->isSorted())
			{
				// Although the indication whether to sort the particles is set by the Particle Renderer, the actual 
				// sorting of the particles is performed in the Particle Technique.
				_sortVisualParticles(camera);
			}

			mRenderer->_notifyCurrentCamera(camera);

			// Do the same for the the pooled techniques (if available)
			_notifyCurrentCameraPooledTechniques(camera);
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_notifyCurrentCameraPooledTechniques(Camera* camera)
	{
		if (mPool.isEmpty(Particle::PT_TECHNIQUE))
			return;

		ParticleTechnique* technique = static_cast<ParticleTechnique*>(mPool.getFirst(Particle::PT_TECHNIQUE));
		while (!mPool.end(Particle::PT_TECHNIQUE))
		{
			if (technique)
			{
				technique->_notifyCurrentCamera(camera);
			}
			
			technique = static_cast<ParticleTechnique*>(mPool.getNext(Particle::PT_TECHNIQUE));
		}
	}
	//-----------------------------------------------------------------------
	ParticleTechnique::DirectionSorter::DirectionSorter(const Vector3& direction) : sortDirection(direction)
	{
	}
	//-----------------------------------------------------------------------
	float ParticleTechnique::DirectionSorter::operator()(Particle* p) const
	{
		return sortDirection.dotProduct(p->position);
	}
	//-----------------------------------------------------------------------
	ParticleTechnique::DistanceSorter::DistanceSorter(const Vector3& position) : sortPosition(position)
	{
	}
	//-----------------------------------------------------------------------
	float ParticleTechnique::DistanceSorter::operator()(Particle* p) const
	{
		return - (sortPosition - p->position).squaredLength();
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_sortVisualParticles(Camera* camera)
	{
		if (mRenderer)
        {
			SortMode sortMode = mRenderer->_getSortMode();
			if (sortMode == SM_DIRECTION)
			{
				Vector3 cameraDirection = camera->getDerivedDirection();
				mRadixSorter.sort(mPool.getVisualParticlesList(), DirectionSorter(- cameraDirection));
			}
			else if (sortMode == SM_DISTANCE)
			{
				Vector3 cameraPosition = camera->getDerivedPosition();
				mRadixSorter.sort(mPool.getVisualParticlesList(), DistanceSorter(cameraPosition));
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_notifyParticleResized(void)
	{
		if (mRenderer)
		{
			mRenderer->_notifyParticleResized();
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_notifyStart (void)
	{
#ifdef PU_LOG_DEBUG
		mMaxNumVisualParticles = 0;
		mMaxNumEmitterParticles = 0;
		mMaxNumTechniqueParticles = 0;
		mMaxNumAffectorParticles = 0;
		mMaxNumSystemParticles = 0;
#endif // PU_LOG_DEBUG

		// Added for 1.3 (latestPosition not properly initialised)
        latestPosition = getDerivedPosition();

		// Notify the registered objects that the ParticleSystem/ParticleTechnique starts.
		if (mRenderer)
		{
			mRenderer->_notifyStart();
		}

		if (!mExterns.empty())
		{
			Hook<Extern>::_notifyStart(&mExterns);
		}

		if (!mObservers.empty())
		{
			Hook<ParticleObserver>::_notifyStart(&mObservers);
		}

		// Notify Affectors
		// Remark: Cannot use the templated version, because only affectors not marked for emission are taken into account.
		if (!mAffectors.empty())
		{
			ParticleAffectorIterator affectorIt;
			ParticleAffectorIterator affectorItEnd = mAffectors.end();
			for (affectorIt = mAffectors.begin(); affectorIt != affectorItEnd; ++affectorIt)
			{
				if (!(*affectorIt)->_isMarkedForEmission())
				{
					(*affectorIt)->_notifyStart();
				}
			}
		}

		// Notify Emitters
		// Remark: Cannot use the templated version, because only emitters not marked for emission 
		// are taken into account.
		if (!mEmitters.empty())
		{
			ParticleEmitterIterator emitterIt;
			ParticleEmitterIterator emitterItEnd = mEmitters.end();
			for (emitterIt = mEmitters.begin(); emitterIt != emitterItEnd; ++emitterIt)
			{
				if (!(*emitterIt)->_isMarkedForEmission())
				{
					(*emitterIt)->_notifyStart();
				}
			}
		}

		// Notify the components in the pool
		_notifyStartPooledComponents();

		setEnabled(mOriginalEnabled);
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_notifyStartPooledComponents(void)
	{
		if (mPool.isEmpty())
			return;

		Particle* particle = static_cast<Particle*>(mPool.getFirst());
		while (!mPool.end())
		{
			switch (particle->particleType)
			{
				case Particle::PT_TECHNIQUE:
				{
					ParticleTechnique* technique = static_cast<ParticleTechnique*>(particle);
					technique->_notifyStart();
				}
				break;
				case Particle::PT_SYSTEM:
				{
					ParticleSystem* system = static_cast<ParticleSystem*>(particle);
					system->start();
				}
				break;
				case Particle::PT_EMITTER:
				{
					ParticleEmitter* emitter = static_cast<ParticleEmitter*>(particle);
					emitter->_notifyStart();
				}
				break;
				case Particle::PT_AFFECTOR:
				{
					ParticleAffector* affector = static_cast<ParticleAffector*>(particle);
					affector->_notifyStart();
				}
				break;
			}

			particle = static_cast<Particle*>(mPool.getNext());
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_notifyStop (void)
	{
		// Notify the registered objects that the ParticleSystem/ParticleTechnique stops.
		if (mRenderer)
		{
			mRenderer->_notifyStop();
		}

		if (!mExterns.empty())
		{
			Hook<Extern>::_notifyStop(&mExterns);
		}

		if (!mObservers.empty())
		{
			Hook<ParticleObserver>::_notifyStop(&mObservers);
		}

		// Notify Affectors
		// Remark: Cannot use the templated version, because only affectors not marked for emission are taken into account.
		if (!mAffectors.empty())
		{
			ParticleAffectorIterator affectorIt;
			ParticleAffectorIterator affectorItEnd = mAffectors.end();
			for (affectorIt = mAffectors.begin(); affectorIt != affectorItEnd; ++affectorIt)
			{
				if (!(*affectorIt)->_isMarkedForEmission())
				{
					(*affectorIt)->_notifyStop();
				}
			}
		}

		// Notify Emitters
		// Remark: Cannot use the templated version, because only emitters not marked for emission 
		// are taken into account.
		if (!mEmitters.empty())
		{
			ParticleEmitterIterator emitterIt;
			ParticleEmitterIterator emitterItEnd = mEmitters.end();
			for (emitterIt = mEmitters.begin(); emitterIt != emitterItEnd; ++emitterIt)
			{
				if (!(*emitterIt)->_isMarkedForEmission())
				{
					(*emitterIt)->_notifyStop();
				}
			}
		}

		// Notify the components in the pool.
		_notifyStopPooledComponents();

		// Expire all particles at once.
		_initAllParticlesForExpiration();

		// Reset the bounding box of this technique.
		_resetBounds();

#ifdef PU_LOG_DEBUG
		logDebug();
#endif // PU_LOG_DEBUG
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_notifyStopPooledComponents(void)
	{
		if (mPool.isEmpty())
			return;

		Particle* particle = static_cast<Particle*>(mPool.getFirst());
		while (!mPool.end())
		{
			switch (particle->particleType)
			{
				case Particle::PT_TECHNIQUE:
				{
					ParticleTechnique* technique = static_cast<ParticleTechnique*>(particle);
					technique->_notifyStop();
				}
				break;
				case Particle::PT_SYSTEM:
				{
					ParticleSystem* system = static_cast<ParticleSystem*>(particle);
					system->stop();
				}
				break;
				case Particle::PT_EMITTER:
				{
					ParticleEmitter* emitter = static_cast<ParticleEmitter*>(particle);
					emitter->_notifyStop();
				}
				break;
				case Particle::PT_AFFECTOR:
				{
					ParticleAffector* affector = static_cast<ParticleAffector*>(particle);
					affector->_notifyStop();
				}
				break;
			}

			particle = static_cast<Particle*>(mPool.getNext());
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_notifyPause (void)
	{
		/** The renderer, Externs and Observers aren't notified. There is no specific reasons for that.
			If it is needed in the future, it can be added.
		*/
		if (!mAffectors.empty())
		{
			ParticleAffectorIterator affectorIt;
			ParticleAffectorIterator affectorItEnd = mAffectors.end();
			for (affectorIt = mAffectors.begin(); affectorIt != affectorItEnd; ++affectorIt)
			{
				if (!(*affectorIt)->_isMarkedForEmission())
				{
					(*affectorIt)->_notifyPause();
				}
			}
		}
		if (!mEmitters.empty())
		{
			ParticleEmitterIterator emitterIt;
			ParticleEmitterIterator emitterItEnd = mEmitters.end();
			for (emitterIt = mEmitters.begin(); emitterIt != emitterItEnd; ++emitterIt)
			{
				if (!(*emitterIt)->_isMarkedForEmission())
				{
					(*emitterIt)->_notifyPause();
				}
			}
		}

		// Notify the components in the pool.
		_notifyPausePooledComponents();
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_notifyPausePooledComponents(void)
	{
		if (mPool.isEmpty())
			return;

		Particle* particle = static_cast<Particle*>(mPool.getFirst());
		while (!mPool.end())
		{
			switch (particle->particleType)
			{
				case Particle::PT_TECHNIQUE:
				{
					ParticleTechnique* technique = static_cast<ParticleTechnique*>(particle);
					technique->_notifyPause();
				}
				break;
				case Particle::PT_SYSTEM:
				{
					ParticleSystem* system = static_cast<ParticleSystem*>(particle);
					system->pause();
				}
				break;
				case Particle::PT_EMITTER:
				{
					ParticleEmitter* emitter = static_cast<ParticleEmitter*>(particle);
					emitter->_notifyPause();
				}
				break;
				case Particle::PT_AFFECTOR:
				{
					ParticleAffector* affector = static_cast<ParticleAffector*>(particle);
					affector->_notifyPause();
				}
				break;
			}

			particle = static_cast<Particle*>(mPool.getNext());
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_notifyResume (void)
	{
		/** The renderer, Externs and Observers aren't notified. There is no specific reasons for that.
			If it is needed in the future, it can be added.
		*/
		if (!mAffectors.empty())
		{
			ParticleAffectorIterator affectorIt;
			ParticleAffectorIterator affectorItEnd = mAffectors.end();
			for (affectorIt = mAffectors.begin(); affectorIt != affectorItEnd; ++affectorIt)
			{
				if (!(*affectorIt)->_isMarkedForEmission())
				{
					(*affectorIt)->_notifyResume();
				}
			}
		}
		if (!mEmitters.empty())
		{
			ParticleEmitterIterator emitterIt;
			ParticleEmitterIterator emitterItEnd = mEmitters.end();
			for (emitterIt = mEmitters.begin(); emitterIt != emitterItEnd; ++emitterIt)
			{
				if (!(*emitterIt)->_isMarkedForEmission())
				{
					(*emitterIt)->_notifyResume();
				}
			}
		}

		// Notify the components in the pool.
		_notifyResumePooledComponents();
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_notifyResumePooledComponents(void)
	{
		if (mPool.isEmpty())
			return;

		Particle* particle = static_cast<Particle*>(mPool.getFirst());
		while (!mPool.end())
		{
			switch (particle->particleType)
			{
				case Particle::PT_TECHNIQUE:
				{
					ParticleTechnique* technique = static_cast<ParticleTechnique*>(particle);
					technique->_notifyResume();
				}
				break;
				case Particle::PT_SYSTEM:
				{
					ParticleSystem* system = static_cast<ParticleSystem*>(particle);
					system->resume();
				}
				break;
				case Particle::PT_EMITTER:
				{
					ParticleEmitter* emitter = static_cast<ParticleEmitter*>(particle);
					emitter->_notifyResume();
				}
				break;
				case Particle::PT_AFFECTOR:
				{
					ParticleAffector* affector = static_cast<ParticleAffector*>(particle);
					affector->_notifyResume();
				}
				break;
			}

			particle = static_cast<Particle*>(mPool.getNext());
		}
	}
	//-----------------------------------------------------------------------
	bool ParticleTechnique::isStopFade(void)
	{
		if (mParentSystem)
		{
			return mParentSystem->isStopFade();
		}
		return false;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_processParticles(Real timeElapsed)
	{
		if (mPool.isEmpty())
			return;

		// Loop through all particles
		Particle* particle = mPool.getFirst();
		ParticleEmitter* emitter = 0;
		ParticleTechnique* technique = 0;
		bool firstParticle = true; // The real first particle (expired or non-expired)
		bool firstActiveParticle = true; // The first non-expired particle
		while (!mPool.end())
		{
			if (particle)
			{
				if (!_isExpired(particle, timeElapsed))
				{
					// Particle performs actions itself
					_processParticleSelf(particle, timeElapsed, firstActiveParticle);

					// Apply spatial hashing (if needed)
					_processSpatialHashing(particle, timeElapsed);

					// Apply affectors (both the techniques' own affectors and the pooled affectors)
					_processAffectors(particle, timeElapsed, firstActiveParticle);

					// Process individual particle by the externals
					_processExternals(particle, timeElapsed, firstActiveParticle);

					// Process individual particle by the renderer
					_processRenderer(particle, timeElapsed, firstActiveParticle);

					// Some particles need special treatment, but only if this technique is enabled.
					// If the technique is disabled, only the last visual particles are handled (part of smooth LOD).
					if (mEnabled)
					{
						if (particle->particleType == Particle::PT_EMITTER)
						{
							// Trigger emitters that are emitted themselves.
							emitter = static_cast<ParticleEmitter*>(particle);
							_executeEmitParticles(emitter, emitter->_calculateRequestedParticles(timeElapsed), timeElapsed);
						}
						else if (particle->particleType == Particle::PT_TECHNIQUE)
						{
							technique = static_cast<ParticleTechnique*>(particle);

							// Notify the pooled technique to calculate the world AABB in the _update() function
							if (mUpdateWorldAABB)
							{
								technique->_notifyUpdateBounds();
							}

							// Update the pooled techniques
							technique->_update(timeElapsed);

							// Update the world AABB if needed
							if (mUpdateWorldAABB)
							{
								mWorldAABB.merge(technique->getWorldBoundingBox());
							}
						}
					}

					firstActiveParticle = false;

					// Keep latest position
					particle->latestPosition = particle->position;

					// Apply motion
					_processMotion(particle, timeElapsed, firstActiveParticle);
				}
				else
				{
					// Perform some activities on the Particle if it is expired.
					_initParticleForExpiration(particle, timeElapsed);

					// Lock the expired particle!
					mPool.lockLatestParticle();
				}

				// Observe the particle (even if it is already expired and locked)
				_processObservers(particle, timeElapsed, firstParticle);

				// All just emitted particles are processed by now, so the flag can be reset unless it is expired.
				// Expired particles are locked.
				if (particle->hasEventFlags(PEF_EXPIRED))
				{
					particle->setEventFlags(0);
					particle->addEventFlags(PEF_EXPIRED);
				}
				else
				{
					particle->setEventFlags(0);
				}

				// Decrement time to live
				particle->timeToLive -= timeElapsed;
			}

			firstParticle = false;
			particle = mPool.getNext();
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_processDependencies(void)
	{
		// Fast rejection
		if (!(mWidthCameraDependency || mHeightCameraDependency || mDepthCameraDependency))
			return;

		Real width = mDefaultWidth;
		Real height = mDefaultHeight;
		Real depth = mDefaultDepth;
		bool changed = false;
		if (mWidthCameraDependency)
		{
			// Dependency has been set. Use camera (square) distance to recalculate.
			changed = mWidthCameraDependency->affect(width, mCameraSquareDistance);
		}
		if (mHeightCameraDependency)
		{
			// Dependency has been set. Use camera (square) distance to recalculate.
			changed |= mHeightCameraDependency->affect(height, mCameraSquareDistance);
		}
		if (mDepthCameraDependency)
		{
			// Dependency has been set. Use camera (square) distance to recalculate.
			changed |= mDepthCameraDependency->affect(depth, mCameraSquareDistance);
		}

		if (changed && mRenderer)
		{
			mRenderer->_notifyDefaultDimensions(_mParticleSystemScale.x * width, 
				_mParticleSystemScale.y * height, 
				_mParticleSystemScale.z * depth);
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_extractPooledAffectors(void)
	{
		// Copy all pooled affectors to separate list.
		if (mPool.isEmpty(Particle::PT_AFFECTOR))
			return;

		mCopyOfPooledAffectors.clear();
		ParticleAffector* affector = static_cast<ParticleAffector*>(mPool.getFirst(Particle::PT_AFFECTOR));
		while (!mPool.end(Particle::PT_AFFECTOR))
		{
			if (affector)
			{
				mCopyOfPooledAffectors.push_back(affector);
			}

			affector = static_cast<ParticleAffector*>(mPool.getNext(Particle::PT_AFFECTOR));
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_processSpatialHashing(Particle* particle, Real timeElapsed)
	{
		/** If set, then add the particle to mSpatialHashTableA.
		@remarks
			Always use the same hashtable (mSpatialHashTableA); in the _postProcessSpatialHashing() 
			the tables are cycled. 
			Optional: Use an interval to prevent updating every frame.
		*/
		if (mIsSpatialHashingUsed && mSpatialHashTableA)
		{
			if (mSpatialHashingIntervalSet)
			{
				if (mSpatialHashingIntervalActivate)
				{
					mSpatialHashTableA->put(particle->position, particle);
				}
			}
			else
			{
				mSpatialHashTableA->put(particle->position, particle);
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_processAffectors(Particle* particle, Real timeElapsed, bool firstParticle)
	{
		// Iterate through all affector objects that are registered at this technique and which are not emitted
		// themselves.
		// Remark: Cannot use the templated version, because only affectors not marked for emission are taken into account.
		if (!mAffectors.empty())
		{
			ParticleAffectorIterator affectorIt;
			ParticleAffectorIterator affectorItEnd = mAffectors.end();
			for (affectorIt = mAffectors.begin(); affectorIt != affectorItEnd; ++affectorIt)
			{
				if (!(*affectorIt)->_isMarkedForEmission() && (*affectorIt)->isEnabled())
				{
					(*affectorIt)->_processParticle(this, particle, timeElapsed, firstParticle);
				}
			}
		}

		/*  Iterate through all pooled affector objects (these are the affectors that are emitted).
			The pool itself isn¥t used, but an extraction of the pooled affectors.
		*/
		if (mCopyOfPooledAffectors.empty())
			return;

		ParticleAffectorIterator pooledAffectorIt;
		ParticleAffectorIterator pooledAffectorItEnd = mCopyOfPooledAffectors.end();
		for (pooledAffectorIt = mCopyOfPooledAffectors.begin(); pooledAffectorIt != pooledAffectorItEnd; ++pooledAffectorIt)
		{
			if ((*pooledAffectorIt) != particle && (*pooledAffectorIt)->isEnabled())
			{
				(*pooledAffectorIt)->_processParticle(this, particle, timeElapsed, firstParticle);
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_preProcessParticles(Real timeElapsed)
	{
		// Note, the particle pool may be empty, but the preprocessing must still be executed, because
		// this could trigger an necessary action.

		// Perform pre-processing on every Extern
		if (!mExterns.empty())
		{
			Hook<Extern>::_preProcessParticles(&mExterns, this, timeElapsed);
		}

		// Apply dependencies on all particles at once
		_processDependencies();

		// Extract the pooled affectors (only the released (emitted) pooled affectors of course)
		_extractPooledAffectors();

		// Perform pre-processing on every Emitter
		// Remark: Cannot use the templated version, because only emitters not marked for emission are taken into account.
		if (!mEmitters.empty())
		{
			ParticleEmitterIterator emitterIt;
			ParticleEmitterIterator emitterItEnd = mEmitters.end();
			for (emitterIt = mEmitters.begin(); emitterIt != emitterItEnd; ++emitterIt)
			{
				if (!(*emitterIt)->_isMarkedForEmission() && (*emitterIt)->isEnabled())
				{
					(*emitterIt)->_preProcessParticles(this, timeElapsed);
				}
			}
		}

		// Perform pre-processing on every Affector
		// Remark: Cannot use the templated version, because only affectors not marked for emission are taken into account.
		if (!mAffectors.empty())
		{
			ParticleAffectorIterator affectorIt;
			ParticleAffectorIterator affectorItEnd = mAffectors.end();
			for (affectorIt = mAffectors.begin(); affectorIt != affectorItEnd; ++affectorIt)
			{
				if (!(*affectorIt)->_isMarkedForEmission() && (*affectorIt)->isEnabled())
				{
					(*affectorIt)->_preProcessParticles(this, timeElapsed);
				}
			}
		}

		// Perform pre-processing on every emitted Affector
		// Todo: Change this, because only enabled affectors are allowed
		if (!mCopyOfPooledAffectors.empty())
		{
			Hook<ParticleAffector>::_preProcessParticles(&mCopyOfPooledAffectors, this, timeElapsed);
		}

		// Perform pre-processing on every Observer
		if (!mObservers.empty())
		{
			Hook<ParticleObserver>::_preProcessParticles(&mObservers, this, timeElapsed);
		}

		// Update Spatial Hashing interval
		if (mSpatialHashingIntervalSet)
		{
			mSpatialHashingIntervalActivate = false;
			mSpatialHashingIntervalRemainder -= timeElapsed;
			if (mSpatialHashingIntervalRemainder < 0)
			{
				mSpatialHashingIntervalActivate = true;
				mSpatialHashingIntervalRemainder += mSpatialHashingInterval;
			}
		}
	}	
	//-----------------------------------------------------------------------
	void ParticleTechnique::_postProcessParticles(Real timeElapsed)
	{
		// Note, the particle pool may be empty, but the postprocessing must still be executed, because
		// this could trigger an necessary action.

		// Spatial hashtables
		_postProcessSpatialHashing();

		// Set the mUpdateWorldAABB-flag to false to prevent that the mWorldAABB is calculated too often
		mUpdateWorldAABB = false;
		if (mHasExtents)
		{
			mWorldAABB.setExtents(mMinWorldExtend, mMaxWorldExtend);
		}

		// Perform post-processing on every Extern
		if (!mExterns.empty())
		{
			Hook<Extern>::_postProcessParticles(&mExterns, this, timeElapsed);
		}

		// Perform post-processing on every Emitter
		// Remark: Cannot use the templated version, because only emitters not marked for emission are taken into account.
		if (!mEmitters.empty())
		{
			ParticleEmitterIterator emitterIt;
			ParticleEmitterIterator emitterItEnd = mEmitters.end();
			for (emitterIt = mEmitters.begin(); emitterIt != emitterItEnd; ++emitterIt)
			{
				if (!(*emitterIt)->_isMarkedForEmission() && (*emitterIt)->isEnabled())
				{
					(*emitterIt)->_postProcessParticles(this, timeElapsed);
				}
			}
		}

		// Perform post-processing on every Affector
		// Remark: Cannot use the templated version, because only affectors not marked for emission are taken into account.
		if (!mAffectors.empty())
		{
			ParticleAffectorIterator affectorIt;
			ParticleAffectorIterator affectorItEnd = mAffectors.end();
			for (affectorIt = mAffectors.begin(); affectorIt != affectorItEnd; ++affectorIt)
			{
				if (!(*affectorIt)->_isMarkedForEmission() && (*affectorIt)->isEnabled())
				{
					(*affectorIt)->_postProcessParticles(this, timeElapsed);
				}
			}
		}

		// Perform post-processing on every emitted Affector
		// Todo: Change this, because only enabled affectors are allowed
		if (!mCopyOfPooledAffectors.empty())
		{
			Hook<ParticleAffector>::_postProcessParticles(&mCopyOfPooledAffectors, this, timeElapsed);
		}

		// Perform post-processing on every Observer
		if (!mObservers.empty())
		{
			Hook<ParticleObserver>::_postProcessParticles(&mObservers, this, timeElapsed);
		}

#ifdef PU_LOG_DEBUG
		mMaxNumVisualParticles = std::max(mMaxNumVisualParticles, mPool.getSize(Particle::PT_VISUAL));
		mMaxNumEmitterParticles = std::max(mMaxNumEmitterParticles, mPool.getSize(Particle::PT_EMITTER));
		mMaxNumTechniqueParticles = std::max(mMaxNumTechniqueParticles, mPool.getSize(Particle::PT_TECHNIQUE));
		mMaxNumAffectorParticles = std::max(mMaxNumAffectorParticles, mPool.getSize(Particle::PT_AFFECTOR));
		mMaxNumSystemParticles = std::max(mMaxNumSystemParticles, mPool.getSize(Particle::PT_SYSTEM));
#endif // PU_LOG_DEBUG
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_postProcessSpatialHashing(void)
	{
		/** Cycle tables.
		*/ 
		if (mIsSpatialHashingUsed)
		{
			mCurrentSpatialHashTable = mSpatialHashTableA;
			mSpatialHashTableA = mSpatialHashTableB;
			mSpatialHashTableB = mCurrentSpatialHashTable;
			mSpatialHashTableA->clear();
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_processExternals(Particle* particle, Real timeElapsed, bool firstParticle)
	{
		if (mExterns.empty())
			return;

		Hook<Extern>::_processParticle(&mExterns, this, particle, timeElapsed, firstParticle);
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_processRenderer(Particle* particle, Real timeElapsed, bool firstParticle)
	{
		if (!mRenderer)
			return;

		mRenderer->_processParticle(this, particle, timeElapsed, firstParticle);
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_processParticleSelf(Particle* particle, Real timeElapsed, bool firstParticle)
	{
		// Perform 'self' processing
		particle->_process(this, timeElapsed);

		// Determine contribution of particle to mWorldAABB
		if (mUpdateWorldAABB && particle->particleType == Particle::PT_VISUAL)
		{
			VisualParticle* p = static_cast<VisualParticle*>(particle);
			Real maxDim = 0;
			Vector3 padding = Vector3::ZERO;
			if (p->ownDimensions)
			{
				maxDim = std::max(p->width, p->height);
				maxDim = std::max(maxDim, p->depth);
			}
			else
			{
				maxDim = std::max(mDefaultWidth, mDefaultHeight);
				maxDim = std::max(maxDim, mDefaultDepth);
			}

			padding = HALFSCALE * maxDim;
			if (mHasExtents)
			{
				mMinWorldExtend.makeFloor(p->position - padding);
				mMaxWorldExtend.makeCeil(p->position + padding);
			}
			else
			{
				mMinWorldExtend = p->position - padding;
				mMaxWorldExtend = p->position + padding;
				mHasExtents = true;
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_initParticleForExpiration(Particle* particle, Real timeElapsed)
	{
		particle->_initForExpiration(this, timeElapsed);

		if (!mTechniqueListenerList.empty())
		{
			// Run through all listeners
			TechniqueListenerIterator it;
			TechniqueListenerIterator itEnd = mTechniqueListenerList.end();
			for (it = mTechniqueListenerList.begin(); it != itEnd; ++it)
			{
				(*it)->particleExpired(this, particle);
			}
		}

		/** Externs are also called to perform expiration activities. If needed, affectors and emitters may be added, but at the moment
			there is no reason for (and we don¥t want to waste cpu resources).
		*/
		if (!mExterns.empty())
		{
			ExternIterator itExtern;
			ExternIterator itExternEnd = mExterns.end();
			for (itExtern = mExterns.begin(); itExtern != itExternEnd; ++itExtern)
			{
				(*itExtern)->_initParticleForExpiration(particle);
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_processObservers(Particle* particle, Real timeElapsed, bool firstParticle)
	{
		if (mObservers.empty())
			return;

		Hook<ParticleObserver>::_processParticle(&mObservers, this, particle, timeElapsed, firstParticle);
	}
	//-----------------------------------------------------------------------
	bool ParticleTechnique::_isExpired(Particle* particle, Real timeElapsed)
	{
		bool expired = particle->timeToLive < timeElapsed;
		if (expired)
		{
			// Set the flag to indicate that the particle has been expired
			particle->addEventFlags(Particle::PEF_EXPIRED);
		}

		return expired;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_emitParticles(Real timeElapsed)
	{
		// Don't emit if the technique is not enabled
		if (!mEnabled)
			return;

		if (mEmitters.empty())
			return;

		// Todo: Check if the quota will be exceeded, if so reduce demand
		//................


		// Todo: Scale down if there are too many particles within one frame
		//................

		ParticleEmitterIterator itEmitter;
		ParticleEmitterIterator itEmitterBegin = mEmitters.begin();
		ParticleEmitterIterator itEmitterEnd = mEmitters.end();
		for (itEmitter = itEmitterBegin; itEmitter != itEmitterEnd; ++itEmitter)
		{
			//  Trigger the emitters, but exclude the emitters that are already emitted themselves
			if (!(*itEmitter)->_isMarkedForEmission())
			{
				// Scale _getEmissionCount if there are too many particles within one frame
				_executeEmitParticles(*itEmitter, (*itEmitter)->_calculateRequestedParticles(timeElapsed), timeElapsed);
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::forceEmission(ParticleEmitter* emitter, unsigned requested)
	{
		// Fast rejection: Don't emit if the technique is not enabled
		if (!mEnabled)
			return;

		_executeEmitParticles(emitter, requested, 0);
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::forceEmission(const Particle::ParticleType particleType, unsigned requested)
	{
		// Fast rejection: Don't emit if the technique is not enabled
		if (!mEnabled)
			return;

		if (mEmitters.empty())
			return;

		// Run through all emitters and use the first particle of the requested type that is encountered.
		ParticleEmitterIterator emitterIt;
		ParticleEmitterIterator emitterItEnd = mEmitters.end();
		for (emitterIt = mEmitters.begin(); emitterIt != emitterItEnd; ++emitterIt)
		{
			if ((*emitterIt)->getEmitsType() == particleType)
			{
				_executeEmitParticles(*emitterIt, requested, 0);
				return;
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_executeEmitParticles(ParticleEmitter* emitter, unsigned requested, Real timeElapsed)
	{
		// Only proceed if the emitter and technique are enabled
		if (!(mEnabled && emitter->isEnabled()))
			return;

		Real timePoint = 0.0f;
		Real timeInc = timeElapsed / requested;
		for (unsigned int j = 0; j < requested; ++j)
		{
			// Create a new particle & init using emitter
			Particle* particle = mPool.releaseParticle(emitter->getEmitsType(), emitter->getEmitsName());

			// Return if there is no particle left anymore, or the name cannot be found
			if (!particle)
				return;

			// Initialise the particle for emission
			particle->_initForEmission();

			// Initialise the particle with data from the emitter.
			emitter->_initParticleForEmission(particle);

			/** Apply initial orientation to the direction. This cannot be done with the position. 
			    Applying orientation to the position is already taken care of by the emitters.
			*/
			particle->direction = (getParentSystem()->getDerivedOrientation() * particle->direction);
			particle->originalDirection = (getParentSystem()->getDerivedOrientation() * particle->originalDirection);

			// Apply particle initialization by the affectors (if the affector is enabled)
			if (!mAffectors.empty())
			{
				ParticleAffectorIterator affectorIt;
				ParticleAffectorIterator affectorItEnd = mAffectors.end();
				for (affectorIt = mAffectors.begin(); affectorIt != affectorItEnd; ++affectorIt)
				{
					if ((*affectorIt)->isEnabled())
					{
						(*affectorIt)->_initParticleForEmission(particle);
					}
				}
			}

			// Apply initialization by the externs
			if (!mExterns.empty())
			{
				ExternIterator itExtern;
				ExternIterator itExternEnd = mExterns.end();
				for (itExtern = mExterns.begin(); itExtern != itExternEnd; ++itExtern)
				{
					(*itExtern)->_initParticleForEmission(particle);
				}
			}

			/** Initialise the particle from the technique, which could override existing settings.
			@remarks
				Do this after the other initialisation calls and transformation of the direction, because
				the _initParticleForEmission could overwrite the values if needed.
			*/
			_initParticleForEmission(particle);

			// Apply partial frame motion to this particle
			particle->position += (particle->direction * _mParticleSystemScaleVelocity * timePoint);

			// Increment time fragment
			timePoint += timeInc;
		}
	}
	//-----------------------------------------------------------------------
	const Vector3& ParticleTechnique::getDerivedPosition(void)
	{
		if (mMarkedForEmission)
		{
			// Use the technique position, because it is emitted
			// If a particle is emitted, position and derived position are the same
			mDerivedPosition = position;
		}
		else
		{
			if (mParentSystem)
			{
				// Use the techniques' own 'position' as offset
				mDerivedPosition = mParentSystem->getDerivedPosition() + getParentSystem()->getDerivedOrientation() * (_mParticleSystemScale * position);
			}
		}
		return mDerivedPosition;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_processMotion(Particle* particle, Real timeElapsed, bool firstParticle)
	{
		if (particle->isFreezed())
			return;


		/** Because everything is calculated in worldspace we recalculate it back to the techniques' origin (the result is still 
			worldspace) just by adding a relative offset of the particle system, technique, emitter or visual particle.
			Change in V1.4:
			The additional PEF_EMITTED check fixes the problem with scenenodese moving forward at extremely fast speeds 
			The bug is due to how PU code processes keep_local, and the calculation shouldn't be applied to newly emitted particles.
		*/
		if (!particle->hasEventFlags(Particle::PEF_EMITTED))
		{
			if (!particle->parentEmitter->makeParticleLocal(particle))
			{
				if (!makeParticleLocal(particle))
				{
					getParentSystem()->makeParticleLocal(particle);
				}
			}
		}

		/** Adjust position of the particle if the parent has rotated (only in case of particle system with 'keep local').
			PU 1.4: Added check that technique may not be local, otherwise particles are rotated twice as fast.
		*/
		if (getParentSystem()->isKeepLocal() && !mKeepLocal)
		{
			/** Ignore some rendersystems, because they are rotated by Ogre itself.
				Entities for example are always rotated (even if not local), based on the node orientation. A Billboard not.
			*/
			if (mRenderer && !mRenderer->autoRotate)
			{
				getParentSystem()->rotationOffset(particle->position);
			}
		}

		// Added for 1.3
		if (particle->hasEventFlags(Particle::PEF_EMITTED))
			return;

		// Adjust the velocity to the allowed maximum.
		if (mMaxVelocitySet && particle->calculateVelocity() > mMaxVelocity)
		{
			particle->direction *= (mMaxVelocity / particle->direction.length());
		}

		// Update the position with the direction.
		particle->position += (particle->direction * _mParticleSystemScaleVelocity * timeElapsed);
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setWidthCameraDependency(CameraDependency* cameraDependency)
	{
		if (mWidthCameraDependency)
			mCameraDependencyFactory.destroy(mWidthCameraDependency);

		mWidthCameraDependency = cameraDependency;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setWidthCameraDependency(Real squareDistance, bool inc)
	{
		if (!mWidthCameraDependency)
		{
			mWidthCameraDependency = mCameraDependencyFactory.create(squareDistance, inc);
		}
		else
		{
			mWidthCameraDependency->setThreshold(squareDistance);
			mWidthCameraDependency->setIncrease(inc);
		}
	}
	//-----------------------------------------------------------------------
	CameraDependency* ParticleTechnique::getWidthCameraDependency(void) const
	{
		return mWidthCameraDependency;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setHeightCameraDependency(CameraDependency* cameraDependency)
	{
		if (mHeightCameraDependency)
			mCameraDependencyFactory.destroy(mHeightCameraDependency);

		mHeightCameraDependency = cameraDependency;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setHeightCameraDependency(Real squareDistance, bool inc)
	{
		if (!mHeightCameraDependency)
		{
			mHeightCameraDependency = mCameraDependencyFactory.create(squareDistance, inc);
		}
		else
		{
			mHeightCameraDependency->setThreshold(squareDistance);
			mHeightCameraDependency->setIncrease(inc);
		}
	}
	//-----------------------------------------------------------------------
	CameraDependency* ParticleTechnique::getHeightCameraDependency(void) const
	{
		return mHeightCameraDependency;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setDepthCameraDependency(CameraDependency* cameraDependency)
	{
		if (mDepthCameraDependency)
			mCameraDependencyFactory.destroy(mDepthCameraDependency);

		mDepthCameraDependency = cameraDependency;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setDepthCameraDependency(Real squareDistance, bool inc)
	{
		if (!mDepthCameraDependency)
		{
			mDepthCameraDependency = mCameraDependencyFactory.create(squareDistance, inc);
		}
		else
		{
			mDepthCameraDependency->setThreshold(squareDistance);
			mDepthCameraDependency->setIncrease(inc);
		}
	}
	//-----------------------------------------------------------------------
	CameraDependency* ParticleTechnique::getDepthCameraDependency(void) const
	{
		return mDepthCameraDependency;
	}
	//-----------------------------------------------------------------------
	size_t ParticleTechnique::getNumberOfEmittedParticles(void)
	{
		// Get number from the pool
		size_t total = mPool.getSize();

		if (mPool.isEmpty(Particle::PT_TECHNIQUE))
		{
			return total;
		}

		// Take the emitted techniques into account
		ParticleTechnique* technique = static_cast<ParticleTechnique*>(mPool.getFirst(Particle::PT_TECHNIQUE));
		while (!mPool.end(Particle::PT_TECHNIQUE))
		{
			if (technique)
			{
				total += technique->getNumberOfEmittedParticles();
			}
			
			technique = static_cast<ParticleTechnique*>(mPool.getNext(Particle::PT_TECHNIQUE));
		}

		return total;
	}
	//-----------------------------------------------------------------------
	size_t ParticleTechnique::getNumberOfEmittedParticles(Particle::ParticleType particleType)
	{
		// Get number from the pool
		size_t total = mPool.getSize(particleType);

		if (mPool.isEmpty(Particle::PT_TECHNIQUE))
		{
			return total;
		}

		// Take the emitted techniques into account
		ParticleTechnique* technique = static_cast<ParticleTechnique*>(mPool.getFirst(Particle::PT_TECHNIQUE));
		while (!mPool.end(Particle::PT_TECHNIQUE))
		{
			if (technique)
			{
				total += technique->getNumberOfEmittedParticles(particleType);
			}
			
			technique = static_cast<ParticleTechnique*>(mPool.getNext(Particle::PT_TECHNIQUE));
		}

		return total;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_initAllParticlesForExpiration(void)
	{
		if (!mPool.isEmpty())
		{
			Particle* particle = static_cast<Particle*>(mPool.getFirst());
			while (!mPool.end())
			{
				if (particle)
				{
					_initParticleForExpiration(particle, 0);
				}
			
				particle = static_cast<Particle*>(mPool.getNext());
			}
		}

		mPool.lockAllParticles();
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::lockAllParticles(void)
	{
		mPool.lockAllParticles();
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::initVisualDataInPool(void)
	{
		mPool.releaseAllParticles();
		Particle* particle = static_cast<Particle*>(mPool.getFirst());
		while (!mPool.end())
		{
			if (particle)
			{
				particle->visualData = 0;
			}
			particle = static_cast<Particle*>(mPool.getNext());
		}
		mPool.lockAllParticles();
	}
	//-----------------------------------------------------------------------
	ParticlePool* ParticleTechnique::_getParticlePool(void)
	{
		return &mPool;
	}
	//-----------------------------------------------------------------------
	bool ParticleTechnique::isKeepLocal(void) const
	{
		return mKeepLocal;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setKeepLocal(bool keepLocal)
	{
		mKeepLocal = keepLocal;
	}
	//-----------------------------------------------------------------------
	bool ParticleTechnique::makeParticleLocal(Particle* particle)
	{
		if (!particle)
			return true;

		if (!mKeepLocal || hasEventFlags(Particle::PEF_EXPIRED))
			return false;

		Vector3 diff = getDerivedPosition() - latestPosition; // diff of the technique
		particle->position += diff;
		return true;
	}
	//-----------------------------------------------------------------------
	SpatialHashTable<Particle*>* ParticleTechnique::getSpatialHashTable(void) const
	{
		return mCurrentSpatialHashTable;
	}
	//-----------------------------------------------------------------------
	bool ParticleTechnique::isSpatialHashingUsed(void) const
	{
		return mIsSpatialHashingUsed;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setSpatialHashingUsed(bool spatialHashingUsed)
	{
		mIsSpatialHashingUsed = spatialHashingUsed;
	}
	//-----------------------------------------------------------------------
	unsigned short ParticleTechnique::getSpatialHashingCellDimension(void) const
	{
		return mSpatialHashingCellDimension;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setSpatialHashingCellDimension(unsigned short spatialHashingCellDimension)
	{
		mSpatialHashingCellDimension = spatialHashingCellDimension;
	}
	//-----------------------------------------------------------------------
	unsigned short ParticleTechnique::getSpatialHashingCellOverlap(void) const
	{
		return mSpatialHashingCellOverlap;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setSpatialHashingCellOverlap(unsigned short spatialHashingCellOverlap)
	{
		mSpatialHashingCellOverlap = spatialHashingCellOverlap;
	}
	//-----------------------------------------------------------------------
	unsigned int ParticleTechnique::getSpatialHashTableSize(void) const
	{
		return mSpatialHashTableSize;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setSpatialHashTableSize(unsigned int spatialHashTableSize)
	{
		mSpatialHashTableSize = spatialHashTableSize;
	}
	//-----------------------------------------------------------------------
	Real ParticleTechnique::getSpatialHashingInterval(void) const
	{
		return mSpatialHashingInterval;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setSpatialHashingInterval(Real spatialHashingInterval)
	{
		mSpatialHashingInterval = spatialHashingInterval;
		mSpatialHashingIntervalSet = true;
	}
	//-----------------------------------------------------------------------
	Real ParticleTechnique::getMaxVelocity(void) const
	{
		return mMaxVelocity;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::setMaxVelocity(Real maxVelocity)
	{
		mMaxVelocity = maxVelocity;
		mMaxVelocitySet = true;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::addTechniqueListener (TechniqueListener* techniqueListener)
	{
		mTechniqueListenerList.push_back(techniqueListener);
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::removeTechniqueListener (TechniqueListener* techniqueListener)
	{
		assert(techniqueListener && "TechniqueListener is null!");
		TechniqueListenerList::iterator it;
		TechniqueListenerIterator itEnd = mTechniqueListenerList.end();
		for (it = mTechniqueListenerList.begin(); it != itEnd; ++it)
		{
			if (*it == techniqueListener)
			{
				// Remove it (don¥t destroy it, because the technique is not the owner)
				mTechniqueListenerList.erase(it);
				break;
			}
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::logDebug(void)
	{
		LogManager::getSingleton().logMessage("\n");
		if (!mParentSystem->getName().empty())
		{
			LogManager::getSingleton().logMessage("ParticleUniverse - System name: " + mParentSystem->getName());
		}
		if (!mParentSystem->getTemplateName().empty())
		{
			LogManager::getSingleton().logMessage("ParticleUniverse - System templatename: " + mParentSystem->getTemplateName());
		}
		if (!getName().empty())
		{
			LogManager::getSingleton().logMessage("ParticleUniverse - Technique name: " + getName());
		}
		LogManager::getSingleton().logMessage("ParticleUniverse - Material name: " + getMaterialName());
		LogManager::getSingleton().logMessage("ParticleUniverse - Maximum number of visual particles emitted: " + 
			StringConverter::toString(mMaxNumVisualParticles));

		if (mMaxNumEmitterParticles > 0)
		{
			LogManager::getSingleton().logMessage("ParticleUniverse - Maximum number of emitter particles emitted: " + 
				StringConverter::toString(mMaxNumEmitterParticles));
		}

		if (mMaxNumTechniqueParticles > 0)
		{
			LogManager::getSingleton().logMessage("ParticleUniverse - Maximum number of technique particles emitted: " + 
				StringConverter::toString(mMaxNumTechniqueParticles));
		}

		if (mMaxNumAffectorParticles > 0)
		{
			LogManager::getSingleton().logMessage("ParticleUniverse - Maximum number of affector particles emitted: " + 
				StringConverter::toString(mMaxNumAffectorParticles));
		}

		if (mMaxNumSystemParticles > 0)
		{
			LogManager::getSingleton().logMessage("ParticleUniverse - Maximum number of particle systems emitted: " + 
				StringConverter::toString(mMaxNumSystemParticles));
		}
	}
	//-----------------------------------------------------------------------
	Real ParticleTechnique::getParticleSystemScaleVelocity(void) const
	{
		return _mParticleSystemScaleVelocity;
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_pushTechniqueEvent(EventType eventType)
	{
		// Create the event
		ParticleUniverseEvent evt;
		evt.eventType = eventType;
		evt.componentType = CT_TECHNIQUE;
		evt.componentName = getName();
		evt.technique = this;
		evt.emitter = 0;
		pushEvent(evt);
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::pushEvent(ParticleUniverseEvent& particleUniverseEvent)
	{
		// Forward the event
		if (mParentSystem)
		{
			mParentSystem->pushEvent(particleUniverseEvent);
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::copyAttributesTo (ParticleTechnique* technique)
	{
		// Destroy the emitters, affectors, etc.
		technique->destroyAllEmitters();
		technique->destroyAllAffectors();
		technique->destroyAllObservers();
		technique->destroyAllExterns();
		technique->destroyRenderer();

		// Copy Parent attributes
		Particle::copyAttributesTo(technique);

		technique->mName = mName;
		technique->mVisualParticlePoolIncreased = false;
		technique->mParticleEmitterPoolIncreased = false;
		technique->mParticleTechniquePoolIncreased = false;
		technique->mParticleAffectorPoolIncreased = false;
		technique->mVisualParticleQuota = mVisualParticleQuota;
		technique->mEmittedEmitterQuota = mEmittedEmitterQuota;
		technique->mEmittedTechniqueQuota = mEmittedTechniqueQuota;
		technique->mEmittedAffectorQuota = mEmittedAffectorQuota;
		technique->mEmittedSystemQuota = mEmittedSystemQuota;
		technique->mMaterialName = mMaterialName;
		technique->mDefaultWidth = mDefaultWidth;
		technique->mDefaultHeight = mDefaultHeight;
		technique->mDefaultDepth = mDefaultDepth;
		technique->mParentSystem = mParentSystem;
		technique->mLodIndex = mLodIndex;
		technique->mKeepLocal = mKeepLocal;
		technique->mIsSpatialHashingUsed = mIsSpatialHashingUsed;
		technique->mSpatialHashingCellDimension = mSpatialHashingCellDimension;
		technique->mSpatialHashingCellOverlap = mSpatialHashingCellOverlap;
		technique->mSpatialHashTableSize = mSpatialHashTableSize;
		technique->mSpatialHashingInterval = mSpatialHashingInterval;
		technique->mSpatialHashingIntervalRemainder = mSpatialHashingIntervalRemainder;
		technique->mSpatialHashingIntervalSet = mSpatialHashingIntervalSet;
		technique->mMaxVelocity = mMaxVelocity;
		technique->mMaxVelocitySet = mMaxVelocitySet;
		technique->_mParticleSystemScale = _mParticleSystemScale;
		technique->setWidthCameraDependency (mCameraDependencyFactory.clone(getWidthCameraDependency()));
		technique->setHeightCameraDependency (mCameraDependencyFactory.clone(getHeightCameraDependency()));
		technique->setDepthCameraDependency (mCameraDependencyFactory.clone(getDepthCameraDependency()));

		// Copy the renderer
		ParticleRenderer* clonedRenderer = ParticleSystemManager::getSingletonPtr()->cloneRenderer(mRenderer);
		technique->setRenderer(clonedRenderer);

		// Copy all emitters
		ParticleEmitter* clonedEmitter = 0;
		ParticleEmitterIterator itEmitter;
		ParticleEmitterIterator itEmitterEnd = mEmitters.end();
		for (itEmitter = mEmitters.begin(); itEmitter != itEmitterEnd; ++itEmitter)
		{
			clonedEmitter = ParticleSystemManager::getSingletonPtr()->cloneEmitter(*itEmitter);
			technique->addEmitter(clonedEmitter);
		}

		// Copy all affectors
		ParticleAffector* clonedAffector = 0;
		ParticleAffectorIterator itAffector;
		ParticleAffectorIterator itAffectorEnd = mAffectors.end();
		for (itAffector = mAffectors.begin(); itAffector != itAffectorEnd; ++itAffector)
		{
			clonedAffector = ParticleSystemManager::getSingletonPtr()->cloneAffector(*itAffector);
			technique->addAffector(clonedAffector);
		}

		// Copy all observers
		ParticleObserver* clonedObserver = 0;
		ParticleObserverIterator itObserver;
		ParticleObserverIterator itObserverEnd = mObservers.end();
		for (itObserver = mObservers.begin(); itObserver != itObserverEnd; ++itObserver)
		{
			clonedObserver = ParticleSystemManager::getSingletonPtr()->cloneObserver(*itObserver);
			technique->addObserver(clonedObserver);
		}

		// Copy all behaviour templates
		ParticleBehaviour* clonedBehaviour = 0;
		ParticleBehaviourIterator itBehaviour;
		ParticleBehaviourIterator itBehaviourEnd = mBehaviourTemplates.end();
		for (itBehaviour = mBehaviourTemplates.begin(); itBehaviour != itBehaviourEnd; ++itBehaviour)
		{
			clonedBehaviour = ParticleSystemManager::getSingletonPtr()->cloneBehaviour(*itBehaviour);
			technique->_addBehaviourTemplate(clonedBehaviour);
		}

		// Copy all externs
		Extern* clonedExtern = 0;
		ExternIterator itExtern;
		ExternIterator itExternEnd = mExterns.end();
		for (itExtern = mExterns.begin(); itExtern != itExternEnd; ++itExtern)
		{
			clonedExtern = ParticleSystemManager::getSingletonPtr()->cloneExtern(*itExtern);
			technique->addExtern(clonedExtern);
		}
	}

}
