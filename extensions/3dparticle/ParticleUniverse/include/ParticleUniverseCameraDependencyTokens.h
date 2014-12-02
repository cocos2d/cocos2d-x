/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_CAMERA_DEPENDENCY_TOKENS_H__
#define __PU_CAMERA_DEPENDENCY_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseCameraDependency.h"
#include "ParticleUniverseScriptDeserializer.h"

namespace ParticleUniverse
{
	/** The CameraDependencyTranslator parses 'CameraDependency' tokens
	*/
	class _ParticleUniverseExport CameraDependencyTranslator : public ScriptTranslator
	{
		public:
			CameraDependencyTranslator(void);
			virtual ~CameraDependencyTranslator(void){};
			virtual void translate(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport CameraDependencyWriter : public ScriptWriter
	{
		public:

			CameraDependencyWriter(void) {};
			virtual ~CameraDependencyWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element);
	};

}
#endif
