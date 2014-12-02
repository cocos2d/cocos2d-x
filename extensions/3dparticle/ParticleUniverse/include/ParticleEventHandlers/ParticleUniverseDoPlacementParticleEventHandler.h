/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_DO_PLACEMENT_PARTICLE_EVENT_HANDLER_H__
#define __PU_DO_PLACEMENT_PARTICLE_EVENT_HANDLER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEventHandler.h"
#include "ParticleUniverseParticle.h"
#include "ParticleUniverseTechniqueListener.h"

namespace ParticleUniverse
{
	/** This class 'sticks' one or more particles to the position of a particle that is passed through the 
		DoPlacementParticleEventHandler.
	@remarks
		The position of each particle that is passed through the DoPlacementParticleEventHandler is used to emit
		one or more particles on that same position. The ParticleEmitter that is used for emitting the particle(s)
		is searched (once) by means of its name.
	@par
		This class uses a 'TechniqueListener' to pass the newly created particle from the ParticleTechnique to the 
		DoPlacementParticleEventHandler, where it is initialised.
    */
	class _ParticleUniverseExport DoPlacementParticleEventHandler : public ParticleEventHandler, public TechniqueListener
	{
		protected:
			// Identifies the name of emitter
			String mForceEmitterName;

			// The number of particles to emit
			unsigned int mNumberOfParticles;

			/** Store the technique value to keep up to speed.
			@remarks
				If the ParticleTechnique has been destroyed, the DoPlacementParticleEventHandler isn´t automatically
				notified. Using the pointer causes an exception.
	        */
			ParticleTechnique* mTechnique;

			/** Store the emitter value to keep up to speed.
			@remarks
				If the ParticleEmitter has been destroyed, the DoPlacementParticleEventHandler isn´t automatically
				notified. Using the pointer causes an exception.
	        */
			ParticleEmitter* mEmitter;

			/** Used to determine whether the emitter used by the DoPlacementParticleEventHandler, is already found.
	        */
			bool mFound;

			/** By default the place where to put a new particle is on the position of the particle in the _handle function. If 
				mAlwaysUsePosition is set to false, it tries the contact point of the physics actor that is associated with the 
				particle.
	        */
			bool mAlwaysUsePosition;

			/** The base particle from which the attributes are inherited
			*/
			Particle* mBaseParticle;

			/** These flags are used to determine which attributes must be inherited from the base particle.
	        */
			bool mInheritPosition;
			bool mInheritDirection;
			bool mInheritOrientation;
			bool mInheritTimeToLive;
			bool mInheritMass;
			bool mInheritTextureCoordinate;
			bool mInheritColour;
			bool mInheritParticleWidth;
			bool mInheritParticleHeight;
			bool mInheritParticleDepth;

		public:
			// Constants
			static const unsigned int DEFAULT_NUMBER_OF_PARTICLES;

			DoPlacementParticleEventHandler(void);
	        virtual ~DoPlacementParticleEventHandler(void);

			/** Getters/Setters
	        */
			bool isInheritPosition(void) const {return mInheritPosition;};
			bool isInheritDirection(void) const {return mInheritDirection;};
			bool isInheritOrientation(void) const {return mInheritOrientation;};
			bool isInheritTimeToLive(void) const {return mInheritTimeToLive;};
			bool isInheritMass(void) const {return mInheritMass;};
			bool isInheritTextureCoordinate(void) const {return mInheritTextureCoordinate;};
			bool isInheritColour(void) const {return mInheritColour;};
			bool isInheritParticleWidth(void) const {return mInheritParticleWidth;};
			bool isInheritParticleHeight(void) const {return mInheritParticleHeight;};
			bool isInheritParticleDepth(void) const {return mInheritParticleDepth;};

			void setInheritPosition(bool inheritPosition) {mInheritPosition = inheritPosition;};
			void setInheritDirection(bool inheritDirection) {mInheritDirection = inheritDirection;};
			void setInheritOrientation(bool inheritOrientation) {mInheritOrientation = inheritOrientation;};
			void setInheritTimeToLive(bool inheritTimeToLive) {mInheritTimeToLive = inheritTimeToLive;};
			void setInheritMass(bool inheritMass) {mInheritMass = inheritMass;};
			void setInheritTextureCoordinate(bool inheritTextureCoordinate) {mInheritTextureCoordinate = inheritTextureCoordinate;};
			void setInheritColour(bool inheritColour) {mInheritColour = inheritColour;};
			void setInheritParticleWidth(bool inheritParticleWidth) {mInheritParticleWidth = inheritParticleWidth;};
			void setInheritParticleHeight(bool inheritParticleHeight) {mInheritParticleHeight = inheritParticleHeight;};
			void setInheritParticleDepth(bool inheritParticleDepth) {mInheritParticleDepth = inheritParticleDepth;};

			/** Get the name of the emitter that is used to emit its particles.
	        */
			const String& getForceEmitterName(void) const {return mForceEmitterName;};

			/** Set the name of the emitter that is used to emit its particles.
	        */
			void setForceEmitterName(const String& forceEmitterName);

			/** Returns a pointer to the emitter that is used as a force emitter.
	        */
			ParticleEmitter* getForceEmitter(void) const;

			/** Remove this as a listener from the technique.
			@remarks
				If a new force-emitter name has been set, the removeAsListener must be called, to remove the DoPlacementParticleEventHandler
				from the old technique (to which the force-emitter belongs. Only then the new force-emitter is used. 
				The reason why it is not called automatically in the setForceEmitterName() funtion is to offer some flexibility on 
				the moment the removeAsListener() is called.
	        */
			void removeAsListener(void);

			/** Get the number of particles to emit.
	        */
			unsigned int getNumberOfParticles(void) const {return mNumberOfParticles;};

			/** Set the number of particles to emit.
	        */
			void setNumberOfParticles(unsigned int numberOfParticles){mNumberOfParticles = numberOfParticles;};

			/** Boolean that determines whether always the position of the particle that is handled must be used for emission of 
				the new particle.
	        */
			bool alwaysUsePosition(void) const {return mAlwaysUsePosition;};

			/** Set the boolean to indicate whether the position of the particle that is handled must be used for emission of 
				the new particle or whether the contact point of the physics actor must be used. This only applies if a physics angine
				is used, otherwise the default is used.
	        */
			void setAlwaysUsePosition(bool alwaysUsePosition) {mAlwaysUsePosition = alwaysUsePosition;};

			/** If the _handle() function of this class is invoked (by an Observer), it searches the 
				ParticleEmitter defined by the mForceEmitterName. This ParticleEmitter is either part of 
				the ParticleTechnique in which the DoPlacementParticleEventHandler is defined, and if the ParticleEmitter
				is not found, other ParticleTechniques are searched. The ParticleEmitter is 'forced' to emit the
				requested number of particles.
	        */
			virtual void _handle (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** Initialise the emitted particle. This means that its position is set.
	        */
			virtual void particleEmitted(ParticleTechnique* particleTechnique, Particle* particle);

			/** No implementation.
	        */
			virtual void particleExpired(ParticleTechnique* particleTechnique, Particle* particle){};

			/** Copy attributes to another event handler.
	        */
			virtual void copyAttributesTo (ParticleEventHandler* eventHandler);
	};

}
#endif
