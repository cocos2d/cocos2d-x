/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "CCComAttribute.h"
#include "cocos2d.h"

NS_CC_EXT_BEGIN

CCComAttribute::CCComAttribute(void)
: m_pJsonDict(NULL),
 m_pAttributes(NULL)
{
    m_strName = "ComAttribute";
}

CCComAttribute::CCComAttribute(const char *pszFileName)
: m_pJsonDict(NULL)
{
	  m_strName = "ComAttribute";
	  if (pszFileName != NULL)
	  {
		  m_strFileName.assign(pszFileName);
	  }
}

CCComAttribute::~CCComAttribute(void)
{
    CC_SAFE_DELETE(m_pJsonDict);
	CC_SAFE_RELEASE(m_pAttributes);
}

bool CCComAttribute::init()
{
	m_pAttributes = CCDictionary::create();
	m_pAttributes->retain();

	unsigned long size = 0;
	const char* pData = 0;
	pData = (char*)(cocos2d::CCFileUtils::sharedFileUtils()->getFileData(m_strFileName.c_str(), "r", &size));
	if(pData != NULL && strcmp(pData, "") != 0)
	{
		m_pJsonDict= new cs::CSJsonDictionary();
		m_pJsonDict->initWithDescription(pData);
	}

    return true;
}

CCComAttribute* CCComAttribute::create(void)
{
    CCComAttribute * pRet = new CCComAttribute();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

CCComAttribute* CCComAttribute::create(const char *pszFileName)
{
	CCComAttribute *pRet = NULL;
	do 
	{
		CC_BREAK_IF(pszFileName == NULL);
		pRet = new CCComAttribute(pszFileName);
		if (pRet && pRet->init())
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_DELETE(pRet);
		}
	} while (0);
	
    return pRet;
}


void CCComAttribute::setInt(const char *key, int value)
{
    CCAssert(key != NULL, "Argument must be non-nil"); 
    m_pAttributes->setObject(CCInteger::create(value), key);
}

void CCComAttribute::setDouble(const char *key, double value)
{
    CCAssert(key != NULL, "Argument must be non-nil"); 
    m_pAttributes->setObject(CCDouble::create(value), key);
}

void CCComAttribute::setFloat(const char *key, float value)
{
    CCAssert(key != NULL, "Argument must be non-nil"); 
    m_pAttributes->setObject(CCFloat::create(value), key);
}

void CCComAttribute::setBool(const char *key, bool value)
{
    CCAssert(key != NULL, "Argument must be non-nil"); 
    m_pAttributes->setObject(CCBool::create(value), key);
}

void CCComAttribute::setCString(const char *key, const char *value)
{
    CCAssert(key != NULL, "Argument must be non-nil"); 
    m_pAttributes->setObject(CCString::create(value), key);
}

void CCComAttribute::setObject(const char *key, CCObject *value)
{
    CCAssert(key != NULL, "Argument must be non-nil"); 
    m_pAttributes->setObject(value, key);
}

int CCComAttribute::getInt(const char *key) const
{
    CCObject *ret = m_pAttributes->objectForKey(key);
	if( ret )
    {
		if( CCInteger *obj=dynamic_cast<CCInteger*>(ret) )
			return obj->getValue();

		CCAssert(false, "Key found, type is not integer");
	}

	// XXX: Should it throw an exception ?
	CCLOG("Key not found: '%s'", key );
	return 0;
}

double CCComAttribute::getDouble(const char *key) const
{
    CCObject *ret = m_pAttributes->objectForKey(key);
	if( ret )
    {
		if( CCDouble *obj=dynamic_cast<CCDouble*>(ret) )
			return obj->getValue();

		CCAssert(false, "Key found, type is not double");
	}

	// XXX: Should it throw an exception ?
	CCLOG("Key not found: '%s'", key );
	return 0.0;
}

float CCComAttribute::getFloat(const char *key) const
{
    CCObject *ret = m_pAttributes->objectForKey(key);
	if( ret )
    {
		if( CCFloat *obj=dynamic_cast<CCFloat*>(ret) )
			return obj->getValue();

		CCAssert(false, "Key found, type is not float");
	}

	// XXX: Should it throw an exception ?
	CCLOG("Key not found: '%s'", key );
	return 0.0;
}

bool CCComAttribute::getBool(const char *key) const
{
    CCObject *ret = m_pAttributes->objectForKey(key);
	if( ret )
    {
		if( CCBool *boolobj=dynamic_cast<CCBool*>(ret) )
			return boolobj->getValue();
		if( CCString *strobj=dynamic_cast<CCString*>(ret) )
			return strobj->boolValue();
		CCAssert(false, "Key found, type is not Bool");
	}

	// XXX: Should it throw an exception ?
	CCLOG("Key not found: '%s'", key );
	return false;
}

const char* CCComAttribute::getCString(const char *key) const
{
   CCObject *ret = m_pAttributes->objectForKey(key);
	if( ret )
    {
		if( CCString *str=dynamic_cast<CCString*>(ret) )
			return str->getCString();

		CCAssert(false, "Key found, type is not CString");
	}

	// XXX: Should it throw an exception ?
	CCLOG("Key not found: '%s'", key );
	return NULL;
}

CCObject* CCComAttribute::getObject(const char *key) const
{
    return m_pAttributes->objectForKey(key);
}
 
cs::CSJsonDictionary* CCComAttribute::getDict()
{
	return m_pJsonDict;
}

NS_CC_EXT_END
