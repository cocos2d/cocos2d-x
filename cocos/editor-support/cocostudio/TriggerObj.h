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

#ifndef __TRIGGEROBJ_H__
#define __TRIGGEROBJ_H__

#include "CocoStudio.h"
#include "base/CCVector.h"

namespace cocos2d {
class EventListenerCustom;
}

namespace cocostudio {

/** 
 * @class BaseTriggerCondition
 * @brief @~english condition base class.
 * @~chinese 触发器条件基类。
*/
class CC_STUDIO_DLL BaseTriggerCondition : public cocos2d::Ref
{
protected:
    /**
     * @brief @~english BaseTriggerCondition constructor.
     * @~chinese 触发器条件基类构造函数。
     */
    BaseTriggerCondition(void);
public:
    /**
     * @brief @~english BaseTriggerCondition destructor.
     * @~chinese 触发器条件基类析构函数。
     */
    virtual ~BaseTriggerCondition(void);

    /**
     * @brief @~english initialize a BaseTriggerCondition.
     * @~chinese 初始化触发器条件。
     * @return @~english true Initialize successfully false failed to initialize.
     * @~chinese true 初始化成功，否则false。
     */
    virtual bool init();

    /**
     * @brief @~english Detect condition of trigger.
     * @~chinese 触发器条件判断。
     * @return @~english true Detect successfully false failed to Detect.
     * @~chinese true 条件成功，否则false。
     */
    virtual bool detect();

    /**
     * @brief @~english Deserialization json data of cocos studio 1.x scene editor.
     * @~chinese 反序列化cocos studio 1.x 场景编辑器导出的数据。
     * @param val @~english Json object point.
     * @~chinese json对象指针。
     */
    virtual void serialize(const rapidjson::Value &val);

    /**
     * @brief @~english Deserialization binary data of cocos studio 1.x scene editor.
     * @~chinese 反序列化cocos studio 1.x导出的二进制数据。
     * @param cocoLoader @~english Loader scene object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x场景编辑器导出二进制数据加载器对象。
     * @param cocoNode @~english Loader node object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x场景编辑器导出二进制数据node对象。
     */
    virtual void serialize(cocostudio::CocoLoader *cocoLoader, cocostudio::stExpCocoNode *cocoNode);

    /**
     * @brief @~english it is called when the trigger condition is removed , you can override this method to implement free the resources here.
     * @~chinese 触发器被移除的时候被调用，可以重载这个方法把资源释放到这里。
     */
    virtual void removeAll();
};

/** 
 * @class BaseTriggerAction
 * @brief @~english Action base class.
 * @~chinese 触发器动作基类。
*/
class CC_STUDIO_DLL BaseTriggerAction : public cocos2d::Ref
{
protected:
    /**
     * @brief @~english BaseTriggerAction constructor.
     * @~chinese 触发器动作基类构造函数。
     */
    BaseTriggerAction(void);
public:
    /**
     * @brief @~english BaseTriggerAction destructor.
     * @~chinese 触发器动作基类析构函数。
     */
    virtual ~BaseTriggerAction(void);

    /**
     * @brief @~english initialize a BaseTriggerAction.
     * @~chinese 初始化触发器动作。
     * @return @~english true Initialize successfully false failed to initialize.
     * @~chinese true 初始化成功，否则false。
     */
    virtual bool init();

    /**
     * @brief @~english BaseTriggerAction execution.
     * @~chinese 触发器动作执行。
     */
    virtual void done();

    /**
     * @brief @~english Deserialization json data of cocos studio 1.x scene editor.
     * @~chinese 反序列化cocos studio 1.x 场景编辑器导出的数据。
     * @param val @~english Json object point.
     * @~chinese json对象指针。
     */
    virtual void serialize(const rapidjson::Value &val);

    /**
     * @brief @~english Deserialization binary data of cocos studio 1.x scene editor.
     * @~chinese 反序列化cocos studio 1.x导出的二进制数据。
     * @param cocoLoader @~english Loader scene object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x场景编辑器导出二进制数据加载器对象。
     * @param cocoNode @~english Loader node object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x场景编辑器导出二进制数据node对象。
     */
    virtual void serialize(cocostudio::CocoLoader *cocoLoader, cocostudio::stExpCocoNode *cocoNode);

    /**
     * @brief @~english It is called when the trigger action is removed , you can override this method to implement free the resources here.
     * @~chinese 触发器被移除的时候被调用，可以重载这个方法把资源释放到这里。
     */
    virtual void removeAll();
};

/** 
 * @class TriggerObj
 * @brief @~english Trigger class.
 * @~chinese 触发器。
*/
class CC_STUDIO_DLL TriggerObj : public cocos2d::Ref
{
public:
    /**
     * @brief @~english TriggerObj constructor.
     * @~chinese TriggerObj构造函数。
     */
    TriggerObj(void);

    /**
     * @brief @~english TriggerObj destructor.
     * @~chinese TriggerObj析构函数。
     */
    virtual ~TriggerObj(void);

    /**
     * @brief @~english initialize a TriggerObj.
     * @~chinese 初始化触发器。
     * @return @~english true initialize successfully false failed to initialize.
     * @~chinese true 初始化成功，否则false。
     */
    virtual bool init();

    /**
     * @brief @~english Allocates and initializes a create.
     * @~chinese 分配并且初始化触发器。
     * @return @~english A initialized TriggerObj which is marked as "autorelease".
     * @~chinese 一个初始化的触发器，该节点会自动被标记为“autorelease”(自动释放)。
     */
    static TriggerObj* create(void);

    /**
     * @brief @~english Detect condition of trigger.
     * @~chinese 触发器条件判断。
     * @return @~english true Detect successfully false failed to Detect.
     * @~chinese true 条件成功，否则false。
     */
    virtual bool detect();

    /**
     * @brief @~english trigger execution.
     * @~chinese 触发器动作执行。
     */
    virtual void done();

    /**
     * @brief @~english it is called when the trigger is removed , you can override this method to implement free the resources here.
     * @~chinese 触发器被移除的时候被调用，可以重载这个方法把资源释放到这里。
     */
    virtual void removeAll();

    /**
     * @brief @~english Deserialization json data of cocos studio 1.x scene editor.
     * @~chinese 反序列化cocos studio 1.x 场景编辑器导出的数据。
     * @param val @~english json object point.
     * @~chinese json对象指针。
     */
    virtual void serialize(const rapidjson::Value &val);

    /**
     * @brief @~english Deserialization binary data of cocos studio 1.x scene editor.
     * @~chinese 反序列化cocos studio 1.x导出的二进制数据。
     * @param cocoLoader @~english loader scene object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x场景编辑器导出二进制数据加载器对象。
     * @param cocoNode @~english loader node object of binary data exported by scene reader in cocos studio 1.x.
     * @~chinese cocos studio 1.x场景编辑器导出二进制数据node对象。
     */
    virtual void serialize(cocostudio::CocoLoader *cocoLoader, cocostudio::stExpCocoNode *cocoNode);

    /**
     * @brief @~english get unique id of trigger.
     * @~chinese 获取触发器唯一id。
     * @return @~english unique id of trigger.
     * @~chinese 触发器唯一id。
     */
    unsigned int getId();

    /**  
     * @brief @~english enables or disables the trigger.
     * @~chinese 启用或禁用触发器。
     * @param enabled @~english true enable the trigger, false disabled the trigger. 
     * @~chinese true，启用触发器 false，禁用触发器。
     */
    void setEnabled(bool enabled);
  
private:
    cocos2d::Vector<BaseTriggerCondition*> _cons;
    cocos2d::Vector<BaseTriggerAction*> _acts;
    unsigned int _id;
    bool _enabled;
    cocos2d::Vector<cocos2d::EventListenerCustom*> _listeners;
};

}

#endif


