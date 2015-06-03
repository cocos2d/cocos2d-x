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
#ifndef __TRIGGERMNG_H__
#define __TRIGGERMNG_H__

#include "CocoStudio.h"

namespace cocos2d {
class EventDispatcher;
class EventListener;
}

namespace cocostudio {

class TriggerObj;

 /** 
 @类名 ArmatureMovementDispatcher
 @主题 Armature运行状态事件分发器
 @细节 把Armature的运行状态发送给触发器，用来判断条件判断与动作触发
 @组 触发器
 */
class CC_STUDIO_DLL ArmatureMovementDispatcher : public cocos2d::Ref
{
public:
	ArmatureMovementDispatcher(void);
	~ArmatureMovementDispatcher(void);
public:
    /**
    @主题 为触发器对象增加事件回调
    @参数 pTarget 触发器对象指针
    @参数 mecf 回调函数
    @返回 无
    */
    void addAnimationEventCallBack(cocos2d::Ref*pTarget, SEL_MovementEventCallFunc mecf);
    /**
    @主题 移除触发器对象事件回调
    @参数 pTarget 触发器对象指针
    @参数 mecf 回调函数
    @返回 无
    */
    void removeAnnimationEventCallBack(cocos2d::Ref*pTarget, SEL_MovementEventCallFunc mecf);
    /**
    @主题 提供给Armature进行事件回调的方法
    @参数 armature Armature指针
    @参数 movementType 移动事件类型
    @参数 movementID 动作ID
    @返回 无
    */
    void animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
    
private:
	std::unordered_map<cocos2d::Ref*, SEL_MovementEventCallFunc> *_mapEventAnimation;

};

 /** 
 @类名 TriggerMng
 @主题 触发器系统管理器
 @细节 负责根据cocos studio 1.x编辑器导出数据构建触发器，负责事件分发，管理所有触发器的生命周期
 @组 触发器
 */
class CC_STUDIO_DLL TriggerMng
{
public:
    /**
    @主题 TriggerMng构造函数
    */
    TriggerMng(void);
    /**
    @主题 TriggerMng析构函数
    */
    virtual ~TriggerMng(void);

public:
    /**
    @主题 获取TriggerMng单例指针
    @返回 TriggerMng单例指针
    */
    static TriggerMng* getInstance();
    /**
    @主题 销毁TriggerMng单例指针
    @返回 无
    */
    static void destroyInstance();
    /**
    @主题 返回TriggerMng版本
    @返回 TriggerMng版本号字符串
    */
    static const char* triggerMngVersion();
    
public:
    /**
    @主题 解析cocos studio 1.x导出的json对象，构建触发器系统
    @参数 root cocos studio 1.x导出的json对象
    @返回 无
    */
    void parse(const rapidjson::Value &root);
    /**
    @主题 解析cocos studio 1.x导出的二进制数据，构建触发器系统
    @参数 cocoLoader cocos studio 1.x导出二进制数据加载器对象
    @参数 cocoNode cocos studio 1.x导出二进制数据node对象
    @返回 无
    */
    void parse(cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode);
    /**
    @主题 移除所有触发器
    @返回 无
    */
    void removeAll(void);
    /**
    @主题 根据触发器事件id,获取绑定到这个id上的所有触发器
    @参数 event 触发器事件id
    @返回 绑定到事件id的所有触发器
    */
    cocos2d::Vector<TriggerObj*>* get(unsigned int event) const;
   /**
    @主题 根据触发器id,获取触发器
    @参数 id 触发器id
    @返回 获取触发器
    */
    TriggerObj* getTriggerObj(unsigned int id) const;
    /**
    @主题 根据触发器指针，移除触发器
    @参数 Obj 触发器指针
    @返回 true成功移除，否则false
    */
    bool removeTriggerObj(TriggerObj *Obj);
    /**
    @主题 根据触发器id，移除触发器
    @参数 id 触发器id
    @返回 true成功移除，否则false
    */
    bool removeTriggerObj(unsigned int id);
    /**
    @主题 是否为没有触发器
    @返回 true 没有触发器，否则false
    */
    bool isEmpty(void) const;

    /**
    @主题 为触发器对象绑定Armature事件回调，从而当Armature有事件发生，触发器对象也可以获得
    @参数 pAr Armature
    @参数 pTarget 触发器对象指针
    @参数 mecf 回调函数
    @返回 无
    */
    void addArmatureMovementCallBack(Armature *pAr, cocos2d::Ref *pTarget, SEL_MovementEventCallFunc mecf);
    /**
    @主题 移除绑定在Armature的触发器对象事件回调
    @参数 pAr Armature
    @参数 pTarget 触发器对象指针
    @参数 mecf 回调函数
    @返回 无
    */
    void removeArmatureMovementCallBack(Armature *pAr, cocos2d::Ref *pTarget, SEL_MovementEventCallFunc mecf);
    /**
    @主题 移除绑定到指定Armature的触发器事件回调
    @参数 pAr Armature
    @返回 无
    */
    void removeArmatureAllMovementCallBack(Armature *pAr);
    /**
    @主题 移除绑定到所有Armature的触发器事件回调
    @参数 pAr Armature
    @返回 无
    */
    void removeAllArmatureMovementCallBack();
    /**
    @主题 分发触发器事件
    @参数 tEvent 触发器事件
    @返回 无
    */
    void dispatchEvent(cocos2d::EventCustom* tEvent);
    /**
    @主题 移除触发器事件监听器
    @参数 listener 触发器监听器
    @返回 无
    */
    void removeEventListener(cocos2d::EventListener* listener);
   /**
    @主题 增加触发器事件监听器，并制定接收优先级
    @参数 listener 触发器监听器
    @参数 fixedPriority 触发器监听器接收优先级
    @返回 无
    */
    void addEventListenerWithFixedPriority(cocos2d::EventListener* listener, int fixedPriority);
private:
    /**
    @主题 根据cocos studio 1.x导出的二进制对象转换为json对象，用于lua调用
    @参数 document json对象
    @参数 pCocoLoader cocos studio 1.x导出二进制数据加载器对象
    @参数 pCocoNode cocos studio 1.x导出二进制数据node对象
    @返回 无
    */
    void buildJson(rapidjson::Document &document, cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode);

private:
    static TriggerMng *_sharedTriggerMng;
    std::unordered_map<unsigned int, TriggerObj*> _triggerObjs;
    std::unordered_map<Armature*, ArmatureMovementDispatcher*> *_movementDispatches;
    cocos2d::EventDispatcher* _eventDispatcher;  ///< event dispatcher used to dispatch all kinds of events
};

}

#endif
