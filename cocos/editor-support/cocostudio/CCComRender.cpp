/****************************************************************************
Copyright (c) 2013-2017 Chukong Technologies Inc.

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

#include "editor-support/cocostudio/CCComRender.h"
#include "editor-support/cocostudio/CocoStudio.h"

#include "platform/CCFileUtils.h"
#include "2d/CCTMXTiledMap.h"
#include "2d/CCParticleSystemQuad.h"
#include "2d/CCSpriteFrameCache.h"

using namespace cocos2d;

namespace cocostudio {

IMPLEMENT_CLASS_COMPONENT_INFO(ComRender)

const std::string ComRender::COMPONENT_NAME = "CCComRender";

ComRender::ComRender()
: _render(nullptr)
{
    _name = COMPONENT_NAME;
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

ComRender::~ComRender()
{
    CC_SAFE_RELEASE_NULL(_render);
}

void ComRender::onEnter()
{
    if (_owner != nullptr && _render->getParent() == nullptr)
    {
       _owner->addChild(_render);
    }
}

void ComRender::onExit()
{
    if (_owner != nullptr && _render->getParent() == nullptr)
    {
       _owner->removeChild(_render, true);
    }
}

void ComRender::onAdd()
{
    if (_owner != nullptr && _render->getParent() == nullptr)
    {
        _owner->addChild(_render);
    }
}

void ComRender::onRemove()
{
    if (_owner != nullptr && _render->getParent() == nullptr)
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


// TODO: This method is soooo big!! We should refactor it!
bool ComRender::serialize(void* r)
{
    bool ret = false;
    do
    {
        CC_BREAK_IF(r == nullptr);
        SerData *serData = (SerData *)(r);
        const rapidjson::Value *v = serData->_rData;
        stExpCocoNode *cocoNode = serData->_cocoNode;
        CocoLoader *cocoLoader = serData->_cocoLoader;
        const char *className = nullptr;
        const char *comName = nullptr;
        const char *file = nullptr;
        const char *plist = nullptr;
        std::string filePath;
        std::string plistPath;
        int resType = 0;
        if (v != nullptr)
        {
            className = DICTOOL->getStringValue_json(*v, "classname");
            CC_BREAK_IF(className == nullptr);
            comName = DICTOOL->getStringValue_json(*v, "name");
            const rapidjson::Value &fileData = DICTOOL->getSubDictionary_json(*v, "fileData");
            CC_BREAK_IF(!DICTOOL->checkObjectExist_json(fileData));
            file = DICTOOL->getStringValue_json(fileData, "path");
            plist = DICTOOL->getStringValue_json(fileData, "plistFile");
            CC_BREAK_IF(file == nullptr && plist == nullptr);
            resType = DICTOOL->getIntValue_json(fileData, "resourceType", -1);
        }
        else if(cocoNode != nullptr)
        {
            className = cocoNode[1].GetValue(cocoLoader);
            CC_BREAK_IF(className == nullptr);
            comName = cocoNode[2].GetValue(cocoLoader);
            stExpCocoNode *pfileData = cocoNode[4].GetChildArray(cocoLoader);
            CC_BREAK_IF(!pfileData);
            file = pfileData[0].GetValue(cocoLoader);
            plist = pfileData[1].GetValue(cocoLoader);
            CC_BREAK_IF(file == nullptr && plist == nullptr);
            resType = atoi(pfileData[2].GetValue(cocoLoader));
        }
        if (comName != nullptr)
        {
            setName(comName);
        }
        else
        {
            setName(className);
        }
        
        if (file != nullptr)
        {
            filePath.assign(cocos2d::FileUtils::getInstance()->fullPathForFilename(file));
        }
        if (plist != nullptr)
        {
            plistPath.assign(cocos2d::FileUtils::getInstance()->fullPathForFilename(plist));
        }
        if (resType == 0)
        {
            if (strcmp(className, "CCSprite") == 0 && (filePath.find(".png") != filePath.npos || filePath.find(".pvr.ccz") != filePath.npos))
            {
                _render = Sprite::create(filePath);
                _render->retain();
                
                ret = true;
            }
            else if(strcmp(className, "CCTMXTiledMap") == 0 && filePath.find(".tmx") != filePath.npos)
            {
                _render = TMXTiledMap::create(filePath);
                _render->retain();
                
                ret = true;
            }
            else if(strcmp(className, "CCParticleSystemQuad") == 0 && filePath.find(".plist") != filePath.npos)
            {
                _render = ParticleSystemQuad::create(filePath);
                _render->setPosition(0.0f, 0.0f);
                _render->retain();
                
                ret = true;
            }
            else if(strcmp(className, "CCArmature") == 0)
            {
                std::string fileExtension = FileUtils::getInstance()->getFileExtension(filePath);
                if (fileExtension == ".json" || fileExtension == ".exportjson")
                {
                    rapidjson::Document doc;
                    if(!readJson(filePath, doc))
                    {
                        log("read json file[%s] error!\n", filePath.c_str());
                        continue;
                    }
                    const rapidjson::Value &subData = DICTOOL->getDictionaryFromArray_json(doc, "armature_data", 0);
                    const char *name = DICTOOL->getStringValue_json(subData, "name");
                    ArmatureDataManager::getInstance()->addArmatureFileInfo(filePath);
                    Armature *pAr = Armature::create(name);
                    _render = pAr;
                    _render->retain();
                    const char *actionName = nullptr;
                    if (cocoNode != nullptr)
                    {
                        actionName = cocoNode[6].GetValue(cocoLoader);//DICTOOL->getStringValue_json(*v, "selectedactionname");
                    }
                    else
                    {
                        actionName = DICTOOL->getStringValue_json(*v, "selectedactionname");
                    }
                    if (actionName != nullptr && pAr->getAnimation() != nullptr)
                    {
                        pAr->getAnimation()->play(actionName);
                    }
                    ret = true;
                }
                else if (fileExtension == ".csb")
                {
                    std::string binaryFilePath = FileUtils::getInstance()->fullPathForFilename(filePath);
                    auto fileData = FileUtils::getInstance()->getDataFromFile(binaryFilePath);
                    auto fileDataBytes = fileData.getBytes();
                    CC_BREAK_IF(fileData.isNull());
                    CocoLoader tCocoLoader;
                    if (tCocoLoader.ReadCocoBinBuff((char*)fileDataBytes))
                    {
                        stExpCocoNode *tpRootCocoNode = tCocoLoader.GetRootCocoNode();
                        rapidjson::Type tType = tpRootCocoNode->GetType(&tCocoLoader);
                        if (rapidjson::kObjectType  == tType)
                        {
                            int count = tpRootCocoNode->GetChildNum();
                            stExpCocoNode *tpChildArray = tpRootCocoNode->GetChildArray(&tCocoLoader);
                            for (int i = 0; i < count; ++i)
                            {
                                std::string key = tpChildArray[i].GetName(&tCocoLoader);
                                if (key.compare("armature_data") == 0)
                                {
                                    int length = tpChildArray[i].GetChildNum();
                                    stExpCocoNode *armature_dataArray = tpChildArray[i].GetChildArray(&tCocoLoader);
                                    if (length < 1)
                                    {
                                        continue;
                                    }
                                    
                                    length = armature_dataArray[0].GetChildNum();
                                    stExpCocoNode *armature_data = armature_dataArray[0].GetChildArray(&tCocoLoader);
                                    for (int j = 0; j < length; ++j)
                                    {
                                        std::string key1 = armature_data[j].GetName(&tCocoLoader);
                                        const char *str1 = armature_data[j].GetValue(&tCocoLoader);
                                        if (key.compare("name") == 0)
                                        {
                                            if (str1 != nullptr)
                                            {
                                                ArmatureDataManager::getInstance()->addArmatureFileInfo(filePath);
                                                Armature *pAr = Armature::create(str1);
                                                _render = pAr;
                                                _render->retain();
                                                const char *actionName = nullptr;
                                                if (cocoNode != nullptr)
                                                {
                                                    actionName = cocoNode[6].GetValue(&tCocoLoader);
                                                }
                                                else
                                                {
                                                    actionName = DICTOOL->getStringValue_json(*v, "selectedactionname");
                                                }
                                                if (actionName != nullptr && pAr->getAnimation() != nullptr)
                                                {
                                                    pAr->getAnimation()->play(actionName);
                                                }
                                                ret = true;
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
            else if(strcmp(className, "GUIComponent") == 0)
            {
                std::string fileExtension = FileUtils::getInstance()->getFileExtension(filePath);
                if (fileExtension == ".json" || fileExtension == ".exportjson")
                {
                    cocos2d::ui::Widget* widget = GUIReader::getInstance()->widgetFromJsonFile(filePath.c_str());
                    _render = widget;
                    _render->retain();
                    
                    ret = true;
                }
                else if (fileExtension == ".csb")
                {
                    cocos2d::ui::Widget* widget = GUIReader::getInstance()->widgetFromBinaryFile(filePath.c_str());
                    _render = widget;
                    _render->retain();
                    
                    ret = true;
                }
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
                SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistPath, strPngFile);
                _render = Sprite::createWithSpriteFrameName(filePath);
                _render->retain();
                
                ret = true;
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
    
    return ret;
}

ComRender* ComRender::create()
{
    ComRender * ret = new (std::nothrow) ComRender();
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
    ComRender * ret = new (std::nothrow) ComRender(node, comName);
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
