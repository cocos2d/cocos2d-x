/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_DYNAMIC_ATTRIBUTE_TOKENS_H__
#define __PU_DYNAMIC_ATTRIBUTE_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseScriptWriter.h"
#include "ParticleUniverseScriptDeserializer.h"
#include "ParticleUniverseDynamicAttribute.h"

namespace ParticleUniverse
{
	/** The DynamicAttributeTranslator parses 'dynamic attributes' tokens
	*/
	class _ParticleUniverseExport DynamicAttributeTranslator : public ScriptTranslator
	{
		protected:
			DynamicAttribute* mDynamicAttribute;
		public:
			DynamicAttributeTranslator(void);
			virtual ~DynamicAttributeTranslator(void){};
			virtual void translate(ScriptCompiler* compiler, const AbstractNodePtr &node);
	};
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	/** 
    */
	class _ParticleUniverseExport DynamicAttributeWriter : public ScriptWriter
	{
		public:

			DynamicAttributeWriter(void) {};
			virtual ~DynamicAttributeWriter(void) {};

			/** @see
				ScriptWriter::write
			*/
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element);
	};

}
#endif
