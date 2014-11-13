/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_DYNAMIC_ATTRIBUTE_FACTORY_H__
#define __PU_DYNAMIC_ATTRIBUTE_FACTORY_H__

#include "ParticleUniverseDynamicAttribute.h"
#include "ParticleUniverseDynamicAttributeTokens.h"
#include "ParticleUniverseScriptDeserializer.h"

namespace ParticleUniverse
{
	/** This factory class is responsible for creating a DynamicAttribute object.
    */
	class _ParticleUniverseExport DynamicAttributeFactory : public ScriptWriter, public FactoryAlloc
	{
	    public:

			DynamicAttributeFactory(void) {};
	        virtual ~DynamicAttributeFactory(void) {};

			/** 
	        */
			template <class T>
			T* createDynamicAttribute(void)
			{
				return PU_NEW_T(T, MEMCATEGORY_SCENE_OBJECTS)();
			};


			/** 
	        */
			DynamicAttribute* cloneDynamicAttribute(DynamicAttribute* dynamicAttribute)
			{
				if (dynamicAttribute)
				{
					switch(dynamicAttribute->getType())
					{
						case DynamicAttribute::DAT_FIXED:
						{
							DynamicAttributeFixed* dynAttr = createDynamicAttribute<DynamicAttributeFixed>();
							dynamicAttribute->copyAttributesTo(dynAttr);
							return dynAttr;	
						}
						break;

						case DynamicAttribute::DAT_RANDOM:
						{
							DynamicAttributeRandom* dynAttr = createDynamicAttribute<DynamicAttributeRandom>();
							dynamicAttribute->copyAttributesTo(dynAttr);
							return dynAttr;
						}
						break;

						case DynamicAttribute::DAT_CURVED:
						{
							DynamicAttributeCurved* dynAttr = createDynamicAttribute<DynamicAttributeCurved>();
							dynamicAttribute->copyAttributesTo(dynAttr);
							return dynAttr;
						}
						break;

						case DynamicAttribute::DAT_OSCILLATE:
						{
							DynamicAttributeOscillate* dynAttr = createDynamicAttribute<DynamicAttributeOscillate>();
							dynamicAttribute->copyAttributesTo(dynAttr);
							return dynAttr;
						}
						break;
					}
				}

				return 0;
			}
			
			/** Delete a DynamicAttribute
	        */
			void destroyDynamicAttribute (DynamicAttribute* dynamicAttribute)
			{
				PU_DELETE_T(dynamicAttribute, DynamicAttribute, MEMCATEGORY_SCENE_OBJECTS);
			};

			/** See ScriptWriter */
			virtual void write(ParticleScriptSerializer* serializer, const IElement* element)
			{
				// Delegate to mDynamicAttributeWriter
				mDynamicAttributeWriter.write(serializer, element);
			}

			/** Returns the default value of a DynamicAttribute. Not for general use. */
			Real _getDefaultValue(const DynamicAttribute* dynAttribute)
			{
				if (!dynAttribute)
					return 0;

				switch (dynAttribute->getType())
				{
					case DynamicAttribute::DAT_FIXED:
						{
							const DynamicAttributeFixed* dynFixed = static_cast<const DynamicAttributeFixed*>(dynAttribute);
							DynamicAttributeFixed d(*dynFixed); // Needed to get rid of the const, because the getValue function is not a const!
							return d.getValue();
						}
						break;

					case DynamicAttribute::DAT_RANDOM:
						{
							const DynamicAttributeRandom* dynRandom = static_cast<const DynamicAttributeRandom*>(dynAttribute);
							DynamicAttributeRandom d(*dynRandom); // Needed to get rid of the const
							return d.getValue();
						}
						break;

					case DynamicAttribute::DAT_CURVED:
						{
							const DynamicAttributeCurved* dynCurved = static_cast<const DynamicAttributeCurved*>(dynAttribute);
							DynamicAttributeCurved d(*dynCurved); // Needed to get rid of the const
							return d.getValue();
						}
						break;

					case DynamicAttribute::DAT_OSCILLATE:
						{
							const DynamicAttributeOscillate* dynOscillate = static_cast<const DynamicAttributeOscillate*>(dynAttribute);
							DynamicAttributeOscillate d(*dynOscillate); // Needed to get rid of the const
							return d.getValue();
						}
				}

				return 0; // Take 0 as the default
			}

		protected:
			DynamicAttributeWriter mDynamicAttributeWriter;
	};

}
#endif
