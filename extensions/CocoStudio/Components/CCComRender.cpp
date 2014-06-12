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

#include "cocos-ext.h"
#include "CCComRender.h"
#include "../Json/CocoLoader.h"

NS_CC_EXT_BEGIN

IMPLEMENT_CLASS_COMPONENT_INFO(CCComRender)
CCComRender::CCComRender(void)
: m_pRender(NULL)
{
	m_strName = "CCComRender";
}

CCComRender::CCComRender(cocos2d::CCNode *node, const char *comName)
{
    if (node != NULL)
    {		
        m_pRender = node;
        m_pRender->retain();    
    }
    m_strName.assign(comName);
}

CCComRender::~CCComRender(void)
{
    CC_SAFE_RELEASE_NULL(m_pRender);
}

void CCComRender::onEnter()
{
    if (m_pOwner != NULL)
    {
        m_pOwner->addChild(m_pRender);
    }
}

void CCComRender::onExit()
{
    if (m_pOwner != NULL)
    {
        m_pOwner->removeChild(m_pRender, true);
    }
}

cocos2d::CCNode* CCComRender::getNode()
{
    return m_pRender;
}

void CCComRender::setNode(cocos2d::CCNode *pNode)
{
	if (m_pRender != NULL)
	{
		m_pRender->release();
		m_pRender = NULL;
	}
    if (pNode != NULL)
    {		
		m_pRender = pNode;
        m_pRender->retain();    
    }
}

bool CCComRender::serialize(void* r)
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(r == NULL);
		SerData *pSerData = (SerData *)(r);
        const rapidjson::Value *v = pSerData->prData;
		stExpCocoNode *pCocoNode = pSerData->pCocoNode;
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
			strFilePath.assign(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(pFile));
		}
		if (pPlist != NULL)
		{
			strPlistPath.assign(cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(pPlist));
		}
		if (nResType == 0)
		{
			if (strcmp(pClassName, "CCSprite") == 0 && (strFilePath.find(".png") != strFilePath.npos || strFilePath.find(".pvr.ccz") != strFilePath.npos))
			{
				m_pRender = CCSprite::create(strFilePath.c_str());
				m_pRender->retain();
			}
			else if(strcmp(pClassName, "CCTMXTiledMap") == 0 && strFilePath.find(".tmx") != strFilePath.npos)
			{
				m_pRender = CCTMXTiledMap::create(strFilePath.c_str());
				m_pRender->retain();
			}
			else if(strcmp(pClassName, "CCParticleSystemQuad") == 0 && strFilePath.find(".plist") != strFilePath.npos)
			{
				m_pRender = CCParticleSystemQuad::create(strFilePath.c_str());
				m_pRender->setPosition(ccp(0.0f, 0.0f));
				m_pRender->retain();
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
						CCLog("read json file[%s] error!\n", strFilePath.c_str());
						continue;
					}
					const rapidjson::Value &subData = DICTOOL->getDictionaryFromArray_json(doc, "armature_data", 0);
					const char *name = DICTOOL->getStringValue_json(subData, "name");
					CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(strFilePath.c_str());
					CCArmature *pAr = CCArmature::create(name);
					m_pRender = pAr;
					m_pRender->retain();
					const char *actionName = NULL;
					actionName = DICTOOL->getStringValue_json(*v, "selectedactionname");
					if (actionName != NULL && pAr->getAnimation() != NULL)
					{
						pAr->getAnimation()->play(actionName);
					}
				}
				else if (file_extension == ".CSB")
				{
					unsigned long size = 0;
					unsigned char *pBytes = NULL;
					std::string binaryFilePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(strFilePath.c_str());
					pBytes = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(binaryFilePath.c_str(), "rb", &size);
					CC_BREAK_IF(pBytes == NULL || strcmp((char*)pBytes, "") == 0);
					CocoLoader tCocoLoader;
					if (tCocoLoader.ReadCocoBinBuff((char*)pBytes))
					{
						stExpCocoNode *tpRootCocoNode = tCocoLoader.GetRootCocoNode();
						rapidjson::Type tType = tpRootCocoNode->GetType(&tCocoLoader);
						if (rapidjson::kObjectType  == tType)
						{
							stExpCocoNode *tpChildArray = tpRootCocoNode->GetChildArray();
							stExpCocoNode *armaturedataArray = tpChildArray[0].GetChildArray();
							stExpCocoNode *armaturedata = armaturedataArray[0].GetChildArray();
							const char *name = armaturedata[2].GetValue();
							CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(strFilePath.c_str());
							CCArmature *pAr = CCArmature::create(name);
							m_pRender = pAr;
							m_pRender->retain();
							const char *actionName = NULL;
							if (pCocoNode != NULL)
							{
								actionName = pCocoNode[6].GetValue();//DICTOOL->getStringValue_json(*v, "selectedactionname");
							}
							if (actionName != NULL && pAr->getAnimation() != NULL)
							{
								pAr->getAnimation()->play(actionName);
							}
						}
					}
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
					cocos2d::ui::TouchGroup* tg = cocos2d::ui::TouchGroup::create();
					cocos2d::ui::Widget* widget = cocos2d::extension::GUIReader::shareReader()->widgetFromJsonFile(strFilePath.c_str());
					tg->addWidget(widget);
					m_pRender = tg;
					m_pRender->retain();
				}
				else if (file_extension == ".CSB")
				{

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
				CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(strPlistPath.c_str(), strPngFile.c_str());
				m_pRender = CCSprite::createWithSpriteFrameName(strFilePath.c_str());
				m_pRender->retain();
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

CCComRender* CCComRender::create(cocos2d::CCNode *pNode, const char *comName)
{
    CCComRender * pRet = new CCComRender(pNode, comName);
    if (pRet != NULL && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
        return pRet;
}

CCComRender* CCComRender::create(void)
{
    CCComRender * pRet = new CCComRender();
    if (pRet != NULL && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool CCComRender::readJson(const char *pszFileName, rapidjson::Document &doc)
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


NS_CC_EXT_END
