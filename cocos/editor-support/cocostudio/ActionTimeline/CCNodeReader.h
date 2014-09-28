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

#ifndef __CC_NODE_CACHE_H__
#define __CC_NODE_CACHE_H__

#include <unordered_map>
#include "cocostudio/DictionaryHelper.h"
#include "cocostudio/CocosStudioExport.h"
#include "2d/CCNode.h"

namespace protocolbuffers
{
    class NodeTree;
	class WidgetOptions;
    class SpriteOptions;
}

namespace cocostudio {


namespace timeline{

class CC_STUDIO_DLL NodeReader
{
public:
    static NodeReader* getInstance();
    static void destroyInstance();

    NodeReader();
    void purge();

    void init();

    cocos2d::Node* createNode(const std::string& filename);

    cocos2d::Node* loadNodeWithFile(const std::string& fileName);
    cocos2d::Node* loadNodeWithContent(const std::string& content);

    void setRecordJsonPath(bool record) { _recordJsonPath = record; }
    bool isRecordJsonPath() const { return _recordJsonPath; }

    void setJsonPath(std::string jsonPath) { _jsonPath = jsonPath; }
    std::string getJsonPath() const { return _jsonPath; }
    
    cocos2d::Node* createNodeFromProtocolBuffers(const std::string& filename);
    cocos2d::Node* nodeFromProtocolBuffersFile(const std::string& fileName);
    cocos2d::Node* nodeFromProtocolBuffers(const protocolbuffers::NodeTree& nodetree);
    
    void setRecordProtocolBuffersPath(bool record) { _recordProtocolBuffersPath = record; }
    bool isRecordProtocolBuffersPath() const { return _recordProtocolBuffersPath; }
    
    void setProtocolBuffersPath(std::string protocolBuffersPath) { _protocolBuffersPath = protocolBuffersPath; }
    std::string getProtocolBuffersPath() const { return _protocolBuffersPath; }

protected:

    cocos2d::Node* loadNode(const rapidjson::Value& json);
    
    void locateNodeWithMulresPosition(cocos2d::Node* node, const rapidjson::Value& json);

    void initNode(cocos2d::Node* node, const rapidjson::Value& json);

    // load nodes
    cocos2d::Node* loadSimpleNode(const rapidjson::Value& json);
    cocos2d::Node* loadSubGraph  (const rapidjson::Value& json);
    cocos2d::Node* loadSprite    (const rapidjson::Value& json);
    cocos2d::Node* loadParticle  (const rapidjson::Value& json);

    // load gui
    cocos2d::Node* loadWidget(const rapidjson::Value& json);
    
    void setPropsForNodeFromProtocolBuffers(cocos2d::Node* node, const protocolbuffers::WidgetOptions& nodeOptions);
    void setPropsForSpriteFromProtocolBuffers(cocos2d::Node* node,
                                              const protocolbuffers::SpriteOptions& spriteOptions,
                                              const protocolbuffers::WidgetOptions& nodeOptions);
    
    bool isWidget(const std::string& type);
    bool isCustomWidget(const std::string& type);
    
    std::string getGUIClassName(const std::string &name);
    std::string getWidgetReaderClassName(cocos2d::ui::Widget *widget);

    typedef std::function<cocos2d::Node*(const rapidjson::Value& json)> NodeCreateFunc;
    typedef std::pair<std::string, NodeCreateFunc> Pair;

    std::unordered_map<std::string, NodeCreateFunc> _funcs;

    bool _recordJsonPath;

    std::string _jsonPath;
    
    bool _recordProtocolBuffersPath;
    std::string _protocolBuffersPath;
    
    std::string _monoCocos2dxVersion;
};

}
}


#endif /*__CC_NODE_CACHE_H__*/
