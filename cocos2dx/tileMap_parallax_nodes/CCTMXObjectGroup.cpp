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
#include "CCTMXObjectGroup.h"
#include "ccMacros.h"
namespace cocos2d {

	//implementation CCTMXObjectGroup

	CCTMXObjectGroup::CCTMXObjectGroup()
        :m_tPositionOffset(CCPointZero)
		,m_sGroupName("")		
	{
		m_pObjects = new CCMutableArray<CCStringToStringDictionary*>();
		m_pProperties = new CCStringToStringDictionary();
	}
	CCTMXObjectGroup::~CCTMXObjectGroup()
	{
		CCLOGINFO( "cocos2d: deallocing.");
		CC_SAFE_RELEASE(m_pObjects);
		CC_SAFE_RELEASE(m_pProperties);
	}
	CCStringToStringDictionary * CCTMXObjectGroup::objectNamed(const char *objectName)
	{
		if (m_pObjects && m_pObjects->count() > 0)
		{
			CCMutableArray<CCStringToStringDictionary*>::CCMutableArrayIterator it;
			for (it = m_pObjects->begin(); it != m_pObjects->end(); ++it)
			{
				CCString *name = (*it)->objectForKey(std::string("name"));
				if (name && name->m_sString == objectName)
				{
					return *it;
				}
			}
		}
		// object not found
		return NULL;	
	}
	CCString *CCTMXObjectGroup::propertyNamed(const char* propertyName)
	{
		return m_pProperties->objectForKey(std::string(propertyName));
	}

	CCStringToStringDictionary * CCTMXObjectGroup::getProperties()
	{ 
		return m_pProperties;
	}
	void CCTMXObjectGroup::setProperties(CCStringToStringDictionary * properties)
	{
		CC_SAFE_RETAIN(properties);
		CC_SAFE_RELEASE(m_pProperties);
		m_pProperties = properties;
	}
	CCMutableArray<CCStringToStringDictionary*> *CCTMXObjectGroup::getObjects()
	{
		return m_pObjects;
	}
	void CCTMXObjectGroup::setObjects(CCMutableArray<CCStringToStringDictionary*> * objects)
	{
		CC_SAFE_RETAIN(objects);
		CC_SAFE_RELEASE(m_pObjects);
		m_pObjects = objects;
	}

}// namespace cocos2d