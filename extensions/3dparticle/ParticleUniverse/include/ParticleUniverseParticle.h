/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_PARTICLE_H__
#define __PU_PARTICLE_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseBehaviour.h"
#include "ParticleUniverseIVisualData.h"
#include "ParticleUniverseAny.h"
#include "ParticleUniversePhysicsActor.h"

namespace ParticleUniverse
{
	/** Particle is the abstract/virtual class that represents the object to be emitted.
	@remarks
		Several types of particles are distinguished, where the visual particle is the most obvious one.
		Other types of particles are also possible. ParticleAffectors, ParticleEmitters, ParticleTechniques
		and even ParticleSystems can act as a particle.
    */
	class _ParticleUniverseExport Particle
	{
		public:

			typedef vector<ParticleBehaviour*> ParticleBehaviourList;
			typedef ParticleBehaviourList::const_iterator ParticleBehaviourIterator;

			static Real DEFAULT_TTL;
			static Real DEFAULT_MASS;
			enum ParticleType
			{
				PT_VISUAL,
				PT_TECHNIQUE,
				PT_EMITTER,
				PT_AFFECTOR,
				PT_SYSTEM
			};

			/** Enumeration which lists a number of reserved event flags. Although custom flags can be used to
				indicate that a certain condition occurs, the first number of flags may not be used as custom flags.
		    */
			enum ReservedParticleEventFlags
			{
				PEF_EXPIRED = 1<<0,
				PEF_EMITTED = 1<<1,
				PEF_COLLIDED = 1<<2
			};

			Particle(void) : 
				mMarkedForEmission(false),
				position(Vector3::ZERO),
				mDerivedPosition(Vector3::ZERO),
				direction(Vector3::ZERO),
				timeToLive(DEFAULT_TTL),
				totalTimeToLive(DEFAULT_TTL),
				timeFraction(0.0f),
				particleType(PT_VISUAL),
				physicsActor(0),
				mass(DEFAULT_MASS),
				mEventFlags(0),
				mEnabled(true),
				mFreezed(false),
				mOriginalEnabled(true),
				mOriginalEnabledSet(false),
				originalPosition(Vector3::ZERO),
				latestPosition(Vector3::ZERO),
				originalDirection(Vector3::ZERO),
				originalDirectionLength(0.0f),
				originalScaledDirectionLength(0.0f),
				originalVelocity(0.0f),
				parentEmitter(0),
				visualData(0){};
			virtual ~Particle(void);

			// Note: Use public attributes for speed

			/*  Pointer to emitter that has emitted the particle.
			@remarks
				Since the particle can be reused by several emitters, this values can change.
			*/
			ParticleEmitter* parentEmitter;

			/*  Position.
			@remarks
				Unlike Ogre's particle plugin, the ParticleUniverse plugin doesn't distinguish between local
				and worldspace.
			*/
			Vector3 position;

			// Direction (and speed)
			Vector3 direction;

			/*  Mass of a particle.
			@remarks
				In case of simulations where mass of a particle is needed (i.e. exploding particles of different
				mass) this attribute can be used.
			*/
			Real mass;

			// Time to live, number of seconds left of particles natural life
			Real timeToLive;

			// Total Time to live, number of seconds of particles natural life
			Real totalTimeToLive;

			// The timeFraction is calculated every update. It is used in other observers, affectors, etc. so it is
			// better to calculate it once at the Particle level.
			Real timeFraction;

			// Determine type of particle, to prevent Realtime type checking
			ParticleType particleType;

			/** Keep the posibility to attach some custom data. This is additional to the Behaviour data. The
				advantage of a UserDefinedObject in favour of a ParticleBehaviour is, that no search is
				needed.
			@remarks
				The UserDefinedObject is not managed by the Particle itself, so assigned UserDefinedObjects must
				be deleted outside the Particle.
			*/
			Any mUserDefinedObject;

			/** If a physics engine is used, this attribute is set as soon as a particle is emitted.
			*/
			PhysicsActor* physicsActor;

			/** For some renderers it is needed to relate a particle to some visual data
			@remarks
				The visual data is set into the Particle instead of the VisualParticle, to enable other
				particle types do use visual data (if needed). The IVisualData is not managed by the Particle 
				itself, so assigned IVisualData must be deleted outside the Particle.
			*/
			IVisualData* visualData;

			// Values that are assigned as soon as the particle is emitted (non-transformed)
			Vector3 originalPosition;
			Vector3 originalDirection;
			Real originalVelocity;
			Real originalDirectionLength; // Length of the direction that has been set
			Real originalScaledDirectionLength; // Length of the direction after multiplication with the velocity

			// Keep latest position
			Vector3 latestPosition;

			/** Todo
	        */
			inline bool _isMarkedForEmission(void) const {return mMarkedForEmission;};
			inline void _setMarkedForEmission(bool markedForEmission) {mMarkedForEmission = markedForEmission;};

			/** Perform initialising activities as soon as the particle is emitted.
	        */
			virtual void _initForEmission(void);

			/** Perform some action if the particle expires.
			@remarks
				Note, that this function applies to all particle types (including Particle Techniques, Emitters and
				Affectors).
			*/
			virtual void _initForExpiration(ParticleTechnique* technique, Real timeElapsed);

			/** Todo
	        */
			virtual bool isEnabled(void) const;

			/** Todo
	        */
			virtual void setEnabled(bool enabled);

			/** This function sets the original 'enabled' value of the particle.
			@remarks
				Only use this function if you really know what you're doing. Otherwise it shouldn't be used for regular usage.
			*/
			void _setOriginalEnabled(bool originalEnabled);

			/** Returns the original 'enabled' value of the particle
			*/
			bool _getOriginalEnabled(void) const;

			/** Returns true if the particle is freezed and doesn't move anymore.
			@remarks
				Although it is freezed, repositioning the particle is still possible.
	        */
			bool isFreezed(void) const;

			/** Freeze the particle, so it doesn't move anymore.
	        */
			void setFreezed(bool freezed);

			/** Sets the event flags.
			*/
			inline void setEventFlags(uint32 flags) {mEventFlags = flags;}

			/** As setEventFlags, except the flags passed as parameters are appended to the
				existing flags on this object.
			*/
			inline void addEventFlags(uint32 flags) {mEventFlags |= flags;}
            
			/** The flags passed as parameters are removed from the existing flags.
			*/
			inline void removeEventFlags(uint32 flags) {mEventFlags &= ~flags;}
        
			/** Return the event flags.
			*/
			inline uint32 getEventFlags(void) const {return mEventFlags;}

			/** Determines whether it has certain flags set.
			*/
			inline bool hasEventFlags(uint32 flags) const {return mEventFlags & flags;}

			/** Copy a vector of ParticleBehaviour objects to this particle.
			*/
			void copyBehaviours(ParticleBehaviourList& behaviours);

			/** Perform actions on the particle itself during the update loop of a ParticleTechnique.
			@remarks
				Active particles may want to do some processing themselves each time the ParticleTechnique is updated.
				One example is to perform actions by means of the registered ParticleBehaviour objects. 
				ParticleBehaviour objects apply internal behaviour of each particle individually. They add both 
				data and behaviour to a particle, which means that each particle can be extended with functionality.
			*/
			virtual void _process(ParticleTechnique* technique, Real timeElapsed);

			/** Returns the first occurence of the ParticleBehaviour specified by its type.
			*/
			ParticleBehaviour* getBehaviour(const String& behaviourType);

			/** Calculates the velocity, based on the direction vector.
			*/
			Real calculateVelocity(void) const;

			/** Copy the data of this particle to another particle.
			*/
			virtual void copyAttributesTo (Particle* particle);

		protected:
			/*  Flags that can be used to determine whether a certain condition occurs.
			@remarks
				This attribute is used to assign a certain condition to a particle. During processing of the particle
				(process all affectors) a certain condition may occur. A particle may expire, reach a certain
				threshold, etc. Some of these conditions are determined by a ParticleObserver, but there are
				situations where this condition has been determined even before the ParticleObserver has done its
				validation. One example is the determination of an expired particle. Since we want to prevent that
				a ParticleObserver validates the same condition, a flag can be set.
			*/
			uint32 mEventFlags;

			/** Determines whether the particle is marked for emission.
			@remarks
				This means that the particle is emitted. This is obvious for visual particles, but 
				a ParticleEmitter for instance is also a Particle; this means that is can be emitted also.
			*/
			bool mMarkedForEmission;

			/** Determines whether a particle is activated.
			@remarks
				This attribute is particularly used for child classes that must have a capability to be
				enabled or disabled (emitters, affectors, ...). There is no need for disabling a visual particle, 
				because expiring a particle seems sufficient. The default value of this attribute is true.
	        */
			bool mEnabled;

			/** Determines whether a particle is 'freezed'. This means that the particle doesn´t move anymore.
	        */
			bool mFreezed;

			/** Original setting.
	        */
			bool mOriginalEnabled;

			/** Original may be set only once.
	        */
			bool mOriginalEnabledSet;

			/** Because the public attribute ´position´ is sometimes used for both localspace and worldspace
				position, the mDerivedPosition attribute is introduced.
	        */
			Vector3 mDerivedPosition;

			/** List containing ParticleBehaviours.
	        */
			ParticleBehaviourList mBehaviours;
	};

}
#endif
