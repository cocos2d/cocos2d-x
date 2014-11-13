/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_GRAVITY_EXTERN_FACTORY_H__
#define __PU_GRAVITY_EXTERN_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseExternFactory.h"
#include "ParticleUniverseGravityExtern.h"
#include "ParticleUniverseGravityExternTokens.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the GravityExtern.
    */
	class _ParticleUniverseExport GravityExternFactory : public ExternFactory
	{
		public:
			GravityExternFactory(void) : 
				ExternFactory(){};
	        virtual ~GravityExternFactory(void){};

			/** 
			*/
			String getExternType(void) const
			{
				return "Gravity";
			};

			/** 
			*/
			Extern* createExtern(void)
			{
				return _createExtern<GravityExtern>();
			};

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mGravityExternTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mGravityExternTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element)
			{
				// Delegate to mGravityExternWriter
				mGravityExternWriter.write(serializer, element);
			}


		protected:
			GravityExternWriter mGravityExternWriter;
			GravityExternTranslator mGravityExternTranslator;
	};

}
#endif
