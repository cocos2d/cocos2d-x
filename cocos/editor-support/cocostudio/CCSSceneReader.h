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
 @类名 SceneReader
 @主题 用于解析cocos studio 1.x导出的json与二进制数据
 @细节 根据json，二进制文件反序列化出cocos2d-x对象结构树
 @组 加载器（reader）
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
    @主题 获取SceneReader单例指针
    @返回 SceneReader单例指针
    */
    static SceneReader* getInstance();
    /**
     *  @js purge
     *  @lua destroySceneReader
     */
    /**
    @主题 销毁SceneReader单例指针，销毁DictionaryHelper单例指针， 销毁TriggerMng单例指针 销毁SimpleAudioEngine单例指针
    @返回 无
    */
    static void destroyInstance();
    /**
    @主题 返回SceneReader版本
    @返回 SceneReader版本号字符串
    */
    static const char* sceneReaderVersion();
    /**
    @主题 根据二进制或者json路径和结构树构建类型，创建场景
    @参数 fileName 1.x导出数据路径
    @参数 attachComponent 对象结构树构建类型
    @返回 场景节点指针
    */
    cocos2d::Node* createNodeWithSceneFile(const std::string &fileName, AttachComponentType attachComponent = AttachComponentType::EMPTY_NODE);
    /**
    @主题 设置每个组件创建完毕后回调方法
    @参数 selector 回调方法
    @返回 无
    */
    void setTarget(const std::function<void(cocos2d::Ref* obj, void* doc)>& selector);
    /**
    @主题 根据nTag获取场景对象结构树node指针
    @参数 nTag 逻辑表示
    @返回 node指针
    */
    cocos2d::Node* getNodeByTag(int nTag);
    /**
    @主题 获取场景对象结构树构建类型
    @返回 场景对象结构树构建类型
    */
    inline AttachComponentType getAttachComponentType(){return _attachComponent;}
CC_CONSTRUCTOR_ACCESS:
    /**
    @主题 SceneReader构造函数
    */
    SceneReader(void);
    /**
    @主题 SceneReader析构函数
    */
    virtual ~SceneReader(void);
    
private:
    /**
    @主题 根据类名获取组件名称，构建场景树调用
    @参数 name 引擎对象类名
    @返回 组件名称
    */
    std::string getComponentClassName(const std::string& name);
   /**
    @主题 根据类名创建组件
    @参数 name 引擎对象类名
    @返回 组件名称
    */
    cocos2d::Component* createComponent(const std::string classname);

    /**
    @主题 创建场景结构树node对象
    @参数 dict cocos studio 1.x导出json对象
    @参数 parent 父node指针
    @参数 场景结构构建类型
    @返回 结构树node对象
    */
    cocos2d::Node* createObject(const rapidjson::Value& dict, cocos2d::Node* parent, AttachComponentType attachComponent);
   /**
    @主题 设置node对象属性
    @参数 dict json对象
    @参数 node node指针
    @返回 无
    */
    void setPropertyFromJsonDict(const rapidjson::Value& dict, cocos2d::Node *node);
    /**
    @主题 解析cocos studio 1.x 场景编辑器导出的json数据，给doc赋值
    @参数 fileName cocos studio 1.x 场景编辑器导出的json名称
    @参数 doc json对象
    @返回 true 解析json成功，否则解析json失败
    */
    bool readJson(const std::string &fileName, rapidjson::Document& doc);

    /**
    @主题 创建场景结构树node对象
    @参数 cocoLoader cocos studio 1.x导出二进制数据加载器对象
    @参数 cocoNode cocos studio 1.x导出二进制数据node对象
    @参数 parent 父node指针
    @参数 场景结构构建类型
    @返回 结构树node对象
    */
    cocos2d::Node* createObject(CocoLoader *cocoLoader, stExpCocoNode *cocoNode, cocos2d::Node* parent, AttachComponentType attachComponent);
    /**
    @主题 创建场景结构树node对象
    @参数 cocoLoader cocos studio 1.x导出二进制数据加载器对象
    @参数 cocoNode cocos studio 1.x导出二进制数据node对象
    @参数 parent 父node指针
    @参数 场景结构构建类型
    @返回 结构树node对象
    */
    void setPropertyFromJsonDict(CocoLoader *cocoLoader, stExpCocoNode *cocoNode, cocos2d::Node *node);
    /**
    @主题 根据tag和parent指针，在parent的孩子中间根据tag匹配获取node指针
    @参数 parent node指针
    @参数 nTag 逻辑表示
    @返回 node指针
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
