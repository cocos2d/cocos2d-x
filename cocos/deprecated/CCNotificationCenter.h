/****************************************************************************
Copyright (c) 2011      Erawppa
Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef __CCNOTIFICATIONCENTER_H__
#define __CCNOTIFICATIONCENTER_H__

#include "base/CCRef.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

class __Array;
class ScriptHandlerMgr;

class CC_DLL __NotificationCenter : public Ref
{
    friend class ScriptHandlerMgr;
public:
    /** __NotificationCenter 构造函数
     * @js ctor
     */
    __NotificationCenter();

    /** __NotificationCenter 析构函数
     * @js NA
     * @lua NA
     */
    ~__NotificationCenter();
    
    /** 得到 __NotificationCenter的单例. */
    static __NotificationCenter *getInstance();

    /** 销毁 __NotificationCenter的单例. */
    static void destroyInstance();

    /** @deprecated 废弃使用 getInstance() 替代 */
    CC_DEPRECATED_ATTRIBUTE static __NotificationCenter *sharedNotificationCenter(void);

    /** @deprecated 废弃使用 destroyInstance() 替代 */
    CC_DEPRECATED_ATTRIBUTE static void purgeNotificationCenter(void);


    /** @brief 根据指定的target，添加观察者.
     *  @param target The target which wants to observe notification events.
     *  @param selector The callback function which will be invoked when the specified notification event was posted.
     *  @param name The name of this notification.
     *  @param sender The object whose notifications the target wants to receive. Only notifications sent by this sender are delivered to the target. nullptr means that the sender is not used to decide whether to deliver the notification to target.
     */
    void addObserver(Ref *target, 
                     SEL_CallFuncO selector,
                     const std::string& name,
                     Ref *sender);

    /** @brief 根据指定的target 和 name 移除观察者.
     *  @param target The target of this notification.
     *  @param name The name of this notification. 
     */
    void removeObserver(Ref *target,const std::string& name);
    
    /** @brief 移除这个target注册的所有通知
     *  @param target The target of this notification.
     *  @returns the number of observers removed
     */
    int removeAllObservers(Ref *target);

    /** @brief 注册一个 hander 用作脚本绑定.
     *  @note Only supports Lua Binding now.
     *  @param handler The lua handler.
     */
    void registerScriptObserver(Ref *target,int handler,const std::string& name);

    /** 取消注册脚本observer */
    void unregisterScriptObserver(Ref *target,const std::string& name);
    
    /** @brief 根据某个名字发送一个通知事件.
     *  @param name The name of this notification.
     */
    void postNotification(const std::string& name);

    /** @brief 根据某个名字发送一个通知事件.
     *  @param name The name of this notification.
     *  @param sender The object posting the notification. Can be nullptr
     */
    void postNotification(const std::string& name, Ref *sender);
    
    /** @brief 获取脚本 handler.
     *  @note Only supports Lua Binding now.
     *  @return The script handle.
     */
    inline int getScriptHandler() const { return _scriptHandler; };
    
    /** @brief 获取 observer 脚本 handler.
     *  @param name The name of this notification.
     *  @return The observer script handle.
     */
    int getObserverHandlerByName(const std::string& name);
private:
    // 内部函数

    // 根据特定的 target 和 name 检查观察者是否存在.
    bool observerExisted(Ref *target,const std::string& name, Ref *sender);
    
    // variables
    //
    __Array *_observers;
    int     _scriptHandler;
};

class CC_DLL NotificationObserver : public Ref
{
public:
    /** @brief NotificationObserver 构造函数
     *  @param target 这个 target 用于监听通知事件.
     *  @param selector 当指定的通知事件被传递，毁掉函数将被调用
     *  @param name notification 名字.
     *  @param sender The object whose notifications the target wants to receive. Only notifications sent by this sender are delivered to the target. nullptr means that the sender is not used to decide whether to deliver the notification to target.
     * @js NA
     * @lua NA
     */
    NotificationObserver(Ref *target, 
                           SEL_CallFuncO selector,
                           const std::string& name,
                           Ref *sender);

    /** NotificationObserver 析构方法
     * @js NA
     * @lua NA
     */
    ~NotificationObserver();      
    
    /** 调用观察者回调方法 
     * @js NA
     * @lua NA
     */
    void performSelector(Ref *sender);
    
    // Getters / Setters
    /**
     * @js NA
     * @lua NA
     */
    Ref* getTarget() const;
    /**
     * @js NA
     * @lua NA
     */
    SEL_CallFuncO getSelector() const;
    /**
     * @js NA
     * @lua NA
     */
    const std::string& getName() const;
    /**
     * @js NA
     * @lua NA
     */
    Ref* getSender() const;
    /**
     * @js NA
     * @lua NA
     */
    int getHandler() const;
    /**
     * @js NA
     * @lua NA
     */
    void setHandler(int handler);

private:
    Ref* _target;
    SEL_CallFuncO _selector;
    std::string _name;
    Ref* _sender;
    int _handler;
};

NS_CC_END

#endif//__CCNOTIFICATIONCENTER_H__
