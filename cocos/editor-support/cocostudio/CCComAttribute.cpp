/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "cocostudio/CCComAttribute.h"
#include "platform/CCFileUtils.h"

using namespace cocos2d;

namespace cocostudio {

IMPLEMENT_CLASS_COMPONENT_INFO(ComAttribute)
ComAttribute::ComAttribute(void)
{
    _name = "CCComAttribute";
}

ComAttribute::~ComAttribute(void)
{
    _dict.clear();
}

bool ComAttribute::init()
{
    return true;
}

void ComAttribute::setInt(const std::string& key, int value)
{
    _dict[key] = cocos2d::Value(value);
}

void ComAttribute::setFloat(const std::string& key, float value)
{
    _dict[key] = cocos2d::Value(value);
}

void ComAttribute::setBool(const std::string& key, bool value)
{
    _dict[key] = cocos2d::Value(value);
}

void ComAttribute::setString(const std::string& key, const std::string& value)
{
    _dict[key] = cocos2d::Value(value);
}

int ComAttribute::getInt(const std::string& key, int def) const
{
    if (_dict.find(key) != _dict.end())
    {
        const cocos2d::Value& v = _dict.at(key);
        return v.asInt();
    }
   
    if (!DICTOOL->checkObjectExist_json(_doc, key.c_str()))
    {
        return def;
    }
  
    return DICTOOL->getIntValue_json(_doc, key.c_str());
}

float ComAttribute::getFloat(const std::string& key, float def) const
{
    if (_dict.find(key) != _dict.end())
    {
        const cocos2d::Value& v = _dict.at(key);
        return v.asFloat();
    }

    if (!DICTOOL->checkObjectExist_json(_doc, key.c_str()))
    {
        return def;
    }
    return DICTOOL->getFloatValue_json(_doc, key.c_str());
}

bool ComAttribute::getBool(const std::string& key, bool def) const
{
    if (_dict.find(key) != _dict.end())
    {
        const cocos2d::Value& v = _dict.at(key);
        return v.asBool();
    }
    
    if (!DICTOOL->checkObjectExist_json(_doc, key.c_str()))
    {
        return def;
    }
  
    return DICTOOL->getBooleanValue_json(_doc, key.c_str());
}

std::string ComAttribute::getString(const std::string& key, const std::string& def) const
{
    if (_dict.find(key) != _dict.end())
    {
        const cocos2d::Value& v = _dict.at(key);
        return v.asString();
    }
    
    if (!DICTOOL->checkObjectExist_json(_doc, key.c_str()))
    {
        return def;
    }
  
    return DICTOOL->getStringValue_json(_doc, key.c_str());
}

ComAttribute* ComAttribute::create(void)
{
	ComAttribute * pRet = new ComAttribute();
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

bool ComAttribute::serialize(void* r) 
{
    bool bRet = false;
	do 
	{
		CC_BREAK_IF(r == nullptr);
		rapidjson::Value *v = (rapidjson::Value *)r;
		const char *className = DICTOOL->getStringValue_json(*v, "classname");
		CC_BREAK_IF(className == nullptr);
		const char *comName = DICTOOL->getStringValue_json(*v, "name");
		if (comName != nullptr)
		{
			setName(comName);
		}
		else
		{
			setName(className);
		}
		const rapidjson::Value &fileData = DICTOOL->getSubDictionary_json(*v, "fileData");
		CC_BREAK_IF(!DICTOOL->checkObjectExist_json(fileData));
		const char *file = DICTOOL->getStringValue_json(fileData, "path");
		CC_BREAK_IF(file == nullptr);
		std::string filePath;
		if (file != nullptr)
		{
			filePath.assign(cocos2d::FileUtils::getInstance()->fullPathForFilename(file));
		}
		int resType = DICTOOL->getIntValue_json(fileData, "resourceType", -1);
		CC_BREAK_IF(resType != 0);
        parse(filePath.c_str());
		bRet = true;
	} while (0);

	return bRet;
}

bool ComAttribute::parse(const std::string &jsonFile)
{
    bool ret = false;
    do {
        std::string contentStr = FileUtils::getInstance()->getStringFromFile(jsonFile);
        _doc.Parse<0>(contentStr.c_str());
        CC_BREAK_IF(_doc.HasParseError());
        ret = true;
    } while (0);
    return ret;
}

}
