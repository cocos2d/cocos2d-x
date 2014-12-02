/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_VERTEX_EMITTER_FACTORY_H__
#define __PU_VERTEX_EMITTER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEmitterFactory.h"
#include "ParticleUniverseVertexEmitterTokens.h"
#include "ParticleUniverseVertexEmitter.h"

namespace ParticleUniverse
{
	/** This is the factory class that is responsible for creating a VertexEmitter.
    */
	class _ParticleUniverseExport VertexEmitterFactory : public ParticleEmitterFactory
	{
		protected:
			VertexEmitterWriter mVertexEmitterWriter;
			VertexEmitterTranslator mVertexEmitterTranslator;

		public:
			VertexEmitterFactory(void) {};
	        virtual ~VertexEmitterFactory(void) {};

			/** See ParticleEmitterFactory */
			String getEmitterType(void) const
			{
				return "Vertex";
			}

			/** See ParticleEmitterFactory */
			ParticleEmitter* createEmitter(void)
			{
				return _createEmitter<VertexEmitter>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mVertexEmitterTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mVertexEmitterTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate to mVertexEmitterWriter
				mVertexEmitterWriter.write(serializer, element);
			}
	};

}
#endif
