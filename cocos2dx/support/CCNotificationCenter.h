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
    /** NotificationCenter constructor */
    NotificationCenter();

    /** NotificationCenter destructor */
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
     *  @param obj The extra parameter which will be passed to the callback function.
     */
    void addObserver(Object *target, 
                     SEL_CallFuncO selector,
                     const char *name,
                     Object *obj);

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
     *  @param object The extra parameter.
     */
    void postNotification(const char *name, Object *object);
    
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
    bool observerExisted(Object *target,const char *name);
    
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
     *  @param obj The extra parameter which will be passed to the callback function.
     */
    NotificationObserver(Object *target, 
                           SEL_CallFuncO selector,
                           const char *name,
                           Object *obj);

    /** NotificationObserver destructor function */
    ~NotificationObserver();      
    
    /** Invokes the callback function of this observer */
    void performSelector(Object *obj);
    
    // Getters / Setters
    Object* getTarget() const;
    SEL_CallFuncO getSelector() const;
    const char* getName() const;
    Object* getObject() const;
    int getHandler() const;
    void setHandler(int handler);

private:
    Object* _target;
    SEL_CallFuncO _selector;
    std::string _name;
    Object* _object;
    int _handler;
};

NS_CC_END

#endif//__CCNOTIFICATIONCENTER_H__
