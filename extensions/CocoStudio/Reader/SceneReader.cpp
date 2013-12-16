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
		return "1.0.0.0";
	}

    cocos2d::CCNode* SceneReader::createNodeWithSceneFile(const char* pszFileName)
    {
		cocos2d::CCNode *pNode = NULL;
        rapidjson::Document jsonDict;
        do {
			  CC_BREAK_IF(!readJson(pszFileName, jsonDict));
              pNode = createObject(jsonDict, NULL);
        } while (0);
        
        return pNode;
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
              CCData *data = new CCData(pBytes, size);
	          std::string load_str = std::string((const char *)data->getBytes(), data->getSize() );
	          CC_SAFE_DELETE(data);
              doc.Parse<0>(load_str.c_str());
              CC_BREAK_IF(doc.HasParseError());
              bRet = true;
            } while (0);
        return bRet;
    }

	CCNode* SceneReader::createObject(const rapidjson::Value &root, cocos2d::CCNode* parent)
    {
        const char *className = DICTOOL->getStringValue_json(root, "classname"); //inputFiles->getItemStringValue("classname");
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
				const char *pComName = DICTOOL->getStringValue_json(subDict, "name");
				const rapidjson::Value &fileData = DICTOOL->getSubDictionary_json(subDict, "fileData");
                std::string pPath;
                std::string pPlistFile;
				int nResType = 0;
				//if (fileData != NULL)
                if (DICTOOL->checkObjectExist_json(fileData))
                {
					const char *file = DICTOOL->getStringValue_json(fileData, "path");
					nResType = DICTOOL->getIntValue_json(fileData, "resourceType", - 1);
					const char *plistFile = DICTOOL->getStringValue_json(fileData, "plistFile");
					if (file != NULL)
					{
						pPath.append(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(file));
					}

					if (plistFile != NULL)
					{
						pPlistFile.append(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(plistFile));
					}
                }

                if (comName != NULL && strcmp(comName, "CCSprite") == 0)
                {
					cocos2d::CCSprite *pSprite = NULL;

					if (nResType == 0)
					{
						if (pPath.find(".png") == pPath.npos)
						{
							continue;
						}
						pSprite = CCSprite::create(pPath.c_str());
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
						CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pPlistFile.c_str(), pngFile.c_str());
						pSprite = CCSprite::createWithSpriteFrameName(pPath.c_str());
					}
					else
					{
						continue;
					}
					
                    CCComRender *pRender = CCComRender::create(pSprite, "CCSprite");
                    if (pComName != NULL)
                    {
                        pRender->setName(pComName);
                    }
                    
                    gb->addComponent(pRender);
                }
                else if(comName != NULL && strcmp(comName, "CCTMXTiledMap") == 0)
                {
					cocos2d::CCTMXTiledMap *pTmx = NULL;
					if (nResType == 0)
					{
						if (pPath.find(".tmx") == pPath.npos)
						{
							continue;
						}
						pTmx = CCTMXTiledMap::create(pPath.c_str());
					}
					else
					{
						continue;
					}

                    CCComRender *pRender = CCComRender::create(pTmx, "CCTMXTiledMap");
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

					cocos2d::CCParticleSystemQuad *pParticle = NULL;
					if (nResType == 0)
					{
						pParticle = CCParticleSystemQuad::create(pPath.c_str());
					}
					else
					{
						CCLog("unknown resourcetype on CCParticleSystemQuad!");
					}

					pParticle->setPosition(0, 0);
                    CCComRender *pRender = CCComRender::create(pParticle, "CCParticleSystemQuad");
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
                    
                    rapidjson::Document jsonDict;
                    if(!readJson(pPath.c_str(), jsonDict))
                    {
                        CCLog("read json file[%s] error!\n", pPath.c_str());
                        continue;
                    }
                    
                    
                    int childrenCount = DICTOOL->getArrayCount_json(jsonDict, "armature_data");
                    const rapidjson::Value &subData = DICTOOL->getDictionaryFromArray_json(jsonDict, "armature_data", 0);
                    const char *name = DICTOOL->getStringValue_json(subData, "name");

                    childrenCount = DICTOOL->getArrayCount_json(jsonDict, "config_file_path");
                    for (int i = 0; i < childrenCount; ++i)
                    {
                        const char* plist = DICTOOL->getStringValueFromArray_json(jsonDict, "config_file_path", i);
                        if (plist == NULL)
                        {
                            continue;
                        }
                        std::string plistpath;
                        plistpath += file_path;
                        plistpath.append(plist);
                        cocos2d::CCDictionary *root = CCDictionary::createWithContentsOfFile(plistpath.c_str());
                        CCDictionary* metadata = DICTOOL->getSubDictionary(root, "metadata");
                        const char* textureFileName = DICTOOL->getStringValue(metadata, "textureFileName");

                        std::string textupath;
                        textupath += file_path;
                        textupath.append(textureFileName);

                        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(textupath.c_str(), plistpath.c_str(), pPath.c_str());
                        
                    }
                    
                    CCArmature *pAr = CCArmature::create(name);
                    CCComRender *pRender = CCComRender::create(pAr, "CCArmature");
                    if (pComName != NULL)
                    {
                        pRender->setName(pComName);
                    }
                    gb->addComponent(pRender);

					const char *actionName = DICTOOL->getStringValue_json(subDict, "selectedactionname"); 
					if (actionName != NULL && pAr->getAnimation() != NULL)
					{
						pAr->getAnimation()->play(actionName);
					}
                }
                else if(comName != NULL && strcmp(comName, "CCComAudio") == 0)
                {
					CCComAudio *pAudio = NULL;
					if (nResType == 0)
					{
						pAudio = CCComAudio::create();
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
                    CCComAttribute *pAttribute = NULL;
					if (nResType == 0)
					{
						pAttribute = CCComAttribute::create();
						unsigned long size = 0;
						const char* pData = 0;
						pData = (char*)(cocos2d::CCFileUtils::sharedFileUtils()->getFileData(pPath.c_str(), "r", &size));
						if(pData != NULL && strcmp(pData, "") != 0)
						{
                            pAttribute->parse(pData);
						}
					}
					else
					{
						CCLog("unknown resourcetype on CCComAttribute!");
						continue;
					}
                    gb->addComponent(pAttribute);
                }
                else if (comName != NULL && strcmp(comName, "CCBackgroundAudio") == 0)
                {
					CCComAudio *pAudio = NULL;
					if (nResType == 0)
					{
						pAudio = CCComAudio::create();
					}
					else
					{
						continue;
					}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
                    // no MP3 support for CC_PLATFORM_WP8
                    std::string::size_type pos = pPath.find(".mp3");
					if (pos  == pPath.npos)
					{
						continue;
					}
					pPath.replace(pos, pPath.length(), ".wav");
#endif
                    pAudio->preloadBackgroundMusic(pPath.c_str());
					pAudio->setFile(pPath.c_str());
					bool bLoop = (bool)(DICTOOL->getIntValue_json(subDict, "loop"));
					pAudio->setLoop(bLoop);
                    gb->addComponent(pAudio);
					pAudio->playBackgroundMusic(pPath.c_str(), bLoop);
                }
				else if(comName != NULL && strcmp(comName, "GUIComponent") == 0)
				{
					cocos2d::extension::UILayer *pLayer = cocos2d::extension::UILayer::create();
                    pLayer->scheduleUpdate();
                    UIWidget* widget = cocos2d::extension::GUIReader::shareReader()->widgetFromJsonFile(pPath.c_str());
					pLayer->addWidget(widget);
					CCComRender *pRender = CCComRender::create(pLayer, "GUIComponent");
					if (pComName != NULL)
					{
					pRender->setName(pComName);
					}
					gb->addComponent(pRender);
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


    void SceneReader::setPropertyFromJsonDict(const rapidjson::Value &root, cocos2d::CCNode *node)
    {
		float x = DICTOOL->getFloatValue_json(root, "x");
		float y = DICTOOL->getFloatValue_json(root, "y");
        
		node->setPosition(ccp(x, y));
		
		bool bVisible = (bool)(DICTOOL->getIntValue_json(root, "visible", 1));
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
