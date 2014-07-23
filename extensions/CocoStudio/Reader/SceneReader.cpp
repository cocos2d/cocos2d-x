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

#include "SceneReader.h"
#include <algorithm>
#include "SimpleAudioEngine.h"
#include "../Trigger/ObjectFactory.h"

NS_CC_EXT_BEGIN

SceneReader* SceneReader::_sharedReader = NULL;
CCObject*  SceneReader::_pListener = NULL;
SEL_CallFuncOD  SceneReader::_pfnSelector = NULL;

SceneReader::SceneReader()
:_pNode(NULL)
,_eAttachComponent(ATTACH_EMPTY_NODE)
{
    ObjectFactory::getInstance()->registerType(CREATE_CLASS_COMPONENT_INFO(CCComAttribute));
    ObjectFactory::getInstance()->registerType(CREATE_CLASS_COMPONENT_INFO(CCComRender));
    ObjectFactory::getInstance()->registerType(CREATE_CLASS_COMPONENT_INFO(CCComAudio));
	ObjectFactory::getInstance()->registerType(CREATE_CLASS_COMPONENT_INFO(CCComController));
}

SceneReader::~SceneReader()
{
}

const char* SceneReader::sceneReaderVersion()
{
	return "1.2.0.0";
}

cocos2d::CCNode* SceneReader::createNodeWithSceneFile(const char* pszFileName, AttachComponentType eAttachComponent /*= ATTACH_EMPTY_NODE*/)
{
	std::string reDir = pszFileName;
	std::string file_extension = "";
	size_t pos = reDir.find_last_of('.');
	if (pos != std::string::npos)
	{
		file_extension = reDir.substr(pos, reDir.length());
		std::transform(file_extension.begin(),file_extension.end(), file_extension.begin(), (int(*)(int))toupper);
	}
	if (file_extension == ".JSON")
	{
		rapidjson::Document jsonDict;
		do {
			CC_BREAK_IF(!readJson(pszFileName, jsonDict));
			_eAttachComponent = eAttachComponent;
			_pNode = createObject(jsonDict, NULL, eAttachComponent);
			TriggerMng::getInstance()->parse(jsonDict);
		} while (0);
		return _pNode;
	}
	else if (file_extension == ".CSB")
	{
		unsigned long size = 0;
		unsigned char *pBytes = NULL;
		do {
			CC_BREAK_IF(pszFileName == NULL);
			std::string binaryFilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFileName);
			pBytes = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(binaryFilePath.c_str(), "rb", &size);
			CC_BREAK_IF(pBytes == NULL || strcmp((char*)pBytes, "") == 0);
			CocoLoader tCocoLoader;
			if (tCocoLoader.ReadCocoBinBuff((char*)pBytes))
			{
				stExpCocoNode *tpRootCocoNode = tCocoLoader.GetRootCocoNode();
				rapidjson::Type tType = tpRootCocoNode->GetType(&tCocoLoader);
				if (rapidjson::kObjectType  == tType)
				{
					stExpCocoNode *tpChildArray = tpRootCocoNode->GetChildArray(&tCocoLoader);
					CC_BREAK_IF(tpRootCocoNode->GetChildNum() == 0);
					_pNode = CCNode::create();
					int  nCount = 0;
					std::vector<CCComponent*> _vecComs;
					CCComRender *pRender = NULL;
					std::string key = tpChildArray[15].GetName(&tCocoLoader);
					if (key == "components")
					{
						nCount = tpChildArray[15].GetChildNum();
					}
					stExpCocoNode *pComponents = tpChildArray[15].GetChildArray(&tCocoLoader);
					
					for (int i = 0; i < nCount; i++)
					{
						stExpCocoNode *subDict = pComponents[i].GetChildArray(&tCocoLoader);
						if (subDict == NULL)
						{
							continue;
						}
						std::string key = subDict[1].GetName(&tCocoLoader);
						const char *comName = subDict[1].GetValue(&tCocoLoader);//DICTOOL->getStringValue_json(subDict, "classname");
						CCComponent *pCom = NULL;
						if (key == "classname" && comName != NULL)
						{
							pCom = ObjectFactory::getInstance()->createComponent(comName);
						}
						CCLOG("classname = %s", comName);
                        SerData *data = new SerData();
						if (pCom != NULL)
						{
							data->prData = NULL;
							data->pCocoNode = subDict;
							data->pCocoLoader = &tCocoLoader;
							if (pCom->serialize(data))
							{
								CCComRender *pTRender = dynamic_cast<CCComRender*>(pCom);
								if (pTRender != NULL)
								{
									pRender = pTRender;
								}
								else
								{
									_vecComs.push_back(pCom);
								}
							}
							else
							{
								CC_SAFE_RELEASE_NULL(pCom);
							}
						}
						if (_pListener && _pfnSelector)
						{
							(_pListener->*_pfnSelector)(pCom, data);
						}
                        CC_SAFE_DELETE(data);
					}
                    

					setPropertyFromJsonDict(&tCocoLoader, tpRootCocoNode, _pNode);
					for (std::vector<CCComponent*>::iterator iter = _vecComs.begin(); iter != _vecComs.end(); ++iter)
					{
						_pNode->addComponent(*iter);
					}

					stExpCocoNode *pGameObjects = tpChildArray[11].GetChildArray(&tCocoLoader);
					int length = tpChildArray[11].GetChildNum();
					for (int i = 0; i < length; ++i)
					{
						createObject(&tCocoLoader, &pGameObjects[i], _pNode, eAttachComponent);
					}
					TriggerMng::getInstance()->parse(&tCocoLoader, tpChildArray);
				}
				
			}
		}while (0);
		return _pNode;
	}
	else
	{
		CCLog("read json file extension [%s] error!\n", pszFileName);
	}
	return NULL;
}


bool SceneReader::readJson(const char *pszFileName, rapidjson::Document &doc)
{
	bool bRet = false;
	unsigned long size = 0;
	unsigned char *pBytes = NULL;
	do {
		CC_BREAK_IF(pszFileName == NULL);
		std::string jsonpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFileName);
		pBytes = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(jsonpath.c_str(), "r", &size);
		CC_BREAK_IF(pBytes == NULL || strcmp((char*)pBytes, "") == 0);
		std::string load_str((const char*)pBytes, size);
		CC_SAFE_DELETE_ARRAY(pBytes);
		doc.Parse<0>(load_str.c_str());
		CC_BREAK_IF(doc.HasParseError());
		bRet = true;
	} while (0);
	return bRet;
}

CCNode* SceneReader::nodeByTag(CCNode *pParent, int nTag)
{		
	if (pParent == NULL)
	{
		return NULL;
	}
	CCNode *_retNode = NULL;
	CCArray *pChildren = pParent->getChildren();
	if(pChildren && pChildren->count() > 0)
	{
		CCObject* child;
		CCARRAY_FOREACH(pChildren, child)
		{
			CCNode* pNode = (CCNode*)child;
			if(pNode && pNode->getTag() == nTag)
			{
				_retNode =  pNode;
				break;
			}
			else
			{
				_retNode = nodeByTag(pNode, nTag);
				if (_retNode != NULL)
				{
					break;
				}

			}
		}
	}
	return _retNode;
}

CCNode* SceneReader::createObject(const rapidjson::Value &root, cocos2d::CCNode* parent, AttachComponentType eAttachComponent /*= ATTACH_EMPTY_NODE*/)
{
	const char *className = DICTOOL->getStringValue_json(root, "classname");
	if(strcmp(className, "CCNode") == 0)
	{
		CCNode* gb = NULL;
		if(NULL == parent)
		{
			gb = CCNode::create();
		}

        std::vector<CCComponent*> _vecComs;
        CCComRender *pRender = NULL;
		int count = DICTOOL->getArrayCount_json(root, "components");
		for (int i = 0; i < count; i++)
		{
			const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(root, "components", i);
			if (!DICTOOL->checkObjectExist_json(subDict))
			{
				break;
			}
			const char *comName = DICTOOL->getStringValue_json(subDict, "classname");
			CCComponent *pCom = ObjectFactory::getInstance()->createComponent(comName);
            SerData *pData = new SerData();
			if (pCom != NULL)
			{
				pData->prData = &subDict;
				pData->pCocoNode = NULL;
				pData->pCocoLoader = NULL;
				if (pCom->serialize(pData))
				{
                    CCComRender *pTRender = dynamic_cast<CCComRender*>(pCom);
                    if (pTRender != NULL)
                    {
                        pRender = pTRender;
                    }
                    else
                    {
                        _vecComs.push_back(pCom);
                    }
                }
                else
                {
                    CC_SAFE_RELEASE_NULL(pCom);
                }
            }
			
			if (_pListener && _pfnSelector)
			{
				(_pListener->*_pfnSelector)(pCom, pData);
			}
            CC_SAFE_DELETE(pData);
		}
        

        if (parent != NULL)
        {
            if (pRender == NULL || eAttachComponent == ATTACH_EMPTY_NODE)
            {
                gb = CCNode::create();
                if (pRender != NULL)
                {
                    _vecComs.push_back(pRender);
                }
            }
            else
            {
                gb = pRender->getNode();
                gb->retain();
                pRender->setNode(NULL);
                CC_SAFE_RELEASE_NULL(pRender);
            }
            parent->addChild(gb);
        }
        setPropertyFromJsonDict(root, gb);
        for (std::vector<CCComponent*>::iterator iter = _vecComs.begin(); iter != _vecComs.end(); ++iter)
        {
            gb->addComponent(*iter);
        }
        
		int length = DICTOOL->getArrayCount_json(root, "gameobjects");
		for (int i = 0; i < length; ++i)
		{
			const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(root, "gameobjects", i);
			if (!DICTOOL->checkObjectExist_json(subDict))
			{
				break;
			}
			createObject(subDict, gb, eAttachComponent);
		}
		return gb;
	}
	return NULL;
}

cocos2d::CCNode* SceneReader::createObject(CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode, cocos2d::CCNode* parent, AttachComponentType eAttachComponent)
{
	const char *className = NULL;
	stExpCocoNode *pNodeArray = pCocoNode->GetChildArray(pCocoLoader);
	std::string Key = pNodeArray[1].GetName(pCocoLoader);
	if (Key == "classname")
	{
		className = pNodeArray[1].GetValue(pCocoLoader);
	}
	if(strcmp(className, "CCNode") == 0)
	{
		CCNode* gb = NULL;
		std::vector<CCComponent*> _vecComs;
		CCComRender *pRender = NULL;
		int count = 0;
		std::string key = pNodeArray[13].GetName(pCocoLoader);
		if (key == "components")
		{
			count = pNodeArray[13].GetChildNum();
		}
		stExpCocoNode *pComponents = pNodeArray[13].GetChildArray(pCocoLoader);
		
		for (int i = 0; i < count; ++i)
		{
			stExpCocoNode *subDict = pComponents[i].GetChildArray(pCocoLoader);
			if (subDict == NULL)
			{
				continue;
			}
			std::string key = subDict[1].GetName(pCocoLoader);
			const char *comName = subDict[1].GetValue(pCocoLoader);//DICTOOL->getStringValue_json(subDict, "classname");
			CCComponent *pCom = NULL;
			if (key == "classname" && comName != NULL)
			{
				pCom = ObjectFactory::getInstance()->createComponent(comName);
			}
			CCLOG("classname = %s", comName);
            SerData *data = new SerData();
			if (pCom != NULL)
			{
				data->prData = NULL;
				data->pCocoNode = subDict;
				data->pCocoLoader = pCocoLoader;
				if (pCom->serialize(data))
				{
					CCComRender *pTRender = dynamic_cast<CCComRender*>(pCom);
					if (pTRender != NULL)
					{
						pRender = pTRender;
					}
					else
					{
						_vecComs.push_back(pCom);
					}
				}
				else
				{
					CC_SAFE_RELEASE_NULL(pCom);
				}
			}
			if (_pListener && _pfnSelector)
			{
				(_pListener->*_pfnSelector)(pCom, data);
			}
            CC_SAFE_DELETE(data);
		}

		if (parent != NULL)
		{
			if (pRender == NULL || eAttachComponent == ATTACH_EMPTY_NODE)
			{
				gb = CCNode::create();
				if (pRender != NULL)
				{
					_vecComs.push_back(pRender);
				}
			}
			else
			{
				gb = pRender->getNode();
				gb->retain();
				pRender->setNode(NULL);
				CC_SAFE_RELEASE_NULL(pRender);
			}
			parent->addChild(gb);
		}
		setPropertyFromJsonDict(pCocoLoader, pCocoNode, gb);
		for (std::vector<CCComponent*>::iterator iter = _vecComs.begin(); iter != _vecComs.end(); ++iter)
		{
			gb->addComponent(*iter);
		}

		stExpCocoNode *pGameObjects = pNodeArray[12].GetChildArray(pCocoLoader);
		if (pGameObjects != NULL)
		{
			int length = pNodeArray[12].GetChildNum();
			for (int i = 0; i < length; ++i)
			{
				createObject(pCocoLoader, &pGameObjects[i], gb, eAttachComponent);
			}
		}
		return gb;
	}
	return NULL;
}


void SceneReader::setTarget(CCObject *rec, SEL_CallFuncOD selector)
{
	_pListener = rec;
	_pfnSelector = selector;
}

CCNode* SceneReader::getNodeByTag(int nTag)
{
	if (_pNode == NULL)
	{
		return NULL;
	}
	if (_pNode->getTag() == nTag)
	{
		return _pNode;
	}
	return nodeByTag(_pNode, nTag);
}

void SceneReader::setPropertyFromJsonDict(const rapidjson::Value &root, cocos2d::CCNode *node)
{
	float x = DICTOOL->getFloatValue_json(root, "x");
	float y = DICTOOL->getFloatValue_json(root, "y");

	node->setPosition(ccp(x, y));
    
	bool bVisible = DICTOOL->getIntValue_json(root, "visible", 1) != 0? true:false;
	node->setVisible(bVisible);

	int nTag = DICTOOL->getIntValue_json(root, "objecttag", -1);
	node->setTag(nTag);

	int nZorder = DICTOOL->getIntValue_json(root, "zorder");
	node->setZOrder(nZorder);

	float fScaleX = DICTOOL->getFloatValue_json(root, "scalex", 1.0);
	float fScaleY = DICTOOL->getFloatValue_json(root, "scaley", 1.0);
	node->setScaleX(fScaleX);
	node->setScaleY(fScaleY);

	float fRotationZ = DICTOOL->getFloatValue_json(root, "rotation"); 
	node->setRotation(fRotationZ);
}

void SceneReader::setPropertyFromJsonDict(CocoLoader *pCocoLoader, stExpCocoNode *pCocoNode, cocos2d::CCNode *node)
{
	stExpCocoNode *stChildArray = pCocoNode->GetChildArray(pCocoLoader);
	float x = 0.0f, y = 0.0f, fScaleX = 1.0f, fScaleY = 1.0f, fRotationZ = 1.0f;
	bool bVisible = false;
	int nTag = 0, nZorder = -1;

	for (int i = 0; i < pCocoNode->GetChildNum(); ++i) 
	{
		std::string key = stChildArray[i].GetName(pCocoLoader);
		std::string value = stChildArray[i].GetValue(pCocoLoader);
		
		if (key == "x") 
		{
			x = atof(value.c_str());
			node->setPositionX(x);
		}
		else if (key == "y")
		{
			y = atof(value.c_str());
			node->setPositionY(y);
		}
		else if (key == "visible")
		{
			bVisible = (bool)atoi(value.c_str());
			node->setVisible(bVisible);
		}
		else if (key == "objecttag")
		{
			nTag = atoi(value.c_str());
			node->setTag(nTag);
		}
		else if (key == "zorder")
		{
			nZorder = atoi(value.c_str());
			node->setZOrder(nZorder);
		}
		else if(key == "scalex")
		{
			fScaleX = atof(value.c_str());
			node->setScaleX(fScaleX);
		}
		else if(key == "scaley")
		{
			fScaleY = atof(value.c_str());
			node->setScaleY(fScaleY);
		}
		else if(key == "rotation")
		{
			fRotationZ = atof(value.c_str());
			node->setRotation(fRotationZ);
		}
	}
}

SceneReader* SceneReader::sharedSceneReader()
{
	if (_sharedReader == NULL)
	{
		_sharedReader = new SceneReader();
	}
	return _sharedReader;
}

void SceneReader::purge()
{		
    cocos2d::extension::DictionaryHelper::shareHelper()->purgeDictionaryHelper();
    TriggerMng::getInstance()->destroyInstance();
    _pfnSelector = NULL;
    _pListener = NULL;
    CocosDenshion::SimpleAudioEngine::sharedEngine()->end();
    CC_SAFE_DELETE(_sharedReader);
}

NS_CC_EXT_END