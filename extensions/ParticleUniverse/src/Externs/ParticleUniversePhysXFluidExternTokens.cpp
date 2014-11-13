/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode
Special thanks to: M. Geissler

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#include "ParticleUniversePCH.h"

#ifdef PU_PHYSICS_PHYSX

	#ifndef PARTICLE_UNIVERSE_EXPORTS
	#define PARTICLE_UNIVERSE_EXPORTS
	#endif

	#include "ParticleUniversePrerequisites.h"
	#include "Externs/ParticleUniversePhysXFluidExternTokens.h"
	#include "Externs/ParticleUniversePhysXFluidExtern.h"

	namespace ParticleUniverse
	{
		//-----------------------------------------------------------------------
		bool PhysXFluidExternTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
		{
			PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
			Extern* ex = any_cast<Extern*>(prop->parent->context);
			PhysXFluidExtern* externObject = static_cast<PhysXFluidExtern*>(ex);
			NxFluidDesc fluidDesc = externObject->mFluidDesc;

			if (prop->name == token[TOKEN_REST_PARTICLE_PER_METER])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_REST_PARTICLE_PER_METER], VAL_REAL))
				{
					Real val = 0.0f;
					if(getReal(prop->values.front(), &val))
					{
						externObject->mFluidDesc.restParticlesPerMeter = val;
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_REST_DENSITY])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_REST_DENSITY], VAL_REAL))
				{
					Real val = 0.0f;
					if(getReal(prop->values.front(), &val))
					{
						externObject->mFluidDesc.restDensity = val;
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_KERNEL_RADIUS_MULTIPLIER])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_KERNEL_RADIUS_MULTIPLIER], VAL_REAL))
				{
					Real val = 0.0f;
					if(getReal(prop->values.front(), &val))
					{
						externObject->mFluidDesc.kernelRadiusMultiplier = val;
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_MOTION_LIMIT_MULTIPLIER])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_MOTION_LIMIT_MULTIPLIER], VAL_REAL))
				{
					Real val = 0.0f;
					if(getReal(prop->values.front(), &val))
					{
						externObject->mFluidDesc.motionLimitMultiplier = val;
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_COLLISION_DISTANCE_MULTIPLIER])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_COLLISION_DISTANCE_MULTIPLIER], VAL_REAL))
				{
					Real val = 0.0f;
					if(getReal(prop->values.front(), &val))
					{
						externObject->mFluidDesc.collisionDistanceMultiplier = val;
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_PACKET_SIZE_MULTIPLIER])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_PACKET_SIZE_MULTIPLIER], VAL_UINT))
				{
					uint32 val = 0;
					if(getUInt(prop->values.front(), &val))
					{
						externObject->mFluidDesc.packetSizeMultiplier = val;
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_STIFFNESS])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_STIFFNESS], VAL_REAL))
				{
					Real val = 0.0f;
					if(getReal(prop->values.front(), &val))
					{
						externObject->mFluidDesc.stiffness = val;
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_VISCOSITY])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_VISCOSITY], VAL_REAL))
				{
					Real val = 0.0f;
					if(getReal(prop->values.front(), &val))
					{
						externObject->mFluidDesc.viscosity = val;
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_SURFACE_TENSION])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_SURFACE_TENSION], VAL_REAL))
				{
					Real val = 0.0f;
					if(getReal(prop->values.front(), &val))
					{
						externObject->mFluidDesc.surfaceTension = val;
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_DAMPING])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_DAMPING], VAL_REAL))
				{
					Real val = 0.0f;
					if(getReal(prop->values.front(), &val))
					{
						externObject->mFluidDesc.damping = val;
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_EXTERNAL_ACCELERATION])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_EXTERNAL_ACCELERATION], VAL_VECTOR3))
				{
					Vector3 val;
					if(getVector3(prop->values.begin(), prop->values.end(), &val))
					{
						externObject->mFluidDesc.externalAcceleration = NxVec3(val.x, val.y, val.z);
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}

				}
			}
			else if (prop->name == token[TOKEN_RESTITUTION_FOR_STATIC_SHAPES])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_RESTITUTION_FOR_STATIC_SHAPES], VAL_REAL))
				{
					Real val = 0.0f;
					if(getReal(prop->values.front(), &val))
					{
						externObject->mFluidDesc.restitutionForStaticShapes = val;
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_DYNAMIC_FRICTION_FOR_STATIC_SHAPES])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_DYNAMIC_FRICTION_FOR_STATIC_SHAPES], VAL_REAL))
				{
					Real val = 0.0f;
					if(getReal(prop->values.front(), &val))
					{
						externObject->mFluidDesc.dynamicFrictionForStaticShapes = val;
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_STATIC_FRICTION_FOR_STATIC_SHAPES])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_STATIC_FRICTION_FOR_STATIC_SHAPES], VAL_REAL))
				{
					Real val = 0.0f;
					if(getReal(prop->values.front(), &val))
					{
						externObject->mFluidDesc.staticFrictionForStaticShapes = val;
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_ATTRACTION_FOR_STATIC_SHAPES])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_ATTRACTION_FOR_STATIC_SHAPES], VAL_REAL))
				{
					Real val = 0.0f;
					if(getReal(prop->values.front(), &val))
					{
						externObject->mFluidDesc.attractionForStaticShapes = val;
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_RESTITUTION_FOR_DYNAMIC_SHAPES])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_RESTITUTION_FOR_DYNAMIC_SHAPES], VAL_REAL))
				{
					Real val = 0.0f;
					if(getReal(prop->values.front(), &val))
					{
						externObject->mFluidDesc.restitutionForDynamicShapes = val;
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_DYNAMIC_FRICTION_FOR_DYNAMIC_SHAPES])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_DYNAMIC_FRICTION_FOR_DYNAMIC_SHAPES], VAL_REAL))
				{
					Real val = 0.0f;
					if(getReal(prop->values.front(), &val))
					{
						externObject->mFluidDesc.dynamicFrictionForDynamicShapes = val;
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_STATIC_FRICTION_FOR_DYNAMIC_SHAPES])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_STATIC_FRICTION_FOR_DYNAMIC_SHAPES], VAL_REAL))
				{
					Real val = 0.0f;
					if(getReal(prop->values.front(), &val))
					{
						externObject->mFluidDesc.staticFrictionForDynamicShapes = val;
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_ATTRACTION_FOR_DYNAMIC_SHAPES])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_ATTRACTION_FOR_DYNAMIC_SHAPES], VAL_REAL))
				{
					Real val = 0.0f;
					if(getReal(prop->values.front(), &val))
					{
						externObject->mFluidDesc.attractionForDynamicShapes = val;
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_COLLISION_RESPONSE_COEFFICIENT])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_COLLISION_RESPONSE_COEFFICIENT], VAL_REAL))
				{
					Real val = 0.0f;
					if(getReal(prop->values.front(), &val))
					{
						externObject->mFluidDesc.collisionResponseCoefficient = val;
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_COLLISION_GROUP])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_COLLISION_GROUP], VAL_UINT))
				{
					uint val = 0;
					if(getUInt(prop->values.front(), &val))
					{
						externObject->mFluidDesc.collisionGroup = val;
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_GROUP_MASK])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_GROUP_MASK], VAL_VECTOR4))
				{
					Vector4 val;
					if(getVector4(prop->values.begin(), prop->values.end(), &val))
					{
						externObject->mFluidDesc.groupsMask.bits0 = (NxU32)val.x;
						externObject->mFluidDesc.groupsMask.bits1 = (NxU32)val.y;
						externObject->mFluidDesc.groupsMask.bits2 = (NxU32)val.z;
						externObject->mFluidDesc.groupsMask.bits3 = (NxU32)val.w;
						if (!externObject->mFluidDesc.isValid()) 
						{
							externObject->mFluidDesc = fluidDesc;
							compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
						}
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_SIMULATION_METHOD])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_SIMULATION_METHOD], VAL_STRING))
				{
					externObject->mFluidDesc.simulationMethod = NX_F_SPH;
					String val;
					if(getString(prop->values.front(), &val))
					{
						if (val == token[TOKEN_NOINTERCOLLISION])
						{
							externObject->mFluidDesc.simulationMethod = NX_F_NO_PARTICLE_INTERACTION;
						}
						else if (val == token[TOKEN_MIX_INTERCOLLISION])
						{
							externObject->mFluidDesc.simulationMethod = NX_F_MIXED_MODE;
						}
					}
					if (!externObject->mFluidDesc.isValid()) 
					{
						externObject->mFluidDesc = fluidDesc;
						compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
					}
					return true;
				}
			}
			else if (prop->name == token[TOKEN_COLLISION_METHOD])
			{
				if (passValidateProperty(compiler, prop, token[TOKEN_COLLISION_METHOD], VAL_STRING))
				{
					externObject->mFluidDesc.collisionMethod = NX_F_STATIC;
					String val;
					if(getString(prop->values.front(), &val))
					{
						if (val == token[TOKEN_DYNAMIC])
						{
							externObject->mFluidDesc.collisionMethod = NX_F_DYNAMIC;
						}
					}
					if (!externObject->mFluidDesc.isValid()) 
					{
						externObject->mFluidDesc = fluidDesc;
						compiler->addError(ScriptCompiler::CE_INVALIDPARAMETERS, prop->file, prop->line);
					}
					return true;
				}
			}

			return false;
		}
		//-----------------------------------------------------------------------
		bool PhysXFluidExternTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
		{
			ObjectAbstractNode* child = reinterpret_cast<ObjectAbstractNode*>(node.get());
			Extern* ex = any_cast<Extern*>(child->parent->context);
			PhysXFluidExtern* externObject = static_cast<PhysXFluidExtern*>(ex);

			if (child->cls == token[TOKEN_FLAGS])
			{
				PhysXFluidFlagTranslator physXFluidFlagTranslator;
				child->context = Any(externObject);
				physXFluidFlagTranslator.translate(compiler, node);
				return true;
			}

			return false;
		}
		//-----------------------------------------------------------------------
		void PhysXFluidFlagTranslator::translate(ScriptCompiler* compiler, const AbstractNodePtr &node)
		{
			ObjectAbstractNode* obj = reinterpret_cast<ObjectAbstractNode*>(node.get());
			PhysXFluidExtern* externObject = any_cast<PhysXFluidExtern*>(obj->context);

			// Run through properties
			for(AbstractNodeList::iterator i = obj->children.begin(); i != obj->children.end(); ++i)
			{
				if((*i)->type == ANT_PROPERTY)
				{
					PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>((*i).get());
					if (prop->name == token[TOKEN_FLAG_VISUALIZATION])
					{
						if (passValidateProperty(compiler, prop, token[TOKEN_FLAG_VISUALIZATION], VAL_BOOL))
						{
							bool val = false;
							if(getBoolean(prop->values.front(), &val))
							{
								if (val)
								{
									externObject->mFluidDesc.flags |= NX_FF_VISUALIZATION;
								}
								else
								{
									externObject->mFluidDesc.flags &= ~NX_FF_VISUALIZATION;
								}
							}
						}
					}
					else if (prop->name == token[TOKEN_FLAG_DISABLE_GRAVITY])
					{
						if (passValidateProperty(compiler, prop, token[TOKEN_FLAG_DISABLE_GRAVITY], VAL_BOOL))
						{
							bool val = false;
							if(getBoolean(prop->values.front(), &val))
							{
								if (val)
								{
									externObject->mFluidDesc.flags |= NX_FF_DISABLE_GRAVITY;
								}
								else
								{
									externObject->mFluidDesc.flags &= ~NX_FF_DISABLE_GRAVITY;
								}
							}
						}
					}
					else if (prop->name == token[TOKEN_FLAG_COLLISION_TWOWAY])
					{
						if (passValidateProperty(compiler, prop, token[TOKEN_FLAG_COLLISION_TWOWAY], VAL_BOOL))
						{
							bool val = false;
							if(getBoolean(prop->values.front(), &val))
							{
								if (val)
								{
									externObject->mFluidDesc.flags |= NX_FF_COLLISION_TWOWAY;
								}
								else
								{
									externObject->mFluidDesc.flags &= ~NX_FF_COLLISION_TWOWAY;
								}
							}
						}
					}
					else if (prop->name == token[TOKEN_FLAG_FLUID_ENABLED])
					{
						if (passValidateProperty(compiler, prop, token[TOKEN_FLAG_FLUID_ENABLED], VAL_BOOL))
						{
							bool val = false;
							if(getBoolean(prop->values.front(), &val))
							{
								if (val)
								{
									externObject->mFluidDesc.flags |= NX_FF_ENABLED;
								}
								else
								{
									externObject->mFluidDesc.flags &= ~NX_FF_ENABLED;
								}
							}
						}
					}
					else if (prop->name == token[TOKEN_FLAG_HARDWARE])
					{
						if (passValidateProperty(compiler, prop, token[TOKEN_FLAG_HARDWARE], VAL_BOOL))
						{
							bool val = false;
							if(getBoolean(prop->values.front(), &val))
							{
								if (val)
								{
									externObject->mFluidDesc.flags |= NX_FF_HARDWARE;
								}
								else
								{
									externObject->mFluidDesc.flags &= ~NX_FF_HARDWARE;
								}
							}
						}
					}
					else if (prop->name == token[TOKEN_FLAG_PRIORITY_MODE])
					{
						if (passValidateProperty(compiler, prop, token[TOKEN_FLAG_PRIORITY_MODE], VAL_BOOL))
						{
							bool val = false;
							if(getBoolean(prop->values.front(), &val))
							{
								if (val)
								{
									externObject->mFluidDesc.flags |= NX_FF_PRIORITY_MODE;
								}
								else
								{
									externObject->mFluidDesc.flags &= ~NX_FF_PRIORITY_MODE;
								}
							}
						}
					}
					else if (prop->name == token[TOKEN_FLAG_PROJECT_TO_PLANE])
					{
						if (passValidateProperty(compiler, prop, token[TOKEN_FLAG_PROJECT_TO_PLANE], VAL_BOOL))
						{
							bool val = false;
							if(getBoolean(prop->values.front(), &val))
							{
								if (val)
								{
									externObject->mFluidDesc.flags |= NX_FF_PROJECT_TO_PLANE;
								}
								else
								{
									externObject->mFluidDesc.flags &= ~NX_FF_PROJECT_TO_PLANE;
								}
							}
						}
					}
					else if (prop->name == token[TOKEN_FLAG_STRICT_COOKING_FORMAT])
					{
						if (passValidateProperty(compiler, prop, token[TOKEN_FLAG_STRICT_COOKING_FORMAT], VAL_BOOL))
						{
							bool val = false;
							if(getBoolean(prop->values.front(), &val))
							{
								if (val)
								{
									externObject->mFluidDesc.flags |= NX_FF_FORCE_STRICT_COOKING_FORMAT;
								}
								else
								{
									externObject->mFluidDesc.flags &= ~NX_FF_FORCE_STRICT_COOKING_FORMAT;
								}
							}
						}
					}
					else
					{
						errorUnexpectedProperty(compiler, prop);
					}
				}
			}
		}
		//-----------------------------------------------------------------------
		//-----------------------------------------------------------------------
		//-----------------------------------------------------------------------
		void PhysXFluidExternWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
		{
			// Cast the element to a PhysXFluidExtern
			const Extern* externObject = static_cast<const Extern*>(element);
			const PhysXFluidExtern* physXFluidExtern = static_cast<const PhysXFluidExtern*>(externObject);
			serializer->writeLine(token[TOKEN_EXTERN], externObject->getExternType(), externObject->getName(), 8);
			serializer->writeLine("{", 8);
	
			// Write base attributes
			ExternWriter::write(serializer, element);
	
			// Start: Own attributes to write
			NxFluidDesc fluidDesc;
			fluidDesc.setToDefault();

			if (physXFluidExtern->mFluidDesc.restParticlesPerMeter != fluidDesc.restParticlesPerMeter)
				serializer->writeLine(token[TOKEN_REST_PARTICLE_PER_METER], StringConverter::toString(physXFluidExtern->mFluidDesc.restParticlesPerMeter), 12);

			if (physXFluidExtern->mFluidDesc.restDensity != fluidDesc.restDensity)
				serializer->writeLine(token[TOKEN_REST_DENSITY], StringConverter::toString(physXFluidExtern->mFluidDesc.restDensity), 12);

			if (physXFluidExtern->mFluidDesc.kernelRadiusMultiplier != fluidDesc.kernelRadiusMultiplier)
				serializer->writeLine(token[TOKEN_KERNEL_RADIUS_MULTIPLIER], StringConverter::toString(physXFluidExtern->mFluidDesc.kernelRadiusMultiplier), 12);

			if (physXFluidExtern->mFluidDesc.motionLimitMultiplier != fluidDesc.motionLimitMultiplier)
				serializer->writeLine(token[TOKEN_MOTION_LIMIT_MULTIPLIER], StringConverter::toString(physXFluidExtern->mFluidDesc.motionLimitMultiplier), 12);

			if (physXFluidExtern->mFluidDesc.collisionDistanceMultiplier != fluidDesc.collisionDistanceMultiplier)
				serializer->writeLine(token[TOKEN_COLLISION_DISTANCE_MULTIPLIER], StringConverter::toString(physXFluidExtern->mFluidDesc.collisionDistanceMultiplier), 12);

			if (physXFluidExtern->mFluidDesc.packetSizeMultiplier != fluidDesc.packetSizeMultiplier)
				serializer->writeLine(token[TOKEN_PACKET_SIZE_MULTIPLIER], StringConverter::toString(physXFluidExtern->mFluidDesc.packetSizeMultiplier), 12);

			if (physXFluidExtern->mFluidDesc.stiffness != fluidDesc.stiffness)
				serializer->writeLine(token[TOKEN_STIFFNESS], StringConverter::toString(physXFluidExtern->mFluidDesc.stiffness), 12);

			if (physXFluidExtern->mFluidDesc.viscosity != fluidDesc.viscosity)
				serializer->writeLine(token[TOKEN_VISCOSITY], StringConverter::toString(physXFluidExtern->mFluidDesc.viscosity), 12);

			if (physXFluidExtern->mFluidDesc.surfaceTension != fluidDesc.surfaceTension)
				serializer->writeLine(token[TOKEN_SURFACE_TENSION], StringConverter::toString(physXFluidExtern->mFluidDesc.surfaceTension), 12);

			if (physXFluidExtern->mFluidDesc.damping != fluidDesc.damping)
				serializer->writeLine(token[TOKEN_DAMPING], StringConverter::toString(physXFluidExtern->mFluidDesc.damping), 12);

			if (physXFluidExtern->mFluidDesc.externalAcceleration != fluidDesc.externalAcceleration)
				serializer->writeLine(token[TOKEN_EXTERNAL_ACCELERATION], StringConverter::toString(physXFluidExtern->mFluidDesc.externalAcceleration.x) + " " + 
				StringConverter::toString(physXFluidExtern->mFluidDesc.externalAcceleration.y) + " " +
				StringConverter::toString(physXFluidExtern->mFluidDesc.externalAcceleration.z), 12);

			//////////////////////////////////////////////////////////////////////////
			if (physXFluidExtern->mFluidDesc.restitutionForStaticShapes != fluidDesc.restitutionForStaticShapes)
				serializer->writeLine(token[TOKEN_RESTITUTION_FOR_STATIC_SHAPES], StringConverter::toString(physXFluidExtern->mFluidDesc.restitutionForStaticShapes), 12);

			if (physXFluidExtern->mFluidDesc.dynamicFrictionForStaticShapes != fluidDesc.dynamicFrictionForStaticShapes)
				serializer->writeLine(token[TOKEN_DYNAMIC_FRICTION_FOR_STATIC_SHAPES], StringConverter::toString(physXFluidExtern->mFluidDesc.dynamicFrictionForStaticShapes), 12);

			if (physXFluidExtern->mFluidDesc.staticFrictionForStaticShapes != fluidDesc.staticFrictionForStaticShapes)
				serializer->writeLine(token[TOKEN_STATIC_FRICTION_FOR_STATIC_SHAPES], StringConverter::toString(physXFluidExtern->mFluidDesc.staticFrictionForStaticShapes), 12);

			if (physXFluidExtern->mFluidDesc.attractionForStaticShapes != fluidDesc.attractionForStaticShapes)
				serializer->writeLine(token[TOKEN_ATTRACTION_FOR_STATIC_SHAPES], StringConverter::toString(physXFluidExtern->mFluidDesc.attractionForStaticShapes), 12);

			//////////////////////////////////////////////////////////////////////////
			if (physXFluidExtern->mFluidDesc.restitutionForDynamicShapes != fluidDesc.restitutionForDynamicShapes)
				serializer->writeLine(token[TOKEN_RESTITUTION_FOR_DYNAMIC_SHAPES], StringConverter::toString(physXFluidExtern->mFluidDesc.restitutionForDynamicShapes), 12);

			if (physXFluidExtern->mFluidDesc.dynamicFrictionForDynamicShapes != fluidDesc.dynamicFrictionForDynamicShapes)
			serializer->writeLine(token[TOKEN_DYNAMIC_FRICTION_FOR_DYNAMIC_SHAPES], StringConverter::toString(physXFluidExtern->mFluidDesc.dynamicFrictionForDynamicShapes), 12);

			if (physXFluidExtern->mFluidDesc.staticFrictionForDynamicShapes != fluidDesc.staticFrictionForDynamicShapes)
				serializer->writeLine(token[TOKEN_STATIC_FRICTION_FOR_DYNAMIC_SHAPES], StringConverter::toString(physXFluidExtern->mFluidDesc.staticFrictionForDynamicShapes), 12);

			if (physXFluidExtern->mFluidDesc.attractionForDynamicShapes != fluidDesc.attractionForDynamicShapes)
			serializer->writeLine(token[TOKEN_ATTRACTION_FOR_DYNAMIC_SHAPES], StringConverter::toString(physXFluidExtern->mFluidDesc.attractionForDynamicShapes), 12);

			//////////////////////////////////////////////////////////////////////////
			if (physXFluidExtern->mFluidDesc.collisionResponseCoefficient != fluidDesc.collisionResponseCoefficient)
				serializer->writeLine(token[TOKEN_COLLISION_RESPONSE_COEFFICIENT], StringConverter::toString(physXFluidExtern->mFluidDesc.collisionResponseCoefficient), 12);

			if (physXFluidExtern->mFluidDesc.collisionGroup != fluidDesc.collisionGroup)
				serializer->writeLine(token[TOKEN_COLLISION_GROUP], StringConverter::toString(physXFluidExtern->mFluidDesc.collisionGroup), 12);

			if (physXFluidExtern->mFluidDesc.groupsMask.bits3 != fluidDesc.groupsMask.bits3 &&
				physXFluidExtern->mFluidDesc.groupsMask.bits2 != fluidDesc.groupsMask.bits2 && 
				physXFluidExtern->mFluidDesc.groupsMask.bits1 != fluidDesc.groupsMask.bits1 &&
				physXFluidExtern->mFluidDesc.groupsMask.bits0 != fluidDesc.groupsMask.bits0) 
					serializer->writeLine(token[TOKEN_GROUP_MASK], 
					StringConverter::toString(physXFluidExtern->mFluidDesc.groupsMask.bits3) + " " +
					StringConverter::toString(physXFluidExtern->mFluidDesc.groupsMask.bits2) + " " +
					StringConverter::toString(physXFluidExtern->mFluidDesc.groupsMask.bits1) + " " +
					StringConverter::toString(physXFluidExtern->mFluidDesc.groupsMask.bits0), 12);

			if (physXFluidExtern->mFluidDesc.simulationMethod != fluidDesc.simulationMethod) 
			{
				if (physXFluidExtern->mFluidDesc.simulationMethod == NX_F_SPH)
					serializer->writeLine(token[TOKEN_SIMULATION_METHOD], token[TOKEN_INTERCOLLISION], 12);
				else if (physXFluidExtern->mFluidDesc.simulationMethod == NX_F_NO_PARTICLE_INTERACTION)
					serializer->writeLine(token[TOKEN_SIMULATION_METHOD], token[TOKEN_NOINTERCOLLISION], 12);
				else if (physXFluidExtern->mFluidDesc.simulationMethod == NX_F_MIXED_MODE)
					serializer->writeLine(token[TOKEN_SIMULATION_METHOD], token[TOKEN_MIX_INTERCOLLISION], 12);
			}

			if (physXFluidExtern->mFluidDesc.collisionMethod != fluidDesc.collisionMethod) 
			{
				if (physXFluidExtern->mFluidDesc.collisionMethod == NX_F_STATIC)
					serializer->writeLine(token[TOKEN_COLLISION_METHOD], token[TOKEN_STATIC], 12);
				else if (physXFluidExtern->mFluidDesc.collisionMethod == NX_F_DYNAMIC)
					serializer->writeLine(token[TOKEN_COLLISION_METHOD], token[TOKEN_DYNAMIC], 12);
			}

			//////////////////////////////////////////////////////////////////////////
			if (physXFluidExtern->mFluidDesc.flags != fluidDesc.flags) 
			{
				// Open flags
				serializer->writeLine(token[TOKEN_FLAGS], 12);
				serializer->writeLine("{", 12);		

				// For each component see it if is different than the default value, if it is write it
				if ((physXFluidExtern->mFluidDesc.flags & NX_FF_VISUALIZATION) != (fluidDesc.flags & NX_FF_VISUALIZATION))
				if (physXFluidExtern->mFluidDesc.flags & NX_FF_VISUALIZATION) serializer->writeLine(token[TOKEN_FLAG_VISUALIZATION], "true", 16);
				else serializer->writeLine(token[TOKEN_FLAG_VISUALIZATION], "false", 16);

				if ((physXFluidExtern->mFluidDesc.flags & NX_FF_DISABLE_GRAVITY) != (fluidDesc.flags & NX_FF_DISABLE_GRAVITY) )
				if (physXFluidExtern->mFluidDesc.flags & NX_FF_DISABLE_GRAVITY) serializer->writeLine(token[TOKEN_FLAG_DISABLE_GRAVITY], "true", 16);
				else serializer->writeLine(token[TOKEN_FLAG_DISABLE_GRAVITY], "false", 16);

				if ((physXFluidExtern->mFluidDesc.flags & NX_FF_COLLISION_TWOWAY) != (fluidDesc.flags & NX_FF_COLLISION_TWOWAY) )
				if (physXFluidExtern->mFluidDesc.flags & NX_FF_COLLISION_TWOWAY ) serializer->writeLine(token[TOKEN_FLAG_COLLISION_TWOWAY], "true", 16);
				else serializer->writeLine(token[TOKEN_FLAG_COLLISION_TWOWAY], "false", 16);

				if ((physXFluidExtern->mFluidDesc.flags & NX_FF_ENABLED) != (fluidDesc.flags & NX_FF_ENABLED) )
					if (physXFluidExtern->mFluidDesc.flags & NX_FF_ENABLED ) serializer->writeLine(token[TOKEN_FLAG_FLUID_ENABLED], "true", 16);
					else serializer->writeLine(token[TOKEN_FLAG_FLUID_ENABLED], "false", 16);

				if ((physXFluidExtern->mFluidDesc.flags & NX_FF_HARDWARE) != (fluidDesc.flags & NX_FF_HARDWARE) )
				if (physXFluidExtern->mFluidDesc.flags & NX_FF_HARDWARE ) serializer->writeLine(token[TOKEN_FLAG_HARDWARE], "true", 16);
				else serializer->writeLine(token[TOKEN_FLAG_HARDWARE], "false", 16);

				if ((physXFluidExtern->mFluidDesc.flags & NX_FF_PRIORITY_MODE) != (fluidDesc.flags & NX_FF_PRIORITY_MODE) )
				if (physXFluidExtern->mFluidDesc.flags & NX_FF_PRIORITY_MODE ) serializer->writeLine(token[TOKEN_FLAG_PRIORITY_MODE], "true", 16);
				else serializer->writeLine(token[TOKEN_FLAG_PRIORITY_MODE], "false", 16);

				if ((physXFluidExtern->mFluidDesc.flags & NX_FF_PROJECT_TO_PLANE) != (fluidDesc.flags & NX_FF_PROJECT_TO_PLANE) )
				if (physXFluidExtern->mFluidDesc.flags & NX_FF_PROJECT_TO_PLANE ) serializer->writeLine(token[TOKEN_FLAG_PROJECT_TO_PLANE], "true", 16);
				else serializer->writeLine(token[TOKEN_FLAG_PROJECT_TO_PLANE], "false", 16);

				if ((physXFluidExtern->mFluidDesc.flags & NX_FF_FORCE_STRICT_COOKING_FORMAT) != (fluidDesc.flags & NX_FF_FORCE_STRICT_COOKING_FORMAT) )
				if (physXFluidExtern->mFluidDesc.flags & NX_FF_FORCE_STRICT_COOKING_FORMAT ) serializer->writeLine(token[TOKEN_FLAG_STRICT_COOKING_FORMAT], "true", 16);
				else serializer->writeLine(token[TOKEN_FLAG_STRICT_COOKING_FORMAT], "false", 16);

				// Close flags
				serializer->writeLine("}", 12);		
			}
			// End: Own attributes to write

			// Write the close bracket
			serializer->writeLine("}", 8);
		}

}
#endif //PU_PHYSICS_PHYSX