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

#include "ParticleAffectors/ParticleUniverseAlignAffector.h"
#include "ParticleAffectors/ParticleUniverseAlignAffectorTokens.h"

namespace ParticleUniverse
{
	//-----------------------------------------------------------------------
	bool AlignAffectorTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
		ParticleAffector* af = any_cast<ParticleAffector*>(prop->parent->context);
		AlignAffector* affector = static_cast<AlignAffector*>(af);

		if (prop->name == token[TOKEN_RESIZE])
		{
			if (passValidateProperty(compiler, prop, token[TOKEN_RESIZE], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					affector->setResize(val);
					return true;
				}
			}
		}
		else if (prop->name == token[TOKEN_ALIGN_RESIZE])
		{
			if (passValidateProperty(compiler, prop, token[TOKEN_ALIGN_RESIZE], VAL_BOOL))
			{
				bool val;
				if(getBoolean(prop->values.front(), &val))
				{
					affector->setResize(val);
					return true;
				}
			}
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool AlignAffectorTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		// No objects
		return false;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void AlignAffectorWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a AlignAffector
		const AlignAffector* affector = static_cast<const AlignAffector*>(element);

		// Write the header of the AlignAffector
		serializer->writeLine(token[TOKEN_AFFECTOR], affector->getAffectorType(), affector->getName(), 8);
		serializer->writeLine("{", 8);

		// Write base attributes
		ParticleAffectorWriter::write(serializer, element);

		// Write own attributes
		if (affector->isResize() != AlignAffector::DEFAULT_RESIZE) serializer->writeLine(
			token[TOKEN_RESIZE], StringConverter::toString(affector->isResize()), 12);

		// Write the close bracket
		serializer->writeLine("}", 8);
	}

}
