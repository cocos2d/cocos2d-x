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

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "ObjectFactory.h"

using namespace cocos2d;
using namespace ui;

namespace cocostudio {

SceneReader* SceneReader::s_sharedReader = nullptr;

SceneReader::SceneReader()
: _fnSelector(nullptr)
, _node(nullptr)
, _attachComponent(AttachComponentType::EMPTY_NODE)
{
    ObjectFactory::getInstance()->registerType(CREATE_CLASS_COMPONENT_INFO(ComAttribute));
    ObjectFactory::getInstance()->registerType(CREATE_CLASS_COMPONENT_INFO(ComRender));
    ObjectFactory::getInstance()->registerType(CREATE_CLASS_COMPONENT_INFO(ComAudio));
	ObjectFactory::getInstance()->registerType(CREATE_CLASS_COMPONENT_INFO(ComController));
}

SceneReader::~SceneReader()
{
}

const char* SceneReader::sceneReaderVersion()
{
    return "1.0.0.0";
}

cocos2d::Node* SceneReader::createNodeWithSceneFile(const std::string &fileName, AttachComponentType attachComponent /*= AttachComponentType::EMPTY_NODE*/)
{
    _node = nullptr;
    rapidjson::Document jsonDict;
    do {
          CC_BREAK_IF(!readJson(fileName, jsonDict));
          _node = createObject(jsonDict, nullptr, attachComponent);
          TriggerMng::getInstance()->parse(jsonDict);
    } while (0);
    
    return _node;
}

bool SceneReader::readJson(const std::string &fileName, rapidjson::Document &doc)
{
    bool bRet = false;
    do {
        std::string jsonpath = FileUtils::getInstance()->fullPathForFilename(fileName);
        std::string contentStr = FileUtils::getInstance()->getStringFromFile(jsonpath);
        doc.Parse<0>(contentStr.c_str());
        CC_BREAK_IF(doc.HasParseError());
        bRet = true;
    } while (0);
    return bRet;
}

Node* SceneReader::nodeByTag(Node *parent, int tag)
{		
    if (parent == nullptr)
    {
        return nullptr;
    }
    Node *_retNode = nullptr;
    Vector<Node*>& Children = parent->getChildren();
    Vector<Node*>::iterator iter = Children.begin();
    while (iter != Children.end())
    {
        Node* pNode = *iter;
        if(pNode != nullptr && pNode->getTag() == tag)
        {
            _retNode =  pNode;
            break;
        }
        else
        {
            _retNode = nodeByTag(pNode, tag);
            if (_retNode != nullptr)
            {
                break;
            }

        }
        ++iter;
    }
    return _retNode;
}


Node* SceneReader::createObject(const rapidjson::Value &dict, cocos2d::Node* parent, AttachComponentType attachComponent)
{
    const char *className = DICTOOL->getStringValue_json(dict, "classname");
    if(strcmp(className, "CCNode") == 0)
    {
        Node* gb = nullptr;
        if(nullptr == parent)
        {
            gb = Node::create();
        }

        std::vector<Component*> vecComs;
        ComRender *render = nullptr;
        int count = DICTOOL->getArrayCount_json(dict, "components");
        for (int i = 0; i < count; i++)
        {
            const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(dict, "components", i);
            if (!DICTOOL->checkObjectExist_json(subDict))
            {
                break;
            }
            const char *comName = DICTOOL->getStringValue_json(subDict, "classname");
            Component *com = ObjectFactory::getInstance()->createComponent(comName);
            if (com != nullptr)
            {
                if (com->serialize((void*)(&subDict)))
                {
                    ComRender *tRender = dynamic_cast<ComRender*>(com);
                    if (tRender == nullptr)
                    {
                        vecComs.push_back(com);
                    }
                    else
                    {
                        render = tRender;
                    }
                }
            }
            if(_fnSelector != nullptr)
            {
                _fnSelector(com, (void*)(&subDict));
            }
        }

        if (parent != nullptr)
        {
            if (render == nullptr || attachComponent == AttachComponentType::EMPTY_NODE)
            {
                gb = Node::create();
                if (render != nullptr)
                {
                    vecComs.push_back(render);
                }
            }
            else
            {
                gb = render->getNode();
                gb->retain();
                render->setNode(nullptr);
            }
            parent->addChild(gb);
        }

        setPropertyFromJsonDict(dict, gb);
        for (std::vector<Component*>::iterator iter = vecComs.begin(); iter != vecComs.end(); ++iter)
        {
              gb->addComponent(*iter);
        }

        int length = DICTOOL->getArrayCount_json(dict, "gameobjects");
        for (int i = 0; i < length; ++i)
        {
            const rapidjson::Value &subDict = DICTOOL->getSubDictionary_json(dict, "gameobjects", i);
            if (!DICTOOL->checkObjectExist_json(subDict))
            {
                break;
            }
            createObject(subDict, gb, attachComponent);
        }
        
        return gb;
    }
    
    return nullptr;
}

void SceneReader::setTarget(const std::function<void(cocos2d::Ref* obj, void* doc)>& selector)
{
    _fnSelector = selector;
}

Node* SceneReader::getNodeByTag(int nTag)
{
    if (_node == nullptr)
    {
        return nullptr;
    }
    if (_node->getTag() == nTag)
    {
        return _node;
    }
    return nodeByTag(_node, nTag);
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
    node->setLocalZOrder(nZorder);
    
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
    CocosDenshion::SimpleAudioEngine::end();
    CC_SAFE_DELETE(s_sharedReader);
}

}
