/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SPHERE_SURFACE_EMITTER_FACTORY_H__
#define __PU_SPHERE_SURFACE_EMITTER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEmitterFactory.h"
#include "ParticleUniverseSphereSurfaceEmitterTokens.h"
#include "ParticleUniverseSphereSurfaceEmitter.h"

namespace ParticleUniverse
{
	/** This is the factory class that is responsible for creating a SphereSurfaceEmitter.
    */
	class _ParticleUniverseExport SphereSurfaceEmitterFactory : public ParticleEmitterFactory
	{
		protected:
			SphereSurfaceEmitterWriter mSphereSurfaceEmitterWriter;
			SphereSurfaceEmitterTranslator mSphereSurfaceEmitterTranslator;

		public:
			SphereSurfaceEmitterFactory(void) {};
	        virtual ~SphereSurfaceEmitterFactory(void) {};

			/** See ParticleEmitterFactory */
			String getEmitterType(void) const
			{
				return "SphereSurface";
			}

			/** See ParticleEmitterFactory */
			ParticleEmitter* createEmitter(void)
			{
				return _createEmitter<SphereSurfaceEmitter>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mSphereSurfaceEmitterTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mSphereSurfaceEmitterTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate to mSphereSurfaceEmitterWriter
				mSphereSurfaceEmitterWriter.write(serializer, element);
			}
	};

}
#endif
