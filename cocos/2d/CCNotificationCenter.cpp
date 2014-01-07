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

#include "CCNotificationCenter.h"
#include "CCArray.h"
#include "CCScriptSupport.h"
#include <string>

using namespace std;

NS_CC_BEGIN

static __NotificationCenter *s_sharedNotifCenter = nullptr;

__NotificationCenter::__NotificationCenter()
: _scriptHandler(0)
{
    _observers = __Array::createWithCapacity(3);
    _observers->retain();
}

__NotificationCenter::~__NotificationCenter()
{
    _observers->release();
}

__NotificationCenter *__NotificationCenter::getInstance()
{
    if (!s_sharedNotifCenter)
    {
        s_sharedNotifCenter = new __NotificationCenter;
    }
    return s_sharedNotifCenter;
}

void __NotificationCenter::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(s_sharedNotifCenter);
}

// XXX: deprecated
__NotificationCenter *__NotificationCenter::sharedNotificationCenter(void)
{
    return __NotificationCenter::getInstance();
}

// XXX: deprecated
void __NotificationCenter::purgeNotificationCenter(void)
{
    __NotificationCenter::destroyInstance();
}

//
// internal functions
//
bool __NotificationCenter::observerExisted(Object *target, const std::string& name, Object *sender)
{
    Object* obj = nullptr;
    CCARRAY_FOREACH(_observers, obj)
    {
        NotificationObserver* observer = (NotificationObserver*) obj;
        if (!observer)
            continue;
        
        if (observer->getName() == name && observer->getTarget() == target && observer->getSender() == sender)
            return true;
    }
    return false;
}

//
// observer functions
//
void __NotificationCenter::addObserver(Object *target, 
                                       SEL_CallFuncO selector,
                                       const std::string& name,
                                       Object *sender)
{
    if (this->observerExisted(target, name, sender))
        return;
    
    NotificationObserver *observer = new NotificationObserver(target, selector, name, sender);
    if (!observer)
        return;
    
    observer->autorelease();
    _observers->addObject(observer);
}

void __NotificationCenter::removeObserver(Object *target, const std::string& name)
{
    Object* obj = nullptr;
    CCARRAY_FOREACH(_observers, obj)
    {
        NotificationObserver* observer = static_cast<NotificationObserver*>(obj);
        if (!observer)
            continue;
        
        if (observer->getName() == name && observer->getTarget() == target)
        {
            _observers->removeObject(observer);
            return;
        }
    }
}

int __NotificationCenter::removeAllObservers(Object *target)
{
    Object *obj = nullptr;
    __Array *toRemove = __Array::create();

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
    return static_cast<int>(toRemove->count());
}

void __NotificationCenter::registerScriptObserver( Object *target, int handler,const std::string& name)
{
    
    if (this->observerExisted(target, name, nullptr))
        return;
    
    NotificationObserver *observer = new NotificationObserver(target, nullptr, name, nullptr);
    if (!observer)
        return;
    
    observer->setHandler(handler);
    observer->autorelease();
    _observers->addObject(observer);
}

void __NotificationCenter::unregisterScriptObserver(Object *target,const std::string& name)
{        
    Object* obj = nullptr;
    CCARRAY_FOREACH(_observers, obj)
    {
        NotificationObserver* observer = static_cast<NotificationObserver*>(obj);
        if (!observer)
            continue;
            
        if ( observer->getName() == name && observer->getTarget() == target)
        {
            _observers->removeObject(observer);
        }
    }
}

void __NotificationCenter::postNotification(const std::string& name, Object *sender)
{
    __Array* ObserversCopy = __Array::createWithCapacity(_observers->count());
    ObserversCopy->addObjectsFromArray(_observers);
    Object* obj = nullptr;
    CCARRAY_FOREACH(ObserversCopy, obj)
    {
        NotificationObserver* observer = static_cast<NotificationObserver*>(obj);
        if (!observer)
            continue;
        
        if (observer->getName() == name && (observer->getSender() == sender || observer->getSender() == nullptr || sender == nullptr))
        {
            if (0 == observer->getHandler())
            {
                observer->performSelector(sender);
            }
        }
    }
}

void __NotificationCenter::postNotification(const std::string& name)
{
    this->postNotification(name,nullptr);
}

int __NotificationCenter::getObserverHandlerByName(const std::string& name)
{
    if (name.empty())
    {
        return 0;
    }
    
    Object* obj = nullptr;
    CCARRAY_FOREACH(_observers, obj)
    {
        NotificationObserver* observer = static_cast<NotificationObserver*>(obj);
        if (nullptr == observer)
            continue;
        
        if ( observer->getName() == name )
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
                                               const std::string& name,
                                               Object *sender)
{
    _target = target;
    _selector = selector;
    _sender = sender;
    
    _name = name;
    _handler = 0;
}

NotificationObserver::~NotificationObserver()
{

}

void NotificationObserver::performSelector(Object *sender)
{
    if (_target)
    {
		if (sender) {
			(_target->*_selector)(sender);
		} else {
			(_target->*_selector)(_sender);
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

const std::string& NotificationObserver::getName() const
{
    return _name;
}

Object* NotificationObserver::getSender() const
{
    return _sender;
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
