/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_POINT_EMITTER_H__
#define __PU_POINT_EMITTER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseSystem.h"
#include "ParticleUniverseEmitter.h"

namespace ParticleUniverse
{
	/** The PointEmitter is a ParticleEmitter that emits particles from a 3D point.
    */
	class _ParticleUniverseExport PointEmitter : public ParticleEmitter
	{
		protected:

		public:
			PointEmitter(void) : ParticleEmitter()
			{
			};
	        virtual ~PointEmitter(void) {};

			/** 
	        */
			virtual void copyAttributesTo (ParticleEmitter* emitter);
	};

}
#endif
