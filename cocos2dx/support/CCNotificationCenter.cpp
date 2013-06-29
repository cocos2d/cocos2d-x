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

static CCNotificationCenter *s_sharedNotifCenter = NULL;

CCNotificationCenter::CCNotificationCenter()
: _scriptHandler(0)
{
    _observers = CCArray::createWithCapacity(3);
    _observers->retain();
}

CCNotificationCenter::~CCNotificationCenter()
{
    _observers->release();
}

CCNotificationCenter *CCNotificationCenter::sharedNotificationCenter(void)
{
    if (!s_sharedNotifCenter)
    {
        s_sharedNotifCenter = new CCNotificationCenter;
    }
    return s_sharedNotifCenter;
}

void CCNotificationCenter::purgeNotificationCenter(void)
{
    CC_SAFE_RELEASE_NULL(s_sharedNotifCenter);
}

//
// internal functions
//
bool CCNotificationCenter::observerExisted(CCObject *target,const char *name)
{
    CCObject* obj = NULL;
    CCARRAY_FOREACH(_observers, obj)
    {
        CCNotificationObserver* observer = (CCNotificationObserver*) obj;
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
void CCNotificationCenter::addObserver(CCObject *target, 
                                       SEL_CallFuncO selector,
                                       const char *name,
                                       CCObject *obj)
{
    if (this->observerExisted(target, name))
        return;
    
    CCNotificationObserver *observer = new CCNotificationObserver(target, selector, name, obj);
    if (!observer)
        return;
    
    observer->autorelease();
    _observers->addObject(observer);
}

void CCNotificationCenter::removeObserver(CCObject *target,const char *name)
{
    CCObject* obj = NULL;
    CCARRAY_FOREACH(_observers, obj)
    {
        CCNotificationObserver* observer = (CCNotificationObserver*) obj;
        if (!observer)
            continue;
        
        if (!strcmp(observer->getName(),name) && observer->getTarget() == target)
        {
            _observers->removeObject(observer);
            return;
        }
    }
}

int CCNotificationCenter::removeAllObservers(CCObject *target)
{
    CCObject *obj = NULL;
    CCArray *toRemove = CCArray::create();

    CCARRAY_FOREACH(_observers, obj)
    {
        CCNotificationObserver *observer = (CCNotificationObserver *)obj;
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

void CCNotificationCenter::registerScriptObserver( CCObject *target, int handler,const char* name)
{
    
    if (this->observerExisted(target, name))
        return;
    
    CCNotificationObserver *observer = new CCNotificationObserver(target, NULL, name, NULL);
    if (!observer)
        return;
    
    observer->setHandler(handler);
    observer->autorelease();
    _observers->addObject(observer);
}

void CCNotificationCenter::unregisterScriptObserver(CCObject *target,const char* name)
{        
    CCObject* obj = NULL;
    CCARRAY_FOREACH(_observers, obj)
    {
        CCNotificationObserver* observer = (CCNotificationObserver*) obj;
        if (!observer)
            continue;
            
        if ( !strcmp(observer->getName(),name) && observer->getTarget() == target)
        {
            _observers->removeObject(observer);
        }
    }
}

void CCNotificationCenter::postNotification(const char *name, CCObject *object)
{
    CCArray* ObserversCopy = CCArray::createWithCapacity(_observers->count());
    ObserversCopy->addObjectsFromArray(_observers);
    CCObject* obj = NULL;
    CCARRAY_FOREACH(ObserversCopy, obj)
    {
        CCNotificationObserver* observer = (CCNotificationObserver*) obj;
        if (!observer)
            continue;
        
        if (!strcmp(name,observer->getName()) && (observer->getObject() == object || observer->getObject() == NULL || object == NULL))
        {
            if (0 != observer->getHandler())
            {
                CCScriptEngineProtocol* engine = CCScriptEngineManager::sharedManager()->getScriptEngine();
                engine->executeNotificationEvent(this, name);
            }
            else
            {
                observer->performSelector(object);
            }
        }
    }
}

void CCNotificationCenter::postNotification(const char *name)
{
    this->postNotification(name,NULL);
}

int CCNotificationCenter::getObserverHandlerByName(const char* name)
{
    if (NULL == name || strlen(name) == 0)
    {
        return -1;
    }
    
    CCObject* obj = NULL;
    CCARRAY_FOREACH(_observers, obj)
    {
        CCNotificationObserver* observer = (CCNotificationObserver*) obj;
        if (NULL == observer)
            continue;
        
        if ( 0 == strcmp(observer->getName(),name) )
        {
            return observer->getHandler();
            break;
        }
    }
    
    return -1;
}

////////////////////////////////////////////////////////////////////////////////
///
/// CCNotificationObserver
///
////////////////////////////////////////////////////////////////////////////////
CCNotificationObserver::CCNotificationObserver(CCObject *target, 
                                               SEL_CallFuncO selector,
                                               const char *name,
                                               CCObject *obj)
{
    _target = target;
    _selector = selector;
    _object = obj;
    
    _name = new char[strlen(name)+1];
    memset(_name,0,strlen(name)+1);
    
    string orig (name);
    orig.copy(_name,strlen(name),0);
    _handler = 0;
}

CCNotificationObserver::~CCNotificationObserver()
{
    CC_SAFE_DELETE_ARRAY(_name);
}

void CCNotificationObserver::performSelector(CCObject *obj)
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

CCObject *CCNotificationObserver::getTarget() const
{
    return _target;
}

SEL_CallFuncO CCNotificationObserver::getSelector() const
{
    return _selector;
}

char *CCNotificationObserver::getName() const
{
    return _name;
}

CCObject *CCNotificationObserver::getObject() const
{
    return _object;
}

int CCNotificationObserver::getHandler()
{
    return _handler;
}

void CCNotificationObserver::setHandler(int var)
{
    _handler = var;
}

NS_CC_END
