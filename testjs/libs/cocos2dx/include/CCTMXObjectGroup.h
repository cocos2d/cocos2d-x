/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2010      Neophit
Copyright (c) 2010      Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef __CCTMX_OBJECT_GROUP_H__
#define __CCTMX_OBJECT_GROUP_H__

#include "CCGeometry.h"
#include "CCString.h"
#include "CCMutableArray.h"
#include "CCMutableDictionary.h"

namespace cocos2d {

	/** @brief CCTMXObjectGroup represents the TMX object group.
	@since v0.99.0
	*/
	class CC_DLL CCTMXObjectGroup : public CCObject
	{
		/** offset position of child objects */
		CC_SYNTHESIZE_PASS_BY_REF(CCPoint, m_tPositionOffset, PositionOffset);
		/** list of properties stored in a dictionary */
		CC_PROPERTY(CCStringToStringDictionary*, m_pProperties, Properties);
		/** array of the objects */
		CC_PROPERTY(CCMutableArray<CCStringToStringDictionary*>*, m_pObjects, Objects);
	public:
		CCTMXObjectGroup();
		virtual ~CCTMXObjectGroup();

		inline const char* getGroupName(){ return m_sGroupName.c_str(); }
		inline void setGroupName(const char *groupName){ m_sGroupName = groupName; }

		/** return the value for the specific property name */
		CCString *propertyNamed(const char* propertyName);

		/** return the dictionary for the specific object name.
		It will return the 1st object found on the array for the given name.
		*/
		CCStringToStringDictionary *objectNamed(const char *objectName);
	protected:	
		/** name of the group */
		std::string m_sGroupName;
	};

}// namespace cocos2d
#endif //__CCTMX_OBJECT_GROUP_H__