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
 @���� SceneReader
 @���� ���ڽ���cocos studio 1.x������json�����������
 @ϸ�� ����json���������ļ������л���cocos2d-x����ṹ��
 @�� ��������reader��
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
    @���� ��ȡSceneReader����ָ��
    @���� SceneReader����ָ��
    */
    static SceneReader* getInstance();
    /**
     *  @js purge
     *  @lua destroySceneReader
     */
    /**
    @���� ����SceneReader����ָ�룬����DictionaryHelper����ָ�룬 ����TriggerMng����ָ�� ����SimpleAudioEngine����ָ��
    @���� ��
    */
    static void destroyInstance();
    /**
    @���� ����SceneReader�汾
    @���� SceneReader�汾���ַ���
    */
    static const char* sceneReaderVersion();
    /**
    @���� ���ݶ����ƻ���json·���ͽṹ���������ͣ���������
    @���� fileName 1.x��������·��
    @���� attachComponent ����ṹ����������
    @���� �����ڵ�ָ��
    */
    cocos2d::Node* createNodeWithSceneFile(const std::string &fileName, AttachComponentType attachComponent = AttachComponentType::EMPTY_NODE);
    /**
    @���� ����ÿ�����������Ϻ�ص�����
    @���� selector �ص�����
    @���� ��
    */
    void setTarget(const std::function<void(cocos2d::Ref* obj, void* doc)>& selector);
    /**
    @���� ����nTag��ȡ��������ṹ��nodeָ��
    @���� nTag �߼���ʾ
    @���� nodeָ��
    */
    cocos2d::Node* getNodeByTag(int nTag);
    /**
    @���� ��ȡ��������ṹ����������
    @���� ��������ṹ����������
    */
    inline AttachComponentType getAttachComponentType(){return _attachComponent;}
CC_CONSTRUCTOR_ACCESS:
    /**
    @���� SceneReader���캯��
    */
    SceneReader(void);
    /**
    @���� SceneReader��������
    */
    virtual ~SceneReader(void);
    
private:
    /**
    @���� ����������ȡ������ƣ���������������
    @���� name �����������
    @���� �������
    */
    std::string getComponentClassName(const std::string& name);
   /**
    @���� ���������������
    @���� name �����������
    @���� �������
    */
    cocos2d::Component* createComponent(const std::string classname);

    /**
    @���� ���������ṹ��node����
    @���� dict cocos studio 1.x����json����
    @���� parent ��nodeָ��
    @���� �����ṹ��������
    @���� �ṹ��node����
    */
    cocos2d::Node* createObject(const rapidjson::Value& dict, cocos2d::Node* parent, AttachComponentType attachComponent);
   /**
    @���� ����node��������
    @���� dict json����
    @���� node nodeָ��
    @���� ��
    */
    void setPropertyFromJsonDict(const rapidjson::Value& dict, cocos2d::Node *node);
    /**
    @���� ����cocos studio 1.x �����༭��������json���ݣ���doc��ֵ
    @���� fileName cocos studio 1.x �����༭��������json����
    @���� doc json����
    @���� true ����json�ɹ����������jsonʧ��
    */
    bool readJson(const std::string &fileName, rapidjson::Document& doc);

    /**
    @���� ���������ṹ��node����
    @���� cocoLoader cocos studio 1.x�������������ݼ���������
    @���� cocoNode cocos studio 1.x��������������node����
    @���� parent ��nodeָ��
    @���� �����ṹ��������
    @���� �ṹ��node����
    */
    cocos2d::Node* createObject(CocoLoader *cocoLoader, stExpCocoNode *cocoNode, cocos2d::Node* parent, AttachComponentType attachComponent);
    /**
    @���� ���������ṹ��node����
    @���� cocoLoader cocos studio 1.x�������������ݼ���������
    @���� cocoNode cocos studio 1.x��������������node����
    @���� parent ��nodeָ��
    @���� �����ṹ��������
    @���� �ṹ��node����
    */
    void setPropertyFromJsonDict(CocoLoader *cocoLoader, stExpCocoNode *cocoNode, cocos2d::Node *node);
    /**
    @���� ����tag��parentָ�룬��parent�ĺ����м����tagƥ���ȡnodeָ��
    @���� parent nodeָ��
    @���� nTag �߼���ʾ
    @���� nodeָ��
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
