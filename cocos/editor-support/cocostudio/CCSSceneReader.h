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

#ifndef __CCSSCENEREADER_H__
#define __CCSSCENEREADER_H__

#include "cocostudio/DictionaryHelper.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {

/** 
 * @class SceneReader
 * @brief @~english Reader of parsing export data of cocos studio 1.x scene reader.
 * @~chinese cocos studio 1.x 场景编辑器导出数据解析器。
*/
class CC_STUDIO_DLL SceneReader
{
public:

    enum class AttachComponentType
    {
        ///parent: Empty Node
        ///            ComRender(Sprite, Armature, TMXTiledMap, ParticleSystemQuad, GUIComponent)
        ///            ComAttribute
        ///            ComAudio
        ///            ....
        EMPTY_NODE,
        
        ///parent:   ComRender(Sprite, Armature, TMXTiledMap, ParticleSystemQuad, GUIComponent)
        ///          ComAttribute
        ///          ComAudio
        ///          .....
        RENDER_NODE,
        
        /// Default AttachComponentType is _EmptyNode
        DEFAULT = EMPTY_NODE,
    };

    /**
     * @brief @~english Get instance point of SceneReader.
     * @~chinese SceneReader单例指针。
     */
    static SceneReader* getInstance();

    /**
     * @brief @~english Destroy instance point of SceneReader.
     * @~chinese 销毁SceneReader单例指针。
     *  @js purge
     *  @lua destroySceneReader
     */
    static void destroyInstance();

    /**
     * @brief @~english Get version string of SceneReader.
     * @~chinese SceneReader版本号字符串。
     */
    static const char* sceneReaderVersion();

    /**
     * @brief @~english Create a scene with json or binary file path and type of attach component.
     * @~chinese 根据二进制或者json路径和结构树构建类型，创建场景。
     * @param fileName @~english Json or binary file path
     * @~chinese json或者二进制文件路径
     * @param attachComponent @~english Type of attach component
     * @~chinese 对象结构树构建类型
     *  @js purge
     *  @lua destroySceneReader
     */
    cocos2d::Node* createNodeWithSceneFile(const std::string &fileName, AttachComponentType attachComponent = AttachComponentType::EMPTY_NODE);

    /**
     * @brief @~english Call selector after each of the components created.
     * @~chinese 设置每个组件创建完毕后回调方法。
     * @param @~english Callback function of selector
     * @~chinese selector 回调方法
     */
    void setTarget(const std::function<void(cocos2d::Ref* obj, void* doc)>& selector);

    /**
     * @brief @~english Get Node point by tag.
     * @~chinese 根据nTag获取node指针。
     * @param tag @~english Tag of node.
     * @~chinese node的tag。
     * @return @~english Node point by tag.
     * @~chinese 根据tag返回node指针。
     */
    cocos2d::Node* getNodeByTag(int nTag);

    /**
     * @brief @~english Get the type of attach component.
     * @~chinese 获取场景对象结构树构建类型。
     */
    inline AttachComponentType getAttachComponentType(){return _attachComponent;}
CC_CONSTRUCTOR_ACCESS:

    /**
     * @brief @~english SceneReader constructor.
     * @~chinese SceneReader构造函数。
     * @js ctor
     */
    SceneReader(void);

    /**
     * @brief @~english SceneReader destructor.
     * @~chinese SceneReader析构函数。
     */
    virtual ~SceneReader(void);
    
private:
    /**
     * @brief @~english Get component name with class name.
     * @~chinese 根据类名获取组件名称。
     * @param @~english Component name
     * @~chinese 组件名称
     */
    std::string getComponentClassName(const std::string& name);

    /**
     * @brief @~english Create component point with class name.
     * @~chinese 根据类名创建组件。
     * @param classname @~english Class name.
     * @~chinese 类名。
     * @return @~english Component point.
     * @~chinese 组件指针。
     */
    cocos2d::Component* createComponent(const std::string classname);

    /**
     * @brief @~english Create node object and add it to parent node with json file path.
     * @~chinese 创建场景结构树node对象。
     * @param dict @~english Json object.
     * @~chinese json对象。
     * @param parent @~english Parent node point.
     * @~chinese 父类node指针。
     * @param attachComponent @~english Type of attach component
     * @~chinese 对象结构树构建类型
     * @return @~english Node object point.
     * @~chinese node对象指针。
     */
    cocos2d::Node* createObject(const rapidjson::Value& dict, cocos2d::Node* parent, AttachComponentType attachComponent);

    /**
     * @brief @~english Set property of node.
     * @~chinese 设置node对象属性。
     * @param dict @~english Json object.
     * @~chinese json对象。
     * @param node @~english Node point.
     * @~chinese node指针。
     */
    void setPropertyFromJsonDict(const rapidjson::Value& dict, cocos2d::Node *node);

     /**
     * @brief @~english Parse export json data of cocos studio 1.x Scene Editor and assign to doc.
     * @~chinese 解析cocos studio 1.x 场景编辑器导出json数据，判断json的有效性，给json对象doc赋值。
     * @param fileName @~english Json file path.
     * @~chinese json路径。
     * @param doc @~english Json data object
     * @~chinese json数据对象。
     * @return @~english true parse successfully, false failed to parse.
     * @~chinese true 解析成功，否则false。
     */
    bool readJson(const std::string &fileName, rapidjson::Document& doc);

    /**
     * @brief @~english Create node object and add it to parent node by binary file path.
     * @~chinese 创建场景结构树node对象。
     * @param cocoLoader @~english Loader scene object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x场景编辑器导出二进制数据加载器对象。
     * @param cocoNode @~english Loader node object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x场景编辑器导出二进制数据node对象。
     * @param parent @~english Parent node point.
     * @~chinese 父node指针。
     * @param attachComponent @~english Type of attach component
     * @~chinese 对象结构树构建类型
     * @return @~english Node object point.
     * @~chinese node对象指针。
     */
    cocos2d::Node* createObject(CocoLoader *cocoLoader, stExpCocoNode *cocoNode, cocos2d::Node* parent, AttachComponentType attachComponent);

    /**
     * @brief @~english Create node object and add it to parent node with binary file path.
     * @~chinese 创建场景结构树node对象。
     * @param cocoLoader @~english Loader scene object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x场景编辑器导出二进制数据加载器对象。
     * @param cocoNode @~english Loader node object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x场景编辑器导出二进制数据node对象。
     * @param node @~english Node point.
     * @~chinese node指针。
     */
    void setPropertyFromJsonDict(CocoLoader *cocoLoader, stExpCocoNode *cocoNode, cocos2d::Node *node);

    /**
     * @brief @~english get Node point by tag based on its parent node point.
     * @~chinese 根据tag和parent指针，在parent的孩子中间根据tag匹配获取node指针。
     * @param parent @~english Parent node point.
     * @~chinese 父node指针。
     * @param tag @~english Tag of node.
     * @~chinese node的tag。
     * @return @~english Node point by tag.
     * @~chinese 根据tag返回node指针。
     */
    cocos2d::Node* nodeByTag(cocos2d::Node *parent, int tag);
private:
    static SceneReader* s_sharedReader;
    std::function<void(cocos2d::Ref* obj, void* doc)> _fnSelector;
    cocos2d::Node*      _node;
    AttachComponentType _attachComponent;
};


}

#endif
