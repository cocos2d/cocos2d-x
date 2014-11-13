/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_BOX_EMITTER_H__
#define __PU_BOX_EMITTER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseSystem.h"
#include "ParticleUniverseEmitter.h"

namespace ParticleUniverse
{
	/** The BoxEmitter is a ParticleEmitter that emits particles within a box shape.
    */
	class _ParticleUniverseExport BoxEmitter : public ParticleEmitter
	{
		protected:
			Real mHeight;
			Real mWidth;
			Real mDepth;

			Real mXRange;
			Real mYRange;
			Real mZRange;

		public:
			// Constants
			static const Real DEFAULT_WIDTH;
			static const Real DEFAULT_HEIGHT;
			static const Real DEFAULT_DEPTH;

			BoxEmitter(void);
	        virtual ~BoxEmitter(void) {};

			/** 
	        */
			const Real getHeight(void) const;
			void setHeight(const Real height);

			/** 
	        */
			const Real getWidth(void) const;
			void setWidth(const Real width);

			/** 
	        */
			const Real getDepth(void) const;
			void setDepth(const Real depth);

			/** 
	        */
			virtual void _initParticlePosition(Particle* particle);

			/** 
	        */
			virtual void copyAttributesTo (ParticleEmitter* emitter);
	};

}
#endif
