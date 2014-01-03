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
#include "../Json/DictionaryHelper.h"

NS_CC_EXT_BEGIN

IMPLEMENT_CLASS_COMPONENT_INFO(CCComAttribute)
CCComAttribute::CCComAttribute(void)
: m_pDict(NULL)
{
    m_strName = "CCComAttribute";
}

CCComAttribute::~CCComAttribute(void)
{
    CC_SAFE_RELEASE(m_pDict);
}

bool CCComAttribute::init()
{
    m_pDict = CCDictionary::create();
	m_pDict->retain();
    return true;
}

void CCComAttribute::setInt(const char *key, int value)
{
    m_pDict->setObject(CCInteger::create(value), key);
}

void CCComAttribute::setFloat(const char *key, float value)
{
    m_pDict->setObject(CCFloat::create(value), key);
}

void CCComAttribute::setBool(const char *key, bool value)
{
    m_pDict->setObject(CCBool::create(value), key);
}

void CCComAttribute::setCString(const char *key, const char *value)
{
    m_pDict->setObject(CCString::create(value), key);
}


int CCComAttribute::getInt(const char *key, int def) const
{
    CCObject *ret = m_pDict->objectForKey(key);
	if(ret)
    {
		
		if( CCInteger *obj=dynamic_cast<CCInteger*>(ret) )
			return obj->getValue();
	}
    return def;
}

float CCComAttribute::getFloat(const char *key, float def) const
{
    CCObject *ret = m_pDict->objectForKey(key);
	if(ret)
    {
		
		if( CCFloat *obj=dynamic_cast<CCFloat*>(ret) )
			return obj->getValue();
	}
    return def;
}

bool CCComAttribute::getBool(const char *key, bool def) const
{
    CCObject *ret = m_pDict->objectForKey(key);
	if(ret) {
		
		if( CCBool *obj = dynamic_cast<CCBool*>(ret) )
			return obj->getValue();
	}
    return def;
}

const char* CCComAttribute::getCString(const char *key, const char *def) const
{
   CCObject *ret = m_pDict->objectForKey(key);
	if(ret) {
		
		if( CCString *obj = dynamic_cast<CCString*>(ret) )
			return obj->getCString();
	}
    return def;
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

void CCComAttribute::setFile(const std::string &jsonName)
{
	m_strJsonFile = jsonName;
}
std::string CCComAttribute::getFile() const
{
	return m_strJsonFile;
}

bool CCComAttribute::serialize(void* r)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(r == NULL);
		rapidjson::Value *v = (rapidjson::Value *)r;
		const char *pClassName = DICTOOL->getStringValue_json(*v, "classname");
		CC_BREAK_IF(pClassName == NULL);
		const char *pComName = DICTOOL->getStringValue_json(*v, "name");
		if (pComName != NULL)
		{
			setName(pComName);
		}
		else
		{
			setName(pClassName);
		}
		const rapidjson::Value &fileData = DICTOOL->getSubDictionary_json(*v, "fileData");
		CC_BREAK_IF(!DICTOOL->checkObjectExist_json(fileData));
		int nResType = nResType = DICTOOL->getIntValue_json(fileData, "resourceType", -1);
		CC_BREAK_IF(nResType != 0);
		const char *pFile = DICTOOL->getStringValue_json(fileData, "path");
		CC_BREAK_IF(pFile == NULL);
		std::string strFilePath;
		if (pFile != NULL)
		{
			strFilePath.assign(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(pFile));
		}
		setFile(strFilePath);
		bRet = true;
	} while (0);

	return bRet;
}

NS_CC_EXT_END
