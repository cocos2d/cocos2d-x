/*
-----------------------------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2012 Henry van Merode

Usage of this program is licensed under the terms of the Particle Universe Commercial License.
You can find a copy of the Commercial License in the Particle Universe package.
-----------------------------------------------------------------------------------------------
*/

#ifndef __PU_CONTEXT_H__
#define __PU_CONTEXT_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseSection.h"
#include "ParticleUniverseLogManager.h"
#include "ParticleUniverseException.h"

namespace ParticleUniverse
{
	// String representation of the Particle Universe contexts. Numeric values are used to keep the string small.
	const static String ALIAS					= "1";
	const static String SYSTEM				= "2";
	const static String TECHNIQUE				= "3";
	const static String RENDERER				= "4";
	const static String EMITTER				= "5";
	const static String AFFECTOR				= "6";
	const static String OBSERVER				= "7";
	const static String HANDLER				= "8";
	const static String BEHAVIOUR				= "9";
	const static String EXTERN				= "10";
	const static String DYNAMIC_ATTRIBUTE		= "11";
	const static String DEPENDENCY			= "12";
	const static String INNER_CONTEXT			= "13"; // To be used for deeper sections

	/** The Context class is used to manage the sections of a particle universe script.
	@remarks
		Each script consists of sections, levels with sublevels and subsublevels, etc. The Context 
		keeps track of each section and during parsing it is clear to which section the script parses 
		is pointing. The Context is used to store crucial data of each section.

		Note, that Context is not used for parsing scripts anymore, but it is still used in writing scripts.
	*/
	class _ParticleUniverseExport Context
	{
		protected:
			typedef vector<Section*> ContextStack;
			ContextStack mContextStack;

			/** This is the last processed section, which is still available for a 'higher' section
			*/

			Section mPreviousProcessedSection;

			/** 
			*/
			Section* _getCurrentSection(void)
			{
				if (!mContextStack.empty())
					return mContextStack.back();
				else
					return 0;
			}

			/** 
			*/
			Section* _getParentSection(void)
			{
				if (mContextStack.size() > 1)
				{
					ContextStack::iterator it = mContextStack.end();
					--it;
					--it;
					return *it;
				}
				else
					return 0;
			}

		public:
			Context(void) : attributeToken(0)
			{
				mPreviousProcessedSection.sectionName = StringUtil::BLANK;
				mPreviousProcessedSection.element = 0;
				mPreviousProcessedSection.elementName = StringUtil::BLANK;
			};
			virtual ~Context(void) {};
			
			/** attributeToken is needed to temporary set the last attribute value of the parsed script.
			*/
			IToken* attributeToken;

			/** 
			*/
			void beginSection(
				const String& sectionName, 
				IElement* element = 0,
				const String& elementName = StringUtil::BLANK)
			{
				// Add a new section to the stack
				Section* section = PU_NEW_T(Section, MEMCATEGORY_SCRIPTING)();
				section->sectionName = sectionName;
				section->elementName = elementName;
				section->element = element;
				mContextStack.push_back(section);
			}
			
			/** 
			*/
			void endSection(void)
			{
				Section* section = _getCurrentSection();

				// Set the values in the mPreviousProcessedSection
				if (section)
				{
					mPreviousProcessedSection.sectionName = section->sectionName;
					mPreviousProcessedSection.element = section->element;
					mPreviousProcessedSection.elementName = section->elementName;
				}
				
				if (!mContextStack.empty())
					mContextStack.pop_back();
				
				if (section)
					PU_DELETE_T(section, Section, MEMCATEGORY_SCRIPTING);
			}
			
			/** 
			*/
			const String& getCurrentSectionName(void)
			{
				Section* section = _getCurrentSection();
				if (section)
					return section->sectionName;
				else
					return StringUtil::BLANK;
			}

			/** 
			*/
			const String& getPreviousSectionName(void)
			{
				return mPreviousProcessedSection.sectionName;
			}

			/** 
			*/
			const String& getParentSectionName(void)
			{
				Section* parent = _getParentSection();
				if (parent)
					return parent->sectionName;
				else
					return StringUtil::BLANK;
			}

			/** 
			*/
			IElement* getCurrentSectionElement(void)
			{
				Section* section = _getCurrentSection();
				if (section)
					return section->element;
				else
					return 0;
			}

			/** 
			*/
			IElement* getPreviousSectionElement(void)
			{
				return mPreviousProcessedSection.element;
			}

			/** 
			*/
			IElement* getParentSectionElement(void)
			{
				Section* parent = _getParentSection();
				if (parent)
					return parent->element;
				else
					return 0;
			}

			/** 
			*/
			const String& getCurrentSectionElementName(void)
			{
				Section* section = _getCurrentSection();
				if (section)
					return section->elementName;
				else
					return StringUtil::BLANK;
			}

			/** 
			*/
			const String& getPreviousSectionElementName(void)
			{
				return mPreviousProcessedSection.elementName;
			}

			/** 
			*/
			const String& getParentSectionElementName(void)
			{
				Section* parent = _getParentSection();
				if (parent)
					return parent->elementName;
				else
					return StringUtil::BLANK;
			}

			/** 
			*/
			IElement* getSectionElement(const String& sName)
			{
				if (mContextStack.empty())
					return 0;

				ContextStack::iterator it;
				for (it = mContextStack.begin(); it != mContextStack.end(); ++it)
				{
					if ((*it)->sectionName == sName)
					{
						return (*it)->element;
					}
				}
				return 0;
			}

			/** 
			*/
			void validateCurrentSectionName(const String& sectionName, 
				const String& calledFromFunction = StringUtil::BLANK)
			{
				Section* section = _getCurrentSection();
				if (!section || section->sectionName != sectionName)
				{
					EXCEPT(Exception::ERR_INVALIDPARAMS, "Invalid section, expected "  + section->sectionName + 
						" but validated section is " + sectionName, calledFromFunction);
				}
			}
	};

}
#endif
