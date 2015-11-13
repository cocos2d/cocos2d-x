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

#ifndef __cocos2d_libs__CSLoader__
#define __cocos2d_libs__CSLoader__

#include "cocostudio/DictionaryHelper.h"
#include "cocostudio/CocosStudioExport.h"
#include "cocos2d.h"
#include "base/ObjectFactory.h"

namespace flatbuffers
{
    class FlatBufferBuilder;
    
    struct NodeTree;
    
    struct WidgetOptions;
    struct SingleNodeOptions;
    struct SpriteOptions;
    struct ParticleSystemOptions;
    struct TMXTiledMapOptions;
    struct ProjectNodeOptions;
    
    struct ComponentOptions;
    struct ComAudioOptions;
}

namespace cocostudio
{
    class ComAudio;
}

namespace cocostudio
{
    namespace timeline
    {
        class ActionTimeline;
        class ActionTimelineNode;
    }
}

NS_CC_BEGIN

typedef std::function<void(Ref*)> ccNodeLoadCallback;

class CC_STUDIO_DLL CSLoader
{
public:
    /**
    * @~english Get singleton.
    * @~chinese 获取单例。
    * @return @~english Singleton of `CSLoader`.
    * @~chinese `CSLoader`的单例。
    */
    static CSLoader* getInstance();
    /**
    * @~english Destory singleton.
    * @~chinese 销毁单例。
    */
    static void destroyInstance();
    
    CSLoader();
    /** @deprecated Use method destroyInstance() instead */
    CC_DEPRECATED_ATTRIBUTE void purge();    
    
    void init();
    
    /**
    * @~english Create node from binary file.
    * @~chinese 从二进制文件中创建节点。
    * @param filename @~english File name.
    * @~chinese 文件名称。
    * @return @~english Created node.
    * @~chinese 创建出的节点。
    */
    static cocos2d::Node* createNode(const std::string& filename);
    /**
    * @~english Create node from binary file and run specified callback function after creating.
    * @~chinese 从二进制文件中创建节点，在创建完成后调用指定的回调函数。
    * @param filename @~english File name.
    * @~chinese 文件名称。
    * @param filename @~english Specified callback function.
    * @~chinese 指定的回调函数。
    * @return @~english Created node.
    * @~chinese 创建出的节点。
    */
    static cocos2d::Node* createNode(const std::string& filename, const ccNodeLoadCallback& callback);
    static cocos2d::Node* createNode(const Data data);
    static cocos2d::Node* createNode(const Data data, const ccNodeLoadCallback &callback);
    static cocos2d::Node* createNodeWithVisibleSize(const std::string& filename);
    static cocos2d::Node* createNodeWithVisibleSize(const std::string& filename, const ccNodeLoadCallback& callback);

    static cocostudio::timeline::ActionTimeline* createTimeline(const std::string& filename);
    static cocostudio::timeline::ActionTimeline* createTimeline(const Data data, const std::string& filename);

    /*
    static cocostudio::timeline::ActionTimelineNode* createActionTimelineNode(const std::string& filename);
    static cocostudio::timeline::ActionTimelineNode* createActionTimelineNode(const std::string& filename, int startIndex, int endIndex, bool loop);
     */
    
    /**
    * @~english Create node from json file.
    * @~chinese 从Json文件中创建节点。
    * @param filename @~english Json file name.
    * @~chinese Json文件名称。
    * @return @~english Created node.
    * @~chinese 创建出的节点。
    */
    cocos2d::Node* createNodeFromJson(const std::string& filename);
    /**
    * @~english Load node from json file.
    * @~chinese 从Json文件中载入节点。
    * @param filename @~english Json file name.
    * @~chinese Json文件名称。
    * @return @~english Created node.
    * @~chinese 创建出的节点。
    */
    cocos2d::Node* loadNodeWithFile(const std::string& fileName);
    /**
    * @~english Load node from json string.
    * @~chinese 从Json字符串中载入节点。
    * @param content @~english Json string.
    * @~chinese Json字符串。
    * @return @~english Created node.
    * @~chinese 创建出的节点。
    */
    cocos2d::Node* loadNodeWithContent(const std::string& content);
    
    /*
    * @~english Set is record json path.
    * @~chinese 设置是否记录Json路径。
    * @param record @~english Is record json path.
    * @~chinese 是否记录Json路径。
    */
    void setRecordJsonPath(bool record) { _recordJsonPath = record; }
    /*
    * @~english Get is record json path.
    * @~chinese 获取是否记录Json路径。
    * @return @~english Is record json path.
    * @~chinese 是否记录Json路径。
    */
    bool isRecordJsonPath() const { return _recordJsonPath; }
    
    /*
    * @~english Set json path.
    * @~chinese 设置Json路径。
    * @param record @~english Json path.
    * @~chinese Json路径。
    */
    void setJsonPath(std::string jsonPath) { _jsonPath = jsonPath; }
    /*
    * @~english Get json path.
    * @~chinese 获取Json路径。
    * @return @~english Json path.
    * @~chinese Json路径。
    */
    std::string getJsonPath() const { return _jsonPath; }
    
    /**
    * @~english Create node from flatbuffer binary file.
    * @~chinese 从flatbuffer二进制文件中创建节点。
    * @param filename @~english File name.
    * @~chinese 文件名称。
    * @return @~english Created node.
    * @~chinese 创建出的节点。
    */
    cocos2d::Node* createNodeWithFlatBuffersFile(const std::string& filename);
    /**
    * @~english Create node from flatbuffer binary file.
    * @~chinese 从flatbuffer二进制文件中创建节点。
    * @param filename @~english File name.
    * @~chinese 文件名称。
    * @return @~english Created node.
    * @~chinese 创建出的节点。
    */
    cocos2d::Node* nodeWithFlatBuffersFile(const std::string& fileName);
    /**
    * @~english Create node from nodetree.
    * @~chinese 从节点树中创建节点。
    * @param nodetree @~english Node tree.
    * @~chinese 节点树。
    * @return @~english Created node.
    * @~chinese 创建出的节点。
    */
    cocos2d::Node* nodeWithFlatBuffers(const flatbuffers::NodeTree* nodetree);

    
    bool bindCallback(const std::string& callbackName,
                      const std::string& callbackType,
                      cocos2d::ui::Widget* sender,
                      cocos2d::Node* handler);
    
    void registReaderObject(const std::string& className,
                            ObjectFactory::Instance ins);
    
    /**
    * @~english Create node from flatbuffer binary file(for simulator).
    * @~chinese 从flatbuffer二进制文件中创建节点(为模拟器)。
    * @param filename @~english File name.
    * @~chinese 文件名称。
    * @return @~english Created node.
    * @~chinese 创建出的节点。
    */
    cocos2d::Node* createNodeWithFlatBuffersForSimulator(const std::string& filename);
    /**
    * @~english Create node from nodetree(for simulator).
    * @~chinese 从节点树中创建节点(为模拟器)。
    * @param nodetree @~english Node tree.
    * @~chinese 节点树。
    * @return @~english Created node.
    * @~chinese 创建出的节点。
    */
    cocos2d::Node* nodeWithFlatBuffersForSimulator(const flatbuffers::NodeTree* nodetree);

protected:

    cocos2d::Node* createNodeWithFlatBuffersFile(const std::string& filename, const ccNodeLoadCallback& callback);
    cocos2d::Node* nodeWithFlatBuffersFile(const std::string& fileName, const ccNodeLoadCallback& callback);
    cocos2d::Node* nodeWithFlatBuffers(const flatbuffers::NodeTree* nodetree, const ccNodeLoadCallback& callback);
    
    cocos2d::Node* loadNode(const rapidjson::Value& json);
    
    void locateNodeWithMulresPosition(cocos2d::Node* node, const rapidjson::Value& json);
    
    void initNode(cocos2d::Node* node, const rapidjson::Value& json);
    
    // load nodes
    cocos2d::Node* loadSimpleNode(const rapidjson::Value& json);
    cocos2d::Node* loadSubGraph  (const rapidjson::Value& json);
    cocos2d::Node* loadSprite    (const rapidjson::Value& json);
    cocos2d::Node* loadParticle  (const rapidjson::Value& json);
    cocos2d::Node* loadTMXTiledMap(const rapidjson::Value& json);
    
    // load gui
    cocos2d::Node* loadWidget(const rapidjson::Value& json);
    
    // load component
    cocos2d::Component* loadComponent(const rapidjson::Value& json);
    cocos2d::Component* loadComAudio(const rapidjson::Value& json);
    
    bool isWidget(const std::string& type);
    bool isCustomWidget(const std::string& type);
    
    std::string getGUIClassName(const std::string &name);
    std::string getWidgetReaderClassName(cocos2d::ui::Widget *widget);
    
    inline void reconstructNestNode(cocos2d::Node * node);
    static inline std::string getExtentionName(const std::string& name);

    typedef std::function<cocos2d::Node*(const rapidjson::Value& json)> NodeCreateFunc;
    typedef std::pair<std::string, NodeCreateFunc> Pair;
    
    std::unordered_map<std::string, NodeCreateFunc> _funcs;
    
    typedef std::function<cocos2d::Component*(const rapidjson::Value& json)> ComponentCreateFunc;
    typedef std::pair<std::string, ComponentCreateFunc> ComponentPair;
    
    std::unordered_map<std::string, ComponentCreateFunc> _componentFuncs;
    
    bool _recordJsonPath;
    
    std::string _jsonPath;
    
    std::string _monoCocos2dxVersion;
    
    Node* _rootNode;
    cocos2d::Vector<cocos2d::Node*> _callbackHandlers;
    
    std::string _csBuildID;
    
};

NS_CC_END

#endif /* defined(__cocos2d_libs__CSLoader__) */
