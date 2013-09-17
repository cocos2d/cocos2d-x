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

#include "CCSSceneReader.h"
#include "cocos-ext.h"

NS_CC_EXT_BEGIN

	SceneReader* SceneReader::s_sharedReader = NULL;

    SceneReader::SceneReader()
    {
	}

    SceneReader::~SceneReader()
    {
    }

	const char* SceneReader::sceneReaderVersion()
	{
		return "0.1.0.0";
	}

    cocos2d::Node* SceneReader::createNodeWithSceneFile(const char* pszFileName)
    {
        unsigned long size = 0;
        const char* pData = 0;
		cocos2d::Node *pNode = NULL;
        do {
			  CC_BREAK_IF(pszFileName == NULL);
              pData = (char*)(cocos2d::FileUtils::getInstance()->getFileData(pszFileName, "r", &size));
              CC_BREAK_IF(pData == NULL || strcmp(pData, "") == 0);
              cs::JsonDictionary *jsonDict = new cs::JsonDictionary();
              jsonDict->initWithDescription(pData);
              pNode = createObject(jsonDict,NULL);
              CC_SAFE_DELETE(jsonDict);
        } while (0);
        
        return pNode;
	}

	Node* SceneReader::createObject(cs::JsonDictionary * inputFiles, Node* parenet)
    {
        const char *className = inputFiles->getItemStringValue("classname"); 
        if(strcmp(className, "CCNode") == 0)
        {
            Node* gb = NULL;
            if(NULL == parenet)
            {
                gb = Node::create();
            }
            else
            {
                gb = Node::create();
                parenet->addChild(gb);
            }
            
            setPropertyFromJsonDict(gb, inputFiles);
    
            int count = inputFiles->getArrayItemCount("components");
            for (int i = 0; i < count; i++)
            {
                cs::JsonDictionary * subDict = inputFiles->getSubItemFromArray("components", i);
                if (!subDict)
				{
				   CC_SAFE_DELETE(subDict);
                   break;
				}
                const char *comName = subDict->getItemStringValue("classname");
				const char *pComName = subDict->getItemStringValue("name");
                
				cs::JsonDictionary *fileData = subDict->getSubDictionary("fileData");
				std::string pPath;
                std::string pPlistFile;
				int nResType = 0;
				if (fileData != NULL)
                {
					const char *file = fileData->getItemStringValue("path");
					nResType = fileData->getItemIntValue("resourceType", -1);
					const char *plistFile = fileData->getItemStringValue("plistFile");
					if (file != NULL)
					{
						pPath.append(cocos2d::FileUtils::getInstance()->fullPathForFilename(file));
					}

					if (plistFile != NULL)
					{
						pPlistFile.append(cocos2d::FileUtils::getInstance()->fullPathForFilename(plistFile));
					}
					CC_SAFE_DELETE(fileData);
                }

                if (comName != NULL && strcmp(comName, "CCSprite") == 0)
                {
					cocos2d::Sprite *pSprite = NULL;

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
                    if (pComName != NULL)
                    {
                        pRender->setName(pComName);
                    }
                    
                    gb->addComponent(pRender);
                }
                else if(comName != NULL && strcmp(comName, "CCTMXTiledMap") == 0)
                {
					cocos2d::TMXTiledMap *pTmx = NULL;
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
                    if (pComName != NULL)
                    {
                        pRender->setName(pComName);
                    }
                    gb->addComponent(pRender);
                }
                else if(comName != NULL && strcmp(comName, "CCParticleSystemQuad") == 0)
                {
                    std::string::size_type pos =  pPath.find(".plist");
                    if (pos  == pPath.npos)
                    {
                        continue;
                    }

					cocos2d::ParticleSystemQuad *pParticle = NULL;
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
                    if (pComName != NULL)
                    {
                        pRender->setName(pComName);
                    }
                    gb->addComponent(pRender);
                }
                else if(comName != NULL && strcmp(comName, "CCArmature") == 0)
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
					unsigned long size = 0;
					const char *des = (char*)(cocos2d::FileUtils::getInstance()->getFileData(pPath.c_str(),"r" , &size));
					cs::JsonDictionary *jsonDict = new cs::JsonDictionary();
					jsonDict->initWithDescription(des);
					if(NULL == des || strcmp(des, "") == 0)
					{
						CCLOG("read json file[%s] error!\n", pPath.c_str());
					}

					int childrenCount = DICTOOL->getArrayCount_json(jsonDict, "armature_data");
					cs::JsonDictionary* subData = DICTOOL->getDictionaryFromArray_json(jsonDict, "armature_data", 0);
					const char *name = DICTOOL->getStringValue_json(subData, "name");

					childrenCount = DICTOOL->getArrayCount_json(jsonDict, "config_file_path");
					for (int i = 0; i < childrenCount; ++i)
					{
						const char* plist = DICTOOL->getStringValueFromArray_json(jsonDict, "config_file_path", i);
						std::string plistpath;
						plistpath += file_path;
						plistpath.append(plist);
						cocos2d::Dictionary *root = Dictionary::createWithContentsOfFile(plistpath.c_str());
						Dictionary* metadata = DICTOOL->getSubDictionary(root, "metadata");
						const char* textureFileName = DICTOOL->getStringValue(metadata, "textureFileName");

						std::string textupath;
						textupath += file_path;
						textupath.append(textureFileName);

						cocos2d::extension::armature::ArmatureDataManager::getInstance()->addArmatureFileInfo(textupath.c_str(), plistpath.c_str(), pPath.c_str());

					}

					cocos2d::extension::armature::Armature *pAr = cocos2d::extension::armature::Armature::create(name);
					ComRender *pRender = ComRender::create(pAr, "CCArmature");
					if (pComName != NULL)
					{
						pRender->setName(pComName);
					}
					gb->addComponent(pRender);

					const char *actionName = subDict->getItemStringValue("selectedactionname");
					if (actionName != NULL && pAr->getAnimation() != NULL)
					{
						pAr->getAnimation()->play(actionName);
					}

					CC_SAFE_DELETE(jsonDict);
					CC_SAFE_DELETE(subData);
					CC_SAFE_DELETE_ARRAY(des);
                }
                else if(comName != NULL && strcmp(comName, "CCComAudio") == 0)
                {
					ComAudio *pAudio = NULL;
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
                }
                else if(comName != NULL && strcmp(comName, "CCComAttribute") == 0)
                {
                    ComAttribute *pAttribute = NULL;
					if (nResType == 0)
					{
						pAttribute = ComAttribute::create();
						unsigned long size = 0;
						const char* pData = 0;
						pData = (char*)(cocos2d::FileUtils::getInstance()->getFileData(pPath.c_str(), "r", &size));
						if(pData != NULL && strcmp(pData, "") != 0)
						{
							pAttribute->getDict()->initWithDescription(pData);
						}
					}
					else
					{
						CCLOG("unknown resourcetype on CCComAttribute!");
						continue;
					}
                    gb->addComponent(pAttribute);
                }
                else if (comName != NULL && strcmp(comName, "CCBackgroundAudio") == 0)
                {
					ComAudio *pAudio = NULL;
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
					bool bLoop = subDict->getItemIntValue("loop", 0);
					pAudio->setLoop(bLoop);
                    gb->addComponent(pAudio);
					pAudio->playBackgroundMusic(pPath.c_str(), bLoop);
                }
				else if(comName != NULL && strcmp(comName, "GUIComponent") == 0)
				{
                    cocos2d::extension::UILayer *pLayer = cocos2d::extension::UILayer::create();
					pLayer->scheduleUpdate();
					UIWidget* widget=cocos2d::extension::UIHelper::instance()->createWidgetFromJsonFile(pPath.c_str());
					pLayer->addWidget(widget);
					ComRender *pRender = ComRender::create(pLayer, "GUIComponent");
					if (pComName != NULL)
					{
					pRender->setName(pComName);
					}
					gb->addComponent(pRender);
				}
                
                CC_SAFE_DELETE(subDict);
            }

            for (int i = 0; i < inputFiles->getArrayItemCount("gameobjects"); i++)
            {
                cs::JsonDictionary * subDict = inputFiles->getSubItemFromArray("gameobjects", i);
                if (!subDict)
                {
                    break;
                }
                createObject(subDict, gb);
                CC_SAFE_DELETE(subDict);
            }
            
            return gb;
        }
        
        return NULL;
    }


    void SceneReader::setPropertyFromJsonDict(cocos2d::Node *node, cs::JsonDictionary* dict)
    {
		int x = dict->getItemIntValue("x", 0);
		int y = dict->getItemIntValue("y", 0);
		node->setPosition(Point(x, y));
		
		bool bVisible = (bool)(dict->getItemIntValue("visible", 1));
		node->setVisible(bVisible);
		
		int nTag = dict->getItemIntValue("objecttag", -1);
        node->setTag(nTag);
		
		int nZorder = dict->getItemIntValue("zorder", 0);
		node->setZOrder(nZorder);
		
		float fScaleX = dict->getItemFloatValue("scalex", 1.0);
		float fScaleY = dict->getItemFloatValue("scaley", 1.0);
        node->setScaleX(fScaleX);
        node->setScaleY(fScaleY);
        
		float fRotationZ = dict->getItemIntValue("rotation", 0);
        node->setRotation(fRotationZ);
    }

	SceneReader* SceneReader::getInstance()
	{
		if (s_sharedReader == NULL)
		{
			s_sharedReader = new SceneReader();
		}
		return s_sharedReader;
	}

    void SceneReader::purgeSceneReader()
    {
		CC_SAFE_DELETE(s_sharedReader);
		cocos2d::extension::DictionaryHelper::shareHelper()->purgeDictionaryHelper();
    }

NS_CC_EXT_END
