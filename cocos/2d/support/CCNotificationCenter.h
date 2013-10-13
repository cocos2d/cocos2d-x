/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Erawppa
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

#include "cocoa/CCObject.h"
#include "cocoa/CCArray.h"

NS_CC_BEGIN

class ScriptHandlerMgr;
class CC_DLL NotificationCenter : public Object
{
    friend class ScriptHandlerMgr;
public:
    /** NotificationCenter constructor
     * @js ctor
     */
    NotificationCenter();

    /** NotificationCenter destructor
     * @js NA
     * @lua NA
     */
    ~NotificationCenter();
    
    /** Gets the single instance of NotificationCenter. */
    static NotificationCenter *getInstance();

    /** Destroys the single instance of NotificationCenter. */
    static void destroyInstance();

    /** @deprecated use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static NotificationCenter *sharedNotificationCenter(void);

    /** @deprecated use destroyInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static void purgeNotificationCenter(void);


    /** @brief Adds an observer for the specified target.
     *  @param target The target which wants to observe notification events.
     *  @param selector The callback function which will be invoked when the specified notification event was posted.
     *  @param name The name of this notification.
     *  @param sender The object whose notifications the target wants to receive. Only notifications sent by this sender are delivered to the target. NULL means that the sender is not used to decide whether to deliver the notification to target.
     */
    void addObserver(Object *target, 
                     SEL_CallFuncO selector,
                     const char *name,
                     Object *sender);

    /** @brief Removes the observer by the specified target and name.
     *  @param target The target of this notification.
     *  @param name The name of this notification. 
     */
    void removeObserver(Object *target,const char *name);
    
    /** @brief Removes all notifications registered by this target
     *  @param target The target of this notification.
     *  @returns the number of observers removed
     */
    int removeAllObservers(Object *target);

    /** @brief Registers one hander for script binding.
     *  @note Only supports Lua Binding now.
     *  @param handler The lua handler.
     */
    void registerScriptObserver(Object *target,int handler,const char* name);

    /** Unregisters script observer */
    void unregisterScriptObserver(Object *target,const char* name);
    
    /** @brief Posts one notification event by name.
     *  @param name The name of this notification.
     */
    void postNotification(const char *name);

    /** @brief Posts one notification event by name.
     *  @param name The name of this notification.
     *  @param sender The object posting the notification. Can be NULL
     */
    void postNotification(const char *name, Object *sender);
    
    /** @brief Gets script handler.
     *  @note Only supports Lua Binding now.
     *  @return The script handle.
     */
    inline int getScriptHandler() const { return _scriptHandler; };
    
    /** @brief Gets observer script handler.
     *  @param name The name of this notification.
     *  @return The observer script handle.
     */
    int getObserverHandlerByName(const char* name);
private:
    // internal functions

    // Check whether the observer exists by the specified target and name.
    bool observerExisted(Object *target,const char *name, Object *sender);
    
    // variables
    //
    Array *_observers;
    int     _scriptHandler;
};

class CC_DLL NotificationObserver : public Object
{
public:
    /** @brief NotificationObserver constructor
     *  @param target The target which wants to observer notification events.
     *  @param selector The callback function which will be invoked when the specified notification event was posted.
     *  @param name The name of this notification.
     *  @param sender The object whose notifications the target wants to receive. Only notifications sent by this sender are delivered to the target. NULL means that the sender is not used to decide whether to deliver the notification to target.
     * @js NA
     * @lua NA
     */
    NotificationObserver(Object *target, 
                           SEL_CallFuncO selector,
                           const char *name,
                           Object *sender);

    /** NotificationObserver destructor function 
     * @js NA
     * @lua NA
     */
    ~NotificationObserver();      
    
    /** Invokes the callback function of this observer 
     * @js NA
     * @lua NA
     */
    void performSelector(Object *sender);
    
    // Getters / Setters
    /**
     * @js NA
     * @lua NA
     */
    Object* getTarget() const;
    /**
     * @js NA
     * @lua NA
     */
    SEL_CallFuncO getSelector() const;
    /**
     * @js NA
     * @lua NA
     */
    const char* getName() const;
    /**
     * @js NA
     * @lua NA
     */
    Object* getSender() const;
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
    Object* _target;
    SEL_CallFuncO _selector;
    std::string _name;
    Object* _sender;
    int _handler;
};

NS_CC_END

#endif//__CCNOTIFICATIONCENTER_H__
