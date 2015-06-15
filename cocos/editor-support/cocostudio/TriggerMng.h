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
 * @class ArmatureMovementDispatcher
 * @brief @~english Armature action state dispatcher.
 * @~chinese  Armature运行状态事件分发器。
*/
class CC_STUDIO_DLL ArmatureMovementDispatcher : public cocos2d::Ref
{
public:
    /**
     * @brief @~english ArmatureMovementDispatcher constructor.
     * @~chinese ArmatureMovementDispatcher构造函数。
     */
    ArmatureMovementDispatcher(void);
    /**
     * @brief @~english ArmatureMovementDispatcher destructor.
     * @~chinese ArmatureMovementDispatcher析构函数。
     */
    ~ArmatureMovementDispatcher(void);
public:
    /**
     * @brief @~english Add armature event callback function to trigger object.
     * @~chinese 为触发器对象增加事件回调。
     * @param pTarget @~english Trigger object point.
     * @~chinese 触发器对象指针。
     * @param mecf @~english Callback function.
     * @~chinese 回调函数。
     */
    void addAnimationEventCallBack(cocos2d::Ref *pTarget, SEL_MovementEventCallFunc mecf);

    /**
     * @brief @~english Remove armature event callback function from trigger object.
     * @~chinese 为触发器对象移除事件回调。
     * @param pTarget @~english Trigger object point.
     * @~chinese 触发器对象指针。
     * @param mecf @~english Callback function.
     * @~chinese 回调函数。
     */
    void removeAnnimationEventCallBack(cocos2d::Ref *pTarget, SEL_MovementEventCallFunc mecf);

    /**
     * @brief @~english Animation event callback function.
     * @~chinese Armature事件回调的方法。
     * @param armature @~english Armature object point.
     * @~chinese 1.x骨骼动画对象指针。
     * @param movementType @~english Armature movement type.
     * @~chinese 1.x骨骼动画移动类型。
     * @param movementID @~english Armature movement action id.
     * @~chinese 1.x骨骼动画动作ID。
     */
    void animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID);
    
private:
    std::unordered_map<cocos2d::Ref*, SEL_MovementEventCallFunc> *_mapEventAnimation;

};

/** 
 * @class TriggerMng
 * @brief @~english Trigger manager.
 * @~chinese  Armature运行状态事件分发器。
*/
class CC_STUDIO_DLL TriggerMng
{
public:
    /**
     * @brief @~english TriggerMng constructor.
     * @~chinese TriggerMng构造函数。
     */
    TriggerMng(void);

    /**
     * @brief @~english TriggerMng destructor.
     * @~chinese TriggerMng析构函数。
     */
    virtual ~TriggerMng(void);

public:
    /**
     * @brief @~english Get instance point of TriggerMng.
     * @~chinese TriggerMng单例指针。
     */
    static TriggerMng* getInstance();

    /**
     * @brief @~english Destroy instance point of TriggerMng.
     * @~chinese 销毁TriggerMng单例指针。
     */
    static void destroyInstance();

    /**
     * @brief @~english Get version string of TriggerMng.
     * @~chinese TriggerMng版本号字符串。
     */
    static const char* triggerMngVersion();
    
public:
     /**
     * @brief @~english Parse export json data of cocos studio 1.x Scene Editor.
     * @~chinese 解析cocos studio 1.x 场景编辑器导出json数据。
     * @param root @~english json data object
     * @~chinese json数据对象。
     */
    void parse(const rapidjson::Value &root);

    /**
     * @brief @~english Parse binary data of cocos studio 1.x scene editor.
     * @~chinese 解析cocos studio 1.x导出的二进制数据。
     * @param pCocoLoader @~english loader scene object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x场景编辑器导出二进制数据加载器对象。
     * @param pCocoNode @~english loader node object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x场景编辑器导出二进制数据node对象。
     */
    void parse(cocostudio::CocoLoader *pCocoLoader, cocostudio::stExpCocoNode *pCocoNode);

    /**
     * @brief @~english remove all triggers.
     * @~chinese 移除所有触发器。
     */
    void removeAll(void);

    /**
     * @brief @~english Get triggers with event id.
     * @~chinese 根据触发器事件id,获取绑定到这个id上的所有触发器。
     * @param event @~english Event id.
     * @~chinese 事件id。
     * @return @~english Trigger vector.
     * @~chinese 触发器数组。
     */
    cocos2d::Vector<TriggerObj*>* get(unsigned int event) const;

    /**
     * @brief @~english Get trigger with trigger id.
     * @~chinese 根据触发器id,获取触发器。
     * @param id @~english Trigger unique id.
     * @~chinese 触发器唯一id。
     * @return @~english Trigger point.
     * @~chinese 获取触发器指针。
     */
    TriggerObj* getTriggerObj(unsigned int id) const;

    /**
     * @brief @~english Remove trigger with trigger point.
     * @~chinese 根据触发器指针，移除触发器。
     * @param Obj @~english Trigger point.
     * @~chinese 触发器指针。
     * @return @~english true remove successfully false failed to remove .
     * @~chinese true成功移除，否则false。
     */
    bool removeTriggerObj(TriggerObj *Obj);

    /**
     * @brief @~english Remove trigger with trigger unique id.
     * @~chinese 根据触发器id，移除触发器。
     * @param id @~english Trigger unique id.
     * @~chinese 触发器唯一id。
     * @return @~english true remove successfully false failed to remove .
     * @~chinese true成功移除，否则false。
     */
    bool removeTriggerObj(unsigned int id);

    /** @brief @~english Returns whether _triggerObjs is empty (i.e. whether its size is 0).
     * @~chinese 返回_triggerObjs Vector是否为空(即无论其大小为0)。
     * @return @~english true _triggerObjs isn't empty false empty .
     * @~chinese true 没有触发器，否则false。
     */
    bool isEmpty(void) const;

    /**
     * @brief @~english Add armature event callback to trigger object.
     * @~chinese 为触发器对象增加事件回调。
     * @param pTarget @~english Trigger object point.
     * @~chinese 触发器对象指针。
     * @param mecf @~english Callback function.
     * @~chinese 回调函数。
     */
    void addArmatureMovementCallBack(Armature *pAr, cocos2d::Ref *pTarget, SEL_MovementEventCallFunc mecf);

    /**
     * @brief @~english Remove armature event callback function with armature point, trigger point, callback function.
     * @~chinese 为触发器对象移除事件回调。
     * @param pTarget @~english Trigger object point.
     * @~chinese 触发器对象指针。
     * @param mecf @~english Callback function.
     * @~chinese 回调函数。
     */
    void removeArmatureMovementCallBack(Armature *pAr, cocos2d::Ref *pTarget, SEL_MovementEventCallFunc mecf);

    /**
     * @brief @~english Remove all event callback functions binding to armature point.
     * @~chinese 移除绑定到Armature所有事件回调。
     * @param pAr @~english Armature point.
     * @~chinese 1.x骨骼动画指针。
     */
    void removeArmatureAllMovementCallBack(Armature *pAr);

    /**
     * @brief @~english Remove all armature event callback functions. 
     * @~chinese 移除Armature所有事件回调。
     */
    void removeAllArmatureMovementCallBack();

    /**
     * @brief @~english Dispatch trigger events. 
     * @~chinese  分发触发器事件。
     * @param tEvent @~english Trigger event.
     * @~chinese 触发器事件。
     */
    void dispatchEvent(cocos2d::EventCustom* tEvent);

    /**
     * @brief @~english Remove trigger event listener. 
     * @~chinese 移除触发器事件监听器。
     * @param listener @~english Trigger event listener.
     * @~chinese 触发器事件监听器。
     */
    void removeEventListener(cocos2d::EventListener* listener);

    /**
     * @brief @~english Add a trigger event listener with the fixed priority.
     * @~chinese 增加触发器事件监听器，并指定优先级。
     * @param listener @~english Trigger event listener.
     * @~chinese 触发器事件监听器。
     * @param fixedPriority @~english The fixed priority of the listener
     * @~chinese 监听器优先级
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
    /**
     * @brief @~english Transform binary object into a json object, assign to document.
     * @~chinese 根据cocos studio 1.x导出的二进制对象转换为json对象，并赋值给document。
     * @param document @~english Json data object
     * @~chinese json数据对象。
     * @param pCocoLoader @~english Loader scene object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x场景编辑器导出二进制数据加载器对象。
     * @param pCocoNode @~english Loader node object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x场景编辑器导出二进制数据node对象。
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
