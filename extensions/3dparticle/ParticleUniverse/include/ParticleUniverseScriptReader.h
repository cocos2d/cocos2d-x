/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_SCRIPT_READER_H__
#define __PU_SCRIPT_READER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseIElement.h"
#include "ParticleUniverseScriptCompiler.h"

namespace ParticleUniverse
{
	class ParticleScriptSerializer;

	/*	A class that implements the ScriptReader, is responsible for writing (serialization) to a particle script, but it is not a ScriptTranslator
		itself. It can only delegate the translation to underlying components (Translators).
	*/
	class _ParticleUniverseExport ScriptReader
    {

		public:
			ScriptReader(void) {};
			virtual ~ScriptReader(void) {};

			/** Child classes must implement this pure virtual function, which must be used to write an object or attribute to
				a particle script.
			**/
			virtual void translate(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				// No own implementation
			};

			/** Only parses a certain child property
			*/
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				// No own implementation
				return false;
			};

			/** Only parses a certain child objec
			*/
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				// No own implementation
				return false;
			};
	};

}
#endif
