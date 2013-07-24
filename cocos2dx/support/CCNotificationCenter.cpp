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

#include "CCNotificationCenter.h"
#include "cocoa/CCArray.h"
#include "script_support/CCScriptSupport.h"
#include <string>

using namespace std;

NS_CC_BEGIN

static NotificationCenter *s_sharedNotifCenter = NULL;

NotificationCenter::NotificationCenter()
: _scriptHandler(0)
{
    _observers = Array::createWithCapacity(3);
    _observers->retain();
}

NotificationCenter::~NotificationCenter()
{
    _observers->release();
}

NotificationCenter *NotificationCenter::getInstance()
{
    if (!s_sharedNotifCenter)
    {
        s_sharedNotifCenter = new NotificationCenter;
    }
    return s_sharedNotifCenter;
}

void NotificationCenter::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(s_sharedNotifCenter);
}

// XXX: deprecated
NotificationCenter *NotificationCenter::sharedNotificationCenter(void)
{
    return NotificationCenter::getInstance();
}

// XXX: deprecated
void NotificationCenter::purgeNotificationCenter(void)
{
    NotificationCenter::destroyInstance();
}

//
// internal functions
//
bool NotificationCenter::observerExisted(Object *target,const char *name)
{
    Object* obj = NULL;
    CCARRAY_FOREACH(_observers, obj)
    {
        NotificationObserver* observer = (NotificationObserver*) obj;
        if (!observer)
            continue;
        
        if (!strcmp(observer->getName(),name) && observer->getTarget() == target)
            return true;
    }
    return false;
}

//
// observer functions
//
void NotificationCenter::addObserver(Object *target, 
                                       SEL_CallFuncO selector,
                                       const char *name,
                                       Object *obj)
{
    if (this->observerExisted(target, name))
        return;
    
    NotificationObserver *observer = new NotificationObserver(target, selector, name, obj);
    if (!observer)
        return;
    
    observer->autorelease();
    _observers->addObject(observer);
}

void NotificationCenter::removeObserver(Object *target,const char *name)
{
    Object* obj = NULL;
    CCARRAY_FOREACH(_observers, obj)
    {
        NotificationObserver* observer = static_cast<NotificationObserver*>(obj);
        if (!observer)
            continue;
        
        if (!strcmp(observer->getName(),name) && observer->getTarget() == target)
        {
            _observers->removeObject(observer);
            return;
        }
    }
}

int NotificationCenter::removeAllObservers(Object *target)
{
    Object *obj = NULL;
    Array *toRemove = Array::create();

    CCARRAY_FOREACH(_observers, obj)
    {
        NotificationObserver *observer = static_cast<NotificationObserver *>(obj);
        if (!observer)
            continue;

        if (observer->getTarget() == target)
        {
            toRemove->addObject(observer);
        }
    }

    _observers->removeObjectsInArray(toRemove);
    return toRemove->count();
}

void NotificationCenter::registerScriptObserver( Object *target, int handler,const char* name)
{
    
    if (this->observerExisted(target, name))
        return;
    
    NotificationObserver *observer = new NotificationObserver(target, NULL, name, NULL);
    if (!observer)
        return;
    
    observer->setHandler(handler);
    observer->autorelease();
    _observers->addObject(observer);
}

void NotificationCenter::unregisterScriptObserver(Object *target,const char* name)
{        
    Object* obj = NULL;
    CCARRAY_FOREACH(_observers, obj)
    {
        NotificationObserver* observer = static_cast<NotificationObserver*>(obj);
        if (!observer)
            continue;
            
        if ( !strcmp(observer->getName(),name) && observer->getTarget() == target)
        {
            _observers->removeObject(observer);
        }
    }
}

void NotificationCenter::postNotification(const char *name, Object *object)
{
    Array* ObserversCopy = Array::createWithCapacity(_observers->count());
    ObserversCopy->addObjectsFromArray(_observers);
    Object* obj = NULL;
    CCARRAY_FOREACH(ObserversCopy, obj)
    {
        NotificationObserver* observer = static_cast<NotificationObserver*>(obj);
        if (!observer)
            continue;
        
        if (!strcmp(name,observer->getName()) && (observer->getObject() == object || observer->getObject() == NULL || object == NULL))
        {
            if (0 != observer->getHandler())
            {
                BasicScriptData data(this, (void*)name);
                ScriptEvent scriptEvent(kNotificationEvent,(void*)&data);
                ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&scriptEvent);
            }
            else
            {
                observer->performSelector(object);
            }
        }
    }
}

void NotificationCenter::postNotification(const char *name)
{
    this->postNotification(name,NULL);
}

int NotificationCenter::getObserverHandlerByName(const char* name)
{
    if (NULL == name || strlen(name) == 0)
    {
        return 0;
    }
    
    Object* obj = NULL;
    CCARRAY_FOREACH(_observers, obj)
    {
        NotificationObserver* observer = static_cast<NotificationObserver*>(obj);
        if (NULL == observer)
            continue;
        
        if ( 0 == strcmp(observer->getName(),name) )
        {
            return observer->getHandler();
            break;
        }
    }
    
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
///
/// NotificationObserver
///
////////////////////////////////////////////////////////////////////////////////
NotificationObserver::NotificationObserver(Object *target, 
                                               SEL_CallFuncO selector,
                                               const char *name,
                                               Object *obj)
{
    _target = target;
    _selector = selector;
    _object = obj;
    
    _name = name;
    _handler = 0;
}

NotificationObserver::~NotificationObserver()
{

}

void NotificationObserver::performSelector(Object *obj)
{
    if (_target)
    {
		if (obj) {
			(_target->*_selector)(obj);
		} else {
			(_target->*_selector)(_object);
		}
    }
}

Object *NotificationObserver::getTarget() const
{
    return _target;
}

SEL_CallFuncO NotificationObserver::getSelector() const
{
    return _selector;
}

const char* NotificationObserver::getName() const
{
    return _name.c_str();
}

Object* NotificationObserver::getObject() const
{
    return _object;
}

int NotificationObserver::getHandler() const
{
    return _handler;
}

void NotificationObserver::setHandler(int var)
{
    _handler = var;
}

NS_CC_END
