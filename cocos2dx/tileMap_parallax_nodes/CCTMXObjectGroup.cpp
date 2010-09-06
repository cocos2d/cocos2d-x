/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
		:m_sGroupName("")
		,m_tPositionOffset(CGPointZero)
	{
		m_pObjects = new NSArray<StringToStringDictionary*>();
		m_pProperties = new StringToStringDictionary();
	}
	CCTMXObjectGroup::~CCTMXObjectGroup()
	{
		CCLOGINFO( "cocos2d: deallocing.");
		CCX_SAFE_RELEASE(m_pObjects);
		CCX_SAFE_RELEASE(m_pProperties);
	}
	StringToStringDictionary * CCTMXObjectGroup::objectNamed(const char *objectName)
	{
		if (m_pObjects && m_pObjects->count() > 0)
		{
			NSArray<StringToStringDictionary*>::NSMutableArrayIterator it;
			for (it = m_pObjects->begin(); it != m_pObjects->end(); ++it)
			{
				NSString *name = (*it)->objectForKey("name");
				if (name && name->m_sString == objectName)
				{
					return *it;
				}
			}
		}
		// object not found
		return NULL;	
	}
	NSString *CCTMXObjectGroup::propertyNamed(const char* propertyName)
	{
		return m_pProperties->objectForKey(propertyName);
	}

	StringToStringDictionary * CCTMXObjectGroup::getProperties()
	{ 
		return m_pProperties;
	}
	void CCTMXObjectGroup::setProperties(StringToStringDictionary * properties)
	{
		CCX_SAFE_RELEASE(m_pProperties);
		m_pProperties = properties;
		CCX_SAFE_RETAIN(m_pProperties);
	}
	NSArray<StringToStringDictionary*> *CCTMXObjectGroup::getObjects()
	{
		return m_pObjects;
	}
	void CCTMXObjectGroup::setObjects(NSArray<StringToStringDictionary*> * objects)
	{
		CCX_SAFE_RELEASE(m_pObjects);
		m_pObjects = objects;
		CCX_SAFE_RETAIN(m_pObjects);
	}

}// namespace cocos2d