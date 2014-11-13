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

#include "ParticleUniverseEmitterTokens.h"
#include "ParticleUniverseDynamicAttributeTokens.h"
#include "ParticleUniverseCameraDependency.h"

namespace ParticleUniverse
{
	/**************************************************************************
	 * EmitterTranslator
	 *************************************************************************/
	EmitterTranslator::EmitterTranslator()
		:mEmitter(0)
	{
	}
	//-------------------------------------------------------------------------
	void EmitterTranslator::translate(ScriptCompiler* compiler, const AbstractNodePtr &node)
	{
		ObjectAbstractNode* obj = reinterpret_cast<ObjectAbstractNode*>(node.get());
		ObjectAbstractNode* parent = obj->parent ? reinterpret_cast<ObjectAbstractNode*>(obj->parent) : 0;

		// The name of the obj is the type of the emitter
		// Remark: This can be solved by using a listener, so that obj->values is filled with type + name. Something for later
		String type;
		if(!obj->name.empty())
		{
			type = obj->name;
		}
		else
		{
			compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
			return;
		}

		// Get the factory
		ParticleEmitterFactory* particleEmitterFactory = ParticleSystemManager::getSingletonPtr()->getEmitterFactory(type);
		if (!particleEmitterFactory)
		{
			compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
			return;
		}

		// Create the emitter
		mEmitter = ParticleSystemManager::getSingletonPtr()->createEmitter(type);
		if (!mEmitter)
		{
			compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, obj->file, obj->line);
			return;
		}

		if (!obj->parent->context.isEmpty())
		{
			ParticleTechnique* technique = any_cast<ParticleTechnique*>(obj->parent->context);
			technique->addEmitter(mEmitter);
		}
		else
		{
			// It is an alias
			mEmitter->setAliasName(parent->name);
			ParticleSystemManager::getSingletonPtr()->addAlias(mEmitter);
		}

		// The first value is the (optional) name
		String name;
		if(!obj->values.empty())
		{
			getString(obj->values.front(), &name);
			mEmitter->setName(name);
		}

		// Set it in the context
		obj->context = Any(mEmitter);

		// Run through properties
		for(AbstractNodeList::iterator i = obj->children.begin(); i != obj->children.end(); ++i)
		{
			if((*i)->type == ANT_PROPERTY)
			{
				PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>((*i).get());
				if (prop->name == token[TOKEN_ENABLED])
				{
					// Property: enabled
					if (passValidateProperty(compiler, prop, token[TOKEN_ENABLED], VAL_BOOL))
					{
						bool val;
						if(getBoolean(prop->values.front(), &val))
						{
							mEmitter->setEnabled(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_POSITION])
				{
					// Property: positon
					if (passValidateProperty(compiler, prop, token[TOKEN_POSITION], VAL_VECTOR3))
					{
						Vector3 val;
						if(getVector3(prop->values.begin(), prop->values.end(), &val))
						{
							mEmitter->position = val;
							mEmitter->originalPosition = val;
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_DIRECTION])
				{
					// Property: direction
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_DIRECTION], VAL_VECTOR3))
					{
						Vector3 val;
						if(getVector3(prop->values.begin(), prop->values.end(), &val))
						{
							mEmitter->setParticleDirection(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_ORIENTATION])
				{
					// Property: orientation
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_ORIENTATION], VAL_QUATERNION))
					{
						Quaternion val;
						if(getQuaternion(prop->values.begin(), prop->values.end(), &val))
						{
							mEmitter->setParticleOrientation(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_START_ORIENTATION_RANGE])
				{
					// Property: start_orientation_range
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_START_ORIENTATION_RANGE], VAL_QUATERNION))
					{
						Quaternion val;
						if(getQuaternion(prop->values.begin(), prop->values.end(), &val))
						{
							mEmitter->setParticleOrientationRangeStart(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_ORIENTATION_RANGE_START])
				{
					// Property: range_start_orientation (deprecated and replaced by start_orientation_range)
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_ORIENTATION_RANGE_START], VAL_QUATERNION))
					{
						Quaternion val;
						if(getQuaternion(prop->values.begin(), prop->values.end(), &val))
						{
							mEmitter->setParticleOrientationRangeStart(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_END_ORIENTATION_RANGE])
				{
					// Property: end_orientation_range
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_END_ORIENTATION_RANGE], VAL_QUATERNION))
					{
						Quaternion val;
						if(getQuaternion(prop->values.begin(), prop->values.end(), &val))
						{
							mEmitter->setParticleOrientationRangeEnd(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_ORIENTATION_RANGE_END])
				{
					// Property: range_end_orientation (deprecated and replaced by end_orientation_range)
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_ORIENTATION_RANGE_END], VAL_QUATERNION))
					{
						Quaternion val;
						if(getQuaternion(prop->values.begin(), prop->values.end(), &val))
						{
							mEmitter->setParticleOrientationRangeEnd(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_EMISSION_RATE])
				{
					// Property: emission_rate
					// If it is a property, it is a fixed value
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_EMISSION_RATE], VAL_REAL))
					{
						Real val = 0.0f;
						if(getReal(prop->values.front(), &val))
						{
							DynamicAttributeFixed* dynamicAttributeFixed = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
							dynamicAttributeFixed->setValue(val);
							mEmitter->setDynEmissionRate(dynamicAttributeFixed);
						}
					}
				}
				else if (prop->name == token[TOKEN_TIME_TO_LIVE])
				{
					// Property: time_to_live
					// If it is a property, it is a fixed value
					if (passValidateProperty(compiler, prop, token[TOKEN_TIME_TO_LIVE], VAL_REAL))
					{
						Real val = 0.0f;
						if(getReal(prop->values.front(), &val))
						{
							DynamicAttributeFixed* dynamicAttributeFixed = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
							dynamicAttributeFixed->setValue(val);
							mEmitter->setDynTotalTimeToLive(dynamicAttributeFixed);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_MASS])
				{
					// Property: mass
					// If it is a property, it is a fixed value
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_MASS], VAL_REAL))
					{
						Real val = 0.0f;
						if(getReal(prop->values.front(), &val))
						{
							DynamicAttributeFixed* dynamicAttributeFixed = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
							dynamicAttributeFixed->setValue(val);
							mEmitter->setDynParticleMass(dynamicAttributeFixed);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_START_TEXCOORDS_RANGE])
				{
					// Property: start_texture_coords_range
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_START_TEXCOORDS_RANGE], VAL_UINT))
					{
						uint val = 0;
						if(getUInt(prop->values.front(), &val))
						{
							mEmitter->setParticleTextureCoordsRangeStart(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_START_TEXCOORDS])
				{
					// Property: start_texture_coords (deprecated and replaced by start_texture_coords_range)
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_START_TEXCOORDS], VAL_UINT))
					{
						uint val = 0;
						if(getUInt(prop->values.front(), &val))
						{
							mEmitter->setParticleTextureCoordsRangeStart(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_END_TEXCOORDS_RANGE])
				{
					// Property: end_texture_coords_range
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_END_TEXCOORDS_RANGE], VAL_UINT))
					{
						uint val = 0;
						if(getUInt(prop->values.front(), &val))
						{
							mEmitter->setParticleTextureCoordsRangeEnd(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_END_TEXCOORDS])
				{
					// Property: end_texture_coords (deprecated and replaced by end_texture_coords_range)
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_END_TEXCOORDS], VAL_UINT))
					{
						uint val = 0;
						if(getUInt(prop->values.front(), &val))
						{
							mEmitter->setParticleTextureCoordsRangeEnd(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_TEXCOORDS])
				{
					// Property: texture_coords
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_TEXCOORDS], VAL_UINT))
					{
						uint val = 0;
						if(getUInt(prop->values.front(), &val))
						{
							mEmitter->setParticleTextureCoords(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_START_COLOUR_RANGE])
				{
					// Property: start_colour_range
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_START_COLOUR_RANGE], VAL_COLOURVALUE))
					{
						ColourValue val;
						if(getColour(prop->values.begin(), prop->values.end(), &val))
						{
							mEmitter->setParticleColourRangeStart(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_END_COLOUR_RANGE])
				{
					// Property: end_colour_range
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_END_COLOUR_RANGE], VAL_COLOURVALUE))
					{
						ColourValue val;
						if(getColour(prop->values.begin(), prop->values.end(), &val))
						{
							mEmitter->setParticleColourRangeEnd(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_COLOUR])
				{
					// Property: colour
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_COLOUR], VAL_COLOURVALUE))
					{
						ColourValue val;
						if(getColour(prop->values.begin(), prop->values.end(), &val))
						{
							mEmitter->setParticleColour(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_VELOCITY])
				{
					// Property: velocity
					// If it is a property, it is a fixed value
					if (passValidateProperty(compiler, prop, token[TOKEN_VELOCITY], VAL_REAL))
					{
						Real val = 0.0f;
						if(getReal(prop->values.front(), &val))
						{
							DynamicAttributeFixed* dynamicAttributeFixed = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
							dynamicAttributeFixed->setValue(val);
							mEmitter->setDynVelocity(dynamicAttributeFixed);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_DURATION])
				{
					// Property: duration
					// If it is a property, it is a fixed value
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_DURATION], VAL_REAL))
					{
						Real val = 0.0f;
						if(getReal(prop->values.front(), &val))
						{
							DynamicAttributeFixed* dynamicAttributeFixed = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
							dynamicAttributeFixed->setValue(val);
							mEmitter->setDynDuration(dynamicAttributeFixed);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_REPEAT_DELAY])
				{
					// Property: repeat_delay
					// If it is a property, it is a fixed value
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_REPEAT_DELAY], VAL_REAL))
					{
						Real val = 0.0f;
						if(getReal(prop->values.front(), &val))
						{
							DynamicAttributeFixed* dynamicAttributeFixed = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
							dynamicAttributeFixed->setValue(val);
							mEmitter->setDynRepeatDelay(dynamicAttributeFixed);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_EMITS])
				{
					// Property: emits
					if (passValidatePropertyNumberOfValues(compiler, prop, token[TOKEN_EMITTER_EMITS], 2))
					{
						String particleType;
						String name;
						AbstractNodeList::const_iterator i = prop->values.begin();
						if (getString(*i, &particleType))
						{
							if (particleType == token[TOKEN_VISUAL_PARTICLE])
							{
								mEmitter->setEmitsType(Particle::PT_VISUAL);
							}
							else if (particleType == token[TOKEN_EMITTER_PARTICLE])
							{
								mEmitter->setEmitsType(Particle::PT_EMITTER);
							}
							else if (particleType == token[TOKEN_AFFECTOR_PARTICLE])
							{
								mEmitter->setEmitsType(Particle::PT_AFFECTOR);
							}
							else if (particleType == token[TOKEN_TECHNIQUE_PARTICLE])
							{
								mEmitter->setEmitsType(Particle::PT_TECHNIQUE);
							}
							else if (particleType == token[TOKEN_SYSTEM_PARTICLE])
							{
								mEmitter->setEmitsType(Particle::PT_SYSTEM);
							}
							++i;
							if (getString(*i, &name))
							{
								mEmitter->setEmitsName(name);
							}
						}
					}
				}
				else if (prop->name == token[TOKEN_ANGLE])
				{
					// Property: angle
					// If it is a property, it is a fixed value
					if (passValidateProperty(compiler, prop, token[TOKEN_ANGLE], VAL_REAL))
					{
						Real val = 0.0f;
						if(getReal(prop->values.front(), &val))
						{
							DynamicAttributeFixed* dynamicAttributeFixed = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
							dynamicAttributeFixed->setValue(val);
							mEmitter->setDynAngle(dynamicAttributeFixed);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_ALL_PARTICLE_DIM])
				{
					// Property: all_particle_dimensions
					// If it is a property, it is a fixed value
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_ALL_PARTICLE_DIM], VAL_REAL))
					{
						Real val = 0.0f;
						if(getReal(prop->values.front(), &val))
						{
							DynamicAttributeFixed* dynamicAttributeFixed = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
							dynamicAttributeFixed->setValue(val);
							mEmitter->setDynParticleAllDimensions(dynamicAttributeFixed);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_PARTICLE_WIDTH])
				{
					// Property: particle_width
					// If it is a property, it is a fixed value
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_PARTICLE_WIDTH], VAL_REAL))
					{
						Real val = 0.0f;
						if(getReal(prop->values.front(), &val))
						{
							DynamicAttributeFixed* dynamicAttributeFixed = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
							dynamicAttributeFixed->setValue(val);
							mEmitter->setDynParticleWidth(dynamicAttributeFixed);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_PARTICLE_HEIGHT])
				{
					// Property: particle_height
					// If it is a property, it is a fixed value
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_PARTICLE_HEIGHT], VAL_REAL))
					{
						Real val = 0.0f;
						if(getReal(prop->values.front(), &val))
						{
							DynamicAttributeFixed* dynamicAttributeFixed = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
							dynamicAttributeFixed->setValue(val);
							mEmitter->setDynParticleHeight(dynamicAttributeFixed);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_PARTICLE_DEPTH])
				{
					// Property: particle_depth
					// If it is a property, it is a fixed value
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_PARTICLE_DEPTH], VAL_REAL))
					{
						Real val = 0.0f;
						if(getReal(prop->values.front(), &val))
						{
							DynamicAttributeFixed* dynamicAttributeFixed = PU_NEW_T(DynamicAttributeFixed, MEMCATEGORY_SCENE_OBJECTS)();
							dynamicAttributeFixed->setValue(val);
							mEmitter->setDynParticleDepth(dynamicAttributeFixed);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_AUTO_DIRECTION])
				{
					// Property: auto_direction
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_AUTO_DIRECTION], VAL_BOOL))
					{
						bool val;
						if(getBoolean(prop->values.front(), &val))
						{
							mEmitter->setAutoDirection(val);
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
							mEmitter->setKeepLocal(val);
						}
					}
				}
				else if (prop->name == token[TOKEN_EMITTER_FORCE_EMISISON])
				{
					// Property: force_emission
					if (passValidateProperty(compiler, prop, token[TOKEN_EMITTER_FORCE_EMISISON], VAL_BOOL))
					{
						bool val;
						if(getBoolean(prop->values.front(), &val))
						{
							mEmitter->setForceEmission(val);
						}
					}
				}
				else if (particleEmitterFactory->translateChildProperty(compiler, *i))
				{
					// Parsed the property by another translator; do nothing
				}
				else
				{
					errorUnexpectedProperty(compiler, prop);
				}
			}
			else if((*i)->type == ANT_OBJECT)
			{
				ObjectAbstractNode* child = reinterpret_cast<ObjectAbstractNode*>((*i).get());
				DynamicAttributeTranslator dynamicAttributeTranslator;
				if (child->cls == token[TOKEN_EMITTER_EMISSION_RATE])
				{
					// Property: emission_rate
					dynamicAttributeTranslator.translate(compiler, *i);
					DynamicAttribute* dynamicAttribute = any_cast<DynamicAttribute*>(child->context);
					mEmitter->setDynEmissionRate(dynamicAttribute);
				}
				else if (child->cls == token[TOKEN_TIME_TO_LIVE])
				{
					// Property: time_to_live
					dynamicAttributeTranslator.translate(compiler, *i);
					DynamicAttribute* dynamicAttribute = any_cast<DynamicAttribute*>(child->context);
					mEmitter->setDynTotalTimeToLive(dynamicAttribute);
				}
				else if (child->cls == token[TOKEN_EMITTER_MASS])
				{
					// Property: mass
					dynamicAttributeTranslator.translate(compiler, *i);
					DynamicAttribute* dynamicAttribute = any_cast<DynamicAttribute*>(child->context);
					mEmitter->setDynParticleMass(dynamicAttribute);
				}
				else if (child->cls == token[TOKEN_VELOCITY])
				{
					// Property: velocity
					dynamicAttributeTranslator.translate(compiler, *i);
					DynamicAttribute* dynamicAttribute = any_cast<DynamicAttribute*>(child->context);
					mEmitter->setDynVelocity(dynamicAttribute);
				}
				else if (child->cls == token[TOKEN_EMITTER_DURATION])
				{
					// Property: duration
					dynamicAttributeTranslator.translate(compiler, *i);
					DynamicAttribute* dynamicAttribute = any_cast<DynamicAttribute*>(child->context);
					mEmitter->setDynDuration(dynamicAttribute);
				}
				else if (child->cls == token[TOKEN_EMITTER_REPEAT_DELAY])
				{
					// Property: repeat_delay
					dynamicAttributeTranslator.translate(compiler, *i);
					DynamicAttribute* dynamicAttribute = any_cast<DynamicAttribute*>(child->context);
					mEmitter->setDynRepeatDelay(dynamicAttribute);
				}
				else if (child->cls == token[TOKEN_ANGLE])
				{
					// Property: angle
					dynamicAttributeTranslator.translate(compiler, *i);
					DynamicAttribute* dynamicAttribute = any_cast<DynamicAttribute*>(child->context);
					mEmitter->setDynAngle(dynamicAttribute);
				}
				else if (child->cls == token[TOKEN_EMITTER_ALL_PARTICLE_DIM])
				{
					// Property: all_particle_dimensions
					dynamicAttributeTranslator.translate(compiler, *i);
					DynamicAttribute* dynamicAttribute = any_cast<DynamicAttribute*>(child->context);
					mEmitter->setDynParticleAllDimensions(dynamicAttribute);
				}
				else if (child->cls == token[TOKEN_EMITTER_PARTICLE_WIDTH])
				{
					// Property: particle_width
					dynamicAttributeTranslator.translate(compiler, *i);
					DynamicAttribute* dynamicAttribute = any_cast<DynamicAttribute*>(child->context);
					mEmitter->setDynParticleWidth(dynamicAttribute);
				}
				else if (child->cls == token[TOKEN_EMITTER_PARTICLE_HEIGHT])
				{
					// Property: particle_height
					dynamicAttributeTranslator.translate(compiler, *i);
					DynamicAttribute* dynamicAttribute = any_cast<DynamicAttribute*>(child->context);
					mEmitter->setDynParticleHeight(dynamicAttribute);
				}
				else if (child->cls == token[TOKEN_EMITTER_PARTICLE_DEPTH])
				{
					// Property: particle_depth
					dynamicAttributeTranslator.translate(compiler, *i);
					DynamicAttribute* dynamicAttribute = any_cast<DynamicAttribute*>(child->context);
					mEmitter->setDynParticleDepth(dynamicAttribute);
				}
				else if (child->cls == token[TOKEN_CAMERA_DEPENDENCY])
				{
					// Property: it can only be a camera_dependency for emission rate
					CameraDependency* cameraDependency = PU_NEW_T(CameraDependency, MEMCATEGORY_SCRIPTING)();
					child->context = Any(cameraDependency);
					CameraDependencyTranslator cameraDependencyTranslator;
					cameraDependencyTranslator.translate(compiler, *i);
					Real threshold = cameraDependency->getThreshold();
					mEmitter->setEmissionRateCameraDependency(threshold * threshold, cameraDependency->isIncrease());
					
					// Delete the camera dependency
					PU_DELETE_T(cameraDependency, CameraDependency, MEMCATEGORY_SCRIPTING);
				}
				else if (particleEmitterFactory->translateChildObject(compiler, *i))
				{
					// Parsed the object by another translator; do nothing
				}
				else
				{
					processNode(compiler, *i);
				}
			}
            else
			{
				errorUnexpectedToken(compiler, *i);
			}
		}
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------	//-----------------------------------------------------------------------
	void ParticleEmitterWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
	{
		// Cast the element to a ParticleEmitter
		const ParticleEmitter* emitter = static_cast<const ParticleEmitter*>(element);

		// Write own attributes
		DynamicAttributeFactory dynamicAttributeFactory;

		if (emitter->getDynEmissionRate()->getType() != DynamicAttribute::DAT_FIXED || 
			emitter->getDynEmissionRate()->getValue() != ParticleEmitter::DEFAULT_EMISSION_RATE)
		{
			serializer->setKeyword(token[TOKEN_EMITTER_EMISSION_RATE]);
			serializer->setIndentation(12);
			dynamicAttributeFactory.write(serializer, emitter->getDynEmissionRate());
		}

		if (emitter->getDynAngle()->getType() != DynamicAttribute::DAT_FIXED || 
			emitter->getDynAngle()->getValue() != ParticleEmitter::DEFAULT_ANGLE)
		{
			serializer->setKeyword(token[TOKEN_ANGLE]);
			serializer->setIndentation(12);
			dynamicAttributeFactory.write(serializer, emitter->getDynAngle());
		}

		if (emitter->getDynTotalTimeToLive()->getType() != DynamicAttribute::DAT_FIXED || 
			emitter->getDynTotalTimeToLive()->getValue() != ParticleEmitter::DEFAULT_TIME_TO_LIVE)
		{
			serializer->setKeyword(token[TOKEN_TIME_TO_LIVE]);
			serializer->setIndentation(12);
			dynamicAttributeFactory.write(serializer, emitter->getDynTotalTimeToLive());
		}

		if (emitter->getDynParticleMass()->getType() != DynamicAttribute::DAT_FIXED || 
			emitter->getDynParticleMass()->getValue() != ParticleEmitter::DEFAULT_MASS)
		{
			serializer->setKeyword(token[TOKEN_EMITTER_MASS]);
			serializer->setIndentation(12);
			dynamicAttributeFactory.write(serializer, emitter->getDynParticleMass());
		}

		if (emitter->getDynVelocity()->getType() != DynamicAttribute::DAT_FIXED || 
			emitter->getDynVelocity()->getValue() != ParticleEmitter::DEFAULT_VELOCITY)
		{
			serializer->setKeyword(token[TOKEN_VELOCITY]);
			serializer->setIndentation(12);
			dynamicAttributeFactory.write(serializer, emitter->getDynVelocity());
		}

		if (emitter->getDynDuration()->getType() != DynamicAttribute::DAT_FIXED || 
			emitter->getDynDuration()->getValue() != ParticleEmitter::DEFAULT_DURATION)
		{
			serializer->setKeyword(token[TOKEN_EMITTER_DURATION]);
			serializer->setIndentation(12);
			dynamicAttributeFactory.write(serializer, emitter->getDynDuration());
		}

		if (emitter->getDynRepeatDelay()->getType() != DynamicAttribute::DAT_FIXED || 
			emitter->getDynRepeatDelay()->getValue() != ParticleEmitter::DEFAULT_REPEAT_DELAY)
		{
			serializer->setKeyword(token[TOKEN_EMITTER_REPEAT_DELAY]);
			serializer->setIndentation(12);
			dynamicAttributeFactory.write(serializer, emitter->getDynRepeatDelay());
		}

		if (emitter->getDynParticleAllDimensions()->getType() != DynamicAttribute::DAT_FIXED || 
			emitter->getDynParticleAllDimensions()->getValue() != ParticleEmitter::DEFAULT_DIMENSIONS)
		{
			serializer->setKeyword(token[TOKEN_EMITTER_ALL_PARTICLE_DIM]);
			serializer->setIndentation(12);
			dynamicAttributeFactory.write(serializer, emitter->getDynParticleAllDimensions());
		}

		if (emitter->getDynParticleWidth()->getType() != DynamicAttribute::DAT_FIXED || 
			emitter->getDynParticleWidth()->getValue() != ParticleEmitter::DEFAULT_WIDTH)
		{
			serializer->setKeyword(token[TOKEN_EMITTER_PARTICLE_WIDTH]);
			serializer->setIndentation(12);
			dynamicAttributeFactory.write(serializer, emitter->getDynParticleWidth());
		}

		if (emitter->getDynParticleHeight()->getType() != DynamicAttribute::DAT_FIXED || 
			emitter->getDynParticleHeight()->getValue() != ParticleEmitter::DEFAULT_HEIGHT)
		{
			serializer->setKeyword(token[TOKEN_EMITTER_PARTICLE_HEIGHT]);
			serializer->setIndentation(12);
			dynamicAttributeFactory.write(serializer, emitter->getDynParticleHeight());
		}

		if (emitter->getDynParticleDepth()->getType() != DynamicAttribute::DAT_FIXED || 
			emitter->getDynParticleDepth()->getValue() != ParticleEmitter::DEFAULT_DEPTH)
		{
			serializer->setKeyword(token[TOKEN_EMITTER_PARTICLE_DEPTH]);
			serializer->setIndentation(12);
			dynamicAttributeFactory.write(serializer, emitter->getDynParticleDepth());
		}

		if (emitter->_getOriginalEnabled() != ParticleEmitter::DEFAULT_ENABLED) serializer->writeLine(
			token[TOKEN_ENABLED], StringConverter::toString(emitter->_getOriginalEnabled()), 12);
		if (emitter->position != ParticleEmitter::DEFAULT_POSITION) serializer->writeLine(
			token[TOKEN_POSITION], StringConverter::toString(emitter->position), 12);
		if (emitter->isKeepLocal() != ParticleEmitter::DEFAULT_KEEP_LOCAL) serializer->writeLine(
			token[TOKEN_KEEP_LOCAL], StringConverter::toString(emitter->isKeepLocal()), 12);
		if (emitter->getOriginalParticleDirection() != ParticleEmitter::DEFAULT_DIRECTION) serializer->writeLine(
			token[TOKEN_EMITTER_DIRECTION], StringConverter::toString(emitter->getOriginalParticleDirection()), 12);
		if (emitter->getParticleOrientation() != ParticleEmitter::DEFAULT_ORIENTATION) serializer->writeLine(
			token[TOKEN_EMITTER_ORIENTATION], StringConverter::toString(emitter->getParticleOrientation()), 12);
		if (emitter->getParticleOrientationRangeStart() != ParticleEmitter::DEFAULT_ORIENTATION_RANGE_START) serializer->writeLine(
			token[TOKEN_EMITTER_START_ORIENTATION_RANGE], StringConverter::toString(emitter->getParticleOrientationRangeStart()), 12);
		if (emitter->getParticleOrientationRangeEnd() != ParticleEmitter::DEFAULT_ORIENTATION_RANGE_END) serializer->writeLine(
			token[TOKEN_EMITTER_END_ORIENTATION_RANGE], StringConverter::toString(emitter->getParticleOrientationRangeEnd()), 12);
		if (emitter->getEmitsType() != ParticleEmitter::DEFAULT_EMITS)
		{
			String particle = token[TOKEN_EMITTER_PARTICLE];
			if (emitter->getEmitsType() == Particle::PT_AFFECTOR) particle = token[TOKEN_AFFECTOR_PARTICLE];
			else if (emitter->getEmitsType() == Particle::PT_TECHNIQUE) particle = token[TOKEN_TECHNIQUE_PARTICLE];
			else if (emitter->getEmitsType() == Particle::PT_SYSTEM) particle = token[TOKEN_SYSTEM_PARTICLE];
			serializer->writeLine(token[TOKEN_EMITTER_EMITS], particle, emitter->getEmitsName(), 12);
		}
		if (emitter->getParticleTextureCoordsRangeStart() != ParticleEmitter::DEFAULT_START_TEXTURE_COORDS) serializer->writeLine(
			token[TOKEN_EMITTER_START_TEXCOORDS_RANGE], StringConverter::toString(emitter->getParticleTextureCoordsRangeStart()), 12);
		if (emitter->getParticleTextureCoordsRangeEnd() != ParticleEmitter::DEFAULT_END_TEXTURE_COORDS) serializer->writeLine(
			token[TOKEN_EMITTER_END_TEXCOORDS_RANGE], StringConverter::toString(emitter->getParticleTextureCoordsRangeEnd()), 12);
		if (emitter->getParticleTextureCoords() != ParticleEmitter::DEFAULT_TEXTURE_COORDS) serializer->writeLine(
			token[TOKEN_EMITTER_TEXCOORDS], StringConverter::toString(emitter->getParticleTextureCoords()), 12);
		if (emitter->getParticleColourRangeStart() != ParticleEmitter::DEFAULT_START_COLOUR_RANGE) serializer->writeLine(
			token[TOKEN_EMITTER_START_COLOUR_RANGE], StringConverter::toString(emitter->getParticleColourRangeStart()), 12);
		if (emitter->getParticleColourRangeEnd() != ParticleEmitter::DEFAULT_END_COLOUR_RANGE) serializer->writeLine(
			token[TOKEN_EMITTER_END_COLOUR_RANGE], StringConverter::toString(emitter->getParticleColourRangeEnd()), 12);
		if (emitter->getParticleColour() != ParticleEmitter::DEFAULT_COLOUR) serializer->writeLine(
			token[TOKEN_EMITTER_COLOUR], StringConverter::toString(emitter->getParticleColour()), 12);
		if (emitter->isAutoDirection() != ParticleEmitter::DEFAULT_AUTO_DIRECTION) serializer->writeLine(
			token[TOKEN_EMITTER_AUTO_DIRECTION], StringConverter::toString(emitter->isAutoDirection()), 12);
		if (emitter->isForceEmission() != ParticleEmitter::DEFAULT_FORCE_EMISSION) serializer->writeLine(
			token[TOKEN_EMITTER_FORCE_EMISISON], StringConverter::toString(emitter->isForceEmission()), 12);

		if (emitter->getEmissionRateCameraDependency())
		{
			serializer->writeLine(token[TOKEN_CAMERA_DEPENDENCY], token[TOKEN_EMITTER_EMISSION_RATE], 12);
			serializer->writeLine("{", 12);
			if (Math::Sqrt(emitter->getEmissionRateCameraDependency()->getThreshold()) != CameraDependency::DEFAULT_DISTANCE_THRESHOLD) serializer->writeLine(
				token[TOKEN_DISTANCE_THRESHOLD], StringConverter::toString(Math::Sqrt(emitter->getEmissionRateCameraDependency()->getThreshold())), 16);
			if (emitter->getEmissionRateCameraDependency()->isIncrease() != CameraDependency::DEFAULT_INCREASE) serializer->writeLine(
				token[TOKEN_INCREASE], StringConverter::toString(emitter->getEmissionRateCameraDependency()->isIncrease()), 16);
			serializer->writeLine("}", 12);
		}
	}

}
