/****************************************************************************
Copyright (c) 2011      Erawppa
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.

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
/// @cond DO_NOT_SHOW

#include "base/CCRef.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

class __Array;
class ScriptHandlerMgr;

/**
 * @cond DO_NOT_SHOW
 * @{
 */

class CC_DLL __NotificationCenter : public Ref
{
    friend class ScriptHandlerMgr;
public:
    /** __NotificationCenter constructor
     * @js ctor
     */
    __NotificationCenter();

    /** __NotificationCenter destructor
     * @js NA
     * @lua NA
     */
    ~__NotificationCenter();
    
    /** Gets the single instance of __NotificationCenter. */
    static __NotificationCenter *getInstance();

    /** Destroys the single instance of __NotificationCenter. */
    static void destroyInstance();

    /** @deprecated use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static __NotificationCenter *sharedNotificationCenter(void);

    /** @deprecated use destroyInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static void purgeNotificationCenter(void);


    /** @brief Adds an observer for the specified target.
     *  @param target The target which wants to observe notification events.
     *  @param selector The callback function which will be invoked when the specified notification event was posted.
     *  @param name The name of this notification.
     *  @param sender The object whose notifications the target wants to receive. Only notifications sent by this sender are delivered to the target. nullptr means that the sender is not used to decide whether to deliver the notification to target.
     */
    void addObserver(Ref *target, 
                     SEL_CallFuncO selector,
                     const std::string& name,
                     Ref *sender);

    /** @brief Removes the observer by the specified target and name.
     *  @param target The target of this notification.
     *  @param name The name of this notification. 
     */
    void removeObserver(Ref *target,const std::string& name);
    
    /** @brief Removes all notifications registered by this target
     *  @param target The target of this notification.
     *  @returns the number of observers removed
     */
    int removeAllObservers(Ref *target);

    /** @brief Registers one hander for script binding.
     *  @note Only supports Lua Binding now.
     *  @param handler The lua handler.
     */
    void registerScriptObserver(Ref *target,int handler,const std::string& name);

    /** Unregisters script observer */
    void unregisterScriptObserver(Ref *target,const std::string& name);
    
    /** @brief Posts one notification event by name.
     *  @param name The name of this notification.
     */
    void postNotification(const std::string& name);

    /** @brief Posts one notification event by name.
     *  @param name The name of this notification.
     *  @param sender The object posting the notification. Can be nullptr
     */
    void postNotification(const std::string& name, Ref *sender);
    
    /** @brief Gets script handler.
     *  @note Only supports Lua Binding now.
     *  @return The script handle.
     */
    int getScriptHandler() const { return _scriptHandler; }
    
    /** @brief Gets observer script handler.
     *  @param name The name of this notification.
     *  @return The observer script handle.
     */
    int getObserverHandlerByName(const std::string& name);
private:
    // internal functions

    // Check whether the observer exists by the specified target and name.
    bool observerExisted(Ref *target,const std::string& name, Ref *sender);
    
    // variables
    //
    __Array *_observers;
    int     _scriptHandler;
};

class CC_DLL NotificationObserver : public Ref
{
public:
    /** @brief NotificationObserver constructor
     *  @param target The target which wants to observer notification events.
     *  @param selector The callback function which will be invoked when the specified notification event was posted.
     *  @param name The name of this notification.
     *  @param sender The object whose notifications the target wants to receive. Only notifications sent by this sender are delivered to the target. nullptr means that the sender is not used to decide whether to deliver the notification to target.
     * @js NA
     * @lua NA
     */
    NotificationObserver(Ref *target, 
                           SEL_CallFuncO selector,
                           const std::string& name,
                           Ref *sender);

    /** NotificationObserver destructor function 
     * @js NA
     * @lua NA
     */
    ~NotificationObserver();      
    
    /** Invokes the callback function of this observer 
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

/**
 * @}
 */

NS_CC_END

/// @endcond
#endif//__CCNOTIFICATIONCENTER_H__
