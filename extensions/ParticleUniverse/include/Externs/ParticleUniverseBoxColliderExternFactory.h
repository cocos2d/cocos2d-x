/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_BOX_COLLIDER_EXTERN_FACTORY_H__
#define __PU_BOX_COLLIDER_EXTERN_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseExternFactory.h"
#include "ParticleUniverseBoxColliderExtern.h"
#include "ParticleUniverseBoxColliderExternTokens.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the BoxColliderExtern.
	*/
	class _ParticleUniverseExport BoxColliderExternFactory : public ExternFactory
	{
		public:
			BoxColliderExternFactory(void) : 
				ExternFactory(){};
		     virtual ~BoxColliderExternFactory(void){};

			/** 
			*/
			String getExternType(void) const
			{
				return "BoxCollider";
			};

			/** 
			*/
			Extern* createExtern(void)
			{
				return _createExtern<BoxColliderExtern>();
			};

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mBoxColliderExternTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mBoxColliderExternTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate to mBoxColliderExternWriter
				mBoxColliderExternWriter.write(serializer, element);
			}

		protected:
			BoxColliderExternWriter mBoxColliderExternWriter;
			BoxColliderExternTranslator mBoxColliderExternTranslator;
	};

}
#endif
