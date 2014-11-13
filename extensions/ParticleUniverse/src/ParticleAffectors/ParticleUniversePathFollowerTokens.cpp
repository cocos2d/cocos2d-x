/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#include "ParticleUniversePCH.h"

#ifndef PARTICLE_UNIVERSE_EXPORTS
#define PARTICLE_UNIVERSE_EXPORTS
#endif

#include "ParticleAffectors/ParticleUniversePathFollower.h"
#include "ParticleAffectors/ParticleUniversePathFollowerTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool PathFollowerTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleAffector* af = any_cast<ParticleAffector*>(prop->parent->context);
		PathFollower* affector = static_cast<PathFollower*>(af);

		if (prop->name == token[TOKEN_PATH_POINT])
		{
			// Property: path_follower_point
			if (passValidateProperty(compiler, prop, token[TOKEN_PATH_POINT], VAL_VECTOR3))
			{
				Vector3 val;
				if(getVector3(prop->values.begin(), prop->values.end(), &val))
				{
					affector->addPoint(val);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool PathFollowerTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void PathFollowerWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a PathFollower
		const PathFollower* affector = static_cast<const PathFollower*>(element);

		// Write the header of the PathFollower
		serializer->writeLine(token[TOKEN_AFFECTOR], affector->getAffectorType(), affector->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleAffectorWriter::write(serializer, element);

		// Write own attributes
		unsigned short numberOfPoints = affector->getNumPoints();
		if (numberOfPoints > 0)
		{
			for (unsigned short u = 0; u < numberOfPoints; ++u)
			{
				serializer->writeLine(token[TOKEN_PATH_POINT], StringConverter::toString(affector->getPoint(u)), 12);
			}
		}
				
		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
