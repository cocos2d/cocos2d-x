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

#include "ParticleUniverseSystemTokens.h"

namespace ParticleUniverse
{
	/**************************************************************************
	 * SystemTranslator
	 *************************************************************************/
	SystemTranslator::SystemTranslator(void)
		:mSystem(0)
	{
	}
	//-------------------------------------------------------------------------
	void SystemTranslator::translate(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		ObjectAbstractNode* obj = reinterpret_cast<ObjectAbstractNode*>(node.get());
		if(obj->name.empty())
		{
			compiler->addError(ScriptCompiler::CE_OBJECTNAMEEXPECTED, obj->file, obj->line);
			return;
		}

		// Create a particle system with the given name
		mSystem = ParticleSystemManager::getSingletonPtr()->createParticleSystemTemplate(obj->name, compiler->getResourceGroup());
		if (!mSystem)
		{
			compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
			return;
		}
		obj->context = Any(mSystem);

		for(AbstractNodeList::iterator i = obj->children.begin(); i != obj->children.end(); ++i)
		{
			if((*i)->type == ANT_PROPERTY)
			{
				PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>((*i).get());
				if (prop->name == token[TOKEN_PS_ITERATION_INTERVAL])
				{
					// Property: iteration_interval
					if (passValidateProperty(compiler, prop, token[TOKEN_PS_ITERATION_INTERVAL], VAL_REAL))
					{
						Real val = 0.0f;
						if(getReal(prop->values.front(), &val))
						{
							mSystem->setIterationInterval(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_PS_NONVIS_UPDATE_TIMEOUT])
				{
					// Property: nonvisible_update_timeout
					if (passValidateProperty(compiler, prop, token[TOKEN_PS_NONVIS_UPDATE_TIMEOUT], VAL_REAL))
					{
						Real val = 0.0f;
						if(getReal(prop->values.front(), &val))
						{
							mSystem->setNonVisibleUpdateTimeout(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_PS_FIXED_TIMEOUT])
				{
					// Property: fixed_timeout
					if (passValidateProperty(compiler, prop, token[TOKEN_PS_FIXED_TIMEOUT], VAL_REAL))
					{
						Real val = 0.0f;
						if(getReal(prop->values.front(), &val))
						{
							mSystem->setFixedTimeout(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_PS_LOD_DISTANCES])
				{
					// Property: lod_distances
					if (passValidatePropertyNoValues(compiler, prop, token[TOKEN_PS_LOD_DISTANCES]))
					{
						for(AbstractNodeList::iterator j = prop->values.begin(); j != prop->values.end(); ++j)
						{
							Real val = 0.0f;
							if(getReal(*j, &val))
							{
								mSystem->addLodDistance(val);
							}
							else
							{
								compiler->addError(ScriptCompiler::CE_NUMBEREXPECTED, prop->file, prop->line,
									"PU Compiler: lod_distances expects only numbers as arguments");
							}
						}
					}
				}
				else if (prop->name == token[TOKEN_PS_MAIN_CAMERA_NAME])
				{
					// Property: main_camera_name
					if (passValidateProperty(compiler, prop, token[TOKEN_PS_MAIN_CAMERA_NAME], VAL_STRING))
					{
						String val;
						if(getString(prop->values.front(), &val))
						{
							mSystem->setMainCameraName(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_PS_SMOOTH_LOD])
				{
					// Property: smooth_lod
					if (passValidateProperty(compiler, prop, token[TOKEN_PS_SMOOTH_LOD], VAL_BOOL))
					{
						bool val;
						if(getBoolean(prop->values.front(), &val))
						{
							mSystem->setSmoothLod(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_PS_FAST_FORWARD])
				{
					// Property: fast_forward
					if (passValidateProperty(compiler, prop, token[TOKEN_PS_SCALE], VAL_VECTOR2))
					{
						Vector2 val;
						if(getVector2(prop->values.begin(), prop->values.end(), &val))
						{
							mSystem->setFastForward(val.x, val.y);
						}
					}
				}
				else if (prop->name == token[TOKEN_PS_SCALE])
				{
					// Property: scale
					if (passValidateProperty(compiler, prop, token[TOKEN_PS_SCALE], VAL_VECTOR3))
					{
						Vector3 val;
						if(getVector3(prop->values.begin(), prop->values.end(), &val))
						{
							mSystem->setScale(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_PS_SCALE_VELOCITY])
				{
					// Property: scale_velocity
					if (passValidateProperty(compiler, prop, token[TOKEN_PS_ITERATION_INTERVAL], VAL_REAL))
					{
						Real val = 0.0f;
						if(getReal(prop->values.front(), &val))
						{
							mSystem->setScaleVelocity(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_PS_SCALE_TIME])
				{
					// Property: scale_time
					if (passValidateProperty(compiler, prop, token[TOKEN_PS_SCALE_TIME], VAL_REAL))
					{
						Real val = 0.0f;
						if(getReal(prop->values.front(), &val))
						{
							mSystem->setScaleTime(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_KEEP_LOCAL])
				{
					// Property: keep_local
					if (passValidateProperty(compiler, prop, token[TOKEN_KEEP_LOCAL], VAL_BOOL))
					{
						bool val;
						if(getBoolean(prop->values.front(), &val))
						{
							mSystem->setKeepLocal(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_PS_TIGHT_BOUNDING_BOX])
				{
					// Property: tight_bounding_box
					if (passValidateProperty(compiler, prop, token[TOKEN_PS_TIGHT_BOUNDING_BOX], VAL_BOOL))
					{
						bool val;
						if(getBoolean(prop->values.front(), &val))
						{
							mSystem->setTightBoundingBox(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_PS_CATEGORY])
				{
					// Property: category
					if (passValidateProperty(compiler, prop, token[TOKEN_PS_CATEGORY], VAL_STRING))
					{
						String val;
						if(getString(prop->values.front(), &val))
						{
							mSystem->setCategory(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_USE_ALIAS])
				{
					// Property: use_alias
					// The alias can only be a technique
					if (passValidateProperty(compiler, prop, token[TOKEN_USE_ALIAS], VAL_STRING))
					{
						String val;
						if(getString(prop->values.front(), &val))
						{
							IAlias* alias = ParticleSystemManager::getSingletonPtr()->getAlias(val);
							if (alias->getAliasType() == IAlias::AT_TECHNIQUE)
							{
								ParticleTechnique* technique = static_cast<ParticleTechnique*>(alias);
								ParticleTechnique* newTechnique = ParticleSystemManager::getSingletonPtr()->cloneTechnique(technique);
								mSystem->addTechnique(newTechnique);
							}
						}
					}
				}
				else
				{
					errorUnexpectedProperty(compiler, prop);
				}
			}
			else if((*i)->type == ANT_OBJECT)
			{
				processNode(compiler, *i);
			}
            else
			{
				errorUnexpectedToken(compiler, *i);
			}
		}
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	void ParticleSystemWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a ParticleSystem
		const ParticleSystem* system = static_cast<const ParticleSystem*>(element);

		// Write the header of the ParticleSystem
		String name = system->getTemplateName();
		if (name.empty())
		{
			name = system->getName();
		}
		serializer->writeLine(token[TOKEN_SYSTEM], name, 0, 1);
		serializer->writeLine("{", 0);

		// Write attributes (only the changed ones)
		if (system->isKeepLocal() != ParticleSystem::DEFAULT_KEEP_LOCAL) serializer->writeLine(
			token[TOKEN_KEEP_LOCAL], StringConverter::toString(system->isKeepLocal()), 4);
		if (system->getFixedTimeout() != ParticleSystem::DEFAULT_FIXED_TIMEOUT) serializer->writeLine(
			token[TOKEN_PS_FIXED_TIMEOUT], StringConverter::toString(system->getFixedTimeout()), 4);
		if (system->getIterationInterval() != ParticleSystem::DEFAULT_ITERATION_INTERVAL) serializer->writeLine(
			token[TOKEN_PS_ITERATION_INTERVAL], StringConverter::toString(system->getIterationInterval()), 4);
		if (system->getNonVisibleUpdateTimeout() != ParticleSystem::DEFAULT_NON_VISIBLE_UPDATE_TIMEOUT) serializer->writeLine(
			token[TOKEN_PS_NONVIS_UPDATE_TIMEOUT], StringConverter::toString(system->getNonVisibleUpdateTimeout()), 4);
		if (system->isSmoothLod() != ParticleSystem::DEFAULT_SMOOTH_LOD) serializer->writeLine(
			token[TOKEN_PS_SMOOTH_LOD], StringConverter::toString(system->isSmoothLod()), 4);
		if (system->getFastForwardTime() != ParticleSystem::DEFAULT_FAST_FORWARD_TIME ||
			system->getFastForwardInterval() != 0.0f)
		{
			serializer->writeLine(token[TOKEN_PS_FAST_FORWARD], StringConverter::toString(system->getFastForwardTime()) + " " +
				StringConverter::toString(system->getFastForwardInterval()), 4);
		}
		if (system->getMainCameraName() != ParticleSystem::DEFAULT_MAIN_CAMERA_NAME) serializer->writeLine(
			token[TOKEN_PS_MAIN_CAMERA_NAME], system->getMainCameraName(), 4);
		if (system->getScaleVelocity() != ParticleSystem::DEFAULT_SCALE_VELOCITY) serializer->writeLine(
			token[TOKEN_PS_SCALE_VELOCITY], StringConverter::toString(system->getScaleVelocity()), 4);
		if (system->getScaleTime() != ParticleSystem::DEFAULT_SCALE_TIME) serializer->writeLine(
			token[TOKEN_PS_SCALE_TIME], StringConverter::toString(system->getScaleTime()), 4);
		if (system->getScale() != ParticleSystem::DEFAULT_SCALE) serializer->writeLine(
			token[TOKEN_PS_SCALE], StringConverter::toString(system->getScale()), 4);
		if (system->hasTightBoundingBox() != ParticleSystem::DEFAULT_TIGHT_BOUNDINGBOX) serializer->writeLine(
			token[TOKEN_PS_TIGHT_BOUNDING_BOX], StringConverter::toString(system->hasTightBoundingBox()), 4);
		if (system->getCategory() != StringUtil::BLANK) serializer->writeLine(
			token[TOKEN_PS_CATEGORY], system->getCategory(), 4);

		// Write lod distances
		if (!(system->getLodDistances()).empty())
		{
			serializer->writeLine(
				token[TOKEN_PS_LOD_DISTANCES], ParticleScriptSerializer::toString(system->getLodDistances(), true), 4);
		}

		// Continue with the techniques
		size_t numerOfTechnique = system->getNumTechniques();
		serializer->context.beginSection(TECHNIQUE, 0);
		for (size_t i = 0; i < numerOfTechnique; ++i)
		{
			mParticleTechniqueWriter.write(serializer , system->getTechnique(i));
		}
		serializer->context.endSection();

		// Write the close bracket
		serializer->writeLine("}", 0);
	}

}
