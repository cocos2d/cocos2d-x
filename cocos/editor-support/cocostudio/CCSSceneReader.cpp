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

#include "cocostudio/CocoStudio.h"
#include "gui/CocosGUI.h"

using namespace cocos2d;
using namespace gui;

namespace cocostudio {

    SceneReader* SceneReader::s_sharedReader = nullptr;

    SceneReader::SceneReader()
    : _pListener(NULL)
    , _pfnSelector(NULL)
    , _pNode(NULL)
    {
    }

    SceneReader::~SceneReader()
    {
    }

    const char* SceneReader::sceneReaderVersion()
    {
        return "1.0.0.0";
    }

    cocos2d::Node* SceneReader::createNodeWithSceneFile(const char* pszFileName)
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
		do {
			CC_BREAK_IF(pszFileName == NULL);
			std::string jsonpath = CCFileUtils::getInstance()->fullPathForFilename(pszFileName);
            std::string contentStr = FileUtils::getInstance()->getStringFromFile(jsonpath);
			doc.Parse<0>(contentStr.c_str());
			CC_BREAK_IF(doc.HasParseError());
			bRet = true;
		} while (0);
		return bRet;
	}

	Node* SceneReader::nodeByTag(Node *pParent, int nTag)
	{		
		if (pParent == NULL)
		{
			return NULL;
		}
		Node *_retNode = NULL;
		Vector<Node*>& Children = pParent->getChildren();
		Vector<Node*>::iterator iter = Children.begin();
		while (iter != Children.end())
		{
			Node* pNode = *iter;
			if(pNode != NULL && pNode->getTag() == nTag)
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
            ++iter;
		}
		return _retNode;
	}


	Node* SceneReader::createObject(const rapidjson::Value &dict, cocos2d::Node* parent)
    {
        const char *className = DICTOOL->getStringValue_json(dict, "classname");
        if(strcmp(className, "CCNode") == 0)
        {
            Node* gb = nullptr;
            if(nullptr == parent)
            {
                gb = Node::create();
            }
            else
            {
                gb = Node::create();
                parent->addChild(gb);
            }
            
            setPropertyFromJsonDict(dict, gb);
    
            int count = DICTOOL->getArrayCount_json(dict, "components");
            for (int i = 0; i < count; i++)
            {
                const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(dict, "components", i);
                if (!DICTOOL->checkObjectExist_json(subDict))
                {
                    break;
                }
                const char *comName = DICTOOL->getStringValue_json(subDict, "classname");
				const char *pComName = DICTOOL->getStringValue_json(subDict, "name");
                
				const rapidjson::Value &fileData = DICTOOL->getSubDictionary_json(subDict, "fileData");
                std::string pPath;
                std::string pPlistFile;
                int nResType = 0;
                if (DICTOOL->checkObjectExist_json(fileData))
                {
					const char *file = DICTOOL->getStringValue_json(fileData, "path");
					nResType = DICTOOL->getIntValue_json(fileData, "resourceType", - 1);
					const char *plistFile = DICTOOL->getStringValue_json(fileData, "plistFile");
                    if (file != nullptr)
                    {
                        pPath.append(cocos2d::FileUtils::getInstance()->fullPathForFilename(file));
                    }

                    if (plistFile != nullptr)
                    {
                        pPlistFile.append(cocos2d::FileUtils::getInstance()->fullPathForFilename(plistFile));
                    }
                    
                    if (file == nullptr && plistFile == nullptr)
                    {
                        continue;
                    }
                }
                else
                {
                    continue;
                }

                if (comName != nullptr && strcmp(comName, "CCSprite") == 0)
                {
                    cocos2d::Sprite *pSprite = nullptr;

                    if (nResType == 0)
                    {
                        if (pPath.find(".png") == pPath.npos)
                        {
                            continue;
                        }
                        pSprite = Sprite::create(pPath.c_str());
                    }
                    else if (nResType == 1)
                    {
                        std::string pngFile = pPlistFile;
                        std::string::size_type pos = pngFile.find(".plist");
                        if (pos  == pPath.npos)
                        {
                            continue;
                        }
                        pngFile.replace(pos, pngFile.length(), ".png");
                        CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile(pPlistFile.c_str(), pngFile.c_str());
                        pSprite = Sprite::createWithSpriteFrameName(pPath.c_str());
                    }
                    else
                    {
                        continue;
                    }
                    
                    ComRender *pRender = ComRender::create(pSprite, "CCSprite");
                    if (pComName != nullptr)
                    {
                        pRender->setName(pComName);
                    }
                    
                    gb->addComponent(pRender);
					if (_pListener && _pfnSelector)
					{
						(_pListener->*_pfnSelector)(pSprite, (void*)(&subDict));
					}
                }
                else if(comName != nullptr && strcmp(comName, "CCTMXTiledMap") == 0)
                {
                    cocos2d::TMXTiledMap *pTmx = nullptr;
                    if (nResType == 0)
                    {
                        if (pPath.find(".tmx") == pPath.npos)
                        {
                            continue;
                        }
                        pTmx = TMXTiledMap::create(pPath.c_str());
                    }
                    else
                    {
                        continue;
                    }

                    ComRender *pRender = ComRender::create(pTmx, "CCTMXTiledMap");
                    if (pComName != nullptr)
                    {
                        pRender->setName(pComName);
                    }
                    gb->addComponent(pRender);
					if (_pListener && _pfnSelector)
					{
						(_pListener->*_pfnSelector)(pTmx, (void*)(&subDict));
					}
                }
                else if(comName != nullptr && strcmp(comName, "CCParticleSystemQuad") == 0)
                {
                    std::string::size_type pos =  pPath.find(".plist");
                    if (pos  == pPath.npos)
                    {
                        continue;
                    }

                    cocos2d::ParticleSystemQuad *pParticle = nullptr;
                    if (nResType == 0)
                    {
                        pParticle = ParticleSystemQuad::create(pPath.c_str());
                    }
                    else
                    {
                        CCLOG("unknown resourcetype on CCParticleSystemQuad!");
                    }

                    pParticle->setPosition(0, 0);
                    ComRender *pRender = ComRender::create(pParticle, "CCParticleSystemQuad");
                    if (pComName != nullptr)
                    {
                        pRender->setName(pComName);
                    }
                    gb->addComponent(pRender);
					if (_pListener && _pfnSelector)
					{
						(_pListener->*_pfnSelector)(pParticle, (void*)(&subDict));
					}
                }
                else if(comName != nullptr && strcmp(comName, "CCArmature") == 0)
                {
                    if (nResType != 0)
                    {
                        continue;
                    }
                    std::string reDir = pPath;
                    std::string file_path = "";
                    size_t pos = reDir.find_last_of('/');
                    if (pos != std::string::npos)
                    {
                        file_path = reDir.substr(0, pos+1);
                    }

                    rapidjson::Document jsonDict;
                    if(!readJson(pPath.c_str(), jsonDict))
                    {
                        log("read json file[%s] error!\n", pPath.c_str());
                        continue;
                    }
                    
                    const rapidjson::Value &subData = DICTOOL->getDictionaryFromArray_json(jsonDict, "armature_data", 0);
                    const char *name = DICTOOL->getStringValue_json(subData, "name");

                    ArmatureDataManager::getInstance()->addArmatureFileInfo(pPath.c_str());

                    Armature *pAr = Armature::create(name);
                    ComRender *pRender = ComRender::create(pAr, "CCArmature");
                    if (pComName != nullptr)
                    {
                        pRender->setName(pComName);
                    }
                    gb->addComponent(pRender);

					const char *actionName = DICTOOL->getStringValue_json(subDict, "selectedactionname"); 
                    if (actionName != nullptr && pAr->getAnimation() != nullptr)
                    {
                        pAr->getAnimation()->play(actionName);
                    }
					if (_pListener && _pfnSelector)
					{
						(_pListener->*_pfnSelector)(pAr, (void*)(&subDict));
					}
                }
                else if(comName != nullptr && strcmp(comName, "CCComAudio") == 0)
                {
                    ComAudio *pAudio = nullptr;
                    if (nResType == 0)
                    {
                        pAudio = ComAudio::create();
                    }
                    else
                    {
                        continue;
                    }
                    pAudio->preloadEffect(pPath.c_str());
                    gb->addComponent(pAudio);
					if (_pListener && _pfnSelector)
					{
						(_pListener->*_pfnSelector)(pAudio, (void*)(&subDict));
					}
                }
                else if(comName != nullptr && strcmp(comName, "CCComAttribute") == 0)
                {
                    ComAttribute *pAttribute = nullptr;
                    if (nResType == 0)
                    {
                        pAttribute = ComAttribute::create();
                    }
                    else
                    {
                        CCLOG("unknown resourcetype on CCComAttribute!");
                        continue;
                    }
                    gb->addComponent(pAttribute);
					if (_pListener && _pfnSelector)
					{
						(_pListener->*_pfnSelector)(pAttribute, (void*)(&subDict));
					}
                }
                else if (comName != nullptr && strcmp(comName, "CCBackgroundAudio") == 0)
                {
                    ComAudio *pAudio = nullptr;
                    if (nResType == 0)
                    {
                        pAudio = ComAudio::create();
                    }
                    else
                    {
                        continue;
                    }
                    pAudio->preloadBackgroundMusic(pPath.c_str());
                    pAudio->setFile(pPath.c_str());
                    const bool bLoop = (DICTOOL->getIntValue_json(subDict, "loop") != 0);
                    pAudio->setLoop(bLoop);
                    gb->addComponent(pAudio);
                    pAudio->playBackgroundMusic(pPath.c_str(), bLoop);
                }
                else if(comName != nullptr && strcmp(comName, "GUIComponent") == 0)
                {
                    Widget* widget= GUIReader::shareReader()->widgetFromJsonFile(pPath.c_str());
                    ComRender *pRender = ComRender::create(widget, "GUIComponent");
                    if (pComName != nullptr)
                    {
                    pRender->setName(pComName);
                    }
                    gb->addComponent(pRender);
					if (_pListener && _pfnSelector)
					{
						(_pListener->*_pfnSelector)(widget, (void*)(&subDict));
					}
				}
            }

            int length = DICTOOL->getArrayCount_json(dict, "gameobjects");
            for (int i = 0; i < length; ++i)
            {
                const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(dict, "gameobjects", i);
                if (!DICTOOL->checkObjectExist_json(subDict))
                {
                    break;
                }
                createObject(subDict, gb);
            }
            
            return gb;
        }
        
        return nullptr;
    }

	void SceneReader::setTarget(Object *rec, SEL_CallFuncOD selector)
	{
		_pListener = rec;
		_pfnSelector = selector;
	}

	Node* SceneReader::getNodeByTag(int nTag)
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

    void SceneReader::setPropertyFromJsonDict(const rapidjson::Value &root, cocos2d::Node *node)
    {
		float x = DICTOOL->getFloatValue_json(root, "x");
		float y = DICTOOL->getFloatValue_json(root, "y");
        node->setPosition(Point(x, y));
        
        const bool bVisible = (DICTOOL->getIntValue_json(root, "visible", 1) != 0);
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

    SceneReader* SceneReader::getInstance()
    {
        if (s_sharedReader == nullptr)
        {
            s_sharedReader = new SceneReader();
        }
        return s_sharedReader;
    }

    void SceneReader::destroyInstance()
    {
        DictionaryHelper::destroyInstance();
		TriggerMng::destroyInstance();
		CC_SAFE_DELETE(s_sharedReader);
    }

}
