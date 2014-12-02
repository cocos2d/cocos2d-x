/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_GEOMETRY_ROTATOR_FACTORY_H__
#define __PU_GEOMETRY_ROTATOR_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseGeometryRotatorTokens.h"
#include "ParticleUniverseGeometryRotator.h"
#include "ParticleUniverseAffectorFactory.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the GeometryRotator.
    */
	class _ParticleUniverseExport GeometryRotatorFactory : public ParticleAffectorFactory
	{
		public:

			GeometryRotatorFactory(void){};
	        virtual ~GeometryRotatorFactory(void){};

			/** See ParticleAffectorFactory */
			String getAffectorType(void) const
			{
				return "GeometryRotator";
			}

			/** See ParticleAffectorFactory  */
			ParticleAffector* createAffector(void)
			{
				return _createAffector<GeometryRotator>();
			}

			/** See ScriptReader */
			virtual bool translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mGeometryRotatorTranslator.translateChildProperty(compiler, node);
			};

			/** See ScriptReader */
			virtual bool translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
			{
				return mGeometryRotatorTranslator.translateChildObject(compiler, node);
			};

			/*  */
			virtual void write(ParticleScriptSerializer* serializer , const IElement* element)
			{
				// Delegate
				mGeometryRotatorWriter.write(serializer, element);
			}

		protected:
		GeometryRotatorWriter mGeometryRotatorWriter;
		GeometryRotatorTranslator mGeometryRotatorTranslator;
	};

}
#endif
