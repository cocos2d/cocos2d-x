/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_VORTEX_EXTERN_FACTORY_H__
#define __PU_VORTEX_EXTERN_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseExternFactory.h"
#include "ParticleUniverseVortexExtern.h"
#include "ParticleUniverseVortexExternTokens.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the VortexExtern.
    */
	class _ParticleUniverseExport VortexExternFactory : public ExternFactory
	{
		public:
			VortexExternFactory(void) : 
				ExternFactory(){};
	        virtual ~VortexExternFactory(void){};

			/** 
			*/
			String getExternType(void) const
			{
				return "Vortex";
			};

			/** 
			*/
			Extern* createExtern(void)
			{
				return _createExtern<VortexExtern>();
			};

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mVortexExternTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mVortexExternTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element)
			{
				// Delegate to mVortexExternWriter
				mVortexExternWriter.write(serializer, element);
			}

		protected:
			VortexExternWriter mVortexExternWriter;
			VortexExternTranslator mVortexExternTranslator;
	};

}
#endif
