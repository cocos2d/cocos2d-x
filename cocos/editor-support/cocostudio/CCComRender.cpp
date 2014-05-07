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

#include "cocostudio/CCComRender.h"
#include "cocostudio/CocoStudio.h"

using namespace cocos2d;

namespace cocostudio {

IMPLEMENT_CLASS_COMPONENT_INFO(ComRender)
ComRender::ComRender(void)
: _render(nullptr)
{
    _name = "CCComRender";
}


ComRender::ComRender(cocos2d::Node *node, const char *comName)
{
    if (node != nullptr)
    {
        _render = node;
        _render->retain();
    }
    _name.assign(comName);
}

ComRender::~ComRender(void)
{
    CC_SAFE_RELEASE_NULL(_render);
}

void ComRender::onEnter()
{
    if (_owner != nullptr)
    {
        _owner->addChild(_render);
    }
}

void ComRender::onExit()
{
    if (_owner != nullptr)
    {
        _owner->removeChild(_render, true);
    }
}

cocos2d::Node* ComRender::getNode()
{
    return _render;
}

void ComRender::setNode(cocos2d::Node *node)
{
    if (_render != nullptr)
    {
        _render->release();
        _render = nullptr;
    }
    if (node != nullptr)
    {		
        _render = node;
        _render->retain();
    }
}


bool ComRender::serialize(void* r)
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
		const char *plist = DICTOOL->getStringValue_json(fileData, "plistFile");
		CC_BREAK_IF(file == nullptr && plist == nullptr);
		std::string filePath;
		std::string plistPath;
		if (file != nullptr)
		{
			filePath.assign(cocos2d::CCFileUtils::getInstance()->fullPathForFilename(file));
		}
		if (plist != nullptr)
		{
			plistPath.assign(cocos2d::CCFileUtils::getInstance()->fullPathForFilename(plist));
		}
		int resType = DICTOOL->getIntValue_json(fileData, "resourceType", -1);
		if (resType == 0)
		{
			if (strcmp(className, "CCSprite") == 0 && filePath.find(".png") != std::string::npos)
			{
				_render = Sprite::create(filePath.c_str());
                _render->retain();
			}
			else if(strcmp(className, "CCTMXTiledMap") == 0 && filePath.find(".tmx") != std::string::npos)
			{
				_render = TMXTiledMap::create(filePath.c_str());
                _render->retain();
			}
			else if(strcmp(className, "CCParticleSystemQuad") == 0 && filePath.find(".plist") != std::string::npos)
			{
				_render = ParticleSystemQuad::create(filePath.c_str());
                _render->setPosition(Vector2(0.0f, 0.0f));
                _render->retain();
			}
			else if(strcmp(className, "CCArmature") == 0)
			{
				std::string reDir = filePath;
				std::string file_path = "";
				size_t pos = reDir.find_last_of('/');
				if (pos != std::string::npos)
				{
					file_path = reDir.substr(0, pos+1);
				}
				rapidjson::Document doc;
				if(!readJson(filePath.c_str(), doc))
				{
					log("read json file[%s] error!\n", filePath.c_str());
					continue;
				}
				const rapidjson::Value &subData = DICTOOL->getDictionaryFromArray_json(doc, "armature_data", 0);
				const char *name = DICTOOL->getStringValue_json(subData, "name");
				ArmatureDataManager::getInstance()->addArmatureFileInfo(filePath.c_str());
				Armature *pAr = Armature::create(name);
				_render = pAr;
                _render->retain();
				const char *actionName = DICTOOL->getStringValue_json(*v, "selectedactionname");
				if (actionName != nullptr && pAr->getAnimation() != nullptr)
				{
					pAr->getAnimation()->play(actionName);
				}
			}
			else if(strcmp(className, "GUIComponent") == 0)
			{
				cocos2d::ui::Widget* widget = GUIReader::getInstance()->widgetFromJsonFile(filePath.c_str());
                _render = widget;
                _render->retain();
			}
			else
			{
				CC_BREAK_IF(true);
			}
		}
		else if (resType == 1)
		{
			if (strcmp(className, "CCSprite") == 0)
			{
				std::string strPngFile = plistPath;
				std::string::size_type pos = strPngFile.find(".plist");
				if (pos  == strPngFile.npos)
				{
					continue;
				}
				strPngFile.replace(pos, strPngFile.length(), ".png");
				SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistPath.c_str(), strPngFile.c_str());
				_render = Sprite::createWithSpriteFrameName(filePath.c_str());
                _render->retain();
			}
			else
			{
				CC_BREAK_IF(true);
			}
		}
		else
		{
			CC_BREAK_IF(true);
		}
		bRet = true;
	} while (0);

	return bRet;
}

ComRender* ComRender::create(void)
{
    ComRender * ret = new ComRender();
    if (ret != nullptr && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
	return ret;
}

ComRender* ComRender::create(cocos2d::Node *node, const char *comName)
{
    ComRender * ret = new ComRender(node, comName);
    if (ret != nullptr && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
        return ret;
}

bool ComRender::readJson(const std::string &fileName, rapidjson::Document &doc)
{
    bool ret = false;
    do {
        std::string contentStr = FileUtils::getInstance()->getStringFromFile(fileName);
        doc.Parse<0>(contentStr.c_str());
        CC_BREAK_IF(doc.HasParseError());
        ret = true;
    } while (0);
    return ret;
}

}
