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
 @类名 BaseTriggerCondition
 @主题 触发器条件基类
 @细节 条件判断以及从cocos studio 1.x导出的二进制与json数据反序列化
 @组 触发器
 */
class CC_STUDIO_DLL BaseTriggerCondition : public cocos2d::Ref
{
protected:
    /**
    @主题 BaseTriggerCondition构造函数
    */
    BaseTriggerCondition(void);
public:
    /**
    @主题 BaseTriggerCondition析构函数
    */
    virtual ~BaseTriggerCondition(void);
    /**
    @主题 初始化触发器条件
    @返回 true 初始化成功，否则false
    */
    virtual bool init();
    /**
    @主题 触发器条件判断
    @返回 true 条件成功，否则false
    */
    virtual bool detect();
    /**
    @主题 根据cocos studio 1.x导出的json对象反序列化
    @参数 val json对象
    @返回 无
    */
    virtual void serialize(const rapidjson::Value &val);
    /**
    @主题 根据cocos studio 1.x导出的二进制对象反序列化
    @参数 cocoLoader cocos studio 1.x导出二进制数据加载器对象
    @参数 cocoNode cocos studio 1.x导出二进制数据node对象
    @返回 无
    */
    virtual void serialize(cocostudio::CocoLoader *cocoLoader, cocostudio::stExpCocoNode *cocoNode);
    /**
    @主题 触发器条件被删除的时候调用，可以重载这个方法把资源释放到这里
    @返回 无
    */
    virtual void removeAll();
};

 /** 
 @类名 BaseTriggerAction
 @主题 触发器动作基类
 @细节 动作执行以及从cocos studio 1.x导出的二进制与json数据反序列化
 @组 触发器
 */
class CC_STUDIO_DLL BaseTriggerAction : public cocos2d::Ref
{
protected:
    /**
    @主题 BaseTriggerAction析构函数
    */
    BaseTriggerAction(void);
public:
    /**
    @主题 BaseTriggerAction析构函数
    */
    virtual ~BaseTriggerAction(void);
    /**
    @主题 初始化触发器动作
    @返回 true 初始化成功，否则false
    */
    virtual bool init();
    /**
    @主题 触发器动作执行
    @返回 无
    */
    virtual void done();
    /**
    @主题 根据cocos studio 1.x导出的json对象反序列化
    @参数 val json对象
    @返回 无
    */
    virtual void serialize(const rapidjson::Value &val);
    /**
    @主题 根据cocos studio 1.x导出的二进制对象反序列化
    @参数 cocoLoader cocos studio 1.x导出二进制数据加载器对象
    @参数 cocoNode cocos studio 1.x导出二进制数据node对象
    @返回 无
    */
    virtual void serialize(cocostudio::CocoLoader *cocoLoader, cocostudio::stExpCocoNode *cocoNode);
    /**
    @主题 触发器动作被删除的时候调用，可以重载这个方法把资源释放到这里
    @返回 无
    */
    virtual void removeAll();
};

 /** 
 @类名 TriggerObj
 @主题 触发器基类
 @细节 单个触发器条件检测，动作执行以及从cocos studio 1.x导出的二进制与json数据反序列化
 @组 触发器
 */
class CC_STUDIO_DLL TriggerObj : public cocos2d::Ref
{
public:
    /**
    @主题 TriggerObj构造函数
    */
    TriggerObj(void);
    /**
    @主题 TriggerObj析构函数
    */
    virtual ~TriggerObj(void);
    /**
    @主题 初始化触发器条件
    @返回 true 初始化成功，否则false
    */
    virtual bool init();
   /**
    @主题 创建触发器 
    @返回 声音触发器
    */
    static TriggerObj* create(void);
    /**
    @主题 触发器条件判断
    @返回 true 条件成功，否则false
    */
    virtual bool detect();
    /**
    @主题 触发器动作执行
    @返回 无
    */
    virtual void done();
    /**
    @主题 触发器被删除的时候调用，可以重载这个方法把资源释放到这里
    @返回 无
    */
    virtual void removeAll();
    /**
    @主题 根据cocos studio 1.x导出的json对象反序列化
    @参数 val json对象
    @返回 无
    */
    virtual void serialize(const rapidjson::Value &val);
    /**
    @主题 根据cocos studio 1.x导出的二进制对象反序列化
    @参数 cocoLoader cocos studio 1.x导出二进制数据加载器对象
    @参数 cocoNode cocos studio 1.x导出二进制数据node对象
    @返回 无
    */
    virtual void serialize(cocostudio::CocoLoader *cocoLoader, cocostudio::stExpCocoNode *cocoNode);
    /**
    @主题 获取触发器唯一id
    @返回 触发器唯一id
    */
    unsigned int getId();
    /**
    @主题 设置触发器是否可用
    @参数 enabled true为可用，false为不可用
    @返回 无
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


