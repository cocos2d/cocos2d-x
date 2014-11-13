/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

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
	#include "Externs/ParticleUniversePhysXActorExternTokens.h"
	#include "Externs/ParticleUniversePhysXActorExtern.h"

	namespace ParticleUniverse
	{
		//-----------------------------------------------------------------------
		bool PhysXActorExternTranslator::translateChildProperty(ScriptCompiler* compiler, const AbstractNodePtr &node)
		{
			PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>(node.get());
			Extern* ex = any_cast<Extern*>(prop->parent->context);
			PhysXActorExtern* externObject = static_cast<PhysXActorExtern*>(ex);

			if (prop->name == token[TOKEN_ACTOR_COLLISION_GROUP])
			{
				// Property: actor_group
				if (passValidateProperty(compiler, prop, token[TOKEN_ACTOR_COLLISION_GROUP], VAL_UINT))
				{
					uint val = 0;
					if(getUInt(prop->values.front(), &val))
					{
						externObject->setCollisionGroup(val);
						return true;
					}
				}
			}
			else if (prop->name == token[TOKEN_PHYSX_ACTOR_COLLISION_GROUP])
			{
				// Property: physx_actor_group (deprecated and replaced by 'actor_group')
				if (passValidateProperty(compiler, prop, token[TOKEN_PHYSX_ACTOR_COLLISION_GROUP], VAL_UINT))
				{
					uint val = 0;
					if(getUInt(prop->values.front(), &val))
					{
						externObject->setCollisionGroup(val);
						return true;
					}
				}
			}

			return false;
		}
		//-----------------------------------------------------------------------
		bool PhysXActorExternTranslator::translateChildObject(ScriptCompiler* compiler, const AbstractNodePtr &node)
		{
			ObjectAbstractNode* child = reinterpret_cast<ObjectAbstractNode*>(node.get());
			Extern* ex = any_cast<Extern*>(child->parent->context);
			PhysXActorExtern* externObject = static_cast<PhysXActorExtern*>(ex);

			if (child->cls == token[TOKEN_SHAPE_TYPE] || child->cls == token[TOKEN_PHYSX_SHAPE_TYPE])
			{
				// Property: physx_shape (deprecated) / shape
				PhysXShapeTranslator physXShapeTranslator;
				PhysicsShapeDesc* physicsShapeDesc = externObject->mPhysicsShapeDesc;
				if (child->name == token[TOKEN_PHYSX_BOX])
				{
					physicsShapeDesc->mPhysicsShapeType = ST_BOX;
				}
				else if (child->name == token[TOKEN_PHYSX_SPHERE])
				{
					physicsShapeDesc->mPhysicsShapeType = ST_SPHERE;
				}
				else if (child->name == token[TOKEN_PHYSX_CAPSULE])
				{
					physicsShapeDesc->mPhysicsShapeType = ST_CAPSULE;
				}
				child->context = Any(physicsShapeDesc);
				physXShapeTranslator.translate(compiler, node);
				return true;
			}

			return false;
		}
		//-----------------------------------------------------------------------
		void PhysXShapeTranslator::translate(ScriptCompiler* compiler, const AbstractNodePtr &node)
		{
			ObjectAbstractNode* obj = reinterpret_cast<ObjectAbstractNode*>(node.get());
			if (obj->parent->context.isEmpty())
			{
				return;
			}

			PhysicsShapeDesc* physicsShapeDesc = any_cast<PhysicsShapeDesc*>(obj->context);

			// Run through properties
			for(AbstractNodeList::iterator i = obj->children.begin(); i != obj->children.end(); ++i)
			{
				if((*i)->type == ANT_PROPERTY)
				{
					PropertyAbstractNode* prop = reinterpret_cast<PropertyAbstractNode*>((*i).get());
					if (prop->name == token[TOKEN_SHAPE_COLLISION_GROUP])
					{
						// Property: shape_group
						if (passValidateProperty(compiler, prop, token[TOKEN_SHAPE_COLLISION_GROUP], VAL_UINT))
						{
							uint val = 0;
							if(getUInt(prop->values.front(), &val))
							{
								physicsShapeDesc->mCollisionGroup = val;
							}
						}
					}
					else if (prop->name == token[TOKEN_PHYSX_SHAPE_COLLISION_GROUP])
					{
						// Property: physx_shape_group (deprecated and replaced by 'shape_group')
						if (passValidateProperty(compiler, prop, token[TOKEN_PHYSX_SHAPE_COLLISION_GROUP], VAL_UINT))
						{
							uint val = 0;
							if(getUInt(prop->values.front(), &val))
							{
								physicsShapeDesc->mCollisionGroup = val;
							}
						}
					}
					else if (prop->name == token[TOKEN_GROUP_MASK])
					{
						// Property: group_mask
						if (passValidateProperty(compiler, prop, token[TOKEN_GROUP_MASK], VAL_VECTOR4))
						{
							Vector4 val;
							if(getVector4(prop->values.begin(), prop->values.end(), &val))
							{
								physicsShapeDesc->mGroupMask.bits0 = (uint32)val.x;
								physicsShapeDesc->mGroupMask.bits1 = (uint32)val.y;
								physicsShapeDesc->mGroupMask.bits2 = (uint32)val.z;
								physicsShapeDesc->mGroupMask.bits3 = (uint32)val.w;
							}
						}
					}
					else if (prop->name == token[TOKEN_PHYSX_GROUP_MASK])
					{
						// Property: physx_group_mask (deprecated and replaced by 'group_mask')
						if (passValidateProperty(compiler, prop, token[TOKEN_PHYSX_GROUP_MASK], VAL_VECTOR4))
						{
							Vector4 val;
							if(getVector4(prop->values.begin(), prop->values.end(), &val))
							{
								physicsShapeDesc->mGroupMask.bits0 = (uint32)val.x;
								physicsShapeDesc->mGroupMask.bits1 = (uint32)val.y;
								physicsShapeDesc->mGroupMask.bits2 = (uint32)val.z;
								physicsShapeDesc->mGroupMask.bits3 = (uint32)val.w;
							}
						}
					}
					else if (prop->name == token[TOKEN_ANGULAR_VELOCITY])
					{
						// Property: angular_velocity
						if (passValidateProperty(compiler, prop, token[TOKEN_ANGULAR_VELOCITY], VAL_VECTOR3))
						{
							Vector3 val;
							if(getVector3(prop->values.begin(), prop->values.end(), &val))
							{
								physicsShapeDesc->mAngularVelocity = val;
							}
						}
					}
					else if (prop->name == token[TOKEN_PHYSX_ANGULAR_VELOCITY])
					{
						// Property: physx_angular_velocity (deprecated and replaced by 'angular_velocity')
						if (passValidateProperty(compiler, prop, token[TOKEN_PHYSX_ANGULAR_VELOCITY], VAL_VECTOR3))
						{
							Vector3 val;
							if(getVector3(prop->values.begin(), prop->values.end(), &val))
							{
								physicsShapeDesc->mAngularVelocity = val;
							}
						}
					}
					else if (prop->name == token[TOKEN_ANGULAR_DAMPING])
					{
						// Property: angular_damping
						if (passValidateProperty(compiler, prop, token[TOKEN_ANGULAR_DAMPING], VAL_REAL))
						{
							Real val = 0.0f;
							if(getReal(prop->values.front(), &val))
							{
								physicsShapeDesc->mAngularDamping = val;
							}
						}
					}
					else if (prop->name == token[TOKEN_PHYSX_ANGULAR_DAMPING])
					{
						// Property: physx_angular_damping (deprecated and replaced by 'angular_damping')
						if (passValidateProperty(compiler, prop, token[TOKEN_PHYSX_ANGULAR_DAMPING], VAL_REAL))
						{
							Real val = 0.0f;
							if(getReal(prop->values.front(), &val))
							{
								physicsShapeDesc->mAngularDamping = val;
							}
						}
					}
					else if (prop->name == token[TOKEN_MATERIAL_INDEX])
					{
						// Property: material_index
						if (passValidateProperty(compiler, prop, token[TOKEN_MATERIAL_INDEX], VAL_UINT))
						{
							uint val = 0;
							if(getUInt(prop->values.front(), &val))
							{
								physicsShapeDesc->mMaterialIndex = val;
							}
						}
					}
					else if (prop->name == token[TOKEN_PHYSX_MATERIAL_INDEX])
					{
						// Property: physx_material_index (deprecated and replaced by 'material_index')
						if (passValidateProperty(compiler, prop, token[TOKEN_PHYSX_MATERIAL_INDEX], VAL_UINT))
						{
							uint val = 0;
							if(getUInt(prop->values.front(), &val))
							{
								physicsShapeDesc->mMaterialIndex = val;
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
		void PhysXActorExternWriter::write(ParticleScriptSerializer* serializer, const IElement* element)
		{
			// Cast the element to a PhysXActorExtern
			const Extern* externObject = static_cast<const Extern*>(element);
			const PhysXActorExtern* physXActorExtern = static_cast<const PhysXActorExtern*>(externObject);
			serializer->writeLine(token[TOKEN_EXTERN], externObject->getExternType(), externObject->getName(), 8);
			serializer->writeLine("{", 8);
	
			// Write base attributes
			ExternWriter::write(serializer, element);
	
			// Write own attributes
			if (physXActorExtern->getCollisionGroup() != 0) serializer->writeLine(
				token[TOKEN_ACTOR_COLLISION_GROUP], StringConverter::toString(physXActorExtern->getCollisionGroup()), 12);
			PhysicsShapeDesc* physicsShapeDesc = physXActorExtern->mPhysicsShapeDesc;
			if (physicsShapeDesc)
			{
				switch (physicsShapeDesc->mPhysicsShapeType)
				{
					case ST_BOX:
					{
						serializer->writeLine(token[TOKEN_PHYSX_SHAPE_TYPE], token[TOKEN_PHYSX_BOX], 12);
					}
					break;

					case ST_SPHERE:
					{
						serializer->writeLine(token[TOKEN_PHYSX_SHAPE_TYPE], token[TOKEN_PHYSX_SPHERE], 12);
					}
					break;

					case ST_CAPSULE:
					{
						serializer->writeLine(token[TOKEN_PHYSX_SHAPE_TYPE], token[TOKEN_PHYSX_CAPSULE], 12);
					}
					break;
				}

				serializer->writeLine("{", 12);
				if (physicsShapeDesc->mCollisionGroup != 0) serializer->writeLine(
					token[TOKEN_SHAPE_COLLISION_GROUP], StringConverter::toString(physicsShapeDesc->mCollisionGroup), 16);
				if (physicsShapeDesc->mAngularVelocity != Vector3::ZERO) serializer->writeLine(
					token[TOKEN_ANGULAR_VELOCITY], StringConverter::toString(physicsShapeDesc->mAngularVelocity), 16);
				if (physicsShapeDesc->mAngularDamping != 0.5f) serializer->writeLine(
					token[TOKEN_ANGULAR_DAMPING], StringConverter::toString(physicsShapeDesc->mAngularDamping), 16);
				if (physicsShapeDesc->mMaterialIndex != 0) serializer->writeLine(
					token[TOKEN_MATERIAL_INDEX], StringConverter::toString(physicsShapeDesc->mMaterialIndex), 16);
				if (physicsShapeDesc->mGroupMask != GroupsMask(0, 0, 0, 0)) serializer->writeLine(
					token[TOKEN_GROUP_MASK], 
					StringConverter::toString(physicsShapeDesc->mGroupMask.bits0) + " " +
					StringConverter::toString(physicsShapeDesc->mGroupMask.bits1) + " " +
					StringConverter::toString(physicsShapeDesc->mGroupMask.bits2) + " " +
					StringConverter::toString(physicsShapeDesc->mGroupMask.bits3), 16);
	
				// Write the close bracket
				serializer->writeLine("}", 12);
			}
	
			// Write the close bracket
			serializer->writeLine("}", 8);
		}

}
#endif //PU_PHYSICS_PHYSX