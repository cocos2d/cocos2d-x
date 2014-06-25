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
        CC_BREAK_IF(r == NULL);
		SerData *pSerData = (SerData *)(r);
        const rapidjson::Value *v = pSerData->_rData;
		stExpCocoNode *pCocoNode = pSerData->_cocoNode;
		const char *pClassName = NULL;
		const char *pComName = NULL;
		const char *pFile = NULL;
		const char *pPlist = NULL;
		std::string strFilePath;
		std::string strPlistPath;
		int nResType = 0;
		if (v != NULL)
		{
			pClassName = DICTOOL->getStringValue_json(*v, "classname");
			CC_BREAK_IF(pClassName == NULL);
			pComName = DICTOOL->getStringValue_json(*v, "name");
			const rapidjson::Value &fileData = DICTOOL->getSubDictionary_json(*v, "fileData");
			CC_BREAK_IF(!DICTOOL->checkObjectExist_json(fileData));
			pFile = DICTOOL->getStringValue_json(fileData, "path");
			pPlist = DICTOOL->getStringValue_json(fileData, "plistFile");
			CC_BREAK_IF(pFile == NULL && pPlist == NULL);
			nResType = DICTOOL->getIntValue_json(fileData, "resourceType", -1);
		}
		else if(pCocoNode != NULL)
		{
			pClassName = pCocoNode[1].GetValue();
			CC_BREAK_IF(pClassName == NULL);
			pComName = pCocoNode[2].GetValue();
			stExpCocoNode *pfileData = pCocoNode[4].GetChildArray();
			CC_BREAK_IF(!pfileData);
			pFile = pfileData[0].GetValue();
			pPlist = pfileData[1].GetValue();
			CC_BREAK_IF(pFile == NULL && pPlist == NULL);
			nResType = atoi(pfileData[2].GetValue());
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
			strFilePath.assign(cocos2d::FileUtils::getInstance()->fullPathForFilename(pFile));
		}
		if (pPlist != NULL)
		{
			strPlistPath.assign(cocos2d::FileUtils::getInstance()->fullPathForFilename(pPlist));
		}
		if (nResType == 0)
		{
			if (strcmp(pClassName, "CCSprite") == 0 && (strFilePath.find(".png") != strFilePath.npos || strFilePath.find(".pvr.ccz") != strFilePath.npos))
			{
				_render = CCSprite::create(strFilePath.c_str());
				_render->retain();
                
                bRet = true;
			}
			else if(strcmp(pClassName, "CCTMXTiledMap") == 0 && strFilePath.find(".tmx") != strFilePath.npos)
			{
				_render = CCTMXTiledMap::create(strFilePath.c_str());
				_render->retain();
                
                bRet = true;
			}
			else if(strcmp(pClassName, "CCParticleSystemQuad") == 0 && strFilePath.find(".plist") != strFilePath.npos)
			{
				_render = CCParticleSystemQuad::create(strFilePath.c_str());
				_render->setPosition(Point(0.0f, 0.0f));
				_render->retain();
                
                bRet = true;
			}
			else if(strcmp(pClassName, "CCArmature") == 0)
			{
				std::string file_extension = strFilePath;
				size_t pos = strFilePath.find_last_of('.');
				if (pos != std::string::npos)
				{
					file_extension = strFilePath.substr(pos, strFilePath.length());
					std::transform(file_extension.begin(),file_extension.end(), file_extension.begin(), (int(*)(int))toupper);
				}
				if (file_extension == ".JSON" || file_extension == ".EXPORTJSON")
				{
					rapidjson::Document doc;
					if(!readJson(strFilePath.c_str(), doc))
					{
						log("read json file[%s] error!\n", strFilePath.c_str());
						continue;
					}
					const rapidjson::Value &subData = DICTOOL->getDictionaryFromArray_json(doc, "armature_data", 0);
					const char *name = DICTOOL->getStringValue_json(subData, "name");
					ArmatureDataManager::getInstance()->addArmatureFileInfo(strFilePath.c_str());
					Armature *pAr = Armature::create(name);
					_render = pAr;
					_render->retain();
					const char *actionName = NULL;
					if (pCocoNode != NULL)
					{
						actionName = pCocoNode[6].GetValue();//DICTOOL->getStringValue_json(*v, "selectedactionname");
					}
					else
					{
						actionName = DICTOOL->getStringValue_json(*v, "selectedactionname");
					}
					if (actionName != NULL && pAr->getAnimation() != NULL)
					{
						pAr->getAnimation()->play(actionName);
					}
                    bRet = true;
				}
				else if (file_extension == ".CSB")
				{
					ssize_t size = 0;
					unsigned char *pBytes = NULL;
					std::string binaryFilePath = FileUtils::getInstance()->fullPathForFilename(strFilePath.c_str());
					pBytes = cocos2d::FileUtils::getInstance()->getFileData(binaryFilePath.c_str(), "rb", &size);
					CC_BREAK_IF(pBytes == NULL || strcmp((char*)pBytes, "") == 0);
					CocoLoader tCocoLoader;
					if (tCocoLoader.ReadCocoBinBuff((char*)pBytes))
					{
						stExpCocoNode *tpRootCocoNode = tCocoLoader.GetRootCocoNode();
						rapidjson::Type tType = tpRootCocoNode->GetType(&tCocoLoader);
						if (rapidjson::kObjectType  == tType)
						{
                            int count = tpRootCocoNode->GetChildNum();
                            stExpCocoNode *tpChildArray = tpRootCocoNode->GetChildArray();
                            for (int i = 0; i < count; ++i)
                            {
                                std::string key = tpChildArray[i].GetName(&tCocoLoader);
                                const char *str = tpChildArray[i].GetValue();
                                if (key.compare("armature_data") == 0)
                                {
                                    int length = tpChildArray[i].GetChildNum();
                                    stExpCocoNode *armature_dataArray = tpChildArray[i].GetChildArray();
                                    if (length < 1)
                                    {
                                        continue;
                                    }
                                    
                                    length = armature_dataArray[0].GetChildNum();
                                    stExpCocoNode *armature_data = armature_dataArray[0].GetChildArray();
                                    for (int j = 0; j < length; ++j)
                                    {
                                        std::string key1 = armature_data[j].GetName(&tCocoLoader);
                                        const char *str1 = armature_data[j].GetValue();
                                        if (key.compare("name") == 0)
                                        {
                                            if (str1 != NULL)
                                            {
                                                ArmatureDataManager::getInstance()->addArmatureFileInfo(strFilePath.c_str());
                                                Armature *pAr = CCArmature::create(str1);
                                                _render = pAr;
                                                _render->retain();
                                                const char *actionName = NULL;
                                                if (pCocoNode != NULL)
                                                {
                                                    actionName = pCocoNode[6].GetValue();
                                                }
                                                else
                                                {
                                                    actionName = DICTOOL->getStringValue_json(*v, "selectedactionname");
                                                }
                                                if (actionName != NULL && pAr->getAnimation() != NULL)
                                                {
                                                    pAr->getAnimation()->play(actionName);
                                                }
                                                bRet = true;
                                            }
                                        }
                                    }
                                }
                            }
						}
					}
                    else
                    {
                        continue;
                    }
				}
                else
                {
                    continue;
                }
			}
			else if(strcmp(pClassName, "GUIComponent") == 0)
			{
				std::string file_extension = strFilePath;
				size_t pos = strFilePath.find_last_of('.');
				if (pos != std::string::npos)
				{
					file_extension = strFilePath.substr(pos, strFilePath.length());
					std::transform(file_extension.begin(),file_extension.end(), file_extension.begin(), (int(*)(int))toupper);
				}
				if (file_extension == ".JSON" || file_extension == ".EXPORTJSON")
				{
                    cocos2d::ui::Widget* widget = GUIReader::getInstance()->widgetFromJsonFile(strFilePath.c_str());
                    _render = widget;
                    _render->retain();
                    
                    bRet = true;
				}
				else if (file_extension == ".CSB")
				{
                    cocos2d::ui::Widget* widget = GUIReader::getInstance()->widgetFromBinaryFile(strFilePath.c_str());
                    _render = widget;
                    _render->retain();
                    
                    bRet = true;
				}
			}
			else
			{
				CC_BREAK_IF(true);
			}
		}
		else if (nResType == 1)
		{
			if (strcmp(pClassName, "CCSprite") == 0)
			{
				std::string strPngFile = strPlistPath;
				std::string::size_type pos = strPngFile.find(".plist");
				if (pos  == strPngFile.npos)
				{
					continue;
				}
				strPngFile.replace(pos, strPngFile.length(), ".png");
				SpriteFrameCache::getInstance()->addSpriteFramesWithFile(strPlistPath.c_str(), strPngFile.c_str());
				_render = CCSprite::createWithSpriteFrameName(strFilePath.c_str());
				_render->retain();
                
                bRet = true;
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
