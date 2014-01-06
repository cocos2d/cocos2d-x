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
#include "SimpleAudioEngine.h"
#include "../Trigger/ObjectFactory.h"

NS_CC_EXT_BEGIN

SceneReader* SceneReader::_sharedReader = NULL;
CCObject*  SceneReader::_pListener = NULL;
SEL_CallFuncOD  SceneReader::_pfnSelector = NULL;

SceneReader::SceneReader()
:_pNode(NULL)
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

cocos2d::CCNode* SceneReader::createNodeWithSceneFile(const char* pszFileName)
{
	rapidjson::Document jsonDict;
	do {
		CC_BREAK_IF(!readJson(pszFileName, jsonDict));
		_pNode = createObject(jsonDict, NULL);
		TriggerMng::getInstance()->parse(jsonDict);
	} while (0);
	return _pNode;
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

CCNode* SceneReader::createObject(const rapidjson::Value &root, cocos2d::CCNode* parent)
{
	const char *className = DICTOOL->getStringValue_json(root, "classname");
	if(strcmp(className, "CCNode") == 0)
	{
		CCNode* gb = NULL;
		if(NULL == parent)
		{
			gb = CCNode::create();
		}
		else
		{
			gb = CCNode::create();
			parent->addChild(gb);
		}
		setPropertyFromJsonDict(root, gb);
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
			if (pCom != NULL)
			{
				if (pCom->serialize((void*)(&subDict)))
				{
					gb->addComponent(pCom);
				}
				else
				{
					CC_SAFE_RELEASE_NULL(pCom);
				}
			}
			if (_pListener && _pfnSelector)
			{
				(_pListener->*_pfnSelector)(pCom, (void*)(&subDict));
			}
		}
		int length = DICTOOL->getArrayCount_json(root, "gameobjects");
		for (int i = 0; i < length; ++i)
		{
			const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(root, "gameobjects", i);
			if (!DICTOOL->checkObjectExist_json(subDict))
			{
				break;
			}
			createObject(subDict, gb);
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
