/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_DO_AFFECTOR_EVENT_HANDLER_H__
#define __PU_DO_AFFECTOR_EVENT_HANDLER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEventHandler.h"

namespace ParticleUniverse
{
	/** This class explicitly calls an affector to affect the particles. There are several reasons why
		this is appropriate. One reason is, that you only want to affect a particle if a certain event
		occurs. Disable an affector and call it using this event handler, is the method (calling the affector
		from the event handler doesn't take into consideration that the affector is disabled).
    */
	class _ParticleUniverseExport DoAffectorEventHandler : public ParticleEventHandler
	{
		protected:
			// Identifies the name of affector
			String mAffectorName;

			// Determines whether the pre- and post processing activities must be executed also
			bool mPrePost;

		public:
			// Constants
			static const bool DEFAULT_PRE_POST;

			DoAffectorEventHandler(void);
	        virtual ~DoAffectorEventHandler(void) {};

			/** Get the indication whether pre- and postprocessing must be done.
	        */
			const bool getPrePost(void) const {return mPrePost;};

			/** Set the indication whether pre- and postprocessing must be done.
	        */
			void setPrePost(const bool prePost){mPrePost = prePost;};

			/** Get the name of the affector that must be enabled or disabled.
	        */
			const String& getAffectorName(void) const {return mAffectorName;};

			/** Set the name of the affector.
	        */
			void setAffectorName(const String& affectorName){mAffectorName = affectorName;};

			/** If the _handle() function of this class is invoked (by an Observer), it searches the 
				ParticleAffector defined by the its name. 
				The ParticleAffector is either part of the ParticleTechnique in which the 
				DoAffectorEventHandler is defined, or if the Affector is not found, other 
				ParticleTechniques are searched.
	        */
			virtual void _handle (ParticleTechnique* particleTechnique, Particle* particle, Real timeElapsed);

			/** Copy attributes to another event handler.
	        */
			virtual void copyAttributesTo (ParticleEventHandler* eventHandler);
	};

}
#endif
