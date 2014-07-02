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
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

IMPLEMENT_CLASS_COMPONENT_INFO(CCComAttribute)
CCComAttribute::CCComAttribute(void)
: _dict(NULL)
{
    m_strName = "CCComAttribute";
}

CCComAttribute::~CCComAttribute(void)
{
    CC_SAFE_RELEASE(_dict);
}

bool CCComAttribute::init()
{
    _dict = CCDictionary::create();
	_dict->retain();
    return true;
}

void CCComAttribute::setInt(const char *key, int value)
{
    _dict->setObject(CCInteger::create(value), key);
}

void CCComAttribute::setFloat(const char *key, float value)
{
    _dict->setObject(CCFloat::create(value), key);
}

void CCComAttribute::setBool(const char *key, bool value)
{
    _dict->setObject(CCBool::create(value), key);
}

void CCComAttribute::setCString(const char *key, const char *value)
{
    _dict->setObject(CCString::create(value), key);
}

int CCComAttribute::getInt(const char *key, int def) const
{
    CCObject *ret = _dict->objectForKey(key);
	if(ret != NULL)
    {
		if( CCInteger *obj=dynamic_cast<CCInteger*>(ret) )
        {
			return obj->getValue();
        }
	}
    else
    {
        if (DICTOOL->checkObjectExist_json(_doc, key))
        {
            return DICTOOL->getIntValue_json(_doc, key);
        }
    }
    return def;
}

float CCComAttribute::getFloat(const char *key, float def) const
{
    CCObject *ret = _dict->objectForKey(key);
	if(ret != NULL)
    {
		
		if( CCFloat *obj=dynamic_cast<CCFloat*>(ret) )
        {
			return obj->getValue();
        }
	}
    else
    {
        if (DICTOOL->checkObjectExist_json(_doc, key))
        {
            return DICTOOL->getFloatValue_json(_doc, key);
        }
    }
    return def;
}

bool CCComAttribute::getBool(const char *key, bool def) const
{
    CCObject *ret = _dict->objectForKey(key);
	if(ret != NULL)
    {
		if( CCBool *obj = dynamic_cast<CCBool*>(ret) )
        {
			return obj->getValue();
        }
	}
    else
    {
        if (DICTOOL->checkObjectExist_json(_doc, key))
        {
            return DICTOOL->getBooleanValue_json(_doc, key);
        }
    }
    return def;
}

const char* CCComAttribute::getCString(const char *key, const char *def) const
{
    CCObject *ret = _dict->objectForKey(key);
    if (ret != NULL)
    {
        if( CCString *obj = dynamic_cast<CCString*>(ret) )
        {
			return obj->getCString();
        }
    }
    else
    {
        if (DICTOOL->checkObjectExist_json(_doc, key))
        {
            return DICTOOL->getStringValue_json(_doc, key);
        }
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

bool CCComAttribute::serialize(void* r)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(r == NULL);
		SerData *pSerData = (SerData *)(r);
		const rapidjson::Value *v = pSerData->prData;
		stExpCocoNode *pCocoNode = pSerData->pCocoNode;
		CocoLoader *pCocoLoader = pSerData->pCocoLoader;
		const char *pClassName = NULL;
		const char *pComName = NULL;
		const char *pFile = NULL;
		std::string strFilePath;
		int nResType = 0;
		if (v != NULL)
		{
			pClassName = DICTOOL->getStringValue_json(*v, "classname");
			CC_BREAK_IF(pClassName == NULL);
			pComName = DICTOOL->getStringValue_json(*v, "name");
			const rapidjson::Value &fileData = DICTOOL->getSubDictionary_json(*v, "fileData");
			CC_BREAK_IF(!DICTOOL->checkObjectExist_json(fileData));
			pFile = DICTOOL->getStringValue_json(fileData, "path");
			CC_BREAK_IF(pFile == NULL);
			nResType = DICTOOL->getIntValue_json(fileData, "resourceType", -1);
			CC_BREAK_IF(nResType != 0);
		}
		else if (pCocoNode != NULL)
		{
			pClassName = pCocoNode[1].GetValue(pCocoLoader);
			CC_BREAK_IF(pClassName == NULL);
			pComName = pCocoNode[2].GetValue(pCocoLoader);
			stExpCocoNode *pfileData = pCocoNode[3].GetChildArray(pCocoLoader);
			CC_BREAK_IF(!pfileData);
			pFile = pfileData[0].GetValue(pCocoLoader);
			CC_BREAK_IF(pFile == NULL);
			nResType = atoi(pfileData[2].GetValue(pCocoLoader));
			CC_BREAK_IF(nResType != 0);
			
		}
		if (pComName != NULL)
		{
			setName(pComName);
		}
		else
		{
			setName(pClassName);
		}
		if (pFile != NULL)
		{
			strFilePath.assign(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(pFile));
		}
		if (parse(strFilePath.c_str()))
		{
            bRet = true;
		}

	}while (0);
	return bRet;
}

bool CCComAttribute::parse(const std::string &jsonPath)
{
    bool bRet = false;
    unsigned long size = 0;
    unsigned char *pBytes = NULL;
    do {
          pBytes = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(jsonPath.c_str(), "r", &size);
          CC_BREAK_IF(pBytes == NULL || strcmp((char*)pBytes, "") == 0);
          std::string load_str((const char*)pBytes, size);
          CC_SAFE_DELETE_ARRAY(pBytes);
          _doc.Parse<0>(load_str.c_str());
          CC_BREAK_IF(_doc.HasParseError());
          bRet = true;
        } while (0);
    return bRet;
}

NS_CC_EXT_END
