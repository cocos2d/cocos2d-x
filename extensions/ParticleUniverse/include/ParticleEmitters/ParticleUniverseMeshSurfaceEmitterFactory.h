/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_MESH_SURFACE_EMITTER_FACTORY_H__
#define __PU_MESH_SURFACE_EMITTER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEmitterFactory.h"
#include "ParticleUniverseMeshSurfaceEmitterTokens.h"
#include "ParticleUniverseMeshSurfaceEmitter.h"

namespace ParticleUniverse
{
	/** This is the factory class that is responsible for creating a MeshSurfaceEmitter.
    */
	class _ParticleUniverseExport MeshSurfaceEmitterFactory : public ParticleEmitterFactory
	{
		protected:
			MeshSurfaceEmitterWriter mMeshSurfaceEmitterWriter;
			MeshSurfaceEmitterTranslator mMeshSurfaceEmitterTranslator;

		public:
			MeshSurfaceEmitterFactory(void) {};
	        virtual ~MeshSurfaceEmitterFactory(void) {};

            /** See ParticleEmitterFactory */
			String getEmitterType(void) const
			{
				return "MeshSurface";
			}

			/** See ParticleEmitterFactory */
			ParticleEmitter* createEmitter(void)
			{
				return _createEmitter<MeshSurfaceEmitter>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mMeshSurfaceEmitterTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mMeshSurfaceEmitterTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate to mMeshSurfaceEmitterWriter
				mMeshSurfaceEmitterWriter.write(serializer, element);
			}

	};

}
#endif
